//**************************************************************************
//			Copyright (c) , Inc . All rights reserved.
//			STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date	: 
//	Author	: 
//	Purpose	: Provide 2WS Control
//	Sources	: 
//***************************************************************************
//
//	Modification use :
//**************************************************************************
//	Update
//
//	Date		: 
//	Name		: 
//	Description	: 
//
//	Item											Source
//  ----------------------------------------		-------------------

#ifndef __DRV_2WS_H__
#define __DRV_2WS_H__

/*-----------------------------------------------------------------------------*/
/* Including Files                                                             */
/*-----------------------------------------------------------------------------*/
#include "os.h"
#include "def_type.h"
#include "drv_gpio.h"
#include "drv_sys.h"

/*-----------------------------------------------------------------------------*/
/* Constant Definitions                                                        */
/*-----------------------------------------------------------------------------*/
/*
 2WS Time Out value, this value is depended on rate of 2WS.
 if the rate of 2WS is faster, this value will adjust bigger.
 byte_num * bit_num(9)  / Freq(Khz) * 1.2 * 200MHz = TimeOut
*/
#define DRV_2WS_COMPLETE_TIME_OUT (ByteNum, FreqKHz) ( (u32) ByteNum * 9 * 2000 * 120 / ( (u32) FreqKHz /1000) )

/**
 * \brief
 *  Enumerate to indicate the operation's error
 */
enum
{	
	ERROR_DRV_2WS_DEVICE = ERROR_BASE_DRV_2WS,
	ERROR_DRV_2WS_NO_HANDLE,						/*!< No more Handle						*/
	ERROR_DRV_2WS_UNKNOW_DEVICE,
	ERROR_DRV_2WS_TOTAL,
};

/**
 * \brief
 *  Enumerate to indicate the module of 2WS
 */
typedef enum
{
	EN_DRV_2WS_MODULE_0,
	EN_DRV_2WS_MODULE_1,
	EN_DRV_2WS_MODULE_2,
	EN_DRV_2WS_MODULE_TOTAL
}EN_DRV_2WS_MODULE_NO;

/**
 * \brief
 *  Enumerate to indicate the path of 2WS
 */
typedef enum
{
	EN_DRV_2WS_PATH_0 = 0,
	EN_DRV_2WS_PATH_1,
	EN_DRV_2WS_TOTAL
}EN_DRV_2WS_PATH;

/**
 * \brief
 *  Enumerate to indicate the type of 2WS
 */
typedef enum
{ 
    EN_DRV_2WS_CTRL_HW_TYPE,
    EN_DRV_2WS_CTRL_SW_TYPE,
    EN_DRV_2WS_CTRL_TOTAL
} EN_DRV_2WS_CTRL_TYPE;

/**
 * \brief
 *  Enumerate to 2WS read speed 
 */
typedef enum
{
	EN_DRV_2WS_SPEED_20K, 							/*!< 2WS speed : 20K					*/
	EN_DRV_2WS_SPEED_40K,							/*!< 2WS speed : 40K					*/
	EN_DRV_2WS_SPEED_80K,							/*!< 2WS speed : 80K					*/
	EN_DRV_2WS_SPEED_120K,							/*!< 2WS speed : 120K					*/
	EN_DRV_2WS_SPEED_160K,							/*!< 2WS speed : 160K					*/
	EN_DRV_2WS_SPEED_200K,							/*!< 2WS speed : 200K					*/
	EN_DRV_2WS_SPEED_240K,							/*!< 2WS speed : 240K					*/
	EN_DRV_2WS_SPEED_280K,							/*!< 2WS speed : 280K					*/
	EN_DRV_2WS_SPEED_320K,							/*!< 2WS speed : 320K					*/
	EN_DRV_2WS_SPEED_360K,							/*!< 2WS speed : 360K					*/
	EN_DRV_2WS_SPEED_400K,							/*!< 2WS speed : 400K					*/
	EN_DRV_2WS_SPEED_2000K,							/*!< 2WS speed : 2M						*/
	EN_DRV_2WS_SPEED_2400K,							/*!< 2WS speed : 2.4M					*/
	EN_DRV_2WS_SPEED_TOTAL
} EN_DRV_2WS_SPEED;

/**
 * \brief
 *  Enumerate to SW 2WS read speed
 */
typedef enum
{
	EN_DRV_2WS_SW_FREQ_100K = 2, //120,
	EN_DRV_2WS_SW_FREQ_200K = 2,
	EN_DRV_2WS_SW_FREQ_300K = 2,
	EN_DRV_2WS_SW_FREQ_360K = 2,
	EN_DRV_2WS_SW_FREQ_TOTAL
}EN_DRV_2WS_SW_FREQ_MODE;

/**
 * \brief
 *  Enumerate to 2WS power control
 */
typedef enum
{
	EN_DRV_2WS_POWER_ON,							/*!< 2WS power control mode , normal use mode		*/
	EN_DRV_2WS_STANDBY,								/*!< 2WS power control mode , low frequency mode	*/
	EN_DRV_2WS_PWRCTRL_TOTAL
}EN_DRV_2WS_PWRCTRL;

/**
 * \brief
 *  2WS module has address with 7-bits or 10-bits 
 */
typedef enum
{
	EN_DRV_2WS_ADDRESS_7BIT_MODE,					/*!< 2WS 7 bits addressing mode			*/
	EN_DRV_2WS_ADDRESS_10BIT_MODE,					/*!< 2WS 10 bits addressing mode		*/
	EN_DRV_2WS_ADDRESS_MODE_TOTAL
}EN_DRV_2WS_ADDRESS_MODE;

/**
 * \brief
 *  2WS callback event type
 */
typedef enum
{
	EN_DRV_2WS_EVENT_RX,
	EN_DRV_2WS_EVENT_TX,
	EN_DRV_2WS_EVENT_INTR,
	EN_DRV_2WS_EVENT_CHANGE_CONFIG,
	EN_DRV_2WS_EVENT_POWER_DOWN,
	EN_DRV_2WS_EVENT_CLOSE,
	EN_DRV_2WS_EVENT_TERM,
	EN_DRV_2WS_EVENT_TOTAL
}EN_DRV_2WS_EVENT_TYPE;

typedef enum
{
	EN_DRV_2WS_SDA=0,
	EN_DRV_2WS_SCL,
	EN_DRV_2WS_SW_PIN_NUM,
}EN_DRV_2WS_SW_PIN;

/*-----------------------------------------------------------------------------*/
/* Types Declarations                                                          */
/*-----------------------------------------------------------------------------*/
/**
 * \brief
 *  the 2WS callback function
 * \param	u32Handle		(Output) An open handle, as returned by the Open function
 * \param	enEventType		(Output) Callback function event type
 * \param	enStatus		(Output) Operation status
 * \param	pu32para		(Output) It is data information. It's context will depend on enEventType.
 * 
 */
typedef void (*DRV_2WS_CALLBACK) (u32 u32Handle, EN_DRV_2WS_EVENT_TYPE enEventType, ErrorCode enStatus, u32* pu32para);

/**
 * \brief
 *  the device initial structure
 */
typedef struct 
{	
	os_mempool_handle		u32MemPoolHandle;		/*!< A memory pool handle for 2WS module	*/
	ST_GPIO_Open			stGPIO_Open[EN_DRV_2WS_SW_PIN_NUM];
	EN_DRV_2WS_MODULE_NO	en2WSNo;
	EN_DRV_2WS_CTRL_TYPE	enHwSw;
	EN_DRV_2WS_SPEED		en2WSSpeed;
	ST_GPIO					stSCLpin;				/*!< The GPIO for 2WS serial clock line		*/
	ST_GPIO					stSDApin;				/*!< The GPIO for 2WS serial data line		*/
}ST_2WS_Init, *PST_2WS_Init;

/**
 * \brief
 *  The 2WS Registers Map structure.
 */
typedef struct tag2WS_REG
{
	vu32 vu32Ctrl;
	vu32 vu32Buff;
	vu32 vu32Status;
	vu32 vu32Mask;
	vu32 vu322WSint;
	vu32 vu32Swctrl;
}ST_2WS_REG, *PST_2WS_REG;

/**
 * \brief
 *  2WS callback event type
 */
typedef struct tag2WS_SW_DEVICE
{
    ST_GPIO		st2WSSwSCL;
    ST_GPIO		st2WSSwSDA;
}ST_2WS_SW_DEVICE, *PST_2WS_SW_DEVICE;

/**
 * \brief
 *  Structure of 2WS open
 */
typedef struct 
{
	//u8					u8DevID;
	DRV_2WS_CALLBACK	fn2WSCallback;				/*!< Interrupt 2WS callback function	*/
}ST_2WS_Open, *PST_2WS_Open;

/**
 * \brief
 *  Structure of 2WS configure
 */
typedef struct 
{
	u8							u8DevID;
	EN_DRV_2WS_SPEED			en2WSSpeed;			/*!< Define the speed mode of 2WS		*/
	EN_DRV_2WS_ADDRESS_MODE		en2WSAddressMode;	/*!< Define the address mode of 2WS		*/
}ST_2WS_Config, *PST_2WS_Config;

/*-----------------------------------------------------------------------------*/
/* Extern Global Variables                                                     */
/*-----------------------------------------------------------------------------*/
// DON'T export global variable here. Please use function to access them

/*-----------------------------------------------------------------------------*/
/* Interface Function Prototype                                                */
/*-----------------------------------------------------------------------------*/
ErrorCode DRV_2WS_GetVersion (u8 *pu8VersionNum);
/*!\fn ErrorCode DRV_2WS_GetVersion (u8 *pu8VersionNum)
 * \brief 
 *        Get the 2WS's Version number string
 * 
 * \param pu8VersionNum					(Output) Number string
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_2WS_Initialize (DRV_DeviceNameType DeviceName, PST_2WS_Init pstInit);
/*!\fn ErrorCode DRV_2WS_Initialize (DRV_DeviceNameType DeviceName, PST_2WS_Init pstInit)
 * \brief 
 *        Initial the 2WS device with PST_2WS_Init setting 
 * 
 * \param DeviceName					(Input) 2WS device init name
 * \param pstInit						(Input) 2WS device init parameter
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error 
 * \retval ERROR_INITIALISED			This 2WS has initialled
 * \retval ERROR_NO_FREE_HANDLE			No free handle
 * \retval ERROR_NO_MEMORY				No memory
 * 
 */

ErrorCode DRV_2WS_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_2WS_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief 
 *        Terminate the use of the 2WS device
 * 
 * \param DeviceName					(Input) 2WS device name to terminal
 * \param b8Force						(Input) Force terminate the device or not
 * \code
	True, Terminal the 2WS right now
	False, wait until all open handle close then terminate 2WS
   \endcode
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval EN_DRV_2WS_ERR_UNKNOW_DEVICE	Unknow device
 * \retval EN_DRV_2WS_ERR_DEVICE		No such device
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_2WS_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_2WS_PWRCTRL enPwrCtrl, bool b8Force);
/*!\fn ErrorCode DRV_2WS_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_2WS_PWRCTRL enPwrCtrl, bool b8Force)
 * \brief 
 *        Control the 2WS device power mode
 * 
 * \param DeviceName					(Input) 2WS device name to control
 * \param enPwrCtrl						(Input) The setting of the Flash device power mode
 * \code
	EN_DRV_2WS_POWER_ON, 2WS device powers up
	EN_DRV_2WS_STANDBY, 2WS device goes standby mode (low frequncy)
   \endcode
 * \param b8Force						(Input) Force power down the device or not
 * \code
	True, Power control the 2WS right now
	False, wait until all open close then power control 2WS 
   \endcode
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval EN_DRV_2WS_ERR_UNKNOW_DEVICE	Unknow device
 * \retval EN_DRV_2WS_ERR_DEVICE		No such device
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * 
 */

ErrorCode DRV_2WS_Open (DRV_DeviceNameType DeviceName, PST_2WS_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_2WS_Open (DRV_DeviceNameType DeviceName, PST_2WS_Open pstOpen, u32 *pu32Handle)
 * \brief 
 *        Open the 2WS device and associate it with a handle
 * 
 * \param DeviceName					(Input) 2WS device name to open
 * \param pstOpen						(Input) 2WS config parameter
 * \param pu32Handle					(Output) The returned handle of the opened device driver
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval EN_DRV_2WS_ERR_UNKNOW_DEVICE	Unknow device
 * \retval EN_DRV_2WS_ERR_DEVICE		No such device
 * \retval EN_DRV_2WS_ERR_NO_HANDLE		No more Handle
 * \retval ERROR_INVALID_HANDLE			Invalid Handle
 * 
 */

ErrorCode DRV_2WS_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_2WS_Close (u32* pu32Handle)
 * \brief 
 *        Close 2WS device associated with a handle
 * 
 * \param pu32Handle					(Input) Pointer to the opening handle number of the 2WS device
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * 
 */

ErrorCode DRV_2WS_GetConfig (u32 u32Handle, PST_2WS_Config pstPara);
/*!\fn ErrorCode DRV_2WS_GetConfig (u32 u32Handle, PST_2WS_Config pstPara)
 * \brief 
 *        Get the 2WS device's config data
 * 
 * \param u32Handle						(Input) An open handle, as returned by the Open function
 * \param pstPara						(Output) 2WS device config parameter
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * 
 */

ErrorCode DRV_2WS_SetConfig (u32 u32Handle, PST_2WS_Config pstPara);
/*!\fn ErrorCode DRV_2WS_SetConfig (u32 u32Handle, PST_2WS_Config pstPara)
 * \brief 
 *        Set the 2WS device's config data
 * 
 * \param u32Handle						(Input) An open handle, as returned by the Open function
 * \param pstPara						(Input) 2WS device config parameter
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * 
 */

ErrorCode DRV_2WS_Write (u32 u32Handle, u8 u8DevID, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrited, u32 u32TimeOut);
/*!\fn ErrorCode DRV_2WS_Write (u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrited, u32 u32TimeOut)
 * \brief 
 *        Transmit the data in pu8buffer with u32Size to the u32Handle 2WS bus
 * 
 * \param u32Handle						(Input)  An open handle, as returned by the Open function
 * \param pu8Buffer						(Input)  Pointer to the memory buffer
 * \param u32Size						(Input)  The size of the write buffer
 * \param pu32NumOfWrited				(Output) Pointer to the result value of the actual number to write
 * \param u32TimeOut					(Input)  Timeout in MS for write 
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * \retval ERROR_TIMEOUT				Wait 2WS device info time out
 * 
 */

ErrorCode DRV_2WS_WriteNoStop (u32 u32Handle, u8 u8DevID,u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrited, u32 u32TimeOut);
/*!\fn ErrorCode DRV_2WS_WriteNoStop (u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfWrited, u32 u32TimeOut)
 * \brief 
 *        Transmit the data in pu8Buffer with u32Size to the u32Handle 2WS bus with no Stop condition
 * 
 * \param u32Handle						(Input)  An open handle, as returned by the Open function
 * \param pu8Buffer						(Input)  Pointer to the memory buffer
 * \param u32Size						(Input)  The size of the write buffer
 * \param pu32NumOfWrited				(Output) Pointer to the result value of the actual number to write
 * \param u32TimeOut					(Input)  Timeout in MS for write 
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * \retval ERROR_TIMEOUT				Wait 2WS device info time out
 * 
 */

ErrorCode DRV_2WS_Read (u32 u32Handle, u8 u8DevID,u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfRead, u32 u32TimeOut);
/*!\fn ErrorCode DRV_2WS_Read (u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfRead, u32 u32TimeOut)
 * \brief 
 *        Receive the data in the result to pu8Buffer with u32Size from the u32Handle 2WS bus
 * 
 * \param u32Handle						(Input)  An open handle, as returned by the Open function
 * \param pu8Buffer						(Output) Pointer to the memory buffer
 * \param u32Size						(Input)  The size of the read buffer
 * \param pu32NumOfRead					(Output) Pointer to the result value of the actual number to read
 * \param u32TimeOut					(Input)  Timeout in MS for read
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error 
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * \retval ERROR_TIMEOUT				Wait 2WS device info time out
 * 
 */

ErrorCode DRV_2WS_ReadNoAck (u32 u32Handle, u8 u8DevID,u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfRead, u32 u32TimeOut);
/*!\fn ErrorCode DRV_2WS_ReadNoAck (u32 u32Handle, u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfRead, u32 u32TimeOut)
 * \brief 
 *        Receive the data in the result to pu8Buffer with u32Size from the u32Handle 2WS bus with no Ack Condition
 * 
 * \param u32Handle						(Input)  An open handle, as returned by the Open function
 * \param pu8Buffer						(Input)  Pointer to the memory buffer
 * \param u32Size						(Input)  The size of the read buffer
 * \param pu32NumOfRead					(Output) Pointer to the result value of the actual number to read
 * \param u32TimeOut					(Input)  Timeout in MS for read
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_BAD_PARAMETER			Parameter error 
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * \retval ERROR_TIMEOUT				Wait 2WS device info time out
 * 
 */

ErrorCode DRV_2WS_ScanDevice (u32 u32Handle, u8 u8DevID,u32 u32TimeOut);
/*!\fn ErrorCode DRV_2WS_ScanDevice (u32 u32Handle, u32 u32TimeOut)
 * \brief 
 *        Scan the device connect to the u32Handle bus
 * 
 * \param u32Handle						(Input) An open handle, as returned by the Open function
 * \param u32TimeOut					(Input) Timeout in MS for scan
 * 
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 * \retval ERROR_TIMEOUT				Timeout in MS to scan
 * 
 */

ErrorCode DRV_2WS_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_2WS_Lock (u32 u32Handle, bool b8Lock)
 * \brief 
 *		Set the 2WS device to lock mode.\n
 *		No other handle can use the 2WS device unless unlock
 *
 * \param u32Handle						(Input) An open handle, as returned by the Open function
 * \param b8Lock						(Input) Lock the 2WS device or not
   \code
	True, Lock the 2WS
	False, Unlock the 2WS 
   \endcode	
 *
 * \return 2WS Operation Error Code
 * \retval ERROR_NO_ERROR				Operation Success
 * \retval ERROR_INVALID_HANDLE			Handle value is not accepted
 *
 */

ErrorCode DRV_2WS_Read_CVT (u32 u32Handle, u8 u8DevID,u8 *pu8Buffer, u32 u32Size, u32 *pu32NumOfRead, u32 u32TimeOut);

#endif //#ifndef __DRV_2WS_H__
