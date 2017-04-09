//==========================================================================
//  Copyright (c) 2009, NOVATEK MICROELECTRONICS CORP. All rights reserved.
//  STB SA, all right reserved.
//
//	Product	:
//
//	Date	: 2009.01.07
//	Author	:
//	Purpose	: This APIs interfaces AP with audio driver.
//	Sources	: drv_audio.c, drv_audio.h
//==========================================================================
//
// Modification use :
//==========================================================================
//	Update
//
//	Date  	:
//	Name	:
//	Description	:
//
//			Item			                                  Source
//	----------------------------------------		-------------------
//
//==========================================================================
#ifndef __DRV_AUDIO_H__
#define __DRV_AUDIO_H__


/***************************************************************************
 * Include files
 * ************************************************************************/
#include "def_type.h"
#include "def_err.h"
#include "os.h"
//#include "drv_gpio.h"
#include "drv_config.h"
#include "drv_stc.h"

/***************************************************************************
 * Definition
 * ************************************************************************/
//#define DDP_CERTIFICATION
//#define PERFORMANCE_ISSUE

#define MAX_DRV_ADEC_TRICK_SPEEDS				6
#define MAX_DRV_ADEC_INPUT_OBJECTS				1
#define MAX_DRV_ADEC_DECODER_OBJECTS			1
#define MAX_DRV_ADEC_POST_PROC_OBJECTS			1
#define MAX_DRV_ADEC_MIXER_OBJECTS				1
#define MAX_DRV_ADEC_OUTPUT_OBJECTS				3
#define MAX_DRV_ADEC_ENCODER_OBJECTS			1

#define	DRV_ADEC_CLASS_DECODER				(0x1 << 31) //0x80000000
#define	DRV_ADEC_CLASS_ENCODER				(0x1 << 30) //0x40000000
#define	DRV_ADEC_CLASS_OUTPUT				(0x1 << 29) //0x20000000
#define DRV_ADEC_CLASS_POSTPROC				(0x1 << 30) //0x10000000
#define	DRV_ADEC_CLASS_MIXER				(0x1 << 29) //0x08000000

#define DRV_ADEC_TYPE_INPUT_COMPRESSED		(0x1 << 8) //0x00000000
#define DRV_ADEC_TYPE_INPUT_PCM				(0x1 << 9) //0x00000100
#define	DRV_ADEC_TYPE_INPUT_PCM_READER		(0x1 << 10)//0x00000200

#define DRV_ADEC_TYPE_PPROC_GENERIC			(0x1 << 16) //0x00010000

#define DRV_ADEC_TYPE_OUTPUT_ENCODE			(0x1 << 17) //0x00008000
#define DRV_ADEC_TYPE_OUTPUT_STEREO			(0x1 << 15) //0x00008000
#define DRV_ADEC_TYPE_OUTPUT_SPDIF			(0x1 << 14) //0x00004000
#define DRV_ADEC_TYPE_OUTPUT_MULTICHANNEL	(0x1 << 13) //0x00002000
#define	DRV_ADEC_TYPE_OUTPUT_ANALOG			(0x1 << 12) //0x00001000

/* Critical section protect */
#define ADEC_EnterCriticalSection(x)		OS_MutexLock(x.mutex_handle, OS_IPC_ALWAYS_WAIT)
#define ADEC_LeaveCriticalSection(x)		OS_MutexUnLock(x.mutex_handle)

#define ADEC_PTS_BUFFER_SIZE				2048              /* Size must be "power of two - 1" */
typedef struct os_mutex_t					ADEC_Mutex_t;

#define ADEC_PTS_BUFFER_MASK				(ADEC_PTS_BUFFER_SIZE-1)             /* Mask is related to size */

/***************************************************************************
 * Type definition
 * ************************************************************************/
typedef ErrorCode (*GetWriteAddress)(void * const phandle, void** const ppaddress);
typedef ErrorCode (*InformReadAddress)(void * const phandle, void* const paddress);

/***************************************************************************
 * Enumeration
 * ************************************************************************/
/*!
 * \brief
 * Enumeration type that defines the possible audio coding mode.
 */
typedef enum
{
	EN_DRV_ADEC_ACC_MODE20t,				/*  0 */
	EN_DRV_ADEC_ACC_MODE10,					/*  1 */
	EN_DRV_ADEC_ACC_MODE20,					/*  2 */
	EN_DRV_ADEC_ACC_MODE30,					/*  3 */
	EN_DRV_ADEC_ACC_MODE21,					/*  4 */
	EN_DRV_ADEC_ACC_MODE31,					/*  5 */
	EN_DRV_ADEC_ACC_MODE22,					/*  6 */
	EN_DRV_ADEC_ACC_MODE32,					/*  7 */
	EN_DRV_ADEC_ACC_MODE23,					/*  8 */
	EN_DRV_ADEC_ACC_MODE33,					/*  9 */
	EN_DRV_ADEC_ACC_MODE24,					/*  A */
	EN_DRV_ADEC_ACC_MODE34,					/*  B */


	EN_DRV_ADEC_ACC_MODE_ID = 0xFF
/* FF */
} EN_DRV_ADEC_AudioCodingMode;

/*!
 * \brief
 * Defint the MPEG format.
 */
typedef enum
{
	EN_DRV_ADEC_MPEG_LAYER_I = 1,				/*!< MPEG LAYER I */
	EN_DRV_ADEC_MPEG_LAYER_II,					/*!< MPEG LAYER II */
	EN_DRV_ADEC_MPEG_LAYER_III,					/*!< MPEG LAYER III */
	EN_DRV_ADEC_MPEG_LAYER_NONE
} EN_DRV_ADEC_MPEG_Layer;

/*!
 * \brief
 * Device define
 */
typedef enum
{
	EN_DRV_ADEC_DEVICE_NT78310=310,
	EN_DRV_ADEC_DEVICE_NT78320=320
} EN_DRV_ADEC_Device;

/*!
 * \brief
 * Enumeration type that defines the possible PCM output format standards.
 */
typedef enum
{
	EN_DRV_ADEC_DAC_DATA_ALIGNMENT_RIGHT=0x0,			/*!< Data format alignment right. */
	EN_DRV_ADEC_DAC_DATA_FORMAT_I2S,					/*!< Data format used is I2S.	*/
	EN_DRV_ADEC_DAC_DATA_ALIGNMENT_LEFT					/*!< Data format alignment left. */
} EN_DRV_ADEC_DACDataFormat;

/*!
 * \brief
 * Enumeration type that defines the possible bit precisions for PCM output formatting.
 */

typedef enum
{
	EN_DRV_ADEC_DAC_DATA_PRECISION_16BITS=0,			/*!< 16-bit DAC precision.	*/
	EN_DRV_ADEC_DAC_DATA_PRECISION_24BITS,				/*!< 24-bit DAC precision.	*/
	EN_DRV_ADEC_DAC_DATA_PRECISION_32BITS				/*!< 32-bit DAC precision.	*/
} EN_DRV_ADEC_DACDataPrecision;

/*!
 * \brief
 *  Enumeration type that defines the possible number of bits per subframe of PCM data.
 */
typedef enum
{
	EN_DRV_ADEC_DAC_NBITS_SUBFRAME_32						/*!< 32 Bits per subframe.	*/
} EN_DRV_ADEC_DACNumBitsSubframe;

/*!
 * \brief
 * Defines the copyright mode required on the digital output.
 */
typedef enum
{
	EN_DRV_ADEC_COPYRIGHT_MODE_NO_RESTRICTION,				/*!< No restriction.	*/
	EN_DRV_ADEC_COPYRIGHT_MODE_ONE_COPY,					/*!< One copy allowed.	*/
	EN_DRV_ADEC_COPYRIGHT_MODE_NO_COPY						/*!< No copy allowed.	*/
} EN_DRV_ADEC_CopyRightMode;

/*!
 * \brief
 * Enumeration type that defines the possible bit precisions for SPDIF output formatting.
 */
typedef enum
{
	EN_DRV_ADEC_SPDIF_DATA_PRECISION_32BITS					/*!< 32-bit SPDIF precision. */
} EN_DRV_ADEC_SPDIFDataPrecision;

/*!
 * \brief
 * Enumeration type that defines the possible copyright mode for SPDIF.
 */
typedef enum
{
	EN_DRV_AOUT_SPDIF_CP_NONE,
	EN_DRV_AOUT_SPDIF_CP_ONCE,
	EN_DRV_AOUT_SPDIF_CP_NEVER,
	EN_DRV_AOUT_SPDIF_CP_NUM
} EN_DRV_AOUT_SPDIF_CP_TYPE, *PEN_DRV_AOUT_SPDIF_CP_TYPE;   

/*!
 * \brief
 * Enumeration type that defines the possible mode for SPDIF output formatting.
 */

typedef enum
{
	EN_DRV_ADEC_DIGITAL_MODE_OFF=0,							/*!< The digital output is off.	*/
	EN_DRV_ADEC_DIGITAL_MODE_ON=1,							/*!< The digital output is on.	*/
	EN_DRV_ADEC_DIGITAL_MODE_NONCOMPRESSED=2,				/*!< The output are PCM data.	*/
	EN_DRV_ADEC_DIGITAL_MODE_COMPRESSED=3,					/*!< The compressed bitstream is transmitted on the digital output	*/
} EN_DRV_ADEC_DigitalMode;

/*!
 * \brief
 * Enumeration type that defines the possible path for HDMI output.
 */

typedef enum
{
	EN_DRV_ADEC_HDMI_OUT_PATH_PCM=0,							/*!< The HDMI ouput is PCM.	*/
	EN_DRV_ADEC_HDMI_OUT_PATH_TRANSCODE=1,							/*!< The HDMI ouput is Transcode.	*/
	EN_DRV_ADEC_HDMI_OUT_PATH_BYPASS=2,				/*!< The HDMI ouput is Bypass.	*/
} EN_DRV_ADEC_HDMI_OUT_PATH;

/*!
 * \brief
 * Enumeration type that defines the possible mode for Encode Type.
 */

typedef enum
{
    EN_DRV_ADEC_ENCODE_TYPE_OFF,
    EN_DRV_ADEC_ENCODE_TYPE_TRANSCODE,
    EN_DRV_ADEC_ENCODE_TYPE_BYPASS
} EN_DRV_ADEC_Encode_Type;

/*!
 * \brief
 * Enumeration type that defines what kinds of the RAW data output by DD.
 */

typedef enum
{
    EN_DRV_ADEC_DD_RAWDATA_NO_DATA = 0,
    EN_DRV_ADEC_DD_RAWDATA_TRANSCODE_ONLY = 1,
    EN_DRV_ADEC_DD_RAWDATA_BYPASS_ONLY_HBR = 2,
    EN_DRV_ADEC_DD_RAWDATA_BYPASS_ONLY_DAC1 = 3,
    EN_DRV_ADEC_DD_RAWDATA_BOTH_HBR = 4,
    EN_DRV_ADEC_DD_RAWDATA_BOTH_DAC1 = 5,
} EN_DRV_ADEC_DD_RAWDATA;

/*!
 * \brief
 * Enumeration type that defines the PCM out enable/disable.
 */
typedef enum
{
	EN_DRV_ADEC_PCM_ON,										/*!< PCM output ON	*/
	EN_DRV_ADEC_PCM_OFF										/*!< PCM output OFF	*/
} EN_DRV_ADEC_PCMMode;

/*!
 * \brief
 * Enumeration type that defines the possible data rounding format for the data read by the PCM reader.
 */
typedef enum
{
	EN_DRV_ADEC_NO_ROUNDING_PCMR,							/*!< No rounding to be applied */
	EN_DRV_ADEC_BIT16_ROUNDING_PCMR							/*!< 16 Bit rounding of the PCM data */
} EN_DRV_ADEC_PCMReaderRnd;

/*!
 * \brief
 * Enumeration type that defines the possible ways of stopping the decoder.
 */
typedef enum
{
	EN_DRV_ADEC_STOP_WHEN_END_OF_DATA = 1,			/*!< Enumeration type that defines the possible ways of stopping the decoder. */
	EN_DRV_ADEC_STOP_NOW = 2						/*!< The decoder will stop immediately. */
} EN_DRV_ADEC_Stop;

/*!
 * \brief
 *  Enumeration type that defines the possible content of input data streams.
 */
typedef enum
{
#if 0
	EN_DRV_ADEC_STREAM_CONTENT_NULL ,
	EN_DRV_ADEC_STREAM_CONTENT_MPEG ,				/*!< MPEG1/MPEG2 Layer I or Layer II stream		*/
	EN_DRV_ADEC_STREAM_CONTENT_MP3 ,					/*!< MPEG1 or MPEG2 Layer III stream			*/
	EN_DRV_ADEC_STREAM_CONTENT_WMA,					/*!< Windows Media Audio						*/
	EN_DRV_ADEC_STREAM_CONTENT_AAC ,					/*!< MPEG2 Advanced Audio Coding stream			*/
	EN_DRV_ADEC_STREAM_CONTENT_AC3 ,					/*!< AC-3 stream	(Dolby Digital)				*/
	EN_DRV_ADEC_STREAM_CONTENT_OGG ,					/*!< Ogg Vorbis									*/
	EN_DRV_ADEC_STREAM_CONTENT_AMR ,					/*!< Adaptive multi-Rate compression			*/
	EN_DRV_ADEC_STREAM_CONTENT_PCM ,					/*!< PCM stream									*/
	EN_DRV_ADEC_STREAM_CONTENT_LPCM ,				/*!< LPCM stream								*/
	EN_DRV_ADEC_STREAM_CONTENT_ADPCM ,				/*!< Adaptive Differential Pulse Code Modulation	*/
	EN_DRV_ADEC_STREAM_CONTENT_COOK ,
#else
	EN_DRV_ADEC_STREAM_CONTENT_NULL  = 0,
	EN_DRV_ADEC_STREAM_CONTENT_MPEG  = (1 << 0),				/*!< MPEG1/MPEG2 Layer I or Layer II stream		*/
	EN_DRV_ADEC_STREAM_CONTENT_MP3   = (1 << 1),					/*!< MPEG1 or MPEG2 Layer III stream			*/
	EN_DRV_ADEC_STREAM_CONTENT_WMA   = (1 << 2),					/*!< Windows Media Audio						*/
	EN_DRV_ADEC_STREAM_CONTENT_AAC   = (1 << 3),					/*!< MPEG2 Advanced Audio Coding stream			*/
	EN_DRV_ADEC_STREAM_CONTENT_AC3   = (1 << 4),					/*!< AC-3 stream	(Dolby Digital)				*/
	EN_DRV_ADEC_STREAM_CONTENT_OGG   = (1 << 5),					/*!< Ogg Vorbis									*/
	EN_DRV_ADEC_STREAM_CONTENT_AMR   = (1 << 6),					/*!< Adaptive multi-Rate compression			*/
	EN_DRV_ADEC_STREAM_CONTENT_PCM   = (1 << 7),					/*!< PCM stream									*/
	EN_DRV_ADEC_STREAM_CONTENT_LPCM  = (1 << 8),				/*!< LPCM stream								*/
	EN_DRV_ADEC_STREAM_CONTENT_ADPCM = (1 << 9),				/*!< Adaptive Differential Pulse Code Modulation	*/
	EN_DRV_ADEC_STREAM_CONTENT_COOK  = (1 << 10),
	EN_DRV_ADEC_STREAM_CONTENT_DTS   = (1 << 11),
	EN_DRV_ADEC_STREAM_CONTENT_EAC3   = (1 << 12),					/*!< EAC-3 stream	(Dolby Digital Plus)				*/
#endif

} EN_DRV_ADEC_StreamContent;

/*!
 * \brief
 * Define the possible stream type that carries audio content.
 */
typedef enum
{
	EN_DRV_ADEC_STREAM_TYPE_ES = (1 << 0),						/*!< Elementary stream			*/
	EN_DRV_ADEC_STREAM_TYPE_PES = (1 << 1),						/*!< Packetized elementary stream as defined by ISO/IEC13818					*/
	EN_DRV_ADEC_STREAM_TYPE_PES_AD = (1 << 2),					/*!< Packetized elementary stream as defined by ISO/IEC13818 (MPEG2) with audio description channel	*/
} EN_DRV_ADEC_StreamType;

/*!
 * \brief
 * Define the possible stereo output effects.
 */
typedef enum
{
	EN_DRV_ADEC_EFFECT_NONE = (1 << 0),							/*!< No stereo effect applied.	*/
	EN_DRV_ADEC_EFFECT_SRS_3D = (1 << 1),						/*!< Stereo output with 3D sound effect from a stereo input.	*/
	EN_DRV_ADEC_EFFECT_TRUSURROUND = (1 << 2),					/*!< Output an enhanced stereo output from a multichannel input.	*/
	EN_DRV_ADEC_EFFECT_SRS_TRUBASS = (1 << 3),					/*!< Output audio enhancement that provides deep rich bass for small speakers without the need of subwoofer	*/
	EN_DRV_ADEC_EFFECT_SRS_FOCUS = (1 << 4),					/*!< Output an enhanced audio voice				*/
	EN_DRV_ADEC_EFFECT_SRS_TRUSUR_XT = (1 << 5)					/*!< Combination of STAUD_EFFECT_TRUSURROUND	*/
} EN_DRV_ADEC_Effect;

/*!
 * \brief
 * Defines the provided stereo analog downmix modes.
 */
typedef enum
{
	EN_DRV_ADEC_STEREO_MODE_STEREO = 0,							/*!< Stereo output on front channels.	*/
    EN_DRV_ADEC_STEREO_MODE_DUAL_LEFT = 1,						/*!< Left channel of the stream output both on front channels.	*/
    EN_DRV_ADEC_STEREO_MODE_DUAL_RIGHT = 2,						/*!< Right channel of the stream output both on front channels.	*/
    EN_DRV_ADEC_STEREO_MODE_DUAL_MONO = 3,//mixed				/*!< Left and right input channels are mixed and the result is output on both front channels. */
    EN_DRV_ADEC_STEREO_MODE_AUTO = 32,
    //EN_DRV_ADEC_STEREO_MODE_SECOND_STEREO = 64
} EN_DRV_ADEC_StereoMode;

/*!
 * \brief
 * Defines the AC3 DownMix mode.
 */
typedef enum
{
    EN_DRV_ADEC_DOWNMIX_MODE_LORO = 0,						/*!< Stereo (Lo/Ro).				*/
    EN_DRV_ADEC_DOWNMIX_MODE_LTRT = 1,						/*!< Surround compatible (Lt/Rt).	*/
	EN_DRV_ADEC_DOWNMIX_MODE_AUTO = 2,						/*!< Auto detect .					*/
} EN_DRV_ADEC_DownMixMode;

/*!
 * \brief
 * Defines the Karaoke mode for vocal.
 */
typedef enum
{
	EN_DRV_ADEC_KARAOK_MODE_NO_VOCAL = 0,						/*!< No vocal.					*/
    EN_DRV_ADEC_KARAOK_MODE_LEFT_VOCAL = 1,						/*!< Left vocal.	*/
    EN_DRV_ADEC_KARAOK_MODE_RIGHT_VOCAL = 2,					/*!< Right vocal.				*/
    EN_DRV_ADEC_KARAOK_MODE_BOTH_VOCAL = 3,						/*!< Both vocal.				*/
} EN_DRV_ADEC_KARAOK_MODE;

/*!
 * \brief
 * Enumeration type that defines the hardware blocks which comprise an audio decoder.
 */

typedef enum
{
	EN_DRV_ADEC_OBJECT_NONE=0,																			//
	EN_DRV_ADEC_OBJECT_INPUT_ES=(u32) (DRV_ADEC_TYPE_INPUT_COMPRESSED),									/*!< Object for ES				*/
	EN_DRV_ADEC_OBJECT_DECODER_0 = (u32) (DRV_ADEC_CLASS_DECODER),										/*!< Object for Decoder 0		*/
	EN_DRV_ADEC_POST_PROCESSOR_0 = (u32) (DRV_ADEC_TYPE_PPROC_GENERIC),									/*!< Object for processor 0		*/
	EN_DRV_ADEC_OBJECT_OUTPUT_PCM_0 = (u32) (DRV_ADEC_CLASS_OUTPUT | DRV_ADEC_TYPE_OUTPUT_STEREO),		/*!< Object for Output PCM 0	*/
	EN_DRV_ADEC_OBJECT_OUTPUT_SPDIF_0 = (u32) (DRV_ADEC_CLASS_OUTPUT | DRV_ADEC_TYPE_OUTPUT_SPDIF),		/*!< Object for Output SPDIF 0	*/
	EN_DRV_ADEC_OBJECT_OUTPUT_ENCODE_0 = (u32) (DRV_ADEC_CLASS_ENCODER | DRV_ADEC_TYPE_OUTPUT_ENCODE),		/*!< Object for Output SPDIF 0	*/
} EN_DRV_ADEC_Object;

/*!
 * \brief
 * Defines the profile of the broadcasted stream that the audio stream is extracted from.
 */
typedef enum
{
	EN_DRV_ADEC_BROADCAST_DVB,									/*!< Transport complies with the DVB specifications	*/
	//EN_DRV_ADEC_BROADCAST_ATSC
} EN_DRV_ADEC_BroadcastProfile;

/*!
 * \brief
 * Define the possible SRS effect parameters.
 */
typedef enum
{
	EN_DRV_ADEC_EFFECT_FOCUS_ELEVATION = (1 << 0),				/*!< Focus Elevation level			*/
	EN_DRV_ADEC_EFFECT_FOCUS_TWEETER_ELEVATION = (1 << 1),		/*!< Focus Tweeter Elevation level	*/
	EN_DRV_ADEC_EFFECT_TRUBASS_LEVEL = (1 << 2),				/*!< TRU Bass Level					*/
	EN_DRV_ADEC_EFFECT_INPUT_GAIN = (1 << 3),					/*!< Input Gain						*/
	EN_DRV_ADEC_EFFECT_TSXT_HEADPHONE = (1 << 4),				/*!< TXST Headphone					*/
	EN_DRV_ADEC_EFFECT_TRUBASS_SIZE = (1 << 5),					/*!< Size of speaker				*/
	EN_DRV_ADEC_EFFECT_TXST_MODE = (1 << 6)						/*!< TXST mode						*/
} EN_DRV_ADEC_EffectSRSParams;

/*!
 * \brief
 * Enumeration type that defines the possible types of compression in case of AC3 decoding.
 */
typedef enum
{
	EN_DRV_ADEC_CUSTOM_ANALOG,				/*!< Compression custom analog mode		*/
	EN_DRV_ADEC_CUSTOM_DIGITAL,				/*!< Compression custom digital mode	*/
	EN_DRV_ADEC_LINE_OUT,					/*!< Compression line out mode			*/
	EN_DRV_ADEC_RF_MODE						/*!< Compression RF mode				*/
} EN_DRV_ADEC_CompressionMode;

/*!
 * \brief
 * Enumeration type that defines the possible types of compression in case of AC3 decoding.
 */
typedef enum
{
	EN_DRV_ADEC_LFEMODE_DISABLE,				/*!< LFE Disable		*/
	EN_DRV_ADEC_LFEMODE_ENABLE,					/*!< LFE Enable			*/
} EN_DRV_ADEC_LFEMODE;

/*!
 * \brief
 * Defines the speaker types that are used.
 */
typedef enum
{
	EN_DRV_ADEC_SPEAKER_TYPE_SMALL = 1,		/*!< Small speaker */
	EN_DRV_ADEC_SPEAKER_TYPE_LARGE			/*!< Large speaker */
} EN_DRV_ADEC_SpeakerType;

/*!
 * \brief
 * Defines the bass management type.
 */
typedef enum
{
	EN_DRV_ADEC_MGT_OFF = 0,			/*!< No Bass Management							*/
	EN_DRV_ADEC_MGT_DOLBY_1,			/*!< Bass management dolby config 1				*/
	EN_DRV_ADEC_MGT_DOLBY_2,			/*!< Bass management dolby config 2				*/
	EN_DRV_ADEC_MGT_DOLBY_3,			/*!< Bass management dolby config 3				*/
	EN_DRV_ADEC_MGT_SIMPLIFIED,			/*!< Bass management dolby config Simplified	*/
	EN_DRV_ADEC_MGT_DOLBY_CERT,			/*!< Bass management dolby config 0				*/
	EN_DRV_ADEC_MGT_Philips				/*!< Bass management dolby config philips		*/
} EN_DRV_ADEC_BassMgtType;

/*!
 * \brief
 * Enumeration type that defines the possible stereo modes for MPEG2 audio encoder.
 */
typedef enum
{
	EN_DRV_ADEC_STEREO = 0,				/*!< Normal stereo mode.	*/
	EN_DRV_ADEC_JOINTSTEREO = 1,		/*!< Joint stereo Mode.		*/
	EN_DRV_ADEC_DUALMONO = 2,			/*!< Dual mono stereo mode. */
	EN_DRV_ADEC_MONO = 3				/*!< Mono stereo mode.		*/
} EN_DRV_ADEC_Mp2EncStereoMode;

/*!
 * \brief
 * Defines the emphasis filter type.
 */
typedef enum
{
	EN_DRV_ADEC_NO_EMPHASIS,										/*!< No emphasis filter applied.				*/
	EN_DRV_ADEC_EMPHASIS_50_15_US,									/*!< Filter type 50/15 microseconds applied.	*/
	EN_DRV_ADEC_EMPHASIS_RESERVED,
	EN_DRV_ADEC_EMPHASIS_CCITT,										/*!< Filter type CCITT J.17 applied.			*/
	EN_DRV_ADEC_EMPHASIS_PROCESSED_DISABLED = 4,
	EN_DRV_ADEC_EMPHASIS_PROCESSED_50_15_US,
	EN_DRV_ADEC_EMPHASIS_PROCESSED_RESERVED,
	EN_DRV_ADEC_EMPHASIS_PROCESSED_CCITT
} EN_DRV_ADEC_MP2EncEmphasis;

/*!
 * \brief
 * Defines the possible EQ filter type.
 */
typedef enum
{
	EN_DRV_ADEC_Normal,												/*!< Normal style			*/
	EN_DRV_ADEC_BassBooster,										/*!< BassBooster style		*/
	EN_DRV_ADEC_FullTreble,											/*!< FullTreble style		*/
	EN_DRV_ADEC_Jazz,												/*!< Jazz style				*/
	EN_DRV_ADEC_Rock,												/*!< Rock style				*/
	EN_DRV_ADEC_Classical,											/*!< Classical style		*/
	EN_DRV_ADEC_Pop,												/*!< Pop style				*/
	EN_DRV_ADEC_EQMode_Total
} EN_DRV_ADEC_EQ;

/*!
 * \brief
 * Defines the possible sample frequency.
 */
typedef enum
{
	EN_DRV_ADEC_SAMPLE_FREQ_8K	= 8000,	  	/*!< The audio freq type for 8K		*/
	EN_DRV_ADEC_SAMPLE_FREQ_11K = 11025,	/*!< The audio freq type for 11K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_12K = 12000,	/*!< The audio freq type for 12K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_16K = 16000,	/*!< The audio freq type for 16K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_22K = 22050,	/*!< The audio freq type for 22K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_24K = 24000,	/*!< The audio freq type for 24K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_32K = 32000,	/*!< The audio freq type for 32K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_44K = 44100,	/*!< The audio freq type for 44K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_48K = 48000,	/*!< The audio freq type for 48K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_64K = 64000,	/*!< The audio freq type for 64K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_88K = 88200,	/*!< The audio freq type for 88K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_96K = 96000,	/*!< The audio freq type for 96K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_128K = 128000,    /*!< The audio freq type for 128K*/
	EN_DRV_ADEC_SAMPLE_FREQ_176K = 176400,    /*!< The audio freq type for 176K*/
	EN_DRV_ADEC_SAMPLE_FREQ_192K = 192000,	/*!< The audio freq type for 96K	*/
	EN_DRV_ADEC_SAMPLE_FREQ_NUMBER = 15
} EN_DRV_ADEC_SampleFrequency;

/*!
 * \brief
 * Defines the audio Player Frequency Multiplier.
 */
typedef enum
{
	EN_DRV_ADEC_PLAYER_FREQ_128FS = 128, 	/*!< The audio Player Frequency Multiplier for 128fs*/
	EN_DRV_ADEC_PLAYER_FREQ_256FS = 256, 	/*!< The audio Player Frequency Multiplier for 256fs*/
	EN_DRV_ADEC_PLAYER_FREQ_384FS = 384, 	/*!< The audio Player Frequency Multiplier for 384fs*/
	EN_DRV_ADEC_PLAYER_FREQ_512FS = 512, 	/*!< The audio Player Frequency Multiplier for 512fs*/
	EN_DRV_ADEC_PLAYER_FREQ_NUMBER = 4
} EN_DRV_ADEC_PlayerFrequencyMultiplier;

/*!
 * \brief
 * Defines the ADEC event ID.
 */
typedef enum
{
    EN_DRV_ADEC_EVENT_START                     = 0,				/*!< Decode start */
    EN_DRV_ADEC_EVENT_STOP,											/*!< Decode stop */
    EN_DRV_ADEC_EVENT_DECODE_ERROR,									/*!< Decode error */
    EN_DRV_ADEC_EVENT_DECODE_OK,									/*!< Decode OK */
    EN_DRV_ADEC_EVENT_FREQUENCY_CHANGE,								/*!< Frequency change */
    EN_DRV_ADEC_EVENT_AUDIO_CATCH_STC,								/*!< Catch STC */
    EN_DRV_ADEC_EVENT_AUDIO_LOST_STC,								/*!< Get STC */
    EN_DRV_ADEC_EVENT_APU_NO_ACK,                                   /*!< Get FP and handle */
    EN_DRV_ADEC_EVENT_DECODE_DONE,                                    /*!< Decode done */
    EN_DRV_ADEC_EVENT_DDTYPE_CHANGE,					/*!< DD type change */
    EN_DRV_ADEC_EVENT_SPDIF_AUTO_CHANGE,				/*!< Auto change SPDIF type */
    EN_DRV_ADEC_EVENT_DD_RAWOUTPUT_CHANGE,			/*!< Raw output data change */
    EN_DRV_ADEC_EVENT_AUDIOMODE_CHANGE				/*!< Audio Mode change */
}EN_DRV_ADEC_Event, *PEN_DRV_ADEC_Event;

/*!
 * \brief
 * Defines the type of sync.
 */
typedef enum
{
    EN_DRV_ADEC_SYNC_MASTER_BASE             = 0x0,

    EN_DRV_ADEC_SYNC_MASTER_PCR,									/*!< PVR master.	*/
    EN_DRV_ADEC_SYNC_MASTER_VDEC,									/*!< Video master.	*/
    EN_DRV_ADEC_SYNC_MASTER_ADEC,									/*!< Audio master.	*/
    EN_DRV_ADEC_SYNC_MASTER_FREERUN,								/*!< Free run.		*/

    // for count
    EN_DRV_ADEC_SYNC_MASTER_NB
} EN_DRV_ADEC_SyncMaster, *PEN_DRV_ADEC_SyncMaster;

/*!
 * \brief
 * Beep tone Mode.
 */
typedef enum
{
    EN_DRV_ADEC_BEEPTONE_MODE_DISABLE		= 0x0,					/*!< Disable Beep Tone.					*/
    EN_DRV_ADEC_BEEPTONE_MODE_WITHDECPCM,							/*!< Beep Tone with decoded PCM.		*/
    EN_DRV_ADEC_BEEPTONE_MODE_TONEONLY,								/*!< Only output Beep Tone.				*/
    EN_DRV_ADEC_BEEPTONE_MODE_NUM,
} EN_DRV_ADEC_BEEPTONE_MODE, *PEN_DRV_ADEC_BEEPTONE_MODE;

/*!
 * \brief
 * Define the decode source.
 */
typedef enum
{
	EN_DRV_ADEC_DEC_SOURCE_NULL = 0x0,                  	/*!< srource NULL*/
	EN_DRV_ADEC_DEC_SOURCE_LIVE = 0x1,						/*!< srource from Live */
	EN_DRV_ADEC_DEC_SOURCE_STORAGE = 0x2,					/*!< srource from Storage*/
	EN_DRV_ADEC_DEC_SOURCE_MULTIAUDIO = 0x3,				/*!< srource from Storage_MultiAudio*/
} EN_DRV_ADEC_DEC_SOURCE, *PEN_DRV_ADEC_DEC_SOURCE;

/*!
 * \brief
 * Define the decode MixGain.
 */
typedef enum
{
	EN_DRV_ADEC_DEC_MIXGAIN_PLUS30DB = 0x0,
	EN_DRV_ADEC_DEC_MIXGAIN_PLUS25DB,
	EN_DRV_ADEC_DEC_MIXGAIN_PLUS20DB,
	EN_DRV_ADEC_DEC_MIXGAIN_PLUS15DB,
	EN_DRV_ADEC_DEC_MIXGAIN_PLUS10DB,
	EN_DRV_ADEC_DEC_MIXGAIN_PLUS05DB,
	EN_DRV_ADEC_DEC_MIXGAIN_0DB,  
	EN_DRV_ADEC_DEC_MIXGAIN_05DB,
	EN_DRV_ADEC_DEC_MIXGAIN_10DB,
	EN_DRV_ADEC_DEC_MIXGAIN_15DB,
	EN_DRV_ADEC_DEC_MIXGAIN_20DB,
	EN_DRV_ADEC_DEC_MIXGAIN_25DB,
	EN_DRV_ADEC_DEC_MIXGAIN_30DB,
	EN_DRV_ADEC_DEC_MIXGAIN_35DB,
	EN_DRV_ADEC_DEC_MIXGAIN_40DB,
	EN_DRV_ADEC_DEC_MIXGAIN_45DB,
	EN_DRV_ADEC_DEC_MIXGAIN_50DB,
	EN_DRV_ADEC_DEC_MIXGAIN_55DB,
	EN_DRV_ADEC_DEC_MIXGAIN_60DB,
	EN_DRV_ADEC_DEC_MIXGAIN_65DB,
	EN_DRV_ADEC_DEC_MIXGAIN_70DB,
	EN_DRV_ADEC_DEC_MIXGAIN_75DB,
	EN_DRV_ADEC_DEC_MIXGAIN_80DB,
	EN_DRV_ADEC_DEC_MIXGAIN_85DB,
	EN_DRV_ADEC_DEC_MIXGAIN_90DB,
	EN_DRV_ADEC_DEC_MIXGAIN_95DB,
	EN_DRV_ADEC_DEC_MIXGAIN_100DB,
	EN_DRV_ADEC_DEC_MIXGAIN_TOTAL,
} EN_DRV_ADEC_MIXGAIN, *PEN_DRV_ADEC_MIXGAIN;

typedef enum 
{
	EN_DRV_ADEC_DEC_OUTPUT_MODE_NONE = -1,       //!<: No output
	//For two channels audio
	EN_DRV_ADEC_DEC_OUTPUT_MODE_DUAL = 0,        //!<: DUAL
	EN_DRV_ADEC_DEC_OUTPUT_MODE_MONO = -2,        //!<: Mono
	EN_DRV_ADEC_DEC_OUTPUT_MODE_STEREO = 2,      //!<: Stereo
	//For multiple channels audio
	EN_DRV_ADEC_DEC_OUTPUT_MODE_MULTICH = 3,
	EN_DRV_ADEC_DEC_OUTPUT_MODE_TOTAL
} EN_DRV_ADEC_DEC_OUTPUT_MODE;

/***************************************************************************
 * Structure
 * ************************************************************************/
/*!
 * \brief
 * Structure defining a 33-bit PTS value.
 */
typedef struct
{
    u32     u32PTS;												/*!< bit31~bit0 of PTS */
    u32     u32PTS33;											/*!< bit32 of PTS */
    u32     u32BitBufAddr;										/*!< describe this PTS is which frame in audio bitstream buffer */
} ST_DRV_ADEC_PTS, *PST_DRV_ADEC_PTS;

/*!
 * \brief
 * Defines the PTS buffer info.
 */
typedef struct
{
    u32                     u32WriteIndex;						/*!< Write index of PTS buffer */
    u32                     u32ReadIndex;						/*!< Read index of PTS buffer */

    ST_DRV_ADEC_PTS         astPTSBuffer[ADEC_PTS_BUFFER_SIZE];
} ST_DRV_ADEC_PTSBufferInfo, *PST_DRV_ADEC_PTSBufferInfo;

/*!
 * \brief
 * Define a structure to save 33 bits PTS/PCR value.
 */
typedef struct
{
    u32             u32Time;									/*!< bit31~bit0 of TIME */
    u32             u32Time33;									/*!< bit32 of TIME */
} ST_DRV_ADEC_STC_Time, *PST_DRV_ADEC_STC_Time;

/*!
 * \brief
 * Defines the supported and unsupported features of a particular mixer object.
 */
typedef struct
{
	u8 u8NumberOfInputs;										/*!< Number of inputs that can be connected to this mixer. */
} ST_DRV_ADEC_MixerCapability;

/*!
 * \brief
 * Structure containing information pertaining to a particular audio stream.
 */
typedef struct
{
	EN_DRV_ADEC_StreamContent enStreamContent;					/*!< Type of audio stream being decoded. */
	u32 u32BitRate;												/*!< Input bit rate in Kbits per second of the audio stream.*/
	u32 u32SamplingFrequency;									/*!< Sampling frequency in Hertz of the audio stream. */
	EN_DRV_ADEC_MPEG_Layer enLayerNumber;						/*!< Defines the layer id of incoming streams(MPEG) in terms of EN_DRV_ADEC_MPEG_Layer */
	bool b8Emphasis;											/*!< State of deemphasis filter */
	bool b8CopyRight;											/*!< Copyright status of the stream (not valid for the current release */
	u8 u8Mode;													/*!< Indicates the stereo mode in MPEG stream */
	u8 u8Bit_Rate_Code;											/*!< Indicates the BitrateCode in AC3 stream */
	u8 u8Bit_Stream_Mode;										/*!< Indicates the type of service that the bitstream conveys in AC3 */
	u8 u8Audio_Coding_Mode;										/*!< Indicates which of the main service channels are in use, ranging from 3/2 to 1/0 in AC3 */
} ST_DRV_ADEC_StreamInfo;

/*!
 * \brief
 * Structure defining the PCM input parameters.
 */
typedef struct
{
	u32 u32Frequency;											/*!< Playback Frequency fo the input PCM Stream. */
	u32 u32DataPrecision;										/*!< Number of bits per audio sample. */
	u8 u8NumChannels;											/*!< Number of channels of input PCM Stream. */
} ST_DRV_ADEC_PCMInputParams;

/*!
 * \brief
 * Type defining a PCM buffer that contains PCM data.
 */
typedef struct
{
	u32 u32Block;												/*!< A/V Memory block handle associated with allocated memory block. */
	u32 u32StartOffset;											/*!< Number of bytes offset into memory block where PCM buffer begins. */
	u32 u32Length;												/*!< Length in bytes of PCM buffer. */
} ST_DRV_ADEC_PCMBuffer;

/*!
 * \brief
 * Defines the supported and unsupported features of a particular input object.
 */
typedef struct
{
	bool b8PESParserCapable;									/*!< TRUE: This input object has a PES parser. FALSE: No PES parser on this object */
	bool b8I2SInputCapable;									/*!< TRUE: This input can be configured to receive data over an I2S input. FALSE: No I2S input on this object */
	bool b8PCMBufferPlayback;									/*!< TRUE: This object is able to play PCM samples from memory. FALSE: No PCM playback from memory. */
	u32   u32ESBufferMinRequire;								/*!< ES buffer min required */
	u32   u32ESBuffAlign;										/*!< ES buffer align limitation */
} ST_DRV_ADEC_IntCapability;

/*!
 * \brief
 *Defines the supported and unsupported features of a particular decoder object.
 */
typedef struct
{
	bool b8DynamicRangeCapable;																/*!< TRUE: coder supports dynamic range control setting. FALSE: no dynamic range control support */
	bool b8FadingCapable;																	/*!< TRUE: decoder supports audio fading for pause and stop. FALSE: no fading support */
	bool b8RunTimeSwitch;																	/*!< Run Time decoder switch is supoorted or not. */
	bool b8DeEmphasisCapable;																/*!< DeEmphasis capable or not */
	bool b8PrologicDecodingCapable;															/*!< Prologic enabled or not */
	EN_DRV_ADEC_SampleFrequency enSupportedPCMSamplingFreqs[EN_DRV_ADEC_SAMPLE_FREQ_NUMBER];/*!< List of supported sampling frequency for PCM decoding.*/
	s32 s32SupportedTrickSpeeds[MAX_DRV_ADEC_TRICK_SPEEDS];									/*!< List of supported trick mode speeds */
	EN_DRV_ADEC_Stop enSupportedStopModes;													/*!< Supported stop modes */
	u32 u32SupportedStreamContents;									                        /*!< Supported stream contents */
	EN_DRV_ADEC_StreamType enSupportedStreamTypes;											/*!< Supported stream types */
	EN_DRV_ADEC_Effect enSupportedEffects;													/*!< Supported Effects */
	EN_DRV_ADEC_StereoMode enSupportedStereoModes;											/*!< Supported Effects */

	u32 u32DecodeBufferMinRequire;															/*!< Decode buffer min required */
	u32	u32DecodeBuffAlign;																	/*!< Decode buffer align limitation */

} ST_DRV_ADEC_DecCapability;

/*!
 * \brief
 * Defines the supported and unsupported features of a particular post processor object.
 */
typedef struct
{
	bool b8DownsamplingCapable;									/*!< Downsampling Capable */
	bool b8ChannelAttenuationCapable;								/*!< Channel Attenuation Capable */
	bool b8DelayCapable;											/*!< Delay Capable */
	bool b8MultiChannelOutputCapable;								/*!< Multi Channel Outpu tCapable */
	u16 u16MaxVolume;												/*!< Max Volume */
	u16 u16MaxDelay;												/*!< MaxDelay */
} ST_DRV_ADEC_PPCapability;

/*!
 * \brief
 * Defines the supported and unsupported features of a particular output object.
 */
typedef struct
{
	bool b8ChannelMuteCapable;					/*!< Channel Mute Capable */
	s32 s32MaxSyncOffset;						/*!< Max sync offset */
	s32 s32MinSyncOffset;						/*!< Min Sync Offset */

	u32	u32PCMBufferMinRequire;					/*!< PCM buffer min required */
	u32	u32PCMBuffAlign;						/*!< PCM buffer align limitation */
	u32	u32SPDIFBufferMinRequire;				/*!< SPDIF buffer min required */
	u32	u32SPDIFBuffAlign;						/*!< SPDIF buffer align limitation */
	u32	u32BypassBufferMinRequire;				/*!< BYPASS buffer min required */
	u32	u32BypassBuffAlign;						/*!< BYPASS buffer align limitation */
} ST_DRV_ADEC_OupCapability;

/*!
 * \brief
 * Defines the supported features of a particular encoder object.
 */
typedef struct
{
	EN_DRV_ADEC_StreamContent enSupportedStreamContents;		/*!< Supported stream contents */
	EN_DRV_ADEC_StreamType enSupportedStreamTypes;				/*!< Supported stream types */

	u32	u32EncodeBufferMinRequire;								/*!< Encode buffer min required */
	u32	u32EncodeBuffAlign;										/*!< Encode buffer align limitation */
} ST_DRV_ADEC_EncCapability;

/*!
 * \brief
 * Structure defining the parameters for configuring the S/PDIF output interface.
 */
typedef struct
{
	u16 u16NumChannels;								/*!< The number of output channels generated. */
	bool b8I2SInputCapable;						/*!< TRUE: This input can be configured to receive data over an I2S input. FALSE: No I2S input on this object */
} ST_DRV_ADEC_ReaderCapability;

/*!
 * \brief
 * Defines the supported and unsupported features of a given implementation of this driver.
 */
typedef struct
{
	/* Module level Capabilities */
	ST_DRV_ADEC_IntCapability stIntCapability;										/*!< Input Capability */
	ST_DRV_ADEC_DecCapability stDecCapability;										/*!< Decoder Capability */
	ST_DRV_ADEC_MixerCapability stMixerCapability;									/*!< Mixer Capability */
	ST_DRV_ADEC_PPCapability stPostProcCapability;									/*!< PostProcessor Capability */
	ST_DRV_ADEC_OupCapability stOupCapability;										/*!< Output Capability */
	ST_DRV_ADEC_EncCapability stEncCapability;										/*!< Encoder Capability */
	ST_DRV_ADEC_ReaderCapability stReaderCapability;								/*!< PCM Reader capability */

	u8 u8NumberOfInputObjects;													/*!< Number of elements in the InputObjects array. */
	u8 u8NumberOfDecoderObjects;												/*!< Number of elements in the DecoderObjects array. */
	u8 u8NumberOfPostProcObjects;												/*!< Number of elements in the PostProcObjects array. */
	u8 u8NumberOfMixerObjects;													/*!< Number of elements in the MixerObjects array. */
	u8 u8NumberOfOutputObjects;													/*!< Number of elements in the OutputObjects array. */
	u8 u8NumberOfEncoderObjects;												/*!< Number of elements in the EncoderObjects array. */

	EN_DRV_ADEC_Object InputObjects[MAX_DRV_ADEC_INPUT_OBJECTS];				/*!< Array of supported audio input interface objects. */
	EN_DRV_ADEC_Object DecoderObjects[MAX_DRV_ADEC_DECODER_OBJECTS];			/*!< Array of supported audio decoder objects. */
	EN_DRV_ADEC_Object PostProcObjects[MAX_DRV_ADEC_POST_PROC_OBJECTS];			/*!< Array of the supported post processor objects. */
	EN_DRV_ADEC_Object MixerObjects[MAX_DRV_ADEC_MIXER_OBJECTS];				/*!< Array of the supported mixer objects. */
	EN_DRV_ADEC_Object OutputObjects[MAX_DRV_ADEC_OUTPUT_OBJECTS];				/*!< Array of the supported output interface objects. */
	EN_DRV_ADEC_Object EncoderObjects[MAX_DRV_ADEC_ENCODER_OBJECTS];			/*!< Array of the supported Encoder interface objects */
} ST_DRV_ADEC_Capability;

/*!
 * \brief
 * Defines the parameters required to open a handle to an audio decoder.
 */
typedef struct
{
	u32 u32EvtHandle;							/*!< Event handle */
	u32 u32SyncDelay;							/*!< Delay to introduce into the synchronization process which will be added to the audio PTS */
	u32 u32InputBufferAddr;						/*!< Input Buffer Address */
	u32 u32InputBufferSize;						/*!< Input Buffer Size */
	u32 u32Input2BufferAddr;						/*!< Input Buffer Address */
	u32 u32Input2BufferSize;						/*!< Input Buffer Size */
	u32	u32DecodeBufferAddr;					/*!< Decode Buffer Address */
	u32	u32DecodeBufferSize;					/*!< Decode Buffer Size */
	u32	u32PCMBufferAddr;						/*!< PCM Buffer Address */
	u32	u32PCMBufferSize;						/*!< PCM Buffer Size */
	u32	u32SPDIFBufferAddr;						/*!< SPDIF Buffer Address */
	u32	u32SPDIFBufferSize;						/*!< SPDIF Buffer Size */
	u32	u32BypassBufferAddr;
	u32	u32BypassBufferSize;	
	u32	u32EncodeBufferAddr;					/*!< Encode Buffer Address */
	u32	u32EncodeBufferSize;					/*!< Encode Buffer Size */
	u32 u32STCHandle;							/*!< STC handle */
	bool b8PostEnable;							/*!< Post enable */
	bool b8PerformanceIssue;					/*!< Performance Issue enable */
	EN_DRV_ADEC_DEC_SOURCE enDecSource;         /*!< Decode Source */
} ST_DRV_ADEC_OpenParams;

/*!
 * \brief
 * Structure defining the parameters for configuring the PCM data transfers.
 */
typedef struct
{
	bool b8InvertWordClock;															/*!< Invert Word Clock or not */
	EN_DRV_ADEC_DACDataFormat enDataFormat;												/*!< PCM output format */
	EN_DRV_ADEC_DACDataPrecision enPrecision;											/*!< Bit precisions for PCM output formatting */
	bool b8LSBFirst;																	/*!< LSB firse or MSB first */
	EN_DRV_ADEC_PlayerFrequencyMultiplier enPcmPlayerFrequencyMultiplier;				/*!< Player Frequency Multiplier, 384 Fs, 256 Fs etc... */
//	bool b8MemoryStorageFormat16; // Data given to PCM player is in 16/16 format
} ST_DRV_ADEC_PCMDataConf;

/*!
 * \brief
 * Structure defining the parameters for configuring the S/PDIF output interface.
 */
typedef struct
{
	//bool b8AutoLatency; //not support
	//u16 u16Latency; //not support
	EN_DRV_ADEC_CopyRightMode enCopyPermitted;											/*!< Specifies whether or not copying is permitted from the S/PDIF output */
	bool b8AutoCategoryCode;															/*!< Specifies whether or not to automatically configure the S/PDIF output Categorycode header information */
	//u8 u8CategoryCode;
	//bool b8AutoDTDI;
	//u8 u8DTDI;
	EN_DRV_ADEC_SPDIFDataPrecision enSPDIFDataPrecision;								/*!< Bit precisions for SPDIF output formatting */
	EN_DRV_ADEC_PlayerFrequencyMultiplier enSPDIFPlayerFrequencyMultiplier;				/*!< Player Frequency Multiplier, 384 Fs, 256 Fs etc... */
} ST_DRV_ADEC_SPDIFOutParams;

/*!
 * \brief
 * Structure defining the parameters for configuring the PCM reaser data transfers.
 */
typedef struct
{
	bool b8LSBFirst;										/*!< TRUE: PCM data arrives MSB first. FALSE:PCM data arrives LSB first. */
	EN_DRV_ADEC_DACDataPrecision enPrecision;				/*!< Specifies the precision of the PCM data */
	EN_DRV_ADEC_DACNumBitsSubframe enBitsPerSubFrame;		/*!< Specifies the number of bits per subframe //32/16 bits per subframe */
	u32 u32Frequency;
} ST_DRV_ADEC_PCMReaderConf;

/*!
 * \brief
 * Structure defining the parameters required to start an audio decoder.
 */
typedef struct
{
	EN_DRV_ADEC_StreamContent enStreamContent;				/*!< Specifies the expected input stream content. */
	EN_DRV_ADEC_StreamType enStreamType;					/*!< Specifies the expected stream type carrying the audio. */
	EN_DRV_ADEC_SampleFrequency enSamplingFrequency;		/*!< Specifies the required sampling frequency */
	u8 u8StreamID;											/*!< Specifies a stream identifier to filter on. */
} ST_DRV_ADEC_StreamParams;

/*!
 * \brief
 * Structure defining the parameters required to stop an audio decoder.
 */
typedef struct
{
	EN_DRV_ADEC_Stop enStopMode;						/*Parameters for ways of stopping the decoder.*/
} ST_DRV_ADEC_StopParams;

typedef struct
{
    bool b8Enable;          //(IN)
    u8  u8BandNum;              //(IN) Number of spectrum band. ( 32 >= u8BandNum > 0 )
    u8  au8BandWidth[32];       //(IN) Set band interval from au8BandWidth[0] to au8BandWidth[u8BandNum-1],
                                // au8BandWidth[0] +..+ au8BandWidth[u8BandNum-1] should be 256.
    u8  u8LineLevel;            //(IN) Level of spectrum line. ( 32 >= u8LineLevel > 0 )
    u32 au32LineLevelGrid[31];  //(IN) Set line level interval from au32LineLevelGrid[0] to au32LineLevelGrid[u8LineLevel-2],
                                // 0 < au32LineLevelGrid[0] <..< au32LineLevelGrid[u8BandNum-2] < 2^31-1
    u8  au8BarOutput[32];       //(Out) returned Bar output, u8LineLevel>= au8BarOutput >=0;

} ST_DRV_ADEC_SPECTRUM, *PST_DRV_ADEC_SPECTRUM;

/*!
 * \brief
 * Defines the parameters required to initialize.
 */
typedef struct
{
	os_mempool_handle	u32MemPoolHandle;				/*!< A memory pool handle for Audio module	*/
	EN_DRV_ADEC_Device 	enDeviceType;					/*!< Audio cell architecture type.	*/
	ST_DRV_ADEC_PCMDataConf stPCMOutParams;				/*!< Parameters for configuring PCM output stages. */
	ST_DRV_ADEC_SPDIFOutParams stSPDIFOutParams;		/*!< Parameters for configuring SPDIF output stages. */
	EN_DRV_ADEC_DigitalMode enSPDIFMode;				/*!< Parameters for configuring SPDIF mode stages. */
	ST_DRV_ADEC_PCMReaderConf stPCMReaderMode;			/*!< Parameters for configuring SPDIF mode stages. */
//	ST_GPIO_Open stGPIOParams;							/*!< Parameters for configuring GPIO. */
	ST_DRV_ADEC_SPECTRUM stSpectrum;
	u8 u8DriverIndex;
	u8 u8NumChannels;
} ST_DRV_ADEC_InitParams;
/*!
 * \brief
 * Structure defining the parameters for buffer info.
 */

typedef struct
{
	void* pBufferBaseAddr;							/*!< Buffer base address. */
	u32 u32BufferSize;								/*!< Buffer size. */
} ST_DRV_ADEC_BufferParams;

/*!
 * \brief
 * Union defining the parameters for configuring the device¡¦s output parameters.
 */
typedef union
{
	ST_DRV_ADEC_PCMDataConf stPCMOutParams;			/*!< PCM data parameters */
	ST_DRV_ADEC_SPDIFOutParams stSPDIFOutParams;	/*!< SPDIF output parameters */
} ST_DRV_ADEC_OutputParams;

/*!
 * \brief
 * Synchronization unit for skip and pause functions.
 */
typedef struct
{
	u32 u32SkipPrecision;						/*!< Defines the granularity in ms of the */
	u32 u32PausePrecision;						/*!< Defines the granularity in ms of the DRV_ADEC_DecPauseSynchro() API for the current decoded stream */
} ST_DRV_ADEC_SynchroUnit;

/*!
 * \brief
 * Structure defining dynamic range control settings.
 */
typedef struct
{
	u8 u8CutFactor;								/*!< Scaling factor applied to high range.	0~100*/
	u8 u8BoostFactor;							/*!< Scaling factor applied to low range.	0~100*/
} ST_DRV_ADEC_DynamicRange;

/*!
 * \brief
 * Structure defining the volume attenuation for each output channel.
 */
typedef struct
{
	u16 u16Left;								/*!< Attenuation (in dB) to be applied to the front left channel	*/
	u16 u16Right;								/*!< Attenuation (in dB) to be applied to the front right channel	*/
	u16 u16LeftSurround;						/*!< Attenuation (in dB) to be applied to the front left surround channel	*/
	u16 u16RightSurround;						/*!< Attenuation (in dB) to be applied to the front right surround channel	*/
	u16 u16Center;								/*!< Attenuation (in dB) to be applied to the front center channel	*/
	u16 u16Subwoofer;							/*!< Attenuation (in dB) to be applied to the front subwoofer channel	*/
	u16 u16CsLeft;								/*!< Attenuation (in dB) to be applied to the front Center Surround left channel	*/
	u16 u16CsRight;								/*!< Attenuation (in dB) to be applied to the front Center Surround Right channel	*/
	u16 u16LeftMix;								/*!< Attenuation (in dB) to be applied to the front aux left channel	*/
	u16 u16RightMix;							/*!< Attenuation (in dB) to be applied to the front aux right channel	*/
} ST_DRV_ADEC_Volume;

/*!
 * \brief
 * Structure defining the delay for each output channel.
 */
typedef struct
{
	u16 u16Left;								/*!< Delay (in ms) to be applied to the front left channel. */
	u16 u16Right;								/*!< Delay (in ms) to be applied to the front right channel. */
	u16 u16LeftSurround;						/*!< Delay (in ms) to be applied to the center channel.	*/
	u16 u16RightSurround;						/*!< Delay (in ms) to be applied to the left surround channel.	*/
	u16 u16Center;								/*!< Delay (in ms) to be applied to the right surround channel.	*/
	u16 u16Subwoofer;							/*!< Delay (in ms) to be applied to the subwoofer channel. */
	u16 u16CsLeft;								/*!< Delay (in ms) to be applied to the Center Surround left channel. */
	u16 u16CsRight;								/*!< Delay (in ms) to be applied to the Center Surround Right channel.	*/
	u16 u16LeftMix;								/*!< Delay (in ms) to be applied to the aux left channel. */
	u16 u16RightMix;							/*!< Delay (in ms) to be applied to the aux right channel.	*/
} ST_DRV_ADEC_Delay;

/*!
 * \brief
 * Structure defining the speaker types in the listening room configuration.
 */
typedef struct
{
	EN_DRV_ADEC_SpeakerType enFront;					/*!< Front speakers configuration					*/
	EN_DRV_ADEC_SpeakerType enCenter;					/*!< Center speaker configuration					*/
	EN_DRV_ADEC_SpeakerType enLeftSurround;				/*!< Left surround speaker configuration			*/
	EN_DRV_ADEC_SpeakerType enRightSurround;			/*!< Right surround speaker configuration			*/
	EN_DRV_ADEC_SpeakerType enCsLeft;					/*!< Center surround left speaker configuration		*/
	EN_DRV_ADEC_SpeakerType enCsRight;					/*!< Center surround right speaker configuration	*/
} ST_DRV_ADEC_SpeakerConfiguration;

/*!
 * \brief
 * Defines output parameters of a particular audio encoder object. These parameters can't be changed after decoder is started.
 */
typedef struct
{
	bool b8AutoOutputParam;							/*!< Auto select output sampling frequency and Bitrate.	*/
	u32 u32BitRate;										/*!< Output bitrate of audio encoder (in Kbps) */
	u32 u32OutputFrequency;								/*!< Output sampling frequency of audio encoder (in Hz) */

	union
	{
		struct
		{
			bool b8CompOn;								/*!< Boolean for enable/disable Compresseion (Only for DD) */
			bool b8CompOnSec;							/*!< Boolean for enable/disable secondary Compresseion (Only for DD) */
		} DDConfig;

		struct
		{
			u32 u32BandWidth;							/*!< Front speakers configuration */
			bool b8Intensity;							/*!< Boolean for enable/disable intensity stereo (0 means disable) */
			bool b8VbrMode;							/*!< Boolean for enable/disable variable bitrate encoding */
			u32 u32VbrQuality;							/*!< Percentage of VBR quality (0-> 100). */
			bool b8FullHuffman;						/*!< Front speakers configuration */
			bool b8PaddingMode;						/*!< Should always be set to 0 */
			bool b8Crc;								/*!< Flag for enabling CRC check. 0 CRC bit is not inserted, 1 CRC bit is inserted. */
			bool b8PrivateBit;							/*!< Boolean for enable/disable the field privateBit in header. */
			bool b8CopyRightBit;						/*!< Boolean for enable/disable copyRightBit in header. */
			bool b8OriginalCopyBit;					/*!< */
			bool b8EmphasisFlag;						/*!< Boolean for enable/disable emphasis. */
			bool b8Downmix;							/*!< Boolean for enable/disable downmix. 0 means no downmix. */
		} MP3Config;

		struct
		{
			EN_DRV_ADEC_Mp2EncStereoMode enMode;		/*!< Variable used to set stereo Mode. */
			bool b8CrcOn;								/*!< Boolean for enable/disable CRC. */
			EN_DRV_ADEC_MP2EncEmphasis enEmphasis;		/*!< Variable used to Emphasis. */
			bool b8Copyrighted;						/*!< Boolean for enable/disable field in header. */
			bool b8Original;							/*!< Boolean for enable/disable field in header. */
		} MP2Config;
	} EncoderStreamSpecificParams;
} ST_DRV_ADEC_ENCOutputParams;

/*!
 * \brief
 * Structure defining the parameters for configuring the Equalizer.
 */
typedef struct
{
	bool b8Enable;						/*!< Equalizer enable/disable. */
	EN_DRV_ADEC_EQ enEQType;			/*!< Equalizer type. */
} ST_DRV_ADEC_EQ;

/*!
 * \brief
 * Structure defining the parameters for configuring the AVL.
 */
typedef struct
{
	bool b8Enable;						/*!< AVL enable/disable. */
	s32 s32SilenceLevel;
	s32 s32GainDownLevel;
	s32 s32TargetThreshold;
	s32 s32GainUpLevel;
} ST_DRV_ADEC_AVL;

/***************************************************************************
 * API
 * ************************************************************************/

/*****************
//Common Functions
*****************/
ErrorCode DRV_ADEC_Init(DRV_DeviceNameType DeviceName, ST_DRV_ADEC_InitParams *pstInitParams);
/*!\fn ErrorCode DRV_ADEC_Init(DRV_DeviceNameType DeviceName, ST_DRV_ADEC_InitParams *pstInitParams)
 * \brief
 *        Initialize the ADEC device with pstInitParams setting.
 *
 * \param	DeviceName						(Input) Name of the Audio device to initialize.
 * \param	pstInitParams					(Input) Pointer to the initialization parameter structure.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_INITIALISED				A previous Init call has not been terminated or or already initialized.
 * \retval	ERROR_NO_MEMORY					The memory allocate is fail.
 */

ErrorCode DRV_ADEC_Term(DRV_DeviceNameType DeviceName);
/*!\fn ErrorCode DRV_ADEC_Term(DRV_DeviceNameType DeviceName)
 * \brief
 *        Terminate the ADEC device driver.
 *
 * \param	DeviceName						(Input) Name of an initialized audio device.
  *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid.
 * \retval	ERROR_INITIALISED				A previous Init call has not been terminated or or already initialized.
 */

ErrorCode DRV_ADEC_Open(DRV_DeviceNameType DeviceName, ST_DRV_ADEC_OpenParams *pstOpenParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_ADEC_Open(DRV_DeviceNameType DeviceName, ST_DRV_ADEC_OpenParams *pstOpenParams, u32* pu32Handle)
 * \brief
 *        Open the ADEC device and associate it with a handle.
 *
 * \param	DeviceName						(Input) ADEC device name to open.
 * \param	pstOpenParams					(Input) Pointer to the opening parameter structure.
 * \param	pu32Handle						(Output) The returned handle of the opened device driver.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_INITIALISED				A previous Init call has not been terminated or or already initialized.
 */

ErrorCode DRV_ADEC_Close(u32 u32Handle);
/*!\fn ErrorCode DRV_ADEC_Close(u32 u32Handle)
 * \brief
 *        Close an opend device associated with a handle.
 *
 * \param	u32Handle						(Input) An open handle number of the audio device.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid.
 */

ErrorCode DRV_ADEC_GetCapability(DRV_DeviceNameType DeviceName, ST_DRV_ADEC_Capability *pstCapability);
/*!\fn ErrorCode DRV_ADEC_GetCapability(DRV_DeviceNameType DeviceName, ST_DRV_ADEC_Capability *pstCapability)
 * \brief
 *        Get the capabilities of the named audio.
 *
 * \param 	DeviceName						(Input) Name of the initialized audio decoder to obtain the capabilities of.
 * \param	pstCapability					(OutPut) Pointer to the returned capabilities.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid.
 */

ErrorCode DRV_ADEC_ResetBuffer(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject);
/*!\fn ErrorCode DRV_ADEC_ResetBuffer(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject)
 * \brief
 *        Stops the driver.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject					(Input) References a specific input interface.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid.
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid.
 */


ErrorCode DRV_ADEC_GetVersion(u8** ppu8VersionNum);
/*!\fn ErrorCode DRV_ADEC_GetVersion(u8** ppu8VersionNum)
 * \brief
 *        Get the Audio Driver's Version number string
 *
 * \param 	ppu8VersionNum    				(Output) Version Number string
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid.
 */

/*****************
//Input Functions
*****************/
ErrorCode DRV_ADEC_IntGetCapability(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, ST_DRV_ADEC_IntCapability* pstCapability);
/*!\fn ErrorCode DRV_ADEC_IntGetCapability(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, ST_DRV_ADEC_IntCapability* pstCapability)
 * \brief
 *        Gets the capabilities of the specified input object.
 *
 * \param 	u32Handle	    				(Input) An open handle number of the audio device.
 * \param 	enInputObject    				(Input) References a specific input interface.
 * \param 	pstCapability					(Output) Pointer to returned capabilities.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success.
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid.
 */

ErrorCode DRV_ADEC_IntGetSamplingFrequency(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, u32* pu32SamplingFrequency);
/*!\fn ErrorCode DRV_ADEC_IntGetSamplingFrequency(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, u32* pu32SamplingFrequency)
 * \brief
 *       Retrieves the sampling frequency of the input data stream.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enInputObject					(Input) References a specific input interface.
 * \param 	pu32SamplingFrequency			(Output) Stores the result of the current sampling frequency.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

//TODO funtion not implement, return ERROR_NO_ERROR
ErrorCode DRV_ADEC_IntGetStreamInfo(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, ST_DRV_ADEC_StreamInfo* pstStreamInfo);
/*!\fn ErrorCode DRV_ADEC_IntGetStreamInfo(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, ST_DRV_ADEC_StreamInfo* pstStreamInfo)
 * \brief
 *        Returns information pertaining to the audio stream currently being decoded.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enInputObject					(Input) References a specific input interface.
 * \param 	pstStreamInfo					(Output) Pointer to a structure used for returning audio stream information.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 */

ErrorCode DRV_ADEC_IntGetBufferParams(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, ST_DRV_ADEC_BufferParams* pDataParams);
/*!\fn ErrorCode DRV_ADEC_IntGetBufferParams(u32 u32Handle, EN_DRV_ADEC_Object enInputObject, ST_DRV_ADEC_BufferParams* pDataParams)
 * \brief
 *        Get the PES/ES Buffer parameters , stard address and size.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enInputObject					(Input) References a specific input interface.
 * \param 	pDataParams						(Output) PES/ES Buffer configuration.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 */
ErrorCode DRV_ADEC_IntGetAudioPTS(const u32 u32Handle, u32* pu32PTS,u32* pu32PTS33);
/*!\fn ErrorCode DRV_ADEC_IntGetAudioPTS(const u32 u32Handle, u32* pu32PTS,u32* pu32PTS33);
 * \brief
 *        GetAudioPTS
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	pu32PTS							(Input) PTS value.
 * \param 	pu32PTS33						(Input) PTS bit32 value.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
ErrorCode DRV_ADEC_IntUpdatePTS(const u32 u32Handle, PST_DRV_ADEC_PTS pstAudioPTS);
/*!\fn ErrorCode DRV_ADEC_IntUpdatePTS(const u32 u32Handle, PST_DRV_ADEC_PTS pstAudioPTS)
 * \brief
 *        Update PTS
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	pstAudioPTS						(Input) PTS value.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_IntInformWriteAddress(const u32 u32Handle, u32 u32WriteAddress);
/*!\fn ErrorCode DRV_ADEC_IntInformWriteAddress(const u32 u32Handle, u32 u32WriteAddress)
 * \brief
 *        Update current write address.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	u32WriteAddress					(Input) Current write address.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid.
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_IntGetReadAddress(const u32 u32Handle, u32* pu32ReadAddress);
/*!\fn ErrorCode DRV_ADEC_IntGetReadAddress(const u32 u32Handle, u32* pu32ReadAddress)
 * \brief
 *        Get UPK current read address.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	pu32ReadAddress    				(Output) UPK current read address.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid.
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

/*****************
//Output Functions
*****************/
ErrorCode DRV_ADEC_OupMute(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject);
/*!\fn ErrorCode DRV_ADEC_OupMute(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject)
 * \brief
 *        The output device is muted.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_OupUnMute(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject);
/*!\fn ErrorCode DRV_ADEC_OupUnMute(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject)
 * \brief
 *        The output device is un-muted.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_OupGetParams(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, ST_DRV_ADEC_OutputParams* pstParams);
/*!\fn ErrorCode DRV_ADEC_OupGetParams(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, ST_DRV_ADEC_OutputParams* pstParams)
 * \brief
 *        Obtains the current output configuration parameters.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 * \param 	pstParams						(Output) Stores result of current output configuration parameters.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_OupEnableSynchronization(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject);
/*!\fn ErrorCode DRV_ADEC_OupEnableSynchronization(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject)
 * \brief
 *        Enables audio synchronization with the local system clock.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_OupDisableSynchronization(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject);
/*!\fn ErrorCode DRV_ADEC_OupEnableSynchronization(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject)
 * \brief
 *        Obtains the current output configuration parameters.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_OupSetSyncMode(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, u32 u32AvMaster);
/*!\fn ErrorCode DRV_ADEC_OupSetSyncMode(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, u32 u32AvMaster);
 * \brief
 *        Sets the sync mode for the output object given by OutputObject.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 * \param 	u32AvMaster    				    (Input) sync mode to be configured.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_SetSPDIFCopyProtection(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, EN_DRV_AOUT_SPDIF_CP_TYPE enCopyRightMode);

ErrorCode DRV_ADEC_OupSetDigitalMode(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, EN_DRV_ADEC_DigitalMode enOutputMode);
/*!\fn ErrorCode DRV_ADEC_OupSetDigitalMode(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, EN_DRV_ADEC_DigitalMode enOutputMode)
 * \brief
 *        Sets the SPDIF output mode for the output object given by OutputObject.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 * \param 	enOutputMode    				(Input) SPDIF output mode to be configured.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
ErrorCode DRV_ADEC_OupSetHDMIPath(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, EN_DRV_ADEC_HDMI_OUT_PATH enOutputPath);
ErrorCode DRV_ADEC_OutSetEncodeType(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, EN_DRV_ADEC_Encode_Type enEncodeType);
ErrorCode DRV_ADEC_OupGetDigitalMode(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, EN_DRV_ADEC_DigitalMode* penOutputMode);
/*!\fn ErrorCode DRV_ADEC_OupGetDigitalMode(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject, EN_DRV_ADEC_DigitalMode* penOutputMode)
 * \brief
 *        Gets the SPDIF output mode for the output object given by OutputObject.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 * \param 	penOutputMode    				(Output) SPDIF output mode to be configured.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
ErrorCode DRV_ADEC_OupCtrlDAC(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject,bool b8Enable);
/*!\fn ErrorCode DRV_ADEC_OupCtrlDAC(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject,bool b8Enable)
 * \brief
 *        Control the DAC output for the output object given by OutputObject.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enOutputObject    				(Input) References a specific output interface.
 * \param 	b8Enable    				    (Input) Enable/Disable audio DAC.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
/*****************
//Decoder Functions
*****************/
ErrorCode DRV_ADEC_DecStart(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_StreamParams* pstStreamParams);
/*!\fn ErrorCode DRV_ADEC_DecStart(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_StreamParams* pstStreamParams)
 * \brief
 *        Starts the audio decoder or resumes decoding from the prepared state.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject   				(Input) References a specific audio decoder.
 * \param 	pstStreamParams   				(Input) Parameters describing the stream to be decoded.
 *
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecStop(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_StopParams* pstStopParams);
/*!\fn ErrorCode DRV_ADEC_DecStop(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_StopParams* pstStopParams)
 * \brief
 *        Stops the audio decoder.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param	pstStopParams					(Input) Parameters describing to be stop decoding.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecPause(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject);
/*!\fn ErrorCode DRV_ADEC_DecPause(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject)
 * \brief
 *        Pauses the audio decoder.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecStep(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32 skip_video_frame_time);
/*!\fn ErrorCode DRV_ADEC_DecStep(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32 skip_video_frame_time)
 * \brief
 *        Skip some audio frame.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	skip_video_frame_time    		(Input) skip frame time.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecResume(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject);
/*!\fn ErrorCode DRV_ADEC_DecResume(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject)
 * \brief
 *       Resumes the decoder from the paused state.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

//TODO funtion not implement, return ERROR_NOT_SUPPORTED
ErrorCode DRV_ADEC_DecSetDynamicRangeControl(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_DynamicRange* pstDynamicRange);
/*!\fn ErrorCode DRV_ADEC_DecSetDynamicRangeControl(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_DynamicRange* pstDynamicRange)
 * \brief
 *      Sets the dynamic range control of AC3.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pstDynamicRange					(Input) Specifies the dynamic range control settings.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NOT_SUPPORTED				The function is not supported
 */

ErrorCode DRV_ADEC_DecSetSpeed(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, s32 s32Speed);
/*!\fn ErrorCode DRV_ADEC_DecSetSpeed(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, s32 s32Speed)
 * \brief
 *      Sets the decode speed and direction.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	s32Speed						(Input) Signed value representing speed and direction of decoding.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecGetSpeed(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, s32* ps32Speed);
/*!\fn ErrorCode DRV_ADEC_DecGetSpeed(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, s32* ps32Speed)
 * \brief
 *      Gets the current decode speed and direction.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	ps32Speed						(Output) Type of Effect Required (Focus, gain, HeadPhone, Speaker etc etc.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecSetLastFrame(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject);
/*!\fn ErrorCode DRV_ADEC_DecSetLastFrame(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject)
 * \brief
 *      Set decode last frame flag.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
//TODO funtion not implement, return ERROR_NOT_SUPPORTED
ErrorCode DRV_ADEC_DecSetCompressionMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_CompressionMode enCompressionMode);
/*!\fn ErrorCode DRV_ADEC_DecSetCompressionMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_CompressionMode enCompressionMode)
 * \brief
 *      Set compression Mode in case of AC3 decoding.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	enCompressionMode				(Input) Compression Mode to set.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NOT_SUPPORTED				The function is not supported
 */

ErrorCode DRV_ADEC_DecGetCompressionMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_CompressionMode* penCompressionMode);
/*!\fn ErrorCode DRV_ADEC_DecGetCompressionMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_CompressionMode* penCompressionMode)
 * \brief
 *      Get compression Mode in case of AC3 decoding.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	penCompressionMode				(OupPut) Pointer to returned Compression setting.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NOT_SUPPORTED				The function is not supported
 */

ErrorCode DRV_ADEC_DecSetLFEMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_LFEMODE enLFEMode);
/*!\fn ErrorCode DRV_ADEC_DecSetLFEMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_LFEMODE enLFEMode)
 * \brief
 *      Set LFE Mode.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	enLFEMode						(Input) LFE Mode to set.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecGetLFEMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_LFEMODE* penLFEMode);
/*!\fn ErrorCode DRV_ADEC_DecGetCompressionMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_CompressionMode* penCompressionMode)
 * \brief
 *      Get LFE Mode.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	penLFEMode						(OupPut) Pointer to returned LFE setting.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecGetCapability(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_DecCapability* pstCapability);
/*!\fn ErrorCode DRV_ADEC_DecGetCapability(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_DecCapability* pstCapability)
 * \brief
 *      Gets the capabilities of the specified audio decoder object.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pstCapability					(Output) Pointer to returned capabilities.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

//TODO funtion not implement, return ERROR_NO_ERROR
ErrorCode DRV_ADEC_DecGetDynamicRangeControl(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_DynamicRange* pstDynamicRange);
/*!\fn ErrorCode DRV_ADEC_DecGetDynamicRangeControl(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, ST_DRV_ADEC_DynamicRange* pstDynamicRange)
 * \brief
 *      Retrieves the current dynamic range control settings.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pstDynamicRange					(Output) Stores the result of the current dynamic range control settings.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 */

ErrorCode DRV_ADEC_DecSetDownMixMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_DownMixMode enDownMixMode);
/*!\fn ErrorCode DRV_ADEC_DecSetDownMixMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_DownMixMode enDownMixMode)
 * \brief
 *      Set DownMix Mode in case of AC3 decoding.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	enDownMixMode					(Input) DownMix to set.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NOT_SUPPORTED				The function is not supported
 */

ErrorCode DRV_ADEC_DecGetDownMixMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_DownMixMode* penDownMixMode);
/*!\fn ErrorCode DRV_ADEC_DecSetDownMixMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_DownMixMode enDownMixMode)
 * \brief
 *      Get DownMix Mode in case of AC3 decoding.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	penDownMixMode					(Output) Pointer to returned the DownMix configuration.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NOT_SUPPORTED				The function is not supported
 */

ErrorCode DRV_ADEC_DecGetFrameCnt(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32FC);
/*!\fn ErrorCode DRV_ADEC_DecGetFrameCnt(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32FC)
 * \brief
 *      Gets the current frame counter of audio decode.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pu32FC							(Output) Pointer to save current frame counter of audio decode.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecGetSamplePerFrame(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32SamPerFra);
/*!\fn ErrorCode DRV_ADEC_DecGetSamplePerFrame(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32SamPerFra)
 * \brief
 *      Gets the sample number of one frame.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pu32SamPerFra					(Output) Pointer to save current frame counter of audio decode.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
ErrorCode DRV_ADEC_DecTotalSample(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32TotalSam);
/*!\fn ErrorCode DRV_ADEC_DecGetSamplePerFrame(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32SamPerFra)
 * \brief
 *      Gets the sample number of one frame.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pu32TotalSam					(Output) Pointer to save total samples of audio decode.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
ErrorCode DRV_ADEC_DecGetBitRate(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32BitRate);
/*!\fn ErrorCode DRV_ADEC_DecGetBitRate(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, u32* pu32BitRate)
 * \brief
 *      Gets the Bitrate.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pu32BitRate						(Output) Pointer to save bit rate.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_DecGetBuffRem(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject,u32* pu32BuffRem);
/*!\fn ErrorCode DRV_ADEC_DecGetBuffRem(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject,u32* pu32BuffRem)
 * \brief
 *      Gets the buffer remainder of specified object.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enDecoderObject    				(Input) References a specific audio decoder.
 * \param 	pu32BuffRem						(Output) Pointer to save buffer remainder.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

/*****************
//Post Processor Functions
*****************/
ErrorCode DRV_ADEC_PPSetVolume(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_Volume* pstVolume);
/*!\fn ErrorCode DRV_ADEC_PPSetVolume(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_Volume* pstVolume)
 * \brief
 *      Sets the volume attenuation applied to the output channels.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	pstVolume						(Input) Specifies attenuation to apply to output channels.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPGetVolume(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_Volume* pstVolume);
/*!\fn ErrorCode DRV_ADEC_PPGetVolume(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_Volume* pstVolume)
 * \brief
 *      Gets the current volume attenuation applied to the output channels.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	pstVolume						(Output) Stores the result of the current attenuation applied to the output channels.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPSetEQ(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_EQ *pstEQ);
/*!\fn ErrorCode DRV_ADEC_PPSetEQ(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_EQ *pstEQ)
 * \brief
 *      Sets the equalization Parameter.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	pstEQ							(Input) Struct for equalization Parameter.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPGetEQ(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_EQ *pstEQ);
/*!\fn ErrorCode DRV_ADEC_PPGetEQ(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_EQ *pstEQ)
 * \brief
 *     Get the equalization Parameter.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	pstEQ							(Output) Pointer to returned equalization Parameter.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPGetCapability(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_PPCapability* pstCapability);
/*!\fn ErrorCode DRV_ADEC_PPGetCapability(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_PPCapability* pstCapability)
 * \brief
 *     Get the capabilities of the specified postprocessing device.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	pstCapability					(Output) Pointer to returned capabilities.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPSetStereoMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_StereoMode enStereoMode);
/*!\fn ErrorCode DRV_ADEC_PPSetStereoMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_StereoMode enStereoMode)
 * \brief
 *     Set the stereo configuration.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	enStereoMode					(Input) Indicating the stereo configuration.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPGetStereoMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_StereoMode* penStereoMode);
/*!\fn ErrorCode DRV_ADEC_PPGetStereoMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_StereoMode* penStereoMode)
 * \brief
 *     Get the stereo configuration.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	penStereoMode					(Output) Pointer to returned the stereo configuration.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPSetKaraokeMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_KARAOK_MODE enKaraokMode);
/*!\fn ErrorCode DRV_ADEC_PPSetKaraokeMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_KARAOK_MODE enKaraokMode)
 * \brief
 *     Set the Karaok configuration.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	enKaraokMode					(Input) Indicating the Karaok Mode configuration.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPGetKaraokeMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_KARAOK_MODE* penKaraokMode);
/*!\fn ErrorCode DRV_ADEC_PPGetKaraokeMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_KARAOK_MODE* penKaraokMode)
 * \brief
 *     Get the karaok configuration.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	penKaraokMode					(Output) Pointer to returned the karaok configuration.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPReSetACLKOuput(EN_DRV_ADEC_SampleFrequency enSampleFreq);
/*!\fn ErrorCode DRV_ADEC_PPReSetACLKOuput(EN_DRV_ADEC_SampleFrequency enSampleFreq)
 * \brief
 *     Set the APLL clock.
 *
 * \param 	enSampleFreq					(Input) Desired output frequency.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 */

ErrorCode DRV_ADEC_PPGetSpectrum(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_SPECTRUM* pstSpectrum);
/*!\fn ErrorCode DRV_ADEC_PPGetSpectrum(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_SPECTRUM* pstSpectrum);
 * \brief
 *     Retrieves the spectrum parameter.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject   				(Input) References a specific post processor interface.
 * \param 	pstSpectrum						(Output) Pointer to returned the spectrum parameter.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPSetBeepToneFrequency(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, u32 u32BeepToneFrequency);
/*!\fn ErrorCode DRV_ADEC_PPSetBeepToneFrequency(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, u32 u32BeepToneFrequency)
 * \brief
 *      Sets the beep tone frequency.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject    				(Input) References a specific audio decoder.
 * \param 	u32BeepToneFrequency    		(Input) Desired beep tone.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADEC_PPGetBeepToneFrequency(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, u32* u32BeepToneFreq);
/*!\fn ErrorCode DRV_ADEC_PPGetBeepToneFrequency(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, u32* u32BeepToneFreq)
 * \brief
 *      Retrieves the current Beep Tone frequency.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject    				(Input) References a specific audio decoder.
 * \param 	u32BeepToneFreq					(Output) Stores the current value of beep tone frequencty.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 */

ErrorCode DRV_ADEC_PPSetBeepToneMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_BEEPTONE_MODE enBeepToneMode);
/*!\fn ErrorCode DRV_ADEC_PPSetBeepToneMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_BEEPTONE_MODE enBeepToneMode)
 * \brief
 *      Set the Beep Tone Mode.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject    				(Input) References a specific audio decoder.
 * \param 	enBeepToneMode					(Input) Beep Tone Mode.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 */

ErrorCode DRV_ADEC_PPGetBeepToneMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_BEEPTONE_MODE* enBeepToneMode);
/*!\fn ErrorCode DRV_ADEC_PPSetBeepToneMode(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, EN_DRV_ADEC_BEEPTONE_MODE enBeepToneMode)
 * \brief
 *      Retrieves the current Beep Tone Mode.
 *
 * \param 	u32Handle						(Input) An open handle number of the audio device.
 * \param 	enPostProcObject    				(Input) References a specific audio decoder.
 * \param 	enBeepToneMode					(Output) Point for retrieve Beep Tone Mode.
 *
 * \return	ADEC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 */
ErrorCode DRV_ADEC_DecSetDualMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_StereoMode enStereoMode);
ErrorCode DRV_ADEC_DecGetDualMode(u32 u32Handle, EN_DRV_ADEC_Object enDecoderObject, EN_DRV_ADEC_StereoMode* penStereoMode);
ErrorCode DRV_ADEC_OupEnableAACBypass(u32 u32Handle, EN_DRV_ADEC_Object enOutputObject,bool bEnable);
ErrorCode DRV_ADEC_FourceRestAPU(EN_DRV_ADEC_StreamContent enStreamContent);
ErrorCode DRV_ADEC_GetCapBits(DRV_DeviceNameType DeviceName, u32* pu32CapBits);
ErrorCode DRV_ADEC_EnableExtraCap(bool b8Enable);
u32 DRV_ADEC_GetLiveDecStartThres(void);
ErrorCode DRV_ADEC_APBEnable(void);
#ifdef DDP_CERTIFICATION
ErrorCode DRV_ADEC_SetDDCParameters( s32 *s32DDC_parameters );
#endif
/*********************************** for avsync *********************************************/
u32 DRV_ADEC_GetVolume(void);
u32 DRV_ADEC_GetSTCHandle(void);
u32 DRV_ADEC_GetPTSBufAddr(void);
u32 DRV_ADEC_GetStreamStartAddr(void);
u32 DRV_ADEC_GetInputBufferRem(void);
u32 DRV_ADEC_GetOutputBufferRem(void);
u32 DRV_ADEC_GetSamplingRate(void);
u32 DRV_ADEC_GetSamplePerFrame(void);
u32 DRV_ADEC_GetStreamType(void);
u32 DRV_ADEC_GetFrameCount(void);
u32 DRV_ADEC_GetSyncSpeed(void);
u32 DRV_ADEC_GetBitRate(void);
u32 DRV_ADEC_DACReadDoneTime(void);
ErrorCode DRV_ADEC_DecodeMixGain(EN_DRV_ADEC_MIXGAIN enMixGain);
u32 DRV_ADEC_GetCommand(void);
bool DRV_ADEC_GetAVsyncInitStatus(void);
bool DRV_ADEC_GetShowAVsyncResult(void);
bool DRV_ADEC_GetShowUpdateSTC(void);
bool DRV_ADEC_GetShowCalSTC(void);
void DRV_ADEC_SetCalPTS(u64 u64CalPTS);
void DRV_ADEC_SetOneFrameSTCTime(u64 u64OneFrameSTCTime);
void DRV_ADEC_SaveSTC(u32 u32STC, u32 u32STC33);
void DRV_ADEC_SetAVsyncStatus(u32 u32AVsyncStatus);
void DRV_ADEC_SetSyncDelayTime(u32 u32SyncDelayTime);
void DRV_ADEC_SetAVsyncInitStatus(bool b8Enable);
void DRV_ADEC_SetStepStatus(bool b8Enable);
ErrorCode DRV_ADEC_PPSetAVL(u32 u32Handle, EN_DRV_ADEC_Object enPostProcObject, ST_DRV_ADEC_AVL *pstAVL);
EN_DRV_STC_SyncMaster DRV_ADEC_GetAVsyncMaster(void);
EN_DRV_ADEC_DEC_SOURCE DRV_ADEC_GetDecSource(void);
#ifdef PERFORMANCE_ISSUE
ErrorCode DRV_ADEC_AudioPerformanceEnable(u32 u32Handle,bool bEnable);
#endif

#endif /* __DRV_AUDIO_H__ */
