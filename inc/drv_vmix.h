//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide Layer Control
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


#ifndef __DRV_VMIX_H__
#define __DRV_VMIX_H__

#ifdef __cplusplus
extern  "C"
{
#endif

#include "def_type.h"
#include "def_err.h"
#include "os.h"

#define VMIX_MAX_DEV_NUM  	1
#define VMIX_MAX_HANDLE		1

/**
 * \brief
 * enumerate to indicate the error of operation
 */
typedef enum
{
	EN_DRV_VMIX_ERR_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_VMIX,	/*!< Operation invalid, because handle not close*/
	EN_DRV_VMIX_ERR_UNKNOW_DEVICE,								/*!< Invalid device name */
	EN_DRV_VMIX_ERR_HANDLE_USED
}EN_DRV_VMIX_ERROR;


/**
 * \brief
 * enumerate to indicate the Compositor provides 4 Layers to mix the planes, and output to which channels
 * OM:EN_DRV_VMIX_PLANESEL_OSD_MAIN, OS:EN_DRV_VMIX_PLANESEL_OSD_SP 
 * VM:EN_DRV_VMIX_PLANESEL_VIDEO_MAIN, VA:EN_DRV_VMIX_PLANESEL_VIDEO_AUX
 * the mix mode from left to right is top layer to bottom layer
 */
typedef enum
{
    EN_DRV_VMIXMODE_0 = 0,      /*!< mix mode OM/OS/VM/VA*/
    EN_DRV_VMIXMODE_1,          /*!< mix mode OM/OS/VA/VM*/
    EN_DRV_VMIXMODE_2,          /*!< mix mode OM/VM/OS/VA*/
    EN_DRV_VMIXMODE_3,          /*!< mix mode OM/VA/OS/VM*/
    EN_DRV_VMIXMODE_4,          /*!< mix mode OM/VM/VA/OS*/
    EN_DRV_VMIXMODE_5,          /*!< mix mode OM/VA/VM/OS*/  
    EN_DRV_VMIXMODE_6,          /*!< mix mode OS/OM/VM/VA*/
    EN_DRV_VMIXMODE_7,          /*!< mix mode OS/OM/VA/VM*/
    EN_DRV_VMIXMODE_8,          /*!< mix mode VM/OM/OS/VA*/
    EN_DRV_VMIXMODE_9,          /*!< mix mode VA/OM/OS/VM*/
    EN_DRV_VMIXMODE_10,         /*!< mix mode VM/OM/VA/OS*/ 
    EN_DRV_VMIXMODE_11,         /*!< mix mode VA/OM/VM/OS*/ 
    EN_DRV_VMIXMODE_12,         /*!< mix mode VM/OS/OM/VA*/ 
    EN_DRV_VMIXMODE_13,         /*!< mix mode VA/OS/OM/VM*/ 
    EN_DRV_VMIXMODE_14,         /*!< mix mode OS/VM/OM/VA*/
    EN_DRV_VMIXMODE_15,         /*!< mix mode OS/VA/OM/VM*/ 
    EN_DRV_VMIXMODE_16,         /*!< mix mode VA/VM/OM/OS*/ 
    EN_DRV_VMIXMODE_17,         /*!< mix mode VM/VA/OM/OS*/ 
    EN_DRV_VMIXMODE_18,         /*!< mix mode VA/OS/VM/OM*/ 
    EN_DRV_VMIXMODE_19,         /*!< mix mode VM/OS/VA/OM*/ 
    EN_DRV_VMIXMODE_20,         /*!< mix mode VA/VM/OS/OM*/ 
    EN_DRV_VMIXMODE_21,         /*!< mix mode VM/VA/OS/OM*/
    EN_DRV_VMIXMODE_22,         /*!< mix mode OS/VM/VA/OM*/
    EN_DRV_VMIXMODE_23,         /*!< mix mode OS/VA/VM/OM*/
    EN_DRV_VMIXMODE_NUM,        /*!< mix mode total number*/
} EN_DRV_VMIXMODE, *PEN_DRV_VMIXMODE;


/*!
 * \brief
 * the initial structure includes the device hardware setting
 */
typedef struct 
{
	os_mempool_handle	u32MemPoolHandle;				/*!< A memory pool handle for VMIX module	*/
}ST_VMIX_Init, *PST_VMIX_Init;


/*!
 * \brief
 * the open structure includes the MIX opening parameters
 */
typedef struct 
{
    EN_DRV_VMIXMODE		enVmixMode; /*!< set mix mode*/
}ST_VMIX_Open, *PST_VMIX_Open;

ErrorCode DRV_VMIX_GetVersion (u8 *pu8VersionNum);
/*!\fn ErrorCode DRV_VMIX_GetVersion (u8 *pu8VersionNum)
 *
 * \brief
 * 		Get the Module Version number of VMIX
 *
 * \param	pu8VersionNum			(Output) Version string of VMIX
 *
 *
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */



ErrorCode DRV_VMIX_Init(DRV_DeviceNameType DeviceName, PST_VMIX_Init pstInit);
/*!\fn ErrorCode DRV_VMIX_Init(DRV_DeviceNameType DeviceName, PST_VMIX_Init pstInit)
 *
 * \brief
 * 		Initialize VMIX device with pstInit setting
 *
 * \param 	DeviceName						(Input)  Device Name 
 * \param	pstInit							(Input) Pointer to the initialization parameter structure
 *
 * \retval	ERROR_NO_ERROR					no error
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval  ERROR_INITIALISED               The driver is not initialized  
 * \retval  ERROR_NO_FREE_HANDLE            No free handle for the device 
 *
 */

ErrorCode DRV_VMIX_Open (DRV_DeviceNameType DeviceName, PST_VMIX_Open pstOpen, u32 *pu32VmixHandle);
/*!\fn ErrorCode DRV_VMIX_Open (DRV_DeviceNameType DeviceName, PST_VMIX_Open pstOpen, u32 *pu32VmixHandle)
 *
 * \brief
 * 		Open the VMIX device and associate it with a handle
 *
 * \param 	DeviceName		(Input)  Device Name 
 * \param	pstOpen			(Input) Pointer to the opening parameter structure
 * \param	pu32VmixHandle	(Output) The returned handle of the opened device driver
 *
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_INITIALISED			The driver is not initialized
 * \retval	ERROR_BAD_PARAMETER			Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 * \retval	ERROR_NO_FREE_HANDLE		No free handle for the device
 */


ErrorCode DRV_VMIX_Close (u32* pu32VmixHandle);
/*!\fn ErrorCode DRV_VMIX_Close(u32* pu32VmixHandle)
 *
 * \brief
 * 		Close VMIX device associated with a handle
 *
 * \param	pu32VmixHandle			(Input) An open handle number of the VMIX device
 *
 * 
 * \retval	ERROR_NO_ERROR				error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 */
 
 ErrorCode DRV_VMIX_Term(DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_VMIX_Term(DRV_DeviceNameType DeviceName, bool b8Force)
 *
 * \brief
 * 		Terminate the VMIX device driver
 *
 * \param 	DeviceName							(Input)  Device Name 
 * \param	b8Force								(Input) Force terminate the VMIX or not
 *
 * \retval	ERROR_NO_ERROR						no error
 * \retval	EN_DRV_VMIX_ERR_HANDLE_NOT_CLOSED	Handle is not closed
 * \retval	ERROR_INITIALISED					The driver is not initialized
 * \retval	ERROR_INVALID_HANDLE		        Handle is not valid
 *
 */
 
ErrorCode DRV_VMIX_SetMode(u32 u32VmixHandle, EN_DRV_VMIXMODE enVmixMode);
/*!\fn DRV_VMIX_SetMode(u32 u32VmixHandle, EN_DRV_VMIXMODE enVmixMode)
 *
 * \brief
 * 		Set the VMIX Mode associated with a handle
 *
 * \param	u32VmixHandle			(Input) An open handle number of the VMIX device
 * \param	enVmixMode				(Input) The Mix mode of Compositor
 *
 * 
 * \retval	ERROR_NO_ERROR				error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 * \retval	EN_DRV_VMIX_ERR_HANDLE_USED	Handle is used

 */

ErrorCode DRV_VMIX_GetMode(u32 u32VmixHandle, PEN_DRV_VMIXMODE penVmixMode);
/*!\fn DRV_VMIX_GetMode(u32 u32VmixHandle, PEN_DRV_VMIXMODE penVmixMode)
 *
 * \brief
 * 		Get the VMIX Mode associated with a handle
 *
 * \param	u32VmixHandle			(Input) An open handle number of the VMIX device
 * \param	penVmixMode				(Output) The Mix mode of Compositor
 *
 * 
 * \retval	ERROR_NO_ERROR				error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 */
 

ErrorCode DRV_VMIX_SetBackgroundColor(u32 u32VmixHandle, u32 u32YUVColor);
/*!\fn ErrorCode DRV_VMIX_SetBackgroundColor(u32 u32VmixHandle, u32 u32YUVColor)
 *
 * \brief
 * 		Set the background color of VMIX
 *
 * \param	u32VmixHandle			(Input) An open handle number of the VMIX device
 * \param	u32YUVColor			    (Input) set the color value 
 *
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_INVALID_HANDLE	Handle is not valid
 */
 
ErrorCode DRV_VMIX_GetBackgroundColor(u32 u32VmixHandle, u32* pu32YUVColor);
/*!\fn ErrorCode DRV_VMIX_GetBackgroundColor(u32 u32VmixHandle, u32* pu32YUVColor)
 *
 * \brief
 * 		Get the background color of VMIX
 *
 * \param	u32VmixHandle			(Input) An open handle number of the VMIX device
 * \param	pu32YUVColor			(Output) get the color value
 *
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_INVALID_HANDLE	Handle is not valid
 */
 
#ifdef __cplusplus
}
#endif
 
#endif //#ifndef __DRV_VMIX_H__

