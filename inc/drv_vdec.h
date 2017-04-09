/***************************************************************************
**         Copyright (c) 2008, Novatek Inc . All rights reserved.
**         SA2, all right reserved.
**
**	Product	: NV78233A Firmware
**
**	Date		: 2008.11.03
**	Author		: Novatek (SA2)
**	Purpose	: 
**	Sources	: drv_vdec.h
****************************************************************************
**
** Modification use :
****************************************************************************
**	Update
**
**	Date  	: 2008.11.03
**	Name	: Novatek (SA2)
**	Description	: 
**
**	Item			                  Source
**	----------------------------------------		-------------------
**	. create 					            drv_vdec.h
****************************************************************************/

#ifndef __DRV_VDEC_H__
#define __DRV_VDEC_H__

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
#include "drv_event.h"
#include "drv_stc.h"

/***************************************************************************
 * FIXME, just for test, remove later
 * ************************************************************************/

typedef u32 DRV_EVT_EventID_t;


/***************************************************************************
 * Type definition
 * ************************************************************************/

typedef u32 DRV_VDEC_Handle_t;
typedef struct os_mutex_t       VDEC_Mutex_t;
typedef struct os_thread_t      VDEC_Thread_t;
typedef struct os_intr_t        VDEC_Intr_t;
typedef struct os_event_t       VDEC_Event_t;
typedef struct list_head        VDEC_List_t;


/***************************************************************************
 * Definition
 * ************************************************************************/


/***************************************************************************
 * Enumeration
 * ************************************************************************/

typedef enum
{
    EN_DRV_VDEC_BROADCAST_NULL  = 0,        /* Just for driver used */

    EN_DRV_VDEC_BROADCAST_DVB   = 0x1,
    EN_DRV_VDEC_BROADCAST_ATSC  = 0x2,
    EN_DRV_VDEC_BROADCAST_DVD   = 0x4,

    // for count
    EN_DRV_VDEC_BROADCAST_NB
} EN_DRV_VDEC_BroadcastType, *PEN_DRV_VDEC_BroadcastType;
/**
 * \brief
 * Define the type of the broadcasted stream inject to video decoder.
 */

typedef enum
{
    EN_DRV_VDEC_DECODED_PICTURES_NULL = 0,

    EN_DRV_VDEC_DECODED_PICTURES_ALL,
    EN_DRV_VDEC_DECODED_PICTURES_IP,
    EN_DRV_VDEC_DECODED_PICTURES_I,

    // for count
    EN_DRV_VDEC_DECODED_PICTURES_NB
} EN_DRV_VDEC_DecodedPicturesType, *PEN_DRV_VDEC_DecodedPicturesType;
/**
 * \brief
 * Define the type of picture decoded by the video decoder currently.
 */

typedef enum
{
    EN_DRV_VDEC_DECODE_TYPE_NULL        = 0,
    
    /* Motion */
    EN_DRV_VDEC_DECODE_TYPE_MOTION      =  0x0001,   /* This is just for driver used, not a real decode type */
    EN_DRV_VDEC_DECODE_TYPE_MPEG        =  0x0002,
    EN_DRV_VDEC_DECODE_TYPE_H264        =  0x0004,
    EN_DRV_VDEC_DECODE_TYPE_VC1         =  0x0008,
    EN_DRV_VDEC_DECODE_TYPE_MPEG4       =  0x0010,
    EN_DRV_VDEC_DECODE_TYPE_DIVX3       =  0x0020,
    EN_DRV_VDEC_DECODE_TYPE_RMVB        =  0x0040,
    EN_DRV_VDEC_DECODE_TYPE_AVS         =  0x0080,
    EN_DRV_VDEC_DECODE_TYPE_MJPEG       =  0x0100,

    /* Logo */
    EN_DRV_VDEC_DECODE_TYPE_LOGO            =  0x1000, /* This is just for driver used, not a real decode type */
    EN_DRV_VDEC_DECODE_TYPE_LOGO_MPEG  =  0x2000, 

    /* Still */
    EN_DRV_VDEC_DECODE_TYPE_STILL       =  0x10000, /* This is just for driver used, not a real decode type */
    EN_DRV_VDEC_DECODE_TYPE_JPEG        =  0x20000,
    EN_DRV_VDEC_DECODE_TYPE_JPEG_SW     =  0x40000,
    EN_DRV_VDEC_DECODE_TYPE_GIF         =  0x80000,
    EN_DRV_VDEC_DECODE_TYPE_BMP         = 0x100000,
    EN_DRV_VDEC_DECODE_TYPE_PNG         = 0x200000,
    EN_DRV_VDEC_DECODE_TYPE_TIFF        = 0x400000,

    // for count
    EN_DRV_VDEC_DECODE_TYPE_NB          = 0x1000000
} EN_DRV_VDEC_DecodeType, *PEN_DRV_VDEC_DecodeType;
/**
 * \brief
 * Define the video decode type that video decoder support.
 */

typedef enum
{
    EN_DRV_VDEC_RESOLUTION_NULL = 0,

    EN_DRV_VDEC_RESOLUTION_SD   = 0x1,
    EN_DRV_VDEC_RESOLUTION_HD   = 0x2,  

    // for count
    EN_DRV_VDEC_RESOLUTION_NB
} EN_DRV_VDEC_Resolution, *PEN_DRV_VDEC_Resolution;
/**
 * \brief
 * Define the video decode resolution that video decoder support.
 */

typedef enum
{
    EN_DRV_VDEC_SOURCE_NULL = 0,

    EN_DRV_VDEC_SOURCE_LIVE   = 0x1,
    EN_DRV_VDEC_SOURCE_STORAGE   = 0x2,  

    // for count
    EN_DRV_VDEC_SOURCE_NB
} EN_DRV_VDEC_Source, *PEN_DRV_VDEC_Source;
/**
 * \brief
 * Define the video decode resolution that video decoder support.
 */

typedef enum
{
    EN_DRV_VDEC_ASPECT_RATIO_NULL   = 0,

    EN_DRV_VDEC_ASPECT_RATIO_4_3 = 2,
    EN_DRV_VDEC_ASPECT_RATIO_16_9 = 3,
    EN_DRV_VDEC_ASPECT_RATIO_235_100 = 4,

    // for count
    EN_DRV_VDEC_ASPECT_RATIO_NB
} EN_DRV_VDEC_AspectRatio, *PEN_DRV_VDEC_AspectRatio;
/**
 * \brief
 * Define stream aspect ratio.
 */

typedef enum
{
    EN_DRV_VDEC_ERROR_RECOVERY_NULL     = 0,

    EN_DRV_VDEC_ERROR_RECOVERY_FULL     = 0x1,          //do error concealment for all codec.
    EN_DRV_VDEC_ERROR_RECOVERY_SKIP     = 0x2,          //do error concealment for all codec. when decode error occurred for H264, will skip some frames to avoid mosaic display.

    // for count
    EN_DRV_VDEC_ERROR_RECOVERY_NB
} EN_DRV_VDEC_ErrorRecoveryMode, *PEN_DRV_VDEC_ErrorRecoveryMode;
/**
 * \brief
 * Define error recovery mode that video decoder support.
 */

typedef enum
{
    EN_DRV_VDEC_FREEZE_FIELD_NULL       = 0,

    EN_DRV_VDEC_FREEZE_FIELD_TOP        = 0x1,
    EN_DRV_VDEC_FREEZE_FIELD_BOTTOM     = 0x2,
    EN_DRV_VDEC_FREEZE_FIELD_CURRENT    = 0x4,
    EN_DRV_VDEC_FREEZE_FIELD_NEXT       = 0x8,

    // for count
    EN_DRV_VDEC_FREEZE_FIELD_NB
} EN_DRV_VDEC_FreezeField, *PEN_DRV_VDEC_FreezeField;
/**
 * \brief
 * Define the freeze field.
 */

typedef enum
{
    EN_DRV_VDEC_FRAME_TYPE_FRAME_NULL   = 0,

    EN_DRV_VDEC_FRAME_TYPE_FRAME_I,
    EN_DRV_VDEC_FRAME_TYPE_FRAME_P,
    EN_DRV_VDEC_FRAME_TYPE_FRAME_B,
    EN_DRV_VDEC_FRAME_TYPE_FRAME_NONE,

    // for count
    EN_DRV_VDEC_FRAME_TYPE_FRAME_NB
} EN_DRV_VDEC_FrameType, *PEN_DRV_VDEC_FrameType;
/**
 * \brief
 * Define the frame type.
 */

typedef enum
{
    EN_DRV_VDEC_PICTURE_NULL            = 0,

    EN_DRV_VDEC_PICTURE_LAST_DECODED    = 0x1,
    EN_DRV_VDEC_PICTURE_DISPLAYED       = 0x2,

    // for count
    EN_DRV_VDEC_PICTURE_NB
} EN_DRV_VDEC_PictureType, *PEN_DRV_VDEC_PictureType;
/**
 * \brief
 * Define the different pictures from which it is possible to retrieve informations
 */

typedef enum
{
    EN_DRV_VDEC_PICTURE_STRUCTURE_NULL            = 0,

    EN_DRV_VDEC_PICTURE_STRUCTURE_TOP_FIELD,
    EN_DRV_VDEC_PICTURE_STRUCTURE_BOTTOM_FIELD,
    EN_DRV_VDEC_PICTURE_STRUCTURE_FRAME,

    // for count
    EN_DRV_VDEC_PICTURE_STRUCTURE_NB
} EN_DRV_VDEC_PictureStructure, *PEN_DRV_VDEC_PictureStructure;
/**
 * \brief
 * Define the picture encode type.
 */

typedef enum
{
    EN_DRV_VDEC_SCAN_TYPE_INTERLACE     = 0x1,
    EN_DRV_VDEC_SCAN_TYPE_PROGRESSIVE   = 0x2,

    // for count
    EN_DRV_VDEC_SCAN_TYPE_NB
} EN_DRV_VDEC_ScanType, *PEN_DRV_VDEC_ScanType;
/**
 * \brief
 * Define the stream scan types.
 */

typedef enum
{
    EN_DRV_VDEC_STOP_WHEN_NEXT_REFERENCE,
    EN_DRV_VDEC_STOP_WHEN_END_OF_DATA,
    EN_DRV_VDEC_STOP_NOW,
    EN_DRV_VDEC_STOP_NOW_WITHOUT_RESET_STC,
    EN_DRV_VDEC_STOP_WHEN_NEXT_I,

    // for count
    EN_DRV_VDEC_STOP_NB
} EN_DRV_VDEC_StopMode, *PEN_DRV_VDEC_StopMode;
/**
 * \brief
 * Define the different stop modes.
 */

typedef enum
{
	EN_DRV_VDEC_COLOR_TYPE_NULL 	 = 0x0,
	EN_DRV_VDEC_COLOR_TYPE_YUV420	 = 0x1,
	EN_DRV_VDEC_COLOR_TYPE_YUV422V   = 0x2,
	EN_DRV_VDEC_COLOR_TYPE_YUV422H   = 0x4,
	EN_DRV_VDEC_COLOR_TYPE_YUV444	 = 0x8,
	EN_DRV_VDEC_COLOR_TYPE_YUV400	 = 0x10,  
	EN_DRV_VDEC_COLOR_TYPE_IDX_4BIT  = 0x20,  
	EN_DRV_VDEC_COLOR_TYPE_IDX_8BIT  = 0x40,  
	EN_DRV_VDEC_COLOR_TYPE_RGB565	 = 0x80,  
	EN_DRV_VDEC_COLOR_TYPE_ARGB1555  = 0x100, 
	EN_DRV_VDEC_COLOR_TYPE_ARGB4444  = 0x200, 
	EN_DRV_VDEC_COLOR_TYPE_ARGB8888  = 0x400, 
	EN_DRV_VDEC_COLOR_TYPE_RGBA5551  = 0x800, 
	EN_DRV_VDEC_COLOR_TYPE_RGBA4444  = 0x1000,
	EN_DRV_VDEC_COLOR_TYPE_RGBA8888  = 0x2000,
	EN_DRV_VDEC_COLOR_TYPE_CMYK		 = 0x4000,	
	EN_DRV_VDEC_COLOR_TYPE_RGB_24BIT = 0x8000,
	EN_DRV_VDEC_COLOR_TYPE_ARGB_32BIT= 0x10000,
	EN_DRV_VDEC_COLOR_TYPE_RGBA_32BIT= 0x20000,
	EN_DRV_VDEC_COLOR_TYPE_Y_UV_INTERLACE_420  = 0x40000,
	EN_DRV_VDEC_COLOR_TYPE_Y_UV_INTERLACE_422H = 0x80000,
	EN_DRV_VDEC_COLOR_TYPE_Y_UV_INTERLACE_422V = 0x100000,
	EN_DRV_VDEC_COLOR_TYPE_Y_UV_INTERLACE_444  = 0x200000,
    // for count
    EN_DRV_VDEC_COLOR_TYPE_NB
} EN_DRV_VDEC_ColorType, *PEN_DRV_VDEC_ColorType;
/**
 * \brief
 * Define the color types for a picture.
 */

typedef enum
{
    EN_DRV_VDEC_IMAGE_DECODE_MODE_HEADER,
    EN_DRV_VDEC_IMAGE_DECODE_MODE_PICTURE,
    EN_DRV_VDEC_IMAGE_DECODE_MODE_THUMBNAIL,

    // for count
    EN_DRV_VDEC_IMAGE_DECODE_MODE_NB
} EN_DRV_VDEC_ImageDecodeMode, *PEN_DRV_VDEC_ImageDecodeMode;
/**
 * \brief
 * Define the decode modes for still image decoder support.
 */

enum vdec_error_e
{
    ERROR_VDEC_BASE                   = ERROR_BASE_DRV_VDEC,
    ERROR_VDEC_INVALID_DEVICE,
    ERROR_VDEC_DEVICE_NOT_INIT,
    ERROR_VDEC_NO_FREE_DEVICE,
    ERROR_VDEC_DUPLICATE_DEVICE_NAME,
    ERROR_VDEC_INVALID_HANDLE,
    ERROR_VDEC_NO_FREE_HANDLE,
    ERROR_VDEC_HANDLE_IN_USE,
    ERROR_VDEC_NO_FREE_HW_RESOURCE,
    ERROR_VDEC_CREATE_THREAD_FAIL,
    ERROR_VDEC_DECODER_NOT_STOPPED,
    ERROR_VDEC_UNKNOWN_DECODE_TYPE,
    ERROR_VDEC_PIC_INFO_NOT_READY,
    ERROR_VDEC_FREE_MEMORY_FAIL,
    ERROR_VDEC_ALLOCATE_MEMORY_FAIL,
    ERROR_VDEC_PTS_BUFFER_OVERFLOW,
    ERROR_VDEC_PTS_NOT_FOUND,
    ERROR_VDEC_SPEED_NOT_SUPPORT,
    ERROR_VDEC_RESTART_FAIL,
    ERROR_VDEC_STOP_FAIL,
    ERROR_VDEC_OPEN_FAIL,
    ERROR_VDEC_CLOSE_FAIL
};
/**
 * \brief
 * Define the VDEC error code.
 */

typedef enum
{
    EN_DRV_VDEC_EVENT_START                     = 0,
    EN_DRV_VDEC_EVENT_STOP,
    EN_DRV_VDEC_EVENT_DECODE_ERROR,
    EN_DRV_VDEC_EVENT_DECODE_TIMEOUT,    
    EN_DRV_VDEC_EVENT_DECODE_OK,
    EN_DRV_VDEC_EVENT_UNSUPPORT_FORMAT,
    EN_DRV_VDEC_EVENT_PIC_SIZE_CHANGE,
    EN_DRV_VDEC_EVENT_FRAME_RATE_CHANGE,
    EN_DRV_VDEC_EVENT_ASPECT_RATIO_CHANGE,
    EN_DRV_VDEC_EVENT_AFD_CHANGE,
    EN_DRV_VDEC_EVENT_DECODE_FRAME,
    EN_DRV_VDEC_EVENT_DECODE_PICTURE_PROCESS,
    EN_DRV_VDEC_EVENT_BUFFER_UNDERFLOW,
    EN_DRV_VDEC_EVENT_DECODE_FSEEK
}EN_DRV_VDEC_Event, *PEN_DRV_VDEC_Event;
/**
 * \brief
 * Define the VDEC event ID.
 */

typedef enum
{
    EN_DRV_VDEC_PIC_INFO_COLOR_TYPE                     = 0x0001,
    EN_DRV_VDEC_PIC_INFO_ASPECT_RATIO                   = 0x0002,
    EN_DRV_VDEC_PIC_INFO_CODED_PIC_SIZE                 = 0x0004,
    EN_DRV_VDEC_PIC_INFO_FRAME_RATE                     = 0x0008,
    EN_DRV_VDEC_PIC_INFO_ERROR_RATE                     = 0x0010,
    EN_DRV_VDEC_PIC_INFO_AFD                            = 0x0020,
    EN_DRV_VDEC_PIC_INFO_DISP_PIC_SIZE                  = 0x0040,
    EN_DRV_VDEC_PIC_INFO_DISP_PIC_ADDR                  = 0x0080,
    EN_DRV_VDEC_PIC_INFO_DISP_PIC_WIDTH                 = 0x0100,
    EN_DRV_VDEC_PIC_INFO_EXIF                           = 0x0200,
}EN_DRV_VDEC_PicInfo, *PEN_DRV_VDEC_PicInfo;
/**
 * \brief
 * Define the VDEC picture information items.
 */

typedef enum
{
    EN_DRV_VDEC_CHIP_INFO_310                     = 0,
	EN_DRV_VDEC_CHIP_INFO_316                        ,	
	EN_DRV_VDEC_CHIP_INFO_320					     ,
}EN_DRV_VDEC_ChipInfo, *PEN_DRV_VDEC_ChipInfo;
/**
 * \brief
 * Define the VDEC chip information items.
 */



/***************************************************************************
 * Structure
 * ************************************************************************/

typedef struct
{
    VDEC_List_t     listPTS;                            /* linked list structure of PTS */
    u64             u64TimeStamp;                       /* Time stamp of this PTS */
    u32             u32PTS;                             /* bit31~bit0 of PTS */
    u32             u32PTS33;                           /* bit32 of PTS */
    u32             u32BitBufAddr;                      /* describe this PTS is which frame in video bitstream buffer */
} ST_DRV_VDEC_PTS, *PST_DRV_VDEC_PTS;
/*!
* Define a structure to save 33 bits PTS value.
*/


#define DRV_EXIF_ASCII_LENGTH 31
#define DRV_EN_EXIF_INFO_QUERY_NUMBER 21

typedef struct
{
	 // need remove old exif - elaine
	u32   s32PicX;
	u32   s32PicY;
	u32   s32BitPerSample[3];
	u32   s32Compression; // 1 for uncompressed / 6 for compressed(jpeg)
	u32   s32PixelComposition; // 2 for RGB / 6 for YCbCr
	u32   s32SamplePerPixel; 
	u32   s32PlanrConfig; // 1 for chunky / 2 for planar
	u32   s32YCbCrSubSample; // 00020002 for YCbCr 4:2:0 / 00020001 for YCbCr 4:2:2
	u32   u32JpegOffset;
	u32   u32JpegThumbSize;
   
    u8    u8Exif_Make[DRV_EXIF_ASCII_LENGTH+1];
    u8    u8Exif_Model[DRV_EXIF_ASCII_LENGTH+1];
    u8    u8Exif_Date_Time[DRV_EXIF_ASCII_LENGTH+1];
    u32   u32Exif_Is_Progressive;
    u32   u32Exif_Is_Thumbnail;
    u32   u32Exif_Compression;
    u32   u32Exif_PhotometricInterp;
    u32   u32Exif_Orientation;
    u32   u32Exif_ISO_Speed_Rating;
    u32   u32Exif_Metering_Mode;
    u32   u32Exif_Flash;
    u32   u32Exif_Color_Space;
    u32   u32Exif_Valid_Image_Width;
    u32   u32Exif_Valid_Image_Height;
    u32   u32Exif_White_Balance;
    union {
            struct {
                    u32   u32Exif_X_Resolution_n;
                    u32   u32Exif_X_Resolution_d;
                   };
            u64 unExif_X_Resolution;
          };
    union {
           struct {
                   u32   u32Exif_Y_Resolution_n;
            	   u32   u32Exif_Y_Resolution_d;
	              };
			u64 unExif_Y_Resolution;
	      };
    union {
        	struct {
					u32   u32Exif_Exposure_Time_n;
					u32   u32Exif_Exposure_Time_d;
	               };
	        u64 unExif_Exposure_Time;
	      };
    union {
	        struct {
			        u32   u32Exif_Shutter_Speed_n;
					u32   u32Exif_Shutter_Speed_d;
				   };
		    u64 unExif_Shutter_Speed;
		  };
    union {
        	struct {
            	    u32   u32Exif_Aperture_n;
            	    u32   u32Exif_Aperture_d;
                   };
        	u64 unExif_Aperture;
    	  };
	union {
        	struct {
            		u32   u32Exif_Focal_Length_n;
            		u32   u32Exif_Focal_Length_d;
            		};
        	u64 unExif_Focal_Length;
    	  };
    u8    Exif_Valid[DRV_EN_EXIF_INFO_QUERY_NUMBER];

} ST_DRV_VDEC_EXIFInfo, *PST_DRV_VDEC_EXIFInfo;




/**
 * \brief
 * Define EXIF information.
 */

typedef struct
{
    EN_DRV_VDEC_ColorType               enCodedColorSpace;              /* Color space of stream */
    EN_DRV_VDEC_ColorType               enOutputColorSpace;             /* User wanted output color space */
    EN_DRV_VDEC_AspectRatio             enAspectRatio;                  /* Aspect ratio of stream */
    u32                                 u32CodedPicHSize;               /* Picture width */
    u32                                 u32CodedPicVSize;               /* Picture height */
    f32                                 f32FrameRate;                   /* Frame rate of stream */
    u32                                 u32ErrorRate;                   /* Error rate of each frame */
    u32                                 u32ProgSeq;
    u8                                   u8AFD;

    // IMAGE  & LOGO
    u32                                 u32DisplayPicAddr;              /* Picture buffer Start addresss */
    u32                                 u32DisplayChromaAddr;           /* Picture buffer Chroma addresss */
    u32                                 u32DisplayWindow;               /* Picture buffer WindowsWidth */

    // IMAGE only
    u32                                 u32DisplayPicHSize;             /* Picture decode width */
    u32                                 u32DisplayPicVSize;             /* Picture decode height */
	u32									u32IsThumbnail;					/* Picture has thumbnail */
	EN_DRV_VDEC_ColorType				enPixfmt;					    /* Picture color format */

    // JPEG only
    ST_DRV_VDEC_EXIFInfo                stEXIFInfo;                     /* JPEG EXIF information */

    u32                               u32PicInfoValidity;              /* Check validity of picture information */
} ST_DRV_VDEC_PictureInfo, *PST_DRV_VDEC_PictureInfo;
/**
 * \brief
 * Define picture information.
 */

typedef struct
{
    EN_DRV_VDEC_DecodeType                      enWantDecodeType;
    EN_DRV_VDEC_Resolution                      enWantResolution;
    EN_DRV_VDEC_ColorType                       enWantOutputColorType;

    EN_DRV_VDEC_BroadcastType                   enSupportedBroadcastType;
    EN_DRV_VDEC_ColorType                       enSupportedInputColorType;
    EN_DRV_VDEC_ColorType                       enSupportedOutputColorType;
    EN_DRV_VDEC_ErrorRecoveryMode               enSupportedErrorRecoveryMode;
    EN_DRV_VDEC_FreezeField                     enSupportedFreezeField;
    EN_DRV_VDEC_ScanType                        enSupportedScanType;
    EN_DRV_VDEC_Resolution                      enSupportedResolution;
	EN_DRV_VDEC_ChipInfo						enChipInfo;
    u32                                         u32SupportedDecodeType;

    u32                                         u32BitstreamBufferMinimumRequiredSize;  /* Size of bitstream buffer minimum required by video decoder, unit : BYTE */
    u32                                         u32BitstreamBufferAlignLimitation;      /* Align limitation of bitstream buffer, unit : BYTE */

    u32                                         u32FrameBufferMinimumRequiredSize;      /* Size of frame buffer minimum required by video decoder, unit : BYTE */
    u32                                         u32FrameBufferAlignLimitation;          /* Align limitation of frame buffer, unit : BYTE */

    u32                                         u32WorkBufferMinimumRequiredSize;      /* Size of Work buffer minimum required by video decoder, unit : BYTE */
    u32                                         u32WorkBufferAlignLimitation;          /* Align limitation of Work buffer, unit : BYTE */

    //LOGO only
    u32                                         u32LogoFrameBufferMinimumRequiredSize;      /* Size of logo frame buffer minimum required by video decoder, unit : BYTE */
    u32                                         u32LogoFrameBufferAlignLimitation;          /* Align limitation of logo frame buffer, unit : BYTE */

    u32                                         u32MaxDeviceNb;                         /* Max number of device can be used concurrently */
    u32                                         u32MaxHandleNb;                           /* Max number of open handle per device */
} ST_DRV_VDEC_Capability, *PST_DRV_VDEC_Capability;
/**
 * \brief
 * Define the supported/unsupported features and limitation of the video decoder.
 */

typedef struct
{
    bool    b8Enable;
    u32      u32NotificationsToSkip;
} ST_DRV_VDEC_ConfigureEventParams, *PST_DRV_VDEC_ConfigureEventParams;
/**
 * \brief
 * Define the parameters for configure an event notification.
 */

typedef struct
{
    EN_DRV_VDEC_FreezeField     enFreezeField;
} ST_DRV_VDEC_FreezeParams, *PST_DRV_VDEC_FreezeParams;
/**
 * \brief
 * Define the freeze parameters.
 */

typedef struct
{
	os_mempool_handle			u32MemHandle;				/*!< A memory pool handle for VDEC module	*/
    u32                         u32UserDataSize;
} ST_DRV_VDEC_InitParams, *PST_DRV_VDEC_InitParams;
/**
 * \brief
 * Define the parameters of initialization.
 */

typedef struct
{
    // Decode type, resolution and source
    EN_DRV_VDEC_DecodeType          enDecodeType;                /* Want decode type */
    EN_DRV_VDEC_Resolution             enResolution;                      /* Want decode resolution */
    EN_DRV_VDEC_Source                 enSource;                          /* Want decode source */ 
    EN_DRV_VDEC_ErrorRecoveryMode enErrRecoveryMode;

    // Event handle for VDEC
    u32                             u32EvtHandle;

    // Bitstream buffer setting
    bool                           b8BitstreamBufferAllocated;     /* Bitstream buffer allocated by middleware or vdec driver */
    u32                             u32BitstreamBufferAddress;        /* Bitstream buffer start address */
    u32                             u32BitstreamBufferSize;         /* unit : BYTE */

    // Frame buffer setting
    bool                           b8FrameBufferAllocated;         /* Bitstream buffer allocated by middleware or vdec driver */
    u32                             u32FrameBufferAddress;          /* Bitstream buffer start address */
    u32                             u32FrameBufferSize;             /* unit : BYTE */

    // Work buffer setting
    bool                           b8WorkBufferAllocated;         /* Work buffer allocated by middleware or vdec driver */
    u32                             u32WorkBufferAddress;          /* Work buffer start address */
    u32                             u32WorkBufferSize;             /* unit : BYTE */


    os_mempool_handle               u32AVMemHandle;                 /* av memory pool handle, if middleware want driver to allocate bitstream/frame buffer, need give memory pool handle to driver */
    
    // For Mpeg4, H.264, Motion JPG only
    s32								s32FrameRate;					/* Frame Rate */

    // For motion only
    u32                             u32VideoSyncDriftThreshold;     /* Threshold to do video syncchronize or not */
    DRV_STC_Handle_t                u32STCHandle;                   /* STC handle for A/V sync */
    
    // For still image decode only
    EN_DRV_VDEC_ImageDecodeMode     enStillImageDecodeMode;         /* for still image only, ex. HEADER(EXIF), thumbnail, ... */
    u32                             u32RequiredPictureHSize;        /* set desire limitation of picture output width, UNIT : pixel */
    u32                             u32RequiredPictureVSize;        /* set desire limitation of picture output height, UNIT : pixel */
    EN_DRV_VDEC_ColorType           enOutputColorType;              /* for still image only, default is YUV420(video plane) */
    u32                             u32FileSize;       

    bool                            b8IsPTSReOrder;                 /* True:PTS need to be reordered as B-Frame */
    bool                            b8IsVFR;                            /* True:variable frame rate*/

    u32                            u32LogoFramebufAddress;
    u32                            u32LogoFramebufSize;

    u32                            u32SkipErrorRatio;
     
} ST_DRV_VDEC_OpenParams, *PST_DRV_VDEC_OpenParams;
/**
 * \brief
 * Define the parameters of open.
 */

typedef struct
{
    bool                        b8RealTime;                      /* RealTime mode or file play mode */
    bool                        b8UpdateDisplay;                 /* Display decode content or not */
    bool                        b8DecodeOnce;                    /* if TRUE, decode 1 picture, then VDEC will stop itself, ex. SCAN I-frame or still image */
    EN_DRV_VDEC_BroadcastType    enBroadcastType;                 /* Broadcast type of input stream */
} ST_DRV_VDEC_StartParams, *PST_DRV_VDEC_StartParams;
/**
 * \brief
 * Define the parameters of start.
 */

typedef struct
{
    bool       b8ForceTerminate;
} ST_DRV_VDEC_TermParams, *PST_DRV_VDEC_TermParams;
/**
 * \brief
 * Define the parameters of terminate.
 */

typedef struct
{
    bool           b8Enable;                               /* Enable/disable video synchronize */
    u32             u32VideoSyncDriftThreshold;             /* Threshold to do video syncchronize or not */
} ST_DRV_VDEC_CtrlSyncParams, *PST_DRV_VDEC_CtrlSyncParams;


/***************************************************************************
 * API
 * ************************************************************************/
ErrorCode DRV_VDEC_GetMotionCountInfo(const DRV_VDEC_Handle_t Handle, u32 * u32GetMotionThreadCnt, u32 * u32GetMotionTimeOutCnt);
/*!
\fn ErrorCode DRV_VDEC_GetMotionCountInfo(const DRV_VDEC_Handle_t Handle, u32 * u32GetMotionThreadCnt, u32 * u32GetMotionTimeOutCnt)
\brief Get MotionThreadCounter and MotionDecodeTimeOutCounter.
\param Handle IN : Handle of the video driver.
\param  u32GetMotionThreadCnt IN : To get MotionThread Counter.
\param  u32GetMotionTimeOutCnt IN : To get Motion DecodeTimeOut Counter.
\return ErrorCode - Status defined in Error code.
*/


ErrorCode DRV_VDEC_CheckDecodeStopped(const DRV_VDEC_Handle_t Handle);
/*!
\fn ErrorCode DRV_VDEC_CheckDecodeStopped(const DRV_VDEC_Handle_t Handle)
\brief Check decoder is stop.
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_GetWaitValidSTCFlag(const DRV_VDEC_Handle_t Handle, pu8 pu8WaitValidSTCFlag);
/*!\fn ErrorCode DRV_VDEC_GetWaitValidSTCFlag(const DRV_VDEC_Handle_t Handle, pu8 pu8WaitValidSTCFlag)
 *
 * \brief
 *      Get status of video decoder
 *
 * \param Handle IN : Handle of the video driver.
 * \param pu8WaitValidSTCFlag OUT :  video decoder WaitValidSTCFlag
 *
 * \return  VDEC Operation Error Code
 * \retval  ERROR_NO_ERROR          no error
 */

ErrorCode DRV_VDEC_GetVersion(u8 **pu8Version);
/*!\fn ErrorCode DRV_VDEC_GetVersion(u8 *pu8Version)
 *
 * \brief
 * 		Get info of the module version
 *
 * \param	pu8Version  			(Output) Version string
 *
 * \return	VDEC Operation Error Code
 * \retval	ERROR_NO_ERROR			no error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

ErrorCode DRV_VDEC_GetCapability(const DRV_DeviceNameType DeviceName, PST_DRV_VDEC_Capability const pstCapability);
/*!
\fn ErrorCode DRV_VDEC_GetCapability(const DRV_DeviceNameType DeviceName, const PST_DRV_VDEC_Capability pstCapability)
\brief Retrieves the capabilities of the driver.
\param DeviceName IN : Name of the Video Decoder from which to get capabilities.
\param pstCapability IN : Allocated structure
	OUT : Structure filled with capabilities of the implementation of the driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Init(const DRV_DeviceNameType DeviceName, const PST_DRV_VDEC_InitParams const pstInitParams);
/*!
\fn ErrorCode DRV_VDEC_Init(const DRV_DeviceNameType DeviceName, const PST_DRV_VDEC_InitParams pstInitParams)
\brief Initializes a Video Decoder and gives it the name DeviceName.
\param DeviceName IN : Name of the Video Decoder to initialize.
\param pstInitParams IN : parameters to initialise the Video Decoder.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Open(const DRV_DeviceNameType DeviceName, const PST_DRV_VDEC_OpenParams const pstOpenParams, DRV_VDEC_Handle_t * const Handle);
/*!
\fn ErrorCode DRVVID_Open()
\brief Shares the named Video Decoder usage.
\param DeviceName Name of the Video Decoder to open.
\param Params Configuration parameters.
\param Handle IN : Pointer to a handle
	OUT : Handle on open connection to the Video Decoder
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Close(const DRV_VDEC_Handle_t Handle);
/*!
\fn ErrorCode DRV_VDEC_Close(const DRV_VDEC_Handle_t Handle)
\brief Closes an opened connection.
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Term(const DRV_DeviceNameType DeviceName, const PST_DRV_VDEC_TermParams const pstTermParams);
/*!
\fn ErrorCode DRV_VDEC_Term(const DRV_DeviceNameType DeviceName, const PST_DRV_VDEC_TermParams pstTermParams)
\brief Terminates the Video Decoder and let the hardware in the specified state.
\param DeviceName Name of an initialised device.
\param pstTermParams Configuration parameters of the hardware.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_ConfigureEvent(const DRV_VDEC_Handle_t Handle, const DRV_EVT_EventID_t Event, const PST_DRV_VDEC_ConfigureEventParams const pstCfgEvtParams);
/*!
\fn ErrorCode DRV_VDEC_ConfigureEvent(const DRV_VDEC_Handle_t Handle, const DRV_EVT_EventID_t Event, const PST_DRV_VDEC_ConfigureEventParams pstCfgEvtParams)
\brief Configures notification of video driver events.
\param Handle IN : Handle of the video driver.
\param Event IN : Event to configure.
\param pstCfgEvtParams IN : Parameters required to configure an event.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_ControlSynchronisation(const DRV_VDEC_Handle_t Handle, const PST_DRV_VDEC_CtrlSyncParams const pstCtrlSyncParams);
/*!
\fn ErrorCode DRV_VDEC_ControlSynchronisation(const DRV_VDEC_Handle_t Handle, const bool b8Enable)
\brief Enable/Disables automatic video synchronization with local system clock.
\param Handle IN : Handle of the video driver.
\param b8Enable IN : Enable/Disable video synchronization.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_StartUpdatingDisplay(const DRV_VDEC_Handle_t Handle);
/*!
\fn ErrorCode DRV_VDEC_StartUpdatingDisplay(const DRV_VDEC_Handle_t Handle)
\brief Starts updating the display, when STVID_Start() was called with no update of display.
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Start(const DRV_VDEC_Handle_t Handle, const PST_DRV_VDEC_StartParams const pstStartParams);
/*!
\fn ErrorCode DRV_VDEC_Start(const DRV_VDEC_Handle_t Handle, const PST_DRV_VDEC_StartParams const pstStartParams)
\brief Starts the decode and display of the specified data.
\param Handle IN : Handle of the video driver.
\param pstStartParams IN : Decoding and display parameters
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Stop(const DRV_VDEC_Handle_t Handle, const EN_DRV_VDEC_StopMode enStopMode, const PST_DRV_VDEC_FreezeParams const pstFreezeParams);
/*!
\fn ErrorCode DRV_VDEC_Stop(const DRV_VDEC_Handle_t Handle, const EN_DRV_VDEC_StopMode enStopMode, const PST_DRV_VDEC_FreezeParams const pstFreezeParams)
\brief Stops the decoding and the display.
\param Handle IN : Handle of the video driver.
\param enStopMode IN : Indicates when to stop decoding.
\param pstFreezeParams IN : Indicates how to freeze the picture if required.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Step(const DRV_VDEC_Handle_t Handle);
/*!
\fn ErrorCode DRV_VDEC_Step(const DRV_VDEC_Handle_t Handle)
\brief Displays next field when paused or freezed.
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Freeze(const DRV_VDEC_Handle_t Handle, const PST_DRV_VDEC_FreezeParams const pstFreezeParams);
/*!
\fn ErrorCode DRV_VDEC_Freeze(const DRV_VDEC_Handle_t Handle, const PST_DRV_VDEC_FreezeParams pstFreezeParams)
\brief Freezes the display, while decode goes on.
\param Handle IN : Handle of the video driver.
\param pstFreezeParams IN : Display picture freezing method to be used.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Pause(const DRV_VDEC_Handle_t Handle, const PST_DRV_VDEC_FreezeParams const pstFreezeParams);
/*!
\fn ErrorCode DRV_VDEC_Pause(const DRV_VDEC_Handle_t Handle, const PST_DRV_VDEC_FreezeParams const pstFreezeParams)
\brief Pauses the decoding.
\param Handle IN : Handle of the video driver.
\param pstFreezeParams IN : Display picture freezing method to be used.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_Resume(const DRV_VDEC_Handle_t Handle);
/*!
\fn ErrorCode DRV_VDEC_Resume(const DRV_VDEC_Handle_t Handle)
\brief Resumes a previously paused or freezed decoding.
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_GetPictureInfo(const DRV_VDEC_Handle_t Handle, const EN_DRV_VDEC_PictureType enPictureType, u32 u32GetPicInfoItems, PST_DRV_VDEC_PictureInfo pstPictureInfo);
/*!
\fn ErrorCode DRV_VDEC_GetPictureInfo(const DRV_VDEC_Handle_t Handle, const EN_DRV_VDEC_PictureType enPictureType, PST_DRV_VDEC_PictureInfo pstPictureInfo)
\brief Retrieves informations on a given picture.
\param Handle IN : Handle of the video driver.
\param enPictureType IN : Picture from which to get informations.
\param u32GetPicInfoItems IN : The param is passed by user to determine those picture info items are required. Please reference  EN_DRV_VDEC_PicInfo.
\param pstPictureInfo IN : pointer on an allocated structure
	OUT : structure filled with the picture parameters.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_InjectDiscontinuity(const DRV_VDEC_Handle_t Handle);
/*!
\fn ErrorCode DRV_VDEC_InjectDiscontinuity(const DRV_VDEC_Handle_t Handle)
\brief Informs the video driver that a discontinuity will occur in data injection.
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_SetErrorRecoveryMode(const DRV_VDEC_Handle_t Handle, const EN_DRV_VDEC_ErrorRecoveryMode enErrRecoveryMode);
/*!
\fn ErrorCode DRV_VDEC_SetErrorRecoveryMode(const DRV_VDEC_Handle_t Handle, const EN_DRV_VDEC_ErrorRecoveryMode enErrRecoveryMode)
\brief Defines the behavior of the video driver regarding error recovery.
\param Handle IN : Handle of the video driver.
\param enErrRecoveryMode IN : Error recovery mode.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_GetErrorRecoveryMode(const DRV_VDEC_Handle_t Handle, PEN_DRV_VDEC_ErrorRecoveryMode const penErrRecoveryMode);
/*!
\fn ErrorCode DRV_VDEC_GetErrorRecoveryMode(const DRV_VDEC_Handle_t Handle, PEN_DRV_VDEC_ErrorRecoveryMode const penErrRecoveryMode)
\brief Retrieves the current error recovery mode for the specified video driver.
\param Handle IN : Handle of the video driver.
\param penErrRecoveryMode IN : pointer to an allocated DRVVID_ErrorRecoveryMode_t structure.
	OUT : Current error recovery mode.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_SetSpeed(const DRV_VDEC_Handle_t Handle, const s32 s32Speed);
/*!
\fn ErrorCode DRV_VDEC_SetSpeed(const DRV_VDEC_Handle_t Handle, const s32 s32Speed)
\brief Defines the speed of the display (trickmodes).
\param Handle IN : Handle of the video driver.
\param s32Speed IN : Speed of display, in percentage of the nominal speed.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_GetSpeed(const DRV_VDEC_Handle_t Handle, s32 * const ps32Speed);
/*!
\fn ErrorCode DRV_VDEC_GetSpeed(const DRV_VDEC_Handle_t Handle, s32 * const ps32Speed)
\brief Retrieves the current play speed.
\param Handle IN : Handle of the video driver.
\param ps32Speed IN : Pointer to an allocated S32
	OUT: Current speed of the video decoder.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_SetShiftTime(const DRV_VDEC_Handle_t Handle, const s32 s32Shifttime);
/*!
\fn ErrorCode DRV_VDEC_SetShiftTime(const DRV_VDEC_Handle_t Handle, const s32 s32Shifttime)
\brief Update shift time of video rendering \n
    if shift_time > 0, the video will be rendered later than original sync time \n
    if shift_time = 0, the video will be rendered with original sync time \n
    if shift_time < 0, the video will be rendered earlier than original sync time
\param Handle IN : Handle of the video driver.
\param s32Shifttime IN : The shift time(ms) of video rendering 
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_GetShiftTime(const DRV_VDEC_Handle_t Handle, s32 * const ps32Shifttime);
/*!
\fn ErrorCode DRV_VDEC_GetShiftTime(const DRV_VDEC_Handle_t Handle, s32 * const ps32Shifttime)
\brief Retrieves the current shift time.
\param Handle IN : Handle of the video driver.
\param ps32Speed IN : Pointer to an allocated S32
	OUT: Current shift time of the video.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_UpdatePTS(DRV_VDEC_Handle_t Handle, PST_DRV_VDEC_PTS pstVideoPTS);
/*!
\fn ErrorCode DRV_VDEC_UpdatePTS(PST_DRV_VDEC_PTS pstVideoPTS, u32 u32BitBufAddr)
\brief Give data provider a interface to update video PTS.
\param Handle IN : Handle of the video driver.
\param PST_DRV_VDEC_PTS IN : Pointer to structure of video PTS.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_InformWriteAddress(const DRV_VDEC_Handle_t Handle, u32 u32WriteAddress);
/*!
\fn ErrorCode DRV_VDEC_InformWriteAddress(const DRV_VDEC_Handle_t Handle, u32 u32WriteAddress)
\brief Inform write address of bitstream buffer to video decoder.
\param Handle IN : Handle of the video driver.
\param u32WriteAddress IN : Current write address of bitstream buffer.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_GetReadAddress(const DRV_VDEC_Handle_t Handle, u32 * pu32ReadAddress);
/*!
\fn ErrorCode DRV_VDEC_GetReadAddress(const DRV_VDEC_Handle_t Handle, u32 * pu32ReadAddress)
\brief Get read address of bitstream buffer from video decoder.
\param Handle IN : Handle of the video driver.
\param pu32ReadAddress IN : pointer to an allocated u32.
                       OUT : Current read address of bitstream buffer.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_GetVideoBufRem(const DRV_VDEC_Handle_t Handle, u32 * pu32VBufRem);


ErrorCode DRV_VDEC_SetBufferUnderflowThreshold(const DRV_VDEC_Handle_t Handle, u32 u32Threshold);
/*!
\fn ErrorCode DRV_VDEC_SetBufferUnderflowThreshold(const DRV_VDEC_Handle_t Handle, u32 u32Threshold)
\brief Set underflow threshold of video bitstream buffer.
\param Handle IN : Handle of the video driver.
\param u32Threshold IN : underflow threshold of video bitstream buffer.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_VSyncWakeup(const DRV_VDEC_Handle_t Handle);
/*!
\fn ErrorCode DRV_VDEC_VSyncWakeup(const DRV_VDEC_Handle_t Handle)
\brief TVE V-sync callback to wake-up decode thread
\param Handle IN : Handle of the video driver.
\return ErrorCode - Status defined in Error code.
*/

ErrorCode DRV_VDEC_SetDataComplete(const DRV_VDEC_Handle_t Handle, u8 u8DataComplete);
/*!
\fn ErrorCode DRV_VDEC_SetDataComplete(const DRV_VDEC_Handle_t Handle, u8 u8DataComplete)
\brief Set Data transfor complete
\param Handle IN : Handle of the video driver.
\param u8DataComplete : Data complete status.
\return ErrorCode - Status defined in Error code.
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __DRV_VDEC_H__ */
