//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author		:
//	Purpose	: Provide HDMI Control
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

#ifndef __DRV_HDMI_H__
#define __DRV_HDMI_H__

#include "def_type.h"
#include "def_err.h"
#include "os.h"

#include "drv_vtg.h"
#include "drv_vdec.h"
#include "drv_audio.h"
#include "sen5_sw_config.h"


#define DRV_HDMI_MAX_EDID_RETRY_TIMES           (10)                /*!< The maximum retry time to get the Sink EDID	*/

#define DRV_HDMI_MAX_CEA_EXT_NUM				(4)					/*!< The maximum supported CEA extension number of the Sink EDID	*/
#define DRV_HDMI_MAX_VIDEO_DESCRIPTOR_NUM		(64)				/*!< The maximum supported video descriptor number					*/
#define DRV_HDMI_MAX_AUDIO_DESCRIPTOR_NUM		(17)				/*!< The maximum supported audio descriptor number					*/
#define DRV_HDMI_MAX_VSDB_PAYLOAD_NUM			(9)					/*!< The maximum supported VSDB payload byte number					*/

#define DRV_HDMI_AVI_INFOFRAME_LENGTH			(13)				/*!< The AVI infoframe length				*/
#define DRV_HDMI_SPD_INFOFRAME_LENGTH			(25)				/*!< The SPD infoframe length				*/
#define DRV_HDMI_AUDIO_INFOFRAME_LENGTH			(10)				/*!< The Audio infoframe length				*/
#define DRV_HDMI_MS_INFOFRAME_LENGTH			(10)				/*!< The MPEG Source infoframe length		*/

#define DRV_HDMI_AUDIO_INFOFRAME_REFER_TO_STREAM_HEADER	(0xff)		/*!< This is for CT, SF, SS in Audio InfoFrame setting to "Refer to Stream Header"	*/

/**
 * \brief
 * HDMI Error code definition.
 */
enum
{
	ERROR_HDMI_DEV_NAME     = ERROR_BASE_DRV_HDMI,		            /*!< Device Name Error  													*/
	ERROR_HDMI_DEV_RESOURCE,		                                /*!< HDMI don't have device resource										*/
	ERROR_HDMI_CLOSED_HANDLE,										/*!< Input handle is closed													*/
	ERROR_HDMI_PLUG_OUT,											/*!< The HDMI cable is plugged out											*/
	ERROR_HDMI_HPD,													/*!< HPD Signal											*/
	ERROR_HDMI_GET_SINK_EDID_FAIL,									/*!< Fail to get the Sink EDID												*/
	ERROR_HDMI_SINK_DVI,											/*!< DVI device found via the Sink EDID										*/
	ERROR_HDMI_SINK_EDID_RAW_DATA_WRONG,							/*!< Error found in the Sink EDID raw data									*/
	ERROR_HDMI_SINK_EDID_NOT_PARSED_OK,								/*!< The Sink EDID has not wholly been parsed OK							*/
	ERROR_HDMI_HDCP_PARAM_SET,										/*!< Fail to set HDCP parameter								*/
	ERROR_HDMI_HDCP_BKSV_FORMAT,									/*!< Error found in the BKSV format by the IP								*/
	ERROR_HDMI_HDCP_R0_DIFFERENT,									/*!< "R0 = R0'" checked fail												*/
	ERROR_HDMI_HDCP_READY_TIMEOUT,									/*!< Wait READY > 5 second												*/
	ERROR_HDMI_HDCP_MAX_DEVS_EXCEEDED,								/*!< BStatus MAX_DEVS_EXCEEDED												*/
	ERROR_HDMI_HDCP_MAX_CASCADE_EXCEEDED,							/*!< BStatus MAX_CASCADE_EXCEEDED												*/
	ERROR_HDMI_HDCP_V_DIFFERENT,									/*!< "V = V'" checked fail												*/
	ERROR_HDMI_DDC_BUS_LOW,											/*!< The DDC bus is pulled low by an external device						*/
	ERROR_HDMI_DDC_SLAVE_NO_ACK,									/*!< An ACK is not received from slave device during address or data write	*/
	ERROR_HDMI_DDC_CMD_NOT_COMPLETE,								/*!< DDC operation in progress												*/
	ERROR_HDMI_DDC_FIFO_NUMBER,										/*!< DDC FIFO number not as expected														*/
	ERROR_HDMI_DDC_FIFO_HALF,										/*!< DDC FIFO half full														*/
	ERROR_HDMI_DDC_FIFO_FULL,										/*!< DDC FIFO full															*/
	ERROR_HDMI_DDC_FIFO_EMPTY,										/*!< DDC FIFO empty															*/
	ERROR_HDMI_DDC_FIFO_READ_IN_USE,								/*!< DDC FIFO Read In Use													*/
	ERROR_HDMI_DDC_FIFO_WRITE_IN_USE,								/*!< DDC FIFO Write In Use													*/
	ERROR_HDMI_DDC_FIFO_NOT_EMPTY,									/*!< DDC FIFO not empty														*/
	ERROR_HDMI_DDC_TIMEOUT,											/*!< Get DDC data timeout														*/
	ERROR_HDMI_VIDEO_FORMAT_NOT_SUPPORTED,							/*!< The video format is not supported										*/
	ERROR_HDMI_OUTPUT_COLOR_MODE_NOT_SUPPORTED,						/*!< The output color mode is not supported									*/
	ERROR_HDMI_CHANNEL_COUNT_NOT_SUPPORTED,							/*!< The channel count is not supported										*/
	ERROR_HDMI_SAMPLE_SIZE_NOT_SUPPORTED,							/*!< The sample size is not supported										*/
	ERROR_HDMI_MAX_SAMPLE_SIZE_NOT_SUPPORTED,						/*!< The maximum sample size is not supported								*/
	ERROR_HDMI_SAMPLE_FREQUENCY_NOT_SUPPORTED,						/*!< The sample frequency is not supported									*/
	ERROR_HDMI_AUDIO_MCLK_NOT_SUPPORTED,							/*!< The audio MCLK is not supported										*/
	ERROR_HDMI_INFOFRAME_VERSION_NOT_SUPPORTED,						/*!< The infoframe version is not supported									*/
	ERROR_HDMI_IDCK_UNSTABLE,						                /*!< IDCK to TMDS unstable				          							*/
};

/**
 * \brief
 * HDMI EventID definition.
 */
enum
{
	EN_DRV_HDMI_EVENT_STATE_CHANGED,								/*!< The event to indicate the HDMI state	*/
};

/**
 * \brief
 * enumurate to indicate the hdmi color mode
 */
typedef enum
{
    EN_DRV_HDMI_COLOR_MODE_RGB444 = 1,				/*!< Color mode RGB444		*/
    EN_DRV_HDMI_COLOR_MODE_YCBCR422 = 2,			/*!< Color mode YCbCr422	*/
    EN_DRV_HDMI_COLOR_MODE_YCBCR444 = 4,			/*!< Color mode YCbCr444	*/
    EN_DRV_HDMI_COLOR_MODE_FUTURE = 8,				/*!< Color mode future		*/
    EN_DRV_HDMI_COLOR_MODE_NUM = 4					/*!< Color mode number		*/
}EN_DRV_HDMI_COLOR_MODE;

/**
 * \brief
 * enumurate to indicate the hdmi I2S maximum audio sample word length
 */
typedef enum
{
	EN_DRV_HDMI_I2S_MAXLEN_20BITS,					/*!< Maximum 20bits, sample size 16, 17, 18, 19, 20		*/
	EN_DRV_HDMI_I2S_MAXLEN_24BITS					/*!< Maximum 24bits, sample size 20, 21, 22, 23, 24		*/
}EN_DRV_HDMI_I2S_MAXLEN;

/**
 * \brief
 * enumurate to indicate the AVI Infoframe format
 */
typedef enum
{
   EN_DRV_HDMI_AVI_INFOFRAME_FORMAT_NONE,			/*!< AVI Infoframe format none	*/
   EN_DRV_HDMI_AVI_INFOFRAME_FORMAT_VER_ONE,		/*!< AVI Infoframe version 1	*/
   EN_DRV_HDMI_AVI_INFOFRAME_FORMAT_VER_TWO			/*!< AVI Infoframe version 2	*/
}EN_DRV_HDMI_AVI_INFOFRAME_FORMAT;

/**
 * \brief
 * enumurate to indicate the SPD Infoframe format
 */
typedef enum
{
   EN_DRV_HDMI_SPD_INFOFRAME_FORMAT_NONE,			/*!< SPD Infoframe format none	*/
   EN_DRV_HDMI_SPD_INFOFRAME_FORMAT_VER_ONE,		/*!< SPD Infoframe version 1	*/
}EN_DRV_HDMI_SPD_INFOFRAME_FORMAT;

/**
 * \brief
 * enumurate to indicate the Audio Infoframe format
 */
typedef enum
{
   EN_DRV_HDMI_AUDIO_INFOFRAME_FORMAT_NONE,			/*!< Audio Infoframe format none	*/
   EN_DRV_HDMI_AUDIO_INFOFRAME_FORMAT_VER_ONE,		/*!< Audio Infoframe version 1		*/
}EN_DRV_HDMI_AUDIO_INFOFRAME_FORMAT;

/**
 * \brief
 * enumurate to indicate the MPEG Source Infoframe format
 */
typedef enum
{
   EN_DRV_HDMI_MS_INFOFRAME_FORMAT_NONE,			/*!< MS Infoframe format none	*/
   EN_DRV_HDMI_MS_INFOFRAME_FORMAT_VER_ONE,			/*!< MS Infoframe version 1		*/
}EN_DRV_HDMI_MS_INFOFRAME_FORMAT;

/**
 * \brief
 * enumurate to indicate the Info frame type
 */
typedef enum
{
    EN_DRV_HDMI_INFOFRAME_TYPE_AVI = 0x82,			/*!< Infoframe type AVI			*/
    EN_DRV_HDMI_INFOFRAME_TYPE_SPD,					/*!< Infoframe type SPD			*/
    EN_DRV_HDMI_INFOFRAME_TYPE_AUDIO,				/*!< Infoframe type Audio		*/
    EN_DRV_HDMI_INFOFRAME_TYPE_MPEG_SOURCE,			/*!< Infoframe type MS			*/
    EN_DRV_HDMI_INFOFRAME_TYPE_NUM = 4				/*!< Infoframe type number		*/
}EN_DRV_HDMI_INFOFRAME_TYPE;

/**
 * \brief
 * enumurate to indicate the AVI bar info
 */
typedef enum
{
   EN_DRV_HDMI_BAR_INFO_NOT_VALID,      /*!< Bar Data not valid 					*/
   EN_DRV_HDMI_BAR_INFO_V,              /*!< Vertical bar data valid 				*/
   EN_DRV_HDMI_BAR_INFO_H,              /*!< Horizental bar data valid 				*/
   EN_DRV_HDMI_BAR_INFO_VH,             /*!< Horizental and Vertical bar data valid */
   EN_DRV_HDMI_BAR_INFO_NUM				/*!< Bar INFO number	 					*/
}EN_DRV_HDMI_BAR_INFO;

/**
 * \brief
 * enumurate to indicate the AVI scan info
 */
typedef enum
{
    EN_DRV_HDMI_SCAN_INFO_NO_DATA,       	/*!< No Scan information								*/
    EN_DRV_HDMI_SCAN_INFO_OVERSCANNED,   	/*!< Scan information, Overscanned (for television) 	*/
    EN_DRV_HDMI_SCAN_INFO_UNDERSCANNED,   	/*!< Scan information, Underscanned (for computer) 		*/
    EN_DRV_HDMI_SCAN_INFO_FUTURE,			/*!< Scan information future						 	*/
    EN_DRV_HDMI_SCAN_INFO_NUM				/*!< Scan information number						 	*/
}EN_DRV_HDMI_SCAN_INFO;

/**
 * \brief
 * enumurate to indicate the colorimetry
 */
typedef enum
{
    EN_DRV_HDMI_COLORIMETRY_RGB_DEFAULT,					/*!< Colorimetry RGB 					*/
    EN_DRV_HDMI_COLORIMETRY_RGB_ADOBE,						/*!< Colorimetry Adobe RGB				*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR422_DEFAULT,				/*!< Colorimetry YCbCr422 default		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR422_SMPTE170M,				/*!< Colorimetry YCbCr422 SMPTE170M		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR422_ITUR709,				/*!< Colorimetry YCbCr422 ITUR709		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR422_ITUR601_XVYCC,			/*!< Colorimetry YCbCr422 XVYCC601		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR422_ITUR709_XVYCC,			/*!< Colorimetry YCbCr422 XVYCC709		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR422_ITUR601_SYCC,			/*!< Colorimetry YCbCr422 SYCC601		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR422_ITUR601_YCC_ADOBE,		/*!< Colorimetry YCbCr422 Adobe YCC601	*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR444_DEFAULT,				/*!< Colorimetry YCbCr444 default		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR444_SMPTE170M,				/*!< Colorimetry YCbCr444 SMPTE170M		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR444_ITUR709,				/*!< Colorimetry YCbCr444 ITUR709		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR444_ITUR601_XVYCC,			/*!< Colorimetry YCbCr444 XVYCC601		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR444_ITUR709_XVYCC,			/*!< Colorimetry YCbCr444 XVYCC709		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR444_ITUR601_SYCC,			/*!< Colorimetry YCbCr444 SYCC601		*/
    EN_DRV_HDMI_COLORIMETRY_YCBCR444_ITUR601_YCC_ADOBE,		/*!< Colorimetry YCbCr444 Adobe YCC601	*/
    EN_DRV_HDMI_COLORIMETRY_NUM								/*!< Colorimetry number					*/
}EN_DRV_HDMI_COLORIMETRY;

/**
 * \brief
 * enumurate to indicate the picture aspect ratio
 */
typedef enum
{
    EN_DRV_HDMI_PICTURE_ASPECT_RATIO_NO_DATA,		/*!< Picture Aspect Ratio no data	*/
    EN_DRV_HDMI_PICTURE_ASPECT_RATIO_4TO3,			/*!< Picture Aspect Ratio 4:3		*/
    EN_DRV_HDMI_PICTURE_ASPECT_RATIO_16TO9,			/*!< Picture Aspect Ratio 16:9		*/
    EN_DRV_HDMI_PICTURE_ASPECT_RATIO_FUTURE,		/*!< Picture Aspect Ratio future	*/
    EN_DRV_HDMI_PICTURE_ASPECT_RATIO_NUM			/*!< Picture Aspect Ratio number	*/
}EN_DRV_HDMI_PICTURE_ASPECT_RATIO;

/**
 * \brief
 * enumurate to indicate the active format aspect ratio
 */
typedef enum
{
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_AS_PICTURE = 0x08,								/*!< Active Format Aspect Ratio as Picture Aspect Ratio				*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_4TO3_CENTER,										/*!< Active Format Aspect Ratio 4:3 Center							*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_16TO9_CENTER,									/*!< Active Format Aspect Ratio 16:9 Center							*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_14TO9_CENTER,									/*!< Active Format Aspect Ratio 14:9 Center							*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_BOX_16TO9_TOP = 0x02,							/*!< Active Format Aspect Ratio box 16:9 top						*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_BOX_14TO9_TOP,									/*!< Active Format Aspect Ratio box 14:9 top						*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_BOX_16TO9_CENTER,								/*!< Active Format Aspect Ratio box 16:9 center						*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_4TO3_WITH_SHOOT_PROTECT_14TO9_CENTER = 0x0d,		/*!< Active Format Aspect Ratio 4:3 with shoot protect 14:9 Center	*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_16TO9_WITH_SHOOT_PROTECT_14TO9_CENTER,			/*!< Active Format Aspect Ratio 16:9 with shoot protect 14:9 Center	*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_16TO9_WITH_SHOOT_PROTECT_4TO3_CENTER,			/*!< Active Format Aspect Ratio 16:9 with shoot protect 4:3 Center	*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO_NUM = 10											/*!< Active Format Aspect Ratio number								*/
}EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO;

/**
 * \brief
 * enumurate to indicate the IT content
 */
typedef enum
{
    EN_DRV_HDMI_IT_NON,			/*!< IT no data			*/
    EN_DRV_HDMI_IT_CONTENT,		/*!< IT content valid	*/
    EN_DRV_HDMI_IT_NUM			/*!< IT number			*/
}EN_DRV_HDMI_IT;

/**
 * \brief
 * enumurate to indicate the RGB quantization range
 */
typedef enum
{
    EN_DRV_HDMI_RGB_QUANTIZATION_RANGE_DEFAULT,		/*!< Quantization Range default		*/
    EN_DRV_HDMI_RGB_QUANTIZATION_RANGE_LIMITED,		/*!< Quantization Range limited		*/
    EN_DRV_HDMI_RGB_QUANTIZATION_RANGE_FULL,		/*!< Quantization Range full		*/
    EN_DRV_HDMI_RGB_QUANTIZATION_RANGE_RESERVED,	/*!< Quantization Range reserved	*/
    EN_DRV_HDMI_RGB_QUANTIZATION_RANGE_NUM			/*!< Quantization Range number		*/
}EN_DRV_HDMI_RGB_QUANTIZATION_RANGE;

/**
 * \brief
 * enumurate to indicate the non-uniform picture scaling
 */
typedef enum
{
    EN_DRV_HDMI_PICTURE_SCALING_NON,      		 	/*!< No Known, non-uniform picture scaling		  			*/
    EN_DRV_HDMI_PICTURE_SCALING_H,                	/*!< Picture has been scaled horizentally 					*/
    EN_DRV_HDMI_PICTURE_SCALING_V,                	/*!< Picture has been scaled Vertically 					*/
    EN_DRV_HDMI_PICTURE_SCALING_HV,                	/*!< Picture has been scaled Horizentally and Vertically   	*/
    EN_DRV_HDMI_PICTURE_SCALING_NUM					/*!< Picture scaling number				 					*/
}EN_DRV_HDMI_PICTURE_SCALING;

/**
 * \brief
 * enumurate to indicate the IT content type
 */
typedef enum
{
    EN_DRV_HDMI_ITC_TYPE_GRAPHICS,		/*!< IT content type graphics	*/
    EN_DRV_HDMI_ITC_TYPE_PHOTO,			/*!< IT content type Photo		*/
    EN_DRV_HDMI_ITC_TYPE_CINEMA,		/*!< IT content type cinema		*/
    EN_DRV_HDMI_ITC_TYPE_GAME,			/*!< IT content type game		*/
    EN_DRV_HDMI_ITC_TYPE_NUM			/*!< IT content type number		*/
}EN_DRV_HDMI_ITC_TYPE;

/**
 * \brief
 * enumurate to indicate the YCC quantization range
 */
typedef enum
{
    EN_DRV_HDMI_YCC_QUANTIZATION_RANGE_LIMITED,		/*!< YCC Quantization Range limited		*/
    EN_DRV_HDMI_YCC_QUANTIZATION_RANGE_FULL,		/*!< YCC Quantization Range full		*/
    EN_DRV_HDMI_YCC_QUANTIZATION_RANGE_RESERVED0,	/*!< YCC Quantization Range reserved 0	*/
    EN_DRV_HDMI_YCC_QUANTIZATION_RANGE_RESERVED1,	/*!< YCC Quantization Range reserved 1	*/
    EN_DRV_HDMI_YCC_QUANTIZATION_RANGE_NUM			/*!< YCC Quantization Range number		*/
}EN_DRV_HDMI_YCC_QUANTIZATION_RANGE;

/**
 * \brief
 * enumurate to indicate the LFE Playback Level Information
 */
typedef enum
{
    EN_DRV_HDMI_LFE_PLAYBACK_LEVEL_UNKNOWN_OR_REFER_TO_OTHER_INFORMATION,	/*!< LFE playback level unknown or refer to other information	*/
    EN_DRV_HDMI_LFE_PLAYBACK_LEVEL_0DB,										/*!< LFE playback level 0DB										*/
    EN_DRV_HDMI_LFE_PLAYBACK_LEVEL_PLUS10DB,								/*!< LFE playback level +10DB									*/
    EN_DRV_HDMI_LFE_PLAYBACK_LEVEL_RESERVED,								/*!< LFE playback level reserved								*/
    EN_DRV_HDMI_LFE_PLAYBACK_LEVEL_NUM										/*!< LFE playback level number									*/
}EN_DRV_HDMI_LFE_PLAYBACK_LEVEL;

/**
 * \brief
 * enumurate to indicate the EDID timing descriptor stereo type
 */
typedef enum
{
    EN_DRV_HDMI_EDID_STEREO_NORMAL_NO =1,				/*!< Normal display, no stereo									*/
    EN_DRV_HDMI_EDID_STEREO_RIGHT_IMAGE,           		/*!< Field Sequentiel stereo, right image when stereo sync=1 	*/
    EN_DRV_HDMI_EDID_STEREO_2WAY_INTERLEAVED_RIGHT,   	/*!< 2-way interleaved stereo, right image on even lines 		*/
    EN_DRV_HDMI_EDID_STEREO_LEFT_IMAGE,            		/*!< Field Sequentiel stereo, left image when stereo sync =1 	*/
    EN_DRV_HDMI_EDID_STEREO_2WAY_INTERLEAVED_LEFT,   	/*!< 2-way interleaved stereo, left image on even lines  		*/
    EN_DRV_HDMI_EDID_STEREO_4WAY_INTERLEAVED,      		/*!< 4-way interleaved stereo 									*/
    EN_DRV_HDMI_EDID_STEREO_SBS_INTERLEAVED        		/*!< Side-by-side interleaved stereo 							*/
}EN_DRV_HDMI_EDID_STEREO;

/**
 * \brief
 * enumurate to indicate the EDID timing descriptor H/V sync type
 */
typedef enum
{
    EN_DRV_HDMI_EDID_SYNC_ANALOG_COMPOSITE,       							/*!< Analog composite 						*/
    EN_DRV_HDMI_EDID_SYNC_ANALOG_COMPOSITE_RGB,								/*!< Analog composite RGB 					*/
    EN_DRV_HDMI_EDID_SYNC_ANALOG_COMPOSITE_SERRATE,							/*!< Analog composite Serrate				*/
    EN_DRV_HDMI_EDID_SYNC_ANALOG_COMPOSITE_SERRATE_RGB,						/*!< Analog composite Serrate RGB			*/
    EN_DRV_HDMI_EDID_SYNC_BIP_ANALOG_COMPOSITE,   							/*!< Bipolar Analog Composite 				*/
    EN_DRV_HDMI_EDID_SYNC_BIP_ANALOG_COMPOSITE_RGB,							/*!< Bipolar Analog Composite RGB			*/
    EN_DRV_HDMI_EDID_SYNC_BIP_ANALOG_COMPOSITE_SERRATE,						/*!< Bipolar Analog Composite Serrate		*/
    EN_DRV_HDMI_EDID_SYNC_BIP_ANALOG_COMPOSITE_SERRATE_RGB,					/*!< Bipolar Analog Composite Serrate RGB	*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_COMPOSITE,      							/*!< Digital Composite 						*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_COMPOSITE_POSITIVE,						/*!< Digital Composite Positive				*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_COMPOSITE_SERRATE,						/*!< Digital Composite Serrate				*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_COMPOSITE_SERRATE_POSITIVE,				/*!< Digital Composite Serrate Positive		*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_SEPARATE,       							/*!< Digital Separate 						*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_SEPARATE_HSYNC_POSITIVE,					/*!< Digital Separate HSync Positive		*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_SEPARATE_VSYNC_POSITIVE,					/*!< Digital Separate VSync Positive		*/
    EN_DRV_HDMI_EDID_SYNC_DIGITAL_SEPARATE_HSYNC_POSITIVE_VSYNC_POSITIVE	/*!< Digital Separate HSync VSync Positive	*/
}EN_DRV_HDMI_EDID_SYNC;

/**
 * \brief
 * enumurate to indicate the EDID feature supported display type
 */
typedef enum
{
    EN_DRV_HDMI_EDID_DISPLAY_TYPE_MONOCHROME,		/*!< Display type monochrome	*/
    EN_DRV_HDMI_EDID_DISPLAY_TYPE_RGB,				/*!< Display type RGB			*/
    EN_DRV_HDMI_EDID_DISPLAY_TYPE_NON_RGB,			/*!< Display type non RGB		*/
    EN_DRV_HDMI_EDID_DISPLAY_TYPE_UNDEFINED			/*!< Display type undefined		*/
}EN_DRV_HDMI_EDID_DISPLAY_TYPE;

/**
 * \brief
 * enumurate to indicate the EDID established timing
 */
typedef enum
{
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_720_400_70 =1,         /*!< 720*400 70Hz, IBM VGA 		*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_720_400_88 =2,         /*!< 720*400 88Hz, IBM XGA2 		*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_640_480_60 =4,         /*!< 640*480 60Hz, IBM VGA 		*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_640_480_67 =8,         /*!< 640*480 67Hz, Apple, MacII 	*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_640_480_72 =16,        /*!< 640*480 72Hz, VESA 			*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_640_480_75 =32,        /*!< 640*480 75Hz, VESA 			*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_800_600_56 =64,        /*!< 800*600 56Hz, VESA 			*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_800_600_60 =128,       /*!< 800*600 60Hz, VESA 			*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_800_600_72 =256,       /*!< 800*600 72Hz, VESA 			*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_800_600_75 =512,       /*!< 800*600 75Hz, VESA 			*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_832_624_75 =1024,      /*!< 832*624 75Hz, Apple, MacII 	*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_1024_768_87 =2048,     /*!< 1024*768 87Hz, Apple, MacII */
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_1024_768_60 =4096,     /*!< 1024*768 60Hz, VESA 		*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_1024_768_70 =8192,     /*!< 1024*768 70Hz, VESA 		*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_1024_768_75 =16384,    /*!< 1024*768 75Hz, VESA 		*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_1280_1024_75 =32768,   /*!< 1280*1024 75Hz, VESA 		*/
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING_1152_870_75 =65535     /*!< 1152*870 75Hz, Apple, MacII */
}EN_DRV_HDMI_EDID_ESTABLISHED_TIMING;

/**
 * \brief
 * enumurate to indicate the HDMI task state
 */
typedef enum
{
    EN_DRV_HDMI_STATE_NO_RECEIVER,					/*!< The receiver is not plugged in							*/
    EN_DRV_HDMI_STATE_RECEIVER_CONNECTED,			/*!< The receiver is connected								*/
    EN_DRV_HDMI_STATE_NO_HDCP_RECEIVER,				/*!< The receiver is not capable of HDCP encryped			*/
    EN_DRV_HDMI_STATE_AUTHENTICATION_IN_PROGRESS,	/*!< The receiver is running HDCP authentication process	*/
    EN_DRV_HDMI_STATE_AUTHENTICATION_FAILED,		/*!< The receiver is HDCP authentication failed				*/
    EN_DRV_HDMI_STATE_AUTHENTICATION_SUCCEEDED,		/*!< The receiver is HDCP authentication succeeded				*/
}EN_DRV_HDMI_STATE;

/**
 * \brief
 * enumurate to indicate the register name of sink's HDCP port
 */
typedef enum
{
	EN_DRV_HDMI_HDCP_PORT_BKSV,					    /*!< Sink HDCP port register Bksv*/
	EN_DRV_HDMI_HDCP_PORT_RI,					    /*!< Sink HDCP port register Ri'*/
	EN_DRV_HDMI_HDCP_PORT_PJ,					    /*!< Sink HDCP port register Pj'*/
	EN_DRV_HDMI_HDCP_PORT_AKSV,					    /*!< Sink HDCP port register Aksv*/
	EN_DRV_HDMI_HDCP_PORT_AINFO,				    /*!< Sink HDCP port register Ainfo*/
	EN_DRV_HDMI_HDCP_PORT_AN,					    /*!< Sink HDCP port register An*/
	EN_DRV_HDMI_HDCP_PORT_VH0,					    /*!< Sink HDCP port register V'.H0*/
	EN_DRV_HDMI_HDCP_PORT_VH1,					    /*!< Sink HDCP port register V'.H1*/
	EN_DRV_HDMI_HDCP_PORT_VH2,					    /*!< Sink HDCP port register V'.H2*/
	EN_DRV_HDMI_HDCP_PORT_VH3,					    /*!< Sink HDCP port register V'.H3*/
	EN_DRV_HDMI_HDCP_PORT_BCAPS,					/*!< Sink HDCP port register Bcaps*/
	EN_DRV_HDMI_HDCP_PORT_BSTATUS,					/*!< Sink HDCP port register Bstatus*/
	EN_DRV_HDMI_HDCP_PORT_KSVFIFO,					/*!< Sink HDCP port register KSV FIFO*/
	EN_DRV_HDMI_HDCP_PORT_DBG,					    /*!< Sink HDCP port register dbg*/
}EN_DRV_HDMI_HDCP_PORT_REG_NAME;

// 20120813
/**
 * \brief
 *  enumurate to indicate the HDMI swing level
 */
typedef enum
{
    EN_DRV_HDMI_SWING_LEVEL0,
    EN_DRV_HDMI_SWING_LEVEL1,
    EN_DRV_HDMI_SWING_LEVEL2,
    EN_DRV_HDMI_SWING_LEVEL3
}EN_DRV_HDMI_SWING_CTRL_LEVEL;

/**
 * \brief
 *  enumurate to indicate the HDMI pixel frequency
 */
typedef enum
{
    EN_DRV_HDMI_PIXEL_FREQ_27M,
    EN_DRV_HDMI_PIXEL_FREQ_74M,
    EN_DRV_HDMI_PIXEL_FREQ_148M,
    EN_DRV_HDMI_PIXEL_FREQ_NUM = 3
}EN_DRV_HDMI_PIXEL_FREQ;

/**
 * \brief
 *  the HDMI swing ctrl parameter
 */
typedef struct
{
    EN_DRV_HDMI_SWING_CTRL_LEVEL            enSWCtrlTC8;            /*!< */
    EN_DRV_HDMI_SWING_CTRL_LEVEL            enSWCtrlDC10;          	/*!< */
    EN_DRV_HDMI_SWING_CTRL_LEVEL            enSWCtrlDC12;          	/*!< */
} ST_DRV_HDMI_SWING_CTRL, *PST_DRV_HDMI_SWING_CTRL;

/**
 * \brief
 *  the HDMI initial structure
 */
typedef struct
{
    PST_DRV_HDMI_SWING_CTRL         pstSwConfig;                    /*!< Pointer to Swing config table        */
}ST_DRV_HDMI_INIT_PARAMS, *PST_DRV_HDMI_INIT_PARAMS;

/**
 * \brief
 *  the HDMI terminate structure
 */
typedef struct
{
    bool                       b8ForceTerminate;					/*!< Force terminate HDMI	                */
}ST_DRV_HDMI_TERM_PARAMS, *PST_DRV_HDMI_TERM_PARAMS;

/**
 * \brief
 *  the HDMI output parameters structure
 */
typedef struct
{
    EN_DRV_VTG_TIMING                   	enVTGTiming;				/*!< VTG timing item										*/
    EN_DRV_HDMI_COLOR_MODE 					enOutputColorMode;			/*!< Output color mode										*/
    bool									b8EnableAudio;				/*!< Enable audio											*/
    bool									b8AudioFormatRaw;			/*!< RAW or LPCM											*/
    u32                          			u32ChannelCount;			/*!< Channel count											*/
    EN_DRV_ADEC_DACDataPrecision     		enAudioSampleSize;			/*!< Audio sample size										*/
    EN_DRV_HDMI_I2S_MAXLEN     				enAudioMaxSampleSize;		/*!< Maximum audio sample size								*/
    EN_DRV_ADEC_SampleFrequency         	enAudioSamplingFrequency;	/*!< Audio sample frequency									*/
    EN_DRV_ADEC_PlayerFrequencyMultiplier	enAudioMCLK;				/*!< Audio MCLK												*/
    EN_DRV_ADEC_StreamContent				enAudioEncodeType;			/*!< Audio encode Type										*/
    bool 									b8EnableSPDIF;				/*!< SPDIF or I2S											*/
    bool                					b8ForceDVI;					/*!< Force to DVI mode										*/
    bool                					b8IsHDCPEnable;				/*!< HDCP function enable or disable						*/
    bool									b8MuteNoHDCPSink;			/*!< Mute Non-HDCP Sink									*/
}ST_DRV_HDMI_OUTPUT_PARAMS, *PST_DRV_HDMI_OUTPUT_PARAMS;

/**
 * \brief
 *  the HDMI open structure
 */
typedef struct
{
	u32 u32EvtHandle;											/*!< HDMI Event handle		*/
	ST_DRV_HDMI_OUTPUT_PARAMS			stOutputParams;			/*!< Output parameters		*/
    EN_DRV_HDMI_AVI_INFOFRAME_FORMAT    enAVIType;				/*!< AVI infoframe type		*/
    EN_DRV_HDMI_SPD_INFOFRAME_FORMAT    enSPDType;				/*!< SPD infoframe type		*/
    EN_DRV_HDMI_AUDIO_INFOFRAME_FORMAT  enAUDIOType;			/*!< Audio infoframe type	*/
    EN_DRV_HDMI_MS_INFOFRAME_FORMAT     enMSType;				/*!< MS infoframe type		*/
}ST_DRV_HDMI_OPEN_PARAMS, *PST_DRV_HDMI_OPEN_PARAMS;

/**
 * \brief
 *  the HDMI capability structure
 */
typedef struct
{
    u32        u32SupportedOutputColorMode;		/*!< Collection from EN_DRV_HDMI_COLOR_MODE supported	*/
    bool      b8IsEDIDDataSupported;			/*!< The capability of supporting EDID data				*/
    bool      b8IsDataIslandSupported;			/*!< The capability of supporting data island			*/
    bool      b8IsVideoSupported;				/*!< The capability of supporting video					*/
    bool      b8IsAudioSupported;				/*!< The capability of supporting audio					*/
}ST_DRV_HDMI_CAPABILITY, *PST_DRV_HDMI_CAPABILITY;

/**
 * \brief
 *  the HDMI source capability structure
 */
typedef struct
{
   EN_DRV_HDMI_AVI_INFOFRAME_FORMAT    enAVIInfoFrameSupported;		/*!< AVI infoframes type supported		*/
   EN_DRV_HDMI_SPD_INFOFRAME_FORMAT    enSPDInfoFrameSupported;		/*!< SPD infoframes type supported		*/
   EN_DRV_HDMI_AUDIO_INFOFRAME_FORMAT  enAudioInfoFrameSupported;	/*!< Audio infoframes type supported	*/
   EN_DRV_HDMI_MS_INFOFRAME_FORMAT     enMSInfoFrameSupported;		/*!< MS infoframes type supported		*/
}ST_DRV_HDMI_SOURCE_CAPABILITY, *PST_DRV_HDMI_SOURCE_CAPABILITY;

/**
 * \brief
 *  the HDMI sink capability structure
 */
typedef struct
{
    u32                         u32EDIDBasicVersion;			/*!< EDID basic version supported							*/
    u32                         u32EDIDBasicRevision;			/*!< EDID basic revision supported							*/
    u32                         u32EDIDExtRevision;				/*!< EDID Extension revision supported						*/
    bool                       b8IsBasicEDIDSupported;			/*!< The capability of supporting basic EDID block			*/
    bool                       b8IsCEAExtensionSupported;		/*!< The capability of supporting EDID CEA Extension blocks	*/
    bool                       b8IsLCDTimingDataSupported;		/*!< The capability of supporting LCD timing data blocks	*/
    bool                       b8IsColorInfoSupported;			/*!< The capability of supporting Color Info blocks			*/
    bool                       b8IsDviDataSupported;			/*!< The capability of supporting DVI data blocks			*/
    bool                       b8IsTouchScreenDataSupported;	/*!< The capability of supporting Touch Screen data blocks	*/
    bool                       b8IsBlockMapSupported;			/*!< The capability of supporting Block Map blocks			*/
}ST_DRV_HDMI_SINK_CAPABILITY, *PST_DRV_HDMI_SINK_CAPABILITY;

/**
 * \brief
 *  the HDMI AVI Info frame ver2 structure
 */
typedef struct
{
    EN_DRV_HDMI_INFOFRAME_TYPE   		enInfoFrameType;					/*!< Infoframe type	code				*/
    u32                      	 		u32FrameVersion;					/*!< Infoframe version number			*/
    u32                      	 		u32FrameLength;						/*!< Length of AVI Infoframe			*/
    EN_DRV_HDMI_COLOR_MODE   	 		enOutputColorMode;					/*!< RGB or YCbCr						*/
    bool                    	 		b8HasActiveFormatInformation;		/*!< Active Format Information Present	*/
    EN_DRV_HDMI_BAR_INFO     	 		enBarInfo;							/*!< Bar Data Present					*/
    EN_DRV_HDMI_SCAN_INFO    	 		enScanInfo;							/*!< Scan Information					*/
    EN_DRV_HDMI_COLORIMETRY  	 		enColorimetry;						/*!< Colorimetry						*/
    EN_DRV_HDMI_PICTURE_ASPECT_RATIO 	enPictureAspectRatio;				/*!< Coded Frame Aspect Ratio			*/
    EN_DRV_HDMI_ACTIVE_FORMAT_ASPECT_RATIO 		enActiveFormatAspectRatio;	/*!< Active Portion Aspect Ratio		*/
    EN_DRV_HDMI_IT				 		enITContent;						/*!< IT Content							*/
    EN_DRV_HDMI_RGB_QUANTIZATION_RANGE	enRGBQuantizationRange;				/*!< RGB Quantization Range				*/
    EN_DRV_HDMI_PICTURE_SCALING  		enPictureScaling;					/*!< Non-Uniform Picture Scaling		*/
    EN_DRV_VTG_TIMING                   enVTGTiming;						/*!< VTG Timing							*/
    EN_DRV_HDMI_YCC_QUANTIZATION_RANGE	enYCCQuantizationRange;				/*!< YCC Quantization Range				*/
    EN_DRV_HDMI_ITC_TYPE				enITCType;							/*!< IT Content Type					*/
    u32                      	 		u32PixelRepetition;					/*!< Pixel Repetition Factor			*/
    u32                      	 		u32LineNEndofTop;					/*!< Line Number of End of Top Bar		*/
    u32                      	 		u32LineNStartofBot;					/*!< Line Number of Start of Bottom Bar	*/
    u32                      	 		u32PixelNEndofLeft;					/*!< Pixel Number of End of Left Bar	*/
    u32                      	 		u32PixelNStartofRight;				/*!< Pixel Number of Start of Right Bar	*/
}ST_DRV_HDMI_AVI_INFOFRAME, *PST_DRV_HDMI_AVI_INFOFRAME;

/**
 * \brief
 *  the HDMI SPD Info frame structure
 */
typedef struct
{
    EN_DRV_HDMI_INFOFRAME_TYPE   		enInfoFrameType;				/*!< Infoframe type	code				*/
    u32                      	 		u32FrameVersion ;               /*!< Infoframe version number			*/
    u32                      	 		u32FrameLength;                 /*!< Length of SPD Infoframe			*/
    u8                     				au8VendorName[8];				/*!< Vendor Name Character				*/
    u8                     				au8ProductDescription[16];		/*!< Product Description Character		*/
    u8									u8SourceInformation;			/*!< Source Information					*/
}ST_DRV_HDMI_SPD_INFOFRAME, *PST_DRV_HDMI_SPD_INFOFRAME;

/**
 * \brief
 *  the HDMI AUDIO Info frame structure
 */
typedef struct
{
    EN_DRV_HDMI_INFOFRAME_TYPE   		enInfoFrameType;			/*!< Infoframe type	code				*/
    u32                      	 		u32FrameVersion ;           /*!< Infoframe version number			*/
    u32                      	 		u32FrameLength;             /*!< Length of Audio Infoframe			*/
    u32                          		u32ChannelCount;			/*!< Audio Channel Count				*/
    EN_DRV_ADEC_StreamContent        	enCodingType;				/*!< Audio Coding Type					*/
    EN_DRV_ADEC_DACDataPrecision     	enSampleSize;				/*!< Audio Sample Size					*/
    EN_DRV_ADEC_SampleFrequency         enSamplingFrequency;		/*!< Audio Sampling Frequency			*/
    u32                          		u32ChannelAlloc;			/*!< Audio Channel Allocation			*/
    EN_DRV_HDMI_LFE_PLAYBACK_LEVEL		enLFEPlaybackLevel;			/*!< Audio LFE Playback Level			*/
    u32                          		u32LevelShift;				/*!< Audio Level Shift					*/
    bool                         		b8DownmixInhibit;			/*!< Audio Downmix Inhibit				*/
}ST_DRV_HDMI_AUDIO_INFOFRAME, *PST_DRV_HDMI_AUDIO_INFOFRAME;

/**
 * \brief
 *  the HDMI MS Info frame structure
 */
typedef struct
{
    EN_DRV_HDMI_INFOFRAME_TYPE   		enInfoFrameType;			/*!< Infoframe type	code				*/
    u32                      	 		u32FrameVersion ;           /*!< Infoframe version number			*/
    u32                      	 		u32FrameLength;             /*!< Length of MS Infoframe				*/
    u32                      			u32MPEGBitRate;				/*!< MPEG bit rate, in Hz				*/
    bool                     			b8IsFieldRepeated;			/*!< Field Repeated						*/
    EN_DRV_VDEC_FrameType        		enMepgFrameType;			/*!< Mepg Frame Type					*/
}ST_DRV_HDMI_MS_INFOFRAME, *PST_DRV_HDMI_MS_INFOFRAME;

/**
 * \brief
 *  the HDMI EDID short video descriptor structure
 */
typedef struct //_ST_DRV_HDMI_SHORT_VIDEO_DESCRIPTOR
{
    bool  				b8IsNative;			/*!< Native				*/
    EN_DRV_VTG_TIMING	enVTGTiming;		/*!< VTG timing item	*/
}ST_DRV_HDMI_SHORT_VIDEO_DESCRIPTOR, *PST_DRV_HDMI_SHORT_VIDEO_DESCRIPTOR;

/**
 * \brief
 *  the HDMI EDID video data block structure
 */
typedef struct
{
    u8   								u8TagCode;												/*!< Tag Code						*/
    u8   								u8VideoLength;											/*!< Length of data block payload	*/
    u32									u32VideoDescriptorNum;									/*!< Video descriptor number		*/
    ST_DRV_HDMI_SHORT_VIDEO_DESCRIPTOR  astVideoDescriptor[DRV_HDMI_MAX_VIDEO_DESCRIPTOR_NUM];	/*!< Video descriptor				*/
}ST_DRV_HDMI_VIDEO_DATA_BLOCK, *PST_DRV_HDMI_VIDEO_DATA_BLOCK;

/**
 * \brief
 *  the HDMI EDID short audio descriptor structure
 */
typedef struct //_ST_DRV_HDMI_SHORT_AUDIO_DESCRIPTOR
{
    EN_DRV_ADEC_StreamContent   enAudioFormatCode;							/*!< Audio Format Code					*/
    u32                      	u32NumofAudioChannels;						/*!< Number of Audio Channels			*/
    EN_DRV_ADEC_SampleFrequency enSamplingFrequency;						/*!< Sampling Frequency					*/
    union
    {
    	EN_DRV_ADEC_DACDataPrecision	enSampleSize;						/*!< Sample Size						*/
    	u32								u32MaxBitRateDividedBy8kHz;			/*!< Maximum bit rate divided by 8 kHz	*/
    	u32								u32AudioFormatCodeDependentValue;	/*!< Audio Format Code dependent value	*/
    	u32								u32Profile;							/*!< Profile							*/
    	EN_DRV_ADEC_StreamContent   	enAudioFormatCodeExt;				/*!< Audio Format Code Extension		*/
    };
}ST_DRV_HDMI_SHORT_AUDIO_DESCRIPTOR, *PST_DRV_HDMI_SHORT_AUDIO_DESCRIPTOR;

/**
 * \brief
 *  the HDMI EDID audio data block structure
 */
typedef struct
{
    u8   								u8TagCode;												/*!< Tag Code						*/
    u8   								u8AudioLength;                                          /*!< Length of data block payload	*/
    u32									u32AudioDescriptorNum;                                  /*!< Audio descriptor number		*/
    ST_DRV_HDMI_SHORT_AUDIO_DESCRIPTOR  astAudioDescriptor[DRV_HDMI_MAX_AUDIO_DESCRIPTOR_NUM];  /*!< Audio descriptor				*/
}ST_DRV_HDMI_AUDIO_DATA_BLOCK, *PST_DRV_HDMI_AUDIO_DATA_BLOCK;

/**
 * \brief
 *  the HDMI EDID speaker allocation data block structure
 */
typedef struct
{
    u8   u8TagCode;			/*!< Tag Code						*/
    u8   u8SpeakerLength;   /*!< Length of data block payload	*/
    u8   au8SpeakerData[3];	/*!< Speaker Data					*/
}ST_DRV_HDMI_SPEAKER_ALLOCATION_DATA_BLOCK, *PST_DRV_HDMI_SPEAKER_ALLOCATION_DATA_BLOCK;

/**
 * \brief
 *  the HDMI EDID vender specific data block structure
 */
typedef struct
{
    u8  u8TagCode;												/*!< Tag Code						*/
    u8  u8VendorLength;                                         /*!< Length of data block payload	*/
    u8  au8RegistrationId[3];                    				/*!< Registration Id				*/
    u8  au8VendorDataPayload[DRV_HDMI_MAX_VSDB_PAYLOAD_NUM];	/*!< Vendor Data Payload			*/
}ST_DRV_HDMI_VSDB, *PST_DRV_HDMI_VSDB;

/**
 * \brief
 *  the HDMI colormetry data block structure
 */
typedef struct
{
    u8  u8TagCode;				/*!< Tag Code						*/
    u8  u8ColormetryLength;     /*!< Length of data block payload	*/
    u8  u8ExtTagCode;			/*!< Extended Tag Code				*/
    u8  u8ColormetryFlag;		/*!< Colormetry						*/
    u8  u8MetaData;				/*!< Meta Data						*/
}ST_DRV_HDMI_COLORMETRY_DATA_BLOCK, *PST_DRV_HDMI_COLORMETRY_DATA_BLOCK;

/**
 * \brief
 *  the HDMI EDID data block collection structure
 */
typedef struct
{
  ST_DRV_HDMI_VIDEO_DATA_BLOCK     			 stVideoData;		/*!< Video data block			*/
  ST_DRV_HDMI_AUDIO_DATA_BLOCK     			 stAudioData;		/*!< Audio data block			*/
  ST_DRV_HDMI_SPEAKER_ALLOCATION_DATA_BLOCK  stSpeakerData;		/*!< Speaker data block			*/
  ST_DRV_HDMI_VSDB    						 stVendorData;		/*!< Vendor data block			*/
  ST_DRV_HDMI_COLORMETRY_DATA_BLOCK			 stColormetryData;	/*!< Colormetry data block		*/
}ST_DRV_HDMI_DATA_BLOCK_COLLECTION, *PST_DRV_HDMI_DATA_BLOCK_COLLECTION;

/**
 * \brief
 *  the HDMI EDID timing descriptor structure
 */
typedef struct
{
    u32     u32PixelClock;							/*!< Pixel clock, Hz divided by 10000 	*/
    u32     u32HorActivePixel;						/*!< Horizontal Active Pixels			*/
    u32     u32HorBlankingPixel;                    /*!< Horizontal Blanking Pixels			*/
    u32     u32VerActiveLine;                       /*!< Vertical Active Lines				*/
    u32     u32VerBlankingLine;                     /*!< Vertical Blanking Lines			*/
    u32     u32HSyncOffset;                         /*!< Horizontal Sync. Offset, Pixels	*/
    u32     u32HSyncWidth;							/*!< Horizontal Sync Pulse Width Pixels	*/
    u32     u32VSyncOffset;                         /*!< Vertical Sync Offset, Lines		*/
    u32     u32VSyncWidth;                          /*!< Vertical Sync Pulse Width, Lines	*/
    u32     u32HImageSize;                          /*!< Horizontal Image Size, mm			*/
    u32     u32VImageSize;                          /*!< Vertical Image Size, mm			*/
    u32     u32HBorder;								/*!< Horizontal Border, Pixels			*/
    u32     u32VBorder;                             /*!< Vertical Border, Lines				*/
    bool   b8IsInterlaced;                         /*!< Interlace							*/
    EN_DRV_HDMI_EDID_STEREO  enStereo;              /*!< Stereo mode						*/
    EN_DRV_HDMI_EDID_SYNC 	 enSyncDescription;     /*!< Sync Signal Description			*/
}ST_DRV_HDMI_EDID_TIMING_DESCRIPTOR, *PST_DRV_HDMI_EDID_TIMING_DESCRIPTOR;

/**
 * \brief
 *  the HDMI EDID monitor descriptor GTF parameters structure
 */
typedef struct
{
    u32 u32C;    /*!< 0=<C=<127		*/
    u32 u32M;    /*!< 0=<M=<65535	*/
    u32 u32K;    /*!< 0=< K=<255	*/
    u32 u32J;    /*!< 0=< J=<127	*/
}ST_DRV_HDMI_GTF_PARAMS, *PST_DRV_HDMI_GTF_PARAMS;

/**
 * \brief
 *  the HDMI EDID monitor descriptor range limit structure
 */
typedef struct
{
    u32                 	u32MinVertRate;			/*!< Min. Vertical rate, Hz 									*/
    u32                 	u32MaxVertRate;			/*!< Max. Vertical rate, Hz 									*/
    u32                 	u32MinHorRate;			/*!< Min. Horizontal in KHz 									*/
    u32                 	u32MaxHorRate;			/*!< Max. Horizontal in KHz 									*/
    u32                 	u32MaxPixelClock;		/*!< Max. Supported Pixel Clock, MHz/10 						*/
    bool               	b8IsSecondGTFSupported;	/*!< Secondary GTF curve										*/
    u32                 	u32StartFrequency;		/*!< Start frequency for secondary curve, Hor. freq./2 KHz 		*/
    ST_DRV_HDMI_GTF_PARAMS  stGTFParams;			/*!< GTF parameters 											*/
}ST_DRV_HDMI_MONITOR_RANGE_LIMIT, *PST_DRV_HDMI_MONITOR_RANGE_LIMIT;

/**
 * \brief
 *  the HDMI EDID monitor descriptor color point structure
 */
typedef struct
{
    u32 au32White_x[2];			/*!< White_x		*/
    u32 au32White_y[2];			/*!< White_y		*/
    u32 au32WhiteGamma[2];		/*!< White Gamma	*/
}ST_DRV_HDMI_MONITOR_COLOR_POINT, *PST_DRV_HDMI_MONITOR_COLOR_POINT;

/**
 * \brief
 *  the HDMI EDID standard timing structure
 */
typedef struct
{
    bool                  b8IsStandardTimingUsed;	/*!< Is standard timing used							*/
    u32                    u32HorizontalActive;		/*!< (Horizontal active pixels / 8) - 31, 256~2288 		*/
    u32                    u32VerticalActive;		/*!< Vertical active pixels 							*/
    u32                    u32RefreshRate;			/*!< Refresh Rate, 60~123Hz 							*/
}ST_DRV_HDMI_EDID_STANDARD_TIMING, *PST_DRV_HDMI_EDID_STANDARD_TIMING;

/**
 * \brief
 *  the HDMI EDID monitor descriptor timing ID structure
 */
typedef struct
{
    ST_DRV_HDMI_EDID_STANDARD_TIMING    astStdTiming[6];	/*!< Standard timing	*/

}ST_DRV_HDMI_MONITOR_TIMING_ID, *PST_DRV_HDMI_MONITOR_TIMING_ID;

/**
 * \brief
 *  the HDMI EDID monitor descriptor data union
 */
typedef union
{
    u8        						 au8ASCIIData[13];		/*!< String end with null					*/
    ST_DRV_HDMI_MONITOR_RANGE_LIMIT  stRangeLimit;			/*!< Monitor Range Limit					*/
    ST_DRV_HDMI_MONITOR_COLOR_POINT  stColorPoint;			/*!< Monitor Color Point					*/
    ST_DRV_HDMI_MONITOR_TIMING_ID    stTmingId;				/*!< Monitor Standard Timing Identifiers	*/
}UN_DRV_HDMI_MONITOR_DESCRIPTOR_DATA;

/**
 * \brief
 *  the HDMI EDID monitor descriptor parameters structure
 */
typedef struct
{
    u8                             			  u8Tag;			/*!< Data Tag					*/
    UN_DRV_HDMI_MONITOR_DESCRIPTOR_DATA       unDescriptorData;	/*!< Monitor Descriptor Data	*/
}ST_DRV_HDMI_EDID_MONITOR_DESCRIPTOR, *PST_DRV_HDMI_EDID_MONITOR_DESCRIPTOR;

/**
 * \brief
 *  the HDMI EDID CEA extension sink parameters structure
 */
typedef struct
{
    bool                        b8IsUnderscanSink;			/*!< = 1 if sink underscans IT video formats by default	*/
    bool                        b8IsBasicAudioSupported;   /*!< = 1 if sink supports basic audio					*/
    bool                        b8IsYCbCr444;              /*!< = 1 if sink supports YCbCr444						*/
    bool                        b8IsYCbCr422;              /*!< = 1 if sink supports YCbCr422						*/
    u32                          u32NativeFormatNum;		/*!< = total number of native DTDs						*/
}ST_DRV_HDMI_EDID_SINK_PARAMS, *PST_DRV_HDMI_EDID_SINK_PARAMS;

/**
 * \brief
 *  the HDMI EDID CEA extension structure
 */
typedef struct
{
    u32    								 u32Tag;				/*!< Tag (0x02)							*/
    u32    								 u32RevisionNumber;		/*!< Revision Number					*/
    bool								 b8DataBlockExist;		/*!< There is data block collection		*/
    u32    								 u32Checksum;           /*!< Checksum							*/
    ST_DRV_HDMI_EDID_SINK_PARAMS    	 stFormatDescription;	/*!< Sink parameters					*/
    ST_DRV_HDMI_DATA_BLOCK_COLLECTION    stDataBlock;           /*!< Data blocks						*/
    u8									 u8TimingDescNum;       /*!< Timing descriptors number			*/
    ST_DRV_HDMI_EDID_TIMING_DESCRIPTOR   stTimingDesc[6];       /*!< Timing descriptors					*/
    u8									 u8MonitorDescNum;		/*!< Monitor descriptors number			*/
    ST_DRV_HDMI_EDID_MONITOR_DESCRIPTOR  stMonitorDesc[6];      /*!< Monitor descriptors				*/
}ST_DRV_HDMI_EDID_CEA_EXT, *PST_DRV_HDMI_EDID_CEA_EXT;

/**
 * \brief
 *  the HDMI EDID product ID structure
 */
typedef struct
{
    u8  au8IDManufactureName[3];	/*!< ID Manufacturer Name 			*/
    u32 u32IDProductCode;           /*!< ID Product Code 				*/
    u32 u32IDSerialNumber;			/*!< ID Serial Number 				*/
    u32 u32WeekOfManufacture;		/*!< Week of Manufacture, 1~53 		*/
    u32 u32YearOfManufacture;		/*!< Year of Manufacture from 1990 	*/
}ST_DRV_HDMI_EDID_PRODUCT_ID, *PST_DRV_HDMI_EDID_PRODUCT_ID;

/**
 * \brief
 *  the HDMI EDID version/revision structure
 */
typedef struct
{
    u32 u32Version;		/*!< Version no. 	*/
    u32 u32Revision;    /*!< Revision no. */
}ST_DRV_HDMI_EDID_VER, *PST_DRV_HDMI_EDID_VER;

/**
 * \brief
 *  the HDMI EDID video input parameters structure
 */
typedef struct
{
    bool b8IsDigitalSignal;		/*!< Analog/Digital Signal Level 																												*/
    bool b8IsSetupExpected;        /*!< If set = 1, the display expects a blank-to-black setup or pedestal per appropriate Signal Level Standard 									*/
    bool b8IsSepSyncSupported;		/*!< If set = 1, separate syncs. supported 	 																									*/
    bool b8IsCompSyncSupported;    /*!< If set = 1, composite sync. (on Hsync line) supported 																						*/
    bool b8IsSyncOnGreenSupported;	/*!< If set = 1, sync. on green video supported 																								*/
    bool b8IsPulseRequired;        /*!< If set = 1, serration of the Vsync. Pulse is required when composites sync. or sync-on-green video is used									*/
    bool b8IsVesaDFPCompatible;    /*!< If set = 1, Interface is signal compatible with VESA DFP 1.x TMDS CRGB, 1 pixel / clock, up to 8 bits / color MSB aligned, DE active high 	*/
    u32 u32SignalLevelMax;			/*!< reference white above blank, in mili-volts 																								*/
    u32 u32SignalLevelMin;			/*!< level of sync. tip below blank, in mili-volts 																								*/
}ST_DRV_HDMI_VIDEO_INPUT_PARAMS, *PST_DRV_HDMI_VIDEO_INPUT_PARAMS;

/**
 * \brief
 *  the HDMI EDID feature support structure
 */
typedef struct
{
   bool                           b8IsStandby;					/*!< Standby						*/
   bool                           b8IsSuspend;					/*!< Suspend						*/
   bool                           b8IsActiveOff;				/*!< Active Off/Very Low Power		*/
   bool                       	   b8IsRGBDefaultColorSpace; 	/*!< RGB Default Color Space, sRGB	*/
   bool                       	   b8IsPreffredTimingMode;    	/*!< Preffred Timing Mode			*/
   bool                       	   b8IsDefaultGTFSupported;		/*!< Default GTF Supported 			*/
   EN_DRV_HDMI_EDID_DISPLAY_TYPE   enDisplayType;				/*!< Display Type					*/
}ST_DRV_HDMI_FEATURE_SUPPORTED, *PST_DRV_HDMI_FEATURE_SUPPORTED;

/**
 * \brief
 *  the HDMI EDID display parameters structure
 */
typedef struct
{
    u32                        		u32MaxHorImageSize;	/*!< Max. Horizontal Image Size 								*/
    u32                        		u32MaxVerImageSize;	/*!< Max. Vertical Image Size	 								*/
    u32                        		u32DisplayGamma;	/*!< (Gamma display parameter) multiplied by 100 for 100~354 	*/
    ST_DRV_HDMI_VIDEO_INPUT_PARAMS  stVideoInput;		/*!< Video Input												*/
    ST_DRV_HDMI_FEATURE_SUPPORTED   stFeatureSupport;	/*!< Feature Support 											*/
}ST_DRV_HDMI_EDID_DISPLAY_PARAMS, *PST_DRV_HDMI_EDID_DISPLAY_PARAMS;

/**
 * \brief
 *  the HDMI EDID phosphor or filter chromaticity structure
 */
typedef struct
{
    u32 u32Red_x;		/*!< Red_x, multiplied by 1000 		*/
    u32 u32Red_y;		/*!< Red_y, multiplied by 1000 		*/
    u32 u32Green_x;		/*!< Green_x, multiplied by 1000 	*/
    u32 u32Green_y;     /*!< Green_y, multiplied by 1000 	*/
    u32 u32Blue_x;		/*!< Blue_x, multiplied by 1000 	*/
    u32 u32Blue_y;      /*!< Blue_y, multiplied by 1000 	*/
    u32 u32White_x;     /*!< White_x, multiplied by 1000 	*/
    u32 u32White_y;     /*!< White_y, multiplied by 1000 	*/
}ST_DRV_HDMI_EDID_COLOR_PARAMS, *PST_DRV_HDMI_EDID_COLOR_PARAMS;

/**
 * \brief
 *  the HDMI EDID established timings structure
 */
typedef struct
{
    EN_DRV_HDMI_EDID_ESTABLISHED_TIMING   enTiming;		/*!< Established Timing 	*/
    bool                 b8IsManTimingSupported;       /*!< Manufacturer's Timings */
}ST_DRV_HDMI_EDID_ESTABLISHED_TIMING, *PST_DRV_HDMI_EDID_ESTABLISHED_TIMING;

/**
 * \brief
 *  the HDMI EDID structure
 */
typedef struct
{
    u8                              	 au8EDIDHeader[8];			/*!< EDID Header 				*/
    u32                             	 u32EDIDExtensionFlag;      /*!< EDID Extension Flag 		*/
    u32                             	 u32EDIDChecksum;           /*!< EDID Checksum 				*/
    ST_DRV_HDMI_EDID_PRODUCT_ID     	 stEDIDProductID;           /*!< EDID ProductID 			*/
    ST_DRV_HDMI_EDID_VER		         stEDIDVer;                 /*!< EDID Version Revision 		*/
    ST_DRV_HDMI_EDID_DISPLAY_PARAMS  	 stEDIDDisplayParams;       /*!< Display Parameters 		*/
    ST_DRV_HDMI_EDID_COLOR_PARAMS    	 stEDIDColorParams;         /*!< Color Parameters 			*/
    ST_DRV_HDMI_EDID_ESTABLISHED_TIMING  stEDIDEstablishedTiming;   /*!< Established Timing 		*/
    ST_DRV_HDMI_EDID_STANDARD_TIMING     stEDIDStdTiming[8];		/*!< Standard Timing 			*/
    u8									 u8TimingDescNum;           /*!< Timing Descriptor number 	*/
    ST_DRV_HDMI_EDID_TIMING_DESCRIPTOR   stTimingDesc[2];           /*!< Timing Descriptor			*/
    u8									 u8MonitorDescNum;          /*!< Monitor Descriptor number	*/
    ST_DRV_HDMI_EDID_MONITOR_DESCRIPTOR  stMonitorDesc[3];          /*!< Monitor Descriptor 		*/
}ST_DRV_HDMI_EDID_STRUCTURE, *PST_DRV_HDMI_EDID_STRUCTURE;

/**
 * \brief
 *  the HDMI sink EDID structure
 */
typedef struct
{
    ST_DRV_HDMI_EDID_STRUCTURE      stEDIDBasic;							/*!< EDID Basic block				*/
    u8								u8ExtNum;								/*!< EDID Extension block number	*/
    ST_DRV_HDMI_EDID_CEA_EXT		astCEAExt[DRV_HDMI_MAX_CEA_EXT_NUM];    /*!< EDID Extension block 			*/
}ST_DRV_HDMI_EDID_SINK, *PST_DRV_HDMI_EDID_SINK;

/**
 * \brief
 *  the HDCP KSV structure
 */
typedef struct
{
	u8	au8Ksv[5];	/*!< 40 bits KSV	*/
}ST_DRV_HDMI_HDCP_KSV, *PST_DRV_HDMI_HDCP_KSV;

/**
 * \brief
 *  the HDCP device key structure
 */
typedef struct
{
	u8	au8Key[7];	/*!< 56 bits device key	*/
}ST_DRV_HDMI_HDCP_DEVICE_KEY, *PST_DRV_HDMI_HDCP_DEVICE_KEY;

/**
 * \brief
 *  the HDCP parameters structure
 */
typedef struct
{
	ST_DRV_HDMI_HDCP_KSV			stAksv;				/*!< AKSV			*/
	ST_DRV_HDMI_HDCP_DEVICE_KEY		astDeviceKey[40];	/*!< 40 device key	*/
}ST_DRV_HDMI_HDCP_PARAMS, *PST_DRV_HDMI_HDCP_PARAMS;


//function define
u8* DRV_HDMI_GetVersion (void);
/*!\fn u8* DRV_HDMI_GetVersion (void)
 * \brief
 *		Get the HDMI's Version number string
 *
 *
 * \return HDMI Version String
 *
 */

ErrorCode DRV_HDMI_Init (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_INIT_PARAMS pstInitParams);
/*!\fn ErrorCode DRV_HDMI_Init (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_INIT_PARAMS pstInitParams)
 * \brief
 *		Initial the HDMI
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstInitParams		                (Input)  Init parameters
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_HDMI_DEV_RESOURCE			HDMI don't have device resource
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            HDMI already Init.
 *
 */

ErrorCode DRV_HDMI_Term (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_TERM_PARAMS pstTermParams);
/*!\fn ErrorCode DRV_HDMI_Term (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_TERM_PARAMS pstTermParams)
 * \brief
 *		Terminate the HDMI
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstTermParams		                (Input)  Term parameters
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            HDMI not Init.
 *
 */

ErrorCode DRV_HDMI_Open (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_OPEN_PARAMS pstOpenParams, u32 *pu32HdmiHandle);
/*!\fn ErrorCode DRV_HDMI_Open (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_OPEN_PARAMS pstOpenParams, u32 *pu32HdmiHandle)
 * \brief
 *		Open the HDMI
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstOpenParams		                (Input)  Open parameters
 * \param pu32HdmiHandle		            (Input)  HDMI handle
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_NOT_SUPPORTED	            Parameter not supported spec. included
 * \retval ERROR_NO_FREE_HANDLE				No free handle for the device
 *
 */

ErrorCode DRV_HDMI_Close (u32 *pu32HdmiHandle);
/*!\fn ErrorCode DRV_HDMI_Close (u32 *pu32HdmiHandle)
 * \brief
 * 		Release resource associated with a previous opened handle
 *
 * \param	pu32HdmiHandle     	(Input)  Opening handle number
 *
 * \return	EVENT Operation Error Code
 * \retval	ERROR_NO_ERROR               No error
 * \retval	ERROR_INVALID_HANDLE         Handle is not valid
 */

ErrorCode DRV_HDMI_GetCapability (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_CAPABILITY pstCapability);
/*!\fn ErrorCode DRV_HDMI_GetCapability (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_CAPABILITY pstCapability)
 * \brief
 *		Get capabilities of hdmi device
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstCapability		                (Input)  Allocated structure
 *											(Output)	Structure filled with capabilities of the implementation
 *                                                      of the driver
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_GetSourceCapability (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_SOURCE_CAPABILITY pstSourceCapability);
/*!\fn ErrorCode DRV_HDMI_GetSourceCapability (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_SOURCE_CAPABILITY pstSourceCapability)
 * \brief
 *		Get capabilities of hdmi Source
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstSourceCapability               (Input)  Allocated structure
 *											(Output)	Structure filled with capabilities of the HDMI Source
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_GetSinkCapability (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_SINK_CAPABILITY pstSinkCapability);
/*!\fn ErrorCode DRV_HDMI_GetSinkCapability (DRV_DeviceNameType DeviceName, PST_DRV_HDMI_SINK_CAPABILITY pstSinkCapability)
 * \brief
 *		Get capabilities of hdmi Sink deduced from the EDID table
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstSinkCapability	                (Input)  Allocated structure
 *											(Output)	Structure filled with capabilities of the Sink deduced
 *														from the EDID table
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_FillAVIInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_AVI_INFOFRAME pstAVIInfoFrame);
/*!\fn ErrorCode DRV_HDMI_FillAVIInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_AVI_INFOFRAME pstAVIInfoFrame)
 * \brief
 *		Collect and fill the AVI InfoFrame
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstAVIInfoFrame		            (Input)  Allocated structure
 *											(Output)	Structure filled with Auxiliary video information
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_FillSPDInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_SPD_INFOFRAME pstSPDInfoFrame);
/*!\fn ErrorCode DRV_HDMI_FillSPDInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_SPD_INFOFRAME pstSPDInfoFrame)
 * \brief
 *		Collect and fill the SPD InfoFrame
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstSPDInfoFrame		            (Input)  Allocated structure
 *											(Output)	Structure filled with Source product description
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_FillAUDIOInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_AUDIO_INFOFRAME pstAUDIOInfoFrame);
/*!\fn ErrorCode DRV_HDMI_FillAUDIOInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_AUDIO_INFOFRAME pstAUDIOInfoFrame)
 * \brief
 *		Collect and fill the AUDIO InfoFrame
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstAUDIOInfoFrame		            (Input)  Allocated structure
 *											(Output)	Structure filled with audio information
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_FillMSInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_MS_INFOFRAME pstMSInfoFrame);
/*!\fn ErrorCode DRV_HDMI_FillMSInfoFrame (u32 u32HdmiHandle, PST_DRV_HDMI_MS_INFOFRAME pstMSInfoFrame)
 * \brief
 *		Collect and fill the MS InfoFrame
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstMSInfoFrame		            (Input)  Allocated structure
 *											(Output)	Structure filled with MPEG source information
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_FillSinkEDID (u32 u32HdmiHandle, PST_DRV_HDMI_EDID_SINK pstEDIDBuffer);
/*!\fn ErrorCode DRV_HDMI_FillSinkEDID (u32 u32HdmiHandle, PST_DRV_HDMI_EDID_SINK pstEDIDBuffer)
 * \brief
 *		Parse the EDID table and fill all the information retrieved in their appropriate fields
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstEDIDBuffer		            	(Input)  Allocated structure
 *											(Output)	structure filled with Sink information
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_GetPhysicalAddress (u32 u32HdmiHandle, u16* pu16PhysicalAddress);
/*!\fn ErrorCode DRV_HDMI_GetPhysicalAddress (u32 u32HdmiHandle, u16* pu16PhysicalAddress)
 * \brief
 *		Get the Source Physical Address
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pu16PhysicalAddress				(Output) 	HDMI n.n.n.n 4 digits (4 bit each) physical address
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_Enable (u32 u32HdmiHandle);
/*!\fn ErrorCode DRV_HDMI_Enable (u32 u32HdmiHandle)
 * \brief
 *		Enable HDMI output
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_Disable (u32 u32HdmiHandle);
/*!\fn ErrorCode DRV_HDMI_Disable (u32 u32HdmiHandle)
 * \brief
 *		Disable HDMI output
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */
#ifdef SEN5_HDMI_CERTIFICATION
ErrorCode DRV_HDMI_SetOutputParams (u32 u32HdmiHandle, PST_DRV_HDMI_OUTPUT_PARAMS pstOutputParams, EN_DRV_HDMI_PICTURE_ASPECT_RATIO enRatio);
#else
ErrorCode DRV_HDMI_SetOutputParams (u32 u32HdmiHandle, PST_DRV_HDMI_OUTPUT_PARAMS pstOutputParams);
#endif
/*!\fn ErrorCode DRV_HDMI_SetOutputParams (u32 u32HdmiHandle, PST_DRV_HDMI_OUTPUT_PARAMS pstOutputParams)
 * \brief
 *		Set HDMI output parameters
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstOutputParams		            (Input)  Output parameters
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_GetOutputParams (u32 u32HdmiHandle, PST_DRV_HDMI_OUTPUT_PARAMS pstOutputParams);
/*!\fn ErrorCode DRV_HDMI_GetOutputParams (u32 u32HdmiHandle, PST_DRV_HDMI_OUTPUT_PARAMS pstOutputParams)
 * \brief
 *		Get HDMI output parameters
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstOutputParams		            (Input)  Ouput parameters
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_GetState (u32 u32HdmiHandle, EN_DRV_HDMI_STATE *penState);
/*!\fn ErrorCode DRV_HDMI_GetState (u32 u32HdmiHandle, EN_DRV_HDMI_STATE *penState)
 * \brief
 *		Get the HDMI state
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param penState		            		(Output)	HDMI state
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_Authentication (u32 u32HdmiHandle, bool bEnable);
/*!\fn ErrorCode DRV_HDMI_Authentication (u32 u32HdmiHandle, bool bEnable)
 * \brief
 *		Do HDCP authentication
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param bEnable		                	(Input)  Enable or disable authentication
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_SetHDCPParams (u32 u32HdmiHandle, PST_DRV_HDMI_HDCP_PARAMS pstHDCPParams);
/*!\fn ErrorCode DRV_HDMI_SetHDCPParams (u32 u32HdmiHandle, PST_DRV_HDMI_HDCP_PARAMS pstHDCPParams)
 * \brief
 *		Set HDCP parameters
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstHDCPParams		            	(Input)  HDCP parameters
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_HDMI_CheckHDCPBank (u8 *u8HDCPBank, u32 u32BankLen);
/*!\fn ErrorCode DRV_HDMI_CheckHDCPBank (u8 *u8Buff, u32 u32Length)
 * \brief
 *		Set HDCP parameters
 *
 * \param u32HdmiHandle		                (Input)  Handle of opened hdmi driver
 * \param pstHDCPParams		            	(Input)  HDCP parameters
 *
 * \return HDMI Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */
/*******************************************************************************************/
#endif //__DRV_HDMI_H__

