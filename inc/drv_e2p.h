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

#ifndef __DRV_E2P_H__
#define __DRV_E2P_H__

#include "os.h"
#include "drv_2ws.h"
#include "def_type.h"
#include "def_err.h"

typedef enum
{
	EN_DRV_E2P_0,
	EN_DRV_E2P_1,
	EN_DRV_E2P_2,
	EN_DRV_E2P_3,
	EN_DRV_E2P_NUM
}EN_DRV_E2P_NO;

/**
 * \brief
 * enumerate to indicate the error of operation
 */
typedef enum
{
	EN_DRV_E2P_ERR_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_E2P,	/*!< Operation invalid, because handle not close			*/
	EN_DRV_E2P_ERR_ACCESS, 									/*!< Operation invalid, because handle without access right */
	EN_DRV_E2P_ERR_UNKNOW_DEVICE							/*!< Invalid device name */
}EN_DRV_E2P_ERROR;

typedef enum
{
	EN_DRV_E2P_EVENT_RX,			/*!< Indicate the receive event type	*/
	EN_DRV_E2P_EVENT_TX,			/*!< Indicate the transmit event type	*/
	EN_DRV_E2P_EVENT_TERM,			/*!< Indicate the terminate event type	*/
	EN_DRV_E2P_EVENT_NUM
}EN_DRV_E2P_EVENT_TYPE;

/**
 * \brief
 *  the E2P callback function
 * \param	u32Handle		(Output) An open handle, as returned by the open function
 * \param	enEventType		(Output) Event type of callback function
 * \param	enStatus		(Output) Operation status
 * \param	pu32para		(Output) It is data information. It's context will depend on enEventType.
 *
 */
typedef void (*DRV_E2P_CALLBACK) (u32 u32Handle, EN_DRV_E2P_EVENT_TYPE enEventType, ErrorCode enStatus, u32* pu32para);

/**
 * \brief
 *  Structure of E2P Initial Parameter
 */
typedef struct
{
	os_mempool_handle	u32MemPoolHandle;				/*!< A memory pool handle for E2P module	*/
	EN_DRV_E2P_NO		enE2pNo;
	DRV_DeviceNameType	I2CBusName;						/*!< IIC bus name which target device use	*/
	u8					u8DevID;						/*!< Device ID								*/
	u16					u16E2PSize;						/*!< Device size							*/
}ST_E2P_Init, *PST_E2P_Init;

/**
 * \brief
 *  Structure of E2P Open Parameter
 */
typedef struct
{
	DRV_E2P_CALLBACK		pfnE2PCallback;				/*!< E2P callback function	*/
}ST_E2P_Open, *PST_E2P_Open;

ErrorCode DRV_E2P_Initialize (DRV_DeviceNameType DeviceName, PST_E2P_Init pstInit);
/*!\fn ErrorCode DRV_E2P_Initialize (DRV_DeviceNameType DeviceName, PST_E2P_Init pstInit)
 * \brief
 *		Initial the E2P device with PST_E2P_Init setting
 *
 * \param DeviceName		(Input) Target device name
 * \param pstInit			(Input) Pointer of initial parameter
 *
 * \return E2P Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval EN_DRV_E2P_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval ERROR_INITIALISED				The driver is already initialized
 */

ErrorCode DRV_E2P_Terminate (DRV_DeviceNameType DeviceName, bool bForce);
/*!\fn ErrorCode DRV_E2P_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
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
 * \return E2P Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval EN_DRV_E2P_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_INITIALISED				Device has not been initialized
 * \retval EN_DRV_E2P_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 */

ErrorCode DRV_E2P_Open (DRV_DeviceNameType DeviceName, PST_E2P_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_E2P_Open (DRV_DeviceNameType DeviceName, PST_E2P_Open pstOpen, u32 *pu32Handle)
 * \brief
 *			To open a device handle, user control the device through this handle
 * \param	DeviceName			(Input)	Target device name
 * \param	pstOpen				(Input)	Open parameter
 * \param	pu32Handle			(Output)Returned handle of the opened device
 *
 * \return	E2P Operation Error Code
 * \retval	ERROR_NO_ERROR					no error
 * \retval	EN_DRV_E2P_ERR_UNKNOW_DEVICE	Invalid device name
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_INITIALISED				Device has not been initialized
 * \retval	ERROR_NO_FREE_HANDLE			No free handle for the device
 */

ErrorCode DRV_E2P_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_E2P_Close (u32* pu32Handle)
 * \brief
 * 		Release resource associated with a previous opened handle
 *
 * \param	pu32Handle     				(Input) An open handle, as returned by the Open function
 *
 * \return	E2P Operation Error Code
 * \retval	ERROR_NO_ERROR               no error
 * \retval	ERROR_INVALID_HANDLE         Handle is not valid
 */

ErrorCode DRV_E2P_Read (const u32 u32Handle, u8 * pu8Buffer, u16 u16Length, u16 u16Offset, u32 *pu32NumOfTransferrd, u32 u32TimeOut);
/*!\fn ErrorCode DRV_E2P_Read (const u32 u32Handle, u8 * pu8Buffer, u16 u16Length, u16 u16Offset, u32 *pu32NumOfTransferrd, u32 u32TimeOut)
 * \brief
 *		Receive u16Length of data start from u16Offset address associate with specified u32Handle
 *
 * \param u32Handle     (Input)		An open handle, as returned by the Open function
 * \param pu8Buffer     (Output)	Buffer to put data read
 * \param u16Length     (Input)		Size to be read
 * \param u16Offset		(Input)		Offset address from start
 * \param pu32NumOfTransferrd (Output)	Buffer that store length of actual transferred data after operation success
 * \param u32TimeOut    (Input)		Timeout in MS for operation
 *
 * \return E2P Operation Error Code
 * \retval ERROR_NO_ERROR               no error
 * \retval ERROR_INVALID_HANDLE         Handle is not valid
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval EN_DRV_E2P_ERR_ACCESS		Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT				Timeout
 */

ErrorCode DRV_E2P_Write (const u32 u32Handle, u8* pu8Buffer, u16 u16Length, u16 u16Offset, u32 *pu32NumOfTransferrd, u32 u32TimeOut);
/*!\fn ErrorCode DRV_E2P_Write (const u32 u32Handle, u8* pu8Buffer, u16 u16Length, u16 u16Offset, u32 *pu32NumOfTransferrd, u32 u32TimeOut)
 * \brief
 *		Write u16Length of data in pu8buffer to u16Offset address of specified u32Handle
 *
 * \param u32Handle				(Input)	An open handle, as returned by the open function
 * \param pu8Buffer				(Input)	Buffer to be transferred
 * \param u16Length				(Input)	Length of buffer
 * \param u16Offset				(Input)	Offset address from start
 * \param pu32NumOfTransferrd	(Output)Buffer that store length of actual transferred data after operation success
 * \param u32TimeOut			(Input)	Timeout in MS for operation
 *
 * \return E2P Operation Error Code
 * \retval ERROR_NO_ERROR				no error
 * \retval ERROR_INVALID_HANDLE			Handle is not valid
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval EN_DRV_E2P_ERR_ACCESS		Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT				Timeout
 */

ErrorCode DRV_E2P_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_E2P_Lock (u32 u32Handle, bool b8Lock)
 * \brief
 *			Change property of lock to specified handle, no other handles can use resource until it is unlock
 *
 * \param	u32Handle			(Input) An open handle, as returned by the open function
 * \param	b8Lock				(Input) Lock the resource or not
   \code
		True, Lock the resource
		False, Unlock the resource
   \endcode
 * \return E2P Operation Error Code
 * \retval ERROR_NO_ERROR				Operation success
 * \retval ERROR_INVALID_HANDLE			Operation invalid, because handle not open
 * \retval EN_DRV_E2P_ERR_ACCESS		Operation invalid, because handle without access right
 */

u8* DRV_E2P_GetVersion (void);
/*!\fn u8* DRV_E2P_GetVersion (void)
 *
 * \brief
 *		Get the Module version number
 *
 *
 * \return	Pointer of driver version
 */
#endif /* __DRV_E2P_H__ */
