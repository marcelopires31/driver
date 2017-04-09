#ifndef _DRV_DEBUG_H_
#define _DRV_DEBUG_H_

#include "def_type.h"
#include "def_err.h"
#include "def_dbg.h"
#include "os.h"

#define TRACE_ERROR

#if (DEBUG_VERSION==1)
#define MODE DEBUG
#define ENABLE_ERROR_TRACE (0)
#else /* #if (DEBUG_VERSION==1) */
#define MODE RELEASE
#ifdef TRACE_ERROR
#define ENABLE_ERROR_TRACE (1)
#else /* TRACE_ERROR */
#define ENABLE_ERROR_TRACE (0)
#endif /* TRACE_ERROR */
#endif /* #if (DEBUG_VERSION==1) */


#define ENABLE_DEBUG (1)
#define ENABLE_RELEASE (0)

#define DBG_MACRO_START do {
#define DBG_MACRO_END   } while (0)

//#define SUPPORT_PROC2_DBG
//#define SUPPORT_TIMER_DBG

//#define REG_AIU_BASE                (0xB4006100L)
//#define REG_AIU_GR(addr)            (*(volatile u32 *)(REG_AIU_BASE+0x454L+((u8)(addr)<<2)))

/********************************************************/
#define DRV_DBG_TASK_PRIORITY (24)
#define DRV_DBG_MAX_ArgvLength (32)
#define DEBUG_MAX_ARGV_LENGTH (32)


#define DRV_DBG_DRAM_BUF_SIZE   	(64 * 1024)
#ifdef SUPPORT_PROC2_DBG
#define REG_DBG_R_IDX		(*((vu32 *) (0xb40065bc)))
#define REG_DBG_W_IDX		(*((vu32 *) (0xb40065c0)))
#endif
#define DBG_CHAR_LENGTH     (90)
#define DBG_INFO_NULL		(0x00L)
#define REG_PLAT_TIMER3_VALUE 	(*((vu32 *) (0xb40000c0 + 0x2c)))

#define FG(color)	((EN_DBG_CO_FG|color)<<8)
#define BG(color)	(EN_DBG_CO_BG|color)

typedef enum {
	EN_DBG_CO_BLACK    =0,
	EN_DBG_CO_RED      =1,
	EN_DBG_CO_GREEN    =2,
	EN_DBG_CO_YELLOW   =3,
	EN_DBG_CO_BLUE     =4,
	EN_DBG_CO_MAGENTA  =5,
	EN_DBG_CO_CYAN     =6,
	EN_DBG_CO_WHITE    =7,
	EN_DBG_CO_ALL      =8,
	EN_DBG_CO_FG       =30,
	EN_DBG_CO_BG       =40,
}EN_DBG_COLOR;
/********************************************************/
typedef void (*DBG_CALLBACK)(void* a, void* b, void* c, void* d,void* e);
typedef void (*DBG_CALLBACKPTR)(char * a, char * b, char * c, char * d);   // ADD: for char parameter. 

/********************************************************/
/**
 * \brief
 * Enumerate to indicate the debug message level
 */
typedef enum {
    EN_DL_NONE = 0,
    EN_DL_ERROR,	/* error level */
    EN_DL_WARNING,	/* warning level */
    EN_DL_INFO,		/* information level */
    EN_DL_VERBOSE,	/* verbose level */
    EN_DL_TRACE,	/* trace level */
    EN_DL_ALL
}EN_DBG_LEVEL;

/**
 * \brief
 * Enumerate to indicate the statistics level for memory watch
 */
typedef enum {
	EN_GLOBAL = 0,	/* global mode */
	EN_MODULE,		/* module mode */
	EN_DETAIL		/* detail mode */
}EN_DBG_STAT_LEVEL;

/**
 * \brief
 * Enumerate to indicate the debug command type
 */
typedef enum {
	EN_DT_NORMAL = 0,	/* in normal mode */
	EN_DT_DSR,			/* in DSR mode */
	EN_DT_NUM
}EN_DBG_TYPE;


/**
 * \brief
 * Enumerate to indicate the debug operation error
 */
enum
{
	ERROR_DBG_ERR_TERMINATE  = ERROR_BASE_DRV_DBG,	/* error of terminate */
	ERROR_DBG_ERR_TASK,							/* error of task */
	ERROR_DBG_ERR_SEMAPHORE,						/* error of semaphore */
	ERROR_DBG_ERR_INITIAL,							/* error of initial */
	ERROR_DBG_ERR_UN_INITIAL,						/* error of un-initial */
	ERROR_DBG_ERR_PARSE_CMD,						/* error of parser */
	ERROR_DBG_ERR_EXEC_CMD,						/* error of execute command */
	ERROR_DBG_ERR_MSG								/* error of dump message */
};

/**
 * \brief
 *  Structure of DBG Initial Parameter
 */
typedef struct
{
	os_mempool_handle	u32MemHandle;				/*!< A memory pool handle for DBG module	*/
	DRV_DeviceNameType	UARTDeviceName;
	DRV_DeviceNameType	EVTDeviceName;
}ST_DBG_Init, *PST_DBG_Init;


/**
 * \brief
 *  Structure of DBG Message Parameter
 */
typedef struct  tagDBG_INFO
{
    u32   dwTickTime;
    u32	  u32Line;
    EN_DBG_MODULE enType;
    EN_DBG_LEVEL enLevel;
    u8    bSize;
    u8    bData[DBG_CHAR_LENGTH];
    u8	  *pu8Func;
    u8    *pu8File;
} DBG_INFO, *PDBG_INFO;

/********************************************************/
extern EN_DBG_LEVEL dbg_bank[];
extern void DRV_DBG_Set_ModuleLevel(EN_DBG_MODULE enType, EN_DBG_LEVEL enLevel);
extern EN_DBG_LEVEL DRV_DBG_Get_ModuleLevel(EN_DBG_MODULE enType);
extern bool DBG_Printf(EN_DBG_MODULE enType, EN_DBG_LEVEL enLevel, u32 u32Line, const u8 *pu8Func, const u8 *pu8File, u8 *fmt, ...);

/********************************************************/
/* DBG_E */
#define DBG_E(type, message, args...) \
DBG_MACRO_START \
	if ((EN_DL_ERROR) <= dbg_bank[(u32)(type)]) \
	{ \
		DBG_Printf(type, EN_DL_ERROR, __LINE__, __FUNCTION__, __FILE__, message, ##args); \
	} \
DBG_MACRO_END
/* DBG_W */
#define DBG_W(type, message, args...) \
DBG_MACRO_START \
	if ((EN_DL_WARNING) <= dbg_bank[(u32)(type)]) \
	{ \
		DBG_Printf(type, EN_DL_WARNING, __LINE__, __FUNCTION__, __FILE__, message, ##args); \
	} \
DBG_MACRO_END
/* DBG_I */
#define DBG_I(type, message, args...) \
DBG_MACRO_START \
	if ((EN_DL_INFO) <= dbg_bank[(u32)(type)]) \
	{ \
		DBG_Printf(type, EN_DL_INFO, __LINE__, __FUNCTION__, __FILE__, message, ##args); \
	} \
DBG_MACRO_END
/* DBG_V */
#define DBG_V(type, message, args...) \
DBG_MACRO_START \
	if ((EN_DL_VERBOSE) <= dbg_bank[(u32)(type)]) \
	{ \
		DBG_Printf(type, EN_DL_VERBOSE, __LINE__, __FUNCTION__, __FILE__, message, ##args); \
	} \
DBG_MACRO_END
/* DBG_T */
#define DBG_T(type, message, args...) \
DBG_MACRO_START \
	if ((EN_DL_TRACE) <= dbg_bank[(u32)(type)]) \
	{ \
		DBG_Printf(type, EN_DL_TRACE, __LINE__, __FUNCTION__, __FILE__, message, ##args); \
	} \
DBG_MACRO_END


#define dbg_e(type, message, args...) { \
	if(DEBUG_VERSION==1) \
	{ \
		 DBG_E(type, message, ##args); \
	} \
	else \
	{ \
		if(ENABLE_ERROR_TRACE) \
		{ \
			DBG_E(type, message, ##args); \
		} \
	} \
 }
#define dbg_w(type, message, args...) {if(DEBUG_VERSION==1) DBG_W(type, message, ##args); }
#define dbg_i(type, message, args...) {if(DEBUG_VERSION==1) DBG_I(type, message, ##args); }
#define dbg_v(type, message, args...) {if(DEBUG_VERSION==1) DBG_V(type, message, ##args); }
#define dbg_t(type, message, args...) {if(DEBUG_VERSION==1) DBG_T(type, message, ##args); }


#define DBG_MSG(type, level, message, args...) \
DBG_MACRO_START \
	if ((EN_DL_ERROR) == level) \
	{ \
		dbg_e(type, message, ##args); \
	} \
	if ((EN_DL_WARNING) == level) \
	{ \
		dbg_w(type, message, ##args); \
	} \
	if ((EN_DL_INFO) == level) \
	{ \
		dbg_i(type, message, ##args); \
	} \
	if ((EN_DL_VERBOSE) == level) \
	{ \
		dbg_v(type, message, ##args); \
	} \
	if ((EN_DL_TRACE) == level) \
	{ \
		dbg_t(type, message, ##args); \
	} \
DBG_MACRO_END
/*! \fn DBG_MSG(type, level, message, args...)
	\brief
 *		dump the debug message according to module type and dispaly level.
 *
 * \param type		(Input) the module type (type is EN_DBG_MODULE)
 * \param level		(Input) the display level (level is EN_DBG_LEVEL)
 * \param message	(Input) the debug messages
 * \param args...	(Input) the arguments of debug messages
 *
 * \return DBG Operation Error Code
 * \retval ERROR_NO_ERROR			Initial success
 * \retval ERROR_NO_MEMORY
 * \retval EN_DRV_DBG_ERR_MSG
 */


#define DBG_REPORT() REPORT()
/*! \fn DBG_REPORT()
	\brief
 *		dump the error level message.
 *
 * \param None
 *
 * \return None
 */

#define DBG_SET_MODULE_LEVEL(type, level) DRV_DBG_Set_ModuleLevel(type, level)
/*! \fn DBG_SET_MODULE_LEVEL(type, level)
	\brief
 *		set the display level for debug message.
 *
 * \param type (Input) the module type (type is EN_DBG_MODULE)
 * \param level (Input) the display level (type is EN_DBG_LEVEL)
 *
 * \return None
 */

#define DBG_GET_MODULE_LEVEL(type) DRV_DBG_Get_ModuleLevel(type)
/*! \fn DBG_GET_MODULE_LEVEL(type)
	\brief
 *		get the display level according to module type.
 *
 * \param type (Input) the module type (type is EN_DBG_MODULE)
 *
 * \return display level (type is EN_DBG_LEVEL)
 */

u8* DRV_DBG_GetVersion (void);
/*!\fn u8* DRV_DBG_GetVersion (void)
 * \brief
 *		Get the Version number string of DBG
 *
 * \return DBG Version String of DEBUG
 *
 */

ErrorCode DRV_DBG_Initialize(PST_DBG_Init pstInit);
/*! \fn ErrorCode DRV_DBG_Initialize(PST_DBG_Init pstInit)
	\brief
 *		initialize the DEBUG module.
 *
 * \param pstInit	(Input) Pointer of initial parameter
 *
 * \return DBG Operation Error Code
 * \retval ERROR_NO_ERROR			Initial success
 * \retval ERROR_INITIALISED		The driver is already initialized.
 * \retval EN_DRV_DBG_ERR_TASK		Create task fail
 * \retval EN_DRV_DBG_ERR_SEMAPHORE	Create semaphore fail
 * \retval EN_DRV_DBG_ERR_INITIAL	Initial fail
 */


ErrorCode DRV_DBG_RegisterCMD(u8 *pu8CmdName, EN_DBG_TYPE enType, DBG_CALLBACK pfnCallback, u8 *pu8Brief, u8 *pu8Arg);
/*! \fn ErrorCode DRV_DBG_RegisterCMD(u8 *pu8CmdName, EN_DBG_TYPE enType, DBG_CALLBACK pfnCallback, u8 *pu8Brief, u8 *pu8Arg);
	\brief
 *		Register the DEBUG command.
 *
 * \param pu8CmdName (Input) The command name of debug command.
 * \param enType (Input) The command type of debug command.
 * \param pfnCallback (Input) A pointer to the user defined function that will be called when a debug command be notified.
 * \param pu8Brief (Input) The description of debug command.
 * \param pu8Arg (Input) The description of argument.
 *
 * \return DBG Operation Error Code
 * \retval ERROR_NO_ERROR			Register command success
 * \retval ERROR_BAD_PARAMETER		The parameter is error
 */


ErrorCode DRV_DBG_UnregisterCMD(u8 *pu8CmdName);
/*! \fn ErrorCode DRV_DBG_UnregisterCMD(u8 *pu8CmdName);
	\brief
 *		Unregister the DEBUG command.
 *
 * \param pu8CmdName (Input) The command name of debug command.
 *
 * \return DBG Operation Error Code
 * \retval ERROR_NO_ERROR			Register command success
 * \retval ERROR_BAD_PARAMETER		The parameter is error
 */


ErrorCode DRV_DBG_Help(u8 *pu8CmdName);
/*! \fn ErrorCode DRV_DBG_Help(u8 *pu8CmdName);
	\brief
 *		Dump the information of DEBUG command according to command name.
 *
 * \param pu8CmdName (Input) The command name of debug command.
 *
 * \return DBG Operation Error Code
 * \retval ERROR_NO_ERROR			Register command success
 * \retval ERROR_BAD_PARAMETER		The parameter is error
 */


void DRV_DBG_SetMsgType(EN_DBG_TYPE enType);
/*! \fn void DRV_DBG_SetMsgType(EN_DBG_TYPE enType)
	\brief
 *		set the debug message type.
 *
 * \param enType (Input) the debug message type
 *
 * \return None
 */


EN_DBG_TYPE DRV_DBG_GetMsgType(void);
/*! \fn EN_DBG_TYPE DRV_DBG_GetMsgType(void)
	\brief
 *		get the debug message type.
 *
 * \param None
 *
 * \return debug message type
 * \retval EN_DT_NORMAL			In normal case
 * \retval EN_DT_DSR			In DSR case
 */


ErrorCode DRV_DBG_Terminate(void);
/*! \fn ErrorCode DRV_DBG_Terminate(void);
	\brief
 *		Terminate the DEBUG module.
 *
 * \param none
 *
 * \return DBG Operation Error Code
 * \retval ERROR_NO_ERROR			Terminate success
 * \retval EN_DRV_DBG_ERR_TERMINATE	Terminate fail
 */


u8* DRV_DBG_GetRevision (void);
/*!\fn u8* DRV_DBG_GetRevision (void)
 *
 * \brief
 * 		Get the Module Version number of DEBUG
 *
 * \param None
 *
 * \return	Return the version info of DEBUG
 */

ErrorCode DRV_DBG_RstDRAMDbgMsg(void);
/*! \fn ErrorCode DRV_DBG_RstDRAMDbgMsg(void);
	\brief
 *		This function will reset the debugging message in DRAM.
 *
 * \param None.
 *
 * \return DBG Operation Error Code
 * \retval ERROR_NO_ERROR			Reset the debugging message success in DRAM
 * \retval ERROR_BAD_PARAMETER		The parameter is error
 */

void DRV_DBG_DirectDumpMsg (const char *fmt, ...);

/********************************************************
			OS debug command related
********************************************************/
void OSDBG_TaskInfo(bool b8PrioritySort);
void OSDBG_HISRInfo(void);
void OSDBG_DumpPCStackByTaskId(u32 u32TaskID,u32 u32Num, u32 u32Var3);
void OSDBG_MonitorTimerCreate (void);
void OSDBG_MonitorTimerDelete (void);
void OSDBG_SetPriority (u32 u32TaskID, u32 u32Priority, u32 u32Var3);
void OSDBG_MemoryPoolInfo(EN_OS_MEM_BLK_LIST_MODE enMode, u32 u32MemPoolHandle);
void OSDBG_HeapInfo(void);
void OSDBG_StackInfo(void);
ErrorCode DRV_DBG_ExecuteCmd(u8 *pu8ExeArgv);

void OSDBG_DumpCurrentTaskPCStack(u32 u32Num);
#endif /* _DRV_DEBUG_H_ */
