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

#ifndef __DRV_NEO_H__
#define __DRV_NEO_H__

#include "os.h"
#include "drv_2ws.h"
#include "def_type.h"
#include "def_err.h"

typedef enum
{
	EN_DRV_NEO_0,
	EN_DRV_NEO_1,
	EN_DRV_NEO_2,
	EN_DRV_NEO_3,
	EN_DRV_NEO_NUM
}EN_DRV_NEO_NO;

/**
 * \brief
 * enumerate to indicate the error of operation
 */
typedef enum
{
	EN_DRV_NEO_ERR_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_NEO,	/*!< Operation invalid, because handle not close			*/
	EN_DRV_NEO_ERR_ACCESS, 									/*!< Operation invalid, because handle without access right */
	EN_DRV_NEO_ERR_UNKNOW_DEVICE							/*!< Invalid device name */
}EN_DRV_NEO_ERROR;

typedef enum
{
	EN_DRV_NEO_EVENT_RX,			/*!< Indicate the receive event type	*/
	EN_DRV_NEO_EVENT_TX,			/*!< Indicate the transmit event type	*/
	EN_DRV_NEO_EVENT_TERM,			/*!< Indicate the terminate event type	*/
	EN_DRV_NEO_EVENT_NUM
}EN_DRV_NEO_EVENT_TYPE;

/**
 * \brief
 *  the NEO callback function
 * \param	u32Handle		(Output) An open handle, as returned by the open function
 * \param	enEventType		(Output) Event type of callback function
 * \param	enStatus		(Output) Operation status
 * \param	pu32para		(Output) It is data information. It's context will depend on enEventType.
 *
 */
typedef void (*DRV_NEO_CALLBACK) (u32 u32Handle, EN_DRV_NEO_EVENT_TYPE enEventType, ErrorCode enStatus, u32* pu32para);

/**
 * \brief
 *  Structure of NEO Initial Parameter
 */
typedef struct
{
	os_mempool_handle	u32MemPoolHandle;				/*!< A memory pool handle for NEO module	*/
	EN_DRV_NEO_NO		enNeoNo;
	DRV_DeviceNameType	I2CBusName;						/*!< IIC bus name which target device use	*/
	u8					u8DevID;						/*!< Device ID								*/
	u16					u16NEOSize;						/*!< Device size							*/
}ST_NEO_Init, *PST_NEO_Init;

/**
 * \brief
 *  Structure of NEO Open Parameter
 */
typedef struct
{
	DRV_NEO_CALLBACK		pfnNEOCallback;				/*!< NEO callback function	*/
}ST_NEO_Open, *PST_NEO_Open;

ErrorCode DRV_NEO_Initialize (DRV_DeviceNameType DeviceName, PST_NEO_Init pstInit);
/*!\fn ErrorCode DRV_NEO_Initialize (DRV_DeviceNameType DeviceName, PST_NEO_Init pstInit)
 * \brief
 *		Initial the NEO device with PST_NEO_Init setting
 *
 * \param DeviceName		(Input) Target device name
 * \param pstInit			(Input) Pointer of initial parameter
 *
 * \return NEO Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval EN_DRV_NEO_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval ERROR_INITIALISED				The driver is already initialized
 */

ErrorCode DRV_NEO_Terminate (DRV_DeviceNameType DeviceName, bool bForce);
/*!\fn ErrorCode DRV_NEO_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
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
 * \return NEO Operation Error Code
 * \retval ERROR_NO_ERROR					no error
 * \retval EN_DRV_NEO_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval ERROR_INITIALISED				Device has not been initialized
 * \retval EN_DRV_NEO_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 */

ErrorCode DRV_NEO_Open (DRV_DeviceNameType DeviceName, PST_NEO_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_NEO_Open (DRV_DeviceNameType DeviceName, PST_NEO_Open pstOpen, u32 *pu32Handle)
 * \brief
 *			To open a device handle, user control the device through this handle
 * \param	DeviceName			(Input)	Target device name
 * \param	pstOpen				(Input)	Open parameter
 * \param	pu32Handle			(Output)Returned handle of the opened device
 *
 * \return	NEO Operation Error Code
 * \retval	ERROR_NO_ERROR					no error
 * \retval	EN_DRV_NEO_ERR_UNKNOW_DEVICE	Invalid device name
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_INITIALISED				Device has not been initialized
 * \retval	ERROR_NO_FREE_HANDLE			No free handle for the device
 */

ErrorCode DRV_NEO_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_NEO_Close (u32* pu32Handle)
 * \brief
 * 		Release resource associated with a previous opened handle
 *
 * \param	pu32Handle     				(Input) An open handle, as returned by the Open function
 *
 * \return	NEO Operation Error Code
 * \retval	ERROR_NO_ERROR               no error
 * \retval	ERROR_INVALID_HANDLE         Handle is not valid
 */

ErrorCode DRV_NEO_Read (u8 * pu8Buffer, u16 u16Length);
/*!\fn ErrorCode DRV_NEO_Read (const u32 u32Handle, u8 * pu8Buffer, u16 u16Length, u16 u16Offset, u32 *pu32NumOfTransferrd, u32 u32TimeOut)
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
 * \return NEO Operation Error Code
 * \retval ERROR_NO_ERROR               no error
 * \retval ERROR_INVALID_HANDLE         Handle is not valid
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval EN_DRV_NEO_ERR_ACCESS		Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT				Timeout
 */

ErrorCode DRV_NEO_Write (u8* pu8Buffer, u16 u16Length );
/*!\fn ErrorCode DRV_NEO_Write (const u32 u32Handle, u8* pu8Buffer, u16 u16Length, u16 u16Offset, u32 *pu32NumOfTransferrd, u32 u32TimeOut)
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
 * \return NEO Operation Error Code
 * \retval ERROR_NO_ERROR				no error
 * \retval ERROR_INVALID_HANDLE			Handle is not valid
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval EN_DRV_NEO_ERR_ACCESS		Operation invalid, because handle without access right
 * \retval ERROR_TIMEOUT				Timeout
 */


#endif /* __DRV_NEO_H__ */
