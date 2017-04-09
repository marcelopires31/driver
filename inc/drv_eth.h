//**************************************************************************
//      Copyright (c) , Inc . All rights reserved.
//      STB/SA, all right reserved.
//
//  Product : STB Firmware
//
//  Date    :
//  Author  :
//  Purpose : Provide Ethernet(ETH) Control
//  Sources :
//***************************************************************************
//
// Modification use :
//**************************************************************************
//  Update
//
//  Date    :
//  Name    :
//  Description :
//
//  Item                              Source
//   ----------------------------------------        -------------------

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__

#include "sw_config.h"
#include "def_type.h"
#include "def_err.h"
#include "drv_config.h"
//#include "reg_eth_mac.h"
//#include "reg_eth_phy.h"
#include "drv_gpio.h"
#include "sen5_sw_config.h"   //add by wujiang

/*
 * Brief: DRV_ETH global define.
 */
// For CVT Test defines
#define TEST_FRAME_FILTER_FLOW_CONTROL

//#define ETHERNET_FRAME_MAX_DATA_BYTE      (1544)    // need to follow 8 alignment
#define ETHERNET_FRAME_MAX_DATA_BYTE        (1568)    // need to follow 32 alignment

#define FLASH_MAC_OFFSET (368)

/*
 * Brief: ETH Error code definition.
 */
enum
{
    ERROR_ETH_DEV_NAME     = ERROR_BASE_DRV_ETH,                    /*!< Device Name Error                                          */
    ERROR_ETH_DEV_RESOURCE,                                         /*!< ETH don't have device resource                             */
    ERROR_ETH_IS_OPEN,                                              /*!< ETH is open                                                */
    ERROR_ETH_IS_ENABLE,                                            /*!< ETH is enable                                              */
    ERROR_ETH_CLOSED_HANDLE,                                        /*!< Input Handle is closed.                                    */
    ERROR_ETH_RINGBUG_ALLOC,                                        /*!< Ring buffer allocate fail.                                 */
    ERROR_ETH_BUF_TOO_SMALL,                                        /*!< Input buffer size too small to send/get ethernet frame.    */
    ERROR_ETH_BUF_NOT_READY,                                        /*!< ring buffer is not ready for set/get data.                 */
    ERROR_ETH_BUF_EMPTY,                                            /*!< ring buffer is empty that data can not be got.             */
    ERROR_ETH_BUF_INVALID,                                          /*!< bad packets can not be used.                               */
    ERROR_ETH_UNSUPPORT,                                            /*!< Un-support MAC control Type                                */
    ERROR_ETH_HW_CONFIRM,                                           /*!< ETH confirm hardware setting fail                          */
    ERROR_ETH_AN_FAIL,                                              /*!< ETH Auto-Negotiation Fail                                  */
    ERROR_ETH_LINK_DOWN,                                            /*!< ETH Link Down                                              */
    ERROR_ETH_BAD_MAC_ADDRESS,										/*!< Bad MAC address											*/
    ERROR_ETH_DO_DHCP,                                              /*!< ETH do_dhcp() fail                                         */
    ERROR_ETH_INIT_NET,                                             /*!< ETH init_net() fail                                        */
};

/**
 * \brief
 *  enumurate to indicate the ETH Speed mode
 */
typedef enum
{
    EN_DRV_ETH_SPEED_MODE_NONE,                                 /*!< Link Down                                       */
    EN_DRV_ETH_SPEED_MODE_10MBPS,                               /*!< Speed 10M bps                                   */
    EN_DRV_ETH_SPEED_MODE_100MBPS,                              /*!< Speed 100M bps                                  */
    EN_DRV_ETH_SPEED_MODE_1000MBPS,                             /*!< Speed 1000M bps                                 */
    EN_DRV_ETH_SPEED_MODE_NUM,                                  /*!< Total Speed                                     */
} EN_DRV_ETH_SPEED_MODE;

/**
 * \brief
 *  enumurate to indicate the ETH Duplex mode
 */
typedef enum
{
    EN_DRV_ETH_DUPLEX_MODE_NONE,                                /*!< Link Down                                       */
    EN_DRV_ETH_DUPLEX_MODE_HALF,                                /*!< Half Duplex Mode                                */
    EN_DRV_ETH_DUPLEX_MODE_FULL,                                /*!< Full Duplex Mode                                */
    EN_DRV_ETH_DUPLEX_MODE_NUM,                                 /*!< Total Duplex Mode                               */
} EN_DRV_ETH_DUPLEX_MODE;

/**
 * \brief
 *  enumurate to indicate the ETH Link Status
 */
typedef enum
{
    EN_DRV_ETH_LINK_STATUS_LINKDOWN,                            /*!< Link Down                                       */
    EN_DRV_ETH_LINK_STATUS_LINKUP,                              /*!< Link UP                                         */
    EN_DRV_ETH_LINK_STATUS_NUM,                                 /*!< Total Link Status                               */
} EN_DRV_ETH_LINK_STATUS;

/**
 * \brief
 *  enumurate to indicate the ETH LoopBack Mode
 */
typedef enum
{
    EN_DRV_ETH_LOOPBACK_MODE_DISABLE = 0 ,                           /*!< LoopBack Disable                                */
    EN_DRV_ETH_LOOPBACK_MODE_ENABLE,                            /*!< LoopBack Enable                                 */
    EN_DRV_ETH_LOOPBACK_MODE_NUM,                               /*!< Total LoopBack Mode                             */
    EN_DRV_ETH_10M_MAC_LOOPBACK_MODE,
    EN_DRV_ETH_100M_MAC_LOOPBACK_MODE,
    EN_DRV_ETH_10M_PHY_LOOPBACK_MODE,
    EN_DRV_ETH_100M_PHY_LOOPBACK_MODE,
} EN_DRV_ETH_LOOPBACK_MODE;

/**
 * \brief
 *  enumurate to indicate the ETH LoopBack Mode
 */
typedef enum
{
    EN_DRV_ETH_FILTER_NONE = 0 ,                                /*!< Filter None                                */
    EN_DRV_ETH_FILTER_RECEIVE_ALL,                              /*!< Filter receiver all                        */
    EN_DRV_ETH_FILTER_PASS_ALL_MULTICAST,                       /*!< Filter All Multicast                       */
    EN_DRV_ETH_FILTER_MODE_NUM,
} EN_DRV_ETH_FILTER_MODE;

/**
 * \brief
 *  The ETH HAL MAC DMA Descriptor structure
 *    The structure is common for both receive and transmit descriptors
 */
typedef struct
{
    u32   u32Status;         /* Status */
    u32   u32Length;         /* Buffer length */
    u32   u32Buffer1;        /* Buffer 1 pointer */
    u32   u32Buffer2;        /* Buffer 2 pointer or next descriptor pointer in chain structure */
    u32   u32Data1;          /* driver data, are not used by DMA engine,                       */
    u32   u32Data2;          /* set DmaDescriptorSkip4 in DmaBusModeInit to skip these words */
    u32   au32Data[2];       /* set DmaDescriptorSkip4 in DmaBusModeInit to skip these words */
} ST_DRV_ETH_HAL_DMA_DESC, *PST_DRV_ETH_HAL_DMA_DESC;

/*******************************************************************************************/
/**
 * \brief
 *  the ETH MAC control block structure
 */
typedef struct
{
    u32                                     u32TxBlockNum;
    u32                                     u32RxBlockNum;
    PST_DRV_ETH_HAL_DMA_DESC                pstTxDesc;
    PST_DRV_ETH_HAL_DMA_DESC                pstRxDesc;
    u8*                                     pu8TxDataBuffer;
    u8*                                     pu8RxDataBuffer;
    u32                                     u32TxBlockIdx;
    u32                                     u32RxBlockIdx;
    u8                                      au8MacAddr[6];
    u32                                     u32CurIntStatus;
    EN_DRV_ETH_LINK_STATUS                  enLinkStatus;
    EN_DRV_ETH_DUPLEX_MODE                  enDuplexMode;
    EN_DRV_ETH_SPEED_MODE                   enSpeedMode;
    EN_DRV_ETH_LOOPBACK_MODE                enLoopBackMode;
    EN_DRV_ETH_FILTER_MODE                  enFilterMode;
}ST_DRV_ETH_MAC_CTRL_BLOCK, *PST_DRV_ETH_MAC_CTRL_BLOCK;

/**
 * \brief
 *  the ETH Callback function pointer
 */
typedef void (*ETH_INS_CALLBACK)(void);
typedef void (*ETH_REM_CALLBACK)(void);
#if CONFIG_FREEBSD_TCP
typedef void (*ETH_ADDNETIF_CALLBACK)(ErrorCode);
#endif

/**
 * \brief
 *  the ETH initialize structure
 */
typedef struct
{
    u32     u32MemPoolHandle;
    u32     u32TxBlockNum;
    u32     u32RxBlockNum;
    u8      au8MacAddr[6];
} ST_DRV_ETH_INIT_PARAMS, *PST_DRV_ETH_INIT_PARAMS;

#if CONFIG_FREEBSD_TCP
/*!
 * \brief
 * Structure of IP setting data
 */
typedef struct
{
	bool b8Dhcp;
	u8 au8Ip[4];
	u8 au8Nm[4];
	u8 au8Gw[4];
	u8 au8Dns[4];
	u8 au8AuxDns[4];
} ST_DRV_ETH_IP_SETTING, *PST_DRV_ETH_IP_SETTING;
#endif

/**
 * \brief
 *  the ETH terminate structure
 */
typedef struct
{
    bool    b8Force;                        /*!< Force terminate ETH                    */
} ST_DRV_ETH_TERM_PARAMS, *PST_DRV_ETH_TERM_PARAMS;

//function define
u8* DRV_ETH_GetVersion (void);
/*!\fn u8* DRV_ETH_GetVersion (void)
 * \brief
 *        Get the ETH's Version number string
 *
 *
 * \return ETH Version String
 *
 */

void DRV_ETH_SetResetLanGpio(u32 u32ResetLanGpioHandle, PST_GPIO pstResetLanGpio);

bool DRV_ETH_IsLinkUp(void);

void DRV_ETH_RegisterInsCallback(ETH_INS_CALLBACK pfCb);

void DRV_ETH_RegisterRemCallback(ETH_REM_CALLBACK pfCb);

#if CONFIG_FREEBSD_TCP
void DRV_ETH_RegisterAddNetIfCallback(ETH_ADDNETIF_CALLBACK pfCb);
#endif

ErrorCode DRV_ETH_Init            (PST_DRV_ETH_INIT_PARAMS pstParams, EN_DRV_ETH_LOOPBACK_MODE enLoopbackmode);
/*!\fn ErrorCode DRV_ETH_Init (DRV_DeviceNameType DeviceName, PST_DRV_ETH_INIT_PARAMS pstParams, EN_DRV_ETH_LOOPBACK_MODE enLoopbackmode)
 * \brief
 *  Initial the ETH with ST_DRV_ETH_INIT_PARAMS setting
 *
 * \param DeviceName                        (Input)  Device Name
 * \param pstParams                         (Input)  Init parameter
 * \param enLoopbackmode                    (Input)  Init Loopbackmode
 *
 * \return ETH Operation Error Code
 * \retval ERROR_NO_ERROR                   Operation Success
 * \retval ERROR_ETH_DEV_RESOURCE           ETH don't have device resource
 * \retval ERROR_BAD_PARAMETER              Parameter error
 * \retval ERROR_INITIALISED                ETH already Init
 * \retval ERROR_ETH_RINGBUG_ALLOC          Ring buffer allocate fail
 *
 */

ErrorCode DRV_ETH_Term          (PST_DRV_ETH_TERM_PARAMS pstParams);
/*!\fn ErrorCode DRV_ETH_Term (DRV_DeviceNameType DeviceName, PST_DRV_ETH_TERM_PARAMS pstParams)
 * \brief
 *        Terminate the ETH with ST_DRV_ETH_TERM_PARAMS setting
 *
 * \param DeviceName                        (Input)  Device Name
 * \param pstParams                         (Input)  Term parameter
 *
 * \return ETH Operation Error Code
 * \retval ERROR_NO_ERROR                   Operation Success
 * \retval ERROR_BAD_PARAMETER              Parameter error
 * \retval ERROR_ETH_IS_OPEN                Device still open can't be terminated
 * \retval ERROR_ETH_DEV_NAME               Device name is not init
 *
 */

#if CONFIG_FREEBSD_TCP
ErrorCode DRV_ETH_AddNetIf(PST_DRV_ETH_IP_SETTING pstIpSttng);

void DRV_ETH_DhcpDown(void);

void DRV_ETH_ReInitRoute(void);

#endif

#ifdef TEST_FRAME_FILTER_FLOW_CONTROL
void DRV_ETH_SetFrameFilter(EN_DRV_ETH_FILTER_MODE enMode);

void DRV_ETH_Send_FC_BP(bool bEnable, u32 u32PT);
#endif

#endif  //__DRV_ETH_H__
