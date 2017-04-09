//**************************************************************************
//		 Copyright (c) , Inc . All rights reserved.
//		 STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide Crypto Engine Control 
//	Sources	: 
//**************************************************************************
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
//**************************************************************************

#ifndef __DRV_CRYPTO_H__
#define __DRV_CRYPTO_H__

#include "def_type.h"
#include "def_err.h"

#define DRV_CRYPTO_AES_CW_LENGTH           						  (16) 
#define DRV_CRYPTO_TDES_CW_LENGTH           						  (8)  
#define DRV_CRYPTO_M2_DATA_CW_LENGTH           						  (8)
#define DRV_CRYPTO_M2_SYSTEM_CW_LENGTH           						  (32)


/*!
 * \brief 
 * CRYPTO Error code definition.
 */
enum
{
	ERROR_CRYPTO_DEV_NAME     = ERROR_BASE_DRV_CRYPTO,		            /*!< Device Name Error                                          */
	ERROR_CRYPTO_DEV_RESOURCE,		                               				     /*!< Crypto don't have device resource                            */
	ERROR_CRYPTO_RRKL_KEYPROTECT,
	ERROR_CRYPTO_TSKL_KEYPROTECT,
	ERROR_CRYPTO_UNSUPPORTED,								            /*!<                                           */
};

/**
 * \brief
 * enumurate to indicate the RRKL Engine type(crp_type)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_CRP_TYPE_AES,                                   /*!< Engine Selection = AES                                 */
    EN_CRYPTO_KL_RRKL_CRP_TYPE_TDES,                                   /*!< Engine Selection = TDES                                 */   
}EN_CRYPTO_KL_RRKL_CRP_TYPE;


/**
 * \brief
 * enumurate to indicate the RRKL Engine type(cbc_type)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_CBC_TYPE_ECB,                                   /*!< Engine Selection = AES                                 */
    EN_CRYPTO_KL_RRKL_CBC_TYPE_CBC,                                   /*!< Engine Selection = TDES                                 */   
}EN_CRYPTO_KL_RRKL_CBC_TYPE;


/**
 * \brief
 * enumurate to indicate the RRKL Data Key Source(ct_key_sel)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_CT_KEY_SEL_KL,                                   /*!< Data Key Source = Output of the last level TDES                           */
    EN_CRYPTO_KL_RRKL_CT_KEY_SEL_CLEARCONTENTKEY,        /*!< Data Key Source = ClearContentKey			                          */   
}EN_CRYPTO_KL_RRKL_CT_KEY_SEL;

/**
 * \brief
 * enumurate to indicate the RRKL Root Key Selection(root_key_sel)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_ROOT_KEY_SEL_CLEARROOTKEY,                                   /*!< Root Key Selection = ClearRootKey			                                 */
    EN_CRYPTO_KL_RRKL_ROOT_KEY_SEL_OTP1ROOTKEY,        					  /*!< Root Key Selection = Reserved			                          		     */   
    EN_CRYPTO_KL_RRKL_ROOT_KEY_SEL_OTP2ROOTKEY,        			         /*!< Root Key Selection = OTP #2 root key			                          */  
    EN_CRYPTO_KL_RRKL_ROOT_KEY_SEL_BOOTDECRYPTTDESKEY,        		  /*!< Root Key Selection = Boot Decrypt TDES Key			                   */  
}EN_CRYPTO_KL_RRKL_ROOT_KEY_SEL;

/**
 * \brief
 * enumurate to indicate the RRKL Level number(lv_no)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_LEVEL_NUMBER_LEVEL0,                                   /*!< Level Number 0			                   */
    EN_CRYPTO_KL_RRKL_LEVEL_NUMBER_LEVEL1,        			  	   /*!< Level Number 1		                          */   
    EN_CRYPTO_KL_RRKL_LEVEL_NUMBER_LEVEL2,        			          /*!< Level Number 2			                   */  
    EN_CRYPTO_KL_RRKL_LEVEL_NUMBER_LEVEL3,        		  		   /*!< Level Number 3			                   */  
}EN_CRYPTO_KL_RRKL_LEVEL_NUMBER;


/**
 * \brief
 * enumurate to indicate the RRKL Data Idx Type(idx_h)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_DATA_IDX_1ST_IN,                                   /*!< 1st Level input data			*/
    EN_CRYPTO_KL_RRKL_DATA_IDX_2ND_IN,        			  	   /*!< 2nd Level input data		       */   
    EN_CRYPTO_KL_RRKL_DATA_IDX_3RD_IN,        			          /*!< 3rd Level input data			*/  
    EN_CRYPTO_KL_RRKL_DATA_IDX_CLEARROOTKEY,        		   /*!< ClearRootKey   				*/ 
    EN_CRYPTO_KL_RRKL_DATA_IDX_CLEARCONTENTKEY,        	   /*!< ClearContentKey			*/
    EN_CRYPTO_KL_RRKL_DATA_IDX_INITIALVECTOR,        	   /*!< InitialVector			*/
}EN_CRYPTO_KL_RRKL_DATA_IDX_H;
/**
 * \brief
 * enumurate to indicate the RRKL Data Idx Bits(idx_l)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_DATA_IDX_BIT_192,                                  /*!< DATA_IDX_BIT_192			                   */
    EN_CRYPTO_KL_RRKL_DATA_IDX_BIT_160,        			  	   /*!< DATA_IDX_BIT_160		                          */   
    EN_CRYPTO_KL_RRKL_DATA_IDX_BIT_128,        			          /*!< DATA_IDX_BIT_128			                   */  
    EN_CRYPTO_KL_RRKL_DATA_IDX_BIT_96,        		  		   /*!< DATA_IDX_BIT_96		                   	     */ 
    EN_CRYPTO_KL_RRKL_DATA_IDX_BIT_64,        		  		   /*!< DATA_IDX_BIT_64			                   */ 
    EN_CRYPTO_KL_RRKL_DATA_IDX_BIT_32,        		  		   /*!< DATA_IDX_BIT_32		                   	     */
}EN_CRYPTO_KL_RRKL_DATA_IDX_L;

/**
 * \brief
 * enumurate to indicate the RRKL TDES root ley len(root_key_len)
 */
typedef enum
{
	EN_CRYPTO_KL_RRKL_TDES_ROOT_KEY_LEN_64,
	EN_CRYPTO_KL_RRKL_TDES_ROOT_KEY_LEN_128,
	EN_CRYPTO_KL_RRKL_TDES_ROOT_KEY_LEN_192,
}EN_CRYPTO_KL_RRKL_TDES_ROOT_KEY_LEN;

/**
 * \brief
 * enumurate to indicate the RRKL TDES 1st len(1st_len)
 */
typedef enum
{
	EN_CRYPTO_KL_RRKL_TDES_1st_KEY_LEN_64,
	EN_CRYPTO_KL_RRKL_TDES_1st_KEY_LEN_128,
	EN_CRYPTO_KL_RRKL_TDES_1st_KEY_LEN_192,
}EN_CRYPTO_KL_RRKL_TDES_1st_LEN;

/**
 * \brief
 * enumurate to indicate the RRKL TDES 2nd len(2nd_len)
 */
typedef enum
{
	EN_CRYPTO_KL_RRKL_TDES_2nd_KEY_LEN_64,
	EN_CRYPTO_KL_RRKL_TDES_2nd_KEY_LEN_128,
	EN_CRYPTO_KL_RRKL_TDES_2nd_KEY_LEN_192,
}EN_CRYPTO_KL_RRKL_TDES_2nd_LEN;

/**
 * \brief
 * enumurate to indicate the RRKL TDES 3rd len(3rd_len)
 */
typedef enum
{
	EN_CRYPTO_KL_RRKL_TDES_3rd_KEY_LEN_64,
	EN_CRYPTO_KL_RRKL_TDES_3rd_KEY_LEN_128,
	EN_CRYPTO_KL_RRKL_TDES_3rd_KEY_LEN_192,
}EN_CRYPTO_KL_RRKL_TDES_3rd_LEN;

/**
 * \brief
 * enumurate to indicate the RRKL TDES Key option (Tdes_kl_key_opt)
 */
typedef enum
{
    EN_CRYPTO_KL_RRKL_TDES_KEY_OPT0,                                   /*!< Option1: Key1 != Key2 != Key3                      */
    EN_CRYPTO_KL_RRKL_TDES_KEY_OPT1,                                   /*!< Option2: Key1 = Key3 != Key2                      */
    EN_CRYPTO_KL_RRKL_TDES_KEY_OPT2,					      /*!< Option3: Key1 = Key3 = Key2                      */ 	
}EN_CRYPTO_KL_RRKL_TDES_KEY_OPT;


/**
 * \brief
 * enumurate to indicate the TSKL Engine type(crp_type)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_CRP_TYPE_AES,                                   /*!< Engine Selection = AES                                 */
    EN_CRYPTO_KL_TSKL_CRP_TYPE_TDES,                                   /*!< Engine Selection = TDES                                 */   
}EN_CRYPTO_KL_TSKL_CRP_TYPE;


/**
 * \brief
 * enumurate to indicate the TSKL Engine type(cbc_type)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_CBC_TYPE_ECB,                                   /*!< Engine Selection = AES                                 */
    EN_CRYPTO_KL_TSKL_CBC_TYPE_CBC,                                   /*!< Engine Selection = TDES                                 */   
}EN_CRYPTO_KL_TSKL_CBC_TYPE;


/**
 * \brief
 * enumurate to indicate the TSKL Data Key Source(ct_key_sel)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_CT_KEY_SEL_KL,                                   /*!< Data Key Source = Output of the last level TDES                           */
    EN_CRYPTO_KL_TSKL_CT_KEY_SEL_CLEARCONTENTKEY,        /*!< Data Key Source = ClearContentKey			                          */   
}EN_CRYPTO_KL_TSKL_CT_KEY_SEL;

/**
 * \brief
 * enumurate to indicate the TSKL Root Key Selection(root_key_sel)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_ROOT_KEY_SEL_CLEARROOTKEY,                                   /*!< Root Key Selection = ClearRootKey			                                 */
    EN_CRYPTO_KL_TSKL_ROOT_KEY_SEL_OTP1ROOTKEY,        				  /*!< Root Key Selection = OTP #1 root key			                          */   
    EN_CRYPTO_KL_TSKL_ROOT_KEY_SEL_OTP2ROOTKEY,        			         /*!< Root Key Selection = OTP #2 root key			                          */  
    EN_CRYPTO_KL_TSKL_ROOT_KEY_SEL_BOOTDECRYPTTDESKEY,        		  /*!< Root Key Selection = Boot Decrypt TDES Key			                   */  
}EN_CRYPTO_KL_TSKL_ROOT_KEY_SEL;

/**
 * \brief
 * enumurate to indicate the TSKL Data Idx Type(idx_h)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_DATA_IDX_1ST_IN,                                   /*!< 1st Level input data			*/
    EN_CRYPTO_KL_TSKL_DATA_IDX_2ND_IN,        			  	   /*!< 2nd Level input data		       */   
    EN_CRYPTO_KL_TSKL_DATA_IDX_3RD_IN,        			          /*!< 3rd Level input data			*/  
    EN_CRYPTO_KL_TSKL_DATA_IDX_CLEARROOTKEY,        		   /*!< ClearRootKey   				*/ 
    EN_CRYPTO_KL_TSKL_DATA_IDX_CLEARCONTENTKEY,        	   /*!< ClearContentKey			*/
    EN_CRYPTO_KL_TSKL_DATA_IDX_INITIALVECTOR,        	   /*!< Initial Vector			*/
}EN_CRYPTO_KL_TSKL_DATA_IDX_H;
/**
 * \brief
 * enumurate to indicate the TSKL Data Idx Bits(idx_l)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_DATA_IDX_BIT_192,                                  /*!< DATA_IDX_BIT_192			                   */
    EN_CRYPTO_KL_TSKL_DATA_IDX_BIT_160,        			  	   /*!< DATA_IDX_BIT_160		                          */   
    EN_CRYPTO_KL_TSKL_DATA_IDX_BIT_128,        			          /*!< DATA_IDX_BIT_128			                   */  
    EN_CRYPTO_KL_TSKL_DATA_IDX_BIT_96,        		  		   /*!< DATA_IDX_BIT_96		                   	     */ 
    EN_CRYPTO_KL_TSKL_DATA_IDX_BIT_64,        		  		   /*!< DATA_IDX_BIT_64			                   */ 
    EN_CRYPTO_KL_TSKL_DATA_IDX_BIT_32,        		  		   /*!< DATA_IDX_BIT_32		                   	     */
}EN_CRYPTO_KL_TSKL_DATA_IDX_L;

/**
 * \brief
 * enumurate to indicate the TSKL TS descrambler selection(ts_desc_sel)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_DESC_SEL_CSA0,                                   /*!< TS descrambler = DVB CSA0			      */
    EN_CRYPTO_KL_TSKL_DESC_SEL_CSA1,        				     /*!< TS descrambler = DVB CSA1			             */   
}EN_CRYPTO_KL_TSKL_DESC_SEL;

/**
 * \brief
 * enumurate to indicate the TSKL Key table number(key_tab_no)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_KEY_TABLE_NO0,                                   /*!< key table number = 0			                    */
    EN_CRYPTO_KL_TSKL_KEY_TABLE_NO1,        				      /*!< key table number = 1			                    */ 
    EN_CRYPTO_KL_TSKL_KEY_TABLE_NO2,        				      /*!< key table number = 2			                    */ 
    EN_CRYPTO_KL_TSKL_KEY_TABLE_NO3,        				      /*!< key table number = 3			                    */ 
    EN_CRYPTO_KL_TSKL_KEY_TABLE_NO4,        				      /*!< key table number = 4			                    */ 
    EN_CRYPTO_KL_TSKL_KEY_TABLE_NO5,        				      /*!< key table number = 5			                    */ 
}EN_CRYPTO_KL_TSKL_KEY_TABLE_NO;

/**
 * \brief
 * enumurate to indicate the TSKL Key no(key_no)
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_KEY_NO_EVEN,                                      /*!< even key			      */
    EN_CRYPTO_KL_TSKL_KEY_NO_ODD,        				     /*!< odd key			      */   
}EN_CRYPTO_KL_TSKL_KEY_NO;

/**
 * \brief
 * enumurate to indicate the TSKL Level number
 */
typedef enum
{
    EN_CRYPTO_KL_TSKL_LEVEL_NUMBER_LEVEL0,                                   /*!< Level Number 0			                   */
    EN_CRYPTO_KL_TSKL_LEVEL_NUMBER_LEVEL1,        			  	   /*!< Level Number 1		                          */   
    EN_CRYPTO_KL_TSKL_LEVEL_NUMBER_LEVEL2,        			          /*!< Level Number 2			                   */  
    EN_CRYPTO_KL_TSKL_LEVEL_NUMBER_LEVEL3,        		  		   /*!< Level Number 3			                   */  
}EN_CRYPTO_KL_TSKL_LEVEL_NUMBER;


/**
 * \brief
 * enumurate to indicate the crypto-engine block cipher mode
 */
typedef enum
{
    EN_CRYPTO_CE_BLOCK_CIPHER_ECB,                            /*!< Crypto-Engine used ECB mode                */
    EN_CRYPTO_CE_BLOCK_CIPHER_CBC,                            /*!< Crypto-Engine used CBC mode                */		
    EN_CRYPTO_CE_BLOCK_CIPHER_CTR,				      /*!< Crypto-Engine used CTR mode                */ 	
}EN_CRYPTO_CE_BLOCK_CIPHER;

/**
 * \brief
 * enumurate to indicate the crypto-engine operation mode
 */
typedef enum
{
    EN_CRYPTO_CE_OP_ENCRYPT,                               /*!< Crypto-Engine operation by encryption mode    */	
    EN_CRYPTO_CE_OP_DECRYPT,                               /*!< Crypto-Engine operation by decryption mode    */
}EN_CRYPTO_CE_OP;

/**
 * \brief
 * enumurate to indicate the crypto-engine work mode
 */
typedef enum
{
    EN_CRYPTO_CE_WORK_IO,                                  /*!< Crypto-Engine work by IO mode    */
    EN_CRYPTO_CE_WORK_DMA,                               /*!< Crypto-Engine work by DMA mode    */
}EN_CRYPTO_CE_WORK;

/**
 * \brief
 * enumurate to indicate the crypto-engine resd mode(resd_mode)
 */
typedef enum
{
    EN_CRYPTO_CE_RESD_MODE_BYPASS,                                  /*!< Bypass    */
    EN_CRYPTO_CE_RESD_MODE_CYCLE_STEAL,                        /*!< Cycle steal    */
}EN_CRYPTO_CE_RESD_MODE;


/**
 * \brief
 * enumurate to indicate the crypto-engine SHA type
 */
typedef enum
{
    EN_CRYPTO_CE_SHA_TYPE_SHA1,                                  /*!< SHA1    */
    EN_CRYPTO_CE_SHA_TYPE_SHA256,                              /*!< SHA256    */
}EN_CRYPTO_CE_SHA_TYPE;

/**
 * \brief
 * enumurate to indicate the RRKL Reorder Option(reorder_opt)
 */
typedef enum
{
	NOT_REORDER_OPT,
	REORDER_OPT,
}EN_CRYPTO_KL_TDES_REORDER_OPT;

/**
 * \brief
 *  the KeyLadder initial structure
 */
typedef struct
{
   u32 u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_CRYPTO_INIT_PARAMS, *PST_DRV_CRYPTO_INIT_PARAMS;

/**
 * \brief
 *  the KeyLadder terminate structure
 */
typedef struct
{	
    u32 u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_CRYPTO_KL_TERM_PARAMS, *PST_DRV_CRYPTO_KL_TERM_PARAMS;

/**
 * \brief
 *  the Crypto Engine OS Init structure
 */
typedef struct
{
    u32 u32Reserved;                    /*!< Reserved for future used               */
}ST_DRV_CRYPTO_OS_INIT_PARAMS, *PST_DRV_CRYPTO_OS_INIT_PARAMS;

/**
 * \brief
 *  the KeyLadder Key index structure
 */
typedef struct
{
    EN_CRYPTO_KL_RRKL_DATA_IDX_L enDataIdxL;
    EN_CRYPTO_KL_RRKL_DATA_IDX_H enDataIdxH;		
}ST_DRV_CRYPTO_KL_RRKL_DATA_IDX, *PST_DRV_CRYPTO_KL_RRKL_DATA_IDX;

/**
 * \brief
 *  the KeyLadder Key index structure
 */
typedef struct
{
    ST_DRV_CRYPTO_KL_RRKL_DATA_IDX stKeyIdx;
    u8* pu8InputKeyData;
    u32 u32InputKeyDataLen;
	u8* pu8InputIVData;
    u32 u32InputIVDataLen;
}ST_DRV_CRYPTO_KL_KEY_INFO, *PST_DRV_CRYPTO_KL_KEY_INFO;

/**
 * \brief
 *  the R2R KeyLadder configure structure
 */
typedef struct
{
	EN_CRYPTO_KL_RRKL_CBC_TYPE enCBCType;
    EN_CRYPTO_KL_RRKL_CRP_TYPE enCrpType;
    EN_CRYPTO_KL_RRKL_CT_KEY_SEL enCtKeySel;
    EN_CRYPTO_KL_RRKL_ROOT_KEY_SEL enRootKeySel;
    EN_CRYPTO_KL_RRKL_LEVEL_NUMBER enLvno;

    ST_DRV_CRYPTO_KL_RRKL_DATA_IDX st1stIdx;
    ST_DRV_CRYPTO_KL_RRKL_DATA_IDX st2ndIdx;	
    ST_DRV_CRYPTO_KL_RRKL_DATA_IDX st3rdIdx;	

    ST_DRV_CRYPTO_KL_KEY_INFO stClearContentKey;
    ST_DRV_CRYPTO_KL_KEY_INFO stClearRootKey;
	
    u8* pu8Input1stData;
    u32 u32Input1stDataLen;
    u8* pu8Input2ndData;
    u32 u32Input2ndDataLen;
    u8* pu8Input3rdData;
    u32 u32Input3rdDataLen;	
	
    EN_CRYPTO_KL_RRKL_TDES_ROOT_KEY_LEN u32TDESRootKeyLen;
    EN_CRYPTO_KL_RRKL_TDES_1st_LEN u32TDES1stLen;
    EN_CRYPTO_KL_RRKL_TDES_2nd_LEN u32TDES2ndLen;
    EN_CRYPTO_KL_RRKL_TDES_3rd_LEN u32TDES3rdLen;

    bool b8DeactivationFlag;
	
	EN_CRYPTO_KL_TDES_REORDER_OPT u32TDESReorderOpt;
}ST_DRV_CRYPTO_KL_RRKL_PARAMS, *PST_DRV_CRYPTO_KL_RRKL_PARAMS;

/**
 * \brief
 *  the R2R KeyLadder configure structure
 */
typedef struct
{
	EN_CRYPTO_KL_TSKL_CBC_TYPE enCBCType;
    EN_CRYPTO_KL_TSKL_CRP_TYPE enCrpType;
    EN_CRYPTO_KL_TSKL_CT_KEY_SEL enCtKeySel;
    EN_CRYPTO_KL_TSKL_ROOT_KEY_SEL enRootKeySel;

    ST_DRV_CRYPTO_KL_KEY_INFO stClearContentKey;
    ST_DRV_CRYPTO_KL_KEY_INFO stClearRootKey;
	
    ST_DRV_CRYPTO_KL_RRKL_DATA_IDX st1stIdx;
    ST_DRV_CRYPTO_KL_RRKL_DATA_IDX st2ndIdx;	
    ST_DRV_CRYPTO_KL_RRKL_DATA_IDX st3rdIdx;	
	
    EN_CRYPTO_KL_TSKL_DESC_SEL enDescSel;
    EN_CRYPTO_KL_TSKL_KEY_TABLE_NO enKeyTabNo;
    EN_CRYPTO_KL_TSKL_KEY_NO enKeyNo;	

    EN_CRYPTO_KL_TSKL_LEVEL_NUMBER enLvno;
    	
    u8* pu8Input1stData;
    u32 u32Input1stDataLen;
    u8* pu8Input2ndData;
    u32 u32Input2ndDataLen;
    u8* pu8Input3rdData;
    u32 u32Input3rdDataLen;	
	
    bool b8DeactivationFlag;
	
	EN_CRYPTO_KL_TDES_REORDER_OPT u32TDESReorderOpt;
}ST_DRV_CRYPTO_KL_TSKL_PARAMS, *PST_DRV_CRYPTO_KL_TSKL_PARAMS;

/**
 * \brief
 *  the Crypto mode :  AES, config structure
 */
typedef struct
{
    u8*                             pu8InputData;
    u32                             u32InputDataLen;
    u8*                             pu8OutputData;
    u32                             u32OutputDataLen;
    u8                              au8InitialVector[DRV_CRYPTO_AES_CW_LENGTH];
    u8                              au8Key[DRV_CRYPTO_AES_CW_LENGTH];
    bool 				   b8LoadKey; 		
    EN_CRYPTO_CE_RESD_MODE 		enResdMode;	
    EN_CRYPTO_CE_BLOCK_CIPHER 	enBlockCipher;
    EN_CRYPTO_CE_OP		    		enOperation;
    EN_CRYPTO_CE_WORK			enWork;
}ST_DRV_CRYPTO_AES_PARAMS, *PST_DRV_CRYPTO_AES_PARAMS;

/**
 * \brief
 *  the Crypto mode :  TDES, config structure
 */
typedef struct
{
    u8*                             pu8InputData;
    u32                             u32InputDataLen;
    u8*                             pu8OutputData;
    u32                             u32OutputDataLen;
    u8                              au8InitialVector[DRV_CRYPTO_TDES_CW_LENGTH];
    u8                              au8Key1[DRV_CRYPTO_TDES_CW_LENGTH];
    u8                              au8Key2[DRV_CRYPTO_TDES_CW_LENGTH];
    u8                              au8Key3[DRV_CRYPTO_TDES_CW_LENGTH];	
    bool 				   b8LoadKey; 
    EN_CRYPTO_CE_RESD_MODE 		enResdMode;	
    EN_CRYPTO_KL_RRKL_TDES_KEY_OPT 	enTDESKeyOpt;
    EN_CRYPTO_CE_BLOCK_CIPHER 	enBlockCipher;
    EN_CRYPTO_CE_OP		    		enOperation;
    EN_CRYPTO_CE_WORK			enWork;
}ST_DRV_CRYPTO_TDES_PARAMS, *PST_DRV_CRYPTO_TDES_PARAMS;

/**
 * \brief
 *  the Crypto mode :  Multi2, config structure
 */
typedef struct
{
    u8*                             pu8InputData;
    u32                             u32InputDataLen;
    u8*                             pu8OutputData;
    u32                             u32OutputDataLen;
    u8                              au8DataKey[DRV_CRYPTO_M2_DATA_CW_LENGTH];
    u8                              au8SystemKey[DRV_CRYPTO_M2_SYSTEM_CW_LENGTH];
    u8                              au8InitialVector[DRV_CRYPTO_M2_DATA_CW_LENGTH];
    u32                             u32RoundNo;
    EN_CRYPTO_CE_RESD_MODE 		enResdMode;	
    EN_CRYPTO_CE_BLOCK_CIPHER enBlockCipher;
    EN_CRYPTO_CE_OP		    enOperation;
    EN_CRYPTO_CE_WORK			enWork;
}ST_DRV_CRYPTO_MULTI2_PARAMS, *PST_DRV_CRYPTO_MULTI2_PARAMS;

/**
 * \brief
 *  the Crypto mode :  SHA, config structure
 */
typedef struct
{
    u8*                             pu8InputData;
    u32                             u32InputDataLen;
    u8*                             pu8OutputData;
    u32                             u32OutputDataLen;
    EN_CRYPTO_CE_SHA_TYPE enSHAType;
}ST_DRV_CRYPTO_SHA_PARAMS, *PST_DRV_CRYPTO_SHA_PARAMS;


//---Global Function prototypes for public use---------------------------------
ErrorCode DRV_CRYPTO_Initialize(DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_INIT_PARAMS pstParams);
 
ErrorCode DRV_CRYPTO_KL_RRKL_Start(DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_KL_RRKL_PARAMS pstParams); 
ErrorCode DRV_CRYPTO_KL_TSKL_Start(DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_KL_TSKL_PARAMS pstParams);

ErrorCode DRV_CRYPTO_CE_AES_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_AES_PARAMS pstCfg);
ErrorCode DRV_CRYPTO_CE_AES_DMA_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_AES_PARAMS pstCfg);
ErrorCode DRV_CRYPTO_CE_TDES_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_TDES_PARAMS pstCfg);
ErrorCode DRV_CRYPTO_CE_TDES_DMA_Cipher (DRV_DeviceNameType DeviceName,PST_DRV_CRYPTO_TDES_PARAMS pstCfg);
ErrorCode DRV_CRYPTO_CE_MULTI2_Cipher (DRV_DeviceNameType DeviceName,PST_DRV_CRYPTO_MULTI2_PARAMS pstCfg);
ErrorCode DRV_CRYPTO_CE_MULTI2_DMA_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_MULTI2_PARAMS pstCfg);
ErrorCode DRV_CRYPTO_CE_SHA_Cipher (DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_SHA_PARAMS pstCfg);


ErrorCode DRV_CRYPTO_KL_Terminate(DRV_DeviceNameType DeviceName, PST_DRV_CRYPTO_KL_TERM_PARAMS pstParams);


#endif /* __DRV_CRYPTO_H__ */
