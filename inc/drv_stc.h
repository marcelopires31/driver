/***************************************************************************
**         Copyright (c) 2008, Novatek Inc . All rights reserved.
**         SA2, all right reserved.
**
**	Product	: NV78233A Firmware
**
**	Date		: 2009.06.18
**	Author		: Novatek (SA2)
**	Purpose	: 
**	Sources	: drv_stc.h
****************************************************************************
**
** Modification use :
****************************************************************************
**	Update
**
**	Date  	: 2009.06.18
**	Name	: Novatek (SA2)
**	Description	: 
**
**	Item			                  Source
**	----------------------------------------		-------------------
**	. create 					            drv_stc.h
****************************************************************************/

#ifndef __DRV_STC_H__
#define __DRV_STC_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/***************************************************************************
 * Include files
 * ************************************************************************/

#include "def_type.h"
#include "def_err.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "os.h"
#include "drv_debug.h"
#include "drv_event.h"

#define STC_CACHE_CONVERT OS_SysGetNonCacheAddr()

/***************************************************************************
 * Type definition
 * ************************************************************************/

typedef u32                     DRV_STC_Handle_t;


/***************************************************************************
 * Definition
 * ************************************************************************/


/***************************************************************************
 * Enumeration
 * ************************************************************************/

typedef enum
{
    EN_DRV_STC_SYNC_MASTER_BASE             = 0x0,

    EN_DRV_STC_SYNC_MASTER_PCR,
    EN_DRV_STC_SYNC_MASTER_VDEC,
    EN_DRV_STC_SYNC_MASTER_ADEC,
    EN_DRV_STC_SYNC_MASTER_ADEC_VDECFIRSTSTC,
    EN_DRV_STC_SYNC_MASTER_FREERUN,
    EN_DRV_STC_SYNC_MASTER_VDEC_PCRFIRSTSTC,

    // for count
    EN_DRV_STC_SYNC_MASTER_NB
} EN_DRV_STC_SyncMaster, *PEN_DRV_STC_SyncMaster;
/**
 * \brief
 * Define the type of sync master.
 */


typedef enum
{
    EN_DRV_STC_SYNC_STATUS_BASE             = 0x0,

    EN_DRV_STC_SYNC_STATUS_AUDIO_SYNC_ACHIEVED,
    EN_DRV_STC_SYNC_STATUS_AUDIO_SYNC_LOST,
    EN_DRV_STC_SYNC_STATUS_VDEC_SYNC_ACHIEVED,
    EN_DRV_STC_SYNC_STATUS_VDEC_SYNC_LOST,

    // for count
    EN_DRV_STC_SYNC_STATUS_NB
} EN_DRV_STC_SyncStatus, *PEN_DRV_STC_SyncStatus;
/**
 * \brief
 * Define the type of sync status.
 */


enum stc_error_e
{
    ERROR_STC_BASE                   = ERROR_BASE_DRV_STC,
    ERROR_STC_INVALID_DEVICE,
    ERROR_STC_DEVICE_NOT_INIT,
    ERROR_STC_NO_FREE_DEVICE,
    ERROR_STC_DUPLICATE_DEVICE_NAME,
    ERROR_STC_INVALID_HANDLE,
    ERROR_STC_NO_FREE_HANDLE,
    ERROR_STC_HANDLE_IN_USE,
    ERROR_STC_NO_FREE_TIMER,
    ERROR_STC_FREE_MEMORY_FAIL,
    ERROR_STC_ALLOCATE_MEMORY_FAIL,
    ERROR_STC_SPEED_NOT_SUPPORT,
    ERROR_STC_INVALID_TIMER,
    ERROR_STC_INVALID_STC,
    ERROR_STC_NOT_START,
    ERROR_STC_UNKNOWN_SYNC_MASTER,
    ERROR_STC_UNSUPPORT_SPEED,
    ERROR_STC_NOT_PCR_MASTER,
    ERROR_STC_WRONG_SYNC_MASTER,
    ERROR_STC_PCR_MASTER_NOT_SUPPORT_SPEED_FUNCTION,
};
/**
 * \brief
 * Define the STC error code.
 */


typedef enum
{
    EN_DRV_STC_EVENT_AVSYNC_ACHIEVED                     = 0,
    EN_DRV_STC_EVENT_AVSYNC_LOST,
}EN_DRV_STC_Event, *PEN_DRV_STC_Event;
/**
 * \brief
 * Define the STC event ID.
 */


/***************************************************************************
 * Structure
 * ************************************************************************/

typedef struct
{
    /* Base : 90KHz */
    u32             u32Time;                             /* bit31~bit0 of TIME */
    u32             u32Time33;                           /* bit32 of TIME */

    /* Extension : 27MHz */
    u32             u32Extension;                        /* bit8~bit0 extension of TIME */
} ST_DRV_STC_Time, *PST_DRV_STC_Time;
/*!
* Define a structure to save 33 bits base and 9 bits extension of PTS/PCR value.
*/


typedef struct
{
    ST_DRV_STC_Time     stSTC;
    ST_DRV_STC_Time     stPCR;
} ST_DRV_STC_PCR, *PST_DRV_STC_PCR;
/*!
* Define a structure to save PTS/PCR value for clock recovery.
*/


typedef struct
{
    u32             u32MaxDeviceNb;                         /* Max number of device can be used concurrently */
    u32             u32MaxHandleNb;                         /* Max number of open handle per device */
    bool           b8IsSupportPCRMaster;                   /* Is STC module support PCR master */
    bool           b8IsSupportClockRecovery;               /* Is STC module support clock recovery */
} ST_DRV_STC_Capability, *PST_DRV_STC_Capability;
/**
 * \brief
 * Define the supported/unsupported features and limitation of the STC.
 */


typedef struct
{
	os_mempool_handle			u32MemHandle;				/*!< A memory pool handle for STC module	*/
} ST_DRV_STC_InitParams, *PST_DRV_STC_InitParams;
/**
 * \brief
 * Define the parameters of initialization.
 */


typedef struct
{
    EN_DRV_STC_SyncMaster           enSyncMaster;           /* Initial sync master type */
    u32                             u32EvtHandle;           /* Event handle for STC */
} ST_DRV_STC_OpenParams, *PST_DRV_STC_OpenParams;
/**
 * \brief
 * Define the parameters of open.
 */


typedef struct
{
    bool       b8ForceTerminate;
} ST_DRV_STC_TermParams, *PST_DRV_STC_TermParams;
/**
 * \brief
 * Define the parameters of terminate.
 */


/***************************************************************************
 * API
 * ************************************************************************/

ErrorCode DRV_STC_GetVersion(u8 **pu8Version);
/*!\fn ErrorCode DRV_STC_GetVersion(u8 *pu8Version)
 *
 * \brief
 * 		Get info of the module version
 *
 * \param	pu8Version  			(Output) Version string
 *
 * \return	STC Operation Error Code
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRV_STC_GetCapability(const DRV_DeviceNameType DeviceName, PST_DRV_STC_Capability pstCapability);
/*!
\fn ErrorCode DRV_STC_GetCapability(const DRV_DeviceNameType DeviceName, PST_DRV_STC_Capability pstCapability)
\brief Retrieves the capabilities of the driver.
\param DeviceName IN : Name of the STC module from which to get capabilities.
\param pstCapability IN : Allocated structure
	OUT : Structure filled with capabilities of the implementation of the driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_Init(const DRV_DeviceNameType DeviceName, const PST_DRV_STC_InitParams pstInitParams);
/*!
\fn ErrorCode DRV_STC_Init(const DRV_DeviceNameType DeviceName, const PST_DRV_STC_InitParams pstInitParams)
\brief Initializes a STC module and gives it the name DeviceName.
\param DeviceName IN : Name of the STC module to initialize.
\param pstInitParams IN : parameters to initialise the STC module.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_Open(const DRV_DeviceNameType DeviceName, const PST_DRV_STC_OpenParams pstOpenParams, DRV_STC_Handle_t * const Handle);
/*!
\fn ErrorCode DRV_STC_Open(const DRV_DeviceNameType DeviceName, const PST_DRV_STC_OpenParams pstOpenParams, DRV_STC_Handle_t * const Handle)
\brief Open a connection to STC module.
\param DeviceName Name of the STC module to open.
\param Params Configuration parameters.
\param Handle IN : Pointer to a handle
	OUT : Handle on open connection to the STC module
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_Close(const DRV_STC_Handle_t Handle);
/*!
\fn ErrorCode DRV_STC_Close(const DRV_STC_Handle_t Handle)
\brief Close an opened connection.
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_Term(const DRV_DeviceNameType DeviceName, const PST_DRV_STC_TermParams pstTermParams);
/*!
\fn ErrorCode DRV_STC_Term(const DRV_DeviceNameType DeviceName, const PST_DRV_STC_TermParams pstTermParams)
\brief Terminates the STC module and let the hardware in the specified state.
\param DeviceName Name of an initialised device.
\param pstTermParams Configuration parameters of the hardware.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_GetSTC(const DRV_STC_Handle_t Handle, const PST_DRV_STC_Time pstSTC);
/*!
\fn ErrorCode DRV_STC_GetSTC(const DRV_STC_Handle_t Handle, const PST_DRV_STC_Time pstSTC)
\brief Get STC from the STC module.
\param Handle IN : Handle of the STC module.
\param pstSTC IN : pointer of STC structure.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_UpdateSTC(const DRV_STC_Handle_t Handle, const PST_DRV_STC_Time pstSTC);
/*!
\fn ErrorCode DRV_STC_UpdateSTC(const DRV_STC_Handle_t Handle, const PST_DRV_STC_Time pstSTC)
\brief Update STC to the STC module.
\param Handle IN : Handle of the STC module.
\param pstSTC IN : pointer of STC structure.
              OUT : current STC of specified STC handle
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_UpdatePCR(const DRV_STC_Handle_t Handle, const PST_DRV_STC_PCR pstPCR);
/*!
\fn ErrorCode DRV_STC_UpdatePCR(const DRV_STC_Handle_t Handle, const PST_DRV_STC_PCR pstPCR)
\brief Update STC/PCR to the STC module for clock recovery.
\param Handle IN : Handle of the STC module.
\param pstPCR IN : pointer of PCR structure.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_GetSTCNum(const DRV_STC_Handle_t Handle, u32* const pu32STCNum);
/*!
\fn ErrorCode DRV_STC_GetSTCNum(const DRV_STC_Handle_t Handle, const u32* pu32STCNum)
\brief Get STC hardware number by handle.
\param Handle IN : Handle of the STC module.
\param pu32STCNum IN : pointer of STCNum variable.
                  OUT : Index of timer this STC handle ues.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_GetSTCHandle(u32 const u32STCNum, DRV_STC_Handle_t* Handle);
/*!
\fn ErrorCode DRV_STC_GetSTCHandle(u32 const u32STCNum, DRV_STC_Handle_t* Handle)
\brief Get STC handle by STC Number.
\param u32STCNum IN : STCNum of the STC module.
\param * Handle  IN : pointer of Handle structure.
                 OUT : Handle structure of STC Number.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_ControlClockRecovery(const DRV_STC_Handle_t Handle, bool b8Enable);
/*!
\fn ErrorCode DRV_STC_ControlClockRecovery(const DRV_STC_Handle_t Handle, bool b8Enable)
\brief Turn on/off clock recovery mechanism by handle.
\param Handle IN : Handle of the STC module.
\param b8Enable IN : Enable/disable clock recovery.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_GetSyncMaster(const DRV_STC_Handle_t Handle, PEN_DRV_STC_SyncMaster penSyncMaster);
/*!
\fn ErrorCode DRV_STC_GetSyncMaster(const DRV_STC_Handle_t Handle, PEN_DRV_STC_SyncMaster penSyncMaster)
\brief Get sync master type of specified STC module.
\param Handle IN : Handle of the STC module.
\param penSyncMaster IN : pointer of PEN_DRV_STC_SyncMaster variable.
                     OUT : Currect sync master type of the STC module.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_SetSyncMaster(const DRV_STC_Handle_t Handle, EN_DRV_STC_SyncMaster enSyncMaster);
/*!
\fn ErrorCode DRV_STC_SetSyncMaster(const DRV_STC_Handle_t Handle, EN_DRV_STC_SyncMaster enSyncMaster)
\brief Set sync master type of specified STC module.
\param Handle IN : Handle of the STC module.
\param enSyncMaster IN : Sync master type want to set.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_SetSpeed(const DRV_STC_Handle_t Handle, s32 s32Speed);
/*!
\fn ErrorCode DRV_STC_SetSpeed(const DRV_STC_Handle_t Handle, s32 s32Speed)
\brief Set STC speed.
\param Handle IN : Handle of the STC module.
\param s32Speed IN : Speed of this STC module.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_Reset(const DRV_STC_Handle_t Handle);
/*!
\fn ErrorCode DRV_STC_Reset(const DRV_STC_Handle_t Handle)
\brief Reset STC module information.
\param Handle IN : Handle of the STC module.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_NotifySyncStatus(const DRV_STC_Handle_t Handle, EN_DRV_STC_SyncStatus enStatus);
/*!
\fn ErrorCode DRV_STC_NotifySyncStatus(const DRV_STC_Handle_t Handle, EN_DRV_STC_SyncStatus enStatus)
\brief Notify AV sync status to STC module.
\param Handle IN : Handle of the STC module.
\param enStatus IN : AV sync status.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_STC_GetFirstUpdateSTCFlag(const DRV_STC_Handle_t Handle, pu8 pu8FirstUpdateSTC);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __DRV_STC_H__ */

