//**************************************************************************
//         Copyright (c) , Novatek  Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author	:
//	Purpose	: Provide IPC (Inter processor communication) header file 
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

#ifndef __DRV_RTC_H__
#define __DRV_RTC_H__

#include "def_type.h"
#include "def_err.h"


/*******************************************************************************************/
#define DRV_RTC_MAX_NUM						(1)
#define STBC_RTC_STANDBY_ID					(0xaa553130)

#define SECOND_2_DHMS                       (TRUE)
#define DHMS_2_SECOND                       (FALSE)

/*******************************************************************************************/
/**
 * \brief
 *  RTC Error code definition.
 */
enum
{
	ERROR_STBC_RTC_OS_FAIL = ERROR_BASE_DRV_RTC,            /*!< OS Operation invalid 							    */		
	ERROR_STBC_RTC_DEV_NAME,                                /*!< Device Name Error									*/
	ERROR_STBC_RTC_DEV_RESOURCE,		                    /*!< RTC don't have device resource						*/
	ERROR_STBC_RTC_DEV_NOT_INIT,                            /*!< RTC is not initializated yet						*/
	ERROR_STBC_RTC_IS_OPENED,		                        /*!< RTC is opened										*/
	ERROR_STBC_RTC_IS_ENABLED,		                        /*!< RTC is enabled										*/
	ERROR_STBC_RTC_IS_CLOSED,	                            /*!< Input Handle is closed								*/
	ERROR_STBC_RTC_USING,   								/*!< RTC is using               						*/
	ERROR_STBC_RTC_UNSUPPORT,								/*!< Un-support RTC control Type						*/
	ERROR_STBC_RTC_EVENT_ERROR_OPEN,						/*!< RTC event error open                               */
	ERROR_STBC_RTC_EVENT_OPENED,
	ERROR_STBC_RTC_EVENT_UNOPEN,
	ERROR_STBC_RTC_EVENT_ERROR_SUBSCRIBE,
	ERROR_STBC_RTC_BUF_ALLOC,								/*!< Allocate memory failed								*/
	ERROR_STBC_RTC_OTHERS,	                                /*!< RTC other error                					*/
	ERROR_STBC_RTC_OPENTYPE
};// EN_STBC_RTC_ERROR;

/**
 * \brief
 * enumerate to indicate RTC control type.
 */
typedef enum
{
	EN_STBC_RTC_OPEN_INVALID_TYPE = 0,
	EN_STBC_RTC_OPEN_COUNTER,
	EN_STBC_RTC_OPEN_DOWNCOUNTER
}EN_STBC_RTC_OPEN_TYPE;


/**
 * \brief
 *  enumurate to indicate the RTC Notify Status
 */
typedef enum
{
	EN_DRV_RTC_EVENT_SEC,				/*!< RTC second trigger event */
	EN_DRV_RTC_EVENT_MIN,				/*!< RTC minute trigger event */
	EN_DRV_RTC_EVENT_HOUR,				/*!< RTC hour trigger event */
	EN_DRV_RTC_EVENT_DAY,				/*!< RTC day trigger event */
    EN_DRV_RTC_EVENT_NUM
}EN_DRV_RTC_EVENT_TYPE;


/*******************************************************************************************/

/**
 * \brief
 * enumerate to indicate RTC control command.
 */
typedef enum
{
	EN_STBC_RTC_CNT_CTRL_STP = 0,
	EN_STBC_RTC_CNT_CTRL_RST
}EN_STBC_RTC_CNT_CTRL;

/**
 * \brief
 * enumerate to indicate downcounter control command.
 */
typedef enum
{
	EN_STBC_RTC_DOWNCNT_CTRL_STP = 0,
	EN_STBC_RTC_DOWNCNT_CTRL_RST
}EN_STBC_RTC_DOWNCNT_CTRL;

/**
 * \brief
 * enumerate to indicate the path of RTC external clock.
 */
typedef enum
{
	EN_STBC_RTC_CLK_SRC_EXT = 0,
	EN_STBC_RTC_CLK_SRC_SYS,
	EN_STBC_RTC_CLK_SRC_27M
}EN_STBC_RTC_CLK_SRC;

/**
 * \brief
 *  the STBC Notify function pointer
 */
typedef ErrorCode (*DRV_STBC_RTC_NOTIFY_FN)(u32 u32Handle, u32 u32Status);

/**
 * \brief
 *  the STBC INIT Notify function pointer
 */
typedef bool (*DRV_RTC_INTR_NOTIFY_FN)(u32 u32Vector, u32 u32Param0, u32 u32Param1);


/**
 * \brief
 *  STBC-RTC initialize structure
 */
typedef struct
{
	EN_STBC_RTC_CLK_SRC						enRTCClkSrc;			/*!< clock source (only 310 chip used)	    		*/
	u32 									u32ExtClkHz; 			/*!< external clock frequency, default:27MHz (310)	*/
	u32										u32SetRTCDiv;			/*!< second level divider of RTC (310)				*/
	u32										u32SetDCntDiv;			/*!< second level divider of down counter (310)		*/
	bool 									b8EnDCntWakeup;			/*!< DownCounter weakup enable (310)				*/
    bool                                    b8ReprogramRTC;         /*!< Reprogram RTC parameter(310), ex:clock			*/
	bool 									b8EnTmSecInt;
	bool 									b8EnTmMinInt;
	bool 									b8EnTmHourInt;
	bool 									b8EnTmDayInt;
} ST_DRV_STBC_RTC_INIT_PARAMS, *PST_DRV_STBC_RTC_INIT_PARAMS;

/**
 * \brief
 *  the RTC open structure
 */
typedef struct
{
    DRV_STBC_RTC_NOTIFY_FN					pfnNotifyFn;            /*!< RTC Control Notify function pointer 			*/
    u32										u32EvtHandle;			/*!< Event handle for RTC 							*/
	EN_STBC_RTC_OPEN_TYPE					enOpenType; 			/*!< DownCounter or RTC timer	 					*/
} ST_DRV_STBC_RTC_OPEN_PARAMS, *PST_DRV_STBC_RTC_OPEN_PARAMS;

/**
 * \brief
 *  the RTC configuration structure
 */
typedef struct
{
	u32 									u32DownCounterSec;
	u32 									u32RTCBaseSecTime;
} ST_DRV_STBC_RTC_CONFIG_PARAMS, *PST_DRV_STBC_RTC_CONFIG_PARAMS;


/**
 * \brief
 *  the RTC day-time data structure.
 */
typedef struct
{
	u16										u16Day;
	u8 										u8Hour;
	u8 										u8Min;
	u8 										u8Sec;
	u32 									u32BaseTime;
} ST_DRV_STBC_RTC_DHMS, *PST_DRV_STBC_RTC_DHMS;



/*******************************************************************************************/
ErrorCode DRV_STBC_RTC_Init (DRV_DeviceNameType DeviceName, PST_DRV_STBC_RTC_INIT_PARAMS pstInit);
ErrorCode DRV_STBC_RTC_Term (DRV_DeviceNameType DeviceName);
ErrorCode DRV_STBC_RTC_Open (DRV_DeviceNameType DeviceName, PST_DRV_STBC_RTC_OPEN_PARAMS pstOpen, u32* pu32Handle);
ErrorCode DRV_STBC_RTC_Close (u32* pu32Handle);
ErrorCode DRV_STBC_RTC_SetConfig (u32 u32Handle, PST_DRV_STBC_RTC_CONFIG_PARAMS pstConfig);
ErrorCode DRV_STBC_RTC_GetConfig (u32 u32Handle, PST_DRV_STBC_RTC_CONFIG_PARAMS pstConfig);
ErrorCode DRV_STBC_RTC_Enable (u32 u32Handle);
ErrorCode DRV_STBC_RTC_Disable (u32 u32Handle);
ErrorCode DRV_STBC_RTC_EventActive (u32 u32Handle, EN_DRV_RTC_EVENT_TYPE enTimerEvent, bool b8Enable);
ErrorCode DRV_STBC_RTC_IntActive (DRV_DeviceNameType DeviceName, EN_DRV_RTC_EVENT_TYPE enTimerEvent, bool b8Enable);
ErrorCode DRV_STBC_RTC_GetDHMSTime (u32 u32Handle, PST_DRV_STBC_RTC_DHMS pDHMS);
//ErrorCode DRV_STBC_GetResetType (EN_DRV_STBC_RESET_ID_TYPE* penResetIdType);
//ErrorCode DRV_STBC_SetResetType (EN_DRV_STBC_RESET_ID_TYPE enResetIdType);
void DRV_STBC_RTC_Event_Msg (u32 u32EVTHandle, u32 u32EventID, u32 u32Data);
u8* DRV_STBC_RTC_GetVersion (void);
ErrorCode DRV_STBC_RTC_DHMS_Conver(bool b8ToDHMS, u32* pu32Sec, u32* pu32DHMS);

#endif /* __DRV_RTC_H__ */


