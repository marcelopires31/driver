//**************************************************************************
//         Copyright (c) , Novatek  Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide STBC Control
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

#ifndef __DRV_STBC_H__
#define __DRV_STBC_H__

#include "def_type.h"
#include "def_err.h"
#include "drv_config.h"
#include "sen5_sw_config.h"   //add by wujiang


/*-----------------------------------------------------------------------------*/
/* Definitions                                                                 */
/*-----------------------------------------------------------------------------*/
#define STBC_IO_LEV_HIGH 						(1)
#define STBC_IO_LEV_LOW 						(0)

#define DRV_STBC_GPIO_MAX_NUM					(12)

//320s Interrupt mask
#define DRV_STBC_INT_EDGE_TYPE_MASK             (0x80)
#define DRV_STBC_INT_NO_PARSE(INT_NO)           (INT_NO & (~DRV_STBC_INT_EDGE_TYPE_MASK))

//320s GPIO interrupt vector
#define DRV_STBC_GP7_RISING_INT                 (DRV_STBC_INT_EDGE_TYPE_MASK | 0)
#define DRV_STBC_GP8_RISING_INT                 (DRV_STBC_INT_EDGE_TYPE_MASK | 1)
#define DRV_STBC_GP9_RISING_INT                 (DRV_STBC_INT_EDGE_TYPE_MASK | 2)
#define DRV_STBC_GP10_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 3)
#define DRV_STBC_GP11_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 4)
#define DRV_STBC_GP12_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 5)
#define DRV_STBC_GP13_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 6)
#define DRV_STBC_GP14_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 7)
#define DRV_STBC_GP15_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 8)
#define DRV_STBC_GP16_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 9)
#define DRV_STBC_GP17_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 10)
#define DRV_STBC_GP18_RISING_INT                (DRV_STBC_INT_EDGE_TYPE_MASK | 11)

#define DRV_STBC_GP7_FALLING_INT                (0)
#define DRV_STBC_GP8_FALLING_INT                (1)
#define DRV_STBC_GP9_FALLING_INT                (2)
#define DRV_STBC_GP10_FALLING_INT               (3)
#define DRV_STBC_GP11_FALLING_INT               (4)
#define DRV_STBC_GP12_FALLING_INT               (5)
#define DRV_STBC_GP13_FALLING_INT               (6)
#define DRV_STBC_GP14_FALLING_INT               (7)
#define DRV_STBC_GP15_FALLING_INT               (8)
#define DRV_STBC_GP16_FALLING_INT               (9)
#define DRV_STBC_GP17_FALLING_INT               (10)
#define DRV_STBC_GP18_FALLING_INT               (11)
/*-----------------------------------------------------------------------------*/
/* Enum Definitions                                                                 */
/*-----------------------------------------------------------------------------*/
/**
 * \brief
 * enumerate to indicate the error of operation
 */
enum
{
	ERROR_STBC_OS_FAIL = ERROR_BASE_DRV_STBC,	/*!< OS Operation invalid 							*/
    ERROR_STBC_DEV_NAME,    	            	/*!< STBC device name error         				*/
	ERROR_STBC_DEV_NO_RESOURCE,	            	/*!< STBC device don't have resource				*/
    ERROR_STBC_DEV_NOT_INIT,                    /*!< STBC device is not initializated yet		    */
	ERROR_STBC_DEV_IS_OPENED,		            /*!< STBC device is opened							*/
	ERROR_STBC_DEV_IS_ENABLED,		            /*!< STBC device is enabled							*/
	ERROR_STBC_DEV_IS_CLOSED,					/*!< STBC device is cloesed 						*/
	ERROR_STBC_DEV_USING,						/*!< STBC device is using 							*/    
	ERROR_STBC_DEV_UNSUPPORT,					/*!< STBC device don't support this action or API   */
	ERROR_STBC_DEV_EVENT_ERROR_OPEN,			/*!< STBC device event error open                   */
	ERROR_STBC_DEV_EVENT_OPENED,
	ERROR_STBC_DEV_EVENT_UNOPEN,
	ERROR_STBC_DEV_EVENT_ERROR_SUBSCRIBE,
	ERROR_STBC_IO_CTRL_FAIL,					/*!< STBC device I/O control fail	    			*/
	ERROR_STBC_51SRAM_LOADED,
    ERROR_STBC_HAL_NOT_INIT,                    /*!< STBC device is not initializated yet		    */
	ERROR_STBC_BUF_ALLOC,						/*!< Allocate memory failed							*/
	ERROR_STBC_OTHERS, 							/*!< Other error									*/
	ERROR_STBC_TOTAL
}; //EN_DRV_STBC_ERROR;


/*!
 * \brief
 * enumerate to 8051 SRAM authority switch control
 */
//!!!! This enum type only are used in 320s platform.
typedef enum
{
	EN_DRV_STBC_51SRAM_CTRL_BY_MIPS,
	EN_DRV_STBC_51SRAM_CTRL_BY_8051,
	EN_DRV_STBC_51SRAM_CTRL_NUM
}EN_DRV_STBC_51SRAM_CTRL;

/*!
 * \brief
 * enumerate to STBC H/W switch control
 */
//!!!! This enum type only are used in 320s platform.
typedef enum
{
	EN_DRV_STBC_HW_CTRL_BY_MIPS,
	EN_DRV_STBC_HW_CTRL_BY_8051,
	EN_DRV_STBC_HW_CTRL_NUM
}EN_DRV_STBC_HW_CTRL;

/*!
 * \brief
 * enumerate to STBC sync inform mode
 */
typedef enum
{
	EN_DRV_STBC_SYNC1_INFO_0,        /*!< 310/320s/316								*/
	EN_DRV_STBC_SYNC1_INFO_1,        /*!< 320s/316	    							*/
	EN_DRV_STBC_SYNC1_INFO_2,        /*!< 320s/316	    							*/
	EN_DRV_STBC_SYNC1_INFO_3,        /*!< 320s/316	    							*/

	EN_DRV_STBC_SYNC2_INFO_0,        /*!< 320s/316					 			    */
	EN_DRV_STBC_SYNC2_INFO_1,        /*!< 320s/316	    							*/
	EN_DRV_STBC_SYNC2_INFO_2,        /*!< 320s/316	    							*/
	EN_DRV_STBC_SYNC2_INFO_3,        /*!< 320s/316	    							*/

	EN_DRV_STBC_SYNC_INFO_NUM,
}EN_DRV_STBC_SYNC_INFO_MODE;

/**
 * \brief
 * enumerate to indicate PBC control type.
 */
typedef enum
{
	EN_DRV_STBC_PBC_OPEN_INVALID_TYPE = 0,
	EN_DRV_STBC_PBC_OPEN_PWSW,
	EN_DRV_STBC_PBC_OPEN_HOTPLUG
}EN_DRV_STBC_PBC_OPEN_TYPE;

/**
 * \brief
 * enumerate to indicate PBC event index.
 */
typedef enum
{
	EN_DRV_STBC_PBC_PWSW_NONE_ACT_ID = 0,
	EN_DRV_STBC_PBC_PWSW_PRESSED_ACT_ID,
	EN_DRV_STBC_PBC_PWSW_FREED_ACT_ID,
	EN_DRV_STBC_PBC_PWSW_FREED_ID_NUM
}EN_DRV_STBC_PBC_PWSW_ACTION_ID;


/**
 * \brief
 * enumerate to indicate STBC gpio name.
 */
typedef enum
{
	EN_DRV_STBC_IO_GPE07 = 0,         /*!< 320s, 316 chip  */
	EN_DRV_STBC_IO_GPE08,
	EN_DRV_STBC_IO_GPE09,
	EN_DRV_STBC_IO_GPE10,
	EN_DRV_STBC_IO_GPE11,
	EN_DRV_STBC_IO_GPE12,
	EN_DRV_STBC_IO_GPE13,
	EN_DRV_STBC_IO_GPE14,
	EN_DRV_STBC_IO_GPE15,
	EN_DRV_STBC_IO_GPE16,
	EN_DRV_STBC_IO_GPE17,			
	EN_DRV_STBC_IO_GPE18,
	EN_DRV_STBC_IO_GPE19,             /*!< 316 chip  */

	EN_DRV_STBC_IO_PWEN = 0,          /*!< 310 chip  */
	EN_DRV_STBC_IO_PWSW,
	EN_DRV_STBC_IO_IR,
	EN_DRV_STBC_IO_GPIO1,
	EN_DRV_STBC_IO_GPIO2,
	EN_DRV_STBC_IO_CEC,
	EN_DRV_STBC_IO_HPD,

	EN_DRV_STBC_IO_NONE,
}EN_DRV_STBC_IO_BIT;

/*!
 * \brief
 *  GPIO PULL status
 */
typedef enum
{	
	EN_DRV_STBC_IO_PULL_STATUS_NORMAL,      
	EN_DRV_STBC_IO_PULL_STATUS_DOWN,        
	EN_DRV_STBC_IO_PULL_STATUS_UP,          
    EN_DRV_STBC_IO_PULL_STATUS_KEEPER,      /*!< 320 chip  */
	EN_DRV_STBC_IO_PULL_STATUS_NUM
}EN_DRV_STBC_IO_PULL_STATUS;

/*!
 * \brief
 *  GPIO driving current level.
 */
typedef enum
{	
	EN_DRV_STBC_IO_DRIVING_LEVEL0,     //! 320: 12mA, 316: 2.5mA 
	EN_DRV_STBC_IO_DRIVING_LEVEL1,     //! 320: ??mA, 316:   5mA       
	EN_DRV_STBC_IO_DRIVING_LEVEL2,     //! 320: ??mA, 316: 7.5mA       
	EN_DRV_STBC_IO_DRIVING_LEVEL3,     //! 320: ??mA, 316:  10mA       
	EN_DRV_STBC_IO_DRIVING_LEVEL_NUM
}EN_DRV_STBC_IO_DRIVING_LEVEL;

/**
 * \brief
 * enumerate to define GPIO multi-function.
 */

/*---------------------------------------*/
// Max multi-func Num:
// 310  : 0/1/2 (STBC IO/GPIO/STBC Multi-func)
// 320s : 0~3 (GPIO/Muli-func0/Muli-func1/....)
// 316s : 0~3 (GPIO/Muli-func0/Muli-func1/....)
/*---------------------------------------*/
/*!< Please refer datasheet to select the correct IO function.*/
typedef enum
{
    EN_DRV_STBC_IO_MULTI_FUNC_0 =  0,       
    EN_DRV_STBC_IO_MULTI_FUNC_1,     
    EN_DRV_STBC_IO_MULTI_FUNC_2,     
    EN_DRV_STBC_IO_MULTI_FUNC_3,     
    EN_DRV_STBC_IO_MULTI_FUNC_4,     
    EN_DRV_STBC_IO_MULTI_FUNC_5,     
    EN_DRV_STBC_IO_MULTI_FUNC_6,     
    EN_DRV_STBC_IO_MULTI_FUNC_7,     
    EN_DRV_STBC_IO_MULTI_FUNC_8,     
    EN_DRV_STBC_IO_MULTI_FUNC_MAX    
}EN_DRV_STBC_IO_MULTI_FUNC;

/**
 * \brief
 *  enumurate to indicate the power on or standby status when user presses power key.
 */
typedef enum
{
	EN_DRV_STBC_POWERON_ID = 0x0000000,

	// only use bit 8 ~ 15 for reset ID - Eric 20110427
    // so define enum as 0, 1, 2, 3, 4
    // The other bits are used for boot-code.
	EN_DRV_STBC_STANDYBY_ID,

	EN_DRV_STBC_STANDYBY_AND_DC_ID,
	EN_DRV_STBC_RUNNING_ID,
    EN_DRV_STBC_MMPLAY_ID,
    EN_DRV_STBC_RESET_ID_NUM
}EN_DRV_STBC_RESET_ID_TYPE;

/**
 * \brief
 *  enumurate to indicate the event type when user presses power key.
 */
typedef enum
{
   	EN_DRV_STBC_WAKEUP_EVENT_NO_EVENT   = (0x0000),
	EN_DRV_STBC_WAKEUP_EVENT_RTC        = (0x0001),
	EN_DRV_STBC_WAKEUP_EVENT_CEC        = (0x0002),
	EN_DRV_STBC_WAKEUP_EVENT_IR         = (0x0004),
	EN_DRV_STBC_WAKEUP_EVENT_PWSW       = (0x0008),
    EN_DRV_STBC_WAKEUP_EVENT_HPD        = (0x0010),
    EN_DRV_STBC_WAKEUP_EVENT_KEY        = (0x0020),         //VFD key event.
    EN_DRV_STBC_WAKEUP_EVENT_MASK       = (0x003f),
    EN_DRV_STBC_WAKEUP_EVENT_NUM        = 6,
}EN_DRV_STBC_WAKUP_EVENT_TYPE;

/*-----------------------------------------------------------------------------*/
/* Notify  */
/*-----------------------------------------------------------------------------*/
/**
 * \brief
 *  the STBC Notify function pointer
 */
typedef ErrorCode (*DRV_STBC_NOTIFY_FN)(u32 u32Handle, u32 u32Status);

/**
 * \brief
 *  the STBC INIT Notify function pointer
 */
typedef bool (*DRV_STBC_INTR_NOTIFY_FN)(u32 u32Vector, u32 u32Param0, u32 u32Param1);

/**
 * \brief
 *  the STBC INIT Notify function pointer
 */

// !!!!  This callback-func-point only are used in 320s platform.
typedef bool (*DRV_STBC_GPIO_INTR_NOTIFY_FN)(u32 u32Vector, u32 u32Param0, u32 u32Param1);

/*-----------------------------------------------------------------------------*/
/* Structure Definitions                                                                 */
/*-----------------------------------------------------------------------------*/

/*----------------*/
/* STBC IO module */
/*----------------*/
/**
 * \brief
 *  the STBC initialize structure
 */
typedef struct
{
    EN_DRV_STBC_IO_MULTI_FUNC               enIoFunc;          	/*!< GPIO / function select							*/
	bool									b8IsOutput;			/*!< IO direction									*/
	bool 									b8IoVal; 			/*!< STBC GPIO default output level 				*/
    EN_DRV_STBC_IO_PULL_STATUS              enPullStatus;       /*!< STBC GPIO pull-up/down parameter	            */
    EN_DRV_STBC_IO_DRIVING_LEVEL            enDrivingLevel;       /*!< STBC GPIO pull-up/down parameter	            */
} ST_DRV_STBC_IO_CONFIG, *PST_DRV_STBC_IO_CONFIG;

/**
 * \brief
 *  the STBC IO initialize structure
 */
typedef struct
{
    u32                                     u32PoolHandl;
	PST_DRV_STBC_IO_CONFIG 					pstGpioConfig;
    u32                                     u32ConfigBuffSize;
} ST_DRV_STBC_IO_INIT_PARAMS, *PST_DRV_STBC_IO_INIT_PARAMS;

/**
 * \brief
 *  the IO open structure
 */
typedef struct
{
	EN_DRV_STBC_IO_BIT 	    					enIOName;
} ST_DRV_STBC_IO_OPEN_PARAMS, *PST_DRV_STBC_IO_OPEN_PARAMS;



/*-----------------*/
/* STBC PBC module */
/*-----------------*/
/**
 * \brief
 *  STBC-PBC initialize structure
 */
typedef struct
{
	u32				u32SetRstDelay;			/*!< reset delay time								*/
	bool			b8PwEnIsHiActive;		/*!< PW_EN hi or lo active 							*/
	bool			b8PwEnInverse;			/*!< PWEN inverse record flag(display only)			*/

	bool 			b8PWSWIsRisingEdge;		/*!< Power Key active edge, please refer HW setting(PWSW only) */
	bool 			b8PWSWIsFallingEdge;	/*!< Power Key active edge, please refer HW setting(PWSW only) */
	bool 			b8HotPlugIsRisingEdge;	/*!< HDMI hot-plug active edge, please refer HW setting(HotPlug only) */
	bool 			b8HotPlugIsFallingEdge;	/*!< HDMI hot-plug active edge, please refer HW setting(HotPlug only) */

    bool            b8PwSwESDActive;        /*!< PWSW ESD protection enable */
    bool            b8PorESDActive;         /*!< POR ESD protection enable */
    u32             u32ESDCounter;          /*!< ESD protection counter */
} ST_DRV_STBC_PBC_INIT_PARAMS, *PST_DRV_STBC_PBC_INIT_PARAMS;


/**
 * \brief
 *  the PBC open structure
 */
typedef struct
{
    DRV_STBC_NOTIFY_FN						pfnNotifyFn;            /*!< PBC Control Notify function pointer 				*/
	EN_DRV_STBC_PBC_OPEN_TYPE 				enOpenType; 			/*!< User open a hot-plug or PWSW sub device 			*/
	u32										u32EvtHandle;			/*!< Event handle for PBC 								*/
    u32										u32EvtID;				/*!< Event ID for PBC 									*/
	EN_DRV_STBC_PBC_PWSW_ACTION_ID 			enFallingEdgeActID; 	/*!< Action status  									*/
	EN_DRV_STBC_PBC_PWSW_ACTION_ID			enRisingEdgeActID; 		/*!< Action status  									*/
	u32										u32KeyCode;				/*!< key code, this is a key function name enum   		*/
} ST_DRV_STBC_PBC_OPEN_PARAMS, *PST_DRV_STBC_PBC_OPEN_PARAMS;


/**
 * \brief
 *  the PBC configuration structure
 */
typedef struct
{
	u32						    u32KeyCode;				/*!< Power key code, ie:0x01, 0x02, 0x04, 0x08... 		*/
    bool                        b8PwSwESDActive;        /*!< PWSW ESD protection enable */
    bool                        b8PorESDActive;         /*!< POR ESD protection enable */
    u32                         u32ESDCounter;          /*!< ESD protection counter */
} ST_DRV_STBC_PBC_CONFIG_PARAMS, *PST_DRV_STBC_PBC_CONFIG_PARAMS;



/*-----------------------------------------------------------------------------*/
/* API Prototype Definitions  */
/*-----------------------------------------------------------------------------*/

/* STBC Common APIs */
ErrorCode DRV_STBC_Init (DRV_DeviceNameType DeviceName);

ErrorCode DRV_STBC_Load_8051_SRAM(void);                                                // 320s, 316 used
ErrorCode DRV_STBC_Enable_Reload(bool b8EnReload);
ErrorCode DRV_STBC_Set_SyncInfo(EN_DRV_STBC_SYNC_INFO_MODE enMode, u32 u32Sts);         // 320s, 316 used
ErrorCode DRV_STBC_Get_SyncInfo(EN_DRV_STBC_SYNC_INFO_MODE enMode, u32 *pu32Sts);       // 320s, 316 used
ErrorCode DRV_STBC_Get_KeyPass_Status (bool* pb8Status);                                // 320s, 316 used
ErrorCode DRV_STBC_Set_KeyPass_Status(bool b8Enable);                                   // 320s, 316 used

/* STBC get Wakeup event API */
ErrorCode DRV_STBC_Get_WakeupEvent(EN_DRV_STBC_WAKUP_EVENT_TYPE* penWakeupEvent);       // 310 only
ErrorCode DRV_STBC_Clear_WakeupEvent(EN_DRV_STBC_WAKUP_EVENT_TYPE enWakeupEvent);       // 310 only

ErrorCode DRV_STBC_GetResetType (EN_DRV_STBC_RESET_ID_TYPE* penResetIdType);
ErrorCode DRV_STBC_SetResetType (EN_DRV_STBC_RESET_ID_TYPE enResetIdType);

/* STBC IO Ctrl APIs */
ErrorCode DRV_STBC_IO_Init (DRV_DeviceNameType DeviceName,PST_DRV_STBC_IO_INIT_PARAMS pstInit);
ErrorCode DRV_STBC_IO_Open (DRV_DeviceNameType DeviceName,PST_DRV_STBC_IO_OPEN_PARAMS pstOpen, u32* pu32Handle);
ErrorCode DRV_STBC_IO_Close (u32* pu32Handle);
ErrorCode DRV_STBC_IO_Read (u32 u32Handle,  u8* pu8Value);
ErrorCode DRV_STBC_IO_Write (u32 u32Handle, u8 u8Value);
ErrorCode DRV_STBC_IO_SetDrivingLevel (u32 u32Handle, EN_DRV_STBC_IO_BIT enIoBit, EN_DRV_STBC_IO_DRIVING_LEVEL enDrivingLevel);
ErrorCode DRV_STBC_IO_SetBitDirection (u32 u32Handle, bool b8IsOutput);
ErrorCode DRV_STBC_IO_SetBitPULL (u32 u32Handle, EN_DRV_STBC_IO_PULL_STATUS enPullStatus);
ErrorCode DRV_STBC_IO_GetBitPULL (u32 u32Handle, EN_DRV_STBC_IO_PULL_STATUS* penPullStatus);
ErrorCode DRV_STBC_IO_SetConfig (u32 u32Handle, PST_DRV_STBC_IO_CONFIG pstConfig);
ErrorCode DRV_STBC_IO_GetConfig (u32 u32Handle, PST_DRV_STBC_IO_CONFIG pstConfig);
ErrorCode DRV_STBC_IO_Term (DRV_DeviceNameType DeviceName);

/* STBC I/O register/remove interrupt routine API*/
ErrorCode DRV_STBC_IO_INTR_Register(u32 u32Vector, DRV_STBC_GPIO_INTR_NOTIFY_FN pfnNotify);         // 320s, 316 used
ErrorCode DRV_STBC_IO_INTR_Unrgister(u32 u32Vector);                                                // 320s, 316 used
ErrorCode DRV_STBC_IO_INTR_Enable(u32 u32Vector, bool b8Enable);

/* STBC PBC Ctrl API */
ErrorCode DRV_STBC_PBC_Init (DRV_DeviceNameType DeviceName, PST_DRV_STBC_PBC_INIT_PARAMS pstInit);
ErrorCode DRV_STBC_PBC_Term (DRV_DeviceNameType DeviceName);
ErrorCode DRV_STBC_PBC_Open (DRV_DeviceNameType DeviceName, PST_DRV_STBC_PBC_OPEN_PARAMS pstOpen, u32* pu32Handle);
ErrorCode DRV_STBC_PBC_Close (u32* pu32Handle);
ErrorCode DRV_STBC_PBC_Enable (u32 u32Handle, bool b8Enable);
ErrorCode DRV_STBC_PBC_SetConfig (u32 u32Handle, PST_DRV_STBC_PBC_CONFIG_PARAMS pstConfig);
ErrorCode DRV_STBC_PBC_GetConfig (u32 u32Handle, PST_DRV_STBC_PBC_CONFIG_PARAMS pstConfig);
ErrorCode DRV_STBC_PBC_GetActionID (u32 u32KeyCode, EN_DRV_STBC_PBC_PWSW_ACTION_ID* penActID);

/* MIPS power off API */
ErrorCode DRV_STBC_Cutoff_Power (void);                             // 310 only

/* STBC ESD Ctrl API */
ErrorCode DRV_STBC_ESD_SetProtection (bool b8Enable);               // 320s, 316 used
ErrorCode DRV_STBC_ESD_SetDebounceCounter (u16 u16CounterVal);      // 320s, 316 used
ErrorCode DRV_STBC_PWSW_ESD_SetProtection (bool b8Enable);          // 320s, 316 used
ErrorCode DRV_STBC_WriteReg (u32 u32ADR, u32 u32Val);
void DRV_STBC_ESD_DumpParameter (void);                             // 320s, 316 used

u8* DRV_STBC_GetVersion (void);

void DRV_STBC_DebugCmd(u32 u32Param1, u32 u32Param2, u32 u32Param3);
#endif /* __DRV_STBC_H__ */


