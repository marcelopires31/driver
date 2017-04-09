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

#ifndef __DRV_IPC_H__
#define __DRV_IPC_H__

#include "def_type.h"
#include "def_err.h"
#include "drv_stbc.h"


/*******************************************************************************************/

/**
 * \brief
 *  IPC Error code definition.
 */
enum
{
	ERROR_STBC_IPC_OS_FAIL = ERROR_BASE_DRV_IPC,                /*!< OS Operation invalid 							    */		
	ERROR_STBC_IPC_DEV_NAME,		                            /*!< Device Name Error									*/
	ERROR_STBC_IPC_DEV_RESOURCE,		                        /*!< IPC don't have device resource						*/
	ERROR_STBC_IPC_DEV_NOT_INIT,                                /*!< IPC is not initializated yet						*/
	ERROR_STBC_IPC_IS_OPENED,		                            /*!< IPC is opened										*/
	ERROR_STBC_IPC_IS_ENABLED,		                            /*!< IPC is enabled										*/
	ERROR_STBC_IPC_IS_CLOSED_HANDLE,	                        /*!< Input Handle is closed								*/
	ERROR_STBC_IPC_UNSUPPORT,									/*!< Un-support IPC control Type							*/
	ERROR_STBC_IPC_ERROR,										/*!< IPC is error										*/
	ERROR_STBC_IPC_BUF_ALLOC,									/*!< Allocate memory failed								*/
	ERROR_STBC_IPC_HW_CONFIRM,	                                /*!< IPC confirm hardware setting fail					*/
	ERROR_STBC_IPC_EVENT_ERROR_OPEN,							// IPC event error open
	ERROR_STBC_IPC_EVENT_OPENED,
	ERROR_STBC_IPC_EVENT_UNOPEN,
	ERROR_STBC_IPC_EVENT_ERROR_SUBSCRIBE,
	ERROR_STBC_IPC_CMD_ERROR,
	ERROR_STBC_IPC_OS_ERROR,
	ERROR_STBC_IPC_OPENTYPE

};// EN_STBC_IPC_ERROR;

/**
 * \brief
 *  Enumerate to indicate EventID definition.
 */
typedef enum
{
	EN_DRV_IPC_EVENT_UPLOAD,
	EN_DRV_IPC_EVENT_NUM
}EN_DRV_IPC_EVENT_TYPE;


typedef struct 
{
	u32									u32Temp;	
} ST_DRV_STBC_IPC_INIT_PARAMS, *PST_DRV_STBC_IPC_INIT_PARAMS;

typedef struct
{
	DRV_STBC_NOTIFY_FN						pfnNotifyFn;            // IPC Control Notify function pointer 			
    u32										u32EvtHandle;			// Event handle for IPC
} ST_DRV_STBC_IPC_OPEN_PARAMS, *PST_DRV_STBC_IPC_OPEN_PARAMS;



typedef enum
{
	EN_IPC_SET_STBC_STATE=0x00,
	EN_IPC_GET_STBC_STATE, 
	EN_IPC_RET_STBC_STATE,
	EN_IPC_GET_WAKEUP_CODE,
	EN_IPC_RET_WAKEUP_CODE,
	EN_IPC_SET_WAKEUP_TIME_H,
	EN_IPC_SET_WAKEUP_TIME_L,
	EN_IPC_SET_IR0_POWER_CODE_H,
	EN_IPC_SET_IR0_POWER_CODE_L,
	EN_IPC_SET_KEY_POWER_CODE,

    EN_IPC_SET_VFD_ONOFF_LIGHT = 0x0F,

    EN_IPC_GET_MCU_SW_VER_DATE_H,
    EN_IPC_GET_MCU_SW_VER_DATE_L,
    EN_IPC_GET_MCU_SW_VER_NO_H, 
    EN_IPC_GET_MCU_SW_VER_NO_L,  

    EN_IPC_RET_MCU_SW_VER_DATE_H,
    EN_IPC_RET_MCU_SW_VER_DATE_L,
    EN_IPC_RET_MCU_SW_VER_NO_H, 
    EN_IPC_RET_MCU_SW_VER_NO_L,  

    EN_IPC_SET_MCU_WDT_ENABLE,
    EN_IPC_SET_MCU_REFRESH_WDT,

    EN_IPC_SET_IR1_POWER_CODE_H = 0x29,
    EN_IPC_SET_IR1_POWER_CODE_L  =0x2A,

    EN_IPC_GET_51_Reg  = 0xE0,
    EN_IPC_SET_51_Reg  = 0xE1,
    
    EN_IPC_51_Printf_Via_MIPS = 0xF0,
    EN_IPC_51_MSG_to_MIPS,
    
} EN_IPC_STATUS;

typedef enum
{
    EN_IPC_WAKEUP_NO_EVENT      = (0x0000),     
    EN_IPC_WAKEUP_RTC           = (0x0001),     
    EN_IPC_WAKEUP_HDMI_CEC      = (0x0002),     
    EN_IPC_WAKEUP_IR            = (0x0004),     
    EN_IPC_WAKEUP_PWSW          = (0x0008),     // power key event.
    EN_IPC_WAKEUP_HDMI_HPD      = (0x0010),     
    EN_IPC_WAKEUP_KEY           = (0x0020),     // vfd key scan    
    EN_IPC_WAKEUP_MASK          = (0x003f),    
    EN_IPC_WAKEUP_EVENT_NUM     = 6,
} EN_IPC_WAKEUP_EVENT;

/**
 * \brief
 *  the STBC INIT Notify function pointer
 */
typedef bool (*DRV_IPC_INTR_NOTIFY_FN)(u32 u32Vector, u32 u32Param0, u32 u32Param1);


/*******************************************************************************************/
// STBC register control
/*******************************************************************************************/
//The following API is only called by driver layer.

ErrorCode DRV_STBC_IPC_Init (DRV_DeviceNameType DeviceName, PST_DRV_STBC_IPC_INIT_PARAMS pstInit);
ErrorCode DRV_STBC_IPC_Term (DRV_DeviceNameType DeviceName);
ErrorCode DRV_STBC_IPC_Open (DRV_DeviceNameType DeviceName, PST_DRV_STBC_IPC_OPEN_PARAMS pstOpen, u32* pu32Handle);
ErrorCode DRV_STBC_IPC_Close (u32* pu32Handle);
ErrorCode DRV_STBC_IPC_Enable (u32 u32Handle);
ErrorCode DRV_STBC_IPC_Disable (u32 u32Handle);
ErrorCode DRV_STBC_IPC_Get_DeviceSupportStatus (void);
bool DRV_STBC_IPC_Get_McuBootMsg (void);

ErrorCode DRV_STBC_IPC_Event_Open(u32* pu32IpcEvtHandle);
ErrorCode DRV_STBC_IPC_Event_Close(u32* pu32IpcEvtHandle);
ErrorCode DRV_STBC_IPC_Event_Subscribe(u32 u32IpcEvtHandle);

ErrorCode DRV_STBC_IPC_Load_8051_SRAM(void);

ErrorCode STBC_IPC_SendCommand(EN_IPC_STATUS enMode,u8 u8Data0, u8 u8Data1);
void STBC_IPC_SendAck(u8 u8AckMode);
ErrorCode DRV_STBC_IPC_CMD_SetIRPowerKey (u8 u8Path,u32 u32PowerKey);
ErrorCode DRV_STBC_IPC_CMD_SetRTCWakeupTime (u32 u32WakeupTime);
ErrorCode DRV_STBC_IPC_CMD_CutoffPower (bool b8MonitorRTC);

ErrorCode DRV_STBC_IPC_CMD_GetMcuSwDate (u32 *pu32SwDate);
ErrorCode DRV_STBC_IPC_CMD_GetMcuVer (u32 *pu32Ver);
ErrorCode DRV_STBC_IPC_CMD_GetMcuStatus (u16 *pu16Status);
ErrorCode DRV_STBC_IPC_CMD_GetWakeupEvent (EN_IPC_WAKEUP_EVENT* penWakeupEvent);

//MCU monitor MIPS (4sec.) 
ErrorCode DRV_STBC_IPC_CMD_EnableMcuWatchDog (bool b8Enable);
ErrorCode DRV_STBC_IPC_CMD_RefreshMcuWatchDog (void);
#endif /* __DRV_IPC_H__ */


