//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		:
//	Author	:
//	Purpose	: Provide TVE Control
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

#ifndef __DRV_TVE_H__
#define __DRV_TVE_H__

#include "def_type.h"
#include "def_err.h"
#include "drv_vtg.h"
#include "drv_layer.h"


/*
 * Brief: DRV_TVE global define.
 */
#define TVE_MAX_DEV_NUM  					1   /*!< The maximum device number of tve module        */
#define TVE_MAX_HANDLE_PER_CHANNEL		1   /*!< The maximum handle number of tve module        */

/*!
 * \brief
 * TVE Error code definition.
 */
enum
{
    ERROR_TVE_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_TVE,	/*!< Operation invalid, because handle not close*/
    ERROR_TVE_UNKNOW_DEVICE,								/*!< Invalid device name */
    ERROR_TVE_UNSUPPORT_DEVICE							/*!< Un-Support Device */
};

 /**
 * \brief
 * enumurate to indicate the TVE channel
 */
typedef enum
{
    EN_DRV_TVE_CHANNEL_MAIN,
    EN_DRV_TVE_CHANNEL_NUM,
    EN_DRV_TVE_CHANNEL_UNKNOWN
} EN_DRV_TVE_CHANNEL, *PEN_DRV_TVE_CHANNEL;

/**
 * \brief
 * enumurate to indicate the TVE register
 */
typedef enum
{
    EN_DRV_TVE_R0,                      // 1
    EN_DRV_TVE_R1,                      // 2
    EN_DRV_TVE_CCTX_LN_O,       // 3
    EN_DRV_TVE_CCTX_LN_E,       // 4
    EN_DRV_TVE_CC_D,                 //5
    EN_DRV_TVE_WSS_D_O,          //6
    EN_DRV_TVE_WSS_D_E,          //7
    EN_DRV_TVE_GAIN_YC,           //8
    EN_DRV_TVE_GAIN_CAV,         //9
    EN_DRV_TVE_GAIN_G,            //10
    EN_DRV_TVE_MV0,                  //11
    EN_DRV_TVE_MV1,                  //12
    EN_DRV_TVE_MV2,                  //13
    EN_DRV_TVE_MV3,                  //14
    EN_DRV_TVE_MV4,                  //15
    EN_DRV_TVE_MV5,                  //16
    EN_DRV_TVE_R2,                     //17
    EN_DRV_TVE_WAP_PROG,        //18
    EN_DRV_TVE_CC_AUTO_CR0,          //19
    EN_DRV_TVE_CC_AUTO_CR1,          //20
    EN_DRV_TVE_CC_AUTO_CR2,          //21
    EN_DRV_TVE_HDTV_CR,              //22
    EN_DRV_TVE_ADJ_CR0,              //23
    EN_DRV_TVE_ADJ_CR1,              //24
    EN_DRV_TVE_ADJ_CR2,              //25
    EN_DRV_TVE_ADJ_CR3,              //26
    EN_DRV_TVE_ADJ_CR4,              //27
    EN_DRV_TVE_ADJ_CR5,              //28
    EN_DRV_TVE_ADJ_CR6,              //29
    EN_DRV_TVE_ADJ_CR7,              //30

    EN_DRV_TVE_WSS_HD_CR0,           //31
    EN_DRV_TVE_WSS_HD_CR1,           //32
    EN_DRV_TVE_WSS_HD_CR2,           //33
    EN_DRV_TVE_WSS_HD_CR3,           //34
    EN_DRV_TVE_WSS_HD_CR4,           //35
    EN_DRV_TVE_WSS_HD_CR5,           //36
    EN_DRV_TVE_WSS_HD_CR6,           //37
    EN_DRV_TVE_WSS_HD_CR7,           //38
    EN_DRV_TVE_WSS_HD_CR8,           //39
    EN_DRV_TVE_WSS_HD_CR9,           //40
    EN_DRV_TVE_WSS_HD_CR10,          //41
    EN_DRV_TVE_WSS_HD_CR11,          //42
    EN_DRV_TVE_WSS_HD_CR12,          //43
    EN_DRV_TVE_VIDAC2IN_ADJ_CR,      //44
    EN_DRV_TVE_VIDAC1IN_ADJ_CR,      //45
    EN_DRV_TVE_VIDAC0IN_ADJ_CR,      //46
    EN_DRV_TVE_VIDAC3IN_ADJ_CR,
    EN_DRV_TVE_PI_CR0,
    EN_DRV_TVE_PI_CR1,
    EN_DRV_TVE_PI_CR2,
    EN_DRV_TVE_TTX_BASE,
    EN_DRV_TVE_TTX_UPPER,
    EN_DRV_TVE_TTX_LOWER,
    EN_DRV_TVE_TTX_CTRL,
    EN_DRV_TVE_VIDAC_CTRL,
    EN_DRV_TVE_HBLK_PS_ST,
    EN_DRV_TVE_HBLK_PS_ED,
    EN_DRV_TVE_VBLK_REGION_FID1,
    EN_DRV_TVE_VBLK_REGION_FID2,

}EN_DRV_TVE_REG, *PEN_DRV_TVE_REG;

/*!
 * \brief
 * enumurate to indicate the video encoding format
 */
typedef enum
{
	EN_DRV_TVE_ENCMODE_NONE        	= 0,
	EN_DRV_TVE_ENCMODE_HD,
	EN_DRV_TVE_ENCMODE_PAL_BDGHIN,            /*!< 576_50HZ        */
	EN_DRV_TVE_ENCMODE_PAL_Nc,          	          /*!< 576_50HZ        */
	EN_DRV_TVE_ENCMODE_NTSC,              	   /*!< 480_60HZ        */
	EN_DRV_TVE_ENCMODE_PAL_M,            	   /*!< 480_60HZ        */
	EN_DRV_TVE_ENCMODE_NTSC_443,                /*!< 480_60HZ        */
} EN_DRV_TVE_ENCMODE, *PEN_DRV_TVE_ENCMODE;

/*!
 * \brief
 * enumurate to indicate the video encoding output
 */
typedef enum
{
	EN_DRV_TVE_VOUT_NONE = 0,
       EN_DRV_TVE_VOUT_CVBS = 0x1,           	/*!< DAC0:CVBS, DAC1:Y, DAC2:C, DAC3:CVBS       */
	EN_DRV_TVE_VOUT_YUV = 0x2,             /*!< DAC0:Y, DAC1:Pb, DAC2:Pr, DAC3:CVBS       */
	EN_DRV_TVE_VOUT_RGB = 0x4,	     	/*!< DAC0:G, DAC1:B, DAC2:R, DAC3:CVBS       */
	EN_DRV_TVE_VOUT_VGA = 0x8,     		/*!< DAC0:G, DAC1:B, DAC2:R, DAC3:CVBS       */
	EN_DRV_TVE_VOUT_SVIDEO = 0x10,      /*!< DAC0:CVBS, DAC1:Y, DAC2:C, DAC3:CVBS       */
} EN_DRV_TVE_VOUT, *PEN_DRV_TVE_VOUT;

/*!
 * \brief
 * enumurate to indicate the WSS mode
 */
typedef enum
{
	EN_DRV_TVE_WSSMODE_NONE = 0,
	EN_DRV_TVE_WSSMODE_HD,                  /*!< WSS format for HD mode       */
	EN_DRV_TVE_WSSMODE_525,	               /*!< WSS format for 525-line mode       */
	EN_DRV_TVE_WSSMODE_625,              	 /*!< WSS format for 625-line mode       */
} EN_DRV_TVE_WSSMODE, *PEN_DRV_TVE_WSSMODE;

/*!
 * \brief
 * enumurate to indicate the aspect ratio of WSS 625-line mode
 */
typedef enum
{
	EN_DRV_TVE_625WSS_AR_LB_CENTER_14_9 = 0x1,  /*!< Aspect Ratio:14:9, Format:letterbox, Position On 4:3 Display:center  */
	EN_DRV_TVE_625WSS_AR_LB_TOP_14_9 = 0x2,         /*!< Aspect Ratio:14:9, Format:letterbox, Position On 4:3 Display:top  */
	EN_DRV_TVE_625WSS_AR_LB_TOP_16_9 = 0x4,         /*!< Aspect Ratio:16:9, Format:letterbox, Position On 4:3 Display:top  */
	EN_DRV_TVE_625WSS_AR_FULL_16_9 = 0x7,               /*!< Aspect Ratio:16:9, Format:full format, Position On 4:3 Display:-  */
	EN_DRV_TVE_625WSS_AR_FULL_4_3 = 0x8,                /*!< Aspect Ratio:4:3, Format:full format, Position On 4:3 Display:-  */
	EN_DRV_TVE_625WSS_AR_LB_CENTER_16_9 = 0xB,  /*!< Aspect Ratio:16:9, Format:letterbox, Position On 4:3 Display:center  */
	EN_DRV_TVE_625WSS_AR_FULL_14_9 = 0xE,	        /*!< Aspect Ratio:14:9, Format:full format, Position On 4:3 Display:center  */
} EN_DRV_TVE_625WSS_AR, *PEN_DRV_TVE_625WSS_AR;

/*!
 * \brief
 * enumurate to indicate the subtitles of WSS 625-line mode
 */
typedef enum
{
	EN_DRV_TVE_625WSS_SUB_NO = 0,           /*!< no subtitles       */
	EN_DRV_TVE_625WSS_SUB_INPIC,            /*!< inside active picture      */
	EN_DRV_TVE_625WSS_SUB_OUTPIC,         /*!< outside active picture       */
	EN_DRV_TVE_625WSS_SUB_REV,	            /*!< reserved       */
} EN_DRV_TVE_625WSS_SUB, *PEN_DRV_TVE_625WSS_SUB;

/*!
 * \brief
 * enumurate to indicate the aspect ratio of WSS 525-line mode
 */
typedef enum
{
	EN_DRV_TVE_525WSS_AR_NORMAL_4_3 = 0,        /*!< 4:3 aspect ratio, normal       */
	EN_DRV_TVE_525WSS_AR_ANAMORPHIC_16_9,    /*!< 16:9 aspect ratio, anamorphic       */
	EN_DRV_TVE_525WSS_AR_LB_4_3,                        /*!< 4:3 aspect ratio, letterbox       */
	EN_DRV_TVE_525WSS_AR_REV,	                        /*!< reserved       */
} EN_DRV_TVE_525WSS_AR, *PEN_DRV_TVE_525WSS_AR;

/*!
 * \brief
 * enumurate to indicate the CGMS information of WSS 525-line mode
 */
typedef enum
{
	EN_DRV_TVE_525WSS_CGMS_CPYPERMIT = 0,       /*!< copying permitted       */
	EN_DRV_TVE_525WSS_CGMS_NOMORECPY,	           /*!< no copying permitted      */
	EN_DRV_TVE_525WSS_CGMS_ONECPY,                  /*!< one copy permitted       */
	EN_DRV_TVE_525WSS_CGMS_NEVERCPY               /*!< reserved       */
} EN_DRV_TVE_525WSS_CGMS, *PEN_DRV_TVE_525WSS_CGMS;

/*!
 * \brief
 * enumurate to indicate the analog protection service of WSS 525-line mode
 */
typedef enum
{
	EN_DRV_TVE_525WSS_APS_OFF = 0,      /*!< no Analog Protection Service       */
	EN_DRV_TVE_525WSS_APS_AGC2,          /*!< PSP on, 2-line color striping on       */
	EN_DRV_TVE_525WSS_APS_AGC,            /*!< PSP on, color striping off       */
	EN_DRV_TVE_525WSS_APS_AGC4,	         /*!< PSP on, 4-line color striping on      */
} EN_DRV_TVE_525WSS_APS, *PEN_DRV_TVE_525WSS_APS;

/*!
 * \brief
 * enumurate to indicate the closed caption field to be enabled / written.
 */
typedef enum
{
    EN_DRV_TVE_CCMODE_NONE = 0,     /*!< No closed caption /extended data encoding       */
    EN_DRV_TVE_CCMODE_FIELD1,        /*!< Closed caption /extended data encoding enabled in field 1 (odd)       */
    EN_DRV_TVE_CCMODE_FIELD2,        /*!< Closed caption /extended data encoding enabled in field 2 (even)       */
    EN_DRV_TVE_CCMODE_BOTH,           /*!< Closed caption /extended data encoding enabled in both fields       */
} EN_DRV_TVE_CCMode;

/*!
 * \brief
 * enumurate to indicate the input / output format to be transferred.
 */
typedef enum
{
    EN_DRV_TVE_CSCMODE_Y601C219_RGB255 = 0,     /*!< Input:Y601CbCr219, Output:RGB255      */
    EN_DRV_TVE_CSCMODE_Y709C219_RGB255,           /*!< Input:Y709CbCr219, Output:RGB255       */
    EN_DRV_TVE_CSCMODE_RGB255_Y601C255,          /*!< Input:RGB255, Output:Y601CbCr255       */
    EN_DRV_TVE_CSCMODE_USER_DEF,                        /*!< user defined mode       */
} EN_DRV_TVE_CSCMode;

/*!
 * \brief
 * enumurate to indicate the parameter of tve.
 */
typedef enum
{
	EN_DRV_TVE_OPTION_ASB_DELAY,            /*!< Advanced Split Burst Start Delay, Value: 0 ~ 3      */
	EN_DRV_TVE_OPTION_SYNC_DELAY,          /*!< Sync Signals Adjustment, Value: 0 ~ 3      */
	EN_DRV_TVE_OPTION_LUMA_DELAY,         /*!< Luminance Path Delay w/ Reference to Chrominance Path, Value: 0 ~ 7      */
	EN_DRV_TVE_OPTION_YCBCR_RANGE,        /*!< The YCbCr Input Range Mode. 0: Y:16-235/ CbCr: 16-240, 1: YCbCr: 1-254      */
	EN_DRV_TVE_OPTION_BLEVEL_LEVEL,       /*!< The Black Level 0: 0 IRE 1: 7.5 IRE      */
	EN_DRV_TVE_OPTION_EIA_RATIO,            /*!< 525 Line YPbPr Component Video Interface, 0: 714 mv, 1: 700 mv      */
	EN_DRV_TVE_OPTION_NUM
} EN_DRV_TVE_OPTION;

/*!
 * \brief
 * enumurate to indicate the no. of vdac.
 */
typedef enum
{
    EN_DRV_TVE_DAC_0 = 0x1,     /*!< VDAC0       */
    EN_DRV_TVE_DAC_1 = 0x2,     /*!< VDAC1       */
    EN_DRV_TVE_DAC_2 = 0x4,     /*!< VDAC2       */
    EN_DRV_TVE_DAC_3 = 0x8,     /*!< VDAC3       */
}EN_DRV_TVE_DAC;

/*!
 * \brief
 * enumurate to indicate tve module to be enable / disable.
 */
typedef enum
{
	EN_DRV_TVE_DISABLED,    /*!< Tve is enabled       */
	EN_DRV_TVE_ENABLED      /*!< Tve is disabled       */
} EN_DRV_TVE_STATE, *PEN_DRV_TVE_STATE;

/*!
 * \brief
 * the structure defines the information needed to set up TVE channel
 */
typedef struct
{
    EN_DRV_VTG_TIMING       enVTGTiming;          /*!< The VTG Timing      */
    EN_DRV_TVE_ENCMODE    enTveEncMode;       /*!< The TVE Encode mode      */
    EN_DRV_TVE_VOUT         	 enVOut;         	     /*!< The video encoding output       */

    u32 u32Gain_YC;      	/*!< Y/Cb/Cr Gain for CVBS and S-video Out      */
    u32 u32Gain_CAV;      	/*!< Y/Cb/Cr Gain for Component Y/Pb/Pr and G/B/R Out      */
    u32 u32Gain_G;      	/*!< Cb/Cr Gain for G      */
	u32 u32Gain_ADJ;       /*!< Y/Cb/Cr Gain for Component Y/Pb/Pr and G/B/R Out      */
	u32 u32VDAC_Y;

    u8 u8DAC_Off;               /*!< VDAC enable/disable      */
    u8 u8Asb_dl;       		/*!< Advanced Split Burst Start Delay, Value: 0 ~ 3      */
    u8 u8Sync_on_G;    	/*!< Sync on G 0: Off 1: On      */
    u8 u8Sync_dl;      		/*!< Sync Signals Adjustment, Value: 0 ~ 3      */
    u8 u8Y_dl;         		/*!< Luminance Path Delay w/ Reference to Chrominance Path, Value: 0 ~ 7      */
    u8 u8Full_ip;      		/*!< The YCbCr Input Range Mode. 0: Y:16-235/ CbCr: 16-240, 1: YCbCr: 1-254      */
    u8 u8Setup;        		/*!< The Black Level 0: 0 IRE 1: 7.5 IRE      */
    u8 u8Eia700;       		/*!< 525 Line YPbPr Component Video Interface, 0: 714 mv, 1: 700 mv      */
    u8 u8ColorBar;     		/*!< Internal 100% color bar pattern      */

} ST_TVE_OutputParam, *PST_TVE_OutputParam;

/*!
 * \brief
 * the structure defines the supported and unsupported features of a given plane
 */
typedef struct
{
	EN_DRV_TVE_VOUT 	enSupportedVOuts;       /*!< video encoding output 	*/
	EN_DRV_TVE_DAC		enSupportedDacs;        /*!< the no. of vdac	*/
	bool      	b8HDSupport;	                               /*!< support HD output or not	*/
} ST_TVE_Capability, *PST_TVE_Capability;

/*!
 * \brief
 * the initial structure includes the device hardware setting
 */
typedef struct
{
    EN_DRV_TVE_CHANNEL enTveCh;                /*!< indicate the TVE channel	*/
    os_mempool_handle u32MemPoolHandle;	/*!< A memory pool handle for TVE module	*/
}ST_TVE_Init, *PST_TVE_Init;

/*!
 * \brief
 * the open structure includes the tve opening parameters
 */
typedef struct
{
	ST_TVE_OutputParam stOutput;    /*!< A information needed to set up TVE channel     */
}ST_TVE_Open, *PST_TVE_Open;

/*!
 * \brief
 * the structure includes some parameters of tve
 */
typedef struct
{
    EN_DRV_TVE_OPTION      Option;  /*!< indicate the parameter of tve      */
    union
    {
        u8              u8Asb_dl;		/*!< Advanced Split Burst Start Delay, Value: 0 ~ 3      */
        u8              u8Sync_dl; 	/*!< Sync Signals Adjustment, Value: 0 ~ 3      */
        u8              u8Y_dl;  		/*!< Luminance Path Delay w/ Reference to Chrominance Path, Value: 0 ~ 7      */
        u8              u8Full_ip;		/*!< The YCbCr Input Range Mode. 0: Y:16-235/ CbCr: 16-240, 1: YCbCr: 1-254      */
        u8              u8Setup;		/*!< The Black Level 0: 0 IRE 1: 7.5 IRE      */
        u8              u8Eia700;		/*!< 525 Line YPbPr Component Video Interface, 0: 714 mv, 1: 700 mv      */
    } Value;
} ST_TVE_ModeOption, *PST_TVE_ModeOption;

/*!
 * \brief
 * the structure includes gain and offset of VDAC
 */
typedef struct
{
    u8 u8VDAC_en; 
    u8 u8Gain;          /*!< gain to adjust VDAC's input, 1.6      */
    u16 u16Offset;   /*!< offset to adjust VDAC's input, 2's complement      */
} ST_TVE_DAC_GainOffset_Param, *PST_TVE_DAC_GainOffset_Param;

/*!
 * \brief
 * the structure includes boundary of TVE
 */
typedef struct
{
    u16 u16Left;        /*!< left boundary      */
    u16 u16Right;      /*!< right boundary      */
    u16 u16Top;        /*!< top boundary      */
    u16 u16Bottom;  /*!< bottom boundary      */
    u16 u16Width;     /*!< width boundary      */
    u16 u16Height;   /*!< height boundary      */
} ST_TVE_ScreenBoundary, *PST_TVE_ScreenBoundary;

/*!
 * \brief
 * the structure includes parameters of HD WSS
 */
typedef struct
{
    u16 u16PayloadF1TA;               /*!< type A only needs payload [13:0], field 1 */
    u16 u16PayloadF2TA;               /*!< type A only needs payload [13:0], field 2 */    
    u16 u16AmpDataValue;        	  /*!< the amplitude as the b8IsAmpData is TRUE     */
	// only 320S, 14
    u16 u16HStTimeTA;                 /*!< the horizontal time to start as the b8IsHVTimeSet is TRUE    */
    u16 u16VStTimeF1TA;               /*!< the vertical time to start for 1st. field as the b8IsHVTimeSet is TRUE    */
    u16 u16VStTimeF2TA;               /*!< the vertical time to start for 2nd. field as the b8IsHVTimeSet is TRUE    */
    u16 u16HStTimeTB;                 /*!< the horizontal time to start as the b8IsHVTimeSet is TRUE    */
    u16 u16VStTimeF1TB;               /*!< the vertical time to start for 1st. field as the b8IsHVTimeSet is TRUE    */
    u16 u16VStTimeF2TB;               /*!< the vertical time to start for 2nd. field as the b8IsHVTimeSet is TRUE    */  
    u8 u8StSymF1TA;                   /*!< start symbol for 1st. field    */
    u8 u8HeaderF1TA;                  /*!< header for 1st. field     */
    u8 u8StSymF2TA;                   /*!< start symbol for 2nd. field    */
    u8 u8HeaderF2TA;                  /*!< header for 2nd. field    */
    u8 u8StSymF1TB;                   /*!< start symbol for 1st. field    */
    u8 u8HeaderF1TB;                  /*!< header for 1st. field     */
    u8 u8StSymF2TB;                   /*!< start symbol for 2nd. field    */
    u8 u8HeaderF2TB;                  /*!< header for 2nd. field    */ 
	// only 310T, 7
	u16 u16HStTime; 				  /*!< the horizontal time to start as the b8IsHVTimeSet is TRUE	  */
	u16 u16VStTimeF1;				  /*!< the vertical time to start for 1st. field as the b8IsHVTimeSet is TRUE    */
	u16 u16VStTimeF2;				  /*!< the vertical time to start for 2nd. field as the b8IsHVTimeSet is TRUE    */	
	u8 u8StSymF1;					  /*!< start symbol for 1st. field	*/
	u8 u8HeaderF1;					  /*!< header for 1st. field	   */
	u8 u8StSymF2;					  /*!< start symbol for 2nd. field	*/
	u8 u8HeaderF2;					  /*!< header for 2nd. field	  */	
	
    u8 u8VerNoF1TB;                   /*!< field 1's Version Number Byte for type B     */
    u8 u8LengthF1TB;                  /*!< field 1's length of packet payload in bytes for type B     */
    u8 u8DataF1TB[14];                /*!< field 1's payload[127:0] for type B     */
    u8 u8VerNoF2TB;                   /*!< field 2's Version Number Byte for type B     */
    u8 u8LengthF2TB;                  /*!< field 2's length of packet payload in bytes for type B    */
    u8 u8DataF2TB[14];                /*!< field 2's payload[127:0] for type B     */
	// only 320S, 4 
    u8 u8TotalBitDataTA;              /*!< total bits of W.S.S. data and the maximum is 136 as the b8IsHVTimeSet is TRUE    */
    u8 u8DurationTimeTA;              /*!< the duration of time for one data bit, unit: clock as the b8IsHVTimeSet is TRUE    */
    u8 u8TotalBitDataTB;              /*!< total bits of W.S.S. data and the maximum is 136 as the b8IsHVTimeSet is TRUE    */
    u8 u8DurationTimeTB;              /*!< the duration of time for one data bit, unit: clock as the b8IsHVTimeSet is TRUE    */
	// only 310T, 2
	u8 u8TotalBitData;				  /*!< total bits of W.S.S. data and the maximum is 136 as the b8IsHVTimeSet is TRUE	  */
	u8 u8DurationTime;				  /*!< the duration of time for one data bit, unit: clock as the b8IsHVTimeSet is TRUE	*/	
	
    bool b8IsTypeB;                   /*!< the HD WSS mode is B-type if set TRUE     */
	// only 320S, 1	
    bool b8IsTypeA;                   /*!< the HD WSS mode is A-type if set TRUE     */    
	
    bool b8IsAmpData;                 /*!< the amplitude value can be set if set TRUE     */
	// only 320S, 2	
    bool b8IsHVTimeSetTA;             /*!< the HV start time can be set if set TRUE    */
    bool b8IsHVTimeSetTB;             /*!< the HV start time can be set if set TRUE    */
	
	bool b8IsHVTimeSet; 			  /*!< the HV start time can be set if set TRUE	*/	
	bool b8IsHD480P;	
} ST_TVE_HDWSSParam, *PST_TVE_HDWSSParam;
/*!
 * \brief
 * the structure includes parameters of WSS 625-line mode
 */
typedef struct
{
    EN_DRV_TVE_625WSS_AR enAR;          /*!< indicate the aspect ratio of WSS 625-line mode  */
    EN_DRV_TVE_625WSS_SUB enSub;      /*!< indicate the subtitles of WSS 625-line mode  */
    bool b8IsFileMode;                          /*!< TRUE:film mode, FALSE:camera mode  */
    bool b8IsMAColorPlus;                    /*!< color encoding => TRUE:Motion Adaptive ColorPlus, FALSE:normal PAL  */
    bool b8IsSignalPresent;                  /*!< helper signals => TRUE:present, FALSE:not present  */
    bool b8IsTTXSub;                            /*!< teletext subtitles => TRUE:YES, FALSE:NO  */
    bool b8IsSurroundSound;               /*!< surround sound => TRUE:YES, FALSE:NO  */
    bool b8IsCpyAssert;                       /*!< For CGMS-A, TRUE:copyright asserted, FALSE:no copyright asserted or unknown  */
    bool b8IsCpyRestrict;                     /*!< For CGMS-A, TRUE:copying restricted, FALSE:copying not restricted  */
} ST_TVE_625WSSParam, *PST_TVE_625WSSParam;

/*!
 * \brief
 * the structure includes parameters of WSS 525-line mode
 */
typedef struct
{
    EN_DRV_TVE_525WSS_AR enAR;                  /*!< indicate the aspect ratio of WSS 525-line mode   */
    bool b8IsCpyAssert;                       		/*!< For CGMS-A, TRUE:copyright asserted, FALSE:no copyright asserted or unknown  */
    bool b8IsCpyRestrict;                    		 /*!< For CGMS-A, TRUE:copying restricted, FALSE:copying not restricted  */
    EN_DRV_TVE_525WSS_APS enAPS;             /*!< indicate the analog protection service of WSS 525-line mode   */
    bool b8IsCpyCtrlInfo;                              /*!< TRUE:default, FALSE:copy control information   */
    bool b8IsAnaPreRecMedium;                  /*!< analog pre-recorded medium => TRUE:YES, FALSE:NO  */
} ST_TVE_525WSSParam, *PST_TVE_525WSSParam;

/*!
 * \brief
 * the structure includes parameters of WSS mode
 */
typedef struct
{

    EN_DRV_TVE_WSSMODE enWssMode;	        /*!< indicate the WSS mode   */
    union
    {
        ST_TVE_HDWSSParam stHDWss;             /*!< includes parameters of HD WSS   */
        ST_TVE_625WSSParam st625Wss;          /*!< includes parameters of WSS 625-line mode   */
        ST_TVE_525WSSParam st525Wss;          /*!< includes parameters of WSS 525-line mode   */
    }Type;
} ST_TVE_WSSParam, *PST_TVE_WSSParam;

/*!
 * \brief
 * the structure includes parameters of Close caption
 */
typedef struct
{
    EN_DRV_TVE_CCMode enCCMode;         /*!< indicate the closed caption mode   */
    u16  u16LinesField1;               /*!< select the TV lines in odd fields where closed caption data is to be encoded   */
    u16  u16LinesField2;              /*!< select the TV lines in even fields where closed caption data is to be encoded   */
} ST_TVE_CCParam, *PST_TVE_CCParam;


/*!
 * \brief
 * the structure includes parameters of Color space transfer module for TVE
 */
typedef struct
{
    EN_DRV_TVE_CSCMode enCSCMode;   /*!< indicate the input / output format to be transferred   */
    u16  u16Coef00;                                 /*!< Coefficient 00, Maximum Value is 0x7FFF    */
    u16  u16Coef01;                                 /*!< Coefficient 01, Maximum Value is 0x7FFF    */
    u16  u16Coef02;                                 /*!< Coefficient 02, Maximum Value is 0x7FFF    */
    u16  u16Coef10;                                 /*!< Coefficient 10, Maximum Value is 0x7FFF    */
    u16  u16Coef11;                                 /*!< Coefficient 11, Maximum Value is 0x7FFF    */
    u16  u16Coef12;                                 /*!< Coefficient 12, Maximum Value is 0x7FFF    */
    u16  u16Coef20;                                 /*!< Coefficient 20, Maximum Value is 0x7FFF    */
    u16  u16Coef21;                                 /*!< Coefficient 21, Maximum Value is 0x7FFF    */
    u16  u16Coef22;                                 /*!< Coefficient 22, Maximum Value is 0x7FFF    */
    u16  u16Const01;                               /*!< Const 1, Maximum Value is 0xFFF            */
    u16  u16Const02;                               /*!< Const 2, Maximum Value is 0xFFF            */
    u16  u16Const03;                               /*!< Const 3, Maximum Value is 0xFFF            */
} ST_TVE_CSCParam, *PST_TVE_CSCParam;

ErrorCode DRV_TVE_GetCapability (DRV_DeviceNameType DeviceName, PST_TVE_Capability  pstCapability);
/*!\fn ErrorCode DRV_TVE_GetCapability (DRV_DeviceNameType DeviceName, PST_TVE_Capability  pstCapability)
 *
 * \brief
 * 		Get the capabilities of the named Tve plane
 *
 * \param 	DeviceName				(Input)  Device Name
 * \param	pstCapability				(Output) The capability structure for indicated layer
 *
 *
 * \retval	ERROR_NO_ERROR							No error
 * \retval	ERROR_TVE_UNKNOW_DEVICE			Invalid device name
 * \retval	ERROR_BAD_PARAMETER                                 Bad parameter passed
 */

ErrorCode DRV_TVE_Init (DRV_DeviceNameType DeviceName, PST_TVE_Init pstInit);
/*!\fn ErrorCode DRV_TVE_Init (DRV_DeviceNameType DeviceName, PST_TVE_Init pstInit)
 *
 * \brief
 * 		Initialize TVE device with pstInit setting
 *
 * \param 	DeviceName		                		(Input)  Device Name
 * \param	pstInit							(Input) Pointer to the initialization parameter structure
 *
 * \retval	ERROR_NO_ERROR						        No error
 * \retval	ERROR_BAD_PARAMETER				        Bad parameter passed
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE            Un-Support Device
 * \retval	ERROR_INITIALISED                                         The driver is not initialized or already initialized
 * \retval	ERROR_NO_FREE_HANDLE                                 No free handle for the device
 *
 */

ErrorCode DRV_TVE_Term (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_TVE_Term (DRV_DeviceNameType DeviceName, bool b8Force)
 *
 * \brief
 * 		Terminate the TVE device driver
 *
 * \param 	DeviceName		                		(Input)  Device Name
 * \param	b8Force							(Input) Force terminate the Tve or not
 *
 * \retval	ERROR_NO_ERROR							No error
 * \retval	ERROR_TVE_HANDLE_NOT_CLOSED		Handle is not closed
 * \retval	ERROR_TVE_UNKNOW_DEVICE			Invalid device name
 *
 */

ErrorCode DRV_TVE_Open (DRV_DeviceNameType DeviceName, PST_TVE_Open pstOpen, u32* pu32TveHandle);
/*!\fn ErrorCode DRV_TVE_Open (DRV_DeviceNameType DeviceName, PST_TVE_Open pstOpen, u32* pu32TveHandle)
 *
 * \brief
 * 		Open the TVE device and associate it with a handle
 *
 * \param 	DeviceName		(Input)  Device Name
 * \param	pstOpen			(Input) Pointer to the opening parameter structure
 * \param	pu32TveHandle	(Output) The returned handle of the opened device driver
 *
 * \retval	ERROR_NO_ERROR					            No error
 * \retval	ERROR_TVE_UNKNOW_DEVICE	            Invalid device name
 * \retval	ERROR_BAD_PARAMETER			            Bad parameter passed
 * \retval	ERROR_NO_FREE_HANDLE			            No free handle for the device
 *
 */

ErrorCode DRV_TVE_Close (u32* pu32TveHandle);
/*!\fn ErrorCode DRV_TVE_Close (u32* pu32TveHandle)
 *
 * \brief
 * 		Close TVE device associated with a handle
 *
 * \param	pu32TveHandle			(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR							No error
 * \retval	ERROR_INVALID_HANDLE					Handle is not valid
 */

ErrorCode DRV_TVE_Disable(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_Disable(u32 u32TveHandle)
 *
 * \brief
 * 		Disable a specified Tve device, turn off all the DAC's output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_Enable(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_Enable(u32 u32TveHandle)
 *
 * \brief
 * 		Enable a specified Tve device, turn on all the DAC's output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_ConvertYUVHD2SD( u32 u32TveHandle, bool b8Enable );
/*!\fn ErrorCode DRV_TVE_ConvertYUVHD2SD(u32 u32TveHandle, ST_TVE_OutputParam stOutParam)
 *
 * \brief
 * 		Set the parameters of a Tve output. Force output mode to SD or not.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	b8Enable					(Input) Force output mode to SD or not
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_SetOutputParams(u32 u32TveHandle, ST_TVE_OutputParam stOutParam);
/*!\fn ErrorCode DRV_TVE_SetOutputParams(u32 u32TveHandle, ST_TVE_OutputParam stOutParam)
 *
 * \brief
 * 		Set the parameters of a Tve output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	stOutParam				(Input) The structure containing the Tve output parameters
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_GetOutputParams(u32 u32TveHandle, PST_TVE_OutputParam pstOutParam);
/*!\fn ErrorCode DRV_TVE_GetOutputParams(u32 u32TveHandle, PST_TVE_OutputParam pstOutParam)
 *
 * \brief
 * 		Get the parameters of a Tve output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	pstOutParam				(Output) The structure containing the Tve output parameters
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_EnableSelectDac(u32 u32TveHandle, EN_DRV_TVE_DAC enDAC);
/*!\fn ErrorCode DRV_TVE_EnableSelectDac(u32 u32TveHandle, EN_DRV_TVE_DAC enDAC)
 *
 * \brief
 * 		Enable a specified DAC's output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enDAC					(Input) No. of Tve Dac
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_DisableSelectDac(u32 u32TveHandle, EN_DRV_TVE_DAC enDAC);
/*!\fn ErrorCode DRV_TVE_DisableSelectDac(u32 u32TveHandle, EN_DRV_TVE_DAC enDAC)
 *
 * \brief
 * 		Disable a specified DAC's output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enDAC					(Input) No. of Tve Dac
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_GetState(u32 u32TveHandle, PEN_DRV_TVE_STATE penState);
/*!\fn ErrorCode DRV_TVE_GetState(u32 u32TveHandle, PEN_DRV_TVE_STATE penState)
 *
 * \brief
 * 		Get the status of a specified Tve output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	penState					(Output) The structure containing the Tve status parameters
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_GetMode( u32 u32TveHandle, PEN_DRV_TVE_VOUT penVout, PEN_DRV_TVE_ENCMODE penTveEncMode);
/*!\fn ErrorCode DRV_TVE_GetMode( u32 u32TveHandle, PEN_DRV_TVE_VOUT penVout, PEN_DRV_TVE_ENCMODE penTveEncMode)
 *
 * \brief
 * 		Get the parameters of a video encode output and video encode format.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	penVout					(Output) The structure containing the Tve output format
 * \param	penTveEncMode			(Output) The structure containing the Tve output type
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_SetModeOption (u32 u32TveHandle, ST_TVE_ModeOption stMode);
/*!\fn ErrorCode DRV_TVE_SetModeOption (u32 u32TveHandle, ST_TVE_ModeOption stMode)
 *
 * \brief
 * 		Set the ModeOption of a Tve output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	stMode					(Input) The structure containing the Tve ModeOption
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_TVE_GetModeOption (u32 u32TveHandle, PST_TVE_ModeOption pstMode);
/*!\fn ErrorCode DRV_TVE_GetModeOption (u32 u32TveHandle, PST_TVE_ModeOption pstMode)
 *
 * \brief
 * 		Get the ModeOption of a Tve output.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	pstMode					(Output) The structure containing the Tve ModeOption
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_TVE_GetScreenBoundary(EN_DRV_VTG_TIMING enVTGTiming, PST_TVE_ScreenBoundary pstBoundary);
/*!\fn ErrorCode DRV_TVE_GetScreenBoundary(EN_DRV_VTG_TIMING enVTGTiming, PST_TVE_ScreenBoundary pstBoundary)

 *
 * \brief
 * 		Get the ScreenBoundary of a indicated vtg timing.
 *
 * \param	enVTGTiming				(Input) VTG Timing
 * \param	pstBoundary                 	(Output) The structure containing the screen boundary
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_BAD_PARAMETER						Bad parameter passed
 */

ErrorCode DRV_TVE_SetColorBarPattern(u32 u32TveHandle, bool b8ColorBarPattern);
/*!\fn ErrorCode DRV_TVE_SetColorBarPattern(u32 u32TveHandle, bool b8ColorBarPattern)
 *
 * \brief
 * 		Generate or disable a color bar pattern.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	b8ColorBarPattern			(Input) enable or disable colorbar
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_EnableVDACGainOffset(u32 u32TveHandle, EN_DRV_TVE_DAC enDac);
/*!\fn ErrorCode DRV_TVE_EnableVDACGainOffset(u32 u32TveHandle, EN_DRV_TVE_DAC enDac)
 *
 * \brief
 * 		Enable a specified DAC's gain offset module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enDac			              (Input) indicate the no. of vdac
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_DisableVDACGainOffset(u32 u32TveHandle, EN_DRV_TVE_DAC enDac);
/*!\fn ErrorCode DRV_TVE_DisableVDACGainOffset(u32 u32TveHandle, EN_DRV_TVE_DAC enDac)
 *
 * \brief
 * 		Disable a specified DAC's gain offset module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enDac			              (Input) indicate the no. of vdac
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_SetVDACGainOffset(u32 u32TveHandle, EN_DRV_TVE_DAC enDac, ST_TVE_DAC_GainOffset_Param stParam);
/*!\fn ErrorCode DRV_TVE_SetVDACGainOffset(u32 u32TveHandle, EN_DRV_TVE_DAC enDac, ST_TVE_DAC_GainOffset_Param stParam)
 *
 * \brief
 * 		Set the specified DAC's gain offset value.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enDac			              (Input) indicate the no. of vdac
 * \param	stParam                              (Input) indicate the gain and offset of vdac
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_EnablePI(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_EnablePI(u32 u32TveHandle)
 *
 * \brief
 * 		Enable the PI module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_DisablePI(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_DisablePI(u32 u32TveHandle)
 *
 * \brief
 * 		Disable the PI module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */
ErrorCode DRV_TVE_EnableCC(u32 u32TveHandle, EN_DRV_TVE_CCMode enCCMode);
/*!\fn ErrorCode DRV_TVE_EnableCC(u32 u32TveHandle, EN_DRV_TVE_CCMode enCCMode)
 *
 * \brief
 * 		Enable the Close caption module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enCCMode				(Input) indicate the closed caption field to be enabled/written
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_DisableCC(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_DisableCC(u32 u32TveHandle)
 *
 * \brief
 * 		Disable the Close caption module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_SetCCParams(u32 u32TveHandle, ST_TVE_CCParam stCC);
/*!\fn ErrorCode DRV_TVE_SetCCParams(u32 u32TveHandle, ST_TVE_CCParam stCC)
 *
 * \brief
 * 		Set the parameters of the specified Close caption.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	stCC				       (Input) indicate the parameters of Close caption
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_EnableCSC(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_EnableCSC(u32 u32TveHandle)
 *
 * \brief
 * 		Enable the color space transfer module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_DisableCSC(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_DisableCSC(u32 u32TveHandle)
 *
 * \brief
 * 		Disable the color space transfer module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_SetCSCParams(u32 u32TveHandle, ST_TVE_CSCParam stCSC);
/*!\fn ErrorCode DRV_TVE_SetCSCParams(u32 u32TveHandle, ST_TVE_CSCParam stCSC)
 *
 * \brief
 * 		Set the parameters of the color space transfer module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	stCSC				       (Input) indicate the parameters of color space transfer module
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_EnableWSS(u32 u32TveHandle, EN_DRV_TVE_WSSMODE enMode);
/*!\fn ErrorCode DRV_TVE_EnableWSS(u32 u32TveHandle, EN_DRV_TVE_WSSMODE enMode)
 *
 * \brief
 * 		Enable the WSS module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enMode				       (Input) indicate the WSS mode
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_DisableWSS(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_DisableWSS(u32 u32TveHandle)
 *
 * \brief
 * 		Disable the WSS module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_SetWSSParams(u32 u32TveHandle, ST_TVE_WSSParam stWssParam);
/*!\fn ErrorCode DRV_TVE_SetWSSParams(u32 u32TveHandle, ST_TVE_WSSParam stWssParam)
 *
 * \brief
 * 		Set the parameters of the WSS module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	stWssParam				(Input) indicate the parameters of WSS module
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_EnableTTX(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_EnableTTX(u32 u32TveHandle)
 *
 * \brief
 * 		Enable the teletext module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_DisableTTX(u32 u32TveHandle);
/*!\fn ErrorCode DRV_TVE_DisableTTX(u32 u32TveHandle)
 *
 * \brief
 * 		Disable the teletext module.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_WriteTTXData (u32 u32TveHandle, u8* pu8Data,u32 u32Length);
/*!\fn ErrorCode DRV_TVE_WriteTTXData (u32 u32TveHandle, u8* pu8Data,u32 u32Length)
 *
 * \brief
 * 		Write the teletext data.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	pu8Data				       (Input) Teletext  PES_Packet's data
 * \param	u32Length				(Input) Length of Teletext  PES_Packet's data
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 */

ErrorCode DRV_TVE_WriteReg(u32 u32TveHandle, EN_DRV_TVE_REG enTveReg, u32 u32RegValue);
/*!\fn ErrorCode DRV_TVE_WriteReg(u32 u32TveHandle, EN_DRV_TVE_REG enTveReg, u32 u32RegValue)
 *
 * \brief
 * 		Set the data to TVE register.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enTveReg				(Input) TVE register
 * \param	u32RegValue				(Input) register value
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_TVE_ReadReg(u32 u32TveHandle, EN_DRV_TVE_REG enTveReg, u32 *pu32RegValue);
/*!\fn ErrorCode DRV_TVE_ReadReg(u32 u32TveHandle, EN_DRV_TVE_REG enTveReg, u32 *pu32RegValue)
 *
 * \brief
 * 		Get data from the TVE register.
 *
 * \param	u32TveHandle				(Input) An open handle number of the TVE device
 * \param	enTveReg				(Input) TVE register
 * \param	pu32RegValue				(Output) Pointer to the register value
 *
 *
 * \retval	ERROR_NO_ERROR								No error
 * \retval	ERROR_TVE_UNSUPPORT_DEVICE                  Un-Support Device
 * \retval	ERROR_INVALID_HANDLE						Handle is not valid
 */

ErrorCode DRV_TVE_PI_OSD_SetWindow(u32 u32TveHandle, PST_LAYER_WinParam pstPIOSDWin, u8 u8HScale, u8 u8VScale);
ErrorCode DRV_TVE_PI_OSD_LoadPalette(u32 u32TveHandle, u32* pu32PaletteYUV);
ErrorCode DRV_TVE_PI_OSD_LoadData(u32 u32TveHandle, u32* pu32Data);
ErrorCode DRV_TVE_PI_OSD_DisplayCtrl(u32 u32TveHandle, u8 u8Enable);

ErrorCode DRV_TVE_GetVersion (u8 *pu8VersionNum);
/*!\fn ErrorCode DRV_TVE_GetVersion (u8 *pu8VersionNum)
 *
 * \brief
 * 		Get the Module Version number of TVE
 *
 * \param	pu8VersionNum			(Output) Version string of TVE
 *
 *
 * \retval	ERROR_NO_ERROR				No error
 * \retval	ERROR_BAD_PARAMETER		Bad parameter passed
 */

#endif  // #ifndef __DRV_TVE_H__

