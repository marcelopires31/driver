//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//	Date		: 
//	Author		: 
//	Purpose	: Provide NIM Control 
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

#ifndef __DRV_NIM_H__
#define __DRV_NIM_H__

#include "os.h"
#include "def_type.h"
#include "drv_2ws.h"
#include "drv_gpio.h"
#include "drv_event.h"
#include "sw_config.h"    //add by thomas for CONFIG_TUNER==ST_STV6120_S2
#include "customer_config.h"    //add by thomas for CONFIG_TUNER==ST_STV6120_S2
//Define for New NIM rule
#define NEW_NIM_RULE

//#define MTTEST

/**
 * \brief
 *  NIM Error code definition.
 */
typedef enum 
{
	ERROR_NIM_DEV_NAME = ERROR_BASE_DRV_NIM,            /*!< Device Name Error								*/
	ERROR_NIM_NETWORK_TYPE,
	ERROR_NIM_HANDLE_NOT_CLOSED,						/*!< Handle not closed Error						*/
	ERROR_NIM_UNKNOW_DEVICE,							/*!< Unknow device Error							*/	
}EN_DRV_NIM_ERROR;

/**
 * \brief
 * enumurate to indicate the NIM No.
 */
typedef enum
{
	EN_DRV_NIM_0,										/*!< NIM Num 1										*/
	EN_DRV_NIM_1,										/*!< NIM Num 2										*/
	EN_DRV_NIM_NUM
}EN_DRV_NIM_NO;

/**
 * \brief 
 * enumeration to indicate the network types.
 */
typedef enum
{
	EN_DRV_NIM_NET_DVBT,								/*!< DVB-T (Terrestrial)							*/
	EN_DRV_NIM_NET_DVBS,								/*!< DVB-S (Satellite)  							*/
	EN_DRV_NIM_NET_DVBC,								/*!< DVB-C (Cable) 									*/
	EN_DRV_NIM_NET_DUMMY_S,								/*!< DVB-S (Testing) 								*/
	EN_DRV_NIM_NET_NUM,
}EN_DRV_NIM_NETWORK;

/**
 * \brief 
 * enumeration to indicate the demod types.
 */
typedef enum
{	
	EN_DRV_DEMOD_NONE,									/*!< Demod (none)									*/
	
	//LVDS
	EN_DRV_DEMOD_LVDS,	

	//DVBT/T2/C
	EN_DRV_DEMOD_ZL10353,								/*!< Demod (zl10353)								*/
	EN_DRV_DEMOD_NT221D,								/*!< Demod (nt221d)									*/
	EN_DRV_DEMOD_AFA9013,								/*!< Demod (afa9013)								*/
	EN_DRV_DEMOD_NT820,									/*!< Demod (nt820)									*/
	EN_DRV_DEMOD_NT830, 								/*!< Demod (nt830)									*/
	EN_DRV_DEMOD_NT316TB,								/*!< Demod (nt316tb)									*/
	//DVBS/S2
	EN_DRV_DEMOD_MT312 = 0x8000,						/*!< Demod (mt312)									*/
	EN_DRV_DEMOD_DVBS2,									/*!< Demod (dvbs2)									*/
	EN_DRV_DEMOD_NT201C,								/*!< Demod (NT201C)									*/
	EN_DRV_DEMOD_AVL2108,
	EN_DRV_DEMOD_AVL6211,
	EN_DRV_DEMOD_TC90517,
	EN_DRV_DEMOD_DIB8096,
	EN_DRV_DEMOD_TC90527,
	EN_DRV_DEMOD_DIB7090P,
	EN_DRV_DEMOD_DIB8096P,
	EN_DRV_DEMOD_MXL101SF,
	EN_DRV_DEMOD_MTDS3103,// yli ds3k
	EN_DRV_DEMOD_EDS10530,
	
	EN_DRV_DEMOD_NUM
}EN_DRV_DEMOD_TYPE;

/**
 * \brief 
 * enumeration to indicate the tuner types.
 */
typedef enum
{	
	EN_DRV_TUNER_NONE,									/*!< Tuner (none)									*/
	
	//LVDS
	EN_DRV_TUNER_LVDS,

	//DVBT/T2/C
	EN_DRV_TUNER_SRP6265,								/*!< Tuner (sharp6265)								*/
	EN_DRV_TUNER_TUA6034,								/*!< Tuner (Comtech10cc)							*/
	EN_DRV_TUNER_TDA1611,								/*!< Tuner (TDA1611)								*/
	EN_DRV_TUNER_DTT8D1C,								/*!< Tuner (DTT8D1C)								*/
	EN_DRV_TUNER_MXL5007,								/*!< Tuner (MXL5007)								*/
	EN_DRV_TUNER_TDA18219,								/*!< Tuner (TDA18219)								*/
	EN_DRV_TUNER_RDA5880,								/*!< Tuner (RDA5880)								*/
	EN_DRV_TUNER_RDA5880E,								
	EN_DRV_TUNER_RDA5880P_T2,									
	EN_DRV_TUNER_MXL201,								/*!< Tuner (MXL201)									*/
	EN_DRV_TUNER_EN4020,								/*!< Tuner (EN4020)									*/
	EN_DRV_TUNER_R820T,									/*!< Tuner (R820T)									*/
	EN_DRV_TUNER_RT810S, 								/*!< Tuner (RT810S)									*/// NT316TB_TUNER_RT810S
	EN_DRV_TUNER_MXL603,								/*!< Tuner (MXL603)									*/
	EN_DRV_TUNER_FC5100,								/*!< Tuner (FC5100)									*/
	EN_DRV_TUNER_NM120,									/*!< Tuner (NM120)									*/
	//DVBS/S2
	EN_DRV_TUNER_IX2410 	= 0x8000,					/*!< Tuner (ix2410)									*/
	EN_DRV_TUNER_IX2476_S2,								/*!< Tuner (IX2476_S2)								*/
	EN_DRV_TUNER_AV2011_S2, 							/*!< Tuner (AV2011_S2)								*/
	EN_DRV_TUNER_BS7803_S2, 							/*!< Tuner (BS7803_S2)								*/
	EN_DRV_TUNER_IX2476,
	EN_DRV_TUNER_SRP6306,
	EN_DRV_TUNER_AVL_TUNER_S2,
	EN_DRV_TUNER_TC90517,
	EN_DRV_TUNER_DIB8096,
	EN_DRV_TUNER_DIB8096P,
	EN_DRV_TUNER_DIB7090P,
	EN_DRV_TUNER_MXL136RF,
	EN_DRV_TUNER_MXL101SF,
	EN_DRV_TUNER_SRP7903_S2, 							/*!< Tuner (SRP7903_S2)								*/
	EN_DRV_TUNER_C0045_S2, 							/*!< Tuner (C0045_S2)								*/
	EN_DRV_TUNER_SP720AVb_S2, 							/*!< Tuner (SP720AVb_S2)								*/
	EN_DRV_TUNER_GS4A_S2, 							/*!< Tuner (GS4A_S2)								*/
	EN_DRV_TUNER_RDA5815S_S2, 							/*!< Tuner (RDA5815S_S2)								*/
	EN_DRV_TUNER_RDA5815M_S2,//yli 20130222 add for rda5815m /*!< Tuner (RDA5815M_S2)								*/	
	EN_DRV_TUNER_RAON_RF_MTV600_S2,//yli 20130222 add for RAON_RF_MTV600  /*!< Tuner (RDA5815M_S2)								*/		
	EN_DRV_TUNER_M88TS2022_S2,					/*!< Tuner (M88TS2022_S2)		*/
	EN_DRV_TUNER_MT_AV2011_S2,	// yli ds3k
	EN_DRV_TUNER_MT_AV2026_S2,	// yli ds3k
	EN_DRV_TUNER_AVL_AV2011_S2,     // yli eds10530
#if (CONFIG_TUNER==ST_STV6120_S2)
       EN_DRV_TUNER_STV6120_S2, //add by thomas
#endif
	EN_DRV_TUNER_NUM
}EN_DRV_TUNER_TYPE;

/**
 * \brief
 * enumerate to indicate the hierarchical modulation.
 */
typedef enum
{
	EN_DRV_NIM_HIER_NONE,								/*!< None-Hierarchical								*/
	EN_DRV_NIM_HIER_1,									/*!< Hierarchical a = 1 							*/
	EN_DRV_NIM_HIER_2,									/*!< Hierarchical a = 2 							*/
	EN_DRV_NIM_HIER_4,									/*!< Hierarchical a = 4 							*/
	EN_DRV_NIM_HIER_NUM
}EN_DRV_NIM_HIERARCHY;


/**
 * \brief
 * enumerate to indicate the modulation mode.
 */
typedef enum
{
	EN_DRV_NIM_MOD_NONE,								/*!< Modulation unknown								*/
	EN_DRV_NIM_MOD_BPSK,								/*!< BPSK											*/	
	EN_DRV_NIM_MOD_QPSK,								/*!< QPSK											*/
	EN_DRV_NIM_MOD_QPSK_S2,								/*!< QPSK S2											*/	
	EN_DRV_NIM_MOD_8PSK,								/*!< 8PSK											*/
	EN_DRV_NIM_MOD_16APSK,								/*!< 16APSK											*/	
	EN_DRV_NIM_MOD_32APSK,								/*!< 32APSK											*/
	EN_DRV_NIM_MOD_QAM,									/*!< QAM   											*/
	EN_DRV_NIM_MOD_QAM4,								/*!< QAM4  											*/
	EN_DRV_NIM_MOD_QAM4_NR,								/*!< QAM4_NR										*/
	EN_DRV_NIM_MOD_QAM16,								/*!< QAM16											*/
	EN_DRV_NIM_MOD_QAM32,								/*!< QAM32 											*/
	EN_DRV_NIM_MOD_QAM64,								/*!< QAM64											*/
	EN_DRV_NIM_MOD_QAM128,								/*!< QAM128											*/
	EN_DRV_NIM_MOD_QAM256,								/*!< QAM256											*/
	EN_DRV_NIM_MOD_NUM
}EN_DRV_NIM_MOUDULATION;

/**
 * \brief
 * enumerate to indicate the guard interval.
 */
typedef enum
{
	EN_DRV_NIM_GI_NONE,									/*!< Guard interval unknown							*/
	EN_DRV_NIM_GI_19_256,								/*!< Guard interval = 19/256						*/
	EN_DRV_NIM_GI_19_128,								/*!< Guard interval = 19/128						*/
	EN_DRV_NIM_GI_1_128,								/*!< Guard interval = 1/128							*/
	EN_DRV_NIM_GI_1_32,									/*!< Guard interval = 1/32							*/
	EN_DRV_NIM_GI_1_16,									/*!< Guard interval = 1/16							*/
	EN_DRV_NIM_GI_1_8,									/*!< Guard interval = 1/8							*/
	EN_DRV_NIM_GI_1_4,									/*!< Guard interval = 1/4							*/
	EN_DRV_NIM_GI_PN420,								/*!< Guard interval = PN420 for DTMB				*/
	EN_DRV_NIM_GI_PN595,								/*!< Guard interval = PN595 for DTMB				*/
	EN_DRV_NIM_GI_PN945,								/*!< Guard interval = PN945 for DTMB				*/
	EN_DRV_NIM_GI_NUM
}EN_DRV_NIM_GI;

/**
 * \brief
 * enumerate to indicate the FEC.
 */
typedef enum
{
	EN_DRV_NIM_FEC_NONE,								/*!< FEC rate unknown								*/
	EN_DRV_NIM_FEC_1_2,									/*!< FEC rate 1/2									*/
	EN_DRV_NIM_FEC_2_3,									/*!< FEC rate 2/3									*/
	EN_DRV_NIM_FEC_3_4,									/*!< FEC rate 3/4									*/
	EN_DRV_NIM_FEC_5_6,									/*!< FEC rate 5/6									*/
	EN_DRV_NIM_FEC_6_7,									/*!< FEC rate 6/7									*/
	EN_DRV_NIM_FEC_7_8,									/*!< FEC rate 7/8									*/
	EN_DRV_NIM_FEC_8_9,									/*!< FEC rate 8/9									*/
	EN_DRV_NIM_FEC_1_4,									/*!< FEC rate 1/4									*/
	EN_DRV_NIM_FEC_1_3,									/*!< FEC rate 1/3									*/
	EN_DRV_NIM_FEC_2_5,									/*!< FEC rate 2/5									*/
	EN_DRV_NIM_FEC_3_5,									/*!< FEC rate 3/5									*/
	EN_DRV_NIM_FEC_4_5,									/*!< FEC rate 4/5									*/
	EN_DRV_NIM_FEC_9_10,								/*!< FEC rate 9/10									*/
	EN_DRV_NIM_FEC_NUM
}EN_DRV_NIM_FEC;

/**
 * \brief
 * enumerate to indicate the transmission mode.
 */
typedef enum
{
	EN_DRV_NIM_FFT_NONE,								/*!< FFT unknown									*/
	EN_DRV_NIM_FFT_1K,									/*!< FFT 1K mode									*/
	EN_DRV_NIM_FFT_2K,									/*!< FFT 2K mode									*/
	EN_DRV_NIM_FFT_4K,									/*!< FFT 4K mode									*/
	EN_DRV_NIM_FFT_8K,									/*!< FFT 8K mode									*/
	EN_DRV_NIM_FFT_16K,									/*!< FFT 16K mode									*/
	EN_DRV_NIM_FFT_32K									/*!< FFT 32K mode									*/
}EN_DRV_NIM_FFT;

/**
 * \brief
 * enumerate to indicate the TIM.
 */
typedef enum
{
	EN_DRV_NIM_TIM_240,									/*!< TIM_240										*/
	EN_DRV_NIM_TIM_720									/*!< TIM_720										*/
}EN_DRV_NIM_TIM;

/**
 * \brief
 * enumerate to indicate the carry mode.
 */
typedef enum
{
	EN_DRV_NIM_CARRYMODE_MULTI,							/*!< CARRYMODE_MULTI								*/
	EN_DRV_NIM_CARRYMODE_SINGLE							/*!< CARRYMODE_SINGLE								*/
}EN_DRV_NIM_CARRYMODE;

/**
 * \brief
 * enumerate to indicate the spectrun inversion mode.
 */
typedef enum
{
	EN_DRV_NIM_SPECTRUM_NORMAL,							/*!< Spectrun normal								*/
	EN_DRV_NIM_SPECTRUM_INVERSION,						/*!< Spectrun inversion								*/
	EN_DRV_NIM_SPECTRUM_AUTO,							/*!< Spectrun auto									*/
}EN_DRV_NIM_SPECTRUM;

/**
 * \brief
 * enumerate to indicate the DVB-C network types.
 */
typedef enum
{
	STTUNER_J83_NONE,									/*!< Network types unknown 							*/
	STTUNER_J83_A,										/*!< Annex A cable network							*/
	STTUNER_J83_B,										/*!< Annex B cable network							*/
	STTUNER_J83_C,										/*!< Annex C cable network							*/
}EN_DRV_NIM_J83;

/**
 * \brief
 * enumerate to indicate the channel bandwidth
 */
typedef enum
{
	EN_DRV_NIM_CHAN_BW_1_7M = 1,							/*!< Channel bandwidth 1.7M 						*/
	EN_DRV_NIM_CHAN_BW_5M   = 5,							/*!< Channel bandwidth 5M 							*/	
	EN_DRV_NIM_CHAN_BW_6M   = 6,							/*!< Channel bandwidth 6M 							*/
	EN_DRV_NIM_CHAN_BW_7M   = 7,							/*!< Channel bandwidth 7M 							*/
	EN_DRV_NIM_CHAN_BW_8M   = 8,							/*!< Channel bandwidth 8M 							*/
}EN_DRV_NIM_CHANNEL_BW;

/**
 * \brief
 * enumerate to indicate the Set channel mode
 */
typedef enum
{
	EN_DRV_NIM_SETCHANNEL_MODE_PLAY,					/*!< Set channel in play mode						*/
	EN_DRV_NIM_SETCHANNEL_MODE_NORMAL,					/*!< Set channel in normal mode						*/
	EN_DRV_NIM_SETCHANNEL_MODE_SCAN, 					/*!< Set channel in scanning 						*/
	EN_DRV_NIM_SETCHANNEL_MODE_BLIND, 					/*!< Set channel in blind scanning 					*/
	EN_DRV_NIM_SETCHANNEL_MODE_NUM
}EN_DRV_NIM_SETCHANNEL_MODE;

/**
 * \brief
 * enumerate to indicate the Blind scan mode
 */
typedef enum
{
	EN_DRV_NIM_BLIND_SCAN_MODE_QUICK,					/*!< Set blind scan in quick mode						*/
	EN_DRV_NIM_BLIND_SCAN_MODE_DETAIL, 					/*!< Set blind scan in detail mode 						*/
	EN_DRV_NIM_BLIND_SCAN_MODE_NUM
}EN_DRV_NIM_BLIND_SCAN_MODE;

/**
 * \brief
 * enumerate to indicate the Blind scan control mode
 */
typedef enum
{
	EN_DRV_NIM_BLIND_SCAN_CTL_MODE_START,					/*!< Set blind scan start 						*/
	EN_DRV_NIM_BLIND_SCAN_CTL_MODE_STOP, 					/*!< Set blind scan stop 						*/
	EN_DRV_NIM_BLIND_SCAN_CTL_MODE_SUSPEND,					/*!< Set blind scan suspend						*/
	EN_DRV_NIM_BLIND_SCAN_CTL_MODE_RESUME, 					/*!< Set blind scan resume 						*/	
	EN_DRV_NIM_BLIND_SCAN_CTL_MODE_NUM
}EN_DRV_NIM_BLIND_SCAN_CTL_MODE;

/**
 * \brief
 * enumerate to indicate the Blind scan range
 */
typedef enum
{
	EN_DRV_NIM_BLINDSCAN_RANGE_NORMAL = 0,					/*!< Set blind scan in normal range					*/
	EN_DRV_NIM_BLINDSCAN_RANGE_HIGH_BAND,					/*!< Set blind scan in high band					*/
	EN_DRV_NIM_BLINDSCAN_RANGE_LOW_BAND,					/*!< Set blind scan in high band 					*/
	EN_DRV_NIM_BLINDSCAN_RANGE_NUM
}EN_DRV_NIM_BLINDSCAN_RANGE;

/**
 * \brief
 * enumerate to indicate the priority mode
 */
typedef enum
{
	EN_DRV_NIM_PRIORITY_MODE_HP,						/*!< Set channel High priority (Hierarchical) 		*/
	EN_DRV_NIM_PRIORITY_MODE_LP,						/*!< Set channel Low priority (Hierarchical)  		*/
	EN_DRV_NIM_PRIORITY_MODE_NUM
}EN_DRV_NIM_PRIORITY_MODE;



/**
 * \brief
 * enumerate to indicate the wait lock mode
 */
typedef enum
{
	EN_DRV_NIM_WAIT_LOCK_MODE_NORMAL,					/*!< Wait lock in normal mode						*/			
	EN_DRV_NIM_WAIT_LOCK_MODE_SCAN,						/*!< Wait lock in scan mode							*/			
	EN_DRV_NIM_WAIT_LOCK_MODE_BLIND,					/*!< Wait lock in scan mode							*/			
}EN_DRV_NIM_WAIT_LOCK_MODE;

/**
 * \brief
 * enumerate to indicate the Polarization of NIM
 */
typedef enum
{
	EN_DRV_NIM_POLAR_ALL,								/*!< all available polarization.					*/
	EN_DRV_NIM_POLAR_HORIZONTAL,						/*!< horizontal polarization. 						*/
	EN_DRV_NIM_POLAR_VERTICAL,							/*!< vertical polarization. 						*/
	EN_DRV_NIM_POLAR_OFF,								/*!< No Polarization, LNB power will be off.		*/
#ifdef SUPPORT_LNB_POWER_14V_19V
	EN_DRV_NIM_POLAR_HORIZONTAL_19V,						/*!< horizontal polarization. 						*/
	EN_DRV_NIM_POLAR_VERTICAL_14V,							/*!< vertical polarization. 						*/
#endif
	EN_DRV_NIM_POLAR_NUM
} EN_DRV_NIM_POLAR;

/**
 * \brief
 *  enumerate to power control of NIM
 */
typedef enum
{
	EN_DRV_NIM_POWER_ON,								/*!< NIM power control mode , normal use mode		*/
	EN_DRV_NIM_STANDBY,									/*!< NIM power control mode , low frequency mode	*/
	EN_DRV_NIM_PWRCTRL_NUM
}EN_DRV_NIM_PWRCTRL;

/**
 * \brief
 *  enumerate to TS output mode
 */
typedef enum
{
	EN_DRV_NIM_TSOUT_MODE_SERIAL,						/*!< NIM TS output mode is for Serial				*/
	EN_DRV_NIM_TSOUT_MODE_PARALLEL,						/*!< NIM TS output mode is for Parallel				*/
	EN_DRV_NIM_TSOUT_MODE_DVBCI,						/*!< NIM TS output mode is for DVB-CI				*/
	EN_DRV_NIM_TSOUT_MODE_NUM
}EN_DRV_NIM_TSOUT_MODE;

/**
 * \brief
 *  enumerate to TS Clock mode
 */
typedef enum
{
	EN_DRV_NIM_TSCLOCK_MODE_NORMAL,						/*!< NIM TS clock mode is normal					*/
	EN_DRV_NIM_TSCLOCK_MODE_INVERSE,					/*!< NIM TS clock mode is inverse					*/
	EN_DRV_NIM_TSCLOCK_MODE_NUM
}EN_DRV_NIM_TSCLOCK_MODE;

/**
 * \brief
 *  enumerate to 22KTONE 
 */
typedef enum
{
	EN_DRV_NIM_22KTONE_OFF,								/*!< 22KTONE OFF									*/
	EN_DRV_NIM_22KTONE_ON,								/*!< 22KTONE ON										*/	
	EN_DRV_NIM_22KTONE_NUM
}EN_DRV_NIM_22KTONE;

/**
 * \brief
 *  eEnumerate to Tone Burst
 */
typedef enum
{
 	EN_DRV_NIM_TONE_BURST_OFF,							/*!< TONE BURST off									*/
	EN_DRV_NIM_TONE_BURST_UNMODULATED,					/*!< TONE BURST UNMODULATED							*/
 	EN_DRV_NIM_TONE_BURST_MODULATED,					/*!< TONE BURST MODULATED							*/
 	EN_DRV_NIM_TONE_BURST_NUM	
}EN_DRV_NIM_TONE_BURST;

/**
 * \brief
 *  enumerate to antenna power control
 */
typedef enum
{
 	EN_DRV_NIM_ANTENNA_PWR_OFF,							/*!< antenna power off								*/
 	EN_DRV_NIM_ANTENNA_PWR_ON,							/*!< antenna power on								*/
 	EN_DRV_NIM_ANTENNA_PWR_NUM 		
}EN_DRV_NIM_ANTENNA_PWR;

/**
 * \brief
 *  enumerate to strength format.
 */
typedef enum
{
	EN_DRV_NIM_STRENGTH_PERCENT,						/*!< Strength format is percent						*/
	EN_DRV_NIM_STRENGTH_AGC								/*!< Strength format is AGC value					*/
}EN_DRV_NIM_STRENGTH_FORMAT;

/**
 * \brief
 *  enumerate to quality format.
 */
typedef enum
{
	EN_DRV_NIM_QUALITY_PERCENT,							/*!< Quality format is percent						*/
	EN_DRV_NIM_QUALITY_BER,								/*!< Quality format is BER							*/
	EN_DRV_NIM_QUALITY_PER,								/*!< Quality format is BER							*/
	EN_DRV_NIM_QUALITY_CN,								/*!< Quality format is CN							*/
	EN_DRV_NIM_QUALITY_UCE								/*!< Quality format is UCE							*/
}EN_DRV_NIM_QUALITY_FORMAT;

/**
 * \brief
 *  enumerate to current NIM lock status
 */
typedef enum
{
	EN_DRV_NIM_STATUS_LOCKED,							/*!< NIM Locked a channel							*/
	EN_DRV_NIM_STATUS_UNLOCKED,							/*!< NIM Unlock any channel 						*/
	EN_DRV_NIM_STATUS_SCANNING,							/*!< NIM Scanning				 					*/
	EN_DRV_NIM_STATUS_TIMEOUT,							/*!< NIM Timeout for Wait lock signal				*/
	EN_DRV_NIM_STATUS_NOT_FOUND							/*!< NIM can't find any channel						*/
}EN_DRV_NIM_LOCK_STATUS;

/**
 * \brief
 *  NIM EventID definition.
 */
typedef enum
{
	EN_DRV_NIM_EVENT_LOCK,								/*!< The event to indicate that the NIM was locked			*/
	EN_DRV_NIM_EVENT_UNLOCK,							/*!< The event to indicate that the NIM was unlocked 		*/	
	EN_DRV_NIM_EVENT_SCAN_FAILED,						/*!< The event to indicate that the NIM scan was failed		*/
	EN_DRV_NIM_EVENT_SCAN_TIMEOUT,						/*!< The event to indicate that the NIM scan until timeout	*/
	EN_DRV_NIM_EVENT_SIGNAL_CHANGE,						/*!< The event to indicate that the signal was changed		*/	
	EN_DRV_NIM_EVENT_SCAN_NEXT,							/*!< The event to indicate that the NIM scan next frequency	*/	
	EN_DRV_NIM_EVENT_SCAN_STOP,
	EN_DRV_NIM_EVENT_ANTENNA_OVERLOAD,
#ifdef NEW_NIM_RULE
	EN_DRV_NIM_EVENT_UPDATE_STATUS,
#endif
	EN_DRV_NIM_EVENT_NUM,
}EN_DRV_NIM_EVENT_TYPE;

typedef enum
{
	EN_DRV_NIM_DVB_T2=0,
	EN_DRV_NIM_DVB_C,
	EN_DRV_NIM_DVB_T,
	EN_DRV_NIM_DVB_ISDBT,
	EN_DRV_NIM_DVB_DTMB,
	EN_DRV_NIM_DVB_S,
	EN_DRV_NIM_DVB_S2,
	EN_DRV_NIM_DVB_MAX
}EN_DRV_NIM_TunerSys;

typedef enum
{
    EN_DRV_NIM_IQSWAP_SETTING_000,						/*!< For I+ I- Q+ Q- */
    EN_DRV_NIM_IQSWAP_SETTING_010,						/*!< For I+ I- Q- Q+ */
    EN_DRV_NIM_IQSWAP_SETTING_100,						/*!< For I- I+ Q+ Q- */
    EN_DRV_NIM_IQSWAP_SETTING_110,						/*!< For I- I+ Q- Q+ */
    EN_DRV_NIM_IQSWAP_SETTING_001,						/*!< For Q+ Q- I+ I- */
    EN_DRV_NIM_IQSWAP_SETTING_011,						/*!< For Q- Q+ I+ I- */
    EN_DRV_NIM_IQSWAP_SETTING_101,						/*!< For Q+ Q- I- I+ */
    EN_DRV_NIM_IQSWAP_SETTING_111,						/*!< For Q- Q+ I- I+ */
    EN_DRV_NIM_IQSWAP_SETTING_SE_00,					/*!< For Single End Non Swap */
    EN_DRV_NIM_IQSWAP_SETTING_SE_01,					/*!< For Single End Swap */
	EN_DRV_NIM_IQSWAP_SETTING_ERR							/*!< Error Setting */
} EN_DRV_NIM_IQSWAP_SETTING_TYPE;

/**
 * \brief
 *  structure of NIM initial 
 */
typedef struct 
{
	os_mempool_handle			u32MemPoolHandle;				/*!< A memory pool handle for NIM module	*/	
	EN_DRV_NIM_NO				enNIMNo;						/*!< The number of NIM bus 					*/
	DRV_DeviceNameType			c162WSName;						/*!< The name of device 2WS 				*/
	EN_DRV_NIM_NETWORK			enNetMode;						/*!< The network mode 						*/	
	u8 							Demod2WSAddr;					/*!< Demod 2WS Address 						*/
	EN_DRV_DEMOD_TYPE			enDemodType;					/*!< Demod Type 							*/
	u8 							Tuner2WSAddr;					/*!< Tuner 2WS Address 						*/
	EN_DRV_TUNER_TYPE			enTunerType;					/*!< Tuner Type 							*/		
	EN_DRV_NIM_TSOUT_MODE		enTsOutMode;					/*!< TS output mode 						*/
	EN_DRV_NIM_TSCLOCK_MODE 	enTsClockMode;					/*!< TS clock mode 							*/		
	struct 
	{
		ST_GPIO					stNIM_Reset;					/*!< NIM Reset GPIO pin 					*/
		ST_GPIO				    stNIM_Sleep;					/*!< NIM Sleep ON/OFF GPIO pin 				*/
		ST_GPIO					stLNB_Power;					/*!< LNB Power ON/OFF GPIO pin				*/
		EN_DRV_GPIO_STATUS		enLNB_Power_Active;				/*!< LNB Power GPIO Active Voltage			*/
		EN_DRV_GPIO_STATUS		enLNB_Power_OFF;				/*!< LNB Power GPIO OFF Voltage			*/
		ST_GPIO					stLNB_Polar;					/*!< LNB Polar 18/13V GPIO pin				*/
		EN_DRV_GPIO_STATUS		enLNB_Polar_H;					/*!< LNB Polar 18(H) GPIO Voltage			*/
		EN_DRV_GPIO_STATUS		enLNB_Polar_V;					/*!< LNB Polar 13(V) GPIO Voltage			*/
		ST_GPIO					stAnt_Detector;					/*!< Antenna Overload Detector				*/	
		EN_DRV_GPIO_INTR_TRIGGER_CONDITION		enAnt_Det_Mode;	/*!< Antenna Overload Detector Trigger Mode	*/	
	#ifdef SUPPORT_LNB_REGULATOR
	#if(SUPPORT_LNB_REGULATOR)
		ST_GPIO					stRegulator_22KTone;
	#endif
	#endif
	};
	u32							u32SAR_ADC_Handle;				/*!< SAR_ADC Handle for RF AGC				*/
}ST_NIM_Init, *PST_NIM_Init;

/**
 * \brief
 *  structure of NIM hardware Config
 */
typedef struct 
{
	DRV_DeviceNameType			c162WSName;				/*!< 2WS bus 										*/
	EN_DRV_NIM_TSOUT_MODE		enTsOutMode;			/*!< TSoutMode										*/
	EN_DRV_NIM_TSCLOCK_MODE 	enTsClockMode;			/*!< TsClockMode 									*/
}ST_NIM_Config, *PST_NIM_Config;

/**
 * \brief
 *  structure of NIM open
 */
typedef struct 
{	
	u32				u32EVTHandle;						/*!< EVENT Handle 									*/
}ST_NIM_Open, *PST_NIM_Open;

/**
 * \brief
 *  structure of Multi-PLP parameters
 */
typedef struct 
{
	u8 u8Group_ID;										/*!< Group ID 										*/
	u8 u8Common_ID;										/*!< Common PLP ID									*/
	u8 u8Data_ID;										/*!< Data PLP ID 									*/
	u8 u8Reserved;										/*!< Reserved 										*/	
}ST_DRV_NIM_PLP_PAR, *PST_DRV_NIM_PLP_PAR;

/**
 * \brief
 *  structure of PLP Status
 */
typedef struct 
{
	u8 							u8NumofTSO;				/*!< The total number of TSO 						*/
	ST_DRV_NIM_PLP_PAR			stPLParams[256];		/*!< The structure of PLP Parameters				*/
}ST_DRV_NIM_PLP_STATUS, *PST_DRV_NIM_PLP_STATUS;

/**
 * \brief
 *  structure of NIM set channel parameter
 */
typedef struct
{	
	u32							u32Timeout;     		/*!< Lock Max. time, Reserved for future used 		*/
    u32							u32FreqKHz;				/*!< Scan frquency (KHz)							*/    
    s32							s32FreqOffsetKHz;		/*!< Scan offset frquency (KHz)						*/        
    u32							u32SymbRateKHz;			/*!< Scan symbol rate (KHz) 						*/        
    EN_DRV_NIM_ANTENNA_PWR		enAtennaPwr;			/*!< set antenna power 								*/
    EN_DRV_NIM_22KTONE			en22KTone;				/*!< set 22K tone 									*/
    EN_DRV_NIM_POLAR    		enPolar;				/*!< set polarization 								*/        
    EN_DRV_NIM_CHANNEL_BW		enBandwidth;			/*!< Scan Bandwidth 								*/
    EN_DRV_NIM_PRIORITY_MODE	enPriority;				/*!< Low / High Priority for Hierarchy Mode			*/        
	EN_DRV_NIM_SETCHANNEL_MODE	enSetChannelMode;		/*!< set channel mode : Normal / Scan / Blind		*/
    EN_DRV_NIM_TSCLOCK_MODE		enClkInv;				/*!< TS clock invert or not 						*/        
	EN_DRV_NIM_SPECTRUM			enSpectrum;	    		/*!< SPECTRUM TYPE									*/
    EN_DRV_NIM_MOUDULATION		enModulation;			/*!< MOUDULATION TYPE								*/	
	EN_DRV_NIM_HIERARCHY		enHierarchy;			/*!< Hierarchy 										*/
	EN_DRV_NIM_FEC				enFECRate;				/*!< FEC Rate 										*/
	EN_DRV_NIM_GI				enGI;					/*!< Guard interval									*/	
	EN_DRV_NIM_CARRYMODE		enCarryMode;			/*!< Carry Mode for DTMB							*/
	EN_DRV_NIM_TIM				enTIM;					/*!< TIM for DTMB									*/
	EN_DRV_NIM_TunerSys			enTunerSys;				/*!< Demod Type										*/
	ST_DRV_NIM_PLP_PAR          stPLPar;				/*!< The structure of PLP Parameters				*/
	u32							u32LoFreqKHz;			/*!< Lo frequency (KHz)								*/
	u32							u32UnicableIFKHz;		/*!< Unicable IF Frequency(DVB-S)	*/
}ST_NIM_CHANNEL_PAR, *PST_NIM_CHANNEL_PAR;

/**
 * \brief
 *  Structure of NIM channel status
 */
typedef struct
{    
    u32							u32CenterFreqKHz;		/*!< current lock frequency (KHz)										*/
    s32							s32FreqOffsetKHz;		/*!< offset range between setting frequency and locked frequency  (KHz)	*/
    u16							u32SymbRateKHz;			/*!< current lock symbol rate (KHz)										*/
    EN_DRV_NIM_LOCK_STATUS		enLocked;				/*!< current lock status 												*/
    EN_DRV_NIM_TSCLOCK_MODE		enClkInv;				/*!< TS clock invert or not 											*/	
	EN_DRV_NIM_SPECTRUM			enSpectrumInv;	    	/*!< SPECTRUM TYPE														*/
    EN_DRV_NIM_MOUDULATION		enModulation;			/*!< MOUDULATION TYPE													*/
	EN_DRV_NIM_HIERARCHY		enHierarchy;			/*!< Hierarchy 															*/
    EN_DRV_NIM_FEC				enCodeRate_HP;			/*!< HP code rate 														*/
    EN_DRV_NIM_FEC				enCodeRate_LP;			/*!< LP code rate 														*/
    EN_DRV_NIM_FFT				enFFTMode;				/*!< DVB-T transmition mode 											*/
	EN_DRV_NIM_GI				enGI;					/*!< Guard interval														*/
	EN_DRV_NIM_CARRYMODE		enCarryMode;			/*!< Carry Mode for DTMB												*/
	EN_DRV_NIM_FEC				enFECRate;				/*!< FEC Rate 															*/
	EN_DRV_NIM_TIM				enTIM;					/*!< TIM for DTMB														*/
	EN_DRV_NIM_PRIORITY_MODE	enPriority;				/*!< Low / High Priority												*/
	ST_DRV_NIM_PLP_STATUS		stPLPStatus;			/*!< The status of Multi-PLP			  								*/
	ST_DRV_NIM_PLP_PAR			stCurrentPLP;			/*!< The current TS of Multi-PLP			  							*/
	bool							bTMCCAlertFlag;			/*!<  TMCC ALERT for ISDB-T   TURE: flag ON FLASE: flag off/default	*/
}ST_NIM_CHANNEL_STATUS, *PST_NIM_CHANNEL_STATUS;

/**
 * \brief
 *  Structure of NIM PLP status
 */
typedef struct
{    
	ST_DRV_NIM_PLP_STATUS		stPLPStatus;			/*!< The status of Multi-PLP			  								*/
	ST_DRV_NIM_PLP_PAR			stCurrentPLP;			/*!< The current TS of Multi-PLP			  							*/
}ST_NIM_PLP_STATUS, *PST_NIM_PLP_STATUS;

/**
 * \brief
 *  Structure of NIM scan channel parameter
 */
typedef struct
{
    u32						u32StartFreqKHz;   			/* Scan range Max Freq (KHz). 						*/
    u32						u32EndFreqKHz;     			/* Scan range Min Freq (KHz). 						*/
    u32						u32StepKHz;					/* Scan range step Freq (KHz) 						*/
    u32						u32FreqKHz;					/* The first scan frquency (KHz)					*/
    EN_DRV_NIM_LOCK_STATUS 	enCurtScanLockSta;			/* Current Scan lock status							*/		
}ST_NIM_SCAN_PAR, *PST_NIM_SCAN_PAR;

/**
 * \brief
 *  Structure of NIM DiSEqC command packet
 */
typedef struct
{
	u16						u16MsgLen;	 				/*!< DiSEqC control message length 					*/
	u8						au8Msg[8];	 				/*!< DiSEqC control message 						*/
	EN_DRV_NIM_TONE_BURST	enToneBurst; 				/*!< Select Tone Burst Control Signal 				*/
}ST_NIM_DiSEqC_Sent_PAR, *PST_NIM_DiSEqC_Sent_PAR;

/**
 * \brief
 *  Structure of NIM DiSEqC command packet
 */
typedef struct
{
	u16						u16MsgLen;	 				/*!< DiSEqC control message length 					*/
	u8						au8Msg[8];	 				/*!< DiSEqC control message 						*/
}ST_NIM_DiSEqC_Recevie_PAR, *PST_NIM_DiSEqC_Recevie_PAR;

/**
 * \brief
 *  Structure of Signal Quality threshold
 */
typedef struct
{
	float fSignalLow;									/*!< Low level of signal threshold					*/
	float fSignalHigh;									/*!< High level of signal threshold					*/
}ST_NIM_SignalThreshold, *PST_NIM_SignalThreshold;

/**
 * \brief
 *  Structure of dummy-S parameters
 */
typedef struct
{
	u16 	u16LNBMHz;									/*!< The local frequency (MHz) of LNB				*/
	u16 	u16FreqMHz;									/*!< current lock frequency (MHz)					*/
	u16 	u16SymbolRateMHz;							/*!< current lock symbol rate (MHz)					*/
	bool	b8Polar_H;									/*!< The polarization of horizontal / vertical		*/
	bool	b8Control12V;								/*!< The voltage of 12V ON / OFF					*/
	bool	b8Tone22K;									/*!< 22K Tone ON / OFF								*/
}ST_DUMMY_S_DataBase, *PST_DUMMY_S_DataBase;

typedef struct
{
	u32 u32UnicableIFKHz;
} ST_NIM_SCAN_INFO;

//function define=======================
ErrorCode DRV_NIM_GetVersion (u8 *pu8VersionNum);
/*!\fn ErrorCode DRV_NIM_GetVersion (u8 *pu8VersionNum)
 * \brief
 * 			Get the Version number of NIM
 * 
 * \param	pu8VersionNum				(Output) Version string of NIM
 * 
 * \return	NIM Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_BAD_PARAMETER			One or more of the parameters was invalid
 */

ErrorCode DRV_NIM_Initialize (DRV_DeviceNameType DeviceName, PST_NIM_Init pstInit);
/*!\fn ErrorCode DRV_NIM_Initialize (DRV_DeviceNameType DeviceName, PST_NIM_Init pstInit)
 * \brief
 * 			Initialize the NIM device with pstInit setting
 * 
 * \param	DeviceName					(Input) Device name of NIM
 * \param	pstInit						(Input) Init parameters
 * 
 * \return	NIM Operation Error Code
 * \retval	ERROR_NO_ERROR				Operation Success
 * \retval	ERROR_BAD_PARAMETER			One or more of the parameters was invalid
 * \retval	ERROR_INITIALISED			A previous Init call has not been terminated or or already initialized
 * \retval	ERROR_NO_FREE_HANDLE		No free handle for the device
 * \retval	ERROR_NO_MEMORY				The memory allocate is fail
 */

ErrorCode DRV_NIM_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_NIM_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief
 * 			Terminate the NIM device driver
 * 
 * \param	DeviceName							(Input) Device name of NIM
 * \param	b8Force								(Input) Force terminate the NIM or not
 \code
 			TRUE								Terminate the NIM right now
 			FALSE								wait until all open handles close then terminate NIM
 \endcode
 * \return	NIM Operation Error Code
 * \retval	ERROR_NO_ERROR						Operation Success
 * \retval	ERROR_INITIALISED					A previous Init call has not been terminated or or already initialized 
 * \retval	EN_DRV_NIM_ERR_UNKNOW_DEVICE		No such device
 * \retval	EN_DRV_NIM_ERR_HANDLE_NOT_CLOSED	The device handle not close 
 */

ErrorCode DRV_NIM_Open (DRV_DeviceNameType DeviceName, PST_NIM_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_NIM_Open (DRV_DeviceNameType DeviceName, PST_NIM_Open pstOpen, u32 *pu32Handle)
 * \brief
 * 			Open the NIM device and associate it with a handle
 * 
 * \param	DeviceName							(Input) Device name of NIM
 * \param	pstOpen								(Input) Pointer to the opening parameter structure
 * \param	pu32Handle							(Output) The returned handle of the opened NIM driver
 * 
 * \return	NIM Operation Error Code
 * \retval	ERROR_NO_ERROR						Operation Success
 * \retval	ERROR_INITIALISED					A previous Init call has not been terminated or or already initialized 
 * \retval	ERROR_INVALID_HANDLE				Handle value is not valid
 * \retval	EN_DRV_NIM_ERR_UNKNOW_DEVICE		No such device 
 */

ErrorCode DRV_NIM_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_NIM_Close (u32* pu32Handle)
 * \brief
 * 			Close NIM device associated with a handle
 * 
 * \param	pu32Handle							(Input) An open handle number of the NIM device
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR						Operation Success
 * \retval	ERROR_INVALID_HANDLE				Handle value is not accepted
 */

ErrorCode DRV_NIM_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_NIM_PWRCTRL enPwrCtrl, bool b8Force);
/*!\fn ErrorCode DRV_NIM_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_NIM_PWRCTRL enPwrCtrl, bool b8Force)
 * 
 * \brief
 * 			Control the power mode of NIM device
 *  
 * \param	DeviceName							(Input) Device name of NIM
 * \param	enPwrCtrl							(Input) Setting the NIM device power mode
 * \param	b8Force								(Input) Force terminate the NIM or not
 * \code
 *			TRUE								Terminate the NIM right now
 *			FALSE								Waiting until all opened handles was closed then terminate NIM
 * \endcode
 * 
 \code
 	enPwrCtrl									description
 	-------------------							--------------------------
 	EN_DRV_NIM_POWER_ON							NIM device in power on mode
 	EN_DRV_NIM_STANDBY							NIM device in standby mode
 \endcode
 * \return	NIM Operation Error Code
 * \retval	ERROR_NO_ERROR						Operation Success
 * \retval	ERROR_BAD_PARAMETER					One or more of the parameters was invalid
 * \retval	EN_DRV_NIM_ERR_UNKNOW_DEVICE		No such device
 * \retval	EN_DRV_NIM_ERR_HANDLE_NOT_CLOSED	The device handle not close 
 */

ErrorCode DRV_NIM_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_NIM_Lock (u32 u32Handle, bool b8Lock)
 * \brief 
 *			Set the NIM device to protection mode.\n	   
 *			No other handle can read the NIM device unless unlock
 *
 * \param  	u32Handle							(Input) An open handle number of the NIM device
 * \param  	b8Lock								(Input) Lock the NIM device or not
 \code
 		   	TRUE 								Lock the NIM
 		   	FALSE 								Unlock the NIM
 \endcode
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR						Operation Success
 * \retval 	ERROR_INVALID_HANDLE				Handle value is not accepted
 */

ErrorCode DRV_NIM_SetConfig (u32 u32Handle, PST_NIM_Config pstPara);
/*!\fn ErrorCode DRV_NIM_SetConfig (u32 u32Handle, PST_NIM_Config pstPara)
 * \brief 
 *        	Set the config data of NIM device 
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	pstPara       						(Input) The config parameter of NIM device
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_GetConfig (u32 u32Handle, PST_NIM_Config pstPara);
/*!\fn ErrorCode DRV_NIM_GetConfig (u32 u32Handle, PST_NIM_Config pstPara)
 * \brief 
 *        	Get the config data of NIM device
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	pstPara       						(Output) The config parameter of NIM device
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_SetChannel (u32 u32Handle, PST_NIM_CHANNEL_PAR pstChannelPar);
/*!\fn ErrorCode DRV_NIM_SetChannel (u32 u32Handle, PST_NIM_CHANNEL_PAR pstChannelPar)
 * \brief 
 *        	Set the Channel parameter to the NIM device  
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	pstChannelPar 						(Input) Pointer to the channel parameters
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_GetBlindScanNextFreq (u32 u32Handle, PST_NIM_SCAN_PAR pstScanPar, u32 *pu32NextFreqKHz);
/*!\fn ErrorCode DRV_NIM_GetBlindScanNextFreq (u32 u32Handle, PST_NIM_SCAN_PAR stScanPar, u32 *pu32NextFreqKHz)
 * \brief 
 *        	Get next scan channel frequency   
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	stScanPar 							(Input) Pointer to the scan parameters
 * \param 	pu32NextFreqKHz 					(Output) Pointer to return next scan channel frequency 
 * 
 * \return 	NIM Operation Error Code
 * \retval	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_BlindScanControl (u32 u32Handle, EN_DRV_NIM_BLIND_SCAN_MODE enScanMode, EN_DRV_NIM_BLIND_SCAN_CTL_MODE enCtrlMode, EN_DRV_NIM_BLINDSCAN_RANGE enRange, ST_NIM_SCAN_INFO *pstNimScanInfo);
/*!fn ErrorCode DRV_NIM_BlindScanControl (u32 u32Handle, EN_DRV_NIM_BLIND_SCAN_MODE enScanMode, EN_DRV_NIM_BLIND_SCAN_CTL_MODE enCtrlMode, EN_DRV_NIM_BLINDSCAN_RANGE enRange)
 * \brief 
 *        	Set blind scan   
 * 
 * \param 	u32Handle     							(Input) An open handle number of the NIM device
 * \param 	enScanMode 								(Input) Pointer to the scan parameters
 * \code
 *			EN_DRV_NIM_BLIND_SCAN_MODE_QUICK  		QUICK SCAN
 *			EN_DRV_NIM_BLIND_SCAN_MODE_DETAIL   	DETAIL SCAN
 * \param 	enCtrlMode 								(Input) Pointer to the control parameters
 * \code
 *			EN_DRV_NIM_BLIND_SCAN_CTL_MODE_START  	START
 *			EN_DRV_NIM_BLIND_SCAN_CTL_MODE_STOP    	STOP 
 *			EN_DRV_NIM_BLIND_SCAN_CTL_MODE_SUSPEND  SUSPEND
 *			EN_DRV_NIM_BLIND_SCAN_CTL_MODE_RESUME   RESUME  
 * \endcode 
 * \return 	NIM Operation Error Code
 * \retval	ERROR_NO_ERROR               			Operation Success 
 * \retval 	ERROR_NIM_NETWORK_TYPE            		Network type is not accepted
 * \retval 	ERROR_INVALID_HANDLE            		Handle value is not accepted
 */


ErrorCode DRV_NIM_SetAbort (u32 u32Handle, u16 u16Abort);
/*!\fn ErrorCode DRV_NIM_SetAbort (u32 u32Handle, u16 u16Abort)
 * \brief 
 *      	Unlock current channel or stop scan  
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	u16Abort 							(Input) Abort the NIM or not
 *
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_SetNIMTaskState (u32 u32Handle, u8 u8data);
/*!fn ErrorCode DRV_NIM_SetNIMTaskState  (u32 u32Handle, u8 u8data)
 * \brief 
 *        Unlock current channel or stop scan  
 * 
 * \param u32Handle     (Input) An open handle, as returned by the Open function
 * \param u8data 		(Input)  NIM Task state
   \code
	0  : EN_DRV_NIM_TASK_MONITOR
	1  : EN_DRV_NIM_TASK_WAIT

   \endcode
 * 
 * \return NIM Operation Error Code
 * \retval ERROR_NO_ERROR               Operation Success
 * \retval ERROR_BAD_PARAMETER         One or more of the parameters was invalid
 * \retval ERROR_INVALID_HANDLE            Handle value is not accepted
 */


ErrorCode DRV_NIM_CheckLock (u32 u32Handle, EN_DRV_NIM_LOCK_STATUS *penLockStatus);
/*!\fn ErrorCode DRV_NIM_CheckLock (u32 u32Handle, EN_DRV_NIM_LOCK_STATUS *penLockStatus)
 * \brief 
 *        	Check the NIM lock status 
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	penLockStatus						(Output) Pointer to return the lock status
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success 
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_WaitLock (u32 u32Handle, EN_DRV_NIM_WAIT_LOCK_MODE enWaitLockMode, EN_DRV_NIM_LOCK_STATUS *penLockStatus);
/*!\fn ErrorCode DRV_NIM_WaitLock (u32 u32Handle, EN_DRV_NIM_WAIT_LOCK_MODE enWaitLockMode, EN_DRV_NIM_LOCK_STATUS *penLockStatus);
 * \brief 
 *        	Wait NIM lock with Timer 
 * 
 * \param 	u32Handle      						(Input) An open handle number of the NIM device
 * \param 	enWaitLockMode 						(Input) Select wait lock mode
 *  \code
 *			EN_DRV_NIM_WAIT_LOCK_MODE_NORMAL  	Normal Mode 
 *			EN_DRV_NIM_WAIT_LOCK_MODE_SCAN 		Scan Mode
 *  \endcode
 * \param 	penLockStatus	 					(Output) Pointer to return the lock status
 \code
 			EN_DRV_NIM_STATUS_LOCKED			The status of lock
			EN_DRV_NIM_STATUS_UNLOCKED			The status of unlock
 			EN_DRV_NIM_STATUS_SCANNING			The status of scanning
 			EN_DRV_NIM_STATUS_TIMEOUT			The status of time out
 			EN_DRV_NIM_STATUS_NOT_FOUND			The status of channel not found
 \endcode 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 * 
 */

ErrorCode DRV_NIM_GetChannelStatus (u32 u32Handle, PST_NIM_CHANNEL_STATUS pstStatus);
/*!\fn ErrorCode DRV_NIM_GetChannelStatus (u32 u32Handle, PST_NIM_CHANNEL_STATUS pstStatus)
 * \brief 
 *        	Get current channel status
 * 
 * \param 	u32Handle      						(Input) An open handle number of the NIM device
 * \param 	pstStatus	 	 					(Output) Pointer to return the ST_NIM_CHANNEL_STATUS status
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_GetStrength (u32 u32Handle, EN_DRV_NIM_STRENGTH_FORMAT enStrengthFormat, float *pfStrength);
/*!\fn ErrorCode DRV_NIM_GetStrength (u32 u32Handle, EN_DRV_NIM_STRENGTH_FORMAT enStrengthFormat, float *pfStrength)
 * \brief 
 *        	Get current channel signal strength
 * 
 * \param 	u32Handle      						(Input) An open handle number of the NIM device
 * \param 	enStrengthFormat 					(Input) Select return strength format
 \code
 			EN_DRV_NIM_STRENGTH_PERCENT  		0 ~ 100 
 			EN_DRV_NIM_STRENGTH_AGC 			IF AGC Value 0x00 ~ 0xFF
 \endcode 
 * \param 	pfStrength	 						(Output) Pointer to return the strength level
 *
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success 
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_GetQuality (u32 u32Handle, EN_DRV_NIM_QUALITY_FORMAT enQualityFormat, float *pfQuality);
/*!\fn ErrorCode DRV_NIM_GetQuality (u32 u32Handle, EN_DRV_NIM_QUALITY_FORMAT enQualityFormat, float *pfQuality)
 * \brief 
 *        	Get current channel signal quality
 * 
 * \param 	u32Handle      						(Input) An open handle number of the NIM device
 * \param 	enQualityFormat 					(Input) Select return quality format
 \code
 			EN_DRV_NIM_QUALITY_PERCENT  		0 ~ 100 
 			EN_DRV_NIM_QUALITY_BER 				Bit Error Rate
 			EN_DRV_NIM_QUALITY_CN  				Signal Noise Ratio 
 			EN_DRV_NIM_QUALITY_UCE 				Uncorrectable Value
 \endcode
 * \param 	pfQuality							(Output) Pointer to return the quality level
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_SetThresholdList ( u32 u32Handle, EN_DRV_NIM_QUALITY_FORMAT enQualityFormat, PST_NIM_SignalThreshold pstThresholdList);
/*!\fn ErrorCode DRV_NIM_SetThresholdList ( u32 u32Handle, EN_DRV_NIM_QUALITY_FORMAT enQualityFormat, PST_NIM_SignalThreshold pstThresholdList)
 * \brief 
 *        	Set the list of signal quality thresholds to be used for notification of signal strength fluctuations. 
 * 
 * \param 	u32Handle      						(Input) An open handle number of the NIM device
 * \param 	enQualityFormat						(Input) Select input quality format in stThresholdList
 \code
 			EN_DRV_NIM_QUALITY_PERCENT  		0 ~ 100 
 			EN_DRV_NIM_QUALITY_BER 				Bit Error Rate
 			EN_DRV_NIM_QUALITY_CN  				Signal Noise Ratio 
 			EN_DRV_NIM_QUALITY_UCE 				Uncorrectable Value
 \endcode 
 * \param 	pstThresholdList 					(Input) Point to the ST_NIM_SignalThreshold structure.
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success 
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_GetThresholdList ( u32 u32Handle, EN_DRV_NIM_QUALITY_FORMAT *enQualityFormat, PST_NIM_SignalThreshold pstThresholdList);
/*!\fn ErrorCode DRV_NIM_GetThresholdList ( u32 u32Handle, EN_DRV_NIM_QUALITY_FORMAT *enQualityFormat, PST_NIM_SignalThreshold pstThresholdList)
 * \brief 
 *        	Get the list of signal quality thresholds
 * 
 * \param 	u32Handle      						(Input) An open handle number of the NIM device
 * \param 	enQualityFormat 					(Output) Pointer to return the quality format
 \code
 			EN_DRV_NIM_QUALITY_PERCENT  		0 ~ 100 
 			EN_DRV_NIM_QUALITY_BER 				Bit Error Rate
 			EN_DRV_NIM_QUALITY_CN  				Signal Noise Ratio 
 			EN_DRV_NIM_QUALITY_UCE 				Uncorrectable Value
 \endcode 
 * \param 	pstThresholdList					(Output) Point to the  ST_NIM_SignalThreshold structure
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_SetPolar (u32 u32Handle, EN_DRV_NIM_POLAR enPolar);
/*!\fn ErrorCode DRV_NIM_SetPolar (u32 u32Handle, EN_DRV_NIM_POLAR enPolar)
 * \brief 
 *        	Set Polarization 
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	enPolar 							(Input) Polar HORIZONTAL or VERTICAL
 \code
 			EN_DRV_NIM_POLAR_ALL  				HORIZONTAL and VERTICAL 
 			EN_DRV_NIM_POLAR_HORIZONTAL 		HORIZONTAL
 			EN_DRV_NIM_POLAR_VERTICAL  			VERTICAL
 			EN_DRV_NIM_POLAR_OFF 				OFF
 \endcode 
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success 
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 * 
 */

ErrorCode DRV_NIM_SetTone (u32 u32Handle, EN_DRV_NIM_22KTONE en22KTone);
/*!\fn ErrorCode DRV_NIM_SetTone (u32 u32Handle, EN_DRV_NIM_22KTONE en22KTone)
 * \brief 
 *        	Set 22K tone
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	en22KTone 							(Input) 22K ON or OFF
 \code
 			EN_DRV_NIM_22KTONE_OFF  			22K Tone OFF
 			EN_DRV_NIM_22KTONE_ON 				22K Tone ON
 \endcode 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 * 
 */

ErrorCode DRV_NIM_SetAntennaPwr (u32 u32Handle, EN_DRV_NIM_ANTENNA_PWR enAtennaPwr);
/*!\fn ErrorCode DRV_NIM_SetAntennaPwr (u32 u32Handle, EN_DRV_NIM_ANTENNA_PWR enAtennaPwr)
 * \brief 
 *        	Set LNB/Antenna power
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	enAtennaPwr 						(Input) Antenna Power ON or OFF 
 \code
 			EN_DRV_NIM_ANTENNA_PWR_OFF  		ANTENNA POWER OFF
 			EN_DRV_NIM_ANTENNA_PWR_ON 			ANTENNA POWER ON
 \endcode 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_ReadDiSEqC (u32 u32Handle, PST_NIM_DiSEqC_Recevie_PAR pstDiSEqCMsg);
/*!\fn ErrorCode DRV_NIM_ReadDiSEqC (u32 u32Handle, PST_NIM_DiSEqC_Recevie_PAR pstDiSEqCMsg)
 * \brief 
 *        	Read the response of DiSEqc 2.x.
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	pstDiSEqCMsg 						(Output) Pointer to DiSEqC Recevie structure
 * 
 * \return NIM Operation Error Code
 * \retval ERROR_NO_ERROR               		Operation Success
 * \retval ERROR_INVALID_HANDLE            		Handle value is not accepted
 */

ErrorCode DRV_NIM_WriteDiSEqC (u32 u32Handle, PST_NIM_DiSEqC_Sent_PAR pstDiSEqCMsg);
/*!\fn ErrorCode DRV_NIM_WriteDiSEqC (u32 u32Handle, PST_NIM_DiSEqC_Sent_PAR pstDiSEqCMsg)
 * \brief 
 *        Write DiSEqC message or Tone signals. it uses Demod IC for generating DiSEqC Tones
 * 
 * \param u32Handle     						(Input) An open handle number of the NIM device
 * \param pstDiSEqCMsg 							(Output) Pointer to DiSEqC Sent structure
 * 
 * \return NIM Operation Error Code
 * \retval ERROR_NO_ERROR               		Operation Success
 * \retval ERROR_INVALID_HANDLE            		Handle value is not accepted
 */

ErrorCode DRV_NIM_ReadReg (u32 u32Handle, u16 u16RegIndex, u8 *pu8Buf, u16 u16Len);
/*!\fn ErrorCode DRV_NIM_ReadReg (u32 u32Handle, u16 u16RegIndex, u8 *pu8Buf, u16 u16Len)
 * \brief 
 *        Read the NIM reg data via 2WS bus   
 * 
 * \param u32Handle     						(Input) An open handle number of the NIM device
 * \param u16RegIndex   						(Input) Write the register which one to write
 * \param pu8Buf       							(Input) Point to the Read data buffer
 * \param u16Len       							(Input) Read data length
 * 
 * \return NIM Operation Error Code
 * \retval ERROR_NO_ERROR               		Operation Success
 * \retval ERROR_INVALID_HANDLE            		Handle value is not accepted
 */

ErrorCode DRV_NIM_WriteReg (u32 u32Handle, u16 u16RegIndex, u8 *pu8Buf, u16 u16Len);
/*!\fn ErrorCode DRV_NIM_WriteReg (u32 u32Handle, u16 u16RegIndex, u8 *pu8Buf, u16 u16Len)
 * \brief 
 *        Write the NIM reg data via 2WS bus
 * 
 * \param u32Handle     						(Input) An open handle number of the NIM device
 * \param u16RegIndex   						(Input) Write the register which one to write
 * \param pu8Buf       							(Input) Point to the Write data buffer
 * \param u16Len       							(Input) Write data length
 * 
 * \return NIM Operation Error Code
 * \retval ERROR_NO_ERROR               		Operation Success
 * \retval ERROR_INVALID_HANDLE            		Handle value is not accepted
 * 
 */

ErrorCode DRV_NIM_Get_Min_Tuner_FreqKHz (u32 u32Handle, u32 *pu32MinFreqKHz);
/*!\fn ErrorCode DRV_NIM_Get_Min_Tuner_FreqKHz (u32 u32Handle, u32 *pu32MinFreqKHz)
 * \brief 
 *        	Get the minimum frequency of tuner 
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	pu32MinFreqKHz    					(Output) Pointer to return the minimum frequency of tuner
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 * 
 */

ErrorCode DRV_NIM_Get_Max_Tuner_FreqKHz (u32 u32Handle, u32 *pu32MaxFreqKHz);
/*!\fn ErrorCode DRV_NIM_Get_Max_Tuner_FreqKHz (u32 u32Handle, u32 *pu32MaxFreqKHz)
 * \brief 
 *        Get the maximum frequency of tuner 
 * 
 * \param 	u32Handle     						(Input) An open handle number of the NIM device
 * \param 	pu32MaxFreqKHz    					(Output) Pointer to return the maximum frequency of tuner
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 * 
 */

ErrorCode DRV_NIM_Monitor (u32 u32Handle);
/*!fn ErrorCode DRV_NIM_Monitor (u32 u32Handle)
 * \brief 
 *        Monitor NIM status.
 * 
 * \param u32Handle     (Input) An open handle, as returned by the Open function
 * 
 * \return NIM Operation Error Code
 * \retval ERROR_NO_ERROR               Operation Success
 * \retval ERROR_BAD_PARAMETER			One or more of the parameters was invalid
 * \retval ERROR_INVALID_HANDLE         Handle value is not accepted
 * 
 */

ErrorCode DRV_NIM_GetPLPStatus (u32 u32Handle, PST_NIM_PLP_STATUS pstStatus);
/*!\fn ErrorCode DRV_NIM_GetPLPStatus (u32 u32Handle, PST_NIM_PLP_STATUS pstStatus)
 * \brief 
 *        	Get PLP Status
 * 
 * \param 	u32Handle      						(Input) An open handle number of the NIM device
 * \param 	pstStatus	 	 					(Output) Pointer to return the PST_NIM_PLP_STATUS status
 * 
 * \return 	NIM Operation Error Code
 * \retval 	ERROR_NO_ERROR               		Operation Success
 * \retval  ERROR_BAD_PARAMETER         		One or more of the parameters was invalid
 * \retval 	ERROR_INVALID_HANDLE            	Handle value is not accepted
 */

ErrorCode DRV_NIM_SetIQSwap (EN_DRV_NIM_NO enNIMNo, EN_DRV_NIM_IQSWAP_SETTING_TYPE enIQSwapSetting);
/*!fn ErrorCode DRV_NIM_SetIQSwap (EN_DRV_NIM_NO enNIMNo, EN_DRV_NIM_IQSWAP_SETTING_TYPE enIQSwapSetting)
 * \brief 
 *        Set IQ Swap setting
 * 
 * \param enNIMNo      	(Input) Device number of NIM
 * \param enIQSwapSetting	(Input) IQ Swap setting value
 * 
 * \return NIM Operation Error Code
 * \retval ERROR_NO_ERROR               Operation Success
 * \retval ERROR_BAD_PARAMETER         	One or more of the parameters was invalid
 * \retval ERROR_INVALID_HANDLE         Handle value is not accepted
 * 
 */

#if (CONFIG_CHIP_MODLE == NT78320)  
#define AMAY_320S_NIM_TEST
#ifdef AMAY_320S_NIM_TEST
void DRV_NIM_GET_HANDLE (u32 *u32Pass_Handle);
void DRV_NIM_GET_BLIND_SCAN(EN_DRV_NIM_SETCHANNEL_MODE *EN_SCAN_MODE);
void DRV_NIM_GET_SRS(void);
void DRV_NIM_SET_BLIND_Rrange(u32 u32Start_Freq, u32 u32Stop_Freq);
#endif
#endif

//#if DUAL_NIM  //add by wujiang
u32 DRV_NIM_GetGPIOHandle(EN_DRV_NIM_NO enNIMNo);//gf_test

#endif //#ifndef __DRV_NIM_H__

