//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide SMC Control
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


#ifndef __DRV_SMC_H__
#define __DRV_SMC_H__

#include "os.h"
#include "def_type.h"
#include "def_err.h"
#include "drv_gpio.h"
#include "drv_config.h"


#define MAX_ATR_SIZE (33)

#define MAX_PTS_SIZE (6)
#define SMC_N_DEFAULT         2       /* Extra guardtime */
#define FIRST_BYTE_ATR           2
#define	SMC_TS_DIRECT			0x3B
#define	SMC_TS_INVERSE			0x3F

/* PTS defines */
#define PTS_INITIAL_CHAR        0xFF
#define MAX_HISTORY_SIZE (15)
/* T=0 defines */
#define T0_CMD_LENGTH           5
#define T0_CLA_OFFSET           0
#define T0_INS_OFFSET           1
#define T0_P1_OFFSET            2
#define T0_P2_OFFSET            3
#define T0_P3_OFFSET            4
#define T0_RETRIES_DEFAULT      3
#define TIME_DELAY             10000

#define	SMC_MAX_HANDLE_PER_DEVICE			2

typedef enum
{
	EN_DRV_SMC_CLKSRC_MODE_INTERNAL,
	EN_DRV_SMC_CLKSRC_MODE_EXTERNAL
}EN_DRV_SMC_CLKSRC_MODE;

/**
 * \brief
 * enumerate to indicate the error of operation
 */
enum
{
	ERROR_SMC_ERR_HANDLE_NOT_CLOSED  = ERROR_BASE_DRV_SMC,		/*!< Operation invalid, because handle not close*/
	ERROR_SMC_ERR_ACCESS,										/*!< Operation invalid, because handle without access right		*/
	ERROR_SMC_ERR_UNKNOW_DEVICE,								/*!< Invalid device name */
	ERROR_SMC_ERR_NOT_INSERTED,									/*!< Smartcard has not been inserted */
	ERROR_SMC_ERR_NO_ANSWER,									/*!< No response from smartcard when host request */
	ERROR_SMC_ERR_NOT_RESET,									/*!< Smartcard has not been reset */
	ERROR_SMC_ERR_PARITY,										/*!< A parity error has occurred */
	ERROR_SMC_ERR_FRAMING,										/*!< A framing error has occurred */
	ERROR_SMC_ERR_OVERRUN,										/*!< An internal read buffer has overrun */
	ERROR_SMC_ERR_TX_TOO_MANY_RETRIES,							/*!< Retry counts has reached the allow limit when sent a byte */
	ERROR_SMC_ERR_INVALID_PROTOCOL,							/*!< Driver does not support the protocol requested passed */
	ERROR_SMC_ERR_PTS_NOT_SUPPORTED,							/*!< The card does not support PTS */
	ERROR_SMC_ERR_IN_PTS_CONFIRM,								/*!< An error PTS confirm received from the card */
	ERROR_SMC_ERR_INVALID_STATUS_BYTE,							/*!< Invalid procedure byte received from the card */
	ERROR_SMC_ERR_TS_CHAR,										/*!< Got the wrong TS during ATR */
	ERROR_SMC_ERR_AVAILABLE,									/*!< Card is not available */
	ERROR_SMC_ERR_TIMEOUT,										/*!< Transmit timeout */
	ERROR_SMC_ERR_TRANSMIT,									/*!< Transmit error */
	ERROR_SMC_ERR_RESET_FAILED,								/*!< rest failed */
	ERROR_SMC_ERR_PTS_CONFIRM,									/*!< PTS confirm error */
	ERROR_SMC_ERR_INCORRECT_LENGTH,							/*!< incorrect length error */
	ERROR_SMC_ERR_INCORRECT_REFERENCE,							/*!< incorrect reference error */
	ERROR_SMC_ERR_INVALID_CODE,								/*!< invalid code error */
	ERROR_SMC_ERR_INVALID_CLASS,								/*!< invalid class error */
	ERROR_SMC_ERR_STS_WORD,									/*!< status word error */
	ERROR_SMC_ERR_DEVICE_BUSY,									/*!< device busy */
	ERROR_SMC_ERR_UNKNOW,										/*!< Driver can't determine the problem */
	ERROR_SMC_ERR_ABORT										/*!< All smartcard's operation has been abort */
};

/**
 * \brief
 * enumerate to indicate the module number of smartcard.
 */
typedef enum
{
	EN_DRV_SMC_0,				/*!< Indicate smartcard module number 0 */
	EN_DRV_SMC_1,				/*!< Indicate smartcard module number 1 */
	EN_DRV_SMC_NUM
}EN_DRV_SMC_NO;


/*!
 * \brief
 * enumerate to indicate the clock source to drive the smartcard clock line.
 */
typedef enum
{
	EN_DRV_SMC_CLOCK_INTERNAL,			/*!< The smartcart interface selects and divides-down the CPU clock */
	EN_DRV_SMC_CLOCK_EXTERNAL,			/*!< The smartcart interface selects and divides-down an externally supplied clock (on ClkGenExtClk) */
	EN_DRV_SMC_CLOCK_SOURCE_NUM
}EN_DRV_SMC_ClOCK_SRC;

/*!
 * \brief
 * enumerate to indicate the event type of SMC
 */
typedef enum
{
	EN_DRV_SMC_EVENT_CARD_INSERTED,			/*!< Card has been inserted */
	EN_DRV_SMC_EVENT_CARD_REMOVED,			/*!< Card has been removed */
	EN_DRV_SMC_EVENT_CARD_RESET,			/*!< Card has been reset */
	EN_DRV_SMC_EVENT_CARD_DEACTIVATED,		/*!< Card has it's power supply (Vcc)removed */
	EN_DRV_SMC_EVENT_TRANSFER_COMPLETED,	/*!< Indicate transfer completed */
	EN_DRV_SMC_EVENT_PTS_COMPLETED,			/*!< Indicate PTS completed */
	EN_DRV_SMC_EVENT_WRITE_COMPLETED,		/*!< Indicate raw write command completed */
	EN_DRV_SMC_EVENT_READ_COMPLETED,		/*!< Indicate raw read command completed */
	EN_DRV_SMC_EVENT_RX,					/*!< RX event */
	EN_DRV_SMC_EVENT_CHANGE_CONFIG,			/*!< Config changed event */
	EN_DRV_SMC_EVENT_POWER_DOWN,			/*!< Power down event */
	EN_DRV_SMC_EVENT_TERM,					/*!< Terminate event */
	EN_DRV_SMC_EVENT_NUM
}EN_DRV_SMC_EVENT_TYPE;

/*!
 * \brief
 * enumerate the type of error-detection code used for T=1 transfers.
 */
typedef enum
{
	EN_DRV_SMC_CODETYPE_LRC,				/*!< Indicate LRC code type */
	EN_DRV_SMC_CODETYPE_CRC,				/*!< Indicate LRC code type */
	EN_DRV_SMC_CODETYPE_NUM
}EN_DRV_SMC_CODETYPE;

/*!
 * \brief
 * enumerate available protocols for the smartcard driver.
 */
typedef enum
{
	EN_DRV_SMC_PROTOCOL_T0,					/*!< Indicate asynchronous half duplex byte transmission protocol */
	EN_DRV_SMC_PROTOCOL_T1,					/*!< Indicate asynchronous half duplex block transmission protocol */
	EN_DRV_SMC_PROTOCOL_NUM
}EN_DRV_SMC_PROTOCOL_TYPE;

/*!
 * \brief
 * enumerate type of smartcard power control
 */
typedef enum
{
	EN_DRV_SMC_POWER_ON,					/*!< Indicate "power on" status of smartcard */
	EN_DRV_SMC_STANDBY,						/*!< Indicate "standby" status of smartcard */
	EN_DRV_SMC_PWRCTRL_NUM
}EN_DRV_SMC_PWRCTRL;

/*!
 * \brief
 * enumerate to indicate type of parity mode
 */
typedef enum
{
	EN_DRV_SMC_PARITY_EVEN,					/*!< Indicate even parity mode */
	EN_DRV_SMC_PARITY_ODD,					/*!< Indicate odd parity mode */
	EN_DRV_SMC_PARITY_NUM
}EN_DRV_SMC_PARITY_MODE;

/*!
 * \brief
 * enumerate to indicate number of stop bit
 */
typedef enum
{
	EN_DRV_SMC_STOP_BIT_2,					/*!< 2 stop bits */
	EN_DRV_SMC_STOP_BIT_1_5,				/*!< 1.5 stop bits */
	EN_DRV_SMC_STOP_BIT_1,					/*!< 1 stop bit */
	EN_DRV_SMC_STOP_BIT_NUM
}EN_DRV_SMC_STOP_BIT_MODE;

/*!
 * \brief
 * enumerate to indicate formart of data bit
 */
typedef enum
{
	EN_DRV_SMC_DATA_BIT_8_0,  				/*!< "8-bit" data format */
	EN_DRV_SMC_DATA_BIT_7_1P,				/*!< "7-bit Data + Parity" data format */
	EN_DRV_SMC_DATA_BIT_8_1P, 				/*!< "8-bit Data + Parity" data format */
	EN_DRV_SMC_DATA_BIT_9_0,  				/*!< "9-bit" data format */
	EN_DRV_SMC_DATA_BIT_NUM
}EN_DRV_SMC_DATA_BIT_MODE;

/*!
 * \brief
 * enumerate to indicate formart of context
 */
typedef enum
{
    EN_CONTEXT_NONE = 0,             /*!< default (none) */
    EN_CONTEXT_READ,                 /*!< read operation */
    EN_CONTEXT_WRITE,                /*!< write operation */
    EN_CONTEXT_TRANSFER,             /*!< write & read operation */
    EN_CONTEXT_RESET,                /*!< reset operation */
    EN_CONTEXT_SETPROTOCOL           /*!< set protocol operation */
}EN_CONTEXT;

/*!
 * \brief
 * Definition of a callback function to let the caller know when transmit/receive operation has completed and relative status.
 * \param	u32Handle			(Output) An open handle, as returned by the Open function
 * \param	enEventType			(Output) Callback function event type
 * \param	enStatus			(Output) Smartcard operation status
 * \param	pstPara			(Output) A pointer to the data information. It's context will depend on enEventType.
 */
typedef void (* DRV_SMC_CALLBACK) (u32 u32Handle, EN_DRV_SMC_EVENT_TYPE enEventType, ErrorCode enStatus, void *pstPara);

typedef void (*DRV_SMC_CARD_IO_NOTIFY)(void);

/*!
 * \brief
 * Struct to hold parameters used to config and initial the smartcard driver
 */
typedef struct
{
	os_mempool_handle	u32MemPoolHandle;			/*!< A memory pool handle for smartcard module	*/
	EN_DRV_SMC_NO		enSmcNo;					/*!< SMC device number						*/
	u8					u8InitArray;
	u32 				*pu32BaseAddress;			/*!< The base address of the smartcard clock register. */
}ST_SMC_InitParms, *PST_SMC_InitParms;

/*!
 * \brief
 * structure includes the smartcard setting parameters
 */
typedef struct
{
	u32							u32BaudRate;		/*!< Desire baudrate to be used */
	u32							u32GuardDelay;		/*!< The time between two start leading edge of two byte  */
	u16							u16TxRetries;		/*!< Number of retries to allow */
	u32 						u32TXTimeOut;		/*!< Time out for TX */
	u32 						u32RXTimeOut;		/*!< Time out for RX */
	EN_DRV_SMC_ClOCK_SRC		enClockSrc;			/*!< Indicate clock source to drive the smartcard clock line */
	EN_DRV_SMC_PARITY_MODE		enParityMode;		/*!< Indicate type of parity mode */
	EN_DRV_SMC_STOP_BIT_MODE	enStopBitMode;		/*!< Indicate number of stop bit */
	EN_DRV_SMC_DATA_BIT_MODE	enDataBitMode;		/*!< Indicate formart of data bit */
}ST_SMC_Config, *PST_SMC_Config;

/*!
 * \brief
 * the open structure includes the SMC opening parameters
 */
typedef struct
{
	u32					u32FIFOLength;		/*!< RX FIFO length */
	DRV_SMC_CALLBACK	pfnSMCCallbackFun;	/*!< A pointer to the user defined function that will be called when a transmit or receive event has occurred. The NotifyFunction will be called only if not NULL. */
	bool				b8BlockingIO;		/*!< Specifies the behaviour of asynchronous functions */
	u8					u8SAD;				/*!< Source address (for T=1 only). Only the bits SAD[2:0] are used. */
	u8					u8DAD;				/*!< Destination address (for T=1 only). Only the bits DAD[2:0] are usedo */
}ST_SMC_Open, *PST_SMC_Open;

/*!
 * \brief
 * describing status for protocol T = 0
 */
typedef struct
{
	u8 u8Ins;								/*!< Record last instruction byte sent to smartcard */
	u8 u8Size;								/*!< Numbers of procedure byte returned */
	u8 u8PB[2];								/*!< u8PB[0] present procedure byte 1, u8PB[1] present procedure byte 2 */
}ST_SMC_T0Status, *PST_ST_SMC_T0_Status;

/*!
 * \brief
 * describing status for protocol T = 1
 */
typedef struct
{
	u8 u8Reserved;							/*!< Reserved for future use */
}ST_SMC_T1Status, *PST_ST_SMC_T1_Status;


/*!
 * \brief
 * Structure describing relative protocol's status of the device
 */
typedef struct
{
	EN_DRV_SMC_PROTOCOL_TYPE enProtocol;	/*!< protocol of the smartcard */
	union
	{
		ST_SMC_T0Status T0;
		ST_SMC_T1Status T1;
	} StatusBlock;							/*!< status block of the smartcard */
}ST_SMC_Status, *PST_SMC_Status;

/*!
 * \brief
 * Structure containing info which configs transmission parameter
 */
typedef struct
{
	u8					*pu8WriteBuffer;		/*!< Source data buffer (command and data). */
	u32					u32NumberToWrite;		/*!< Length of source data bufer */
	u32					*pu32NumberWritten;		/*!< The number of bytes successfully sent. */
	u8					*pu8ReadBuffer;			/*!< Destination data buffer. */
	u32					u32NumberToRead;		/*!< Number of bytes expected in response. */
	u32					*pu32NumberRead;		/*!< The number of bytes successfully received. */
	PST_SMC_Status	pstSMCStatus;				/*!< The error code and procedure bytes returned by smartcard. */
}ST_SMC_TransParms,	*PST_SMC_TransParms;

/*!
 * \brief
 * the data structure includes the SMC transmit/receive parameters
 */
typedef struct
{
	u8		*pu8Buffer;				/*!< Pointer to the transmit/received buffer */
	u32		u32ToTransferNo;		/*!< The number of transmit */
	u32		*pu32RealTransferNo;	/*!< Pointer to the number of successfully transmit/received */
	u32		u32TimeOutMs;			/*!< Timeout value */
	u32		u32CountDownMs;			/*!< Count down minute */
	bool	b8Running;				/*!< is running or not */
}ST_SMC_Data, *PST_SMC_Data;

/*!
 * \brief
 * the data structure includes the SMC FIFO parameters
 */
typedef struct
{
	u8					*pu8FIFO;			/*!< Manage by Driver  */
	u8					*pu8Rd;				/*!< Pointer to read the buffer */
	u8					*pu8Wr;				/*!< Pointer to write the buffer */
	u32					u32FIFOLength;		/*!< The length of the FIFO buffer when SwFIFOEnable is true */

}ST_SMC_FIFO, *PST_SMC_FIFO;

/*!
 * \brief
 * the data structure includes the SMC oeration parameters
 */
typedef struct
{
    /* Input parameters */
    EN_CONTEXT             Context;          		/*!< Context of operation e.g., ATR, TRANSFER */
    u8                          *pu8ReadBuffer;		/*!< Pointer to user's read buffer */
    u32                         u32NumberToRead;	/*!< The number of read */
    u32                         u32Timeout;			/*!< Timeout value */
    u32                         *pu32ReadBytes;     /*!< Pointer to final number read */
}ST_SMC_OPERATION;

/*!
 * \brief
 * the data structure includes the SMC cotrol block parameters
 */
typedef struct
{
	bool				b8Lock;									/*!< lock or not */
	bool				b8IsBlockingMode;						/*!< blocking mode or not */
	DRV_SMC_CALLBACK	pfn_Smc_cb;								/*!< A pointer to the user defined function that will be called when a transmit or receive event has occurred. The NotifyFunction will be called only if not NULL. */
	u8					WorkingType;							/*!< Working type */
	ST_SMC_Data			stRxSmcData;							/*!< RX data structure */
	ST_SMC_Data			stTxSmcData;							/*!< TX data structure */
	/* Pending operation */
	ST_SMC_OPERATION	stOperation;							/*!< Operation structure */
	/*ATR*/
	u8                  ATR[MAX_ATR_SIZE];						/*!< Answer to reset */
	u8					ATRSize;								/*!< Size of ATR */
	u8                  HistoricalBytes[MAX_HISTORY_SIZE];		/*!< Historical bytes */
	u8			u8HistoricalChar;
	u8					TS;										/*!< The Initial Character */
	u8					FI;										/*!< The parameter FI in the upper nibble encodes the divider (clock rate conversion factor) F */
	u8					DI;										/*!< The parameter DI in the lower nibble encodes the bit rate adjustment factor D */
	u8					IFSC;									/*!< The information field size of the smart card */
	u8					II;										/*!< Bits b7 and b6 of TB1 encode a programming voltage factor called II */
	u8					PI1;									/*!< Bits b5¡Vb1 of TB1 define the parameter PI1 */
	u8					PI2;									/*!/ This parameter specifies the external programming voltage in tenths of a volt */
	u8					CWI;									/*!< The character waiting time */
	u8					BWI;									/*!< The block waiting time */
	u16					N;										/*!< Extra guardtime */
	u8					WI;										/*!< WI, which encodes the ¡¥work waiting time¡¦ */
	u8					RC;
	u8					u8ModeT;								/*!< Protocol type */
	/* Bytes sent by the card from the last PTS operation; PTS0, PTS1, PTS2, PTS3, PCK stripped */
    u8                  PtsBytes[4];
    ST_SMC_Status		Status;									/*!< Structure describing relative protocol's status of the device */
    u8					*pu8SW;									/*!< Pointer to status words */
    ErrorCode			enDrvErr;								/*!< driver error */
    bool				b8ChkTxTimeout;							/*!< check TX timeout or not */
    u32					u32HandleNo;							/*!< Handle number */
}ST_SMC_Handle, *PST_SMC_Handle;

#if 1//def SEN5_SUPPORT_T1
enum{
	IFD_PROTOCOL_RECV_TIMEOUT = 0x0000,
	IFD_PROTOCOL_T1_BLOCKSIZE,
	IFD_PROTOCOL_T1_CHECKSUM_CRC,
	IFD_PROTOCOL_T1_CHECKSUM_LRC,
	IFD_PROTOCOL_T1_IFSC,
	IFD_PROTOCOL_T1_IFSD,
	IFD_PROTOCOL_T1_STATE,
	IFD_PROTOCOL_T1_MORE
};

/* internal state, do not mess with it. */
/* should be != DEAD after reset/init */
enum 
{
	SENDING, 
	RECEIVING, 
	RESYNCH, 
	DEAD
};

#define NAD 0
#define PCB 1
#define LEN 2
#define DATA 3


/* T=1 protocol constants */
#define T1_I_BLOCK			0x00
#define T1_R_BLOCK			0x80
#define T1_S_BLOCK			0xC0
#define T1_MORE_BLOCKS		0x20
#define T1_BUFFER_SIZE		(3 + 254 + 2)

#define ATR_DEFAULT_IFSC	32
#define ATR_DEFAULT_IFSD	32
#define ATR_DEFAULT_BGT		22
#define ATR_DEFAULT_CHK		0	//default checksum is LRC

/********************************************
T1 related Macro define
*********************************************/
/* I block */
#define T1_I_SEQ_SHIFT		6

/* R block */
#define T1_IS_ERROR(pcb)	((pcb) & 0x0F)
#define T1_EDC_ERROR		0x01
#define T1_OTHER_ERROR		0x02
#define T1_R_SEQ_SHIFT		4

/* S block stuff */
#define T1_S_IS_RESPONSE(pcb)	((pcb) & T1_S_RESPONSE)
#define T1_S_TYPE(pcb)		((pcb) & 0x0F)
#define T1_S_RESPONSE	0x20
#define T1_S_RESYNC		0x00
#define T1_S_IFS		0x01
#define T1_S_ABORT		0x02
#define T1_S_WTX		0x03

#define swap_nibbles(x) ( (x >> 4) | ((x & 0xF) << 4) )


typedef struct t1_buf 
{
	u8*		base;
	u32		head, tail, size;
	u32		overrun;
} t1_buf_t;

/* T1 protocol private*/
typedef struct {
	int		state;  /*internal state*/

	u8		ns;	/* reader side  Send sequence number */
	u8		nr;	/* card side  RCV sequence number*/
	u32		ifsc;
	u32		ifsd;

	u8		wtx;		/* block waiting time extention*/
	u32		retries;
	s32		rc_bytes; 	/*checksum bytes, 1 byte for LRC, 2 for CRC*/

	u32		BGT;
	u32		BWT;
	u32		CWT;
	
	u32  	(*checksum)(u8* pdata, u32 len, u8* rc);

	u8		more;	/* more data bit */
	u8		previous_block[4];	/* to store the last R-block */
	u8		sdata[T1_BUFFER_SIZE];
	u8		rdata[T1_BUFFER_SIZE];
} t1_state_t;

ErrorCode smc_open(DRV_DeviceNameType DeviceName, PST_SMC_Open pstOpen, u32 *pu32Handle);
ErrorCode smc_close(u32* pu32Handle);
ErrorCode smc_card_exist(u32 u32Handle, bool b8Lock);
ErrorCode smc_reset(u32 u32Handle, u8 *pu8Anser, u32 *pu32AnserLength);
ErrorCode smc_deactive(DRV_DeviceNameType DeviceName);
ErrorCode smc_raw_read(u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToRead, u32 *pu32NumberRead);
ErrorCode smc_raw_write(u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToWrite, u32 *pu32NumberWrite);
ErrorCode smc_raw_fifo_write(u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToWrite, u32 *pu32NumberWrite);
//s32 smc_iso_transfer(struct smc_device *dev, u8 *command, s16 num_to_write, u8 *response, s16 num_to_read, s16 *actual_size);
//s32 smc_iso_transfer_t1(struct smc_device *dev, u8 *command, s16 num_to_write, u8 *response, s16 num_to_read,s32 *actual_size);
//s32 smc_iso_transfer_t14(struct smc_device *dev, u8 *command, s16 num_to_write, u8 *response, s16 num_to_read,s32 *actual_size);
//s32 smc_io_control(struct smc_device *dev, u32 cmd, u32 param);

#endif



ErrorCode DRV_SMC_Initialize (DRV_DeviceNameType DeviceName, PST_SMC_InitParms pstInit);
/*!\fn ErrorCode DRV_SMC_Initialize (DRV_DeviceNameType DeviceName, PST_SMC_InitParms pstInit)
 *
 * \brief
 * 		Initialize the specified smartcard device with pstInit setting
 *
 * \param	DeviceName		(Input) smartcard device name to initialize
 * \param	pstInit			(Input) Pointer to the initialization parameter structure
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_INITIALISED					A previous initialization call has not been terminated
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_SMC_ERR_UNKNOW_DEVICE		Invalid device name
 * \retval	ERROR_SMC_ERR_ACCESS				Operation invalid, because handle without access right
 */

ErrorCode DRV_SMC_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_SMC_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 *
 * \brief
 * 		Terminate the smartcard device driver
 *
 * \param	DeviceName		(Input) Smartcard device name to terminate
 * \param	b8Force			(Input) Force terminate the smartcard or not
 \code
	True:	Terminate the smartcard device right now
	False:	Wait until all handles associated with specified smardcard device closed then terminate it
 \endcode
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_SMC_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 * \retval	ERROR_SMC_ERR_UNKNOW_DEVICE		Invalid device name
 */

ErrorCode DRV_SMC_Open (DRV_DeviceNameType DeviceName, PST_SMC_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_SMC_Open (DRV_DeviceNameType DeviceName, PST_SMC_Open pstOpen, u32 *pu32Handle)
 *
 * \brief
 * 		Open a connection to the smartcard device and associate it with a handle
 *
 * \param	DeviceName	(Input) Smartcard device name to open
 * \param	pstOpen		(Input) Pointer to the opening parameter structure
 * \param	pu32Handle	(Output)A handle associated with the opened smartcard device
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_NO_FREE_HANDLE				No free handle for the device
 * \retval	ERROR_SMC_ERR_UNKNOW_DEVICE		Invalid device name
 */

ErrorCode DRV_SMC_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_SMC_Close (u32* pu32Handle)
 *
 * \brief
 * 		Close a connection to the smartcard device by specified handle
 *
 * \param	pu32Handle		(Input) An open handle number of the SMC device
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 */

ErrorCode DRV_SMC_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_SMC_Lock (u32 u32Handle, bool b8Lock)
 *
 * \brief
 *		Lock a connection to the smartcard driver or not with specified handle
 *
 * \param	u32Handle		(Input) An open handle number of the smartcard device.
 * \param	b8Lock			(Input) Lock the resource or not
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_SMC_ERR_ACCESS				Operation invalid, because handle without access right
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 */

ErrorCode DRV_SMC_RawRead (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToRead, u32 *pu32NumberRead, u32 u32TimeOut);
/*!\fn ErrorCode DRV_SMC_RawRead (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToRead, u32 *pu32NumberRead, u32 u32TimeOut)
 *
 * \brief
 *		Direct access function to the smartcard interface for reading data
 *
 * \param	u32Handle			(Input)	An open handle number of the smartcard device.
 * \param	pu8Buffer			(Output)Pointer to buffer which store received bytes.
 * \param	u32NumberToRead		(Input)	Maximum numbers of bytes to be read.
 * \param	pu32NumberRead		(Output)Actural numbers of bytes has been read.
 * \param	u32TimeOut			(Input)	Number of milliseconds to allow between each received character before timing out.
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_BAD_PARAMETER			Parameter is not valid.
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 * \retval	ERROR_SMC_ERR_AVAILABLE	Smartcard has not been inserted.
 * \retval	ERROR_SMC_ERR_DEVICE_BUSY	The smartcard device is busy (card is locked).
 * \retval	ERROR_TIMEOUT				The operation timeout before all data could be read
 */

ErrorCode DRV_SMC_RawWrite (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToWrite, u32 *pu32NumberWrite, u32 u32TimeOut);
/*!\fn ErrorCode DRV_SMC_RawWrite (u32 u32Handle, u8 *pu8Buffer, u32 u32NumberToWrite, u32 *pu32NumberWrite, u32 u32TimeOut)
 *
 * \brief
 *		Direct access function to the smartcard interface for writing data
 *
 * \param	u32Handle			(Input)	An open handle number of the smartcard device.
 * \param	pu8Buffer			(Output)Pointer to buffer to be transmitted.
 * \param	u32NumberToWrite	(Input)	Maximum numbers of bytes to write.
 * \param	pu32NumberWrite		(Output)Actural numbers of bytes has been written.
 * \param	u32TimeOut			(Input)	Number of milliseconds to allow for a character to be transmitted before timeout.
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_INVALID_HANDLE	  			Handle is not valid
 * \retval	ERROR_SMC_ERR_AVAILABLE			Smartcard has not been inserted.
 * \retval	ERROR_SMC_ERR_TRANSMIT				The transfer operation failed.
 * \retval	ERROR_TIMEOUT			  			The transfer operation timeout.
 */

ErrorCode DRV_SMC_Flush (u32 u32Handle);
/*!\fn ErrorCode DRV_SMC_Flush (u32 u32Handle)
 *
 * \brief
 *		To flush the internal receive FIFO of the driver.
 *
 * \param	u32Handle		(Input) An open handle number of the smartcard device.
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 * \retval	ERROR_SMC_ERR_ACCESS		Operation invalid, because handle without access right
 */

ErrorCode DRV_SMC_SetProtocol (u32 u32Handle, u8 *pu8PtsRequest);
/*!\fn ErrorCode DRV_SMC_SetProtocol (u32 u32Handle, u8 *pu8PtsRequest)
 *
 * \brief
 *		To perform smartcard protocol selection
 *
 * \param	u32Handle		(Input) An open handle number of the smartcard device.
 * \param	pu8PtsRequest	(Input) Up to four byte array which contains four byte, PTS0,PTS1,PTS2,PTS3
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 * \retval	ERROR_SMC_ERR_AVAILABLE			Smartcard has not been inserted
 * \retval	ERROR_SMC_ERR_DEVICE_BUSY			The smartcard device is busy (card is locked).
 * \retval	ERROR_SMC_ERR_TRANSMIT				Transmit failed
 * \retval	ERROR_SMC_ERR_PTS_CONFIRM			An error PTS confirm received from the card
 * \retval	ERROR_SMC_ERR_PTS_NOT_SUPPORTED	The smartcard does not support any protocol
 * \retval	ERROR_SMC_ERR_UNKNOW				Driver can't determine the problem
 */

ErrorCode DRV_SMC_GetStatus (u32 u32Handle, PST_SMC_Status pstSMCStatus);
/*!\fn ErrorCode DRV_SMC_GetStatus (u32 u32Handle, PST_SMC_Status pstSMCStatus)
 *
 * \brief
 *		Returns the status of the smartcard driver that is specific to the current protocol type.
 *
 * \param	u32Handle		(Input) An open handle number of the smartcard device.
 * \param	pstSMCStatus	(Output) The error code and protocol-specific status information returned by the smartcard after the last operation.
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 * \retval	ERROR_SMC_ERR_NOT_INSERTED			Smartcard has not been inserted
 * \retval	ERROR_SMC_ERR_NO_ANSWER			Smartcard do not response the host request
 * \retval	ERROR_SMC_ERR_NOT_RESET			Smartcard has not been reset
 */

ErrorCode DRV_SMC_Reset (u32 u32Handle, u8 *pu8Anser, u32 *pu32AnserLength);
/*!\fn ErrorCode DRV_SMC_Reset (u32 u32Handle, u8 *pu8Anser, u32 *pu32AnserLength)
 *
 * \brief
 *		Perform the smartcard reset sequence and get the ATR from the card.
 *
 * \param	u32Handle			(Input)	An open handle number of the smartcard device.
 * \param	pu8Anser			(Output)Buffer which store the ATR message
 * \param	*pu32AnserLength	(Output)Byte count in answer buffer
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 * \retval	ERROR_SMC_ERR_AVAILABLE			Smartcard has not been inserted
 * \retval	ERROR_SMC_ERR_DEVICE_BUSY			The smartcard device is busy (card is locked).
 * \retval	ERROR_SMC_ERR_TIMEOUT				Transfer is timeout
 * \retval	ERROR_SMC_ERR_TS_CHAR				Got the wrong TS (initial character) during ATR.
 * \retval	ERROR_SMC_ERR_RESET_FAILED			The reset operation failed. 
 */

ErrorCode DRV_SMC_WarmReset(u32 u32Handle);
/*!\fn ErrorCode DRV_SMC_WarmReset(u32 u32Handle)
 *
 * \brief
 *		Perform the smartcard warm reset.
 *
 * \param	u32Handle			(Input)	An open handle number of the smartcard device.
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 */

ErrorCode DRV_SMC_GetConfig (u32 u32Handle, PST_SMC_Config pstPara);
/*!\fn ErrorCode DRV_SMC_GetConfig (u32 u32Handle, PST_SMC_Config pstPara)
 *
 * \brief
 * 		To get the parameter of the smartcard configuration in use
 *
 * \param	u32Handle		(Input) An open handle, as returned by the Open function
 * \param	pstPara			(Output) SMC device config parameter
 *
 * \return	SMC Operation Error Code
 * \retval	ERROR_NO_ERROR					no error
 * \retval	ERROR_BAD_PARAMETER				Parameter is not valid
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid
 */

ErrorCode DRV_SMC_SetConfig (u32 u32Handle, PST_SMC_Config pstPara);
/*!\fn ErrorCode DRV_SMC_SetConfig (u32 u32Handle, PST_SMC_Config pstPara)
 *
 * \brief
 * 		To set the SMC configuration to be used
 *
 * \param	u32Handle		(Input) An open handle, as returned by the Open function
 * \param	pstPara			(Input) SMC device config parameter
 *
 * \return	SMC Operation Error Code
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_BAD_PARAMETER			Parameter is not valid
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 * \retval	ERROR_SMC_ERR_ACCESS		Operation invalid, because handle without access right
 */

ErrorCode DRV_SMC_Transfer (u32 u32Handle, PST_SMC_TransParms pstTransParms);
/*!\fn ErrorCode DRV_SMC_Transfer (u32 u32Handle, PST_SMC_TransParms pstTransParms)
 *
 * \brief
 *		Commence a write-read transaction with a smartcard device using current protocol type.
 *
 * \param	u32Handle			(Input)	An open handle number of the smartcard device.
 * \param	pstTransParms		(Output)Pointer to buffer which will be filled and config from / to the data transfer
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 * \retval	ERROR_SMC_ERR_AVAILABLE			Smartcard has not been inserted
 * \retval	ERROR_SMC_ERR_DEVICE_BUSY			The smartcard device is busy (card is locked).
 * \retval	ERROR_SMC_ERR_TRANSMIT				The transfer operation failed.
 * \retval	ERROR_SMC_ERR_TIMEOUT				The transfer operation timeout.
 * \retval	ERROR_SMC_ERR_NO_ANSWER			No response from the card
 * \retval	ERROR_SMC_ERR_INVALID_CLASS		The CLA byte was not recognized by the smartcard (T=0 only).
 * \retval	ERROR_SMC_ERR_INVALID_CODE			The INS byte was not recognized by the smartcard (T=0 only).
 * \retval	ERROR_SMC_ERR_INCORRECT_REFERENCE	The command sent to the smartcard contained an invalid reference.
 * \retval	ERROR_SMC_ERR_INCORRECT_LENGTH		The command sent to the smartcard did not contain the correct number of bytes.
 * \retval	ERROR_SMC_ERR_INVALID_STATUS_BYTE	One or more of the status bytes received from the card do not conform with the protocol (T=0).

 * \retval	ERROR_SMC_ERR_UNKNOW
 */

ErrorCode DRV_SMC_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_SMC_PWRCTRL enPwrCtrl, bool b8Force);
/*!\fn ErrorCode DRV_SMC_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_SMC_PWRCTRL enPwrCtrl, bool b8Force)
 *
 * \brief
 * 		Control the SMC device power mode
 *
 * \param	DeviceName		(Input) SMC device name to control
 * \param	enPwrCtrl		(Input) Setting the SMC device power mode
 * \param	b8Force			(Input) Force terminate the SMC or not
 \code
	bForce					description
	------------------		---------------------------
	True:	Terminate the SMC right now
	False:	wait until all handles close then terminate SMC
 \endcode
 *
 \code
	enPwrCtrl				description
	------------------		---------------------------
	EN_DRV_SMC_POWER_ON		SMC device in power on mode
	EN_DRV_SMC_STANDBY		SMC device in standby mode
 \endcode
 *
 * \return	SMC Operation Error Code
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER					Parameter is not valid
 * \retval	ERROR_SMC_ERR_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 * \retval	ERROR_SMC_ERR_UNKNOW_DEVICE		Invalid device name
 */

u8* DRV_SMC_GetRevision (void);
/*!\fn u8* DRV_SMC_GetRevision (void)
 *
 * \brief
 *		Get the version info of smartcard driver.
 *
 * \return	Return the version info of device driver
 */

ErrorCode DRV_SMC_Register_Notify(DRV_DeviceNameType DeviceName, EN_DRV_SMC_EVENT_TYPE enSmcEventNotify, DRV_SMC_CARD_IO_NOTIFY fpNotify);
/*!\fn ErrorCode DRV_SMC_Register_Notify(DRV_DeviceNameType DeviceName, EN_DRV_SMC_EVENT_TYPE enSmcEventNotify, DRV_SMC_CARD_IO_NOTIFY fpNotify)
 *
 * \brief
 *		Notify the SMC plugin/out function.
 *
 * \param	DeviceName			(Input) SMC device name to notify
 * \param	enSmcEventNotify	(Input) select plugin event or plugout event
 * \param	fpNotify			(Input) function pointer
 *
 * \return	SMC Operation Error Code
 * \retval	ERROR_NO_ERROR					no error
 * \retval	ERROR_SMC_ERR_UNKNOW_DEVICE	Invalid device name
 */

ErrorCode DRV_SMC_CMD_READ(u32 u32Handle, u8 u8Length, u8 Status[2]);

ErrorCode DRV_SMC_CheckCardAvailable(u32 u32Handle);
/*!\fn ErrorCode DRV_SMC_CheckCardAvailable(u32 u32Handle)
 *
 * \brief
 *		Get io status of the SMC.
 *
 * \param	u32Handle		(Input) An open handle, as returned by the Open function
 *
 * \return	Smartcard Operation Error Code
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_SMC_ERR_AVAILABLE	Smartcard has not been inserted.
 */
ErrorCode DRV_SMC_DeactivateCard(DRV_DeviceNameType DeviceName);

ErrorCode DRV_SMC_DecoderATR(EN_DRV_SMC_NO enSmcNo, u8 *pu8Anser, u8 u8Answerlength);
/*!\fn ErrorCode DRV_SMC_DecoderATR(EN_DRV_SMC_NO enSmcNo, u32 u32SmcCLK, u8 *pu8Anser, u8 u8Answerlength)
 *
 * \brief
 *		Decode ATR and reset baud rate the guard time
 *
 * \param	enSmcNo		(Input) SMC0 or SMC1
 			*pu8Anser	(Input) ATR
 			u8Answerlength (Input)ATR length
 *
 * \return	Smartcard Operation Error Code
 * \retval	TRUE			no error
 * \retval	FALSE	              error
 */

#endif //#ifndef __DRV_SMC_H__
