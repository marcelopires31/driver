//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide Consumer Electronics Control(CEC) Driver Control 
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

#ifndef	__DRV_CEC_H__
#define	__DRV_CEC_H__

#include "def_type.h"
#include "def_err.h"
#if 0
#include "drv_stbc.h"
#include "reg_drv_stbc.h"
#endif

/*******************************************************************************************/ 
/**
 * \brief
 *  DRV_STBC_CEC global define.
 */
#define	DRV_CEC_BUF_LENGTH						16


#define DRV_CEC_HW_CONFIRM_ENABLE

/*******************************************************************************************/ 
/**
 * \brief
 *  enumurate to indicate the CEC error
 */
enum
{
	ERROR_STBC_CEC_DEV_NAME     = ERROR_BASE_DRV_CEC,		    	/*!< Device Name Error                                    */
	ERROR_STBC_CEC_DEV_RESOURCE,		                            /*!< CEC don't have device resource                       */
	ERROR_STBC_CEC_IS_OPENED,		                                /*!< CEC is opened                                        */
	ERROR_STBC_CEC_IS_ENABLED,		                                /*!< CEC is enabled                                       */
	ERROR_STBC_CEC_IS_CLOSED_HANDLE,	                            /*!< Input Handle is closed                               */
	ERROR_STBC_CEC_BUF_TOO_SMALL,	                                /*!< Input buffer size too small to send/get CEC frame    */
	ERROR_STBC_CEC_DATA_NOT_READY,	                                /*!< It is not ready for set/get data          			  */
	ERROR_STBC_CEC_UNSUPPORT,										/*!< Un-support CEC control Type                          */
	ERROR_STBC_CEC_TX_RETRY,										/*!< TX retry error				                          */
	ERROR_STBC_CEC_TX_LOST,											/*!< TX lost arbitration error				              */
	ERROR_STBC_CEC_ERROR,											/*!< CEC error								              */
	ERROR_STBC_CEC_HW_CONFIRM,	                                    /*!< CEC confirm hardware setting fail                    */
};

/**
 * \brief
 *  enumurate to indicate the CEC Notify Status
 */
typedef enum
{
    EN_DRV_STBC_CEC_NOTIFY_STATUS_RECEIVE_READY,                   /*!< Frame data receive ready                                       */
    EN_DRV_STBC_CEC_NOTIFY_STATUS_NUM
}EN_DRV_STBC_CEC_NOTIFY_STATUS;

/**
 * \brief
 *  enumurate to indicate the CEC protocol
 */
typedef enum
{
 	EN_CEC_LOGADDR_DATA_ADDR,		/*!< Logical data address                 */
	EN_CEC_CMD_ADDR,				/*!< Opcode data address                  */
	EN_CEC_DATA_ADDR,				/*!< Parameter data address               */
	EN_CEC_PROTOCOL_MAX
}EN_CEC_PROTOCOL;

/*******************************************************************************************/ 
/**
 * \brief
 *  the CEC Notify function pointer
 */
typedef ErrorCode (*DRV_STBC_CEC_NOTIFY_FN)(u32 u32Handle, EN_DRV_STBC_CEC_NOTIFY_STATUS enStatus); 

/**
 * \brief
 *  the CEC initialize structure
 */
typedef struct
{
	u8										u8LogicAddr;			/*!< Logical Address								*/
	u32										u32SetCntDiv;			/*!< count divider									*/
	bool									b8WakeupEnable;			/*!< wake up enable									*/
} ST_DRV_STBC_CEC_INIT_PARAMS, *PST_DRV_STBC_CEC_INIT_PARAMS;

/**
 * \brief
 *  the CEC terminate structure
 */
typedef struct 
{
	bool	b8Force;						/*!< Force terminate CEC	                */
} ST_DRV_STBC_CEC_TERM_PARAMS, *PST_DRV_STBC_CEC_TERM_PARAMS;

/**
 * \brief
 *  the CEC open structure
 */
typedef struct
{
    DRV_STBC_CEC_NOTIFY_FN					pfnNotifyFn;            /*!< CEC Control Notify function pointer 			*/
} ST_DRV_STBC_CEC_OPEN_PARAMS, *PST_DRV_STBC_CEC_OPEN_PARAMS;

/**
 * \brief
 *  the CEC bit timing structure
 */
typedef struct
{
	u8										u8SetTxRiseEdgeOffset;	/*!< TX rising edge offset							*/
	u8										u8SetTxFallEdgeOffset;	/*!< TX falling edge offset							*/
	u32										u32SetRxStartBitRange;	/*!< RX start bit range								*/
	u8										u8SetRxDataBitRange;	/*!< RX data bit range								*/
	u8										u8SetRxSafeSmpData;		/*!< RX safe sample data							*/
	u8										u8SetTxRetryCnt;		/*!< TX retry count									*/
	u32										u32SetTxLowErrorPeriod;	/*!< TX low error period							*/
} ST_DRV_STBC_CEC_CONFIG_PARAMS, *PST_DRV_STBC_CEC_CONFIG_PARAMS;

/**
 * \brief
 *  the CEC information structure
 */
typedef struct
{
    bool	b8IsActiveSrc;
    u8		u8PowerStatus;
    u16		u16PhysicalAddr;
} ST_DRV_STBC_CEC_INFO, *PST_DRV_STBC_CEC_INFO;

/**
 * \brief
 *  the CEC data structure
 */
typedef struct
{
	u8 u8Src;
    u8 u8Dest;
	u32		u32Length;
	u8 		au8Frame[DRV_CEC_BUF_LENGTH];
} ST_DRV_STBC_CEC_Frame, *PST_DRV_STBC_CEC_Frame;

/*******************************************************************************************/ 
//function define
u8* DRV_STBC_CEC_GetVersion (void);
/*!\fn u8* DRV_STBC_CEC_GetVersion (void)
 * \brief 
 *		Get the Version number string of CEC
 *
 * 
 * \return CEC Version String
 * 
 */

ErrorCode DRV_STBC_CEC_Init			(DRV_DeviceNameType DeviceName, PST_DRV_STBC_CEC_INIT_PARAMS pstParams);
/*!\fn ErrorCode DRV_STBC_CEC_Init (DRV_DeviceNameType DeviceName, PST_DRV_STBC_CEC_INIT_PARAMS pstParams)
 * \brief 
 *		Initial the CEC with ST_DRV_STBC_CEC_INIT_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Init parameter
 * 
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success	
 * \retval ERROR_STBC_CEC_DEV_RESOURCE		CEC don't have device resource	
 * \retval ERROR_BAD_PARAMETER	            Parameter error 
 * \retval ERROR_INITIALISED	            CEC already Init
 * 
 */

ErrorCode DRV_STBC_CEC_Term			(DRV_DeviceNameType DeviceName, PST_DRV_STBC_CEC_TERM_PARAMS pstTerm);
/*!\fn ErrorCode DRV_STBC_CEC_Term (DRV_DeviceNameType DeviceName, PST_DRV_STBC_CEC_TERM_PARAMS pstTerm)
 * \brief 
 *		Terminate the CEC with ST_DRV_STBC_CEC_TERM_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstTerm		                    (Input)  Term parameter
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_STBC_CEC_IS_OPEN           Device still open and can't be terminated
 * \retval ERROR_STBC_CEC_DEV_NAME          Device name is not init
 *
 */

ErrorCode DRV_STBC_CEC_Open			(DRV_DeviceNameType DeviceName, PST_DRV_STBC_CEC_OPEN_PARAMS pstOpen, u32* pu32Handle);
/*!\fn ErrorCode DRV_STBC_CEC_Open (DRV_DeviceNameType DeviceName, PST_DRV_STBC_CEC_OPEN_PARAMS pstOpen, u32* pu32Handle)
 * \brief 
 *		Open the CEC with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstOpen		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) CEC Handle
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_STBC_CEC_DEV_RESOURCE      Resouce in used
 * \retval ERROR_STBC_CEC_DEV_NAME          Device name is not init
 */

ErrorCode DRV_STBC_CEC_Close			(u32* pu32Handle);
/*!\fn ErrorCode DRV_STBC_CEC_Close (u32* pu32Handle)
 * \brief 
 *		Close the CEC with a handle
 *
 * \param pu32Handle		                (Input)  CEC Handle
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 */

ErrorCode DRV_STBC_CEC_Enable		(u32 u32Handle);
/*!\fn ErrorCode DRV_STBC_CEC_Enable (u32 u32Handle)
 * \brief 
 *		Enable the CEC for start to receive and transmit data frame
 *
 * \param u32Handle		                    (Input)  CEC Handle
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_STBC_CEC_IS_ENABLED        CEC is enable.
 */

ErrorCode DRV_STBC_CEC_Disable		(u32 u32Handle);
/*!\fn ErrorCode DRV_STBC_CEC_Disable (u32 u32Handle)
 * \brief 
 *		Disable the CEC receive and transmit functions
 *
 * \param u32Handle		                    (Input)  CEC Handle
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 */

ErrorCode DRV_STBC_CEC_Send			(u32 u32Handle, PST_DRV_STBC_CEC_Frame pstTxData);
/*!\fn ErrorCode DRV_STBC_CEC_Send (u32 u32Handle, PST_DRV_STBC_CEC_Frame pstTxData)
 * \brief 
 *		Send the CEC frame.
 *
 * \param u32Handle		                    (Input)  CEC Handle
 * \param pstTxData		                    (Input)  Pointer of the data info(data with data length)
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_STBC_CEC_Recv			(u32 u32Handle, PST_DRV_STBC_CEC_Frame pstRxData, u32 u32BufSize);
/*!\fn ErrorCode DRV_STBC_CEC_Recv (u32 u32Handle, PST_DRV_STBC_CEC_Frame pstRxData, u32 u32BufSize)
 * \brief 
 *		Receive the CEC frame.
 *
 * \param u32Handle		                    (Input)  CEC Handle
 * \param pstRxData		                    (Output) Pointer of the data info(data with data length)
 * \param u32BufSize		                (Input)  Receive buffer Size
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_STBC_CEC_SetConfig			(u32 u32Handle, PST_DRV_STBC_CEC_CONFIG_PARAMS pstConfig);
/*!\fn ErrorCode DRV_STBC_CEC_SetConfig (u32 u32Handle, PST_DRV_STBC_CEC_CONFIG_PARAMS pstConfig)
 * \brief 
 *		To set the CEC configuration to be used.
 *
 * \param u32Handle		                    (Input)  CEC Handle
 * \param pstConfig		                    (Input) Pointer of the CEC config parameters
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_STBC_CEC_GetConfig (u32 u32Handle, PST_DRV_STBC_CEC_CONFIG_PARAMS pstConfig);
/*!\fn ErrorCode DRV_STBC_CEC_SetConfig (u32 u32Handle, PST_DRV_STBC_CEC_CONFIG_PARAMS pstConfig)
 * \brief 
 *		To get the parameter of the CEC configuration in use.
 *
 * \param u32Handle		                    (Input)  CEC Handle
 * \param pstConfig		                    (Output) Pointer of the CEC config parameters
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_STBC_CEC_Set_LogicalAddr		(u32 u32Handle, u8 u8LogicalAddr);
/*!\fn ErrorCode DRV_STBC_CEC_Set_LogicalAddr (u32 u32Handle, u8 u8LogicalAddr)
 * \brief 
 *		Set logical address of CEC device.
 *
 * \param u32Handle		                    (Input)  CEC Handle
 * \param u8LogicalAddr		                (Output) Logical address parameters
 *
 * \return CEC Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_CEC_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

#endif  //__DRV_CEC_H__
