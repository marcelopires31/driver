//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide UART Control
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
//	Item			                  Source
//   ----------------------------------------		-------------------


#ifndef __UART_H__
#define __UART_H__

#include "os.h"
#include "def_type.h"
#include "def_err.h"

/**
 * \brief
 * enumerate to indicate the error of operation
 */
typedef enum
{
	EN_DRV_UART_ERR_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_UART,	/*!< Operation invalid, because handle not close*/
	EN_DRV_UART_ERR_ACCESS,										/*!< Operation invalid, because handle without access right		*/
	EN_DRV_UART_ERR_UNKNOW_DEVICE,								/*!< Invalid device name */
	EN_DRV_UART_ERR_BUSY ,										/*!< Operation invalid, because operation is already in progress */
	EN_DRV_UART_ERR_PARITY,										/*!< Operation invalid, because the parity error*/
	EN_DRV_UART_ERR_FRAMING,									/*!< Operation invalid, because the frame error*/
	EN_DRV_UART_ERR_OVERRUN,									/*!< Operation invalid, because the overrun error*/
	EN_DRV_UART_ERR_UNKNOW										/*!< Unknown Error */
}EN_DRV_UART_ERROR;

/*!
 * \brief
 * enumerate to indicate the parity in a byte of UART
 */
typedef enum
{
	EN_DRV_UART_PARITY_DISABLE,	/*!< Disable parity check */
	EN_DRV_UART_PARITY_EVEN,	/*!< Even parity check */
	EN_DRV_UART_PARITY_ODD,		/*!< Odd parity check */
	EN_DRV_UART_PARITY_NUM
}EN_DRV_UART_PARITY;

/*!
 * \brief
 * enumerate to indicate the transmission flow control type of UART
 */
typedef enum
{
	EN_DRV_UART_NO_FLOWCTRL,		/*!< No flow control is used */
	EN_DRV_UART_SW_FLOWCTRL,		/*!< Software flow control is used (XON/XOFF) */
	EN_DRV_UART_RTSCTS_FLOWCTRL,	/*!< Hardware flow control is used */
	EN_DRV_UART_FLOWCTRL_NUM
}EN_DRV_UART_FLOW_CTRL;

/*!
 * \brief
 * enumerate to indicate the number of bits per byte of UART
 */
typedef enum
{
	EN_DRV_UART_DATA_7,	/*!< 7 data bits */
	EN_DRV_UART_DATA_8,	/*!< 8 data bits */
	EN_DRV_UART_DATA_NUM
}EN_DRV_UART_DATA_BITS;

/*!
 * \brief
 * enumerate to indicate the number of stop bits per byte of UART
 */
typedef enum
{
	EN_DRV_UART_STOP_1_0,	/*!< 1 stop bit */
	EN_DRV_UART_STOP_1_5,	/*!< 1.5 stop bits */
	EN_DRV_UART_STOP_2_0,	/*!< 2 stop bits */
	EN_DRV_UART_STOP_NUM
}EN_DRV_UART_STOP_BITS;

/*!
 * \brief
 * enumerate to indicate the event type of UART
 */
typedef enum
{
	EN_DRV_UART_EVENT_TX,			/*!< Transmit event */
	EN_DRV_UART_EVENT_TX_DONE,		/*!< Transmit finish event */
	EN_DRV_UART_EVENT_RX,			/*!< Receive event */
	EN_DRV_UART_EVENT_CHANGE_CONFIG,
	EN_DRV_UART_EVENT_POWER_DOWN,	/*!< Power down event */
	EN_DRV_UART_EVENT_POWER_ON	,	/*!< Power on event */
	EN_DRV_UART_EVENT_TERM,			/*!< Terminate event */
	EN_DRV_UART_EVENT_NUM
}EN_DRV_UART_EVENT_TYPE;

/*!
 * \brief
 * enumerate to UART power control
 */
typedef enum
{
	EN_DRV_UART_POWER_ON,
	EN_DRV_UART_STANDBY,
	EN_DRV_UART_PWRCTRL_NUM
}EN_DRV_UART_PWRCTRL;


/****************************************************/
typedef enum
{
	EN_DRV_UART_0 = 0,
	EN_DRV_UART_1,
	EN_DRV_UART_NUM
}EN_DRV_UART_NO;

/*!
 * \brief
 * the data structure includes the UART transmit/receive parameters
 */
typedef struct
{
	u8		*pu8Buffer;	/*!< Pointer to the transmit/received buffer */
	u32		u32ToTransferNo;
	u32		*pu32RealTransferNo;	/*!< The number of successfully transmit/received */
	u32		u32TimeOutMs;
	u32		u32CountDownMs;
	bool	b8Running;
}ST_UART_Data, *PST_UART_Data;


/*!
 * \brief
 * Definition of a Callback function to let the caller know when transmit/receive operation has completed
 * \param	u32Handle			(Output) An open handle, as returned by the Open function
 * \param	enEventType			(Output) Callback function event type
 * \param	enStatus			(Output) UART Operation status
 * \param	pPara			(Output) A pointer to the data information. It's context will depend on enEventType.
 */
typedef void (*DRV_UART_CALLBACK) (u32 u32Handle, EN_DRV_UART_EVENT_TYPE enEventType, ErrorCode enStatus, void *pPara);

/*!
 * \brief
 * the open structure includes the UART software setting parameters
 */
typedef struct
{
	u32						u32BaudRate;	/*!< The baud rate in use */
	bool					b8LookBackEnable;
	EN_DRV_UART_DATA_BITS	enDataBits;		/*!< Defines the number of data bits */
	EN_DRV_UART_STOP_BITS	enStopBits;		/*!< Defines the number of stop bits */
	EN_DRV_UART_PARITY		enParity;		/*!< Defines the number of parity bits */
	EN_DRV_UART_FLOW_CTRL	enFlowCtrl;		/*!< Defines the flow control method used */
}ST_UART_Config, *PST_UART_Config;

/*!
 * \brief
 * the open structure includes the UART opening parameters
 */
typedef struct
{
	bool				b8FIFOEnable;		/*!< Enable FIFO implemented in software */
	bool				b8IsBlockingMode;
	u32					u32FIFOLength;		/*!< The length of the FIFO buffer when SwFIFOEnable is true */
	DRV_UART_CALLBACK	pfnUARTCallbackFun;	/*!< A pointer to the user defined function that will be called when a transmit or receive event has occurred. The NotifyFunction will be called only if not NULL. The DRV_UART_Write() and DRV_UART_Read() functions may be used in the non-blocking mode and use the NotifyFunction. */
	// Event handle for UART
	u32                 u32EvtHandle;
}ST_UART_Open, *PST_UART_Open;

typedef struct
{
	u8					*pu8FIFO;			/*!< Manage by Driver  */
	u8					*pu8Rd;
	u8					*pu8Wr;
	u32					u32FIFOLength;		/*!< The length of the FIFO buffer when SwFIFOEnable is true */

}ST_UART_FIFO, *PST_UART_FIFO;


/*!
 * \brief
 * the initial structure includes the device hardware setting
 */

typedef struct
{
	os_mempool_handle	u32MemPoolHandle;				/*!< A memory pool handle for Uart module	*/
	EN_DRV_UART_NO		enUARTNo;
}ST_UART_Init, *PST_UART_Init;

ErrorCode DRV_UART_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_UART_PWRCTRL enPwrCtrl, bool b8Force);
/*!\fn ErrorCode DRV_UART_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_UART_PWRCTRL enPwrCtrl, bool b8Force)
 *
 * \brief
 * 		Control the UART device power mode
 *
 * \param DeviceName	(Input) Device Name
 * \param	enPwrCtrl		(Input) Setting the UART device power mode
 * \param	b8Force			(Input) Force terminate the UART or not
 \code
	True:	Terminate the UART right now
	False:	wait until all handles close then terminate UART
 \endcode
 *
 \code
	enPwrCtrl				description
	------------------		---------------------------
	EN_DRV_UART_POWER_ON	UART device in power on mode
	EN_DRV_UART_STANDBY	UART device in standby mode
 \endcode
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	EN_DRV_UART_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval	ERROR_BAD_PARAMETER					Bad parameter passed
 * \retval	ERROR_INITIALISED					The driver is not initialized
 * \retval	EN_DRV_UART_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 * \retval	EN_DRV_UART_ERR_UNKNOW				Unknown Error
 */

ErrorCode DRV_UART_Initialize (DRV_DeviceNameType DeviceName, PST_UART_Init pstInit);
/*!\fn ErrorCode DRV_UART_Initialize (DRV_DeviceNameType DeviceName, PST_UART_Init pstInit)
 *
 * \brief
 * 		Initialize UART device with pstInit setting
 *
 * \param DeviceName		                (Input)  Device Name
 * \param	pstInit							(Input) Pointer to the initialization parameter structure
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR					no error
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_INITIALISED				The driver already initialized
 * \retval	EN_DRV_UART_ERR_UNKNOW			Unknown Error
 */

ErrorCode DRV_UART_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_UART_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 *
 * \brief
 * 		Terminate the UART device driver
 *
 * \param DeviceName	(Input)  Device Name
 * \param	b8Force			(Input) Force terminate the UART or not
 \code
	True:	Terminate the UART right now
	False:	wait until all handles close then terminate UART
 \endcode
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_INITIALISED					The driver is not initialized
 * \retval	EN_DRV_UART_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 */

ErrorCode DRV_UART_Open (DRV_DeviceNameType DeviceName, PST_UART_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_UART_Open (DRV_DeviceNameType DeviceName, PST_UART_Open pstOpen, u32 *pu32Handle)
 *
 * \brief
 * 		Open the UART device and associate it with a handle
 *
 * \param DeviceName	(Input)  Device Name
 * \param	pstOpen			(Input) Pointer to the opening parameter structure
 * \param	pu32Handle	(Output) The returned handle of the opened device driver
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR					no error
 * \retval	EN_DRV_UART_ERR_UNKNOW_DEVICE	Invalid device name
 * \retval	ERROR_INITIALISED				The driver is not initialized
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_NO_FREE_HANDLE			No free handle for the device
 */

ErrorCode DRV_UART_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_UART_Close (u32* pu32Handle)
 *
 * \brief
 * 		Close UART device associated with a handle
 *
 * \param	pu32Handle			(Input) Pointer of opened handle to be closed
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 */

ErrorCode DRV_UART_GetConfig (u32 u32Handle, PST_UART_Config pstPara);
/*!\fn ErrorCode DRV_UART_GetConfig (u32 u32Handle, PST_UART_Config pstPara)
 *
 * \brief
 * 		Get the UART configuration in use
 *
 * \param	u32Handle			(Input) An open handle, as returned by the Open function
 * \param	pstPara				(Output) UART device configuration parameter
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_INVALID_HANDLE	Handle is not valid
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 * \retval	ERROR_INITIALISED		The driver is not initialized
 */

ErrorCode DRV_UART_SetConfig (u32 u32Handle, PST_UART_Config pstPara);
/*!\fn ErrorCode DRV_UART_SetConfig (u32 u32Handle, PST_UART_Config pstPara)
 *
 * \brief
 * 		Sets the UART configuration
 *
 * \param	u32Handle			(Input) An open handle, as returned by the Open function
 * \param	pstPara				(Input) UART device configuration parameter
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_INVALID_HANDLE	Handle is not valid
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 * \retval	EN_DRV_UART_ERR_ACCESS	Operation invalid, because handle without access right
 * \retval	EN_DRV_UART_ERR_UNKNOW	Unknown Error
 */

u8* DRV_UART_GetVersion (void);
/*!\fn u8* DRV_UART_GetVersion (void)
 *
 * \brief
 * 		Get the Module Version number of UART
 *
 *
 * \return	Pointer of driver version
 */

ErrorCode DRV_UART_Write (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToWrite, u32 *pu32NumberWritten, u32 u32Timeout);
/*!\fn ErrorCode DRV_UART_Write (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToWrite, u32 *pu32NumberWritten, u32 u32Timeout)
 *
 * \brief
 * 		Writes a block of data to a UART device\n
 *		This call to the UART driver writes up to u32NumberToWrite bytes from the buffer pointed to by Buffer.\n
 *
 *		The call completes when one of the following is true:\n
 *		1. the number of bytes specified in NumberToWrite have been completely written\n
 *		2. the timeout period from the most recent write to the hardware output buffers has expired
 *			(noting that a time-out of 0 means that there is no time-out)\n
 *		3. an error occurs\n
 *
 *		The DRV_UART_Write() call is blocking if the transmission NotifyFunction parameter is NULL and the call is non-blocking otherwise.\n
 *
 *		In the blocking mode, the call will return only when one of the reasons listed above is true.\n
 *
 *		In a non-blocking mode, the call returns immediately.\n
 *		If the return value at that stage is other than ERROR_NO_ERROR,
 *		then the write is aborted and the NotifyFunction will not be called.\n
 *		If the return value at that stage is ERROR_NO_ERROR,
 *		then a write operation is initiated and at most u32NumberToWrite bytes of data are transmitted out of the UART.\n
 *		The write call will complete for one of the reasons listed above.\n
 *		On completion of the DRV_UART_Write() call, and the number of bytes written successfully is placed in NumberWritten
 *		and the NotifyFunction is invoked to signal to the calling program the final error result of the write operation.\n
 *
 * \param	u32Handle			(Input) Handle of the device over which data will be written
 * \param	pu8Buffer			(Input) A buffer holding the data to be sent
 * \param	u32NumberToWrite	(Input) Number of bytes to write to the device
 * \param	pu32NumberWritten	(Output) The number of bytes written to the Buffer
 * \param	u32Timeout			(Input) Length of time-out, specified in 1ms intervals. A u32Timeout value of 0 specifies that it should never time-out
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_INVALID_HANDLE	Handle is not valid
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 * \retval	EN_DRV_UART_ERR_BUSY	Operation invalid, because operation is already in progress
 * \retval	EN_DRV_UART_ERR_ACCESS	Operation invalid, because handle without access right
 */

ErrorCode DRV_UART_Read (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToRead, u32 *pu32NumberRead, u32 u32Timeout);
/*!\fn ErrorCode DRV_UART_Read (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToRead, u32 *pu32NumberRead, u32 u32Timeout)
 *
 * \brief
 * 		Reads a block of data from a UART device\n
 *		This call reads up to u32NumberToRead bytes into the buffer pointed to by Buffer.\n
 *
 *		The call completes when one of the following is true:\n
 *		1. the number of bytes specified in u32NumberToRead have been read\n
 *		2. no character has been received after the time-out period since the reception of the last character
 *			(noting that a time-out of 0 means that there is no time-out)\n
 *		3. an error occurs\n
 *
 *		The DRV_UART_Read() call is blocking if the notify function is NULL and the call is non-blocking otherwise.\n
 *
 *		In the blocking mode, the call will return only when one of the reasons listed above is true.\n
 *
 *		In a non-blocking mode, the call returns immediately.
 *		If the return value at that stage is other than ERROR_NO_ERROR,
 *		then the read is aborted and the NotifyFunction will not be called.\n
 *		If the return value at that stage is ERROR_NO_ERROR,
 *		a read operation is initiated and at most u32NumberToRead bytes of data are read from the UART and placed in Buffer.\n
 *		The read call will complete for one of the reasons listed above.\n
 *		On completion of the DRV_UART_Read() call, and the number of bytes read successfully is placed in pu32NumberRead
 *		and the NotifyFunction is invoked to signal to the calling program the final error result of the read operation.\n
 *
 * \param	u32Handle			(Input) Handle of the device over which data to be read
 * \param	pu8Buffer			(Input) A buffer into which to put the data received
 * \param	u32NumberToRead		(Input) Number of bytes to read from the device
 * \param	pu32NumberRead		(Output) On return contains the number of bytes that have been read into the Buffer
 * \param	u32Timeout			(Input) Length of time-out, specified in 1ms intervals. A u32Timeout value of 0 specifies that it should never time-out
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 * \retval	ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval	EN_DRV_UART_ERR_BUSY		Operation invalid, because operation is already in progress
 * \retval	EN_DRV_UART_ERR_ACCESS		Operation invalid, because handle without access right
 */

ErrorCode DRV_UART_PermissionLock (u32 u32Handle, bool b8Enable);
/*!\fn ErrorCode DRV_UART_PermissionLock (u32 u32Handle, bool b8Enable)
 *
 * \brief
 * 		Lock the device with a handle.
 *
 * \param	u32Handle			(Input) An open handle number of the UART device
 * \param	b8Enable			(Input) Control property of Lock
 \code
	True:	Lock
	False:	unLock
 \endcode
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 * \retval	EN_DRV_UART_ERR_ACCESS		Operation invalid, because handle without access right
 */

ErrorCode DRV_UART_PutC(u32 u32Handle, u8 u8Ch);
/*!\fn ErrorCode DRV_UART_PutC(u32 u32Handle, u8 u8Ch)
 *
 * \brief
 *		write one character out directly
 *
 * \param	u32Handle			(Input) An open handle number of the UART device
 * \param	u8Ch				(Input) data to be output
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 */

ErrorCode DRV_UART_Flush (u32 u32Handle);
/*!\fn ErrorCode DRV_UART_Flush (u32 u32Handle)
 *
 * \brief
 *		Flushes the RX buffer by handle, don't allow operation while Read Operation in progress
 *
 * \param	u32Handle			(Input) An open handle number of the UART device
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 * \retval	EN_DRV_UART_ERR_BUSY		Operation invalid, because operation is already in progress
 */

bool _uart_PutC (EN_DRV_UART_NO enUartNo, u8 u8Ch);
/*!\fn _uart_PutC (EN_DRV_UART_NO enUartNo, u8 u8Ch)
 *
 * \brief
 *		Direct output char to uart port
 *
 * \param	enUartNo			(Input) An open handle number of the UART device
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 * \retval	EN_DRV_UART_ERR_BUSY		Operation invalid, because operation is already in progress
 */

int uart0_getCh( char* pcData );
/*!\fn uart0_getCh( char* pcData )
 *
 * \brief
 *		Direct get char from uart port
 *
 * \param	enUartNo			(Input) An open handle number of the UART device
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 * \retval	EN_DRV_UART_ERR_BUSY		Operation invalid, because operation is already in progress
 */

void uart_rest_rx_fifo(EN_DRV_UART_NO enUartNo);
/*!\fn uart_rest_rx_fifo(EN_DRV_UART_NO enUartNo)
 *
 * \brief
 *		Direct get char from uart port
 *
 * \param	enUartNo			(Input) An open handle number of the UART device
 *
 * \return	 	None
 */

ErrorCode _uart_IntrEnable(EN_DRV_UART_NO enUARTNo);
/*!\fn _uart_IntrEnable(EN_DRV_UART_NO enUARTNo)
 *
 * \brief
 *		Direct get char from uart port
 *
 * \param	enUartNo			(Input) An open handle number of the UART device
 *
 * \return	UART Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 * \retval	EN_DRV_UART_ERR_BUSY		Operation invalid, because operation is already in progress
 */

#endif //#ifndef __UART_H__
