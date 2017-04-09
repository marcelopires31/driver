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


#ifndef __LAYER_H__
#define __LAYER_H__
#include "def_type.h"
#include "def_err.h"
#include "os.h"
#include "drv_config.h"

/*
 * Brief: DRV_LAYER global define.
 */
#define LAYER_MAX_DEV_NUM  								1     /*!< The maximum device number of layer module        */
#define LAYER_MAX_OPENHANDLE_PER_PLANE					3     /*!< The maximum open handle number of layer module        */


#define RGBCOLOR_RED           	0xFF0000                /*!< The Red color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */        
#define RGBCOLOR_GREEN       	0x00FF00                /*!< The Green color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_BLUE         	0x0000FF                /*!< The Blue color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_YELLOW     	0xFFFF00                /*!< The Yellow color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_PINK          	0xFF00FF                /*!< The Pink color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_AZURE        0x00FFFF                /*!< The Azure color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_ORANGE     	0xFF8800                /*!< The Orange color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_PURPLE      	0x8800FF                /*!< The Purple color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_WHITE       	0xFFFFFF                /*!< The White color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 
#define RGBCOLOR_BLACK        	0x000000                /*!< The Black color of RGB format (R:D23~D16, G:D15~D8, B:D7~D0)        */ 

#define YUVCOLOR_RED           	0x4C55FF                /*!< The Red color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_GREEN       	0x962C15                /*!< The Green color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_BLUE         	0x1DFF6B                /*!< The Blue color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_YELLOW     	0xE20195                /*!< The Yellow color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_PINK          	0xAA9CBD                /*!< The Pink color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_AZURE       	0xB3AB00                /*!< The Azure color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_ORANGE    	0xAA34D6                /*!< The Orange color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_PURPLE     	0x43EAAB                /*!< The Purple color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_WHITE       	0xFF8080                /*!< The White color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */
#define YUVCOLOR_BLACK       	0x008080                /*!< The Black color of YUV format (Y:D23~D16, U:D15~D8, V:D7~D0)        */

#define ALIGNMENT_4BYTE	4                            /*!< The limitaion of 4 byte alignment       */
#define ALIGNMENT_8BYTE	8                            /*!< The limitaion of 8 byte alignment       */
#define ALIGNMENT_16BYTE	16                          /*!< The limitaion of 16 byte alignment       */
#define ALIGNMENT_32BYTE	32                          /*!< The limitaion of 32 byte alignment       */

#define OSD_8BITPALETTE_MAX      	256          /*!< The maximum palette number of 8-bit bitmap mode       */
#define OSD_4BITPALETTE_MAX      	16            /*!< The maximum palette number of 4-bit bitmap mode       */
#define OSD_2BITPALETTE_MAX      	4              /*!< The maximum palette number of 2-bit bitmap mode       */

#define DRV_NULL_FRAME              	(0xFF)             /*!< The null value of frame index       */
#define DRV_NULL_ADDRESS		(0x0)               /*!< The null value of address       */
#define DRV_NULL_HANDLE             (0x0)               /*!< The null value of handle       */

#define DRV_LAYER_MAX_ALPHA          (0xFF)

/**
 * \brief
 * enumerate to indicate the error of operation
 */
enum
{
    ERROR_LAYER_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_LAYER,	/*!< Operation invalid, because handle not close*/
    ERROR_LAYER_MULTIHANDLE_VPENABLE,						/*!< multihandle viewport is enabled*/
    ERROR_LAYER_VP_NOT_DISABLE,								/*!< Operation invalid, because handle without access right		*/
    ERROR_LAYER_UNKNOW_DEVICE,								/*!< Invalid device name */
    ERROR_LAYER_UNKNOW_COLORMODE ,							/*!< Invalid color mode */
    ERROR_LAYER_UNSUPPORT_DEVICE							/*!< Un-Support Device */
};

/**
 * \brief
 * enumurate to indicate the LAYER event type
 */
typedef enum
{
    EVENT_LAYER_DISPLAY_NEWFRAME = 0x1,                /*!< The event type for display new frame	    */
    EVENT_LAYER_DISPLAY_QUEUE_EMPTY = 0x2,               /*!< The event type for display queue empty	    */        
    EVENT_LAYER_DISPLAY_SYNC_ACHIEVED = 0x4,
    EVENT_LAYER_DISPLAY_SYNC_LOST = 0x8,
    EVENT_LAYER_DISPLAY_CHANGE_PICSIZE = 0x10, 
    EVENT_LAYER_DISPLAY_UNMUTE = 0x18,
    EVENT_LAYER_DISPLAY_CHANGE_AFD = 0x20,            
} EN_DRV_LAYER_EVENT_TYPE;

/**
 * \brief
 * enumerate to indicate the planes of vpu
 */
typedef enum
{
    EN_DRV_LAYER_PLANE_VIDEO1,          /*!< The main video plane       */
    EN_DRV_LAYER_PLANE_VIDEO2,          /*!< The picture plane       */
    EN_DRV_LAYER_PLANE_CURSOR1,         /*!< The cursor1 plane       */
    EN_DRV_LAYER_PLANE_CURSOR2,         /*!< The cursor2 plane       */
    EN_DRV_LAYER_PLANE_OSD,             /*!< The osd plane       */
    EN_DRV_LAYER_PLANE_SP,              /*!< The sp plane       */
    EN_DRV_LAYER_PLANE_SP2,			    /*!< The sp2 plane	   */
    EN_DRV_LAYER_PLANE_BGP,             /*!< The bgp plane     */    
    EN_DRV_LAYER_PLANE_NUM              
} EN_DRV_LAYER_PLANE, *PEN_DRV_LAYER_PLANE;


/**
 * \brief
 * enumerate to indicate the planes of video layer
 */
typedef enum
{
    EN_DRV_LAYER_VIDEO_MAIN,        /*!< The main video plane       */
    EN_DRV_LAYER_VIDEO_AUX,          /*!< The picture plane       */
    EN_DRV_LAYER_VIDEO_NUM
} EN_DRV_LAYER_VIDEO, *PEN_DRV_LAYER_VIDEO;

/**
 * \brief
 * enumerate to indicate the planes of osd layer
 */
typedef enum
{
    EN_DRV_LAYER_OSD_MAIN,          /*!< The osd plane       */
    EN_DRV_LAYER_OSD_SP,              /*!< The sp plane       */
    EN_DRV_LAYER_OSD_SP2,			  /*!< The sp2 plane 	  */
    EN_DRV_LAYER_OSD_NUM
} EN_DRV_LAYER_OSD, *PEN_DRV_LAYER_OSD;


/**
 * \brief
 * enumerate to indicate the planes of cursor layer
 */
typedef enum
{
    EN_DRV_LAYER_CURSOR_1,          /*!< The cursor1 plane       */
    EN_DRV_LAYER_CURSOR_2,          /*!< The cursor2 plane       */
    EN_DRV_LAYER_CURSOR_NUM
} EN_DRV_LAYER_CURSOR, *PEN_DRV_LAYER_CURSOR;

/**
 * \brief
 * enumerate to indicate the planes of bgp layer
 */
typedef enum
{
    EN_DRV_LAYER_BGP_1,          /*!< The bgp plane       */
    EN_DRV_LAYER_BGP_NUM
} EN_DRV_LAYER_BGP, *PEN_DRV_LAYER_BGP;
/**
 * \brief
 * enumerate to indicate the color mode of bitmap
 */

typedef enum
{
    EN_DRV_COLOR_BMP_2BIT                      = 0,      /*!< 2-bit color index mode      */
    EN_DRV_COLOR_BMP_4BIT         			   = 1,      /*!< 4-bit color index mode      */
    EN_DRV_COLOR_BMP_8BIT         	           = 2,      /*!< 8-bit color index mode      */
    EN_DRV_COLOR_ARGB8888         	           = 3,      /*!< ARGB8888 true color mode    */
    EN_DRV_COLOR_RGB565           		       = 4,      /*!< RGB565 true color mode      */
    EN_DRV_COLOR_ARGB1555         	           = 5,      /*!< ARGB1555 true color mode    */
    EN_DRV_COLOR_ARGB4444         	           = 6,      /*!< ARGB4444 true color mode    */
    EN_DRV_COLOR_RGBA8888         	           = 7,      /*!< RGBA8888 true color mode    */
    EN_DRV_COLOR_RGBA5551         	           = 8,      /*!< RGBA5551 true color mode    */
    EN_DRV_COLOR_RGBA4444         	           = 9,      /*!< RGBA4444 true color mode    */
    EN_DRV_COLOR_A8P8         	               = 10,     /*!< A8P8 true color mode    */
    EN_DRV_COLOR_AYUV8888 					   = 11, 	 /*!< AYUV8888 true color mode  */ 
    EN_DRV_COLOR_AYUV1555 					   = 12, 	 /*!< AYUV1555 true color mode  */ 
    EN_DRV_COLOR_YUV655 					   = 13, 	 /*!< YUV565 true color mode  */ 
    EN_DRV_COLOR_YUV888      	               = 14,     /*!< YUV888 true color mode  */ 
    EN_DRV_COLOR_BGR888       		           = 20,     /*!< BGR888 true color mode      */
    EN_DRV_COLOR_ARGB8888_ALPHA 			   = 21,	 /*!< ARGB8888_ALPHA true color mode 	  */
    EN_DRV_COLOR_ARGB4444_ALPHA 			   = 22,	 /*!< ARGB4444_ALPHA true color mode 	  */
    EN_DRV_COLOR_RGBA8888_ALPHA 			   = 23,	 /*!< RGBA8888_ALPHA true color mode 	  */
    EN_DRV_COLOR_RGBA4444_ALPHA 			   = 24,	 /*!< RGBA4444_ALPHA true color mode 	  */
    EN_DRV_COLOR_A4X4P8 					   = 25,	 /*!< A4X4P8 true color mode 	  */
	
    EN_DRV_COLOR_YUV422                    = 26,//Only for 310 compiler need to remove  
    EN_DRV_COLOR_YUV422_601 				   = 27,//Only for 310 compiler need to remove  
	
	EN_DRV_COLOR_YUV420 				   = 28,//Only for 310 compiler need to remove	
} EN_DRV_LAYER_COLORMODE;


/**
 * \brief
 * enumerate to indicate the alpha mode of bitmap
 */
typedef enum
{
    EN_DRV_OSD_ALPHA_CHANNEL = 0,       /*!< The original alpha channel       */
    EN_DRV_OSD_ALPHA_REGION,                /*!< The region alpha for whole region      */
    EN_DRV_OSD_ALPHA_MIX                       /*!< The region_alpha x alpha_channel      */
} EN_DRV_LAYER_ALPHAMODE, *PEN_DRV_LAYER_ALPHAMODE;

/**
 * \brief
 * enumerate to indicate the alpha mode of ARGB4444 color format
 */
typedef enum
{
    EN_DRV_OSD_ARGB4444_ALPHA_CHANNEL = 0,  /*!< Alpha value is 4bit expand 8bit       */
    EN_DRV_OSD_ARGB4444_ALPHA_INDEX,             /*!< Alpha value reference look up talbe 8 bit       */
} EN_DRV_LAYER_ARGB4444ALPHAMODE, *PEN_DRV_LAYER_ARGB4444ALPHAMODE;

/**
 * \brief
 * enumerate to indicate the anti-flicker mode of osd plane
 */
typedef enum
{
    EN_DRV_OSD_AF_NORMAL,               /*!< Always do anti-flicker       */
    EN_DRV_OSD_AF_THRESHOLD,         /*!< Refer the threshold value do anti-flicker      */
    EN_DRV_OSD_AF_OFF                       /*!< Disable anti-flicker       */
} EN_DRV_LAYER_AFMODE, *PEN_DRV_LAYER_AFMODE;

/**
 * \brief
 * enumerate to indicate the RGB range of osd plane
 */
typedef enum
{
    EN_DRV_LAYER_OSD_RANGE_STUDIO,          /*!< convert to studio Y(16-235) UV(16-240)      */
//    EN_DRV_LAYER_OSD_RANGE_FULL,              /*!< convert to full range YUV(0-255)       */ //310 osd bug
    EN_DRV_LAYER_OSD_RANGE_UNKNOWN
} EN_DRV_LAYER_OSD_RANGE, *PEN_DRV_LAYER_OSD_RANGE;

/**
 * \brief
 * enumerate to indicate the color conversion format of osd plane
 */
typedef enum
{
    EN_DRV_LAYER_OSD_COLORCONV_601,     /*!< 601 color space conversion      */
    EN_DRV_LAYER_OSD_COLORCONV_709,     /*!< 709 color space conversion      */
    EN_DRV_LAYER_OSD_COLORCONV_UNKNOWN
} EN_DRV_LAYER_OSD_COLORCONV, *PEN_DRV_LAYER_OSD_COLORCONV;

/**
 * \brief
 * enumerate to indicate the data source format of video plane
 */
typedef enum
{
    EN_DRV_LAYER_VIDEO_FMT_420,     /*!< 420 format      */
    EN_DRV_LAYER_VIDEO_FMT_422,     /*!< 422 format      */
    EN_DRV_LAYER_VIDEO_FMT_444,     /*!< 444 format      */
    EN_DRV_LAYER_VIDEO_FMT_UNKNOWN
} EN_DRV_LAYER_VIDEO_FMT, *PEN_DRV_LAYER_VIDEO_FMT;

/**
 * \brief
 * enumerate to indicate the data source format of bgp plane
 */
typedef enum
{
    EN_DRV_LAYER_BGP_FMT_420,     /*!< 420 format      */
    EN_DRV_LAYER_BGP_FMT_422,     /*!< 422 format      */
    EN_DRV_LAYER_BGP_FMT_444,     /*!< 444 format      */
    EN_DRV_LAYER_BGP_FMT_UNKNOWN
} EN_DRV_LAYER_BGP_FMT, *PEN_DRV_LAYER_BGP_FMT;
/*!
 * \brief
 * enumerate to indicate the MAU burst length to fetch bgp data
 */
typedef enum
{    
    EN_DRV_LAYER_BGP_BURSTLEN_4,        /*!< Burst length 4   */
    EN_DRV_LAYER_BGP_BURSTLEN_8,        /*!< Burst length 8   */
    EN_DRV_LAYER_BGP_BURSTLEN_UNKNOWN
} EN_DRV_LAYER_BGP_BURSTLEN, *PEN_DRV_LAYER_BGP_BURSTLEN;
/**
 * \brief
 * enumerate to indicate the video display mode of video plane
 */
typedef enum
{
    EN_DRV_LAYER_VIDEO_DISPMODE_LIVE,               /*!< normal mode (switch frame buffer to present live video)      */
    EN_DRV_LAYER_VIDEO_DISPMODE_JPUCPY,          /*!< Jpu copy mode (use JPU copy to fixed frame buffer address to present live video)      */
    EN_DRV_LAYER_VIDEO_DISPMODE_PICTURE,        /*!< still picture mode      */
    EN_DRV_LAYER_VIDEO_DISPMODE_UNKNOWN
} EN_DRV_LAYER_VIDEO_DISPMODE, *PEN_DRV_LAYER_VIDEO_DISPMODE;

/*!
 * \brief
 * the initial structure includes the device hardware setting
 */
typedef struct 
{
    os_mempool_handle u32MemPoolHandle;				/*!< A memory pool handle for Layer module	*/
    EN_DRV_LAYER_PLANE enLayerPlane;                            /*!< enumerate to indicate the planes of vpu	*/
}ST_LAYER_Init, *PST_LAYER_Init;

/*!
 * \brief
 * the structure defines the supported and unsupported features of a given plane
 */
typedef struct
{
    bool b8HDSupport;                          /*!< support HD format or not	*/
    bool b8MultipleViewPorts;              /*!< support Multi-ViewPorts or not	*/
    bool b8ScalingUp;                           /*!< support Scaling Up or not	*/
    bool b8ScalingDown;                      /*!< support Scaling Down or not	*/
    bool b8BorderSet;                          /*!< support Border or not	       */  
    bool b8DeinterlaceMode;	           /*!< support Deinterlace or not	*/ 
    bool b8AntiFlickerEn;                    /*!< support AntiFlicker or not	       */
    bool b8AlphaSmoothEn;                /*!< support AlphaSmooth or not	*/
    bool b8HFilter;                              /*!< support H-Filter or not	       */
    bool b8VFilter;	                        /*!< support V-Filter or not	       */
    bool b8TransKey;                          /*!< support TransKey or not	       */
    bool b8ColorKey;		                 /*!< support ColorKey or not	       */
} ST_LAYER_Capability, *PST_LAYER_Capability;

/*!
 * \brief
 * the open structure includes the LAYER opening parameters
 */
typedef struct 
{
    u32 u32EVTHandle;               /*!< A event handle for Layer module	    */
    u32 u32ViewPorts;                /*!< A view port number for the designated plane   */
}ST_LAYER_Open, *PST_LAYER_Open;

/*!
 * \brief
 * the structure includes the display Window information
 */
typedef struct
{
    u16 u16HStart;      	/*!< A horizontal start point for the designated window    */
    u16 u16HWidth;      /*!< A width for the designated window    */
    u16 u16VStart;      	/*!< A vertical start point for the designated window    */
    u16 u16VWidth;      /*!< A height for the designated window    */
} ST_LAYER_WinParam, *PST_LAYER_WinParam;

/*!
 * \brief
 * the structure includes the border information of source picture for mix mode in deinterlace IVTC mode.
 * (Margin region uses MAD mode, whereas inner block region uses IVTC mode for film detection) 
 */
typedef struct
{
    u16 u16LMarginRatio;        /*!< Left margin for IVTC block (Unit : 1/1000)  */
    u16 u16RMarginRatio;        /*!< Right margin for IVTC block  (Unit : 1/1000) */
    u16 u16UMarginRatio;        /*!< Up margin for IVTC block  (Unit : 1/1000)  */
    u16 u16DMarginRatio;        /*!< Down margin for IVTC block  (Unit : 1/1000)  */
    bool  b8EnableMixMode; /*!< Enable IVTC mix mode, makes the margin active    */	
} ST_LAYER_IVTCModeMargin, *PST_LAYER_IVTCModeMargin;


/*!
 * \brief
 * the structure includes the video framebuffer parameters
 */
typedef struct
{    
    u32 u32Luma;            /*!< A start address of the luma domain    */
    u32 u32Chroma;        /*!< A start address of the chroma domain    */
} ST_LAYER_VideoFBAddr, *PST_LAYER_VideoFBAddr;

/*!
 * \brief
 * the structure includes the BGP framebuffer parameters
 */
typedef struct
{    
    u32 u32Luma;            /*!< A start address of the luma domain    */
    u32 u32Chroma;        /*!< A start address of the chroma domain    */
} ST_LAYER_BGPFBAddr, *PST_LAYER_BGPFBAddr;
/*!
 * \brief
 * the structure includes the video border parameters
 */
typedef struct
{
    u32 u32YUVColor;                /*!< A YUV color of the border    */
    u8 u8Width;                         /*!< A width of the border    */
    u8 u8Height;                        /*!< A height of the border    */
    bool b8Enable;                   /*!< Enable border or not    */
} ST_LAYER_VideoBorderParam, *PST_LAYER_VideoBorderParam;

/*!
 * \brief
 * the structure includes the Anti-Flicker parameters
 */
typedef struct 
{       
    EN_DRV_LAYER_AFMODE enAFMode;           /*!< Indicate the anti-flicker mode of osd plane    */
    u8 u8ThresholdValue;                               /*!< The value to decide to do anti-flicker or not    */
    u8 u8EdgeValue;                                       /*!< Y value of edge pixel   */
}ST_LAYER_AFParam, *PST_LAYER_AFParam;

/*!
 * \brief
 * the structure includes the video Live mode parameters
 */
typedef struct 
{
    u32 u32VdecHandle;                      /*!< An associated vdec handle with the video plane    */
    u32 u32OutputRate;                       /*!< An associated output rate with the video plane    */
    u8 u8ForceDispFrame;                  /*!< Indicate the frame index to display    */
    bool b8DeinterlaceMode;	         /*!< Enable de-interlace function or not    */
    ST_LAYER_IVTCModeMargin stIVTCModeMargin;  /*!< Deinterlace IVTC mode border info    */
    ST_LAYER_VideoFBAddr stADDR;      /*!< Video framebuffer parameters    */    
}ST_LAYER_VideoDispLive, *PST_LAYER_VideoDispLive;

/*!
 * \brief
 * the structure includes the video JPU copy mode parameters
 */
typedef struct 
{
    ST_LAYER_VideoFBAddr stADDR;      /*!< Video framebuffer parameters    */
    ST_LAYER_WinParam stCpyWin;      /*!< Jpu copy window     */       
    u32 u32VdecHandle;                      /*!< An associated vdec handle with the video plane    */
    u32 u32OutputRate;                       /*!< An associated output rate with the video plane    */
    bool b8IsCpyOneTime;                 /*!< Copy one time or not    */
    bool b8IsStartCpy;                       /*!< Start Jpu copy or not    */
}ST_LAYER_VideoDispJpuCpy, *PST_LAYER_VideoDispJpuCpy;

/*!
 * \brief
 * the structure includes the video still picture mode parameters
 */
typedef struct 
{
    ST_LAYER_VideoFBAddr stADDR;        /*!< Video framebuffer parameters    */
}ST_LAYER_VideoDispPicture, *PST_LAYER_VideoDispPicture;

/*!
 * \brief
 * the structure includes the LAYER VIDEO opening parameters
 */
typedef struct 
{
    ST_LAYER_VideoBorderParam stBorderParam;            /*!< Video border parameters    */
    EN_DRV_LAYER_VIDEO_FMT enVideoFmt;                    /*!< Data source format of video plane    */
    EN_DRV_LAYER_VIDEO_DISPMODE enDispMode;         /*!< Video display mode of video plane    */
    union
    {
        ST_LAYER_VideoDispLive stLive;                              /*!< Video Live mode parameters    */
        ST_LAYER_VideoDispJpuCpy stJpuCpy;                     /*!< Video JPU copy mode parameters    */
        ST_LAYER_VideoDispPicture stPic;                            /*!< Video still picture mode parameters    */
    }Mode;
    u16 u16WindowWidth;                                              /*!< The distance of two vertical line    */
    u8 u8Alpha;                                                              /*!< The alpha value of video plane    */
    bool b8OneFieldDisp;                                              /*!< Enable one field mode or not    */
}ST_LAYER_VideoOpen, *PST_LAYER_VideoOpen;

/*!
 * \brief
 * the structure includes the LAYER BGP opening parameters
 */
typedef struct 
{
    EN_DRV_LAYER_BGP_FMT enBGPFmt;                    /*!< Data source format of BGP plane    */
    ST_LAYER_BGPFBAddr stADDR;                                                 /*!< The base address of the source data     */
    u16 u16WindowWidth;                                              /*!< The distance of two vertical line    */
    u8 u8Alpha;                                                              /*!< The alpha value of bgp plane    */    
}ST_LAYER_BGPOpen, *PST_LAYER_BGPOpen;
/*!
 * \brief
 * the structure includes the LAYER BITMAP opening parameters
 */
typedef struct 
{
    EN_DRV_LAYER_COLORMODE enColorMode;                         /*!< The color mode of bitmap    */
    EN_DRV_LAYER_ALPHAMODE enAlpha;                                  /*!< The alpha mode of bitmap    */
    EN_DRV_LAYER_ARGB4444ALPHAMODE en4444Alpha;          /*!< The alpha mode of ARGB4444 color format    */
    EN_DRV_LAYER_OSD_RANGE enRange;                                /*!< The RGB range of osd plane    */
    EN_DRV_LAYER_OSD_COLORCONV enColorConv;                 /*!< The color conversion format of osd plane    */
    ST_LAYER_AFParam stAFParam;                                          /*!< The Anti-Flicker parameters    */
    u32 u32DataBaseAddress;                                                 /*!< The base address of the source data     */
    u32 u32PaletteAddress;                                                    /*!< The base address of the palette data    */
    u32 u32ColorKeyValue;                                                     /*!< The color key value    */
    u32 u32TransKeyValue;                                                    /*!< The transparent key value    */           
    u8 u8ColorKeyAlpha;                                                        /*!< The color key alpha value    */
    u8 u8RegionAlpha;                                                           /*!< The region alpha value    */
    u8 u8ARGB_AF;	                                                          /*!< The ARGB1555 alpha value    */
    bool b8TransKeyEn;                                                        /*!< Enable transparent key or not    */
    bool b8ColorKeyEn;	                                                   /*!< Enable color key or not    */
}ST_LAYER_BitmapOpen, *PST_LAYER_BitmapOpen;

/*!
 * \brief
 * the structure includes the ViewPort parameters
 */
typedef struct 
{
    ST_LAYER_WinParam stInWinParam;                     /*!< The clip window information    */
    ST_LAYER_WinParam stOutWinParam;	                  /*!< The display window information    */
    union
    {
        ST_LAYER_VideoOpen stLayerVideoOpen;         /*!< The LAYER VIDEO opening parameters    */
        ST_LAYER_VideoOpen stLayerBGPOpen;             /*!< The LAYER BGP opening parameters    */
        ST_LAYER_BitmapOpen stLayerBitmapOpen;     /*!< The LAYER BITMAP opening parameters    */
    }Data;
    u16 u16SrcW;                                                       /*!< The width of source data    */
    u16 u16SrcH;                                                       /*!< The height of source data    */
    bool b8Enable;                                                   /*!< Enable viewport or not    */
}ST_LAYER_ViewPortParam, *PST_LAYER_ViewPortParam;

/*!
 * \brief
 * the structure includes the VideoSource parameters
 */
typedef struct 
{
    ST_LAYER_VideoFBAddr stADDR;            /*!< The video framebuffer parameters    */
    u16 	u16WindowWidth;                     /*!< The distance of two vertical line    */
}ST_LAYER_VideoSource, *PST_LAYER_VideoSource;

/*!
 * \brief
 * the structure includes the BGPSource parameters
 */
typedef struct 
{
    ST_LAYER_BGPFBAddr stADDR;            /*!< The BGP framebuffer parameters    */
    u16 	u16WindowWidth;                     /*!< The distance of two vertical line    */
}ST_LAYER_BGPSource, *PST_LAYER_BGPSource;
/*!
 * \brief
 * the structure includes the BitmapSource parameters
 */
typedef struct 
{
    EN_DRV_LAYER_COLORMODE enColorMode;     /*!< The color mode of bitmap    */
    u32 u32DataBaseAddress;	                          /*!< The base address of the source data     */
}ST_LAYER_BitmapSource, *PST_LAYER_BitmapSource;

/*!
 * \brief
 * the structure includes the Input/Output window parameters
 */
typedef struct 
{
    ST_LAYER_WinParam stInWin;          /*!< The clip window information    */
    ST_LAYER_WinParam stOutWin;	   /*!< The display window information    */
    u16 u16SrcW;                                 /*!< The width of source data    */
    u16 u16SrcH;	                               /*!< The height of source data    */
}ST_LAYER_IORectParam, *PST_LAYER_IORectParam;

/*!
 * \brief
 * the structure includes the ViewPort source parameters
 */
typedef struct 
{	
    union
    {
        ST_LAYER_VideoSource stVideoSrc;        /*!< The VideoSource parameters    */
        ST_LAYER_BGPSource stBGPSrc;        /*!< The BGPSource parameters    */
        ST_LAYER_BitmapSource stBitmapSrc;    /*!< The BitmapSource parameters    */
    }Data;	
    ST_LAYER_IORectParam stIORect;              /*!< The Input/Output window parameters    */
}ST_LAYER_ViewPortSource, *PST_LAYER_ViewPortSource;

/*!
 * \brief
 * the structure includes the osd alpha parameters
 */
typedef struct 
{
    EN_DRV_LAYER_ALPHAMODE enAlpha;     /*!< The alpha mode of bitmap    */
    u8 u8Alpha;                                           /*!< The region alpha value    */
    u8 u8ARGB_AF;		                        /*!< The ARGB1555 alpha value    */
}ST_LAYER_AlphaParam, *PST_LAYER_AlphaParam;

/*!
 * \brief
 * the structure includes the BitmapAlloc parameters
 */
typedef struct 
{
    EN_DRV_LAYER_COLORMODE enColorMode;	/*!< The color mode of bitmap    */
    u32 u32SizeOfByte;                       			/*!< The size of byte    */	
    u32 u32AlignmentOfByte;    				       /*!< The byte alignment     */	
    u16 u16Width;							       /*!< The source width    */
    u16 u16Height;              				       /*!< The source height    */
}ST_LAYER_BitmapAllocParam, *PST_LAYER_BitmapAllocParam;

/*!
 * \brief
 * the structure includes the PaletteAlloc parameters
 */
typedef struct 
{
    u32 u32SizeOfByte;                       /*!< The size of byte    */	
    u32 u32AlignmentOfByte;             /*!< The byte alignment     */	
}ST_LAYER_PaletteAllocParam, *PST_LAYER_PaletteAllocParam;

/*!
 * \brief
 * the structure includes the VideoAlloc parameters
 */
typedef struct 
{
    EN_DRV_LAYER_VIDEO_FMT enFmt;  /*!< The data source format of video plane   */
    u32 u32SizeOfByte_Y;			    /*!< The size of byte for luma domain   */			
    u32 u32SizeOfByte_C;			    /*!< The size of byte for chroma domain    */			
    u32 u32AlignmentOfByte;   		    /*!< The byte alignment     */			
    u16 u16Width;					    /*!< The source width    */			
    u16 u16Height;				    /*!< The source height    */				
}ST_LAYER_VideoAllocParam, *PST_LAYER_VideoAllocParam;

typedef struct 
{    	
	EN_DRV_LAYER_VIDEO_FMT enChromaFmt;
	u32 u32LumaAddr;
	u32 u32ChromaAddr;
	u16 u16SrcW;
	u16 u16SrcH;
	u16 u16Strip; 					//vertical stride
	u8	u8SrcFrame;					// The Chroma sample position. 1 is progressive. 0 is interlaced
}ST_LAYER_GetFrameInfoParam, *PST_LAYER_GetFrameInfoParam;


ErrorCode DRV_LAYER_Init(DRV_DeviceNameType DeviceName, PST_LAYER_Init pstInit);
/*!\fn ErrorCode DRV_LAYER_Init(DRV_DeviceNameType DeviceName, PST_LAYER_Init pstInit)
 *
 * \brief
 * 		Initialize LAYER device with pstInit setting
 *
 * \param 	DeviceName		                		(Input)  Device Name
 * \param	pstInit							(Input) Pointer to the initialization parameter structure
 *
 * \retval	ERROR_NO_ERROR						No error
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE Un-Support Device				
 * \retval	ERROR_INITIALISED				       The driver is not initialized
 * \retval	ERROR_NO_FREE_HANDLE				No free handle for the device
 *
 */

ErrorCode DRV_LAYER_Term(DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_LAYER_Term(DRV_DeviceNameType DeviceName, bool b8Force)
 *
 * \brief
 * 		Terminate the LAYER device driver
 *
 * \param 	DeviceName		                		(Input)  Device Name
 * \param	b8Force							(Input) Force terminate the LAYER or not
 *
 * \retval	ERROR_NO_ERROR							No error
 * \retval	ERROR_LAYER_HANDLE_NOT_CLOSED	Handle is not closed
 * \retval	ERROR_INITIALISED						The driver is not initialized
 * \retval	ERROR_LAYER_UNKNOW_DEVICE            Invalid device name
 */

ErrorCode DRV_LAYER_Open (DRV_DeviceNameType DeviceName, PST_LAYER_Open pstOpen, u32 *pu32LayerHandle);
/*!\fn ErrorCode DRV_LAYER_Open (DRV_DeviceNameType DeviceName, PST_LAYER_Open pstOpen, u32 *pu32LayerHandle)
 *
 * \brief
 * 		Open the LAYER device and associate it with a handle
 *
 * \param 	DeviceName		(Input)  Device Name
 * \param	pstOpen			(Input) Pointer to the opening parameter structure
 * \param	pu32LayerHandle	(Output) The returned handle of the opened device driver
 *
 * \retval	ERROR_NO_ERROR						No error
 * \retval	ERROR_LAYER_UNKNOW_DEVICE	Invalid device name
 * \retval	ERROR_INITIALISED					The driver is not initialized
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_NO_FREE_HANDLE				No free handle for the device
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE Un-Support Device	
 */

ErrorCode DRV_LAYER_Close (u32* pu32LayerHandle);
/*!\fn ErrorCode DRV_LAYER_Close (u32* pu32LayerHandle)
 *
 * \brief
 * 		Close LAYER device associated with a handle
 *
 * \param	pu32LayerHandle			(Input) An open handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR				                    No error
 * \retval	ERROR_INVALID_HANDLE		                    Handle is not valid
 * \retval	ERROR_LAYER_HANDLE_NOT_CLOSED    Handle not close
 */

ErrorCode DRV_LAYER_GetCapability(DRV_DeviceNameType DeviceName, PST_LAYER_Capability  pstCapability);
/*!\fn ErrorCode DRV_LAYER_GetCapability(DRV_DeviceNameType DeviceName, PST_LAYER_Capability  pstCapability)
 *
 * \brief
 * 		Get the capabilities of the named layer plane
 *
 * \param 	DeviceName				(Input)  Device Name
 * \param	pstCapability				(Output) The capability structure for indicated layer
 *
 * 
 * \retval	ERROR_NO_ERROR				                     No error
 * \retval	ERROR_LAYER_UNKNOW_DEVICE		Invalid device name
 */

ErrorCode DRV_LAYER_GetBitmapAllocParams(PST_LAYER_BitmapAllocParam pstAllocParam);
/*!\fn ErrorCode DRV_LAYER_GetBitmapAllocParams(PST_LAYER_BitmapAllocParam pstAllocParam)
 *
 * \brief
 * 		Get information for bitmap allocation
 *
 *
 * \param	pstAllocParam				(Input)   ColorMode/Width/Height of the Bitmap	
 *									(Output) Size/Alignment of the Bitmap
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNKNOW_COLORMODE		Invalid color mode
 */
 
ErrorCode DRV_LAYER_GetPaletteAllocParams(EN_DRV_LAYER_PLANE enLayerPlane, PST_LAYER_PaletteAllocParam pstAllocParam);
/*!\fn ErrorCode DRV_LAYER_GetPaletteAllocParams(EN_DRV_LAYER_PLANE enLayerPlane, PST_LAYER_PaletteAllocParam pstAllocParam)
 *
 * \brief
 * 		Get the palette allocation parameters.
 *
 *
 * \param 	enLayerPlane				(Input)  layer plane
 * \param	pstAllocParam				(Output) Size/Alignment of the Palette Data
 *									
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 */

ErrorCode DRV_LAYER_GetVideoAllocParams(PST_LAYER_VideoAllocParam pstAllocParam);
/*!\fn ErrorCode DRV_LAYER_GetVideoAllocParams(PST_LAYER_VideoAllocParam pstAllocParam)
 *
 * \brief
 * 		Get the video allocation parameters.
 *
 *
 * \param	pstAllocParam				(Input)   Width/Height of the Video	
 *									(Output) Size/Alignment of the Video									
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 */
 
ErrorCode DRV_LAYER_OpenViewPort(u32 u32LayerHandle, PST_LAYER_ViewPortParam pstViewPort ,u32* pu32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_OpenViewPort(u32 u32LayerHandle, PST_LAYER_ViewPortParam pstViewPort ,u32* pu32ViewPortHandle)
 *
 * \brief
 * 		Open a viewport on a display layer.
 *		need to call DRV_LAYER_EnableViewPort() if we want to enable this viewport
 *
 *
 * \param	u32LayerHandle				(Input)   The handle of the opened device driver
 * \param	pstViewPort					(Input)   The structure containing the viewport parameters									
 * \param	pu32ViewPortHandle			(Output) The returned handle of the viewport device driver
 *
 * 
 * \retval	ERROR_NO_ERROR						No error
 * \retval	ERROR_LAYER_UNKNOW_DEVICE	Invalid device name
 * \retval	ERROR_INITIALISED					The driver is not initialized
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_NO_FREE_HANDLE				No free handle for the device
 * \retval	ERROR_INVALID_HANDLE				Handle is not valid
 * \retval	ERROR_NO_MEMORY                                 The memory allocate is fail
 */
 
ErrorCode DRV_LAYER_CloseViewPort(u32* pu32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_CloseViewPort(u32* pu32ViewPortHandle)
 *
 * \brief
 * 		Close an opened viewport on a display layer.
 *
 * \param	pu32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR							No error
 * \retval	ERROR_INVALID_HANDLE					Handle is not valid
 * \retval	ERROR_LAYER_VP_NOT_DISABLE		ViewPort is not disabled
 */
 
ErrorCode DRV_LAYER_EnableViewPort(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_EnableViewPort(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Enable a specified viewport, showing it on the layer on which it is open.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_LAYER_MULTIHANDLE_VPENABLE		Multihandle viewport is enabled
 * \retval	ERROR_NO_MEMORY                                               The memory allocate is fail
 */
 
ErrorCode DRV_LAYER_DisableViewPort(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_DisableViewPort(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Disable display of a viewport, hiding it from the screen.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_SetViewPortParams(u32 u32ViewPortHandle, ST_LAYER_ViewPortParam stViewPort);
/*!\fn ErrorCode DRV_LAYER_SetViewPortParams(u32 u32ViewPortHandle, ST_LAYER_ViewPortParam stViewPort)
 *
 * \brief
 * 		Set the parameters of a viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	stViewPort				(Input) The structure containing the viewport parameters	
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNKNOW_DEVICE			Invalid device name
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_NO_MEMORY                                               The memory allocate is fail
 */
 
ErrorCode DRV_LAYER_GetViewPortParams(u32 u32ViewPortHandle, PST_LAYER_ViewPortParam pstViewPort);
/*!\fn ErrorCode DRV_LAYER_GetViewPortParams(u32 u32ViewPortHandle, PST_LAYER_ViewPortParam pstViewPort)
 *
 * \brief
 * 		Get the parameters of a viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pstViewPort				(Output) The structure containing the viewport parameters	
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNKNOW_DEVICE			Invalid device name
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_SetViewPortBorder(u32 u32ViewPortHandle, ST_LAYER_VideoBorderParam stBorderParam);
/*!\fn ErrorCode DRV_LAYER_SetViewPortBorder(u32 u32ViewPortHandle, ST_LAYER_VideoBorderParam stBorderParam)
 *
 * \brief
 * 		Set the parameters of Border.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	stBorderParam			(Input) The structure containing the Border parameters	
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_GetViewPortBorder(u32 u32ViewPortHandle, PST_LAYER_VideoBorderParam pstBorderParam);
/*!\fn ErrorCode DRV_LAYER_GetViewPortBorder(u32 u32ViewPortHandle, PST_LAYER_VideoBorderParam pstBorderParam)
 *
 * \brief
 * 		Get the parameters of Border.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pstBorderParam			(Output) The structure containing the Border parameters	
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_EnableColorKey(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_EnableColorKey(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Enable the Color Key on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_DisableColorKey(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_DisableColorKey(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Disable the Color Key on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_GetViewPortColorKey(u32 u32ViewPortHandle, u32* pu32ColorKey, u8* pu8Alpha);
/*!\fn ErrorCode DRV_LAYER_GetViewPortColorKey(u32 u32ViewPortHandle, u32* pu32ColorKey, u8* pu8Alpha)
 *
 * \brief
 * 		Get the color key associated with a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pu32ColorKey			       (Output) The RGB color (D23-D16:B, D15-D8:G, D7-D0:R) or color index
 * \param	pu8Alpha					(Output) The new alpha value
 * 
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_SetViewPortColorKey(u32 u32ViewPortHandle, u32 u32ColorKey, u8 u8Alpha);
/*!\fn ErrorCode DRV_LAYER_SetViewPortColorKey(u32 u32ViewPortHandle, u32 u32ColorKey, u8 u8Alpha)
 *
 * \brief
 * 		Set the color key associated with a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	u32ColorKey				(Input) The RGB color (D23-D16:B, D15-D8:G, D7-D0:R) or color index
 * \param	u8Alpha					(Input) The new alpha value
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_EnableTransKey(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_EnableTransKey(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Enable the Transparency Key on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_DisableTransKey(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_DisableTransKey(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Disable the Transparency Key on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_GetViewPortTransKey(u32 u32ViewPortHandle, u32* pu32TransKey);
/*!\fn ErrorCode DRV_LAYER_GetViewPortTransKey(u32 u32ViewPortHandle, u32* pu32TransKey)
 *
 * \brief
 * 		Get the Transparency key associated with a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pu32TransKey			       (Output) The RGB color (D23-D16:B, D15-D8:G, D7-D0:R) or color index
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_SetViewPortTransKey(u32 u32ViewPortHandle, u32 u32TransKey);
/*!\fn ErrorCode DRV_LAYER_SetViewPortTransKey(u32 u32ViewPortHandle, u32 u32TransKey)
 *
 * \brief
 * 		Set the Transparency key associated with a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	u32TransKey				(Input) The RGB color (D23-D16:B, D15-D8:G, D7-D0:R) or color index
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_GetViewPortAlpha(u32 u32ViewPortHandle, PST_LAYER_AlphaParam pstAlphaParam);
 /*!\fn ErrorCode DRV_LAYER_GetViewPortAlpha(u32 u32ViewPortHandle, PST_LAYER_AlphaParam pstAlphaParam)
 *
 * \brief
 * 		Get the parameters of a alpha.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pstAlphaParam			(Output) The structure containing the alpha parameters	
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_SetViewPortAlpha(u32 u32ViewPortHandle, ST_LAYER_AlphaParam stAlphaParam);
 /*!\fn ErrorCode DRV_LAYER_SetViewPortAlpha(u32 u32ViewPortHandle, ST_LAYER_AlphaParam stAlphaParam)
 *
 * \brief
 * 		Set the parameters of a alpha.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	stAlphaParam				(Input) The structure containing the alpha parameters
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_EnableViewPortDeint(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_EnableViewPortDeint(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Enable the Deinterlace on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * 
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_DisableViewPortDeint(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_DisableViewPortDeint(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Disable the Deinterlace on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * 
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_EnableViewPortAntiFlicker(u32 u32ViewPortHandle, ST_LAYER_AFParam stAFParam);
/*!\fn ErrorCode DRV_LAYER_EnableViewPortAntiFlicker(u32 u32ViewPortHandle, ST_LAYER_AFParam stAFParam)
 *
 * \brief
 * 		Enable the AntiFlicker on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	stAFParam				(Input) The structure containing the AntiFlicker parameters
 * 
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_DisableViewPortAntiFlicker(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_DisableViewPortAntiFlicker(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Disable the AntiFlicker on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_GetViewPortIORectangle(u32 u32ViewPortHandle, PST_LAYER_IORectParam pstIORectParam);
/*!\fn ErrorCode DRV_LAYER_GetViewPortIORectangle(u32 u32ViewPortHandle, PST_LAYER_IORectParam pstIORectParam)

 *
 * \brief
 * 		Get the input and output rectangles of a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pstIORectParam			(Output) The structure containing the input/output window parameters	
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_SetViewPortIORectangle(u32 u32ViewPortHandle, ST_LAYER_IORectParam stIORectParam);
/*!\fn ErrorCode DRV_LAYER_SetViewPortIORectangle(u32 u32ViewPortHandle, ST_LAYER_IORectParam stIORectParam)
 *
 * \brief
 * 		Set Input and Output viewport rectangles.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	stIORectParam			(Input) The structure containing the input/output window parameters	
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_GetViewPortSource(u32 u32ViewPortHandle, PST_LAYER_ViewPortSource  pstSource);
/*!\fn ErrorCode DRV_LAYER_GetViewPortSource(u32 u32ViewPortHandle, PST_LAYER_ViewPortSource  pstVPSource)
 *
 * \brief
 * 		Get the source attached to a viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pstVPSource				(Output) The structure containing the ViewPortSource parameters	
 * 
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */ 
 
ErrorCode DRV_LAYER_SetViewPortSource(u32 u32ViewPortHandle, ST_LAYER_ViewPortSource  stVPSource);
/*!\fn ErrorCode DRV_LAYER_SetViewPortSource(u32 u32ViewPortHandle, ST_LAYER_ViewPortSource  stVPSource)
 *
 * \brief
 * 		Set the source attached to a viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	stVPSource				(Input) The structure containing the ViewPortSource parameters	
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */ 

ErrorCode DRV_LAYER_GetViewPortConvFormat(u32 u32ViewPortHandle, PEN_DRV_LAYER_OSD_RANGE penRange, PEN_DRV_LAYER_OSD_COLORCONV penColorConv);
/*!\fn ErrorCode DRV_LAYER_GetViewPortConvFormat(u32 u32ViewPortHandle, PEN_DRV_LAYER_OSD_RANGE penRange, PEN_DRV_LAYER_OSD_COLORCONV penColorConv)
 *
 * \brief
 * 		Get the osd range and color convert to a viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	penRange				(Output) The enumerate to indicate the RGB range of osd plane	
 * \param	penColorConv				(Output) The enumerate to indicate the color conversion format of osd plane
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */ 

ErrorCode DRV_LAYER_SetViewPortConvFormat(u32 u32ViewPortHandle, EN_DRV_LAYER_OSD_RANGE enRange, EN_DRV_LAYER_OSD_COLORCONV enColorConv);
/*!\fn ErrorCode DRV_LAYER_SetViewPortConvFormat(u32 u32ViewPortHandle, EN_DRV_LAYER_OSD_RANGE enRange, EN_DRV_LAYER_OSD_COLORCONV enColorConv)
 *
 * \brief
 * 		Set the osd range and color convert to a viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	enRange				       (Input) The enumerate to indicate the RGB range of osd plane	
 * \param	enColorConv				(Input) The enumerate to indicate the color conversion format of osd plane
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */ 

u32 DRV_LAYER_GetMaxViewPortPerPlane( void );
/*!\fn ErrorCode DRV_LAYER_GetMaxViewPortPerPlane(u32 u32ViewPortHandle, EN_DRV_LAYER_OSD_RANGE enRange, EN_DRV_LAYER_OSD_COLORCONV enColorConv)
 *
 * \brief
 * 		Set the max num of viewport supported in one plane.
 *
 * \param	None
 *
 * 
 * \retval	u32 Max num of ViewPort supported in one plane
 */ 


ErrorCode DRV_LAYER_GetPaletteColor(u32 u32ViewPortHandle, u32 u32PalIndex, u32*pu32YUVColor);
/*!\fn ErrorCode DRV_LAYER_GetPaletteColor(u32 u32ViewPortHandle, u32 u32PalIndex, u32*pu32YUVColor)
 *
 * \brief
 * 		Get the color value of a given palette entry.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	u32PalIndex				(Input) Palette index from which to retrieve the color
 * \param	pu32YUVColor				(Output) Color corresponding to the specified Palette entry
 *
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */
 
ErrorCode DRV_LAYER_SetPaletteColor(u32 u32ViewPortHandle, u32 u32PalIndex, u32 u32YUVColor);
/*!\fn ErrorCode DRV_LAYER_SetPaletteColor(u32 u32ViewPortHandle, u32 u32PalIndex, u32 u32YUVColor)
 *
 * \brief
 * 		Set the color value of a given palette entry.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	u32PalIndex				(Input) Palette index from which to retrieve the color
 * \param	u32YUVColor				(Input) Color corresponding to the specified Palette entry
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_LoadPaletteColor(u32 u32ViewPortHandle, u32 u32StartIndex, u32 u32LoadNum, u32* pu32PaletteYUVData);
/*!\fn ErrorCode DRV_LAYER_LoadPaletteColor(u32 u32ViewPortHandle, u32 u32StartIndex, u32 u32LoadNum, u32* pu32PaletteYUVData)
 * \brief
 *
 * 		Load the color values from a given palette entry.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	u32StartIndex				(Input) Palette index from which to retrieve the color
 * \param	u32LoadNum				(Input) number of palette will be reload
 * \param	pu32PaletteYUVData		(Input) Color corresponding to the specified Palette entry
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INITIALISED							The driver is not initialized
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_SetViewPortARGB4444AlphaMode(u32 u32ViewPortHandle, EN_DRV_LAYER_ARGB4444ALPHAMODE enAlpha);
/*!\fn ErrorCode DRV_LAYER_SetViewPortARGB4444AlphaMode(u32 u32ViewPortHandle, EN_DRV_LAYER_ARGB4444ALPHAMODE enAlpha)
 *
 * \brief
 * 		Set the alpha mode of ARGB4444 color format.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	enAlpha				       (Input) The enumerate to indicate the alpha mode of ARGB4444 color format
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_SetViewPortARGB4444AlphaTable(u32 u32ViewPortHandle, u8* pu8AlphaValue);
/*!\fn ErrorCode DRV_LAYER_SetViewPortARGB4444AlphaTable(u32 u32ViewPortHandle, u8* pu8AlphaValue)
 *
 * \brief
 * 		Set the alpha index table of ARGB4444 color format.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pu8AlphaValue			(Input) Alpha value corresponding to the 1st alpha table entry
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_LoadCursorData(u32 u32ViewPortHandle, u32 *pu32Data);
/*!\fn ErrorCode DRV_LAYER_LoadCursorData(u32 u32ViewPortHandle, u32 *pu32Data)
 *
 * \brief
 * 		Load the data values from a started entry.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pu32Data			              (Input) Data corresponding to the started entry
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_StartJpuCpy(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_StartJpuCpy(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Start to copy the data from frame buffer by JPU module.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_StopJpuCpy(u32 u32ViewPortHandle);
/*!\fn ErrorCode DRV_LAYER_StopJpuCpy(u32 u32ViewPortHandle)
 *
 * \brief
 * 		Stop to copy the data from frame buffer by JPU module.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_CheckJpuCpyStatus(u32 u32ViewPortHandle, bool* pb8IsCopied);
/*!\fn ErrorCode DRV_LAYER_CheckJpuCpyStatus(u32 u32ViewPortHandle, bool* pb8IsCopied)
 *
 * \brief
 * 		check JPU copy mode to be copied or not
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	pb8IsCopied			       (Output) JPU copy is implemented or not 
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_SetJpuCpyType(u32 u32ViewPortHandle, bool b8IsCpyOneTime);
/*!\fn ErrorCode DRV_LAYER_SetJpuCpyType(u32 u32ViewPortHandle, bool b8IsCpyOneTime)
 *
 * \brief
 * 		Set JPU copy mode to be the scan mode or play mode
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	b8IsCpyOneTime			(Input) Enable the scan mode or the play mode
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_SetJpuCpyWindow(u32 u32ViewPortHandle, ST_LAYER_WinParam stCpyWin);
/*!\fn ErrorCode DRV_LAYER_SetJpuCpyWindow(u32 u32ViewPortHandle, ST_LAYER_WinParam stCpyWin)
 *
 * \brief
 * 		Set the destination window parameter by JPU copy mode.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	stCpyWin			              (Input) The structure containing the destination window by JPU copy
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_SetViewPortOutputRate(u32 u32ViewPortHandle, u32 u32Rate);
/*!\fn ErrorCode DRV_LAYER_SetViewPortOutputRate(u32 u32ViewPortHandle, u32 u32Rate)
 *
 * \brief
 * 		Set the output rate on a specified viewport.
 *
 * \param	u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param	u32Rate			              (Input) The output rate on a specified viewport
 * 
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE			Un-Support Device 
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_LAYER_GetVersion (u8 *pu8VersionNum);
/*!\fn ErrorCode DRV_LAYER_GetVersion (u8 *pu8VersionNum)
 *
 * \brief
 * 		Get the Module Version number of LAYER
 *
 * \param	pu8VersionNum			(Output) Version string of LAYER
 *
 *
 * \retval	ERROR_NO_ERROR			       No error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRV_LAYER_GetWindowWidthAlignment(u8 *pu8AlignOfByte);
/*!\fn ErrorCode DRV_LAYER_GetWindowWidthAlignment (u8 *pu8AlignOfByte)
 *
 * \brief
 * 		Get the Width Alignment number (in bytes) of the current IC
 *
 * \param	pu8AlignOfByte			(Output) Width Alignment value
 *
 *
 * \retval	ERROR_NO_ERROR			       No error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRA_LAYER_SetGammaTableIdx(u8 u8GammaIdx);
/*!\fn ErrorCode DRA_LAYER_SetGammaTableIdx (u8 u8GammaIdx)
 *
 * \brief
 * 		Adjust Gamma curve of image from blending0
 *
 * \param	u8GammaIdx			(Input) Gamma index for gamma table lookup (0~100, default: 50 for gamma = 1.0, from gamma > 1.0 to gamma < 1.0)
 *
 *
 * \retval	ERROR_NO_ERROR			       No error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRV_LAYER_SetBrightnessIdx(u8 u8BrightIdx);
/*!\fn ErrorCode DRV_LAYER_SetBrightnessIdx(u8 u8BrightIdx)
 *
 * \brief
 * 		Adjust brightness of image from blending0
 *
 * \param	u8BrightIdx			(Input) Brightness level (0~100, default: 50, from darkness to brightness)
 *
 *
 * \retval	ERROR_NO_ERROR			       No error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRV_LAYER_SetSaturationIdx(u8 u8SatIdx);
/*!\fn ErrorCode DRV_LAYER_SetSaturationIdx(u8 u8SatIdx)
 *
 * \brief
 *      Adjust saturation of image from blending0
 *
 * \param   u8SatIdx         (Input) Saturation level (0~100, default: 50, from pale to colorful)
 *
 *
 * \retval  ERROR_NO_ERROR                 No error
 * \retval  ERROR_BAD_PARAMETER     Bad parameter passed
 */

ErrorCode DRV_LAYER_SetHueIdx(u8 u8HIdx);
/*!\fn ErrorCode DRV_LAYER_SetHueIdx(u8 u8HIdx)
 *
 * \brief
 *      Adjust hue of image from blending0
 *
 * \param   u8SatIdx         (Input) Hue mapping level (0~100, default: 50, from negative to positive degree offset)
 *
 *
 * \retval  ERROR_NO_ERROR                 No error
 * \retval  ERROR_BAD_PARAMETER     Bad parameter passed
 */

ErrorCode DRV_LAYER_SetSharpnessIdx(u8 u8SharpIdx);
/*!\fn ErrorCode DRV_LAYER_SetSharpnessIdx(u8 u8SharpIdx)
 *
 * \brief
 *      Adjust sharpness of image from blending0
 *
 * \param   u8SatIdx         (Input) Sharpness level (0~15, default: 7, from unsharp to sharp)
 *
 *
 * \retval  ERROR_NO_ERROR                 No error
 * \retval  ERROR_BAD_PARAMETER     Bad parameter passed
 */

ErrorCode DRV_LAYER_DelayVsync( u32 u32Value );
/*!\fn ErrorCode DRV_LAYER_DelayVsync( u32 u32Value )
 *
 * \brief
 *      Wait for OSD Vsync
 *
 * \param   u32Value			(Input) The number of Vsync to wait for
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_BAD_PARAMETER     	Bad parameter passed
 */

ErrorCode DRV_LAYER_SetColorMode( u32 u32ViewPortHandle, EN_DRV_LAYER_COLORMODE enColorMode );
/*!\fn ErrorCode DRV_LAYER_SetColorMode( u32 u32ViewPortHandle, EN_DRV_LAYER_COLORMODE enColorMode )
 *
 * \brief
 *      Enable Run-Length Decode function
 *
 * \param   u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param   enColorMode				(Input) Change Color format
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_BAD_PARAMETER     	Bad parameter passed
 */

ErrorCode DRV_LAYER_SetOSDBufferAddr( u32 u32ViewPortHandle, u32 u32BufAddr );
/*!\fn DRV_LAYER_SetOSDBufferAddr( u32 u32ViewPortHandle, u32 u32BufAddr )
 *
 * \brief
 *      Set OSD Frame buffer start address
 *
 * \param   u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param   u32BufAddr					(Input) OSD Frame buffer start address
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_BAD_PARAMETER     	Bad parameter passed
 */


ErrorCode DRV_LAYER_IsRLFieldMode( bool* pbIsRLFieldMode );
/*!\fn ErrorCode DRV_LAYER_IsRLFieldMode( bool* pbIsRLFieldMode )
 *
 * \brief
 *      Get if RL field mode or not
 *
 * \param   pbIsRLFieldMode				(Output) True is Field mode is enabled
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_BAD_PARAMETER     	Bad parameter passed
 */

ErrorCode DRV_LAYER_EnableRLMode( u32 u32ViewPortHandle, bool bIsEnable );
/*!\fn ErrorCode DRV_LAYER_EnableRLMode( u32 u32ViewPortHandle, bool bIsEnable )
 *
 * \brief
 *      Enable Run-Length Decode function
 *
 * \param   u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param   bIsEnable					(Input) Enable/disable RL decode function
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_BAD_PARAMETER     	Bad parameter passed
 */

ErrorCode DRV_LAYER_SetRLBottomAddr( u32 u32ViewPortHandle, u32 u32RLBottomAddr );
/*!\fn DRV_LAYER_SetRLBottomAddr( u32 u32ViewPortHandle, u32 u32RLBottomAddr )
 *
 * \brief
 *      Set start address of RL bottom field buffer
 *
 * \param   u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param   u32RLBottomAddr			(Input) The start address of RL Bottom field. Exist only in interlace mode.
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_BAD_PARAMETER     	Bad parameter passed
 */

ErrorCode DRV_LAYER_SetRLLength( u32 u32ViewPortHandle, u8 u8Field, u32 u32RLLength );
/*!\fn DRV_LAYER_SetRLLength( u32 u32ViewPortHandle, u8 u8Field, u32 u32RLLength )
 *
 * \brief
 *      Set Length value for RL decode
 *
 * \param   u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param   u8Field						(Input) RL Top or Bottom Field (0: top, 1: bottom)
 * \param   u32RLLength				(Input) Length value for RL decode
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_BAD_PARAMETER     	Bad parameter passed
 */

ErrorCode DRV_LAYER_GetFrameInfo(u32 u32ViewPortHandle, PST_LAYER_GetFrameInfoParam pstGetFrameInfo );

/*!\fn DRV_LAYER_GetFrameInfo( u32 u32ViewPortHandle, PST_LAYER_GetFrameInfoParam pstGetFrameInfo )
 *
 * \brief
 *      Get frame information 
 *      Derive frame buffer info only when frame buffer data exists in frame buffer queue. (Imply Vdec handle != NULL)
 *
 * \param   u32ViewPortHandle				(Input)  An viewport handle number of the LAYER device
 * \param   pstGetFrameInfo					(Output) The structure containing the frame information
 *
 * \retval  ERROR_NO_ERROR                 	No error
 * \retval  ERROR_INITIALISED     	       The driver is not initialized
 */

ErrorCode DRV_LAYER_ForceFrameAddr(u32 u32ViewPortHandle, PST_LAYER_GetFrameInfoParam pstGetFrameInfo );

ErrorCode DRV_LAYER_SetIVTCModeMargin(u32 u32ViewPortHandle, ST_LAYER_IVTCModeMargin stIvtcMargin);
/*!\fn DRV_LAYER_SetIVTCModeMargin(u32 u32ViewPortHandle, ST_LAYER_IVTCModeMargin stIvtcMargin)
 *
 * \brief
 *      Set  margin info for deinterlace IVTC mode
 *
 * \param   u32ViewPortHandle			(Input) An viewport handle number of the LAYER device
 * \param   stIvtcMargin                            (Input) The structure containing the margin information
 *
 * \retval  ERROR_NO_ERROR                                      No error
 * \retval	ERROR_LAYER_UNSUPPORT_DEVICE              Un-Support Device 
 */
 
ErrorCode DRV_LAYER_GetIVTCModeMargin(u32 u32ViewPortHandle, PST_LAYER_IVTCModeMargin pstIvtcMargin);
/*!\fn DRV_LAYER_SetIVTCModeMargin(u32 u32ViewPortHandle, PST_LAYER_IVTCModeMargin pstIvtcMargin)
 *
 * \brief
 *      Get  margin info for deinterlace IVTC mode
 *
 * \param   u32ViewPortHandle           (Input) An viewport handle number of the LAYER device
 * \param   pstIvtcMargin                    (Output) The structure containing the margin information
 *
 * \retval  ERROR_NO_ERROR                                      No error
 * \retval  ERROR_LAYER_UNSUPPORT_DEVICE              Un-Support Device 
 */

ErrorCode DRV_LAYER_ForceUnmute(u32 u32ViewPortHandle, bool b8Enable, ST_LAYER_VideoFBAddr* pstAddr );
/*!\fn ErrorCode DRV_LAYER_ForceUnmute(u32 u32ViewPortHandle, bool b8Enable, ST_LAYER_VideoFBAddr* pstAddr )
 *
 * \brief
 *      Force video layer not mute 
 *      (Ex: Used when switch live channel, keep last channel's picture till next channel's picture is ready)
 *
 * \param   u32ViewPortHandle           (Input) An viewport handle number of the LAYER device
 * \param   b8Enable                    (Input) Enable force-unmute or not
 * \param   pstAddr                    (Input) Frame Buffer needed for unMute enable
 *
 * \retval  ERROR_NO_ERROR                                      No error
 * \retval  ERROR_LAYER_UNSUPPORT_DEVICE              Un-Support Device 
 */

#endif //#ifndef __LAYER_H__

