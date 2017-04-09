//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide VEP Control 
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

#ifndef	__DRV_VEP_H__
#define	__DRV_VEP_H__

#include "def_type.h"
#include "def_err.h"

/*
 * Brief: DRV_VEP global define.
 */
#define DRV_VEP_CM_LOOKUP_TABLE_NUM                     (16)        /*!< The maximum Lookup Table number of Color Management        */
#define DRV_VEP_YHIST_DISTRIBUTION_ITEM_NUM             (32)        /*!< The maximum distrbution number of luminance                */
#define DRV_VEP_IGAMMA_TABLE_ITEM_NUM                   (33)        /*!< The maximum number of igamma table                         */

/*!
 * \brief 
 * VEP Error code definition.
 */
enum
{
	ERROR_VEP_DEV_NAME     = ERROR_BASE_DRV_VEP,		            /*!< Device Name Error                                         */
	ERROR_VEP_DEV_RESOURCE,		                                    /*!< VEP don't have device resource                            */
	ERROR_VEP_CLOSED_HANDLE,	                                    /*!< Input Handle is closed.                                   */
};

/**
 * \brief
 * enumurate to indicate the YUV_Sync operation mode
 */
typedef enum
{
    EN_DRV_VEP_YUV_SYNC_MODE_Y601CBCR219_TO_RGB255,                 /*!< Y601CbCr219 to RGB255                          */
    EN_DRV_VEP_YUV_SYNC_MODE_Y709CBCR219_TO_RGB255,                 /*!< Y601CbCr219 to RGB255                          */
    EN_DRV_VEP_YUV_SYNC_MODE_Y601CBCR255_TO_RGB255,                 /*!< Y601CbCr219 to RGB255                          */
    EN_DRV_VEP_YUV_SYNC_MODE_RGB255_TO_Y601CBCR255,                 /*!< RGB255 to Y601CbCr219                          */
    EN_DRV_VEP_YUV_SYNC_MODE_MANUAL,                                /*!< manual mode, need to config convert matrix     */
    EN_DRV_VEP_YUV_SYNC_MODE_NUM,  
}EN_DRV_VEP_YUV_SYNC_MODE;

/**
 * \brief
 * enumurate to indicate the NCV block size
 */
typedef enum
{
    EN_DRV_VEP_NCV_BLOCK_SIZE_64,                                   /*!< Block size 64                      */
    EN_DRV_VEP_NCV_BLOCK_SIZE_32,                                   /*!< Block size 32                      */
    EN_DRV_VEP_NCV_BLOCK_SIZE_NUM,                                  
}EN_DRV_VEP_NCV_BLOCK_SIZE;

/**
 * \brief
 * enumurate to indicate the NCV Gaussian Table
 */
typedef enum
{
    EN_DRV_VEP_NCV_GAUSSIAN_TABLE_SIGMA_1,                          /*!< Gaussian distribution in sigma 1   */
    EN_DRV_VEP_NCV_GAUSSIAN_TABLE_SIGMA_2,                          /*!< Gaussian distribution in sigma 2   */
    EN_DRV_VEP_NCV_GAUSSIAN_TABLE_NUM,                                                   
}EN_DRV_VEP_NCV_GAUSSIAN_TABLE;

/**
 * \brief
 *  the VEP initial structure
 */
typedef struct
{
    u32                             u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_VEP_INIT_PARAMS, *PST_DRV_VEP_INIT_PARAMS;

/**
 * \brief
 *  the VEP terminate structure
 */
typedef struct 
{
    bool                           b8Force;                        /*!< Force terminate VEP	                */
} ST_DRV_VEP_TERM_PARAMS, *PST_DRV_VEP_TERM_PARAMS;

/**
 * \brief
 *  the VEP open structure
 */
typedef struct
{
    u32                             u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_VEP_OPEN_PARAMS, *PST_DRV_VEP_OPEN_PARAMS;

/**
 * \brief
 *  the VEP query info structure
 */
typedef struct
{
    bool                           b8Sharpness;                    /*!< Sharpness Enable(TRUE)/Disable(FALSE)          */
    bool                           b8GainOffset;                   /*!< Gain Offset Enable(TRUE)/Disable(FALSE)        */
    bool                           b8YuvSync;                      /*!< YUV Sync Enable(TRUE)/Disable(FALSE)           */
    bool                           b8ColorManagement;              /*!< Color Management Enable(TRUE)/Disable(FALSE)   */
    bool                           b8Yhist;                        /*!< Y-histogram Enable(TRUE)/Disable(FALSE)        */
    bool                           b8Igamma;                       /*!< Igamma Enable(TRUE)/Disable(FALSE)             */
    bool                           b8Ncv;                          /*!< NVC Enable(TRUE)/Disable(FALSE)                */
}ST_DRV_VEP_QUERY_INFO, *PST_DRV_VEP_QUERY_INFO;

/**
 * \brief
 *  the Convert matrix config structure
 */
typedef struct
{
    bool                           b8OffsetEnable;                 /*!< Offset Enable/Disable                                  */
    u16                             u16C00;                         /*!< Coefficient 00, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C01;                         /*!< Coefficient 01, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C02;                         /*!< Coefficient 02, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C10;                         /*!< Coefficient 10, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C11;                         /*!< Coefficient 11, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C12;                         /*!< Coefficient 12, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C20;                         /*!< Coefficient 20, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C21;                         /*!< Coefficient 21, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16C22;                         /*!< Coefficient 22, Maximum Value is 0x7FFF, 15bit=s2.12   */
    u16                             u16Offset0;                     /*!< Offset 0, Maximum Value is 1024, 12bit=s11.0           */
    u16                             u16Offset1;                     /*!< Offset 1, Maximum Value is 1024, 12bit=s11.0           */
    u16                             u16Offset2;                     /*!< Offset 2, Maximum Value is 1024, 12bit=s11.0           */
}ST_DRV_VEP_YUV_SYNC_MATRIX, *PST_DRV_VEP_YUV_SYNC_MATRIX;

/**
 * \brief
 *  the Sharpness config structure
 */
typedef struct
{
    u32                             u32Ctrl01;                      /*!< Control Value 01                       */
    u32                             u32Ctrl02;                      /*!< Control Value 02                       */
    u32                             u32Ctrl03;                      /*!< Control Value 03                       */
    u32                             u32Ctrl04;                      /*!< Control Value 04                       */
    u32                             u32Ctrl05;                      /*!< Control Value 05                       */
}ST_DRV_VEP_SHARPNESS_CFG_PARAMS, *PST_DRV_VEP_SHARPNESS_CFG_PARAMS;

/**
 * \brief
 *  the Gain Offset config structure
 */
typedef struct
{
    u8                              u8Gain0;                        /*!< Gain 0                                 */
    u8                              u8Gain1;                        /*!< Gain 1                                 */
    u8                              u8Gain2;                        /*!< Gain 2                                 */
    u8                              u8Offset0;                      /*!< Offset 0                               */
    u8                              u8Offset1;                      /*!< Offset 1                               */
    u8                              u8Offset2;                      /*!< Offset 2                               */
}ST_DRV_VEP_GAIN_OFFSET_CFG_PARAMS, *PST_DRV_VEP_GAIN_OFFSET_CFG_PARAMS;

/**
 * \brief
 *  the YUV_Sync config structure
 */
typedef struct
{
    EN_DRV_VEP_YUV_SYNC_MODE        enMode;                         /*!< Operation Mode                         */
    ST_DRV_VEP_YUV_SYNC_MATRIX      stMatrix;                       /*!< Convert Matrix                         */
}ST_DRV_VEP_YUV_SYNC_CFG_PARAMS, *PST_DRV_VEP_YUV_SYNC_CFG_PARAMS;

/**
 * \brief
 *  the Color Management lookup table structure
 */
typedef struct
{
    bool                           b8Enable;                       /*!< Lookup Table Enable/Disable            */    
    u8                              u8ColorOriginalAxis;            /*!< Color Oriiginal Axis                   */
    u8                              u8ColorMapAxis;                 /*!< Color Map Axis                         */
    s8                              s8SaturationMapAxis;            /*!< Saturation Map Axis, Range : -64 ~ 64  */
}ST_DRV_VEP_CM_LOOKUP_TABLE, *PST_DRV_VEP_CM_LOOKUP_TABLE;

/**
 * \brief
 *  the Color Management config structure
 */
typedef struct
{
    u8                              u8MaxSaturationOffset;                          /*!< Maximum Saturation offset, Range : 0 ~ 7   */
    ST_DRV_VEP_CM_LOOKUP_TABLE      astLookupTable[DRV_VEP_CM_LOOKUP_TABLE_NUM];    /*!< Lookup Table                               */
}ST_DRV_VEP_CM_CFG_PARAMS, *PST_DRV_VEP_CM_CFG_PARAMS;

/**
 * \brief
 *  the Y-Histogram config structure
 */
typedef struct
{
    u32                             au32Luminance[DRV_VEP_YHIST_DISTRIBUTION_ITEM_NUM]; /*!< Luminance data   */
}ST_DRV_VEP_YHIST_QUERY_INFO, *PST_DRV_VEP_YHIST_QUERY_INFO;

/**
 * \brief
 *  the Igamma config structure
 */
typedef struct
{
    u16                             au16Igamma[DRV_VEP_IGAMMA_TABLE_ITEM_NUM];          /*!< Igamma data        */
}ST_DRV_VEP_IGAMMA_CFG_PARAMS, *PST_DRV_VEP_IGAMMA_CFG_PARAMS;

/**
 * \brief
 *  the NCV config structure
 */
typedef struct
{
    EN_DRV_VEP_NCV_BLOCK_SIZE       enBlockSize;                                /*!< Block Size                                                 */
    EN_DRV_VEP_NCV_GAUSSIAN_TABLE   enGaussianTable;                            /*!< Gaussian Table                                             */
    u8                              u8BrightGain;                               /*!< Bright Gain                                                */
    u8                              u8DarkGain;                                 /*!< Dark Gain                                                  */
    bool                           b8SharpEnable;                              /*!< Loacl Sharp Enable(TRUE)/Disable(FALSE)                    */
    u8                              u8SharpBrightGain;                          /*!< Sharp Bright Gain, take effect when b8SharpEnable = TRUE   */
    u8                              u8SharpDarkGain;                            /*!< Sharp Dark Gain, take effect when b8SharpEnable = TRUE     */
}ST_DRV_VEP_NCV_CFG_PARAMS, *PST_DRV_VEP_NCV_CFG_PARAMS;


//function define
u8* DRV_VEP_GetVersion (void);
/*!\fn u8* DRV_VEP_GetVersion (void)
 * \brief 
 *		Get the VEP's Version number string	   
 *
 * 
 * \return VEP Version String
 * 
 */

ErrorCode DRV_VEP_Init (DRV_DeviceNameType DeviceName, PST_DRV_VEP_INIT_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_Init (DRV_DeviceNameType DeviceName, PST_DRV_VEP_INIT_PARAMS pstParams)
 * \brief 
 *		Initial the VEP with ST_DRV_VEP_INIT_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Init parameter
 * 
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success	
 * \retval ERROR_VEP_DEV_RESOURCE			VEP don't have device resource	
 * \retval ERROR_BAD_PARAMETER	            Parameter error 
 * \retval ERROR_INITIALISED	             already Init.
 * 
 */

ErrorCode DRV_VEP_Term (DRV_DeviceNameType DeviceName, PST_DRV_VEP_TERM_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_Term (DRV_DeviceNameType DeviceName, PST_DRV_VEP_TERM_PARAMS pstParams)
 * \brief 
 *		Terminate the VEP with ST_DRV_VEP_TERM_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Term parameter
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            VEP not Init.
 *
 */

ErrorCode DRV_VEP_Open (DRV_DeviceNameType DeviceName, PST_DRV_VEP_OPEN_PARAMS pstParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_VEP_Open (DRV_DeviceNameType DeviceName, PST_DRV_VEP_OPEN_PARAMS pstParams, u32* pu32Handle)
 * \brief 
 *		Open the VEP and associate it with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_NO_FREE_HANDLE             Resouce empty
 * \retval ERROR_INITIALISED	            VEP not Init.
 */

ErrorCode DRV_VEP_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_VEP_Close (u32* pu32Handle)
 * \brief 
 *		Close the VEP associate with a handle
 *
 * \param pu32Handle		                (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_Query (DRV_DeviceNameType DeviceName, PST_DRV_VEP_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_VEP_Query (DRV_DeviceNameType DeviceName, PST_DRV_VEP_QUERY_INFO pstInfo)
 * \brief 
 *		Query the VEP information/	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstInfo		                    (Output) Query info.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_SHARPNESS_Config (u32 u32Handle, PST_DRV_VEP_SHARPNESS_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_SHARPNESS_Config (u32 u32Handle, PST_DRV_VEP_SHARPNESS_CFG_PARAMS pstParams)
 * \brief 
 *		Config the Sharpness /	
 *
 * \param u32Handle		                    (Input)  VEP Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_SHARPNESS_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_SHARPNESS_Enable (u32 u32Handle)
 * \brief 
 *		Enable the Sharpness
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_SHARPNESS_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_SHARPNESS_Disable (u32 u32Handle)
 * \brief 
 *		Disable the Sharpness
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_GAIN_OFFSET_Config (u32 u32Handle, PST_DRV_VEP_GAIN_OFFSET_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_GAIN_OFFSET_Config (u32 u32Handle, PST_DRV_VEP_GAIN_OFFSET_CFG_PARAMS pstParams)
 * \brief 
 *		Config the Gain Offset /	
 *
 * \param u32Handle		                    (Input)  VEP Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_GAIN_OFFSET_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_GAIN_OFFSET_Enable (u32 u32Handle)
 * \brief 
 *		Enable the Gain Offset
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_GAIN_OFFSET_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_GAIN_OFFSET_Disable (u32 u32Handle)
 * \brief 
 *		Disable the Gain Offset
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_YUV_SYNC_Config (u32 u32Handle, PST_DRV_VEP_YUV_SYNC_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_YUV_SYNC_Config (u32 u32Handle, PST_DRV_VEP_YUV_SYNC_CFG_PARAMS pstParams)
 * \brief 
 *		Config the YUV_Sync /	
 *
 * \param u32Handle		                    (Input)  VEP Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_YUV_SYNC_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_YUV_SYNC_Enable (u32 u32Handle)
 * \brief 
 *		Enable the YUV_Sync
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_YUV_SYNC_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_YUV_SYNC_Disable (u32 u32Handle)
 * \brief 
 *		Disable the YUV_Sync
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_CM_Config (u32 u32Handle, PST_DRV_VEP_CM_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_CM_Config (u32 u32Handle, PST_DRV_VEP_CM_CFG_PARAMS pstParams)
 * \brief 
 *		Config the Color Management /	
 *
 * \param u32Handle		                    (Input)  VEP Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_CM_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_CM_Enable (u32 u32Handle)
 * \brief 
 *		Enable the Color Management
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_CM_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_CM_Disable (u32 u32Handle)
 * \brief 
 *		Disable the Color Management
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_YHIST_Query (u32 u32Handle, PST_DRV_VEP_YHIST_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_VEP_YHIST_Query (u32 u32Handle, PST_DRV_VEP_YHIST_QUERY_INFO pstInfo)
 * \brief 
 *		Query the Y-Histogram informataion/	
 *
 * \param u32Handle		                    (Input)  VEP Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_YHIST_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_YHIST_Enable (u32 u32Handle)
 * \brief 
 *		Enable the Y-Histogram
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_YHIST_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_YHIST_Disable (u32 u32Handle)
 * \brief 
 *		Disable the Y-Histogram
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_IGAMMA_Config (u32 u32Handle, PST_DRV_VEP_IGAMMA_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_IGAMMA_Config (u32 u32Handle, PST_DRV_VEP_IGAMMA_CFG_PARAMS pstParams)
 * \brief 
 *		Config the Igamma /	
 *
 * \param u32Handle		                    (Input)  VEP Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_IGAMMA_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_IGAMMA_Enable (u32 u32Handle)
 * \brief 
 *		Enable the Igamma
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_IGAMMA_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_IGAMMA_Disable (u32 u32Handle)
 * \brief 
 *		Disable the Igamma
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_NCV_Config (u32 u32Handle, PST_DRV_VEP_NCV_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_VEP_NCV_Config (u32 u32Handle, PST_DRV_VEP_NCV_CFG_PARAMS pstParams)
 * \brief 
 *		Config the NCV(Natural Clear Vision) /	
 *
 * \param u32Handle		                    (Input)  VEP Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_VEP_NCV_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_NCV_Enable (u32 u32Handle)
 * \brief 
 *		Enable the NCV(Natural Clear Vision)
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_VEP_NCV_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_VEP_NCV_Disable (u32 u32Handle)
 * \brief 
 *		Disable the NCV(Natural Clear Vision)
 *
 * \param u32Handle		                    (Input)  VEP Handle
 *
 * \return VEP Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_VEP_CLOSED_HANDLE	        Closed handle
 */

#endif //#ifndef	__DRV_VEP_H__
