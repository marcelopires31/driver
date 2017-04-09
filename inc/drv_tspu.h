//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide TSPU Control 
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

#ifndef	__DRV_TSPU_H__
#define	__DRV_TSPU_H__

#include "def_type.h"
#include "def_err.h"
/*
 * Brief: DRV_TSPU global define.
 */
//#define DRV_TSPU_CONTROL_PCR_HANDLE                                 /*!< PCR Handle Control by DRV_TSPU                           */          
#define DRV_TSPU_FILT_SECTION_PATTERN_LENGTH            (12)        /*!< The maximum length of Section filter Match & Mask pattern  */
#define DRV_TSPU_FILT_PES_PATTERN_LENGTH                 (4)        /*!< The maximum length of PES filter Match & Mask pattern      */
#define DRV_TSPU_FILT_ES_PATTERN_LENGTH                  (4)        /*!< The maximum length of ES filter Match & Mask pattern       */
#define DRV_TSPU_FILT_MM_ES_PATTERN_LENGTH               (4)        /*!< The maximum length of MM ES filter Match & Mask patter     */
#define DRV_TSPU_DESC_DVB_CSA_CW_LENGTH                  (8)        /*!< The length of DVB CSA Control Word                         */
#define DRV_TSPU_DESC_DVB_CSA3_CW_LENGTH                (16)        /*!< The length of DVB CSA3 Control Word                        */
#define DRV_TSPU_DESC_CI_PLUS_AES_CW_LENGTH             (16)        /*!< The length of CI Plus AES Control Word                     */
#define DRV_TSPU_DESC_CI_PLUS_DES_CW_LENGTH              (8)        /*!< The length of CI Plus DES Control Word                     */
#define DRV_TSPU_DESC_CA_AES_CW_LENGTH                  (16)        /*!< The length of CA AES Control Word                          */
#define DRV_TSPU_DESC_CA_DES_CW_LENGTH                   (8)        /*!< The length of CA DES Control Word                          */
#define DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH                (8)        /*!< The length of ATSC TDES Control Word                       */
#define DRV_TSPU_DESC_ISDB_MULTI2_DATA_CW_LENGTH         (8)        /*!< The length of ISDB MULTI2 Data Control Word                */
#define DRV_TSPU_DESC_ISDB_MULTI2_SYSTEM_CW_LENGTH      (32)        /*!< The length of ISDB MULTI2 System Control Word              */
#define DRV_TSPU_CRYPTO_MULTI2_CTRL_MAX_ROUND_NO		(256)		/*!< The maximum number of Multi2 round for Crypto-Engine       */

/*!
 * \brief 
 * TSPU Error code definition.
 */
enum
{
	ERROR_TSPU_DEV_NAME     = ERROR_BASE_DRV_TSPU,		            /*!< Device Name Error                                          */
	ERROR_TSPU_DEV_RESOURCE,		                                /*!< TSPU don't have device resource                            */
	ERROR_TSPU_PID_IS_ENABLE,		                                /*!< PID is enable                                              */
	ERROR_TSPU_FILT_IS_START,		                                /*!< Filter is start                                            */
	ERROR_TSPU_CLOSED_HANDLE,	                                    /*!< Input Handle is closed.                                    */
	ERROR_TSPU_BUF_TOO_SMALL,	                                    /*!< Input buffer size too small to get section/PES.            */
	ERROR_TSPU_FULLNESS_TOO_SMALL,	                                /*!< ring buffer fullness too small, can't have section/PES data*/
	ERROR_TSPU_SEMAPHORE_FAIL,	                                    /*!< semaphore fail, template error code before OS ready        */
	ERROR_TSPU_EVENT_FAIL,	                                        /*!< event fail, template error code before OS ready            */
	ERROR_TSPU_UNSUPPORT,	                                        /*!< Un-support Filter Type                                     */
	ERROR_TSPU_PCR_NOT_READY,	                                    /*!< PCR data not ready                                         */
	ERROR_TSPU_PTS_NOT_READY,	                                    /*!< PTS data not ready                                         */
	ERROR_TSPU_HW_CONFIRM,	                                        /*!< TSPU confirm hardware setting fail                         */
	ERROR_TSPU_PCR_IS_ENABLE,		                                /*!< PCR is enable                                              */
	ERROR_TSPU_TSI_SEND_DATA,		                                /*!< TSI Send Data fail                                         */
	ERROR_TSPU_TSO_IS_ENABLE,		                                /*!< TSO is enable                                              */
	ERROR_TSPU_DESC_CWB_IS_ENABLE,		                            /*!< DESC Control Word Bank is enable                           */
	ERROR_TSPU_DESC_PID_IS_ENABLE,		                            /*!< DESC PID is enable                                         */
	ERROR_TSPU_TIMESTAMP_IS_ENABLE,		                            /*!< Timestamp is enable                                         */
};

/**
 * \brief
 * enumurate to indicate the tspu source type
 */
typedef enum
{
    EN_DRV_TSPU_SOURCE_TYPE_NONE,                                   /*!< None Input                                 */
    EN_DRV_TSPU_SOURCE_TYPE_DEMOD,                                  /*!< Demod Input                                */
	EN_DRV_TSPU_SOURCE_TYPE_TSI_DMA0,                               /*!< TSI DMA Input 0                            */
	EN_DRV_TSPU_SOURCE_TYPE_TSI_DMA1,                               /*!< TSI DMA Input 1                            */
    EN_DRV_TSPU_SOURCE_TYPE_NIM_0,                                  /*!< NIM0 Input                                 */
    EN_DRV_TSPU_SOURCE_TYPE_NIM_1,                                  /*!< NIM1 Input                                 */
    EN_DRV_TSPU_SOURCE_TYPE_NIM_2,                                  /*!< NIM2 Input                                 */
    EN_DRV_TSPU_SOURCE_TYPE_NIM_3,                                  /*!< NIM3 Input                                 */
    EN_DRV_TSPU_SOURCE_TYPE_NUM,
}EN_DRV_TSPU_SOURCE_TYPE;

/**
 * \brief
 * enumurate to indicate the tspu input packet 188 or 192 type
 */

typedef enum
{
    EN_DRV_TSPU_TSI_PACKET_188,                                     /*!< TSI 188 Byte Mode                          */
    EN_DRV_TSPU_TSI_PACKET_192,                                     /*!< TSI 192 Byte Mode                          */
    EN_DRV_TSPU_TSI_PACKET_NUM,
}EN_DRV_TSPU_TSI_PACKET;

/**
 * \brief
 * enumurate to indicate the tspu output type
 */

typedef enum
{
    EN_DRV_TSPU_OUTPUT_PATH_TSO_0,                                  /*!< TSO 0 Output Path                          */
    EN_DRV_TSPU_OUTPUT_PATH_TSO_1,                                  /*!< TSO 1 Output Path                          */
    EN_DRV_TSPU_OUTPUT_PATH_NUM,
}EN_DRV_TSPU_OUTPUT_PATH;

/**
 * \brief
 * enumurate to indicate the crypto-engine block cipher mode
 */
typedef enum
{
    EN_DRV_TSPU_CRYPTO_BLOCK_CIPHER_CBC,                            /*!< Crypto-Engine used CBC mode                */
    EN_DRV_TSPU_CRYPTO_BLOCK_CIPHER_ECB,                            /*!< Crypto-Engine used ECB mode                */
    EN_DRV_TSPU_CRYPTO_BLOCK_CIPHER_NUM,
}EN_DRV_TSPU_CRYPTO_BLOCK_CIPHER;

/**
 * \brief
 * enumurate to indicate the crypto-engine short block mode
 */
typedef enum
{
    EN_DRV_TSPU_CRYPTO_SHORT_BLOCK_ENCODE,                          /*!< Crypto-Engine encode short block           */
    EN_DRV_TSPU_CRYPTO_SHORT_BLOCK_BYPASS,                          /*!< Crypto-Engine bypass shor block            */
    EN_DRV_TSPU_CRYPTO_SHORT_BLOCK_NUM,
}EN_DRV_TSPU_CRYPTO_SHORT_BLOCK;

/**
 * \brief
 * enumurate to indicate the crypto-engine operation mode
 */
typedef enum
{
    EN_DRV_TSPU_CRYPTO_OP_DECRYPT,                               /*!< Crypto-Engine operation by decryption mode    */
    EN_DRV_TSPU_CRYPTO_OP_ENCRYPT,                               /*!< Crypto-Engine operation by encryption mode    */
    EN_DRV_TSPU_CRYPTO_OP_NUM,
}EN_DRV_TSPU_CRYPTO_OP;

/**
 * \brief
 * enumurate to indicate the crypto-engine work mode
 */
typedef enum
{
    EN_DRV_TSPU_CRYPTO_WORK_IO,                                  /*!< Crypto-Engine work by IO mode    */
    EN_DRV_TSPU_CRYPTO_WORK_DMA,                                 /*!< Crypto-Engine work by DMA mode    */
    EN_DRV_TSPU_CRYPTO_WORK_NUM,
}EN_DRV_TSPU_CRYPTO_WORK;

/**
 * \brief
 * enumurate to indicate the desc operation mode
 */
typedef enum
{
    EN_DRV_TSPU_DESC_MODE_BYPASS,                                   /*!< Bypass DESC module                         */
    EN_DRV_TSPU_DESC_MODE_DVB_CSA,                                  /*!< DESC module used DVB CSA mode              */
    EN_DRV_TSPU_DESC_MODE_DVB_CSA3,                                 /*!< DESC module used DVB CSA3 mode             */
    EN_DRV_TSPU_DESC_MODE_CI_PLUS_AES,                              /*!< DESC module used CI Plus AES               */
    EN_DRV_TSPU_DESC_MODE_CI_PLUS_DES,                              /*!< DESC module used CI Plus DES               */
    EN_DRV_TSPU_DESC_MODE_CA_AES,                                   /*!< DESC module used CA AES                    */
    EN_DRV_TSPU_DESC_MODE_CA_DES,                                   /*!< DESC module used CA DES                    */
    EN_DRV_TSPU_DESC_MODE_ATSC_TDES,                                /*!< DESC module used ATSC TDES (Tripe DES)     */
    EN_DRV_TSPU_DESC_MODE_ISDB_MULTI2,                              /*!< DESC module used ISDB MULTI2               */
    EN_DRV_TSPU_DESC_MODE_NUM,  
}EN_DRV_TSPU_DESC_MODE;

/**
 * \brief
 * enumurate to indicate the desc encrypted layer
 */
typedef enum
{
    EN_DRV_TSPU_DESC_LAYER_TS,                                      /*!< TS layer encrypted                         */
    EN_DRV_TSPU_DESC_LAYER_PES,                                     /*!< PES layer encrypted                        */
    EN_DRV_TSPU_DESC_LAYER_NUM,
}EN_DRV_TSPU_DESC_LAYER;

/**
 * \brief
 * enumurate to indicate the desc block cipher mode
 */
typedef enum
{
    EN_DRV_TSPU_DESC_BLOCK_CIPHER_CBC,                              /*!< DESC used CBC mode                         */
    EN_DRV_TSPU_DESC_BLOCK_CIPHER_ECB,                              /*!< DESC used ECB mode                         */
    EN_DRV_TSPU_DESC_BLOCK_CIPHER_NUM,
}EN_DRV_TSPU_DESC_BLOCK_CIPHER;

/**
 * \brief
 * enumurate to indicate the desc short block mode
 */
typedef enum
{
    EN_DRV_TSPU_DESC_SHORT_BLOCK_CLEAR_END,                         /*!< DESC short block is clear and at packet end    */
    EN_DRV_TSPU_DESC_SHORT_BLOCK_CLEAR_START,                       /*!< DESC short block is clear and at paket start   */
    EN_DRV_TSPU_DESC_SHORT_BLOCK_NUM,
}EN_DRV_TSPU_DESC_SHORT_BLOCK;


/**
 * \brief
 * enumurate to indicate the desc control word bank number
 */
typedef enum
{
    EN_DRV_TSPU_DESC_CWB_NONE,                                      /*!< DESC control word bank None                */
    EN_DRV_TSPU_DESC_CWB_0,                                         /*!< DESC control word bank 0                   */
    EN_DRV_TSPU_DESC_CWB_1,                                         /*!< DESC control word bank 1                   */
    EN_DRV_TSPU_DESC_CWB_2,                                         /*!< DESC control word bank 2                   */
    EN_DRV_TSPU_DESC_CWB_3,                                         /*!< DESC control word bank 3                   */
    EN_DRV_TSPU_DESC_CWB_4,                                         /*!< DESC control word bank 4                   */
    EN_DRV_TSPU_DESC_CWB_5,                                         /*!< DESC control word bank 5                   */
    EN_DRV_TSPU_DESC_CWB_NUM,
}EN_DRV_TSPU_DESC_CWB;

/**
 * \brief
 *  enumurate to indicate the Filter Type
 */
typedef enum
{
    EN_DRV_TSPU_FILT_TYPE_NONE,                                     /*!< Filter Type None 					        */
    EN_DRV_TSPU_FILT_TYPE_SECTION,                                  /*!< Section Filter							    */
    EN_DRV_TSPU_FILT_TYPE_PES,                                      /*!< PES Filter       							*/
    EN_DRV_TSPU_FILT_TYPE_ES,                                       /*!< ES Filter      							*/
    EN_DRV_TSPU_FILT_TYPE_TS,                                       /*!< TS Filter      							*/
    EN_DRV_TSPU_FILT_TYPE_M2TS,                                     /*!< M2TS Filter      							*/
    EN_DRV_TSPU_FILT_TYPE_MM_ES,                                    /*!< MM ES Filter      							*/
    EN_DRV_TSPU_FILT_TYPE_NUM,
}EN_DRV_TSPU_FILT_TYPE;

/**
 * \brief
 *  enumurate to indicate the Filter Notify Status
 */
typedef enum
{
    EN_DRV_TSPU_FILT_NOTIFY_STATUS_SECTION_READY,                   /*!< Section data ready, Support Section Filter                     */
    EN_DRV_TSPU_FILT_NOTIFY_STATUS_PES_READY,                       /*!< PES data ready, Support PES Filter                             */
    EN_DRV_TSPU_FILT_NOTIFY_STATUS_ES_REQUEST_READY,                /*!< ES request data length ready, Support ES Filter                */
    EN_DRV_TSPU_FILT_NOTIFY_STATUS_TS_REQUEST_READY,                /*!< TS request data length ready, Support TS Filter                */
    EN_DRV_TSPU_FILT_NOTIFY_STATUS_PTS_READY,                       /*!< PTS data ready, Support ES Filter                              */
    EN_DRV_TSPU_FILT_NOTIFY_STATUS_RING_BUFFER_OVERFLOW,            /*!< Ring buffer overflow, Support Section/PES/ES/TS Filter         */
    EN_DRV_TSPU_FILT_NOTIFY_STATUS_NUM,
}EN_DRV_TSPU_FILT_NOTIFY_STATUS;

/**
 * \brief
 *  the Filter Notify function pointer
 */
typedef ErrorCode (*DRV_TSPU_FILT_NOTIFY_FN)(u32 u32Handle, EN_DRV_TSPU_FILT_NOTIFY_STATUS enStatus); 

/**
 * \brief
 *  the TSPU initial structure
 */
typedef struct
{
    u32                             u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_TSPU_INIT_PARAMS, *PST_DRV_TSPU_INIT_PARAMS;

/**
 * \brief
 *  the TSPU terminate structure
 */
typedef struct 
{
    bool                            b8Force;                        /*!< Force terminate TSPU	                */
} ST_DRV_TSPU_TERM_PARAMS, *PST_DRV_TSPU_TERM_PARAMS;
/**
 * \brief
 *  the TSPU query info structure
 */
typedef struct
{
    u32                             u32DeviceMaxNum;                /*!< TSPU device maximum number             */
    u32                             u32DataPathMaxNum;              /*!< Data Path maximum number               */
    u32                             u32PidMaxNum;                   /*!< PID maximum number                     */
    u32                             u32FiltMaxNum;                  /*!< Filter maximum number                  */
    u32                             u32BufAlignmentLimited;         /*!< Buffer address alignment limited       */
    u32                             u32BufSizeMinLimited;           /*!< Buffer size minimum limited            */
}ST_DRV_TSPU_QUERY_INFO, *PST_DRV_TSPU_QUERY_INFO;


/**
 * \brief
 *  the TSPU Timestamp Config structure
 */
typedef struct
{
    u32                             u32ClockDivision;               /*!< Timestamp Clock Division               */
    u32                             u32InitValue;                   /*!< Timestamp Initial Value                */
}ST_DRV_TSPU_TIMESTAMP_CFG_PARAMS, *PST_DRV_TSPU_TIMESTAMP_CFG_PARAMS;

// For Data Path
/**
 * \brief
 *  the nim config structure
 */
typedef struct
{
    bool                            b8ClockInverse;                 /*!< NIM clock Inverse, Inverse clock (TRUE)/ Normal clock (FALSE)                              */
    bool                            b8SerialMode;                   /*!< TS Input mode, Serial mode (TRUE)/ Parallel mode (FALSE)                                   */
    bool                            b8SerialD7Input;                /*!< Serial TS Input PIN, D7 Input (TRUE)/ D0 Input (FALSE)                                     */
    bool                            b8IgnoreSync;                   /*!< Nim Ignore Sync signal, take effect when b8SerialMode = FALSE                               */ 
    bool                            b8IgnoreSyncAndValid;           /*!< Nim Ignore Sync & Vaild signal, take effect when b8SerialMode = FALSE                       */ 
    u32                             u32SyncPacketCount;             /*!< packet number of check sync, take effect when b8IgnoreSync or b8IgnoreSyncAndValid = TRUE    */
    u32                             u32LostSyncPacketCount;         /*!< packet number of check lost sync,take effect when b8IgnoreSync or b8IgnoreSyncAndValid = TRUE*/
}ST_DRV_TSPU_NIM_CFG_PARAMS, *PST_DRV_TSPU_NIM_CFG_PARAMS;

/**
 * \brief
 *  the nim query information
 */
typedef struct
{
    bool                            b8ClockInverse;                 /*!< NIM clock Inverse, Inverse clock (TRUE)/ Normal clock (FALSE)                                  */
    bool                            b8SerialMode;                   /*!< TS Input mode, Serial mode (TRUE)/ Parallel mode (FALSE)                                       */
    bool                            b8SerialD7Input;                /*!< Serial TS Input PIN, D7 Input (TRUE)/ D0 Input (FALSE)                                         */
    bool                            b8IgnoreSync;                   /*!< Nim Ignore Sync signal, take effect when b8SerialMode = FALSE                                  */ 
    bool                            b8IgnoreSyncAndValid;           /*!< Nim Ignore Sync & Vaild signal, take effect when b8SerialMode = FALSE                          */ 
    u32                             u32SyncPacketCount;             /*!< packet number of check sync, take effect when b8IgnoreSync or b8IgnoreSyncAndValid = TRUE      */
    u32                             u32LostSyncPacketCount;         /*!< packet number of check lost sync,take effect when b8IgnoreSync or b8IgnoreSyncAndValid = TRUE  */
}ST_DRV_TSPU_NIM_QUERY_INFO, *PST_DRV_TSPU_NIM_QUERY_INFO;

/**
 * \brief
 *  the Data Path open structure
 */
typedef struct
{
    bool                            b8DescRequest;                 /*!< Data path need include DESC feature        */
}ST_DRV_TSPU_DP_OPEN_PARAMS, *PST_DRV_TSPU_DP_OPEN_PARAMS;


/**
 * \brief
 *  the Data Path config structure
 */
typedef struct
{
    EN_DRV_TSPU_SOURCE_TYPE         enSrcType;                      /*!< Data Path Source TSI type                  */
}ST_DRV_TSPU_DP_CFG_PARAMS, *PST_DRV_TSPU_DP_CFG_PARAMS;

/**
 * \brief
 *  the Data Path query info structure
 */
typedef struct
{
    bool                            b8DescRequest;                  /*!< Data Path request DESC feature             */
    EN_DRV_TSPU_SOURCE_TYPE         enSrcType;                      /*!< Data Path Source TSI type                  */
}ST_DRV_TSPU_DP_QUERY_INFO, *PST_DRV_TSPU_DP_QUERY_INFO;

// For Crypto-Engine
/**
 * \brief
 *  the Crypto mode : ATSC TDES, config structure
 */
typedef struct
{
    u8*                             pu8InputData;
    u32                             u32InputDataLen;
    u8*                             pu8OutputData;
    u32                             u32OutputDataLen;
    u8                              au8InitialVector[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];
    u8                              au8Key1[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];
    u8                              au8Key2[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];
    u8                              au8Key3[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];
    EN_DRV_TSPU_CRYPTO_BLOCK_CIPHER enBlockCipher;
    EN_DRV_TSPU_CRYPTO_SHORT_BLOCK  enShortBlock;
    EN_DRV_TSPU_CRYPTO_OP		    enOperation;
    EN_DRV_TSPU_CRYPTO_WORK			enWork;
}ST_DRV_TSPU_CRYPTO_TDES_PARAMS, *PST_DRV_TSPU_CRYPTO_TDES_PARAMS;

/**
 * \brief
 *  the Crypto mode : CI Plus AES, config structure
 */
typedef struct
{
    u8*                             pu8InputData;
    u32                             u32InputDataLen;
    u8*                             pu8OutputData;
    u32                             u32OutputDataLen;
    u8                              au8InitialVector[DRV_TSPU_DESC_CI_PLUS_AES_CW_LENGTH];
    u8                              au8Key[DRV_TSPU_DESC_CI_PLUS_AES_CW_LENGTH];
    EN_DRV_TSPU_CRYPTO_BLOCK_CIPHER enBlockCipher;
    EN_DRV_TSPU_CRYPTO_SHORT_BLOCK  enShortBlock;
    EN_DRV_TSPU_CRYPTO_OP		    enOperation;
    EN_DRV_TSPU_CRYPTO_WORK			enWork;
}ST_DRV_TSPU_CRYPTO_AES_PARAMS, *PST_DRV_TSPU_CRYPTO_AES_PARAMS;

/**
 * \brief
 *  the Crypto mode : ISDB MULTI2, config structure
 */
typedef struct
{
    u8*                             pu8InputData;
    u32                             u32InputDataLen;
    u8*                             pu8OutputData;
    u32                             u32OutputDataLen;
    u8                              au8DataKey[DRV_TSPU_DESC_ISDB_MULTI2_DATA_CW_LENGTH];
    u8                              au8SystemKey[DRV_TSPU_DESC_ISDB_MULTI2_SYSTEM_CW_LENGTH];
    u8                              au8InitialVector[DRV_TSPU_DESC_ISDB_MULTI2_DATA_CW_LENGTH];
    u32                             u32RoundNo;
    EN_DRV_TSPU_CRYPTO_BLOCK_CIPHER enBlockCipher;
    EN_DRV_TSPU_CRYPTO_SHORT_BLOCK  enShortBlock;
    EN_DRV_TSPU_CRYPTO_OP		    enOperation;
    EN_DRV_TSPU_CRYPTO_WORK			enWork;
}ST_DRV_TSPU_CRYPTO_MULTI2_PARAMS, *PST_DRV_TSPU_CRYPTO_MULTI2_PARAMS;

// For DESC
/**
 * \brief
 *  the DESC mode : DVB CSA, config structure
 */
typedef struct
{
    bool                            b8DefaultCWEnable;                                          /*!< Enable Default control word            */
    u8                              au8DefaultCW[DRV_TSPU_DESC_DVB_CSA_CW_LENGTH];              /*!< Default control word                   */
}ST_DRV_TSPU_DESC_MODE_DVB_CSA_PARAMS, *PST_DRV_TSPU_DESC_MODE_DVB_CSA_PARAMS;

/**
 * \brief
 *  the DESC mode : DVB CSA3, config structure
 */
typedef struct
{
    bool                            b8DefaultCWEnable;                                          /*!< Enable Default control word            */
    u8                              au8DefaultCW[DRV_TSPU_DESC_DVB_CSA3_CW_LENGTH];             /*!< Default control word                   */
}ST_DRV_TSPU_DESC_MODE_DVB_CSA3_PARAMS, *PST_DRV_TSPU_DESC_MODE_DVB_CSA3_PARAMS;

/**
 * \brief
 *  the DESC mode : CI Plus AES, config structure
 */
typedef struct
{
    u32                             u32Reserved;                                                /*!< Reserved for future used               */
}ST_DRV_TSPU_DESC_MODE_CI_PLUS_AES_PARAMS, *PST_DRV_TSPU_DESC_MODE_CI_PLUS_AES_PARAMS;

/**
 * \brief
 *  the DESC mode : CI Plus DES, config structure
 */
typedef struct
{
    u32                             u32Reserved;                                                /*!< Reserved for future used               */
}ST_DRV_TSPU_DESC_MODE_CI_PLUS_DES_PARAMS, *PST_DRV_TSPU_DESC_MODE_CI_PLUS_DES_PARAMS;

/**
 * \brief
 *  the DESC mode : CA AES, config structure
 */
typedef struct
{
    EN_DRV_TSPU_DESC_BLOCK_CIPHER   enBlockCipher;                                              /*!< Blcok Cipher Mode                          */
    EN_DRV_TSPU_DESC_SHORT_BLOCK    enShortBlock;                                               /*!< Short Blcok Mode                           */
}ST_DRV_TSPU_DESC_MODE_CA_AES_PARAMS, *PST_DRV_TSPU_DESC_MODE_CA_AES_PARAMS;

/**
 * \brief
 *  the DESC mode : CA DES, config structure
 */
typedef struct
{
    EN_DRV_TSPU_DESC_SHORT_BLOCK    enShortBlock;                                               /*!< Short Blcok Mode                           */
}ST_DRV_TSPU_DESC_MODE_CA_DES_PARAMS, *PST_DRV_TSPU_DESC_MODE_CA_DES_PARAMS;

/**
 * \brief
 *  the DESC mode : ATSC TDES, config structure
 */
typedef struct
{
    u32                             u32Reserved;                                                /*!< Reserved for future used               */
}ST_DRV_TSPU_DESC_MODE_ATSC_TDES_PARAMS, *PST_DRV_TSPU_DESC_MODE_ATSC_TDES_PARAMS;

/**
 * \brief
 *  the DESC mode : ISDB MULTI2, config structure
 */
typedef struct
{
    u8                              au8InitialVector[DRV_TSPU_DESC_ISDB_MULTI2_DATA_CW_LENGTH]; /*!< Initial Vector                         */
    u8                              au8SystemCW[DRV_TSPU_DESC_ISDB_MULTI2_SYSTEM_CW_LENGTH];    /*!< System Control Word                    */
}ST_DRV_TSPU_DESC_MODE_ISDB_MULTI2_PARAMS, *PST_DRV_TSPU_DESC_MODE_ISDB_MULTI2_PARAMS;


/**
 * \brief
 *  the DESC config structure
 */
typedef struct
{
    EN_DRV_TSPU_DESC_MODE           enDescMode;                                                 /*!< DESC operation mode            */
    union
    {
        ST_DRV_TSPU_DESC_MODE_DVB_CSA_PARAMS        stDvbCsaParams;                             /*!< DVB CSA Parameters             */
        ST_DRV_TSPU_DESC_MODE_DVB_CSA3_PARAMS       stDvbCsa3Params;                            /*!< DVB CSA3 Parameters             */
        ST_DRV_TSPU_DESC_MODE_CI_PLUS_AES_PARAMS    stCiPlusAesParams;                          /*!< CI PLUS AES Parameters         */
        ST_DRV_TSPU_DESC_MODE_CI_PLUS_DES_PARAMS    stCiPlusDesParams;                          /*!< CI PLUS DES Parameters         */
        ST_DRV_TSPU_DESC_MODE_CA_AES_PARAMS         stCaAesParams;                              /*!< CA AES Parameters              */
        ST_DRV_TSPU_DESC_MODE_CA_DES_PARAMS         stCaDesParams;                              /*!< CA DES Parameters              */
        ST_DRV_TSPU_DESC_MODE_ATSC_TDES_PARAMS      stAtscTdesParams;                           /*!< ATSC TDES Parameters           */
        ST_DRV_TSPU_DESC_MODE_ISDB_MULTI2_PARAMS    stIsdbMulti2Params;                         /*!< ISDB MULTI2 Parameters         */
    } unCfg;
}ST_DRV_TSPU_DESC_CFG_PARAMS, *PST_DRV_TSPU_DESC_CFG_PARAMS;
/**
 * \brief
 *  the DESC query info structure
 */
typedef struct
{
    EN_DRV_TSPU_DESC_MODE           enDescMode;                                                 /*!< DESC operation mode            */
    union
    {
        ST_DRV_TSPU_DESC_MODE_DVB_CSA_PARAMS        stDvbCsaParams;                             /*!< DVB CSA Parameters             */
        ST_DRV_TSPU_DESC_MODE_DVB_CSA3_PARAMS       stDvbCsa3Params;                            /*!< DVB CSA3 Parameters             */
        ST_DRV_TSPU_DESC_MODE_CI_PLUS_AES_PARAMS    stCiPlusAesParams;                          /*!< CI PLUS AES Parameters         */
        ST_DRV_TSPU_DESC_MODE_CI_PLUS_DES_PARAMS    stCiPlusDesParams;                          /*!< CI PLUS DES Parameters         */
        ST_DRV_TSPU_DESC_MODE_CA_AES_PARAMS         stCaAesParams;                              /*!< CA AES Parameters              */
        ST_DRV_TSPU_DESC_MODE_CA_DES_PARAMS         stCaDesParams;                              /*!< CA DES Parameters              */
        ST_DRV_TSPU_DESC_MODE_ATSC_TDES_PARAMS      stAtscTdesParams;                           /*!< ATSC TDES Parameters           */
        ST_DRV_TSPU_DESC_MODE_ISDB_MULTI2_PARAMS    stIsdbMulti2Params;                         /*!< ISDB MULTI2 Parameters         */
    } unCfg;
}ST_DRV_TSPU_DESC_QUERY_INFO, *PST_DRV_TSPU_DESC_QUERY_INFO;


/**
 * \brief
 *  the DESC Control Word Bank : DVB CSA config structure
 */
typedef struct
{
    u8                              au8EvenCW[DRV_TSPU_DESC_DVB_CSA_CW_LENGTH];                 /*!< Odd control word                           */
    u8                              au8OddCW[DRV_TSPU_DESC_DVB_CSA_CW_LENGTH];                  /*!< Even control word                          */
}ST_DRV_TSPU_DESC_CWB_DVB_CSA_PARAMS, *PST_DRV_TSPU_DESC_CWB_DVB_CSA_PARAMS;

/**
 * \brief
 *  the DESC Control Word Bank : DVB CSA3 config structure
 */
typedef struct
{
    u8                              au8EvenCW[DRV_TSPU_DESC_DVB_CSA3_CW_LENGTH];                /*!< Odd control word                           */
    u8                              au8OddCW[DRV_TSPU_DESC_DVB_CSA3_CW_LENGTH];                 /*!< Even control word                          */
}ST_DRV_TSPU_DESC_CWB_DVB_CSA3_PARAMS, *PST_DRV_TSPU_DESC_CWB_DVB_CSA3_PARAMS;

/**
 * \brief
 *  the DESC Control Word Bank : CI Plus AES config structure
 */
typedef struct
{
    u8                              au8EvenInitialVector[DRV_TSPU_DESC_CI_PLUS_AES_CW_LENGTH];  /*!< Even Initial Vector                        */
    u8                              au8OddInitialVector[DRV_TSPU_DESC_CI_PLUS_AES_CW_LENGTH];   /*!< Odd Initial Vector                         */
    u8                              au8EvenCW[DRV_TSPU_DESC_CI_PLUS_AES_CW_LENGTH];             /*!< Even control word                          */
    u8                              au8OddCW[DRV_TSPU_DESC_CI_PLUS_AES_CW_LENGTH];              /*!< Odd control word                           */
}ST_DRV_TSPU_DESC_CWB_CI_PLUS_AES_PARAMS, *PST_DRV_TSPU_DESC_CWB_CI_PLUS_AES_PARAMS;

/**
 * \brief
 *  the DESC Control Word Bank : CI Plus DES config structure
 */
typedef struct
{
    u8                              au8EvenCW[DRV_TSPU_DESC_CI_PLUS_DES_CW_LENGTH];             /*!< Odd control word                           */
    u8                              au8OddCW[DRV_TSPU_DESC_CI_PLUS_DES_CW_LENGTH];              /*!< Even control word                          */
}ST_DRV_TSPU_DESC_CWB_CI_PLUS_DES_PARAMS, *PST_DRV_TSPU_DESC_CWB_CI_PLUS_DES_PARAMS;

/**
 * \brief
 *  the DESC Control Word Bank : CA AES config structure
 */
typedef struct
{
    u8                              au8EvenInitialVector[DRV_TSPU_DESC_CA_AES_CW_LENGTH];       /*!< Even Initial Vector                        */
    u8                              au8OddInitialVector[DRV_TSPU_DESC_CA_AES_CW_LENGTH];        /*!< Odd Initial Vector                         */
    u8                              au8EvenCW[DRV_TSPU_DESC_CA_AES_CW_LENGTH];                  /*!< Even control word                          */
    u8                              au8OddCW[DRV_TSPU_DESC_CA_AES_CW_LENGTH];                   /*!< Odd control word                           */
}ST_DRV_TSPU_DESC_CWB_CA_AES_PARAMS, *PST_DRV_TSPU_DESC_CWB_CA_AES_PARAMS;

/**
 * \brief
 *  the DESC Control Word Bank : CA DES config structure
 */
typedef struct
{
    u8                              au8EvenCW[DRV_TSPU_DESC_CA_DES_CW_LENGTH];                  /*!< Odd control word                           */
    u8                              au8OddCW[DRV_TSPU_DESC_CA_DES_CW_LENGTH];                   /*!< Even control word                          */
}ST_DRV_TSPU_DESC_CWB_CA_DES_PARAMS, *PST_DRV_TSPU_DESC_CWB_CA_DES_PARAMS;

/**
 * \brief
 *  the DESC Control Word Bank : ATSC TDES config structure
 */
typedef struct
{
    u8                              au8EvenCWA[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];              /*!< Even Control Word A                        */
    u8                              au8EvenCWB[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];              /*!< Even Control Word B                        */
    u8                              au8EvenCWC[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];              /*!< Even Control Word C                        */
    u8                              au8OddCWA[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];               /*!< Odd Control Word A                         */
    u8                              au8OddCWB[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];               /*!< Odd Control Word B                         */
    u8                              au8OddCWC[DRV_TSPU_DESC_ATSC_TDES_CW_LENGTH];               /*!< Odd Control Word C                         */
}ST_DRV_TSPU_DESC_CWB_ATSC_TDES_PARAMS, *PST_DRV_TSPU_DESC_CWB_ATSC_TDES_PARAMS;

/**
 * \brief
 *  the DESC Control Word Bank : ISDB MULTI2 config structure
 */
typedef struct
{
    u8                              au8EvenCW[DRV_TSPU_DESC_ISDB_MULTI2_DATA_CW_LENGTH];        /*!< Odd control word                           */
    u8                              au8OddCW[DRV_TSPU_DESC_ISDB_MULTI2_DATA_CW_LENGTH];         /*!< Even control word                          */
}ST_DRV_TSPU_DESC_CWB_ISDB_MULTI2_PARAMS, *PST_DRV_TSPU_DESC_CWB_ISDB_MULTI2_PARAMS;


/**
 * \brief
 *  the DESC Control Word Bank config structure
 */
typedef struct
{
    union
    {
        ST_DRV_TSPU_DESC_CWB_DVB_CSA_PARAMS        stDvbCsaParams;                              /*!< DVB CSA Parameters                 */
        ST_DRV_TSPU_DESC_CWB_DVB_CSA3_PARAMS       stDvbCsa3Params;                             /*!< DVB CSA3 Parameters                */
        ST_DRV_TSPU_DESC_CWB_CI_PLUS_AES_PARAMS    stCiPlusAesParams;                           /*!< CI PLUS AES Parameters             */
        ST_DRV_TSPU_DESC_CWB_CI_PLUS_DES_PARAMS    stCiPlusDesParams;                           /*!< CI PLUS DES Parameters             */
        ST_DRV_TSPU_DESC_CWB_CA_AES_PARAMS          stCaAesParams;                              /*!< CA AES Parameters                  */
        ST_DRV_TSPU_DESC_CWB_CA_DES_PARAMS          stCaDesParams;                              /*!< CA DES Parameters                  */
        ST_DRV_TSPU_DESC_CWB_ATSC_TDES_PARAMS      stAtscTdesParams;                            /*!< ATSC TDES Parameters               */
        ST_DRV_TSPU_DESC_CWB_ISDB_MULTI2_PARAMS    stIsdbMulti2Params;                          /*!< ISDB MULTI2 Parameters             */
    } unCfg;
}ST_DRV_TSPU_DESC_CWB_CFG_PARAMS, *PST_DRV_TSPU_DESC_CWB_CFG_PARAMS;
/**
 * \brief
 *  the DESC Control Word Bank : query info structure
 */
typedef struct
{
    EN_DRV_TSPU_DESC_MODE           enDescMode;                                                 /*!< DESC operation mode                */
    bool                            b8Enable;                                                   /*!< Control Word Bank Enable/Disable   */    
    union
    {
        ST_DRV_TSPU_DESC_CWB_DVB_CSA_PARAMS        stDvbCsaParams;                              /*!< DVB CSA Parameters                 */
        ST_DRV_TSPU_DESC_CWB_DVB_CSA3_PARAMS       stDvbCsa3Params;                             /*!< DVB CSA3 Parameters                */
        ST_DRV_TSPU_DESC_CWB_CI_PLUS_AES_PARAMS    stCiPlusAesParams;                           /*!< CI PLUS AES Parameters             */
        ST_DRV_TSPU_DESC_CWB_CI_PLUS_DES_PARAMS    stCiPlusDesParams;                           /*!< CI PLUS DES Parameters             */
        ST_DRV_TSPU_DESC_CWB_CA_AES_PARAMS          stCaAesParams;                              /*!< CA AES Parameters                  */
        ST_DRV_TSPU_DESC_CWB_CA_DES_PARAMS          stCaDesParams;                              /*!< CA DES Parameters                  */
        ST_DRV_TSPU_DESC_CWB_ATSC_TDES_PARAMS      stAtscTdesParams;                            /*!< ATSC TDES Parameters               */
        ST_DRV_TSPU_DESC_CWB_ISDB_MULTI2_PARAMS    stIsdbMulti2Params;                          /*!< ISDB MULTI2 Parameters             */
    } unCfg;
}ST_DRV_TSPU_DESC_CWB_QUERY_INFO, *PST_DRV_TSPU_DESC_CWB_QUERY_INFO;

/**
 * \brief
 *  the DESC PID open structure
 */
typedef struct
{
    u32                             u32DpHandle;												/*!< reserve for futher use                                         */
}ST_DRV_TSPU_DESC_PID_OPEN_PARAMS, *PST_DRV_TSPU_DESC_PID_OPEN_PARAMS;

/**
 * \brief
 *  the DESC PID : config structure
 */
typedef struct
{
    u16                             u16PidPattern;                                              /*!< PID Pattern value                  */  
    EN_DRV_TSPU_DESC_CWB            enCWB;                                                      /*!< Control Word Bank Value            */
    EN_DRV_TSPU_DESC_LAYER			enLayer;                                                    /*!< encrypted layer TS/PES             */
}ST_DRV_TSPU_DESC_PID_CFG_PARAMS, *PST_DRV_TSPU_DESC_PID_CFG_PARAMS;

/**
 * \brief
 *  the DESC PID : query info structure
 */
typedef struct
{
    bool                            b8Enable;                                                   /*!< DESC PID Enable/Disable            */    
    u16                             u16PidPattern;                                              /*!< PID Pattern value                  */  
    EN_DRV_TSPU_DESC_CWB            enCWB;                                                      /*!< Control Word Bank Value            */
    EN_DRV_TSPU_DESC_LAYER			enLayer;                                                    /*!< encrypted layer TS/PES             */
}ST_DRV_TSPU_DESC_PID_QUERY_INFO, *PST_DRV_TSPU_DESC_PID_QUERY_INFO;

// For PID
/**
 * \brief
 *  the PID open structure
 */
typedef struct
{
    bool                            b8MaskRequest;                  /*!< PID need include mask feature*/
}ST_DRV_TSPU_PID_OPEN_PARAMS, *PST_DRV_TSPU_PID_OPEN_PARAMS;

/**
 * \brief
 *  the PID config structure
 */
typedef struct
{
	u32		                        u32DpHandle;                    /*!< Data Path Handle                                                                   */
    u32                             u32FiltHandle;                  /*!< Filter Handle                                                                      */
    bool                            b8AdaptMath;                    /*!< When b8AdaptMath equal to TRUE,  the packet must contain Adaptation Field           */ 
	bool 	                        b8MaskEnable;                   /*!< This config only take effect when PID handle open with b8MaskEnable equal to TRUE   */ 
    u16                             u16PidPattern;                  /*!< PID Pattern value                                                                  */
	u16		                        u16MaskPattern;	                /*!< This config only take effect when b8MaskEnable equal to TRUE                        */
}ST_DRV_TSPU_PID_CFG_PARAMS, *PST_DRV_TSPU_PID_CFG_PARAMS;

/**
 * \brief
 *  the PID query information
 */
typedef struct
{
    bool                            bPidEnable;                     /*!< PID Enable/Disable                                                                 */
	u32		                        u32DpHandle;                    /*!< Data Path Handle                                                                   */
    u32                             u32FiltHandle;                  /*!< Filter Handle                                                                      */
    bool                            b8AdaptMath;                    /*!< When b8AdaptMath equal to TRUE,  the packet must contain Adaptation Field           */ 
	bool 	                        b8MaskRequest;                  /*!< Mask deature status                                                                */ 
	bool 	                        b8MaskEnable;                   /*!< This config only take effect when PID handle open with b8MaskEnable equal to TRUE   */ 
    u16                             u16PidPattern;                  /*!< PID Pattern value                                                                  */
	u16		                        u16MaskPattern;	                /*!< This config only take effect when b8MaskEnable equal to TRUE                        */
}ST_DRV_TSPU_PID_QUERY_INFO, *PST_DRV_TSPU_PID_QUERY_INFO;

/**
 * \brief
 *  the filter open structure
 */
typedef struct
{
    EN_DRV_TSPU_FILT_TYPE         enFiltType;                       /*!< Filter Type  */
}ST_DRV_TSPU_FILT_OPEN_PARAMS, *PST_DRV_TSPU_FILT_OPEN_PARAMS;

/**
 * \brief
 *  the Section Filter structure
 */
typedef struct
{
    u8                              au8Match[DRV_TSPU_FILT_SECTION_PATTERN_LENGTH];     /*!< Filter Match pattern               */
    u8                              au8Mask[DRV_TSPU_FILT_SECTION_PATTERN_LENGTH];      /*!< Filter Mask pattern                */
    u8                              au8Excl[DRV_TSPU_FILT_SECTION_PATTERN_LENGTH];      /*!< Filter Exclude Mask Pattern        */
}ST_DRV_TSPU_FILT_SECTION_PARAMS, *PST_DRV_TSPU_FILT_SECTION_PARAMS;

/**
 * \brief
 *  the PES Filter structure
 */
typedef struct
{
    u8                              au8Match[DRV_TSPU_FILT_PES_PATTERN_LENGTH];         /*!< Filter Match pattern               */
    u8                              au8Mask[DRV_TSPU_FILT_PES_PATTERN_LENGTH];          /*!< Filter Mask pattern                */
}ST_DRV_TSPU_FILT_PES_PARAMS, *PST_DRV_TSPU_FILT_PES_PARAMS;

/**
 * \brief
 *  the ES Filter structure
 */
typedef struct
{
    u8                              au8Match[DRV_TSPU_FILT_ES_PATTERN_LENGTH];          /*!< Filter Match pattern               */
    u8                              au8Mask[DRV_TSPU_FILT_ES_PATTERN_LENGTH];           /*!< Filter Mask pattern                */
    u16                             u16RequestLength;                                   /*!< Filter Notify Request Length       */
}ST_DRV_TSPU_FILT_ES_PARAMS, *PST_DRV_TSPU_FILT_ES_PARAMS;

/**
 * \brief
 *  the TS Filter structure
 */
typedef struct
{
    u16                             u16RequestLength;                                   /*!< Filter Notify Request Length       */
}ST_DRV_TSPU_FILT_TS_PARAMS, *PST_DRV_TSPU_FILT_TS_PARAMS;

/**
 * \brief
 *  the M2TS Filter structure
 */
typedef struct
{
    u16                             u16RequestLength;                                   /*!< Filter Notify Request Length       */
}ST_DRV_TSPU_FILT_M2TS_PARAMS, *PST_DRV_TSPU_FILT_M2TS_PARAMS;

/**
 * \brief
 *  the MM ES Filter structure
 */
typedef struct
{
    u8                              au8Match[DRV_TSPU_FILT_MM_ES_PATTERN_LENGTH];          /*!< Filter Match pattern               */
    u8                              au8Mask[DRV_TSPU_FILT_MM_ES_PATTERN_LENGTH];           /*!< Filter Mask pattern                */
    u16                             u16RequestLength;                                   /*!< Filter Notify Request Length       */
}ST_DRV_TSPU_FILT_MM_ES_PARAMS, *PST_DRV_TSPU_FILT_MM_ES_PARAMS;

/**
 * \brief
 *  the Filter config structure
 */
typedef struct
{
    u32                             u32DpHandle;                    /*!< Data Path Handle               */
    u32                             u32BufferAddr;                  /*!< Filter Ring Buffer Address     */
    u32                             u32BufferSize;                  /*!< Filter Ring Buffer Size        */
    DRV_TSPU_FILT_NOTIFY_FN         pfnNotifyFn;                    /*!< Filter Notify function pointer */
    union
    {
        ST_DRV_TSPU_FILT_SECTION_PARAMS     stSectionParams;        /*!< Section Filter Parameters      */
        ST_DRV_TSPU_FILT_PES_PARAMS         stPesParams;            /*!< PES Filter Parameters          */
        ST_DRV_TSPU_FILT_ES_PARAMS          stEsParams;             /*!< ES Filter Parameters           */
        ST_DRV_TSPU_FILT_TS_PARAMS          stTsParams;             /*!< TS Filter Parameters           */
        ST_DRV_TSPU_FILT_M2TS_PARAMS        stM2tsParams;           /*!< M2TS Filter Parameters         */
        ST_DRV_TSPU_FILT_MM_ES_PARAMS       stMmEsParams;           /*!< MM ES Filter Parameters        */
    } unCfg;
}ST_DRV_TSPU_FILT_CFG_PARAMS, *PST_DRV_TSPU_FILT_CFG_PARAMS;

/**
 * \brief
 *  the Filter query information
 */
typedef struct
{
    EN_DRV_TSPU_FILT_TYPE           enFiltType;                     /*!< Filter Type                                            */
    bool                            b8FiltStart;                    /*!< Indicate Filter Start(TRUE) / Stop(FALSE)              */
    u32                             u32DpHandle;                    /*!< Data Path Handle                                       */
    u32                             u32BufferAddr;                  /*!< Filter Ring Buffer Address, must 1K Bytes alignment    */
    u32                             u32BufferSize;                  /*!< Filter Ring Buffer Size                                */
    DRV_TSPU_FILT_NOTIFY_FN         pfnNotifyFn;                    /*!< Filter Notify function pointer                         */
    union
    {
        ST_DRV_TSPU_FILT_SECTION_PARAMS     stSectionParams;        /*!< Section Filter Parameters                              */
        ST_DRV_TSPU_FILT_PES_PARAMS         stPesParams;            /*!< PES Filter Parameters                                  */
        ST_DRV_TSPU_FILT_ES_PARAMS          stEsParams;             /*!< ES Filter Parameters                                   */
        ST_DRV_TSPU_FILT_TS_PARAMS          stTsParams;             /*!< TS Filter Parameters                                   */
        ST_DRV_TSPU_FILT_M2TS_PARAMS        stM2tsParams;           /*!< M2TS Filter Parameters                                 */
        ST_DRV_TSPU_FILT_MM_ES_PARAMS       stMmEsParams;           /*!< MM ES Filter Parameters                                */
    } unCfg;
}ST_DRV_TSPU_FILT_QUERY_INFO, *PST_DRV_TSPU_FILT_QUERY_INFO;

/**
 * \brief
 *  the Filter Buffer query information
 */
typedef struct
{
    u32                             u32StartAddr;                   /*!< Ring buffer start address (non-cache base)     */
    u32                             u32EndAddr;                     /*!< Ring buffer end address (non-cache base)       */
    u32                             u32ReadAddr;                    /*!< Ring buffer read address (non-cache base)      */
    u32                             u32WriteAddr;                   /*!< Ring buffer write address (non-cache base)     */
    u32                             u32Fullness;                    /*!< Ring buffer fullness                           */
}ST_DRV_TSPU_FILT_BUF_QUERY_INFO, *PST_DRV_TSPU_FILT_BUF_QUERY_INFO;

/**
 * \brief
 *  the PTS information structure
 */
typedef struct
{
    u32                             u32Addr;                        /*!< PTS address                            */
    u32                             u32HighPart;                    /*!< The higher partition of PTS            */
    u32                             u32LowPart;                     /*!< The lower partition of PTS             */
}ST_DRV_TSPU_PTS_INFO, *PST_DRV_TSPU_PTS_INFO;

/**
 * \brief
 *  the TSI config structure
 */
typedef struct
{
    u32                                 u32ClockDivision;               /*!< TSI Clock Division                     */
    EN_DRV_TSPU_TSI_PACKET          	enPacketType;                   /*!< TSI Packet 188 or 192 Bytes Type       */
    bool                            	b8TimestampEnable;              /*!< Timestamp Enable/Disable               */    
    bool            	            	b8TimestampCheck;               /*!< TSI Timestamp Check for TSI Packet 192 Bytes Type Only  */
    ST_DRV_TSPU_TIMESTAMP_CFG_PARAMS	stTimestampCfg;                 /*!< PVR STC(Timestamp) Configuration       */
}ST_DRV_TSPU_TSI_CFG_PARAMS, *PST_DRV_TSPU_TSI_CFG_PARAMS;

/**
 * \brief
 *  enumurate to indicate the TSO Notify Status
 */
typedef struct
{
	u32 								u32ClockDivision;				/*!< TSI Clock Division 					*/
	EN_DRV_TSPU_TSI_PACKET				enPacketType;					/*!< TSI Packet 188 or 192 Bytes Type		*/
	bool								b8TimestampEnable;				/*!< Timestamp Enable/Disable				*/	  
	bool								b8TimestampCheck;				/*!< TSI Timestamp Check for TSI Packet 192 Bytes Type Only  */
	ST_DRV_TSPU_TIMESTAMP_CFG_PARAMS	stTimestampCfg; 				/*!< PVR STC(Timestamp) Configuration		*/
}ST_DRV_TSPU_TSI_QUERY_INFO, *PST_DRV_TSPU_TSI_QUERY_INFO;

typedef enum
{
    EN_DRV_TSPU_TSO_NOTIFY_STATUS_OUTPUT_SPEED_TOO_SLOW,            /*!< TSO Output Speed too slow              */
    EN_DRV_TSPU_TSO_NOTIFY_STATUS_NUM,
}EN_DRV_TSPU_TSO_NOTIFY_STATUS;

/**
 * \brief
 *  the TSO Notify function pointer
 */
typedef ErrorCode (*DRV_TSPU_TSO_NOTIFY_FN)(EN_DRV_TSPU_OUTPUT_PATH enOutputPath, EN_DRV_TSPU_TSO_NOTIFY_STATUS enStatus);

/**
 * \brief
 *  the TSO config structure
 */
typedef struct
{
    bool                            b8DirectBypass;                 /*!< TSO Direct Bypass, Enable (TRUE)/ Disable (FALSE)              */
    bool                            b8ClockInverse;                 /*!< TSO clock Inverse, Inverse clock (TRUE)/ Normal clock (FALSE)  */
    EN_DRV_TSPU_SOURCE_TYPE         enSrcType;                      /*!< Data Path Source TSI type                                      */
    u32                             u32ClockDivision;               /*!< TSO Clock Division                                             */
    DRV_TSPU_TSO_NOTIFY_FN          pfnNotifyFn;                    /*!< TSO Notify function pointer */
}ST_DRV_TSPU_TSO_CFG_PARAMS, *PST_DRV_TSPU_TSO_CFG_PARAMS;


/**
 * \brief
 *  the TSO query information
 */
typedef struct
{
    bool                            b8Enable;                       /*!< Enable (TRUE)/Disable (FALSE) TSO Module                       */
    bool                            b8DirectBypass;                 /*!< TSO Direct Bypass, Enable (TRUE)/ Disable (FALSE)              */
    bool                            b8ClockInverse;                 /*!< TSO clock Inverse, Inverse clock (TRUE)/ Normal clock (FALSE)  */
    EN_DRV_TSPU_SOURCE_TYPE         enSrcType;                      /*!< Data Path Source TSI type                                      */
    u32                             u32ClockDivision;               /*!< TSO Clock Division                                             */
    DRV_TSPU_TSO_NOTIFY_FN          pfnNotifyFn;                    /*!< TSO Notify function pointer */
}ST_DRV_TSPU_TSO_QUERY_INFO, *PST_DRV_TSPU_TSO_QUERY_INFO;

/**
 * \brief
 *  the PCR Notify function pointer
 */
typedef ErrorCode (*DRV_TSPU_PCR_NOTIFY_FN)(u32 u32Handle);

/**
 * \brief
 *  the pcr open structure
 */
typedef struct
{
    u32                           u32Reserve;						/*!< reserve for futher use                                         */
}ST_DRV_TSPU_PCR_OPEN_PARAMS, *PST_DRV_TSPU_PCR_OPEN_PARAMS;

/**
 * \brief
 *  the PCR config structure
 */
typedef struct
{
    u32                        		u32DpHandle;					/*!< data path number                                                */
    u32                        		u16PidPattern;                  /*!< PCR PID number                                                  */
    DRV_TSPU_PCR_NOTIFY_FN     		pfnNotifyFn;                    /*!< Notify function pointer                                         */
}ST_DRV_TSPU_PCR_CFG_PARAMS, *PST_DRV_TSPU_PCR_CFG_PARAMS;

/**
 * \brief
 *  the PCR query information
 */
typedef struct
{
    bool                             b8Enable;						  /*!< PCR enable status                                             */
    u32                              u32DpHandle;					  /*!< data path handle                                              */
    u16                              u16PidPattern;                   /*!< PCR PID number                                                */
    DRV_TSPU_PCR_NOTIFY_FN           pfnNotifyFn;                     /*!< Notify function pointer                                       */
}ST_DRV_TSPU_PCR_QUERY_INFO, *PST_DRV_TSPU_PCR_QUERY_INFO;

/**
 * \brief
 *  the PCR information
 */
typedef struct
{
    u32                             u32PcrBaseHiPart;                 /*!< The higher partition of PCR base                              */
    u32                             u32PcrBaseLoPart;                 /*!< The lower partition of PCR base                               */
    u32                             u32PcrExtend;                     /*!< The lower partition of PCR extend                             */
    u32                             u32StcBaseHiPart;                 /*!< The higher partition of STC base                              */
    u32                             u32StcBaseLoPart;                 /*!< The lower partition of STC base                               */
    u32                             u32StcExtend;                     /*!< The lower partition of STC extend                             */
}ST_DRV_TSPU_PCR_INFO, *PST_DRV_TSPU_PCR_INFO;

//function define
u8* DRV_TSPU_GetVersion (void);
/*!\fn u8* DRV_TSPU_GetVersion (void)
 * \brief 
 *		Get the TSPU's Version number string	   
 *
 * 
 * \return TSPU Version String
 * 
 */

ErrorCode DRV_TSPU_Init (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_INIT_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_Init (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_INIT_PARAMS pstParams)
 * \brief 
 *		Initial the TSPU with ST_DRV_TSPU_INIT_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Init parameter
 * 
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success	
 * \retval ERROR_TSPU_DEV_RESOURCE			TSPU don't have device resource	
 * \retval ERROR_BAD_PARAMETER	            Parameter error 
 * \retval ERROR_INITIALISED	            TSPU already Init.
 * 
 */

ErrorCode DRV_TSPU_Term (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_TERM_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_Term (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_TERM_PARAMS pstParams)
 * \brief 
 *		Terminate the TSPU with ST_DRV_TSPU_TERM_PARAMS setting	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Term parameter
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */

ErrorCode DRV_TSPU_Query (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_Query (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_QUERY_INFO pstInfo)
 * \brief 
 *		Query the TSPU information	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 *
 */

ErrorCode DRV_TSPU_NIM_Config (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_NIM_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_NIM_Config (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_NIM_CFG_PARAMS pstParams)
 * \brief 
 *		Config the NIM module	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enSrcType		                    (Input)  Enum to Source type (NIM0/NIM1).
 * \param pstParams		                    (Input)  NIM config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */

ErrorCode DRV_TSPU_NIM_Query (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_NIM_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_NIM_Query (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_NIM_QUERY_INFO pstInfo)
 * \brief 
 *		Query the NIM information	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enSrcType		                    (Input)  Enum to Sourcetype (NIM0/NIM1).
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */

ErrorCode DRV_TSPU_TSI_Config (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_TSI_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_TSI_Config (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_TSI_CFG_PARAMS pstParams)
 * \brief 
 *		Config the TSI module (TSI : TS Input)	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enSrcType		                    (Input)  Enum to Sourcetype (TSI_DMA0/TSI_DMA1).
 * \param pstParams		                    (Input)  TSI config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */
ErrorCode DRV_TSPU_TSI_Query (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_TSI_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_TSI_Query (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, PST_DRV_TSPU_TSI_QUERY_INFO pstInfo)
 * \brief 
 *		Query the TSI information	
 *
 * \param DeviceName						(Input)  Device Name
 * \param enSrcType 						(Input)  Enum to Sourcetype (TSI_DMA0/TSI_DMA1).
 * \param pstInfo							(Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_BAD_PARAMETER				Parameter error
 * \retval ERROR_INITIALISED				TSPU not Init.
 *
 */

ErrorCode DRV_TSPU_TSI_SendData (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, u32 u32SrcAddr, u32 u32DataLen);
/*!\fn ErrorCode DRV_TSPU_TSI_SendData (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType, u32 u32SrcAddr, u32 u32DataLen)
 * \brief 
 *		Data send in TSI (TSI : TS Input)	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enSrcType		                    (Input)  Enum to Sourcetype (TSI_DMA0/TSI_DMA1).
 * \param u32SrcAddr		                (Input)  Data Source Address, must 4 Bytes alignment.
 * \param u32DataLen		                (Input)  Data Length, must 4 byte alignment.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_TSI_SEND_DATA	        TSI Send Data
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */

ErrorCode DRV_TSPU_TSI_Reset (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType);
/*!\fn ErrorCode DRV_TSPU_TSI_Reset (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_SOURCE_TYPE enSrcType)
 * \brief 
 *		Reset TSI module (TSI : TS Output)	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enSrcType		                    (Input)  Enum to Sourcetype (TSI_DMA0/TSI_DMA1).
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */
ErrorCode DRV_TSPU_TSO_Config (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath, PST_DRV_TSPU_TSO_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_TSO_Config (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath, PST_DRV_TSPU_TSO_CFG_PARAMS pstParams)
 * \brief 
 *		Config the TSO module (TSO : TS Output)	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enOutputPath		                (Input)  Enum to Output Path
 * \param pstParams		                    (Input)  TSO config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            TSPU not Init.
 * \retval ERROR_TSPU_TSO_IS_ENABLE         TSO is enable.
 *
 */

ErrorCode DRV_TSPU_TSO_Enable (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath);
/*!\fn ErrorCode DRV_TSPU_TSO_Enable (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath)
 * \brief 
 *		Enable the TSO
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enOutputPath		                (Input)  Enum to Output Path
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_TSPU_TSO_IS_ENABLE         TSO is enable.
 */

ErrorCode DRV_TSPU_TSO_Disable (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath);
/*!\fn ErrorCode DRV_TSPU_TSO_Disable (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath)
 * \brief 
 *		Disable the TSO
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enOutputPath		                (Input)  Enum to Output Path
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 */

ErrorCode DRV_TSPU_TSO_Query (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath, PST_DRV_TSPU_TSO_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_TSO_Query (DRV_DeviceNameType DeviceName, EN_DRV_TSPU_OUTPUT_PATH enOutputPath, PST_DRV_TSPU_TSO_QUERY_INFO pstInfo)
 * \brief 
 *		Query the TSO module (TSO : TS Output) information
 *
 * \param DeviceName		                (Input)  Device Name
 * \param enOutputPath		                (Input)  Enum to Output Path
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */

ErrorCode DRV_TSPU_DP_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_DP_OPEN_PARAMS pstParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_DP_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_DP_OPEN_PARAMS pstParams, u32* pu32Handle)
 * \brief 
 *		Open the Data Path and associate it with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) Data Path Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_NO_FREE_HANDLE             Resouce empty
 * \retval ERROR_INITIALISED	            TSPU not Init.
 */

ErrorCode DRV_TSPU_DP_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_DP_Close (u32* pu32Handle)
 * \brief 
 *		Close the Data Path associate with a handle
 *
 * \param pu32Handle		                (Input)  Data Path Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_DP_Config (u32 u32Handle, PST_DRV_TSPU_DP_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_DP_Config (u32 u32Handle, PST_DRV_TSPU_DP_CFG_PARAMS pstParams)
 * \brief 
 *		Config the Data Path /	
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_TSPU_DP_Query (u32 u32Handle, PST_DRV_TSPU_DP_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_DP_Query (u32 u32Handle, PST_DRV_TSPU_DP_QUERY_INFO pstInfo)
 * \brief 
 *		Query the Data Path information/	
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */


ErrorCode DRV_TSPU_DESC_PID_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_DESC_PID_OPEN_PARAMS pstParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_DESC_PID_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_DESC_PID_OPEN_PARAMS pstParams, u32* pu32Handle)
 * \brief 
 *		Open the DESC PID and associate it with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) DESC PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_NO_FREE_HANDLE             Resouce empty
 * \retval ERROR_INITIALISED	            TSPU not Init.
 */

ErrorCode DRV_TSPU_DESC_PID_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_DESC_PID_Close (u32* pu32Handle)
 * \brief 
 *		Close the DESC PID associate with a handle
 *
 * \param pu32Handle		                (Input)  DESC PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_DESC_PID_Config (u32 u32Handle, PST_DRV_TSPU_DESC_PID_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_DESC_PID_Config (u32 u32Handle, PST_DRV_TSPU_DESC_PID_CFG_PARAMS pstParams)
 * \brief 
 *		Config the DESC PID /	
 *
 * \param u32Handle		                    (Input)  DESC PID Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_DESC_PID_IS_ENABLE    DESC PID is enable.
 *
 */

ErrorCode DRV_TSPU_DESC_PID_Query (u32 u32Handle, PST_DRV_TSPU_DESC_PID_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_DESC_PID_Query (u32 u32Handle, PST_DRV_TSPU_DESC_PID_QUERY_INFO pstInfo)
 * \brief 
 *		Query the DESC PID information/	
 *
 * \param u32Handle		                    (Input)  DESC PID Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 *
 */

ErrorCode DRV_TSPU_DESC_PID_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_DESC_PID_Enable (u32 u32Handle)
 * \brief 
 *		Enable the DESC PID
 *
 * \param u32Handle		                    (Input)  DESC PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_DESC_PID_IS_ENABLE    DESC PID is enable.
 */

ErrorCode DRV_TSPU_DESC_PID_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_DESC_PID_Disable (u32 u32Handle)
 * \brief 
 *		Enable the DESC PID
 *
 * \param u32Handle		                    (Input)  DESC PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 */

ErrorCode DRV_TSPU_DESC_Config (u32 u32Handle, PST_DRV_TSPU_DESC_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_DESC_Config (u32 u32Handle, PST_DRV_TSPU_DESC_CFG_PARAMS pstParams)
 * \brief 
 *		Config the DESC module /	
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_TSPU_DESC_Query (u32 u32Handle, PST_DRV_TSPU_DESC_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_DESC_Query (u32 u32Handle, PST_DRV_TSPU_DESC_QUERY_INFO pstInfo)
 * \brief 
 *		Query the DESC module information/	
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_TSPU_DESC_CWB_Config (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB, PST_DRV_TSPU_DESC_CWB_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_DESC_CWB_Config (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB, PST_DRV_TSPU_DESC_CWB_CFG_PARAMS pstParams)
 * \brief 
 *		Config the DESC Control Word Bank /	
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param enCWB		                        (Input)  Control Word Bank
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_DESC_CWB_IS_ENABLE	DESC Control Word Bank is enable
 */

ErrorCode DRV_TSPU_DESC_CWB_Enable (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB);
/*!\fn ErrorCode DRV_TSPU_DESC_CWB_Enable (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB)
 * \brief 
 *		Enable the DESC DVB_CSA Control Word Bank
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param enCWB		                        (Input)  Control Word Bank
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_DESC_CWB_IS_ENABLE	DESC Control Word Bank is enable
 */

ErrorCode DRV_TSPU_DESC_CWB_Disable (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB);
/*!\fn ErrorCode DRV_TSPU_DESC_CWB_Disable (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB)
 * \brief 
 *		Disable the DESC DVB_CSA Control Word Bank
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param enCWB		                        (Input)  Control Word Bank
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */


ErrorCode DRV_TSPU_DESC_CWB_Query (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB, PST_DRV_TSPU_DESC_CWB_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_DESC_CWB_Query (u32 u32Handle, EN_DRV_TSPU_DESC_CWB enCWB, PST_DRV_TSPU_DESC_CWB_QUERY_INFO pstInfo)
 * \brief 
 *		Query the DESC Control Word Bank/	
 *
 * \param u32Handle		                    (Input)  Data Path Handle
 * \param enCWB		                        (Input)  Control Word Bank
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_TSPU_CRYPTO_TDES_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_CRYPTO_TDES_PARAMS pstCfg);
/*!\fn ErrorCode DRV_TSPU_CRYPTO_TDES_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_CRYPTO_TDES_PARAMS pstCfg)
 * \brief 
 *		Cipher by TDES of Crypto-Engine
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstCfg		                    (Input)  TDES Cipher parameter
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_DEV_NAME	            Device Name Wrong
 */

ErrorCode DRV_TSPU_CRYPTO_AES_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_CRYPTO_AES_PARAMS pstCfg);
/*!\fn ErrorCode DRV_TSPU_CRYPTO_AES_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_CRYPTO_AES_PARAMS pstCfg)
 * \brief 
 *		Cipher by AES of Crypto-Engine
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstCfg		                    (Input)  AES Cipher parameter
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_DEV_NAME	            Device Name Wrong
 */

ErrorCode DRV_TSPU_CRYPTO_MULTI2_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_CRYPTO_MULTI2_PARAMS pstCfg);
/*!\fn ErrorCode DRV_TSPU_CRYPTO_MULTI2_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_CRYPTO_MULTI2_PARAMS pstCfg)
 * \brief 
 *		Cipher by Multi2 of Crypto-Engine
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstCfg		                    (Input)  Multi2 Cipher parameter
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_DEV_NAME	            Device Name Wrong
 */

ErrorCode DRV_TSPU_PID_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_PID_OPEN_PARAMS pstParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_PID_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_PID_OPEN_PARAMS pstParams, u32* pu32Handle)
 * \brief 
 *		Open the PID and associate it with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_NO_FREE_HANDLE             Resouce empty
 * \retval ERROR_INITIALISED	            TSPU not Init.
 */

ErrorCode DRV_TSPU_PID_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_PID_Close (u32* pu32Handle)
 * \brief 
 *		Close the PID associate with a handle
 *
 * \param pu32Handle		                (Input)  PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_PID_Config (u32 u32Handle, PST_DRV_TSPU_PID_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_PID_Config (u32 u32Handle, PST_DRV_TSPU_PID_CFG_PARAMS pstParams)
 * \brief 
 *		Config the PID /	
 *
 * \param u32Handle		                    (Input)  PID Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_PID_IS_ENABLE         PID is enable.
 *
 */

ErrorCode DRV_TSPU_PID_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_PID_Enable (u32 u32Handle)
 * \brief 
 *		Enable the PID
 *
 * \param u32Handle		                    (Input)  PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_PID_IS_ENABLE         PID is enable.
 */

ErrorCode DRV_TSPU_PID_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_PID_Disable (u32 u32Handle)
 * \brief 
 *		Disable the PID
 *
 * \param u32Handle		                    (Input)  PID Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */


ErrorCode DRV_TSPU_PID_Query (u32 u32Handle, PST_DRV_TSPU_PID_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_PID_Query (u32 u32Handle, PST_DRV_TSPU_PID_QUERY_INFO pstInfo)
 * \brief 
 *		Query the PID information/	
 *
 * \param u32Handle		                    (Input)  PID Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_TSPU_FILT_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_FILT_OPEN_PARAMS pstParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_FILT_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_FILT_OPEN_PARAMS pstParams, u32* pu32Handle)
 * \brief 
 *		Open the Filter and associate it with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) Filter Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_UNSUPPORT	            TSPU unsupport
 * \retval ERROR_NO_FREE_HANDLE             Resouce empty
 * \retval ERROR_INITIALISED	            TSPU not Init.
 */

ErrorCode DRV_TSPU_FILT_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_FILT_Close (u32* pu32Handle)
 * \brief 
 *		Close the Filter associate with a handle
 *
 * \param pu32Handle		                (Input)  Filter Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_FILT_Config (u32 u32Handle, PST_DRV_TSPU_FILT_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_FILT_Config (u32 u32Handle, PST_DRV_TSPU_FILT_CFG_PARAMS pstParams)
 * \brief 
 *		Config the Filter /	
 *
 * \param u32Handle		                    (Input)  Filter Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_FILT_IS_START	        Filter is running
 *
 */

ErrorCode DRV_TSPU_FILT_Start (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_FILT_Start (u32 u32Handle)
 * \brief 
 *		Start the Filter
 *
 * \param u32Handle		                    (Input)  Filter Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_FILT_IS_START	        Filter is running
 */

ErrorCode DRV_TSPU_FILT_Stop (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_FILT_Stop (u32 u32Handle)
 * \brief 
 *		Stop the Filter
 *
 * \param u32Handle		                    (Input)  Filter Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_FILT_Reset (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_FILT_Reset (u32 u32Handle)
 * \brief 
 *		Reset the Filter, the filter must be stoped.
 *
 * \param u32Handle		                    (Input)  Filter Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_FILT_IS_START	        Filter is running
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_FILT_GetSectionData (u32 u32Handle, u32 u32BufSize, u8* pu8BufPtr, u32* pu32DataSize);
/*!\fn ErrorCode DRV_TSPU_FILT_GetSectionData (u32 u32Handle, u32 u32BufSize, u8* pu8BufPtr, u32* pu32DataSize)
 * \brief 
 *		Get the section data, only support section filter.
 *
 * \param u32Handle		                    (Input)  Filter Handle
 * \param u32BufSize		                (Input)  Buffer Size
 * \param pu8BufPtr		                    (Output) Pointer of the buffer
 * \param pu32DataSize                      (Output) Section data length
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_BUF_TOO_SMALL	        Input buffer size too small to put the data
 * \retval ERROR_TSPU_FULLNESS_TOO_SMALL	Ring buffer fullness too small, can't get the data.
 */

ErrorCode DRV_TSPU_FILT_SkipSectionData (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_FILT_SkipSectionData (u32 u32Handle)
 * \brief 
 *		Skip the section data, only support section filter.
 *
 * \param u32Handle		                    (Input)  Filter Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_FULLNESS_TOO_SMALL	Ring buffer fullness too small, can't skip the data.
 */

ErrorCode DRV_TSPU_FILT_GetPesData (u32 u32Handle, u32 u32BufSize, u8* pu8BufPtr, u32* pu32DataSize);
/*!\fn ErrorCode DRV_TSPU_FILT_GetPesData (u32 u32Handle, u32 u32BufSize, u8* pu8BufPtr, u32* pu32DataSize)
 * \brief 
 *		Get the PES data, only support PES filter.
 *
 * \param u32Handle		                    (Input)  Filter Handle
 * \param u32BufSize		                (Input)  Buffer Size
 * \param pu8BufPtr		                    (Output) Pointer of the buffer
 * \param pu32DataSize                      (Output) Section data length
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_BUF_TOO_SMALL	        Input buffer size too small to put the data
 * \retval ERROR_TSPU_FULLNESS_TOO_SMALL	Ring buffer fullness too small, can't get the data.
 */

ErrorCode DRV_TSPU_FILT_SkipPesData (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_FILT_SkipPesData (u32 u32Handle)
 * \brief 
 *		Skip the PES data, only support PES filter.
 *
 * \param u32Handle		                    (Input)  Filter Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_FULLNESS_TOO_SMALL	Ring buffer fullness too small, can't skip the data.
 */

ErrorCode DRV_TSPU_FILT_SetReadAddr (u32 u32Handle, u32 u32ReadAddr);
/*!\fn ErrorCode DRV_TSPU_FILT_SetReadAddr (u32 u32Handle, u32 u32ReadAddr)
 * \brief 
 *		Setting read address of the filter ring buffer. Support TS/TS Block/ES/M2TS Filter. when read address equal to end address, it will be reload to start address.
 
 *
 * \param u32Handle		                    (Input)  Filter Handle
 * \param u32ReadAddr		                (Input)  Read Address
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_TSPU_FILT_GetPTS (u32 u32Handle, PST_DRV_TSPU_PTS_INFO pstPts);
/*!\fn ErrorCode DRV_TSPU_FILT_GetPTS (u32 u32Handle, PST_DRV_TSPU_PTS_INFO pstPts)
 * \brief 
 *		Get the PTS data,  only suport ES filter.
 *
 * \param u32Handle		                    (Input)  Filter Handle
 * \param pstPts	    	                (Output) PTS information
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_PTS_NOT_READY	        PTS data not ready
 */

ErrorCode DRV_TSPU_FILT_Query (u32 u32Handle, PST_DRV_TSPU_FILT_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_FILT_Query (u32 u32Handle, PST_DRV_TSPU_FILT_QUERY_INFO pstInfo)
 * \brief 
 *		Query the Filter information/	
 *
 * \param u32Handle		                    (Input)  Filter Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_TSPU_FILT_QueryBuffer (u32 u32Handle, PST_DRV_TSPU_FILT_BUF_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_FILT_QueryBuffer (u32 u32Handle, PST_DRV_TSPU_FILT_BUF_QUERY_INFO pstInfo)
 * \brief 
 *		Query the Filter buffer information/	
 *
 * \param u32Handle		                    (Input)  Filter Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 *
 */

ErrorCode DRV_TSPU_CRC32_Calculate (DRV_DeviceNameType DeviceName, u32 u32InitCRC, u8* pu8Data, u32 u32LengthInBytes, u32* pu32ReturnCRC);
/*!\fn ErrorCode DRV_TSPU_CRC32_Calculate (DRV_DeviceNameType DeviceName, u32 u32InitCRC, u8* pu8Data, u32 u32LengthInBytes, u32* pu32ReturnCRC)
 * \brief 
 *		Calculate CRC32 Value.	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param u32InitCRC		                (Input)  CRC32 Initial Value
 * \param pu8Data		                    (Input)  Data Pointer
 * \param u32LengthInBytes		            (Input)  Data Length
 * \param pu32ReturnCRC		                (Input)  Return CRC32 Value
 * 
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success	
 * 
 */

#ifdef DRV_TSPU_CONTROL_PCR_HANDLE
ErrorCode DRV_TSPU_PCR_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_PCR_OPEN_PARAMS pstParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_PCR_Open (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_PCR_OPEN_PARAMS pstParams, u32* pu32Handle)
 * \brief 
 *		Open the PCR and associate it with a handle
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Open parameter
 * \param pu32Handle		                (Output) PCR Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_UNSUPPORT	            TSPU unsupport
 * \retval ERROR_NO_FREE_HANDLE             Resouce empty
 * \retval ERROR_INITIALISED	            TSPU not Init.
 */

ErrorCode DRV_TSPU_PCR_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_TSPU_PCR_Close (u32* pu32Handle)
 * \brief 
 *		Close the PCR associate with a handle
 *
 * \param pu32Handle		                (Input)  PCR Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_PCR_Config (u32 u32Handle, PST_DRV_TSPU_PCR_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_PCR_Config (u32 u32Handle, PST_DRV_TSPU_PCR_CFG_PARAMS pstParams)
 * \brief 
 *		Config the PCR /	
 *
 * \param u32Handle		                    (Input)  PCR Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_TSPU_PCR_IS_ENABLE			PCR is enable
 */

ErrorCode DRV_TSPU_PCR_Query (u32 u32Handle, PST_DRV_TSPU_PCR_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_PCR_Query (u32 u32Handle, PST_DRV_TSPU_PCR_QUERY_INFO pstInfo)
 * \brief 
 *		Query the PCR information/	
 *
 * \param u32Handle		                    (Input)  PCR Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_PCR_Get (u32 u32Handle, PST_DRV_TSPU_PCR_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_PCR_Get (u32 u32Handle, PST_DRV_TSPU_PCR_INFO pstInfo)
 * \brief 
 *		Get the PCR information/	
 *
 * \param u32Handle		                    (Input)  PCR Handle
 * \param pstInfo		                    (Output) PCR info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */

ErrorCode DRV_TSPU_PCR_Enable (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_PCR_Enable (u32 u32Handle)
 * \brief 
 *		Enable the PCR latch
 *
 * \param u32Handle		                    (Input)  PCR Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 * \retval ERROR_TSPU_PCR_IS_ENABLE			PCR is enable
 */

ErrorCode DRV_TSPU_PCR_Disable (u32 u32Handle);
/*!\fn ErrorCode DRV_TSPU_PCR_Disable (u32 u32Handle)
 * \brief 
 *		Disable the PCR latch
 *
 * \param u32Handle		                    (Input)  PCR Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_INVALID_HANDLE	            Invalid handle
 * \retval ERROR_TSPU_CLOSED_HANDLE	        Closed handle
 */
#else //#ifdef DRV_TSPU_CONTROL_PCR_HANDLE
ErrorCode DRV_TSPU_PCR_Config (u32 u32StcHandle, PST_DRV_TSPU_PCR_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_PCR_Config (u32 u32StcHandle, PST_DRV_TSPU_PCR_CFG_PARAMS pstParams)
 * \brief 
 *		Config the PCR /	
 *
 * \param u32StcHandle		                (Input)  STC Handle
 * \param pstParams		                    (Input)  Config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_TSPU_PCR_Query (u32 u32StcHandle, PST_DRV_TSPU_PCR_QUERY_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_PCR_Query (u32 u32StcHandle, PST_DRV_TSPU_PCR_QUERY_INFO pstInfo)
 * \brief 
 *		Query the PCR information/	
 *
 * \param u32StcHandle		                (Input)  STC Handle
 * \param pstInfo		                    (Output) Query info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_TSPU_PCR_Get (u32 u32StcHandle, PST_DRV_TSPU_PCR_INFO pstInfo);
/*!\fn ErrorCode DRV_TSPU_PCR_Get (u32 u32StcHandle, PST_DRV_TSPU_PCR_INFO pstInfo)
 * \brief 
 *		Get the PCR data/	
 *
 * \param u32StcHandle		                (Input)  STC Handle
 * \param pstInfo		                    (Output) PCR info.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 */

ErrorCode DRV_TSPU_PCR_Enable (u32 u32StcHandle);
/*!\fn ErrorCode DRV_TSPU_PCR_Enable (u32 u32StcHandle)
 * \brief 
 *		Enable the PCR latch
 *
 * \param u32StcHandle		                (Input)  STC Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 */

ErrorCode DRV_TSPU_PCR_Disable (u32 u32StcHandle);
/*!\fn ErrorCode DRV_TSPU_PCR_Disable (u32 u32StcHandle)
 * \brief 
 *		Disable the PCR latch
 *
 * \param u32StcHandle		                (Input)  STC Handle
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 */
#endif //#ifdef DRV_TSPU_CONTROL_PCR_HANDLE
ErrorCode DRV_TSPU_TIMESTAMP_Config (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_TIMESTAMP_CFG_PARAMS pstParams);
/*!\fn ErrorCode DRV_TSPU_TIMESTAMP_Config (DRV_DeviceNameType DeviceName, PST_DRV_TSPU_TIMESTAMP_CFG_PARAMS pstParams)
 * \brief 
 *		Config the Timestamp module ((Added for M2TS Filter))	
 *
 * \param DeviceName		                (Input)  Device Name
 * \param pstParams		                    (Input)  Timestamp config parameters.
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_BAD_PARAMETER	            Parameter error
 * \retval ERROR_INITIALISED	            TSPU not Init.
 *
 */

ErrorCode DRV_TSPU_TIMESTAMP_Enable (DRV_DeviceNameType DeviceName);
/*!\fn ErrorCode DRV_TSPU_TIMESTAMP_Enable (DRV_DeviceNameType DeviceName)
 * \brief 
 *		Enable the Timestamp
 *
 * \param DeviceName		                (Input)  Device Name
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 * \retval ERROR_TSPU_TIMESTAMP_IS_ENABLE   Timestamp is enable.
 */

ErrorCode DRV_TSPU_TIMESTAMP_Disable (DRV_DeviceNameType DeviceName);
/*!\fn ErrorCode DRV_TSPU_TIMESTAMP_Disable (DRV_DeviceNameType DeviceName)
 * \brief 
 *		Disable the Timestamp
 *
 * \param DeviceName		                (Input)  Device Name
 *
 * \return TSPU Operation Error Code
 * \retval ERROR_NO_ERROR			        Operation Success
 */

#endif  //__DRV_TSPU_H__


