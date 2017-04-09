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

#ifndef __DRV_BLIT_H__
#define __DRV_BLIT_H__

#ifdef __cplusplus
extern  "C"
{
#endif

#include "os.h"
#include "def_type.h"
#include "def_err.h"
#include "drv_layer.h"



/**
 * \brief
 * enumerate to indicate the error of operation
 */
typedef enum
{
    EN_DRV_BLIT_ERR_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_BLIT,	/*!< Operation invalid, because handle not close*/
    EN_DRV_BLIT_ERR_UNKNOW_DEVICE,								/*!< Invalid device name */
    EN_DRV_BLIT_ERR_TIMEOUT,                                    /*!< setting over the time */
    EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE							/*!< Un-Support Device */
} EN_DRV_BLIT_ERROR;

/**
 * \brief
 * enumerate to indicate the blit engines
 */
typedef enum
{
    EN_DRV_BLIT_ENGINE_GPU,       /*!< GPU engines */
    EN_DRV_BLIT_ENGINE_JPU,       /*!< JPU engines */
    EN_DRV_BLIT_ENGINE_NUM,       /*!< total number*/
} EN_DRV_BLIT_ENGINE, *PEN_DRV_BLIT_ENGINE;

/**
 * \brief
 * enumerate to indicate the GPU copy type
 */
typedef enum
{
    EN_DRV_BLIT_GPUCPY = 0x1,    /*!< GPU bitmap coy */
    EN_DRV_BLIT_GPUCPY_ALPHA,    /*!< GPU bitmap coy with alpha blending*/
    EN_DRV_BLIT_GPUCPY_LOGICAL,	 /*!< GPU bitmap coy with logical operation*/
    EN_DRV_BLIT_GPUCPY_UNKNOWN   /*!< none */
} EN_DRV_BLIT_GPUCPY_TYPE;

/**
 * \brief
 * enumerate to indicate the logical copy type of the GPU copy
 */
typedef enum
{
    EN_DRV_BLIT_LOGICAL_AND = 0x0, /*!< logical operation - AND*/
    EN_DRV_BLIT_LOGICAL_OR,        /*!< logical operation - OR*/
    EN_DRV_BLIT_LOGICAL_XOR,       /*!< logical operation - XOR*/
    EN_DRV_BLIT_LOGICAL_INV,       /*!< logical operation - INV*/
    EN_DRV_BLIT_LOGICAL_NUM        /*!< logical operation total number*/
} EN_DRV_BLIT_LOGICAL_MODE;

/**
 * \brief
 * enumerate to indicate the horizontal scan order
 */
typedef enum
{
    EN_DRV_BLIT_HSCAN_ORDER_LTOR = 0x0, /*!< horizontal scan order - left to right*/
    EN_DRV_BLIT_HSCAN_ORDER_RTOL        /*!< horizontal scan order - right to left*/
} EN_DRV_BLIT_HSCAN_ORDER;

/**
 * \brief
 * enumerate to indicate the vertical scan order
 */
typedef enum
{
    EN_DRV_BLIT_VSCAN_ORDER_TTOB = 0x0, /*!< vertical scan order - top to bottom*/
    EN_DRV_BLIT_VSCAN_ORDER_BTOT        /*!< vertical scan order - bottom to top*/
} EN_DRV_BLIT_VSCAN_ORDER;

/**
 * \brief
 * enumerate to indicate the flip/rotate operation mode
 */
typedef enum
{
    EN_DRV_BLIT_FLIPROTATE_ORIGINAL,        /*!< flip/rotate operation mode - original*/
    EN_DRV_BLIT_FLIPROTATE_90CLOCK,         /*!< flip/rotate operation mode - 90 clockwise*/
    EN_DRV_BLIT_FLIPROTATE_180CLOCK,        /*!< flip/rotate operation mode - 180 clockwise*/
    EN_DRV_BLIT_FLIPROTATE_270CLOCK,        /*!< flip/rotate operation mode - 270 clockwise*/
    EN_DRV_BLIT_FLIPROTATE_FLIP,	        /*!< flip/rotate operation mode - flip horizontally*/
    EN_DRV_BLIT_FLIPROTATE_FLIP_90CLOCK,	/*!< flip/rotate operation mode - flip horizontally + 90 clockwise*/
    EN_DRV_BLIT_FLIPROTATE_FLIP_180CLOCK,	/*!< flip/rotate operation mode - flip horizontally + 180 clockwise*/
    EN_DRV_BLIT_FLIPROTATE_FLIP_270CLOCK,	/*!< flip/rotate operation mode - flip horizontally + 270 clockwise*/
    EN_DRV_BLIT_FLIPROTATE_NUM              /*!< flip/rotate operation mode total number*/
} EN_DRV_BLIT_FLIPROTATE_TYPE;

/**
 * \brief
 * enumerate to indicate the JPU domain
 */
typedef enum
{
    EN_DRV_BLIT_JPU_DOMAIN_Y,   /*!< Y domain*/
    EN_DRV_BLIT_JPU_DOMAIN_UV,  /*!< UV domain*/
    EN_DRV_BLIT_JPU_DOMAIN_NUM  /*!< total number*/
} EN_DRV_BLIT_JPU_DOMAIN;

/**
 * \brief
 * enumerate to indicate the JPU color mode
 */
typedef enum
{
    EN_DRV_BLIT_JPU_COLOR_YUV420,  	/*!< 420 Color Mode*/
    EN_DRV_BLIT_JPU_COLOR_YUV422V,  /*!< 422V Color Mode*/
    EN_DRV_BLIT_JPU_COLOR_YUV422H,  /*!< 422H Color Mode*/
    EN_DRV_BLIT_JPU_COLOR_YUV444,   	/*!< 444 Color Mode*/
    //only for 320
    EN_DRV_BLIT_JPU_COLOR_8,   	/*!< 8Bit Mode*/
	EN_DRV_BLIT_JPU_COLOR_16, 	/*!< 16Bit Mode*/

	EN_DRV_BLIT_JPU_COLOR_ARGB8888,  
    EN_DRV_BLIT_JPU_COLOR_RGB565,
    EN_DRV_BLIT_JPU_COLOR_ARGB1555,
    EN_DRV_BLIT_JPU_COLOR_ARGB4444,
    EN_DRV_BLIT_JPU_COLOR_RGBA8888,
    EN_DRV_BLIT_JPU_COLOR_RGBA5551,
    EN_DRV_BLIT_JPU_COLOR_RGBA4444,
	EN_DRV_BLIT_JPU_COLOR_AYUV8888,
	EN_DRV_BLIT_JPU_COLOR_AYUV1555,
	EN_DRV_BLIT_JPU_COLOR_YUV655,
	EN_DRV_BLIT_JPU_COLOR_YUV888,
	EN_DRV_BLIT_JPU_COLOR_BGR888,
	
}EN_DRV_BLIT_JPU_COLOR;


//only for 320
/**
 * \brief
 * enumerate to indicate the GPU Scale Mode
 */
typedef enum
{
	EN_DRV_BLIT_2_TAB_SC = 0,					
	EN_DRV_BLIT_4_TAB_SC,					
	EN_DRV_BLIT_NRST_SC,					    
	EN_DRV_BLIT_2_TAB_LP,					
	EN_DRV_BLIT_4_TAB_LP,					
	EN_DRV_BLIT_2_TAB_LP_4_TAB_SC,			
	EN_DRV_BLIT_4_TAB_LP_2_TAB_SC	

} EN_DRV_BLIT_GPU_SCALE_MODE;

/**
 * \brief
 * enumerate to indicate the GPU Blending Mode
 */
typedef enum
{
	EN_DRV_BLIT_Blending_PD_NONE = 0,					
	EN_DRV_BLIT_Blending_PD_CLEAR,					
	EN_DRV_BLIT_Blending_PD_SRC, 					
	EN_DRV_BLIT_Blending_PD_SRC_OVER,					
	EN_DRV_BLIT_Blending_PD_DST_OVER,					
	EN_DRV_BLIT_Blending_PD_SRC_IN,					
	EN_DRV_BLIT_Blending_PD_DST_IN,					
	EN_DRV_BLIT_Blending_PD_SRC_OUT,					
	EN_DRV_BLIT_Blending_PD_DST_OUT,
	EN_DRV_BLIT_Blending_PD_SRC_ATOP,
	EN_DRV_BLIT_Blending_PD_DST_ATOP,
	EN_DRV_BLIT_Blending_PD_XOR,
	EN_DRV_BLIT_Blending_PD_ADD,
	
	EN_DRV_BLIT_Blending_DFB_NONE=0x10,					
	EN_DRV_BLIT_Blending_DFB_ZERO,					
	EN_DRV_BLIT_Blending_DFB_ONE,					
	EN_DRV_BLIT_Blending_DFB_SRCCOLOR,					
	EN_DRV_BLIT_Blending_DFB_INVSRCCOLOR,					
	EN_DRV_BLIT_Blending_DFB_SRCALPHA, 				
	EN_DRV_BLIT_Blending_DFB_INVSRCALPHA, 				
	EN_DRV_BLIT_Blending_DFB_DESTALPHA,					
	EN_DRV_BLIT_Blending_DFB_INVDESTALPHA,
	EN_DRV_BLIT_Blending_DFB_DESTCOLOR,
	EN_DRV_BLIT_Blending_DFB_INVDESTCOLOR,
	EN_DRV_BLIT_Blending_DFB_SRCALPHASAT,

} EN_DRV_BLIT_GPU_Blending_MODE;
//end for 320

/**
 * \brief
 *  union to indicate the different color type
 */
typedef union
{
    u8	u8bit[4];       /*!< 8 bit*/
    u16  u16bit[2];     /*!< 16 bit*/
    u32  u32bit;        /*!< 32 bit*/
} unLong, *punLong;

/*!
 * \brief
 * the initial structure includes the BLIT initial setting
 */
typedef struct
{
    os_mempool_handle	u32MemPoolHandle;			/*!< A memory pool handle for BLIT module	*/
    EN_DRV_BLIT_ENGINE	enBlitEng;                  /*!< Blit engine*/
} ST_BLIT_Init, *PST_BLIT_Init;

/*!
 * \brief
 * the open structure includes the BLIT opening parameters
 */
typedef struct
{
    u32 u32Reserved;                                /*!< Reserved for future used */
} ST_BLIT_Open, *PST_BLIT_Open;

/**
 * \brief
 * the structure defines the GPU setting parameters
 */
typedef struct
{
    EN_DRV_LAYER_COLORMODE enColorMode;      /*!< color mode*/
    u32 u32BaseAdr;                          /*!< source base address or RLE top address*/
    u32 u32PaletteAdr;                       /*!< pattate address or RLE bottom address*/
    u32 u32OriWidth;                         /*!< screen width*/
    u32 u32OriHeight;                        /*!< screen height*/
    u32 u32PosX;                             /*!< position x*/
    u32 u32PosY;                             /*!< position y*/
    u32 u32Width;                            /*!< rectangle width*/
    u32 u32Height;                           /*!< rectangle height*/
} ST_BLIT_GPUParam, *PST_BLIT_GPUParam;

/**
 * \brief
 * the structure defines the JPU setting parameters
 */
typedef struct
{
    u32 u32BaseAdr;                         /*!< source base address*/
	u32 u32PosX;                            /*!< position x*/
    u32 u32PosY;                            /*!< position y*/
    u32 u32Width;                           /*!< width*/
    u32 u32Height;                          /*!< height*/
    u32 u32WindowWidth;                     /*!< windows*/
	//only for 320
	u32 u32BaseAdr_UV;
} ST_BLIT_JPUParam, *PST_BLIT_JPUParam;


/**
 * \brief
 * the structure defines the JPU fill rectangle parameters
 */
typedef struct
{
    EN_DRV_BLIT_JPU_DOMAIN 		enDomain;    /*!< JPU domain*/
    EN_DRV_BLIT_JPU_COLOR       enColor;      /*< JPU color mode*/
    ST_BLIT_JPUParam 			stParam;     /*!< JPU parameters*/
} ST_BLIT_RectJPUParam, *PST_BLIT_RectJPUParam;

/**
 * \brief
 * the structure defines the BLIT fill rectangle parameters
 */
typedef struct
{
    union
    {
        ST_BLIT_GPUParam 		stGpu;        /*!< GPU parameters*/
        ST_BLIT_RectJPUParam	stJpu;	      /*!< JPU fill rectangle parameters*/
    } Data;
    u32						u32FillData;      /*!< fill data value*/
} ST_BLIT_FillRectParam, *PST_BLIT_FillRectParam;

/**
 * \brief
 * the structure defines the BLIT copy rectangle parameters
 */
typedef struct
{
    ST_BLIT_GPUParam 			stGpuSrc;     /*!< GPU source parameters*/
    ST_BLIT_GPUParam 			stGpuDst;     /*!< GPU destination parameters*/
    EN_DRV_BLIT_GPUCPY_TYPE 	enGpuCpyType; /*!< GPU copy type*/
    EN_DRV_BLIT_HSCAN_ORDER	enHscan;          /*!< GPU horizontal scan order*/
    EN_DRV_BLIT_VSCAN_ORDER	enVscan;          /*!< GPU vertical scan order*/
    union
    {
        EN_DRV_BLIT_LOGICAL_MODE 	enLogic;      /*!< logical copy type*/
        u32							u32Alpha;	  /*!< Alpha value*/
    } Data;
    u32							u32ColorKey;      /*!< Color key*/
    bool						b8ColorKeyEn;	  /*!< Color key enable flag*/
	u8                          u8VsyncEn;         /*!< 1:Enable Vsync Trigger 0:Disable Vsync Trigger*/
	u32                         u32VsyncLine;      /*!< Setting Vsync Line*/	
} ST_BLIT_CPYRectParam, *PST_BLIT_CPYRectParam;


//only for 320
/**
 * \brief
 * the structure defines the GPU Scale Mode
 */
typedef struct
{
    EN_DRV_BLIT_GPU_SCALE_MODE	enHScanMode; /*!< GPU horizontal scan Mode*/
    EN_DRV_BLIT_GPU_SCALE_MODE	enVScanMode; /*!< GPU vertical scan Mode*/
} ST_BLIT_ScanModeParam, *PST_BLIT_ScanModeParam;

/**
 * \brief
 * the structure defines the GPU scale parameters
 */
typedef struct
{
    ST_BLIT_GPUParam 		stGpuSrc;             /*< GPU source parameter*/
    ST_BLIT_GPUParam		stGpuDst;             /*< GPU destination parameter*/
	ST_BLIT_ScanModeParam   stGPUScaleMode;       /*< GPU Scale Mode*/
	u8                      u8Rle;
	u8                      u8VsyncEn;            /*!< 1:Enable Vsync Trigger 0:Disable Vsync Trigger*/
	u32                     u32VsyncLine;         /*!< Setting Vsync Line*/	
} ST_BLIT_GPUScalingParam, *PST_BLIT_GPUScalingParam;

/**
 * \brief
 * the structure defines the BLIT Blending parameters
 */
typedef struct
{
    ST_BLIT_GPUParam 			stGpuSrc;     /*!< GPU source parameters*/
    ST_BLIT_GPUParam 			stGpuDst;     /*!< GPU destination parameters*/
    EN_DRV_BLIT_GPU_Blending_MODE	enBlendMode; /*!< GPU blending mode*/
	u32                         u32CaColor;    /*!< GPU constant alpha*/
	u32                         u32ColorKey;   /*!< GPU color key*/
	u8                          u8Rle;

} ST_BLIT_BlendParam, *PST_BLIT_BlendParam;


/**
 * \brief
 * the structure defines the BLIT RLE Encode parameters
 */
typedef struct 
{
	u32 u32BufferSize;    	/*!< Setting Output buffer size to check boundary*/
    u32 u32RLEncSize;      	/*!< Get Rle output size*/
	u8  u8InterlaceMode;	/*!< 0:Frame or 1:Interlace*/
	u32 u32RLEncBottomSize; /*!< Get Rle bottom filed output size*/
} ST_BLIT_RLEParam, *PST_BLIT_RLEParam;

//end for 320


/**
 * \brief
 * the structure defines the BLIT flip/rotate parameters
 */
typedef struct
{
    EN_DRV_BLIT_JPU_DOMAIN 			enDomain;    /*< JPU domain*/
    EN_DRV_BLIT_JPU_COLOR       	enColor;      /*< JPU color mode*/
    EN_DRV_BLIT_FLIPROTATE_TYPE 	enFRType;    /*< Flip/Rotate type*/
    ST_BLIT_JPUParam 				stJpuSrc;    /*< JPU source parameter*/
    ST_BLIT_JPUParam				stJpuDst;	 /*< JPU destination parameter*/
} ST_BLIT_FlipRotateParam, *PST_BLIT_FlipRotateParam;

/**
 * \brief
 * the structure defines the JPU copy parameters
 */
typedef struct
{
    EN_DRV_BLIT_JPU_DOMAIN 			enDomain;     /*< JPU domain*/
    EN_DRV_BLIT_JPU_COLOR       	enColor;      /*< JPU color mode*/
    ST_BLIT_JPUParam 				stJpuSrc;     /*< JPU source parameter*/
    ST_BLIT_JPUParam				stJpuDst;	  /*< JPU destination parameter*/
} ST_BLIT_JpuCpyParam, *PST_BLIT_JpuCpyParam;

/**
 * \brief
 * the structure defines the JPU scale parameters
 */
typedef struct
{
    EN_DRV_BLIT_JPU_DOMAIN enDomain;              /*< JPU domain*/
    EN_DRV_BLIT_JPU_COLOR  	enColor;              /*< JPU color mode*/
    ST_BLIT_JPUParam 		stJpuSrc;             /*< JPU source parameter*/
    ST_BLIT_JPUParam		stJpuDst;             /*< JPU destination parameter*/
} ST_BLIT_ScalingParam, *PST_BLIT_ScalingParam;

/**
 * \brief
 * the structure defines the GPU rgb to yuv parameters
 */
typedef struct
{
    EN_DRV_LAYER_COLORMODE 	enSrcColorMode;             /*!< color mode*/
    u32 						u32SrcBaseAdr;          /*!< source base address*/
    u32 						u32SrcWidth;            /*!< source width*/
    u32 						u32SrcHeight;           /*!< source height*/
    u32							u32DstBaseAdrY;         /*!< destination Y base address*/
    u32							u32DstBaseAdrC;         /*!< destination Chroma base address*/
    u32							u32DstPosX;             /*!< destination position x*/
    u32							u32DstPosY;             /*!< destination position y*/
    u32							u32DstWindowWidth;      /*!< destination windows*/
    bool                       b8ITU601;               /*!< ITU601 or ITU709 flag*/
} ST_BLIT_RGB2YUVParam, *PST_BLIT_RGB2YUVParam;

/**
 * \brief
 * the structure defines the source and destination information of the BLIT copy
 */
typedef struct
{
    u16 u16SrcPosX;         /*!< source position x*/
    u16 u16SrcPosY;         /*!< source position y*/
    u16 u16SrcWidth;        /*!< source width*/
    u16 u16SrcHeight;	    /*!< source height*/
    u16 u16DstPosX;         /*!< destination position x*/
    u16 u16DstPosY;         /*!< destination position y*/
    u16 u16DstWidth;        /*!< destination width*/
    u16 u16DstHeight;	    /*!< destination height*/
} ST_BLIT_CpySrcDstParam, *PST_BLIT_CpySrcDstParam;



/**
 * \brief
 * the structure defines the BLIT scan order parameters
 */
typedef struct
{
    EN_DRV_BLIT_HSCAN_ORDER	enHScanOrder; /*!< GPU horizontal scan order*/
    EN_DRV_BLIT_VSCAN_ORDER	enVScanOrder; /*!< GPU vertical scan order*/
} ST_BLIT_ScanLineParam, *PST_BLIT_ScanLineParam;


/**
 * \brief
 * the structure defines the BLIT JPU Blending parameters
 */
typedef struct
{
    ST_BLIT_JPUParam 			stJpuSrc;        /*!< JPU source parameters*/
    ST_BLIT_JPUParam 			stJpuDst;        /*!< JPU destination parameters*/
    EN_DRV_BLIT_JPU_DOMAIN 		enDomain;        /*< JPU domain*/
    EN_DRV_BLIT_JPU_COLOR  		enColor;         /*< JPU color mode*/
    EN_DRV_BLIT_GPU_Blending_MODE	enBlendMode; /*!< GPU blending mode*/
	u32                         u32CaColor;      /*!< JPU constant alpha*/
	u8                          u8Rle;

} ST_BLIT_JPU_BlendParam, *PST_BLIT_JPU_BlendParam;
//end for 320

/**
 * \brief
 * the structure defines the JPU scale parameters
 */
typedef struct
{
    EN_DRV_BLIT_JPU_DOMAIN enDomain;              /*< JPU domain*/
    EN_DRV_BLIT_JPU_COLOR  	enSrcColor;              /*< JPU color mode*/
    EN_DRV_BLIT_JPU_COLOR  	enDstColor;              /*< JPU color mode*/
    ST_BLIT_JPUParam 		stJpuSrc;             /*< JPU source parameter*/
    ST_BLIT_JPUParam		stJpuDst;             /*< JPU destination parameter*/
} ST_BLIT_JPU_FormatParam, *PST_BLIT_FormatParam;



ErrorCode DRV_BLIT_GetVersion (u8 *pu8VersionNum);
/*!\fn ErrorCode DRV_BLIT_GetVersion (u8 *pu8VersionNum)
 *
 * \brief
 * 		Get the Module Version number of BLIT
 *
 * \param	pu8VersionNum			(Output) Version string of BLIT
 *
 *
 * \retval	ERROR_NO_ERROR				no error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRV_BLIT_Init (DRV_DeviceNameType DeviceName, PST_BLIT_Init pstInit);
/*!\fn ErrorCode DRV_BLIT_Init (DRV_DeviceNameType DeviceName, PST_BLIT_Init pstInit)
 *
 * \brief
 * 		Initialize BLIT device with pstInit setting
 *
 * \param 	DeviceName		                		(Input)  Device Name
 * \param	pstInit							(Input) Pointer to the initialization parameter structure
 *
 * \retval	ERROR_NO_ERROR						no error
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE	Un-Support Device
 * \retval	ERROR_INITIALISED					The driver is not initialized
 * \retval	ERROR_NO_FREE_HANDLE				No free handle for the device
 *
 */

ErrorCode DRV_BLIT_Term (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_BLIT_Term (DRV_DeviceNameType DeviceName, bool b8Force)
 *
 * \brief
 * 		Terminate the BLIT device driver
 *
 * \param 	DeviceName		                		(Input)  Device Name
 * \param	b8Force							(Input) Force terminate the Blit or not
 *
 * \retval	ERROR_NO_ERROR							no error
 * \retval	EN_DRV_BLIT_ERR_HANDLE_NOT_CLOSED		Handle is not closed
 * \retval	ERROR_INVALID_HANDLE					Handle is not valid
 *
 */

ErrorCode DRV_BLIT_Open (DRV_DeviceNameType DeviceName, PST_BLIT_Open pstOpen, u32* pu32BlitHandle);
/*!\fn ErrorCode DRV_BLIT_Open (DRV_DeviceNameType DeviceName, PST_BLIT_Open pstOpen, u32* pu32BlitHandle)
 *
 * \brief
 * 		Open the BLIT device and associate it with a handle
 *
 * \param 	DeviceName		            (Input)  Device Name
 * \param	pstOpen			            (Input) Pointer to the opening parameter structure
 * \param	pu32BlitHandle	            (Output) The returned handle of the opened device driver
 *
 * \retval	ERROR_NO_ERROR					no error
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid
 * \retval	ERROR_BAD_PARAMETER			    Bad parameter passed
 * \retval	ERROR_NO_FREE_HANDLE			No free handle for the device
 */

ErrorCode DRV_BLIT_Close (u32* pu32BlitHandle);
/*!\fn ErrorCode DRV_BLIT_Close (u32* pu32BlitHandle)
 *
 * \brief
 * 		Close BLIT device associated with a handle
 *
 * \param	pu32BlitHandle			    (Input) An open handle number of the BLIT device
 *
 *
 * \retval	ERROR_NO_ERROR							    error
 * \retval	ERROR_INVALID_HANDLE					    Handle is not valid
 */

ErrorCode DRV_BLIT_GetWindowWidthAlignment(u8 *pu8AlignOfByte);
/*!\fn ErrorCode DRV_BLIT_GetWindowWidthAlignment(u8 *pu8AlignOfByte)
 *
 * \brief
 * 		Gets the GPU memory alignment size
 *
 * \param	pu8AlignOfByte				(Output) return the alignment size
 *
 * \retval	ERROR_NO_ERROR								error
  */


ErrorCode DRV_BLIT_GPU_FillRectangle(u32 u32BlitHandle, ST_BLIT_FillRectParam stFillRect);
/*!\fn ErrorCode DRV_BLIT_GPU_FillRectangle(u32 u32BlitHandle, ST_BLIT_FillRectParam stFillRect)
 *
 * \brief
 * 		Fill a rectangular portion of a bitmap with a specified color according to a specified blitting context
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stFillRect					(Input) The structure containing the Blit FillRect parameters
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 */

ErrorCode DRV_BLIT_GPU_Copy(u32 u32BlitHandle, ST_BLIT_CPYRectParam stCpyRect);
/*!\fn ErrorCode DRV_BLIT_GPU_Copy(u32 u32BlitHandle, ST_BLIT_CPYRectParam stCpyRect)
 *
 * \brief
 * 		Copy a rectangle from one bitmap to another bitmap.
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stCpyRect				    (Input) The structure containing the GPU copy rectangle parameters
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 */

ErrorCode DRV_BLIT_GPU_RGB2YUV(u32 u32BlitHandle, ST_BLIT_RGB2YUVParam stR2Y);
/*!\fn ErrorCode DRV_BLIT_GPU_RGB2YUV(u32 u32BlitHandle, ST_BLIT_RGB2YUVParam stR2Y)
 *
 * \brief
 * 		Transformation RGB to YUV from one bitmap to another video.
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stR2Y					    (Input) The structure containing the GPU RGB2YUV parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 */

ErrorCode DRV_BLIT_GPU_GetScanLineOrder(u32 u32BlitHandle, ST_BLIT_CpySrcDstParam stCpySrc, PST_BLIT_ScanLineParam pstScanLine);
/*!\fn ErrorCode DRV_BLIT_GPU_GetScanLineOrder(u32 u32BlitHandle, ST_BLIT_CpySrcDstParam stCpySrc, PST_BLIT_ScanLineParam pstScanLine)
 *
 * \brief
 * 		Check the scan line order of the copy rectangle DMA(only for the same region copy).
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stCpySrc					(Input) The structure containing the GPU copy rectangle parameters
 * \param	pstScanLine				    (Output) The structure containing the ScanLine parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 */

ErrorCode DRV_BLIT_GPU_SetPixel(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32 u32Color);
/*!\fn ErrorCode DRV_BLIT_GPU_SetPixel(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32 u32Color)
 *
 * \brief
 * 		Set the color value for the GPU fill rectangel
 *
 * \param	u32BlitHandle			(Input) An open handle number of the BLIT device
 * \param	stGpu			        (Input) The structure containing the Blit GPU parameters
 * \param	u32Color			    (Input) Set the color type
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 */

ErrorCode DRV_BLIT_GPU_GetPixel(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32* pu32Color);
/*!\fn ErrorCode DRV_BLIT_GPU_GetPixel(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32* pu32Color)
 *
 * \brief
 * 		Get the color value for the GPU fill rectangel
 *
 * \param	u32BlitHandle			(Input) An open handle number of the BLIT device
 * \param	stGpu			        (Input) The structure containing the Blit GPU parameters
 * \param	pu32Color			    (Output) Get the color type
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 */

ErrorCode DRV_BLIT_GPU_DrawHLine(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32 u32Color);
/*!\fn ErrorCode DRV_BLIT_GPU_DrawHLine(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32 u32Color)
 *
 * \brief
 * 		Use software work to draw one line in horizontal position
 *
 * \param	u32BlitHandle			(Input) An open handle number of the BLIT device
 * \param	stGpu			        (Input) The structure containing the Blit GPU parameters
 * \param	u32Color			    (Input) Set to draw color type
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 */

ErrorCode DRV_BLIT_GPU_DrawVLine(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32 u32Color);
/*!\fn ErrorCode DRV_BLIT_GPU_DrawVLine(u32 u32BlitHandle, ST_BLIT_GPUParam stGpu, u32 u32Color)
 *
 * \brief
 * 		Use software work to draw one line in vertical position
 *
 * \param	u32BlitHandle			(Input) An open handle number of the BLIT device
 * \param	stGpu			        (Input) The structure containing the GPU parameters
 * \param	u32Color			    (Input) Set to draw color type
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 */
ErrorCode DRV_BLIT_JPU_FillRectangle(u32 u32BlitHandle, ST_BLIT_FillRectParam stFillRect);
/*!\fn ErrorCode DRV_BLIT_JPU_FillRectangle(u32 u32BlitHandle, ST_BLIT_FillRectParam stFillRect)
 *
 * \brief
 * 		Fill a rectangular portion of a video with a specified color according to a specified blitting context
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stFillRect					(Input) The structure containing the JPU FillRect parameters
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */

ErrorCode DRV_BLIT_JPU_FlipRotate(u32 u32BlitHandle, ST_BLIT_FlipRotateParam stFlipRotate);
/*!\fn ErrorCode DRV_BLIT_JPU_FlipRotate(u32 u32BlitHandle, ST_BLIT_FlipRotateParam stFlipRotate)
 *
 * \brief
 * 		Flip/Rotate a rectangle from one video to another video.
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stFlipRotate				(Input) The structure containing the JPU FlipRotate parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */

ErrorCode DRV_BLIT_JPU_Copy(u32 u32BlitHandle, ST_BLIT_JpuCpyParam stJpuCpy);
/*!\fn ErrorCode DRV_BLIT_JPU_Copy(u32 u32BlitHandle, ST_BLIT_JpuCpyParam stJpuCpy)
 *
 * \brief
 * 		Copy a rectangle from one video to another video.
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stJpuCpy				    (Input) The structure containing the JPU copy parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */

ErrorCode DRV_BLIT_JPU_Scaling(u32 u32BlitHandle, ST_BLIT_ScalingParam stScaling);
/*!\fn ErrorCode DRV_BLIT_JPU_Scaling(u32 u32BlitHandle, ST_BLIT_ScalingParam stScaling)
 *
 * \brief
 * 		Scaling a rectangle from one video to another video.
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stScaling					(Input) The structure containing the Jpu scaling parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */

//only for 320
ErrorCode DRV_BLIT_GPU_Scaling(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling);
/*!\fn ErrorCode DRV_BLIT_GPU_Scaling(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling)
 *
 * \brief
 * 		Scaling for osd data(RGB format)
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stScaling					(Input) The structure containing the Gpu scaling parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */

ErrorCode DRV_BLIT_GPU_Blending(u32 u32BlitHandle, ST_BLIT_BlendParam stBlend);
/*!\fn ErrorCode DRV_BLIT_GPU_Blending(u32 u32BlitHandle, ST_BLIT_BlendParam stBlend)
 *
 * \brief
 *		Blending for osd data
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stBlend					(Input) The structure containing the Gpu Blending parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER 						Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT 					Time out
 */
//end for 320


ErrorCode DRV_BLIT_JPU_Blending(u32 u32BlitHandle, ST_BLIT_JPU_BlendParam stJPUBlend);
/*!\fn ErrorCode DRV_BLIT_JPU_Blending(u32 u32BlitHandle, ST_BLIT_JPU_BlendParam stJPUBlend)
 *
 * \brief
 *		Blending for osd data
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stBlend 				(Input) The structure containing the Gpu Blending parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER 						Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT 					Time out
 */
//end for 320

ErrorCode DRV_BLIT_GPU_RleScaling(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling, PST_BLIT_RLEParam pstRle);
/*!\fn ErrorCode DRV_BLIT_GPU_RleScaling(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling, PST_BLIT_RLEParam pstRle)
 *
 * \brief
 * 		RLE Scaling for osd data(RGB format)
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stScaling					(Input) The structure containing the Gpu scaling parameters
 * \param	pstRle					    (Input/Output) The structure containing the RLE scaling parameters
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */

ErrorCode DRV_BLIT_GPU_Format_Transform(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling, PST_BLIT_RLEParam pstRle);
/*!\fn ErrorCode DRV_BLIT_GPU_Format_Transform(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling, PST_BLIT_RLEParam pstRle)
 *
 * \brief
 * 		Format Transform for osd data(RGB format)
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stScaling					(Input) The structure containing the Gpu scaling parameters
 * \param	pstRle					    (Input/Output) The structure containing the RLE scaling parameters
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */
 
 ErrorCode DRV_BLIT_GPU_RleFontScaling(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling, PST_BLIT_RLEParam pstRle);
/*!\fn ErrorCode DRV_BLIT_GPU_RleFontScaling(u32 u32BlitHandle, ST_BLIT_GPUScalingParam stScaling, PST_BLIT_RLEParam pstRle)
 *
 * \brief
 * 		RLE and FontArt Scaling for osd data(RGB format)
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stScaling					(Input) The structure containing the Gpu scaling parameters
 * \param	pstRle					    (Input/Output) The structure containing the RLE scaling parameters
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER						    Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT						Time out
 */


ErrorCode DRV_BLIT_JPU_Format_Transform(u32 u32BlitHandle, ST_BLIT_JPU_FormatParam stFormat);
/*!\fn ErrorCode DRV_BLIT_JPU_Format_Transform(u32 u32BlitHandle, ST_BLIT_JPU_FormatParam stScaling)
 *
 * \brief
 *		Color transform for video data (YUV format)
 *
 * \param	u32BlitHandle				(Input) An open handle number of the BLIT device
 * \param	stFormat					(Input) The structure containing the JPU color transform parameters
 *
 *
 * \retval	ERROR_NO_ERROR								error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_BAD_PARAMETER 						Bad parameter passed
 * \retval	EN_DRV_BLIT_ERR_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	EN_DRV_BLIT_ERR_TIMEOUT 					Time out
 */


#ifdef __cplusplus
}
#endif

#endif  // #ifndef __DRV_BLIT_H__

