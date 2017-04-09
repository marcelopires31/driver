//**************************************************************************
//			Copyright (c) , Inc . All rights reserved.
//			STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date	: 
//	Author	: 
//	Purpose	: Provide System high level API
//	Sources	: 
//**************************************************************************
//
//	Modification use :
//**************************************************************************
//	Update
//
//	Date		: 
//	Name		: 
//	Description	: 
//
//	Item											Source
//	----------------------------------------		-------------------

#ifndef __DRV_SYS_H__
#define __DRV_SYS_H__

/*-----------------------------------------------------------------------------*/
/* Including Files                                                             */
/*-----------------------------------------------------------------------------*/
#include "def_type.h"
#include "def_err.h"
#include "os.h"
#include "drv_config.h"
#include "sen5_sw_config.h"	//add by wujiang


/*-----------------------------------------------------------------------------*/
/* Constant Definitions                                                        */
/*-----------------------------------------------------------------------------*/
/**
 * \brief
 * enumurate to indicate the error of system
 */
enum
{
	ERROR_DRV_SYS_SEMAPHORE = ERROR_BASE_DRV_SYS,	/*!< No semaphore							*/
	ERROR_DRV_SYS_TIMER_TYPE,						/*!< Timer type is wrong					*/
	ERROR_DRV_SYS_TIMER_HANDLE_NOT_CLOSED,
	ERROR_DRV_SYS_UNKNOW_DEVICE,
	ERROR_DRV_SYS_OUT_OF_RANGE,
	ERROR_DRV_SYS_UNZIP_FAIL,
	ERROR_DRV_SYS_OTHERS,							/*!< Other error							*/
	ERROR_DRV_SYS_TOTAL,
};

/**
 * \brief
 * enumurate to indicate the type of PORC
 */
typedef enum
{
	EN_DRV_SYS_PROC_TYPE_PROC1,
	EN_DRV_SYS_PROC_TYPE_PROC2,
	EN_DRV_SYS_PROC_TYPE_TOTAL
} EN_DRV_SYS_PROC_TYPE;

/**
 * \brief
 * enumurate to indicate the type of PLL
 */
typedef enum
{
	// Ratio
	EN_DRV_SYS_PLL_TYPE_EPLL,
	EN_DRV_SYS_PLL_TYPE_MPLL,
	EN_DRV_SYS_PLL_TYPE_VCXO_PLL,
	EN_DRV_SYS_PLL_TYPE_BPLL,
	EN_DRV_SYS_PLL_TYPE_UPLL,

	EN_DRV_SYS_PLL_TYPE_AXIPLL,
	EN_DRV_SYS_PLL_TYPE_DDRPLL,
	EN_DRV_SYS_PLL_TYPE_DSPPLL,
	EN_DRV_SYS_PLL_TYPE_DFEPLL,
	EN_DRV_SYS_PLL_TYPE_QPLL,
	
	// M, N
	EN_DRV_SYS_PLL_TYPE_APLL,
	EN_DRV_SYS_PLL_TYPE_VPLL,
	// F, I
	EN_DRV_SYS_PLL_TYPE_QSPLL,
	EN_DRV_SYS_PLL_TYPE_AHB,
	// Total
	EN_DRV_SYS_PLL_TYPE_TOTAL,
} EN_DRV_SYS_PLL_TYPE;

/**
 * \brief
 * enumurate to indicate the source of mclk
 */
typedef enum
{
	EN_DRV_SYS_MCLK_SOURCE_TYPE_OSCI,
	EN_DRV_SYS_MCLK_SOURCE_TYPE_MPLL,
	EN_DRV_SYS_MCLK_SOURCE_TYPE_TOTAL
} EN_DRV_SYS_MCLK_SOURCE_TYPE;

/**
 * \brief
 * enumurate to indicate the ratio of mclk and PROC
 */
typedef enum
{
	EN_DRV_SYS_MCLK_PROC_RATIO_TYPE_1_5,	// 1.5 : 1
	EN_DRV_SYS_MCLK_PROC_RATIO_TYPE_3,		// 3 : 1
	EN_DRV_SYS_MCLK_PROC_RATIO_TYPE_TOTAL
} EN_DRV_SYS_MCLK_PROC_RATIO_TYPE;

/**
 * \brief
 * enumurate to indicate the DIV of mclk power save
 */
typedef enum
{
	EN_DRV_SYS_MCLK_POWER_SAVE_TYPE_DIV_2,
	EN_DRV_SYS_MCLK_POWER_SAVE_TYPE_DIV_4,
	EN_DRV_SYS_MCLK_POWER_SAVE_TYPE_DIV_16,
	EN_DRV_SYS_MCLK_POWER_SAVE_TYPE_DIV_64,
	EN_DRV_SYS_MCLK_POWER_SAVE_TYPE_DIV_TOTAL
} EN_DRV_SYS_MCLK_POWER_SAVE_TYPE;

/**
 * \brief
 * enumurate to indicate the PLL frequency value
 */
typedef enum
{
	EN_DRV_SYS_PLL_FREQUENCY_VALUE_TYPE_CLOSE,
	EN_DRV_SYS_PLL_FREQUENCY_VALUE_TYPE_UP,
	EN_DRV_SYS_PLL_FREQUENCY_VALUE_TYPE_DOWN,
	EN_DRV_SYS_PLL_FREQUENCY_VALUE_TYPE_TOTAL
} EN_DRV_SYS_PLL_FREQUENCY_VALUE_TYPE;

/**
 * \brief
 * enumurate to indicate the type of timer
 */
typedef enum
{
	EN_DRV_SYS_TIMER_TYPE_1,
	EN_DRV_SYS_TIMER_TYPE_2,
	EN_DRV_SYS_TIMER_TYPE_3,						/*!< 90KHz, 33bits, counter is increased	*/
	EN_DRV_SYS_TIMER_TYPE_4,						/*!< 90KHz, 33bits, counter is increased	*/
	EN_DRV_SYS_TIMER_TYPE_5,
	EN_DRV_SYS_TIMER_TYPE_TOTAL
} EN_DRV_SYS_TIMER_TYPE;

/**
 * \brief
 * enumurate to indicate the clock soure of timer
 */
typedef enum
{
	EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE_VCXO=0,
	EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE_APB=0,
	EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE_OSCI,
	EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE_TOTAL
} EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE;

/**
 * \brief
 * enumurate to indicate the clock soure of timer
 */
typedef enum
{
	EN_DRV_SYS_CHIP_VERSION_A_AND_B = 0x0,		//310 Version AB
	EN_DRV_SYS_CHIP_VERSION_C,				//310 Version C
	EN_DRV_SYS_CHIP_VERSION_D,				//310 Version D
	EN_DRV_SYS_CHIP_VERSION_E,				//310 Version E
	EN_DRV_SYS_CHIP_VERSION_ERROR = 0xff
} EN_DRV_SYS_CHIP_VERSION;

typedef enum
{
	EN_DRV_SYS_320_CHIP_VERSION_A = 0x0,		//320 Version A
	EN_DRV_SYS_320_CHIP_VERSION_B,				//320 Version B
	EN_DRV_SYS_320_CHIP_VERSION_ERROR = 0xff
} EN_DRV_SYS_320_CHIP_VERSION;


// Eric20110921, new add to judge TC78320 (test chip) and NT78320 (main chip)
typedef enum
{
    EN_DRV_SYS_CHIP_ID_TC78310_MAIN_CHIP = 0x0,            //310 main chip
	EN_DRV_SYS_CHIP_ID_TC78320_TEST_CHIP,                  //320 test chip
	EN_DRV_SYS_CHIP_ID_NT78320_MAIN_CHIP,                  //320 main chip
	EN_DRV_SYS_CHIP_ID_NT78316_MAIN_CHIP,                  //316 main chip
	EN_DRV_SYS_CHIP_ID_ERROR = 0xff
} EN_DRV_SYS_CHIP_ID;


/**
 * \brief
 * enumurate to indicate the clock soure of timer
 */
typedef enum
{
	EN_DRV_SYS_MEM_PARTITION_APU,
	EN_DRV_SYS_MEM_PARTITION_VDEC,
	EN_DRV_SYS_MEM_PARTITION_ESD,
	EN_DRV_SYS_MEM_PARTITION_DEBUG,
	EN_DRV_SYS_MEM_PARTITION_ERROR = 0xff,
} EN_DRV_SYS_MEM_PARTITION;



/**
 * \brief
 * enumurate to indicate the SSC (spread spectrum clock) modulation freq.
 */
typedef enum
{
	EN_DRV_SYS_PLL_SSC_FREQ_23P4KHZ,
	EN_DRV_SYS_PLL_SSC_FREQ_46P8KHZ,
	EN_DRV_SYS_PLL_SSC_FREQ_93P75KHZ,
	EN_DRV_SYS_PLL_SSC_FREQ_187P5KHZ,
	EN_DRV_SYS_PLL_SSC_FREQ_NUM,	
} EN_DRV_SYS_PLL_SSC_FREQ;

/**
 * \brief
 * enumurate to indicate the SSC (spread spectrum clock) range (ratio, %)
 */
typedef enum
{
	EN_DRV_SYS_PLL_SSC_RATIO_0,
	EN_DRV_SYS_PLL_SSC_RATIO_1,
	EN_DRV_SYS_PLL_SSC_RATIO_2,
	EN_DRV_SYS_PLL_SSC_RATIO_3,
	EN_DRV_SYS_PLL_SSC_RATIO_4,
	EN_DRV_SYS_PLL_SSC_RATIO_5,
	EN_DRV_SYS_PLL_SSC_RATIO_6,
	EN_DRV_SYS_PLL_SSC_RATIO_7,
	EN_DRV_SYS_PLL_SSC_RATIO_8,
	EN_DRV_SYS_PLL_SSC_RATIO_9,
	EN_DRV_SYS_PLL_SSC_RATIO_NUM,
	
} EN_DRV_SYS_PLL_SSC_RATIO;


/**
 * \brief
 * enumurate to indicate the SSC (spread spectrum clock) mode (normal spread, down spread
 */
typedef enum
{
	EN_DRV_SYS_PLL_SSC_NORMAL_SPREAD,
	EN_DRV_SYS_PLL_SSC_DOWN_SPREAD,	
	EN_DRV_SYS_PLL_SSC_SPREAD_NUM,	
} EN_DRV_SYS_PLL_SSC_MODE;




/*-----------------------------------------------------------------------------*/
/* Types Declarations                                                          */
/*-----------------------------------------------------------------------------*/
/**
 * \brief
 *  the SYS initial structure
 */
typedef struct
{
	os_mempool_handle	u32MemPoolHandle;			/*!< A memory pool handle for sys module (Ro unzip)	*/
} ST_DRV_SYS_INIT_PARAMS;

/**
 * \brief
 *  the SYS terminate structure
 */
typedef struct
{
	bool	b8Force;
} ST_DRV_SYS_TERM_PARAMS;

/**
 * \brief
 *  the Timer initial structure
 */
typedef struct
{
	os_mempool_handle	u32MemPoolHandle;
	EN_DRV_SYS_TIMER_TYPE	enTimerType;
} ST_SYS_TIMER_INIT_PARAMS, *PST_SYS_TIMER_INIT_PARAMS;

/**
 * \brief
 *  the Timer terminate structure
 */
typedef struct
{
	bool	b8Force;
} ST_SYS_TIMER_TERM_PARAMS;

typedef void (*DRV_TIMER_CALLBACK) (EN_DRV_SYS_TIMER_TYPE	enTimerType);

/**
 * \brief
 *  the Timer open structure
 */
typedef struct
{
	EN_DRV_SYS_TIMER_TYPE	enTimerType;
	DRV_TIMER_CALLBACK	pfn_Timer_cb;
	bool bReload;
} ST_SYS_TIMER_OPEN_PARAMS;

/**
 * \brief
 *  the Timer Pre-Scaler structure
 */
typedef struct
{
	bool	b8Set;
	bool	b8EnableBit;
	bool	b8ReloadBit;
	bool	b8LoadBit;
	u32		u32Count;
	u32		u32Reload;
} ST_DRV_SYS_TIMER_PER_SCALER_TIMER;

/**
 * \brief
 *  the Timer Fixed-Frequency structure
 */
typedef struct
{
	bool	b8Set;
	bool	b8MSBBit;
	bool	b8EnableBit;
	bool	b8ClockBit;
	u32		u32Value;
} ST_DRV_SYS_TIMER_FIXED_FREQ_TIMER;

/**
 * \brief
 *  the Timer config structure
 */
typedef struct
{
	EN_DRV_SYS_TIMER_TYPE					enTimerType;
	union
	{
		ST_DRV_SYS_TIMER_PER_SCALER_TIMER	stPreScalerTimer;
		ST_DRV_SYS_TIMER_FIXED_FREQ_TIMER	stFixedFreqTimer;
	} unConfig;
} ST_DRV_SYS_TIMER_CFG_PARAMS;

/**
 * \brief
 *  the PLL SSC control structure
 */
typedef struct
{
	bool 						b8SSCEnable;
	EN_DRV_SYS_PLL_SSC_FREQ		enSSCFreq;
	EN_DRV_SYS_PLL_SSC_RATIO	enSSCRatio;
	EN_DRV_SYS_PLL_SSC_MODE		enSSCMode;  
	u32 u32MauFreq;
} ST_PLL_SSC_CTRL, *PST_PLL_SSC_CTRL;

/**
 * \brief
 *  the PLL SSC config params structure
 */
//typedef struct
//{
//	ST_PLL_SSC_CTRL	stMPLLSSC;
//	ST_PLL_SSC_CTRL	stBPLLSSC;
//} ST_DRV_SYS_PLL_SSC_CFG_PARAMS, *PST_DRV_SYS_PLL_SSC_CFG_PARAMS;

/*-----------------------------------------------------------------------------*/
/* Extern Global Variables                                                     */
/*-----------------------------------------------------------------------------*/
// DON'T export global variable here. Please use function to access them
bool DRV_SYS_IsCacheAddress(u32) __attribute__((weak));
u32	DRV_SYS_CachedAddress(u32) __attribute__((weak));
u32 DRV_SYS_NonCachedAddress(u32) __attribute__((weak));

inline bool DRV_SYS_IsCacheAddress(u32 u32Address)
{
	return !(u32Address & 0x20000000);
}

inline u32	DRV_SYS_CachedAddress(u32 u32Address)
{
	return (u32Address & ~(0x20000000));
}

inline u32 DRV_SYS_NonCachedAddress(u32 u32Address)
{
	return (u32Address | (0x20000000));
}


/*-----------------------------------------------------------------------------*/
/* Interface Function Prototype                                                */
/*-----------------------------------------------------------------------------*/
ErrorCode DRV_SYS_Initialize(DRV_DeviceNameType DeviceName, ST_DRV_SYS_INIT_PARAMS *pstInitParams);
/*!\fn ErrorCode DRV_SYS_Initialize(DRV_DeviceNameType DeviceName, ST_DRV_SYS_INIT_PARAMS *pstInitParams)
 * \brief 
 * 		Initial Semaphore, CPU frequency, Timer for System
 * 
 * \param DeviceName					(Input)  Device name
 * \param pstInitParams					(Input)  Initial parameter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INITIALISED			A previous Init call has not been terminated
 * 
 */

ErrorCode DRV_SYS_Terminate(DRV_DeviceNameType DeviceName, ST_DRV_SYS_TERM_PARAMS *pstTermParams);
/*!\fn ErrorCode DRV_SYS_Terminate(DRV_DeviceNameType DeviceName, ST_DRV_SYS_TERM_PARAMS *pstTermParams)
 * \brief 
 * 		Terminate Semaphore, CPU frequency, Timer for System
 * 
 * \param DeviceName					(Input)  Device name
 * \param pstTermParams					(Input)  Terminate parameter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_CPU_GetFrequency(EN_DRV_SYS_PROC_TYPE enProcType, u32 *pu32Frequency);
/*!\fn ErrorCode DRV_SYS_CPU_GetFrequency(EN_DRV_SYS_PROC_TYPE enProcType, u32 *pu32Frequency)
 * \brief 
 * 		Get CPU frequency
 * 
 * \param enProcType					(Input)  PROC type
 * \param pu32Frequency					(Output) CPU frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_DRV_SYS_OUT_OF_RANGE	Value is out of range
 * 
 */

ErrorCode DRV_SYS_PLL_SetPower(EN_DRV_SYS_PLL_TYPE enPllType, bool b8PowerUp);
/*!\fn ErrorCode DRV_SYS_PLL_SetPower(EN_DRV_SYS_PLL_TYPE enPllType, bool b8PowerUp)
 * \brief 
 * 		Set PLL power
 * 
 * \param enPllType						(Input)  PLL type
 * \param b8PowerUp						(Input)  Power up or down
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_PLL_GetPower(EN_DRV_SYS_PLL_TYPE enPllType, bool *pb8PowerUp);
/*!\fn ErrorCode DRV_SYS_PLL_GetPower(EN_DRV_SYS_PLL_TYPE enPllType, bool *pb8PowerUp)
 * \brief 
 * 		Get PLL power
 * 
 * \param enPllType						(Input)  PLL type
 * \param pb8PowerUp					(Output) Power up or down
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_PLL_SetFrequency(EN_DRV_SYS_PLL_TYPE enPllType, EN_DRV_SYS_PLL_FREQUENCY_VALUE_TYPE enPllFrequencyValueType, u32 u32Frequency);
/*!\fn ErrorCode DRV_SYS_PLL_SetFrequency(EN_DRV_SYS_PLL_TYPE enPllType, EN_DRV_SYS_PLL_FREQUENCY_VALUE_TYPE enPllFrequencyValueType, u32 u32Frequency)
 * \brief 
 * 		Set PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param enPllFrequencyValueType		(Input)  PLL frequency value type
 * \param u32Frequency					(Input)  PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

void DRV_SYS_PLL_SSC_Set_Appmain(bool enable, u32 Freq, EN_DRV_SYS_PLL_SSC_RATIO Per);
/*!\fn void DRV_SYS_PLL_SSC_Set_Appmain(EN_DRV_SYS_PLL_TYPE enPllType)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param pu32Frequency					(Output) PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

void DRV_SYS_PLL_Read_Appmain(u8 u8Addr);
/*!\fn void DRV_SYS_PLL_Read_Appmain(EN_DRV_SYS_PLL_TYPE enPllType)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param pu32Frequency					(Output) PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

void DRV_SYS_PLL_Write_Appmain(u8 u8Addr, u8 u8Data);
/*!\fn void DRV_SYS_PLL_Read_Appmain(EN_DRV_SYS_PLL_TYPE enPllType)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param pu32Frequency					(Output) PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

void DRV_SYS_PLL_GetFreq_Appmain(EN_DRV_SYS_PLL_TYPE enPllType);
/*!\fn void DRV_SYS_PLL_GetFreq_Appmain(EN_DRV_SYS_PLL_TYPE enPllType)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param pu32Frequency					(Output) PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

void DRV_SYS_PLL_SetFreq_Appmain(EN_DRV_SYS_PLL_TYPE enPllType,u32 u32Frequency);
/*!\fn void DRV_SYS_PLL_SetFreq_Appmain(EN_DRV_SYS_PLL_TYPE enPllType,u32 u32Frequency)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param pu32Frequency					(Output) PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

void DRV_SYS_PLL_SetPower_Appmain(EN_DRV_SYS_PLL_TYPE enPllType, bool b8PowerUp);
/*!\fn void DRV_SYS_PLL_SetPower_Appmain(EN_DRV_SYS_PLL_TYPE enPllType, bool b8PowerUp)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param pu32Frequency					(Output) PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_PLL_GetFrequency(EN_DRV_SYS_PLL_TYPE enPllType, u32 *pu32Frequency);
/*!\fn ErrorCode DRV_SYS_PLL_GetFrequency(EN_DRV_SYS_PLL_TYPE enPllType, u32 *pu32Frequency)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param enPllType						(Input)  PLL type
 * \param pu32Frequency					(Output) PLL frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_MCLK_SetSource(EN_DRV_SYS_MCLK_SOURCE_TYPE enMclkSourceType);
/*!\fn ErrorCode DRV_SYS_MCLK_SetSource(EN_DRV_SYS_MCLK_SOURCE_TYPE enMclkSourceType)
 * \brief 
 * 		Set mclk source
 * 
 * \param enMclkSourceType				(Input)  mclk source
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_MCLK_GetSource(EN_DRV_SYS_MCLK_SOURCE_TYPE *penMclkSourceType);
/*!\fn ErrorCode DRV_SYS_MCLK_GetSource(EN_DRV_SYS_MCLK_SOURCE_TYPE *penMclkSourceType)
 * \brief 
 * 		Get PLL frequency
 * 
 * \param penMclkSourceType				(Output) mclk source
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_MCLK_SetProcRatio(EN_DRV_SYS_PROC_TYPE enProcType, EN_DRV_SYS_MCLK_PROC_RATIO_TYPE enMclkProcRatioType, bool b8Enable);
/*!\fn ErrorCode DRV_SYS_MCLK_SetProcRatio(EN_DRV_SYS_PROC_TYPE enProcType, EN_DRV_SYS_MCLK_PROC_RATIO_TYPE enMclkProcRatioType, bool b8Enable)
 * \brief 
 * 		Set mclk and PROC ratio
 * 
 * \param enProcType					(Input)  PROC type
 * \param enMclkProcRatioType			(Input)  Ratio type
 * \param b8Enable						(Input)  Enable ratio
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_MCLK_GetProcRatio(EN_DRV_SYS_PROC_TYPE enProcType, EN_DRV_SYS_MCLK_PROC_RATIO_TYPE *penMclkProcRatioType, bool *pb8Enable);
/*!\fn ErrorCode DRV_SYS_MCLK_GetProcRatio(EN_DRV_SYS_PROC_TYPE enProcType, EN_DRV_SYS_MCLK_PROC_RATIO_TYPE *penMclkProcRatioType, bool *pb8Enable)
 * \brief 
 * 		Get mclk and PROC ratio
 * 
 * \param enProcType					(Input)  PROC type
 * \param penMclkProcRatioType			(Output) Ratio type
 * \param pb8Enable						(Output) Enable ratio
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_MCLK_SetPowerSave(bool b8Enable, EN_DRV_SYS_MCLK_POWER_SAVE_TYPE enMclkPowerSaveType);
/*!\fn ErrorCode DRV_SYS_MCLK_SetPowerSave(bool b8Enable, EN_DRV_SYS_MCLK_POWER_SAVE_TYPE enMclkPowerSaveType)
 * \brief 
 * 		Set mclk power save
 * 
 * \param b8Enable						(Input)  Enable power save
 * \param enMclkPowerSaveType			(Input)  Power save type
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_MCLK_GetPowerSave(bool *pb8Enable, EN_DRV_SYS_MCLK_POWER_SAVE_TYPE *penMclkPowerSaveType);
/*!\fn ErrorCode DRV_SYS_MCLK_GetPowerSave(bool *pb8Enable, EN_DRV_SYS_MCLK_POWER_SAVE_TYPE *penMclkPowerSaveType)
 * \brief 
 * 		Get mclk power save
 * 
 * \param pb8Enable						(Output) Enable power save
 * \param penMclkPowerSaveType			(Output) Power save type
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_MCLK_GetFrequency(u32 *pu32Frequency);
/*!\fn ErrorCode DRV_SYS_MCLK_GetFrequency(u32 *pu32Frequency)
 * \brief 
 * 		Get mclk frequency
 * 
 * \param pu32Frequency					(Output) mclk frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_Temperature_GetFrequency(u32 *pu32Frequency);
/*!\fn ErrorCode DRV_SYS_Temperature_GetFrequency(u32 *pu32Frequency)
 * \brief 
 * 		Get temperature frequency
 * 
 * \param pu32Frequency					(Output) frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_TIMEOUT				Timeout
 * 
 */

ErrorCode DRV_SYS_Timer_Initialize(DRV_DeviceNameType DeviceName, ST_SYS_TIMER_INIT_PARAMS *pstTimerInitParams);
/*!\fn ErrorCode DRV_SYS_Timer_Initialize(DRV_DeviceNameType DeviceName, ST_SYS_TIMER_INIT_PARAMS *pstTimerInitParams)
 * 
 * \brief
 * 		Initialize the Timer by device name and initial parameter
 * 
 * \param DeviceName					(Input)  Device name
 * \param pstTimerInitParams			(Input)  Initial parameter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_DRV_SYS_UNKNOW_DEVICE	Unknow device
 * 
 */
 
ErrorCode DRV_SYS_Timer_Terminate(DRV_DeviceNameType DeviceName, ST_SYS_TIMER_TERM_PARAMS *pstTimerTermParams);
/*!\fn ErrorCode DRV_SYS_Timer_Terminate(DRV_DeviceNameType DeviceName, ST_SYS_TIMER_TERM_PARAMS *pstTimerTermParams)
 * 
 * \brief
 * 		Terminate the Timer by device name and terminate parameter
 * 
 * \param DeviceName					(Input)  Device name
 * \param pstTimerTermParams			(Input)  Terminate Parameter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_DRV_SYS_UNKNOW_DEVICE	Unknow device
 * 
 */

ErrorCode DRV_SYS_Timer_Open(DRV_DeviceNameType DeviceName, ST_SYS_TIMER_OPEN_PARAMS *pstTimerOpenParams, u32 *pu32TimerHandle);
/*!\fn ErrorCode DRV_SYS_Timer_Open(DRV_DeviceNameType DeviceName, ST_SYS_TIMER_OPEN_PARAMS *pstTimerOpenParams, u32 *pu32TimerHandle)
 * \brief 
 * 		Open a Timer handle by device name and open parameter, each Timer only has one handle for using
 * 
 * \param DeviceName					(Input)  Device name
 * \param pstTimerOpenParams			(Input)  Open Parameter
 * \param pu32TimerHandle				(Output) Timer handle
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_DRV_SYS_UNKNOW_DEVICE	Unknow device
 * \retval ERROR_NO_FREE_HANDLE			Handle has been opened
 * 
 */

ErrorCode DRV_SYS_Timer_Close(u32 *pu32TimerHandle);
/*!\fn ErrorCode DRV_SYS_Timer_Close(u32 *pu32TimerHandle)
 * \brief 
 * 		Close Timer by handle
 * 
 * \param pu32TimerHandle				(Input)  Timer handle
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_DRV_SYS_UNKNOW_DEVICE	Unknow device
 * 
 */

ErrorCode DRV_SYS_Timer_SetReloadValue(u32 u32TimerHandle, u32 u32Value);
/*!\fn ErrorCode DRV_SYS_Timer_SetReloadValue(u32 u32TimerHandle, u32 u32Value)
 * \brief 
 * 		Set Timer reload value for Timer 2. Timer reload value will reload to Timer counter when Timer counter is underflow
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param u32Value						(Input)  Timer reload value
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_Timer_GetReloadValue(u32 u32TimerHandle, u32 *pu32Value);
/*!\fn ErrorCode DRV_SYS_Timer_GetReloadValue(u32 u32TimerHandle, u32 *pu32Value)
 * \brief 
 * 		Get Timer reload value for Timer 2. Timer reload value will reload to Timer value when Timer value is underflow
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param pu32Value						(Output) Timer reload value
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */
ErrorCode DRV_SYS_Timer_SetPeriod(u32 u32TimerHandle, u32 u32Period);
/*!\fn ErrorCode DRV_SYS_Timer_SetPeriod(u32 u32TimerHandle, u32 u32Counter)
 * \brief 
 * 		Set 24bits counter value for Timer 2 or 32bits counter value for Timer 3, 4
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param u32Counter					(Input)  Counter value
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * 
 */

ErrorCode DRV_SYS_Timer_SetCounter(u32 u32TimerHandle,u16 u16ClkDiv, u32 u32Counter);
/*!\fn ErrorCode DRV_SYS_Timer_SetCounter(u32 u32TimerHandle, u32 u32Counter)
 * \brief 
 * 		Set 24bits counter value for Timer 2 or 32bits counter value for Timer 3, 4
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param u32Counter					(Input)  Counter value
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * 
 */

ErrorCode DRV_SYS_Timer_GetCounter(u32 u32TimerHandle, u32 *pu32Counter);
/*!\fn ErrorCode DRV_SYS_Timer_GetCounter(u32 u32TimerHandle, u32 *pu32Counter)
 * \brief 
 * 		Get 24bits counter value for Timer 2 or 32bits counter value for Timer 3, 4
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param pu32Counter					(Output) Counter value for Timer
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * 
 */

ErrorCode DRV_SYS_Timer_SetEnable(u32 u32TimerHandle, bool b8Enable);
/*!\fn ErrorCode DRV_SYS_Timer_SetEnable(u32 u32TimerHandle, bool b8Enable)
 * \brief 
 * 		Set Timer enable or not
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param b8Enable						(Input)  Enable or disable Timer
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * 
 */

ErrorCode DRV_SYS_Timer_GetEnable(u32 u32TimerHandle, bool *pb8Enable);
/*!\fn ErrorCode DRV_SYS_Timer_GetEnable(u32 u32TimerHandle, bool *pb8Enable)
 * \brief 
 * 		Get Timer enable or not
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param pb8Enable						(Output) Timer is enable or disable 
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * 
 */

ErrorCode DRV_SYS_Timer_SetBit32Value(u32 u32TimerHandle, u32 u32Value);
/*!\fn ErrorCode DRV_SYS_Timer_SetBit32Value(u32 u32TimerHandle, u32 u32Value)
 * \brief 
 * 		Set MSB (bit32) value for Timer 3, 4
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param u32Value						(Input)  Set Timer bit32 value, this value is only 0 or 1
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_Timer_GetBit32Value(u32 u32TimerHandle, u32 *pu32Value);
/*!\fn ErrorCode DRV_SYS_Timer_GetBit32Value(u32 u32TimerHandle, u32 *pu32Value)
 * \brief 
 * 		Get MSB (bit32) value for Timer 3, 4
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param pu32Value						(Output) Get Timer bit32 value, this value is only 0 or 1
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_Timer_SetClockSource(u32 u32TimerHandle, EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE enClockSource);
/*!\fn ErrorCode DRV_SYS_Timer_SetClockSource(u32 u32TimerHandle, EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE enClockSource)
 * \brief 
 * 		Set clock source for Timer 3, 4
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param enClockSource					(Input)  Set clock source
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_Timer_GetClockSource(u32 u32TimerHandle, EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE *penClockSource);
/*!\fn ErrorCode DRV_SYS_Timer_GetClockSource(u32 u32TimerHandle, EN_DRV_SYS_TIMER_CLOCK_SOURCE_TYPE *penClockSource)
 * \brief 
 * 		Get clock source for Timer 3, 4
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param penClockSource				(Output) Get clock source
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_Timer_ForceReload(u32 u32TimerHandle);
/*!\fn ErrorCode DRV_SYS_Timer_ForceReload(u32 u32TimerHandle)
 * \brief 
 * 		Set Timer reload value to Timer counter right away for Timer 2
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_Timer_SetReloadMode(u32 u32TimerHandle, bool b8Reload);
/*!\fn ErrorCode DRV_SYS_Timer_SetReloadMode(u32 u32TimerHandle, bool b8Reload)
 * \brief 
 * 		Set Timer reload value mode
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param b8Reload						(Input)  Whether automatically reload the Timer counter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_Timer_GetReloadMode(u32 u32TimerHandle, bool *pb8Reload);
/*!\fn ErrorCode DRV_SYS_Timer_GetReloadMode(u32 u32TimerHandle, bool *pb8Reload)
 * \brief 
 * 		Get Timer reload value mode
 * 
 * \param u32TimerHandle				(Input)  Timer handle
 * \param pb8Reload						(Output) Whether automatically reload the Timer counter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval ERROR_INVALID_HANDLE			Invalid handle
 * \retval ERROR_DRV_SYS_TIMER_TYPE		Timer type is wrong
 * 
 */

ErrorCode DRV_SYS_WatchDog_Reset(void);
/*!\fn ErrorCode DRV_SYS_WatchDog_Reset(void)
 * \brief 
 * 		Reset Watch Dog enable or not
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * 
 */

ErrorCode DRV_SYS_WatchDog_Enable(bool b8Enable);
/*!\fn ErrorCode DRV_SYS_WatchDog_Enable(bool b8Enable)
 * \brief 
 * 		Set Watch Dog enable or not
 * 
 * \param b8Enable						(Input)  Enable or disable watch dog
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * 
 */

ErrorCode DRV_SYS_WatchDog_TimeOut(u32 u32TimeOutMillisecond);
/*!\fn ErrorCode DRV_SYS_WatchDog_TimeOut(u32 u32TimeOutMillisecond)
 * \brief 
 * 		Set Watch Dog timeout value
 * 
 * \param u32TimeOutMillisecond			(Input)  Set timeout in millisecond (with 0~86480 millisec)
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * 
 */
 
void DRV_SYS_DCache_WriteBack(u32 u32MemAddr, u32 u32Size);
/*!\fn void DRV_SYS_DCache_WriteBack(u32 u32MemAddr, u32 u32Size)
 * \brief 
 * 		DCache write back
 * 
 * \param u32MemAddr					(Input)  Memory address
 * \param u32Size						(Input)  Size
 * 
 */

void DRV_SYS_DCache_Invalidate(u32 u32MemAddr, u32 u32Size);
/*!\fn void DRV_SYS_DCache_Invalidate(u32 u32MemAddr, u32 u32Size)
 * \brief 
 * 		Invalidate DCache
 * 
 * \param u32MemAddr					(Input)  Memory address
 * \param u32Size						(Input)  Size
 * 
 */

void DRV_SYS_DCache_Disable(void);
/*!\fn void DRV_SYS_DCache_Disable(void)
 * \brief 
 * 		Disable DCache
 * 
 */

void DRV_SYS_DCache_Enable(void);
/*!\fn void DRV_SYS_DCache_Enable(void)
 * \brief 
 * 		Enable DCache
 * 
 */

u32 DRV_SYS_DCache_is_Enabled(void);
/*!\fn u32 DRV_SYS_DCache_is_Enabled(void)
 * \brief 
 * 		Get DCache is enable or not
 * 
 * \return DCache Enable Status
 * \retval TRUE							Enable
 * \retval FALSE						Disable
 * 
 */

ErrorCode DRV_SYS_GetMemPartitionInfo(EN_DRV_SYS_MEM_PARTITION const enMemName, u32* pu32StartAddr, u32* pu32Size);
/*!\fn DRV_SYS_GetMemPartitionInfo (EN_DRV_SYS_MEM_PARTITION const enMemName, u32* pu32StartAddr, u32* pu32Size)
 * \brief 
 * 		Get Frame Buffer memory information
 * 		Start Address & Size (bytes)
 * 
 * \return Get Info Status
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

u8* DRV_SYS_GetVersion(void);
/*!\fn u8* DRV_SYS_GetVersion(void)
 * \brief 
 * 		Get version of SYS
 * 
 * \return SYS Version
 * 
 */

ErrorCode DRV_SYS_Unzip(u8* pu8ZipSrcAddr, u8* pu8DstAddr, u32 u32ZipFileLength);
/*!\fn ErrorCode DRV_SYS_Unzip(u8* pu8ZipSrcAddr, u8* pu8DstAddr, u32 u32ZipFileLength)
 * \brief 
 * 		Unzip API
 * 
 * \param pu8ZipSrcAddr			(Input)  The source address of zip data.
 * \param pu8DstAddr			(Input)  Target address 
 * \param u32ZipFileLength		(Input)  The length of zip data.
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Bad parameter passed
 * 
 */

EN_DRV_SYS_CHIP_VERSION DRV_SYS_GetChipVersion(void);
/*!\fn EN_DRV_SYS_CHIP_VERSION DRV_SYS_GetChipVersion(void)
 * \brief 
 * 		Get version of CHIP
 * 
 * \return CHIP Version
 * 
 */

u32 DRV_SYS_GetBootCodeVersion(void);
/*!\fn u32 DRV_SYS_GetBootCodeVersion(void)
 * \brief 
 * 		Get version of boot code
 * 
 * \return boot code Version
 * 
 */


EN_DRV_SYS_CHIP_ID DRV_SYS_GetChipID(void);
/*!\fn EN_DRV_SYS_CHIP_ID DRV_SYS_GetChipID(void)
* \brief 
*		Get CHIP ID
* 
* \return CHIP ID
* 
*/

ErrorCode DRV_SYS_PLL_SSC_SetConfig(EN_DRV_SYS_PLL_TYPE enPllType, PST_PLL_SSC_CTRL pstSSCCtrl);
/*!\fn   ErrorCode DRV_SYS_PLL_SSC_SetConfig(EN_DRV_SYS_PLL_TYPE enPllType, PST_PLL_SSC_CTRL pstSSCCtrl)
 * \brief 
 * 		Set MPLL & BPLL SSC (spread spectrum clcok) configuration
 * 
 * \param enPllType					(Input)  PLL type
 * \param pstSSCCtrl					(Input)  PLL SSC parameter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_PLL_SSC_GetConfig(EN_DRV_SYS_PLL_TYPE enPllType, PST_PLL_SSC_CTRL pstSSCCtrl);
/*!\fn	ErrorCode DRV_SYS_PLL_SSC_GetConfig(EN_DRV_SYS_PLL_TYPE enPllType, PST_PLL_SSC_CTRL pstSSCCtrl)
 * \brief 
 *		Get MPLL & BPLL SSC (spread spectrum clcok) configuration
 * 
 * \param enPllType					(Input)  PLL type
 * \param pstSSCCtrl					(Output)  PLL SSC parameter
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_SYS_GetFrequency(EN_DRV_SYS_PLL_TYPE enPlltype,u32 *pu32Frequency);
/*!\fn	ErrorCode DRV_SYS_GetFrequency(EN_DRV_SYS_PLL_TYPE enPlltype,u32 *pu32Frequency)
 * \brief 
 *		Get sys Frequency
 * 
 * \param enPlltype					(Input)  Frequency type
 * \param pu32Frequency				(Input)  Frequency
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

void DRV_SYS_SET_DM_Event(u8 u8Evt);
void DRV_SYS_CLEAR_DM_Event(u8 u8Evt);

void DRV_SYS_CLK_BIST_GRPA0(u8 u8port);
void DRV_SYS_CLK_BIST_GRPA1(u8 u8port);
void DRV_SYS_CLK_BIST_GRPB0(u8 u8port);
void DRV_SYS_CLK_BIST_GRPB1(u8 u8port);
void DRV_SYS_CLK_BIST_GRPC0(u8 u8port);
void DRV_SYS_CLK_BIST_GRPC2(u8 u8port);
void DRV_SYS_CLK_BIST_GRPD(u8 u8port);
void DRV_SYS_GET_COUNTER(u8 u8port);

void hal_timer_enable(EN_DRV_SYS_TIMER_TYPE enTimerType, bool b8Enable);

ErrorCode DRV_SYS_DDR_Phase(s8 Cmd, s8 Clk, s8 DQ, s8 DQS, s8 RD);
u8 _DRV_SYS_DDR_getCmd(void);
u8 _DRV_SYS_DDR_getRD(void);
u8 _DRV_SYS_DDR_getDQ(void);

void DRV_SYS_ICache_Lock(u32 u32MemAddr, u32 u32Size);
void DRV_SYS_ICache_UnLock(u32 u32MemAddr, u32 u32Size);

void DRV_MPLL_FREQ_DET(u8 u8ClkSel);
void DRV_SYS_PLL_RA_JITTER_TEST(bool bEnable);

#endif // __DRV_SYS_H__
