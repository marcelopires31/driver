//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide FCR Control
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

#ifndef __FCR_H__
#define __FCR_H__

#include "def_type.h"
#include "def_err.h"

#include "drv_gpio.h"

#include "drv_config.h"

//#include "drv_debug.h"
//#include "def_dbg.h"

#define WriteReg( ADDR, DATA )	( *((volatile unsigned int *)(ADDR)) = DATA )
#define ReadReg( ADDR )			( *((volatile unsigned int *)(ADDR)) )
#define WriteRegByOR( ADDR, DATA )	( *((volatile unsigned int *)(ADDR)) |= DATA )

#define FCR_CACHE_CONVERT				OS_SysGetNonCacheAddr()

/*
 * Brief: SDC Error code definition.
 */
enum
{
	ERROR_FCR_DEV_NAME     = ERROR_BASE_DRV_FCR,		            /*!< Device Name Error  			*/
	ERROR_FCR_FCMMGR,
	ERROR_FCR_CARD_NOT_INSERTED,
	ERROR_FCR_SD_CMD_NOT_COMPLETE,
	ERROR_FCR_SD_LINE_SIGNAL,
	ERROR_FCR_SD_NONRECOVABLE,
	ERROR_FCR_SD_GENERAL,
	ERROR_FCR_SD_REG_VALUE_WRONG,
	ERROR_FCR_MS_CMD_NOT_COMPLETE,
	ERROR_FCR_MS_NONRECOVABLE,
	ERROR_FCR_MS_GENERAL,
	ERROR_FCR_MS_NO_PHY_ADDR,
};

/*
 * Brief: FCR EventID definition.
 */
enum
{
	EN_FCR_EVENT_PLUGIN,								/*!< The event to indicate plugged in	*/
	EN_FCR_EVENT_PLUGOUT,								/*!< The event to indicate plugged out	*/
	EN_FCR_EVENT_SDIOIN,								/*!< The event to indicate SDIO in		*/
	EN_FCR_EVENT_SDIOOUT,								/*!< The event to indicate SDIO out		*/
};

typedef enum
{
	EN_FCR_BUS_WIDTH_1BIT,
	EN_FCR_BUS_WIDTH_4BIT,
}EN_FCR_BUS_WIDTH;

/**
 * \brief
 *  the FCR initial structure
 */
typedef struct
{
    u32                             u32EventHandle;                 /*!< Event handle               */
	os_mempool_handle				u32MemPoolHandle;				/*!<  memory pool handle 	    */
}ST_FCR_INIT_PARAMS, *PST_FCR_INIT_PARAMS;

/**
 * \brief
 *  the FCR terminate structure
 */
typedef struct
{
    bool                       b8ForceTerminate;					/*!< Force terminate HDMI	                */
}ST_FCR_TERM_PARAMS, *PST_FCR_TERM_PARAMS;

//function define
ErrorCode FCR_Init(void);
/*!\fn ErrorCode FCR_Init(void)
 * \brief
 *		Do the FCR initialization.
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 *
 */

ErrorCode FCR_Term(void);
/*!\fn ErrorCode FCR_Term(void)
 * \brief
 *		Do the FCR termination.
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 *
 */

void FCR_GetBusFreq(u32 u32Freq);
u32 FCR_GetChipID(void);
void DRV_FCR_Pool_Init(u32 u32MemHandle);

void FCR_SetPweGpio(u32 u32PweGpioHandle, PST_GPIO pstPweGpio, EN_DRV_GPIO_STATUS enActive);

ErrorCode FCR_ConfigBusWidth(EN_FCR_BUS_WIDTH enBusWidth);

ErrorCode FCR_GetWriteProtectedStatus(bool *pb8WriteProtected);

ErrorCode FCR_SafeRemove(void);

ErrorCode FCR_GetCapacity(u32 *pu32Sectors);

//FCR_Read/WriteSector() Buffer must be 32 aligned.
ErrorCode FCR_ReadSector(u32 u32Buffer, u32 u32SectorAddress, u16 u16SectorCount);

ErrorCode FCR_WriteSector(u32 u32Buffer, u32 u32SectorAddress, u16 u16SectorCount);

ErrorCode FCR_GetSDIOWriteProtectedStatus(bool *pb8WriteProtected);

ErrorCode FCR_GetSDIOCapacity(u32 *pu32Sectors);

ErrorCode FCR_ReadSDIOSector(u32 u32Buffer, u32 u32SectorAddress, u16 u16SectorCount);

ErrorCode FCR_WriteSDIOSector(u32 u32Buffer, u32 u32SectorAddress, u16 u16SectorCount);

#endif	// __FCR_H__
