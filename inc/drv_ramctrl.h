#ifndef __DRV_RAMCTRL_H__
#define __DRV_RAMCTRL_H__

/*******************************************************************************************/
#include "def_type.h"
#include "def_err.h"

/*!
 * \brief 
 * Rammonitor Error code definition.
 */
enum
{
	ERROR_RAMCTRL_DEV_NAME     = ERROR_BASE_DRV_RAMCTRL,		            /*!< Device Name Error                                          */
	ERROR_RAMCTRL_DEV_RESOURCE,		                               				     /*!< Rammonitor don't have device resource                            */	
	ERROR_RAMCTRL_UNSUPPORTED,								            /*!<                                           */
};

/**
 * \brief
 *  the Rammonitor initial structure
 */
typedef struct
{
   u32 u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_RAMCTRL_INIT_PARAMS, *PST_DRV_RAMCTRL_INIT_PARAMS;

/**
 * \brief
 *  the Rammonitor OS Init structure
 */
typedef struct
{
    u32 u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_RAMCTRL_OS_INIT_PARAMS, *PST_DRV_RAMCTRL_OS_INIT_PARAMS;

/**
 * \brief
 *  the Rammonitor config structure
 */
typedef struct
{
    u8 				   u8RegioIdx;
    u32 				   u32StartAddr;
    u32 				   u32EndAddr;
    bool 				   b8EnableRegion;	
}ST_DRV_RAMCTRL_CFG_PARAMS, *PST_DRV_RAMCTRL_CFG_PARAMS;

/**
 * \brief
 *  the Rammonitor region structure
 */
typedef struct
{
    u32 				   u32StartAddr;
    u32 				   u32EndAddr;
}ST_DRV_RAMCTRL_REGION_PARAMS, *PST_DRV_RAMCTRL_REGION_PARAMS;

ErrorCode DRV_RAMCTRL_Initialize(DRV_DeviceNameType DeviceName, PST_DRV_RAMCTRL_INIT_PARAMS pstParams);
ErrorCode DRV_RAMCTRL_SetPassword(DRV_DeviceNameType DeviceName, u32 u32Password);
ErrorCode DRV_RAMCTRL_SetRegion(DRV_DeviceNameType DeviceName, PST_DRV_RAMCTRL_CFG_PARAMS pstCfg);
ErrorCode DRV_RAMCTRL_GetRegion(DRV_DeviceNameType DeviceName, u8 u8RegioIdx, PST_DRV_RAMCTRL_REGION_PARAMS pstOutputRegion);


#endif   /* __DRV_RAMCTRL_HAL_H__ */
