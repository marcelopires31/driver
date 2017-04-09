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

#ifndef __DRV_NFC_H__
#define __DRV_NFC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "drv_gpio.h"
#include "def_type.h"
#include "def_err.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "os.h"

typedef enum
{
	EN_DRV_NFC_0 = 0,
	EN_DRV_NFC_NUM
}EN_DRV_NFC_NO;

typedef enum
{
	EN_DRV_NFC_HANDLE_0 = 0,
	EN_DRV_NFC_HANDLE_1,
	EN_DRV_NFC_HANDLE_2,
	EN_DRV_NFC_HANDLE_3,
	EN_DRV_NFC_HANDLE_4,
	EN_DRV_NFC_HANDLE_NUM
}EN_DRV_NFC_HANDLE_NO;

/**
 * \brief
 * enumerate to indicate the operation's error
 */
typedef enum
{
	EN_DRV_NFC_ERR_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_NAND,	/*!< Operation invalid, because handle not close						*/
	EN_DRV_NFC_ERR_ACCESS,									/*!< Operation invalid, because handle without access right				*/
	EN_DRV_NFC_ERR_UNKNOW_DEVICE,								/*!< Invalid device name */
	EN_DRV_NFC_ERR_NOT_SUPPORT_ID,							/*!< Target device is not supported										*/
	EN_DRV_NFC_ERR_POWERDOWN									/*!< Operation invalid, because target device is in 'POWER DOWN' mode	*/
}EN_DRV_NFC_ERROR;

/**
 * \brief
 *  enumerate to Flash power control
 */
typedef enum
{
	EN_DRV_NFC_POWER_ON,									/*!< Flash Vpp pin on								*/
	EN_DRV_NFC_POWER_OFF,								 	/*!< Flash Vpp pin off								*/
	EN_DRV_NFC_STANDBY,								  	/*!< Flash setting to low frequency to standby mode	*/
	EN_DRV_NFC_PWRCTRL_NUM
}EN_DRV_NFC_PWRCTRL;

/**
 * \brief
 *  the NAND flash special purpose tag
 */
typedef enum
{
	EN_DRV_NFC_STAG_APP1,
	EN_DRV_NFC_STAG_APP2,
	EN_DRV_NFC_STAG_DB,
	EN_DRV_NFC_STAG_RESOURCE,
	EN_DRV_NFC_STAG_NUM
}EN_DRV_NFC_STAG;

/**
 * \brief
 *  the device hardware setting like power pin , base address...
 */
typedef struct
{
	EN_DRV_NFC_NO				enNFCNo;                    /*!< NAND flash driver number */
	ST_GPIO						stPowerDownPin;				/*!< the Vcc GPIO pin connect the Flash device								*/
	os_mempool_handle			u32MemHandle;				/*!< A memory pool handle for VDEC module	*/
}ST_NFC_Init, *PST_NFC_Init;

/**
 * \brief
 *  Flash callback event type
 */
typedef enum
{
	EN_DRV_NFC_EVENT_RD,							/*!< Indicate the read event type	*/
	EN_DRV_NFC_EVENT_WR,							/*!< Indicate the write event type	*/
	EN_DRV_NFC_EVENT_CHANGE_CONFIG,				/*!< Indicate the config changed event type	*/
	EN_DRV_NFC_EVENT_CLOSE,						/*!< Indicate the close event type	*/
	EN_DRV_NFC_EVENT_POWER_DOWN,					/*!< Indicate the power down event type	*/
	EN_DRV_NFC_EVENT_TERM,						/*!< Indicate the terminate event type	*/
	EN_DRV_NFC_EVENT_NUM
}EN_DRV_NFC_EVENT_TYPE;

/**
 * \brief
 *  The flash callback function
 * \param	u32Handle		(Output) An open handle, as returned by the Open function
 * \param	enEventType		(Output) Callback function event type
 * \param	enStatus		(Output) Operation status
 * \param	pu32para		(Output) It is data information. It's context will depend on enEventType.
 *
 */
typedef void (*DRV_NFC_CALLBACK)(u32 u32Handle, EN_DRV_NFC_EVENT_TYPE enEventType, ErrorCode enStatus, u32* pu32para);

/**
 * \brief
 *  Structure of flash open
 */
typedef struct
{
    os_mempool_handle               u32AVMemHandle;                 /*!< av memory pool handle, if middleware want driver to allocate bitstream/frame buffer, need give memory pool handle to driver */
	DRV_NFC_CALLBACK				pfnNFCCallback;						/*!< Interrupt Flash callback function				*/

    u32                             u32EvtHandle;                  /*!< Event handle for NFC   */
}ST_NFC_Open, *PST_NFC_Open;

/**
 * \brief
 *  the flash structure include the Flash device ID,manufacture ID, and Block info
 */
typedef struct
{
    u32   					u32DeviceID;							/*!< The NAND Flash Device ID               */
    u32   					u32DeviceSize;                          /*!< NAND flash device size (bytes)    */
    u32   					u32Blockbytes;                          /*!< NAND flash block size             */
    u32    					u32NVRAMbytes;                          /*!< NAND flash page size              */
}ST_NFC_Info, *PST_NFC_Info;

u8* DRV_NFC_GetVersion (void);
/*!\fn u8* DRV_NFC_GetVersion (void)
 * \brief
 *		Get the Module version number
 *
 * \return	Pointer of driver version
 */

ErrorCode DRV_NFC_Initialize (DRV_DeviceNameType DeviceName, PST_NFC_Init pstInit);
/*!\fn ErrorCode DRV_NFC_Initialize (DRV_DeviceNameType DeviceName, PST_NFC_Init pstInit)
 * \brief
 *		Initial the Flash device with PST_NFC_Init setting
 *
 * \param DeviceName								(Input) Target device name
 * \param pstInit									(Input) Pointer of initial parameter
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_NFC_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is already initialized
 * \retval EN_DRV_NFC_ERR_NOT_SUPPORT_ID		Target device is not supported
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_NFC_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief
 *		Terminate the usage of specific device
 *
 * \param DeviceName		(Input) Target device number
 * \param b8Force			(Input) Force terminate the device or not
 * \code
	True, Terminate the device right now
	False, Wait until all open handles close then terminate
   \endcode
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_NFC_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval EN_DRV_NFC_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout  
 */

ErrorCode DRV_NFC_GetInfo (DRV_DeviceNameType DeviceName, PST_NFC_Info pstInfo);
/*!\fn ErrorCode DRV_NFC_GetInfo (DRV_DeviceNameType DeviceName, ST_NFC_Info pstInfo)
 * \brief
 *		Get information of target device
 *
 * \param DeviceName				(Input)		Target device name
 * \param pstInfo					(Output)	Buffer which will store device information after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_NFC_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_NFC_PWRCTRL enPwrCtrl, bool bForce);
/*!\fn ErrorCode DRV_NFC_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_NFC_PWRCTRL enPwrCtrl, bool b8Force)
 * \brief
 *		Control power mode of target device
 *
 * \param DeviceName			(Input)	Target device name
 * \param enPwrCtrl				(Input) The setting of power mode
 * \code
	  enPwrCtrl						description
	---------------------------------------------------------------------
	EN_DRV_NFC_POWER_ON 		Flash device in power up mode
	EN_DRV_NFC_POWER_OFF 		Flash device in power off mode     (low Vcc pin)
	EN_DRV_NFC_STANDBY  		Flash device in standby mode       (low frequency)
	\endcode
 * \param b8Force				(Input) Force power down the device or not
 * \code
	True, Power control the device right now
	False, Wait until all open handles closed then power control the device
   \endcode
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_NFC_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval EN_DRV_NFC_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_Open (DRV_DeviceNameType DeviceName, PST_NFC_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_NFC_Open (DRV_DeviceNameType DeviceName, PST_NFC_Open pstOpen, u32 *pu32Handle)
 * \brief
 *		To open a device handle, user control the device through this handle
 *
 * \param DeviceName					(Input)	Target device name
 * \param pstOpen						(Input)	Open parameter
 * \param pu32Handle					(Output)Returned handle of the opened device
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval EN_DRV_NFC_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval ERROR_INITIALISED					The driver is not initialized
 * \retval EN_DRV_NFC_ERR_POWERDOWN			Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval ERROR_NO_FREE_HANDLE					No free handle for the device
 * \retval ERROR_TIMEOUT						Operation invalid, because the timeout
 */ 

ErrorCode DRV_NFC_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_NFC_Close (u32* pu32Handle)
 * \brief
 *		Release resource associated with a previous opened handle
 *
 * \param pu32Handle				(Input) An open handle, as returned by the Open function
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval EN_DRV_NFC_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_WriteBootSector(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrite);
/*!\fn DRV_NFC_WriteBootSector(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrite)
 * \brief
 *		Burn u32Size of data in pu8buffer to BootSector
 *
 * \param u32Handle			(Input) An open handle, as returned by the open function
 * \param pu8Buffer			(Input) Buffer to be transferred
 * \param u32Size			(Input) Length of buffer
 * \param pu32NumOfWrite	(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_NFC_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_NFC_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_WriteWithTag(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, EN_DRV_NFC_STAG enNFC_TAG, u32 *pu32NumOfWrite);
/*!\fn ErrorCode DRV_NFC_WriteWithTag(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, EN_DRV_NFC_STAG enNFC_TAG, u32 *pu32NumOfWrite)
 * \brief
 *		Burn u32Size of data in pu8buffer to NAND Flash special Tag
 *
 * \param u32Handle			(Input) An open handle, as returned by the open function
 * \param pu8Buffer			(Input) Buffer to be transferred
 * \param u32Size			(Input) Length of buffer
 * \param enNFC_TAG			(Input) NAND flash Tag
 * \param pu32NumOfWrite	(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_NFC_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_NFC_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_ReadWithTag(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, EN_DRV_NFC_STAG enNFC_TAG, u32 *pu32NumOfRead);
/*!\fn ErrorCode DRV_NFC_ReadWithTag(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, EN_DRV_NFC_STAG enNFC_TAG, u32 *pu32NumOfRead)
 * \brief
 *		Read u32Size of data in pu8buffer from NAND Flash special Tag
 *
 * \param u32Handle			(Input) An open handle, as returned by the open function
 * \param pu8Buffer			(Input) Buffer to be transferred
 * \param u32Size			(Input) Length of buffer
 * \param enNFC_TAG			(Input) NAND flash Tag
 * \param pu32NumOfRead  	(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_NFC_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_NFC_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_WriteNVRam(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrite);
/*!\fn ErrorCode DRV_NFC_WriteNVRam(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrite)
 * \brief
 *		Burn u32Size of data in pu8buffer to simulator NVRAM
 *
 * \param u32Handle			(Input) An open handle, as returned by the open function
 * \param pu8Buffer			(Input) Buffer to be transferred
 * \param u32Size			(Input) Length of buffer
 * \param pu32NumOfWrite	(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_NFC_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_NFC_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_ReadNVRam(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfRead);
/*!\fn ErrorCode DRV_NFC_ReadNVRam(const u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfRead)
 * \brief
 *		Read u32Size of data in pu8buffer from simulator NVRAM
 *
 * \param u32Handle			(Input) An open handle, as returned by the open function
 * \param pu8Buffer			(Input) Buffer to be transferred
 * \param u32Size			(Input) Length of buffer
 * \param pu32NumOfRead  	(Output)Buffer that store length of actual transferred data after operation success
 *
 * \return Flash Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval EN_DRV_NFC_ERR_POWERDOWN		Operation invalid, because target device is in 'POWER DOWN' mode
 * \retval EN_DRV_NFC_ERR_ACCESS			Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT					Operation invalid, because the timeout
 */

ErrorCode DRV_NFC_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_NFC_Lock (u32 u32Handle, bool b8Lock)
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
 * \retval EN_DRV_NFC_ERR_ACCESS		Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT				Timeout
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif

