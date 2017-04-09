#ifndef __RT_WIFI_IOCTL_H__
#define __RT_WIFI_IOCTL_H__

#include "def_type.h"

#define WIFI_ENC_MODE_NONE	0
#define WIFI_ENC_MODE_WEP		1
#define WIFI_ENC_MODE_WPA_AES		2
#define WIFI_ENC_MODE_WPA_TKIP		3
#define WIFI_ENC_MODE_WPA2_AES		4
#define WIFI_ENC_MODE_WPA2_TKIP	5

#define WIFI_SET_SYS_ERR				-1
#define WIFI_SET_KEY_FAIL			-2
#define WIFI_SET_SSID_FAIL			-3

/* Reason code definitions */
#define REASON_RESERVED                 0
#define REASON_UNSPECIFY                1
#define REASON_NO_LONGER_VALID          2
#define REASON_DEAUTH_STA_LEAVING       3
#define REASON_DISASSOC_INACTIVE        4
#define REASON_DISASSPC_AP_UNABLE       5
#define REASON_CLS2ERR                  6
#define REASON_CLS3ERR                  7
#define REASON_DISASSOC_STA_LEAVING     8
#define REASON_STA_REQ_ASSOC_NOT_AUTH   9
#define REASON_INVALID_IE               13
#define REASON_MIC_FAILURE              14
#define REASON_4_WAY_TIMEOUT            15
#define REASON_GROUP_KEY_HS_TIMEOUT     16
#define REASON_IE_DIFFERENT             17
#define REASON_MCIPHER_NOT_VALID        18
#define REASON_UCIPHER_NOT_VALID        19
#define REASON_AKMP_NOT_VALID           20
#define REASON_UNSUPPORT_RSNE_VER       21
#define REASON_INVALID_RSNE_CAP         22
#define REASON_8021X_AUTH_FAIL          23
#define REASON_CIPHER_SUITE_REJECTED    24
#define REASON_DECLINED                 37

#define REASON_QOS_UNSPECIFY              32
#define REASON_QOS_LACK_BANDWIDTH         33
#define REASON_POOR_CHANNEL_CONDITION     34
#define REASON_QOS_OUTSIDE_TXOP_LIMITION  35
#define REASON_QOS_QSTA_LEAVING_QBSS      36
#define REASON_QOS_UNWANTED_MECHANISM     37
#define REASON_QOS_MECH_SETUP_REQUIRED    38
#define REASON_QOS_REQUEST_TIMEOUT        39
#define REASON_QOS_CIPHER_NOT_SUPPORT     45


#define REASON_FT_INVALID_FTIE				55

typedef void (*WIFI_INS_CALLBACK)(void);
typedef void (*WIFI_REM_CALLBACK)(void);
typedef void (*WIFI_CONNECT_CALLBACK)(void);
typedef void (*WIFI_DISCONNECT_CALLBACK)(u32);

typedef struct ap_list
{
	u8	essid[32];
	u8 MAC[6];
	u8 quality;
	u8 encryption;
} ap_list;

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
} ST_DRV_WIFI_IP_SETTING, *PST_DRV_WIFI_IP_SETTING;

int NvtWifi_Init(u32 wifiDrvPoolHandle);
void NvtWifi_GetIFMAC(u8 *mac, u32 len);
int NvtWifi_GetAPList(struct ap_list **list, u32 *number);
unsigned char NvtWifi_GetAPQuality(void);
void NvtWifi_FreeAPList(struct ap_list *list);
int NvtWifi_SetAPESSID(u8 *ESSID, u32 len);
int NvtWifi_SetEncKey(u8 *key, u32 len);
int NvtWifi_SetEncMode(u32 mode);
int NvtWifi_Associate(void);
int NvtWifi_DeAssociate(void);
ErrorCode NvtWifi_StartDhcp(PST_DRV_WIFI_IP_SETTING pstIpSetting);
void NvtWifi_DhcpDown(void);
ErrorCode NvtWifi_SetupIf(PST_DRV_WIFI_IP_SETTING pstIpSetting);
void NvtWifi_Scan(void);
void NvtWifi_SetAutoReconn(u8 enable);
void  NvtWifi_RegisterInsCallback(WIFI_INS_CALLBACK pfCb);
void  NvtWifi_RegisterRemCallback(WIFI_REM_CALLBACK pfCb);
void  NvtWifi_RegisterConnectCallback(WIFI_CONNECT_CALLBACK pfCb);
void  NvtWifi_RegisterDisconnectCallback(WIFI_DISCONNECT_CALLBACK pfCb);

#endif
