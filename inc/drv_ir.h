//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide IR Driver Control 
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

#ifndef	__DRV_IR_H__
#define	__DRV_IR_H__

#include "os.h"
#include "def_type.h"
#include "def_err.h"
#include "drv_stbc.h"
#include "drv_config.h"

/*******************************************************************************************/ 
/**
 * \brief
 *  DRV_STBC_IR global define.
 */


/*******************************************************************************************/ 
/*!
 * \brief
 * enumerate to IR device
 */
typedef enum
{
	EN_DRV_IR_0,
	EN_DRV_IR_NUM
}EN_DRV_IR_NO;

/*!
 * \brief
 * enumerate to IR power control
 */
typedef enum
{
	EN_DRV_IR_POWER_ON,
	EN_DRV_IR_STANDBY,
	EN_DRV_IR_PWRCTRL_NUM
}EN_DRV_IR_PWRCTRL;

typedef enum
{
	EN_DRV_IR_FREQ_100K,	/*!< 100 KHz */
	EN_DRV_IR_FREQ_50K,	/*!< 50 KHz */
	EN_DRV_IR_FREQ_10K,	/*!< 10 KHz */
	EN_DRV_IR_FREQ_5K,	/*!< 5 KHz */	
	EN_DRV_IR_FREQ_NUM
}EN_DRV_IR_SAMPLE_FREQ;
/*!
 * \brief
 * enumerate to indicate the sampling frequency of IR
 */

/**
 * \brief
 *  IR Error code definition.
 */
enum
{
	ERROR_STBC_IR_OS_FAIL     = ERROR_BASE_DRV_IR,			    /*!< OS Operation invalid								*/	
	ERROR_STBC_IR_DEV_NAME,                                     /*!< Device Name Error									*/
	ERROR_STBC_IR_DEV_RESOURCE,		                            /*!< IR don't have device resource						*/
	ERROR_STBC_IR_IS_OPENED,		                            /*!< IR is opened										*/
	ERROR_STBC_IR_IS_ENABLED,		                            /*!< IR is enabled										*/
	ERROR_STBC_IR_IS_CLOSED_HANDLE,	                            /*!< Input Handle is closed								*/
	ERROR_STBC_IR_UNSUPPORT,									/*!< Un-support IR control Type							*/
	ERROR_STBC_IR_ERROR,										/*!< IR is error										*/
	ERROR_STBC_IR_BUF_ALLOC,									/*!< Allocate memory failed								*/
	ERROR_STBC_IR_HW_CONFIRM,	                                /*!< IR confirm hardware setting fail					*/
	ERROR_STBC_IR_OPENTYPE
};


/**
 * \brief
 *  enumurate to indicate the IR Notify Status
 */
typedef enum
{
	EN_DRV_IR_EVENT_KEY_CODE,			/*!< Key code event */
	EN_DRV_IR_EVENT_REPEAT_KEY_CODE,	/*!< Repeat key code event */
	EN_DRV_IR_EVENT_SYMBOL,				/*!< Symbol event */
	EN_DRV_IR_EVENT_CHANGE_CONFIG,		/*!< Change config event */
	EN_DRV_IR_EVENT_POWER_DOWN,			/*!< Power down event */
	EN_DRV_IR_EVENT_TERM,				/*!< Terminate event */
    EN_DRV_IR_EVENT_NUM
}EN_DRV_IR_EVENT_TYPE;

/**
 * \brief
 *  enumurate to indicate the IR method
 */
typedef enum
{
	EN_STBC_IR_METHOD_SPACE = 0,								/*!< space coding								*/
	EN_STBC_IR_METHOD_PULSE,									/*!< pulse coding								*/
	EN_STBC_IR_METHOD_BIPHASE_RC5,								/*!< RC5 bi-phase coding						*/
	EN_STBC_IR_METHOD_BIPHASE_RC6								/*!< RC6 bi-phase coding						*/
}EN_STBC_IR_METHOD;

/**
 * \brief
 *  enumurate to indicate the IR mode
 */
typedef enum
{
	EN_STBC_IR_MODE_NEC = 0,									/*!< NEC mode								*/
	EN_STBC_IR_MODE_SONY,										/*!< SONY mode								*/
	EN_STBC_IR_MODE_RC5,										/*!< RC5 mode								*/
	EN_STBC_IR_MODE_RC6,										/*!< RC6 mode								*/
	EN_STBC_IR_MODE_SW_NEC,										/*!< Raw mode 								*/
	EN_STBC_IR_MODE_SW_SONY, 									/*!< Raw mode, Need adding software code!!! */
	EN_STBC_IR_MODE_SW_RC5, 									/*!< Raw mode, Need adding software code!!!	*/
	EN_STBC_IR_MODE_SW_RC6, 									/*!< Raw mode, Need adding software code!!! */
	EN_STBC_IR_MODE_TIMING										/*!< Raw mode for other not defined IR  	*/
}EN_STBC_IR_MODE;

/*******************************************************************************************/ 
/**
 * \brief
 *  the IR Notify function pointer
 */
typedef ErrorCode (*DRV_STBC_IR_NOTIFY_FN)(u32 u32Handle, EN_DRV_IR_EVENT_TYPE enStatus); 

/**
 * \brief
 *  the IR symbol structure
 */
typedef struct 
{
	u16	u16HighCnt;		/*!< The high count of a symbol in microseconds */
	u16	u16LowCnt;		/*!< The low count of a symbol in microseconds */
}ST_IR_Symbol, *PST_IR_Symbol;


/**
 * \brief
 *  the IR raw mode structure
 */
typedef struct 
{
	ST_IR_Symbol			*pstBuffer;			/*!< Pointer to the result buffer */
	u32						u32Size;			/*!< Maximum number of key code/symbol to read into buffer */
	u32						u32ReadTimeout;		/*!< Total inactivity time in milliseconds to allow. A timeout value of 0 specifies an infinite time-out */
	u32						u32IntrTrigThd;		// (new added for 320S)transient number threshod in FIFO. Once FIFO data reach this threshold, will trigger an interrupt (get enough pulse) 
}ST_IR_Raw_Config;

/**
 * \brief
 *  the IR protocol timing structure
 */
typedef struct
{
	u32										u32HeadPulseTimingMin;          /*!< header pulse timing minimum		*/
	u32										u32HeadPulseTimingMax;          /*!< header pulse timing maximum		*/
	u32										u32HeadSpaceTimingMin;          /*!< header space timing minimum		*/
	u32										u32HeadSpaceTimingMax;          /*!< header space timing maximum		*/
	u32										u32Log0PulseTimingMin;          /*!< logical 0 pulse timing minimum		*/
	u32										u32Log0PulseTimingMax;          /*!< logical 0 pulse timing maximum		*/
	u32										u32Log0SpaceTimingMin;          /*!< logical 0 space timing minimum		*/
	u32										u32Log0SpaceTimingMax;          /*!< logical 0 space timing maximum		*/
	u32										u32Log1PulseTimingMin;          /*!< logical 1 pulse timing minimum		*/
	u32										u32Log1PulseTimingMax;          /*!< logical 1 pulse timing maximum		*/
	u32										u32Log1SpaceTimingMin;          /*!< logical 1 space timing minimum		*/
	u32										u32Log1SpaceTimingMax;          /*!< logical 1 space timing maximum		*/
	u32										u32RptCodePulseTimingMin;       /*!< repeat code pulse timing minimum	*/
	u32										u32RptCodePulseTimingMax;       /*!< repeat code pulse timing maximum	*/
	u32										u32RptCodeSpaceTimingMin;       /*!< repeat code space timing minimum	*/
	u32										u32RptCodeSpaceTimingMax;       /*!< repeat code space timing maximum	*/
	u32										u32BiPhaseTimingMin;            /*!< bi-phse timing minimum				*/
	u32										u32BiPhaseTimingMax;            /*!< bi-phse timing maximum				*/
    u32                                     u32Glitch;
}ST_DRV_STBC_IR_TIMING, *PST_DRV_IR_TIMING;

/**
 * \brief
 *  the IR control block structure
 */
typedef struct
{
    bool                                    b8DefMySelf;
	bool									b8IREnable;			        /*!< IR enable										*/
	u32										u32SetCodeLen;
	EN_STBC_IR_MODE							enIrMode;
	EN_STBC_IR_METHOD						enIrMethod;
	bool									b8RptCodeDtcEnable;
	bool									b8WakeUpCodeDtcEnable;
	bool									b8AnyKeyWakeUp;
	u32										u32WakeUpKeyCode;
	bool									b8InvPolarEnable;
    ST_DRV_STBC_IR_TIMING                   stIrTiming;
	ST_IR_Raw_Config						stIrRawMode;
}ST_DRV_STBC_IR_CTRL_BLOCK, *PST_DRV_STBC_IR_CTRL_BLOCK;


/**
 * \brief
 *  the IR initialize structure
 */
typedef struct
{
	os_mempool_handle						u32MemPoolHandle;	    /*!< A memory pool handle for IR module	*/
    ST_DRV_STBC_IR_CTRL_BLOCK               stIrCtrl;
} ST_DRV_STBC_IR_INIT_PARAMS, *PST_DRV_STBC_IR_INIT_PARAMS;

/**
 * \brief
 *  the IR terminate structure
 */
typedef struct 
{
	bool	b8Force;												/*!< Force terminate IR	                */
} ST_DRV_STBC_IR_TERM_PARAMS, *PST_DRV_STBC_IR_TERM_PARAMS;

/**
 * \brief
 *  the IR open structure
 */
typedef struct
{
    DRV_STBC_IR_NOTIFY_FN					pfnNotifyFn;            /*!< IR Control Notify function pointer 			*/
    u32										u32EvtHandle;			/*!< Event handle for IR 			*/
} ST_DRV_STBC_IR_OPEN_PARAMS, *PST_DRV_STBC_IR_OPEN_PARAMS;


typedef struct
{
    bool									b8Used;
	bool									b8Enable;
	u32 									u32Handle;	
    u32										u32EvtHandle;
    ST_DRV_STBC_IR_OPEN_PARAMS				stIrOpen;
    ST_DRV_STBC_IR_CTRL_BLOCK				stIrCtrlBlock;
}ST_DRV_IR_CTRL_HANDLE, *PST_DRV_IR_CTRL_HANDLE;


/**
 * \brief
 *  the IR configuration structure
 */
typedef struct
{
	bool									b8IREnable;			        /*!< IR enable										*/
	u32										u32SetCodeLen;				/*!< code length									*/
	EN_STBC_IR_MODE							enIrMode;					/*!< IR mode										*/
	bool									b8RptCodeDtcEnable;			/*!< repeat code detect enable						*/
	u32										u32WakeUpKeyCode;			/*!< wake up key code								*/
} ST_DRV_STBC_IR_CONFIG_PARAMS, *PST_DRV_STBC_IR_CONFIG_PARAMS;


/**
 * \brief
 *  the STBC INIT Notify function pointer
 */
typedef bool (*DRV_IR_INTR_NOTIFY_FN)(u32 u32Vector, u32 u32Param0, u32 u32Param1);

/*******************************************************************************************/ 
//function define
u8* DRV_STBC_IR_GetVersion (void);
/*!\fn u8* DRV_STBC_IR_GetVersion (void)
 * \brief 
 *		Get the Version number string of IR
 *
 * 
 * \return IR Version String
 * 
 */

ErrorCode DRV_STBC_IR_Init			(DRV_DeviceNameType DeviceName, PST_DRV_STBC_IR_INIT_PARAMS pstParams);
/*!\fn ErrorCode DRV_STBC_IR_Init (DRV_DeviceNameType DeviceName, PST_DRV_STBC_IR_INIT_PARAMS pstParams)
 * \brief 
 *		Initial the IR with ST_DRV_STBC_IR_INIT_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Init parameter
 * 
 * \return IR Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success	
 * \retval ERROR_STBC_IR_DEV_RESOURCE		IR don't have device resource	
 * \retval ERROR_BAD_PARAMETER	            Parameter error 
 * \retval ERROR_INITIALISED	            IR already Init
 * 
 */

ErrorCode DRV_STBC_IR_Term			(DRV_DeviceNameType DeviceName, PST_DRV_STBC_IR_TERM_PARAMS pstTerm);
/*!\fn ErrorCode DRV_STBC_IR_Term (DRV_DeviceNameType DeviceName, PST_DRV_STBC_IR_TERM_PARAMS pstTerm)
 * \brief 
 *		Terminate the IR with ST_DRV_STBC_IR_TERM_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstTerm		                    (Input)  Term parameter
 *
 * \return IR Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_STBC_IR_IS_OPEN           Device still open and can't be terminated
 * \retval ERROR_STBC_IR_DEV_NAME          Device name is not init
 *
 */

ErrorCode DRV_STBC_IR_Open			(DRV_DeviceNameType DeviceName, PST_DRV_STBC_IR_OPEN_PARAMS pstOpen, u32* pu32Handle);
/*!\fn ErrorCode DRV_STBC_IR_Open (DRV_DeviceNameType DeviceName, PST_DRV_STBC_IR_OPEN_PARAMS pstOpen, u32* pu32Handle)
 * \brief 
 *		Open the IR with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstOpen		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) IR Handle
 *
 * \return IR Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_STBC_IR_DEV_RESOURCE      Resouce in used
 * \retval ERROR_STBC_IR_DEV_NAME          Device name is not init
 */

ErrorCode DRV_STBC_IR_Close			(u32* pu32Handle);
/*!\fn ErrorCode DRV_STBC_IR_Close (u32* pu32Handle)
 * \brief 
 *		Close the IR with a handle
 *
 * \param pu32Handle		                (Input)  IR Handle
 *
 * \return IR Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_IR_IS_CLOSED_HANDLE	Closed handle
 */

ErrorCode DRV_STBC_IR_Enable		(u32 u32Handle, bool b8Enable);
/*!\fn ErrorCode DRV_STBC_IR_Enable (u32 u32Handle, bool b8Enable)
 * \brief 
 *		Enable the event callback or not associated with a handle
 *
 * \param u32Handle		                    (Input)  IR Handle
 * \param b8Enable							(Input)  Enable the event callback or not
 \code
	True:	enable the event callback
	False:	disable the event callback
 \endcode 
 *
 * \return IR Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_IR_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_STBC_IR_IS_ENABLED        IR is enable.
 */

ErrorCode DRV_STBC_IR_Disable		(u32 u32Handle);
/*!\fn ErrorCode DRV_STBC_IR_Disable (u32 u32Handle)
 * \brief 
 *		Disable the event callback associated with a handle
 *
 * \param u32Handle		                    (Input)  IR Handle
 *
 * \return IR Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_IR_IS_CLOSED_HANDLE	Closed handle
 */


ErrorCode DRV_STBC_IR_GetConfig			(u32 u32Handle, PST_DRV_STBC_IR_CONFIG_PARAMS pstConfig);
/*!\fn DRV_STBC_IR_GetConfig (u32 u32Handle, PST_DRV_STBC_IR_CONFIG_PARAMS pstConfig)
 * \brief 
 *		To get the parameter of the IR configuration in use.
 *
 * \param u32Handle		                    (Input)  IR Handle
 * \param pstConfig		                    (Output) Pointer of the IR config parameters
 *
 * \return IR Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_STBC_IR_IS_CLOSED_HANDLE	Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_IR_EventCallback_Enable (u32 u32Handle, bool b8Enable);
/*!\fn ErrorCode DRV_IR_EventCallback_Enable (u32 u32Handle, bool b8Enable)
 * 
 * \brief
 * 		Enable the event callback or not associated with a handle
 * 
 * \param	u32Handle			(Input) An open handle number of the IR device
 * \param	b8Enable				(Input) Enable the event callback or not
 \code
	True:	enable the event callback
	False:	disable the event callback
 \endcode  
 * 
 * \return	IR Operation Error Code
 * \retval	ERROR_NO_ERROR			Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 */

ErrorCode DRV_STBC_IR_Test_Close_Term_All(DRV_DeviceNameType DeviceName, PST_DRV_STBC_IR_TERM_PARAMS pstTerm);

void DRV_IR_EnableDumpRawData(bool b8EnDump);
#endif  //__DRV_IR_H__
