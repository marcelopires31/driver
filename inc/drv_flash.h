//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide Flash Control
//	Sources	:
//***************************************************************************
//
// Modification use :
//**************************************************************************
//	Update
//
//	Date  	:
//	Name	:
//	Description	:
//
//	Item							  Source
//   ----------------------------------------		-------------------

#ifndef __DRV_FLASH_H__
#define __DRV_FLASH_H__

#include "os.h"
#include "drv_gpio.h"
#include "def_type.h"
#include "def_err.h"

typedef enum
{
	EN_DRV_FLASH_0,
	EN_DRV_FLASH_NUM
}EN_DRV_FLASH_NO;

/**
 * \brief
 * enumerate to indicate the operation's error
 */
typedef enum
{
	EN_DRV_FLASH_ERR_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_FLASH,	/*!< Operation invalid, because handle not close						*/
	EN_DRV_FLASH_ERR_ACCESS,									/*!< Operation invalid, because handle without access right				*/
	EN_DRV_FLASH_ERR_UNKNOW_DEVICE,								/*!< Invalid device name */
	EN_DRV_FLASH_ERR_NOT_SUPPORT_ID,							/*!< Target device is not supported										*/
	EN_DRV_FLASH_ERR_NOT_SUPPORT_READ_MODE,						/*!< Target device does not support this read mode						*/
	EN_DRV_FLASH_ERR_POWERDOWN									/*!< Operation invalid, because target device is in 'POWER DOWN' mode	*/
}EN_DRV_FLASH_ERROR;

/**
 * \brief
 * enumerate to Serial Peripheral Interface Flash read mode
 */
typedef enum
{
	EN_DRV_FLASH_DEFAULT,									/*!< SPI Flash Read Mode default				*/
	EN_DRV_FLASH_READ_NORMAL,								/*!< SPI Flash Normal Read mode					*/
	EN_DRV_FLASH_READ_FAST,									/*!< SPI Flash Fast Read mode					*/
	EN_DRV_FLASH_READ_FAST_DUAL_OUTPUT,						/*!< SPI Flash Fast Read Dual Output mode		*/
	EN_DRV_FLASH_READ_FAST_DUAL_INPUT_OUTPUT,				/*!< SPI Flash Fast Read Dual Input Output mode	*/
	EN_DRV_FLASH_MODE_NUM
}EN_DRV_FLASH_READ_MODE;

/**
 * \brief
 *  enumerate to Flash power control
 */
typedef enum
{
	EN_DRV_FLASH_POWER_ON,									/*!< Flash Vpp pin on								*/
	EN_DRV_FLASH_POWER_OFF,								 	/*!< Flash Vpp pin off								*/
	EN_DRV_FLASH_STANDBY,								  	/*!< Flash setting to low frequency to standby mode	*/
	EN_DRV_FLASH_PWRCTRL_NUM
}EN_DRV_FLASH_PWRCTRL;

/**
 *\brief
 * the flash structure include the Flash block and sector information
 */
typedef struct
{
	u32						u32DeviceSize;				/*!< Device size (byte)													*/
	u8						u8NumOfBlocks;				/*!< Number of sector defs.												*/
														/*!< This structure record the sector size and number of sectors.	*/
	struct
	{
		u32 				u32SectorSize;				/*!< Size of sector (byte)												*/
		u16  				u16NumOfSectors;			/*!< Number of sector of this size											*/
	}stBlock[8];										/*!<  Max of 256, but 8 is good  											*/
}ST_FLASH_Query, *PST_FLASH_Query;

/**
 * \brief
 *  the device hardware setting like power pin , base address...
 */
typedef struct
{
	os_mempool_handle			u32MemPoolHandle;			/*!< A memory pool handle for Flash module	*/
	EN_DRV_FLASH_NO				enFlashNo;                  /*!< the flash device number                */
	ST_GPIO						stPowerDownPin;				/*!< the Vcc GPIO pin connect the Flash device								*/
	bool						bSPI;						/*!< T: Flash is SPI Flash  F: Flash is PPI Flash							*/
	bool						bByteMode;					/*!< Byte or Word mode. True: Byte mode, FALSE : Word mode.					*/
															/*!< Ex: Serial flash => Byte mode only, Parallel flash => Byte or Word mode*/
	u16							u16ClkMHz;					/*!< The Flash's CLK (MHz) for SPI only										*/
	EN_DRV_FLASH_READ_MODE		enReadMode;					/*!< The Flash's Read mode for SPI only										*/
}ST_FLASH_Init, *PST_FLASH_Init;

/**
 * \brief
 *  Flash callback event type
 */
typedef enum
{
	EN_DRV_FLASH_EVENT_RD,							/*!< Indicate the read event type	*/
	EN_DRV_FLASH_EVENT_WR,							/*!< Indicate the write event type	*/
	EN_DRV_FLASH_EVENT_ERASE,						/*!< Indicate the erase event type	*/
	EN_DRV_FLASH_EVENT_CHANGE_CONFIG,				/*!< Indicate the config changed event type	*/
	EN_DRV_FLASH_EVENT_CLOSE,						/*!< Indicate the close event type	*/
	EN_DRV_FLASH_EVENT_POWER_DOWN,					/*!< Indicate the power down event type	*/
	EN_DRV_FLASH_EVENT_TERM,						/*!< Indicate the terminate event type	*/
	EN_DRV_FLASH_EVENT_NUM
}EN_DRV_FLASH_EVENT_TYPE;

/**
 * \brief
 *  The flash callback function
 * \param	u32Handle		(Output) An open handle, as returned by the Open function
 * \param	enEventType		(Output) Callback function event type
 * \param	enStatus		(Output) Operation status
 * \param	pu32para		(Output) It is data information. It's context will depend on enEventType.
 *
 */
typedef void (*DRV_FLASH_CALLBACK)(u32 u32Handle, EN_DRV_FLASH_EVENT_TYPE enEventType, ErrorCode enStatus, u32* pu32para);

/**
 * \brief
 *  Structure of flash open
 */
typedef struct
{
	DRV_FLASH_CALLBACK				pfnFlashCallback;						/*!< Interrupt Flash callback function				*/
}ST_FLASH_Open, *PST_FLASH_Open;

/**
 * \brief
 *  the flash structure include the Flash device ID,manufacture ID, and Block info
 */
typedef struct
{
	bool					bSector4kMode;				/*!< whether support 4k erase mode for SPI								*/
	u32						u32ManuFactureID;			/*!< manufacture ID of the Flash device									*/
	u32				 		u32DeviceID;				/*!< Device ID of the Flash device										*/
	ST_FLASH_Query			stSectorQuery;				/*!< Struct for record Flash sectors info for SPI always 64K block		*/

}ST_FLASH_Info, *PST_FLASH_Info;

u8* DRV_FLASH_GetVersion (void);
/*!\fn u8* DRV_FLASH_GetVersion (void)
 * \brief
 *		Get the Module version number
 *
 * \return	Pointer of driver version
 */

ErrorCode DRV_FLASH_Initialize (DRV_DeviceNameType DeviceName, PST_FLASH_Init pstInit);
/*!\fn ErrorCode DRV_FLASH_Initialize (DRV_DeviceNameType DeviceName, PST_FLASH_Init pstInit)
 * \brief
 *		Initial the Flash device with PST_FLASH_Init setting
 *
 * \param DeviceName								(Input) Target device name
 * \param pstInit									(Input) Pointer of initial parameter
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_FLASH_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is already initialized
 * \retval EN_DRV_FLASH_ERR_NOT_SUPPORT_ID		Target device is not supported
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */

ErrorCode DRV_FLASH_Terminate (DRV_DeviceNameType DeviceName, bool bForce);
/*!\fn ErrorCode DRV_FLASH_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief
 *		Terminate the usage of specific device
 *
 * \param DeviceName		(Input) Target device name
 * \param b8Force			(Input) Force terminate the device or not
 * \code
	True, Terminate the device right now
	False, Wait until all open handles close then terminate
   \endcode
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_FLASH_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval EN_DRV_FLASH_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout  
 */

ErrorCode DRV_FLASH_GetInfo (DRV_DeviceNameType DeviceName, PST_FLASH_Info pstInfo);
/*!\fn ErrorCode DRV_FLASH_GetInfo (DRV_DeviceNameType DeviceName, PST_FLASH_Info pstInfo)
 * \brief
 *		Get information of target device
 *
 * \param DeviceName				(Input)		Target device name
 * \param pstInfo					(Output)	Buffer which will store device information after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_FLASH_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */

ErrorCode DRV_FLASH_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_FLASH_PWRCTRL enPwrCtrl, bool bForce);
/*!\fn ErrorCode DRV_FLASH_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_FLASH_PWRCTRL enPwrCtrl, bool b8Force)
 * \brief
 *		Control power mode of target device
 *
 * \param DeviceName			(Input) Target device name
 * \param enPwrCtrl				(Input) The setting of power mode
 * \code
	  enPwrCtrl						description
	---------------------------------------------------------------------
	EN_DRV_FLASH_POWER_ON 		Flash device in power up mode
	EN_DRV_FLASH_POWER_OFF 		Flash device in power off mode     (low Vcc pin)
	EN_DRV_FLASH_STANDBY  		Flash device in standby mode       (low frequency)
	\endcode
 * \param b8Force				(Input) Force power down the device or not
 * \code
	True, Power control the device right now
	False, Wait until all open handles closed then power control the device
   \endcode
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_FLASH_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval EN_DRV_FLASH_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */

ErrorCode DRV_FLASH_Open (DRV_DeviceNameType DeviceName, PST_FLASH_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_FLASH_Open (DRV_DeviceNameType DeviceName, PST_FLASH_Open pstOpen, u32 *pu32Handle)
 * \brief
 *		To open a device handle, user control the device through this handle
 *
 * \param DeviceName					(Input)	Target device name
 * \param pstOpen						(Input)	Open parameter
 * \param pu32Handle					(Output)Returned handle of the opened device
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_FLASH_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval EN_DRV_FLASH_ERR_POWERDOWN			Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval ERROR_NO_FREE_HANDLE					No free handle for the device
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */ 

ErrorCode DRV_FLASH_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_FLASH_Close (u32* pu32Handle)
 * \brief
 *		Release resource associated with a previous opened handle
 *
 * \param pu32Handle				(Input) An open handle, as returned by the Open function
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval EN_DRV_FLASH_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_FLASH_Write (const u32 u32Handle, u8 *pu8Buffer, u32 u32Offset, u32 u32Size, u32 *pu32NumOfWrited);
/*!\fn ErrorCode DRV_FLASH_Write (const u32 u32Handle, u8 *pu8Buffer, u32 u32Offset, u32 u32Size, u32 *pu32NumOfWrited)
 * \brief
 *		Burn u32Size of data in pu8buffer to u32Offset address of specified u32Handle
 *
 * \param u32Handle			(Input) An open handle, as returned by the open function
 * \param pu8Buffer			(Input) Buffer to be transferred
 * \param u32Offset			(Input) Offset address from start
 * \param u32Size			(Input) Length of buffer
 * \param pu32NumOfWrited	(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_FLASH_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_FLASH_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_FLASH_Read (const u32 u32Handle, u8 *pu8Buffer, u32 u32Offset, u32 u32Size, u32 *pu32NumOfRead);
/*!\fn ErrorCode DRV_FLASH_Read (const u32 u32Handle, u8 *pu8Buffer, u32 u32Offset, u32 u32Size, u32 *pu32NumOfRead)
 * \brief
 *		Read u32Size of data start from u32Offset address associate with specified u32Handle and store in pu8Buffer
 * \param u32Handle			(Input)	An open handle, as returned by the Open function
 * \param pu8Buffer			(Output)Buffer to put data read
 * \param u32Offset			(Input)	Offset address from start
 * \param u32Size			(Input)	Size to be read
 * \param pu32NumOfRead		(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_FLASH_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_FLASH_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Timeout
 */

ErrorCode DRV_FLASH_Erase (const u32 u32Handle, u32 u32Offset, u32 u32Size, u32 *pu32NumOfErased);
/*!\fn ErrorCode DRV_FLASH_Erase (const u32 u32Handle, u32 u32Offset, u32 u32Size, u32 *pu32NumOfErased)
 * \brief
 *		Erase u32Size of data start from u32offset address associate with u32Handle. \n
 *		If target range does not fit device sector bounding, this operation will return ERROR_BAD_PARAMETER
 *
 * \param u32Handle			(Input) An open handle, as returned by the Open function
 * \param u32Offset			(Input) Offset address from start
 * \param u32Size			(Input) Size to be erase
 * \param pu32NumOfErased	(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_FLASH_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_FLASH_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Timeout
 */

ErrorCode DRV_FLASH_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_FLASH_Lock (u32 u32Handle, bool b8Lock)
 * \brief
 *		Change property of lock to specified handle, no other handles can use resource until it is unlock
 *
 * \param u32Handle			(Input) An open handle, as returned by the Open function
 * \param b8Lock			(Input) Lock the resource or not
   \code
	True, Lock the resource
	False, Unlock the resource
   \endcode
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR				no error
 * \retval ERROR_INVALID_HANDLE			Handle is not valid
 * \retval EN_DRV_FLASH_ERR_ACCESS		Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT				Timeout
 */

ErrorCode DRV_FLASH_GetPhysicalAddr(u32 u32Handle, u32 u32Offset, u32* pu32PhysicalAddr);
/*!\fn ErrorCode DRV_FLASH_GetPhysicalAddr(u32 u32Handle, u32 u32Offset, u32* pu32PhysicalAddr)
 * \brief
 *		Get the physical address of flash.
 *
 * \param u32Handle			(Input) An open handle, as returned by the Open function
 * \param u32Offset			(Input) Flash offset address
 * \param pu32PhysicalAddr	(Output) Retrun the physical address of flash
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR				no error
 * \retval ERROR_INVALID_HANDLE			Handle is not valid
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 */
#endif

