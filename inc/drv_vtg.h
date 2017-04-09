//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide VTG Control
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


#ifndef __DRV_VTG_H__
#define __DRV_VTG_H__
#include "def_type.h"
#include "def_err.h"
#include "drv_layer.h"


/*
 * Brief: DRV_VTG global define.
 */
#define VTG_MAX_DEV_NUM  	1   /*!< The maximum device number of vtg module        */
#define VTG_MAX_HANDLE		1   /*!< The maximum handle number of vtg module        */

//#define NO_BORDER_FUNCTION       /*!< Disable Main/Picture Border */

/*!
 * \brief 
 * VTG Error code definition.
 */
enum
{
    ERROR_VTG_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_VTG,	    /*!< Operation invalid, because handle not close*/
    ERROR_VTG_UNKNOW_DEVICE,							    /*!< Invalid device name */
};

/**
 * \brief
 * enumurate to indicate the VTG timing mode
 */
typedef enum STVTG_TimingMode_e
{

    EN_DRV_VTG_TIMING_NONE = 0,
    EN_DRV_VTG_TIMING_HDMODE = 0x1000,      

    EN_DRV_VTG_TIMING_1080P60000_148500,  /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080P59940_148352,  /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080P50000_148500,  /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080P30000_74250,    /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080P29970_74176,    /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080P25000_74250,    /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080P24000_74250,    /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080P23976_74176,    /*!< 1920x1080P */
    EN_DRV_VTG_TIMING_1080I60000_74250,    /*!< 1920x1080I */
    EN_DRV_VTG_TIMING_1080I59940_74176,    /*!< 1920x1080I */
    EN_DRV_VTG_TIMING_1080I50000_74250,    /*!< 1920x1080I */
    EN_DRV_VTG_TIMING_720P60000_74250,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P59940_74176,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P50000_74250,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P30000_74250,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P29970_74176,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P25000_74250,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P24000_74176,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P23976_74176,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P24000_59400,      /*!< 1280x720P */
    EN_DRV_VTG_TIMING_720P23976_59400,      /*!< 1280x720P */

    EN_DRV_VTG_TIMING_SDMODE = 0x2000,
 
    EN_DRV_VTG_TIMING_576I50000_13500_PAL,       /*!< 720x576I */
    EN_DRV_VTG_TIMING_576P50000_27000_PAL,       /*!< 720x576P */
    EN_DRV_VTG_TIMING_480I60000_13514_NTSC,     /*!< 720x480I */
    EN_DRV_VTG_TIMING_480I59940_13500_NTSC,     /*!< 720x480I */
    EN_DRV_VTG_TIMING_480P60000_27027_NTSC,    /*!< 720x480P */
    EN_DRV_VTG_TIMING_480P59940_27000_NTSC,    /*!< 720x480P */  
    EN_DRV_VTG_TIMING_480P60000_24570,              /*!< 640x480P */
    EN_DRV_VTG_TIMING_480P59940_24545,              /*!< 640x480P */
    EN_DRV_VTG_TIMING_480P60000_25200,              /*!< 640x480P */
    EN_DRV_VTG_TIMING_480P59940_25175,              /*!< 640x480P */
    
} EN_DRV_VTG_TIMING, *PEN_DRV_VTG_TIMING;

/*!
 * \brief
 * enumurate to indicate the VTG event type
 */
typedef enum
{
    EVENT_VTG_VSYNC_INT,                        /*!< The event type for vsync interrupt	    */
    EVENT_VTG_CHANGETIMING,                 /*!< The event type for change vtg timing	    */
    EVENT_VTG_CHANGERATE,                    /*!< The event type for change output rate	    */
    EVENT_VTG_NUM,
}EN_DRV_VTG_EVENT_TYPE;

/*!
 * \brief
 * enumurate to indicate the PI2 line skip mode (316 IC Function)
 */
typedef enum
{
    EN_PI2_LINE_SKIP_MODE_NORMAL,
    EN_PI2_LINE_SKIP_MODE_NORMAL1,
    EN_PI2_LINE_SKIP_MODE_ODD,
    EN_PI2_LINE_SKIP_MODE_EVEN,
}EN_PI2_LINE_SKIP_MODE;


/*!
 * \brief
 * the timing information structure for VTG module (316 IC Function)
 */
typedef struct 
{
    ST_LAYER_WinParam stScreen;

    u16 u16Total_HSize;
    u16 u16Total_VSize;    
    u16 u8HSyncPulseW;
    u16 u8VSyncPulseW;				/*!< A memory pool handle for VTG module	*/
}ST_VTG_TimingInfo, *PST_VTG_TimingInfo;

/*!
 * \brief
 * the initial structure includes the memory pool handle for VTG module
 */
typedef struct 
{
    os_mempool_handle u32MemPoolHandle;				/*!< A memory pool handle for VTG module	*/
}ST_VTG_Init, *PST_VTG_Init;

/*!
 * \brief
 * the open structure includes the VTG timing parameters
 */
typedef struct 
{
    u32 u32EVTHandle;                                       /*!< A event handle for VTG module	    */
    EN_DRV_VTG_TIMING enVTGTiming;              /*!< The VTG timing mode	    */
}ST_VTG_Open, *PST_VTG_Open;

/*!
 * \brief
 * the boundary structure
 */
typedef struct 
{
    u16 u16Left;                        /*!< A left boundary for which VTG timing mode	    */
    u16 u16Right;                       /*!< A right boundary for which VTG timing mode     */
    u16 u16Top;                         /*!< A top boundary for which VTG timing mode	    */
    u16 u16Bottom;                  /*!< A bottom boundary for which VTG timing mode	*/
} ST_VTG_BGActiveArea, *PST_VTG_BGActiveArea;


ErrorCode DRV_VTG_Init(DRV_DeviceNameType DeviceName, PST_VTG_Init pstInit);
/*!\fn ErrorCode DRV_VTG_Init(DRV_DeviceNameType DeviceName, PST_VTG_Init pstInit)
 *
 * \brief
 * 		Initialize VTG device with pstInit setting
 *
 * \param 	DeviceName						(Input)  Device Name 
 * \param	pstInit							(Input) Pointer to the initialization parameter structure
 *
 * \retval	ERROR_NO_ERROR						No error
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_NO_MEMORY					The memory allocate is fail 
 * \retval	ERROR_INITIALISED				       The driver is not initialized or already initialized
 * \retval	ERROR_NO_FREE_HANDLE				No free handle for the device
 *
 */

ErrorCode DRV_VTG_Term(DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_VTG_Term(DRV_DeviceNameType DeviceName, bool b8Force)
 *
 * \brief
 * 		Terminate the VTG device driver
 *
 * \param 	DeviceName							(Input)  Device Name 
 * \param	b8Force								(Input) Force terminate the VTG or not
 *
 * \retval	ERROR_NO_ERROR							No error
 * \retval	ERROR_VTG_UNKNOW_DEVICE	              Invalid device name
 * \retval	ERROR_VTG_HANDLE_NOT_CLOSED		Handle is not closed
 *
 */

ErrorCode DRV_VTG_Open (DRV_DeviceNameType DeviceName, PST_VTG_Open pstOpen, u32 *pu32VtgHandle);
/*!\fn ErrorCode DRV_VTG_Open (DRV_DeviceNameType DeviceName, PST_VTG_Open pstOpen, u32 *pu32VtgHandle)
 *
 * \brief
 * 		Open the VTG device and associate it with a handle
 *
 * \param 	DeviceName		(Input)  Device Name 
 * \param	pstOpen			(Input) Pointer to the opening parameter structure
 * \param	pu32VtgHandle	(Output) The returned handle of the opened device driver
 *
 * \retval	ERROR_NO_ERROR					    No error
 * \retval	ERROR_VTG_UNKNOW_DEVICE	    Invalid device name
 * \retval	ERROR_BAD_PARAMETER			    Bad parameter passed
 * \retval	ERROR_NO_FREE_HANDLE			    No free handle for the device
 */

ErrorCode DRV_VTG_Close (u32* pu32VtgHandle);
/*!\fn ErrorCode DRV_VTG_Close(u32* pu32VtgHandle)
 *
 * \brief
 * 		Close VTG device associated with a handle
 *
 * \param	pu32VtgHandle			(Input) An open handle number of the VTG device
 *
 * 
 * \retval	ERROR_NO_ERROR				No error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 */

ErrorCode DRV_VTG_SetMode(u32 u32VtgHandle, EN_DRV_VTG_TIMING enVTGTiming);
/*!\fn ErrorCode DRV_VTG_SetMode(u32 u32VtgHandle, EN_DRV_VTG_TIMING enVTGTiming)
 *
 * \brief
 * 		Configure the video timing mode for a VTG
 *
 * \param	u32VtgHandle			       (Input) An open handle number of the VTG device
 * \param	enVTGTiming				(Input) The VTG timing mode
 *
 * 
 * \retval	ERROR_NO_ERROR				No error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 */

ErrorCode DRV_VTG_GetMode(u32 u32VtgHandle, PEN_DRV_VTG_TIMING penVTGTiming, PST_VTG_BGActiveArea pstArea);
/*!\fn ErrorCode ErrorCode DRV_VTG_GetMode(u32 u32VtgHandle, PEN_DRV_VTG_TIMING penVTGTiming, PST_VTG_BGActiveArea pstArea)
 *
 * \brief
 * 		Retrieve the current video signal parameters and background layer active area for a VTG device
 *
 * \param	u32VtgHandle			       (Input) An open handle number of the VTG device
 * \param	penVTGTiming				(Output) The VTG timing mode
 * \param       pstArea                               (Output) Active area of background layer
 *
 * 
 * \retval	ERROR_NO_ERROR				No error
 * \retval	ERROR_INVALID_HANDLE		Handle is not valid
 */
 
ErrorCode DRV_VTG_GetVersion (u8 *pu8VersionNum);
/*!\fn ErrorCode DRV_VTG_GetVersion (u8 *pu8VersionNum)
 *
 * \brief
 * 		Get the Module Version number of VTG
 *
 * \param	pu8VersionNum			(Output) Version string of VTG
 *
 *
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRV_VTG_SetHDMIStatus(u32 u32VtgHandle,u8 u8HdmiStaus);
/*!\fn ErrorCode DRV_VTG_SetHDMIStatus(u32 u32VtgHandle,bool b8HdmiStaus)
 *
 * \brief
 *		Get the HDMI Staus for setting Background start position
 *
 * \param	u32VtgHandle		 (Input) An open handle number of the VTG device
 * \param	u8HdmiStaus			 (Input) Setting HDMI Status 
 *
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_BAD_PARAMETER 	Bad parameter passed
 */

bool DRV_VTG_IsTgenProgMode(void);
/*!\fn bool DRV_VTG_IsTgenProgMode(void)
 *
 * \brief
 *      Check if VTG's timing is progress scan or not
 *
 * \param   none
 *
 * \retval  bool              progressive scan or not
 */


#endif //#ifndef __DRV_VTG_H__

