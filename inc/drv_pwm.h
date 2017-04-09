//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide PWM Control 
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


#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include "os.h"
#include "def_type.h"
#include "def_err.h"
#include "drv_gpio.h"
//#include "drv_config.h"

#define BITS_PWM_INT_MASK				0x0000003F	//bit-0~5
#define BIT_PWM_EA_CC3_RST				0x00400000	//bit-22
#define BIT_PWM_EA_CC3_STP				0x00200000	//bit-21
#define BIT_PWM_EA_CC3_INT				0x00100000	//bit-20
#define BIT_PWM_EA_CC2_RST				0x00040000	//bit-18
#define BIT_PWM_EA_CC2_STP				0x00020000	//bit-17
#define BIT_PWM_EA_CC2_INT				0x00010000	//bit-16
#define BIT_PWM_EA_CC1_RST				0x00004000	//bit-14
#define BIT_PWM_EA_CC1_STP				0x00002000	//bit-13
#define BIT_PWM_EA_CC1_INT				0x00001000	//bit-12		
#define BIT_PWM_EA_CC0_RST				0x00000400	//bit-10	//edge reset event action for PWM-n.(counter cleared) --> CC0
#define BIT_PWM_EA_CC0_STP				0x00000200	//bit-9		//edge stop event action for PWM-n.(counter stopped)
#define BIT_PWM_EA_CC0_INT				0x00000100	//bit-8	

/*!
 * \brief
 * enumerate to indicate the error of operation
 */
enum
{
	ERROR_PWM_ERR = ERROR_BASE_DRV_PWM,	/*!< Other error */
	ERROR_PWM_ERR_UNKNOW_DEVICE,			/*!< unknow device */
	ERROR_PWM_ERR_UNKNOW
};


/*!
 * \brief
 * enumerate to indicate the output level of PWM
 */
typedef enum
{
	EN_DRV_PWM_CMP_OUT_LEVEL_LOW,		/*!< output level always low */
	EN_DRV_PWM_CMP_OUT_LEVEL_HEIGHT,	/*!< output level always high */
	EN_DRV_PWM_CMP_OUT_LEVEL_LOW_REG02,	/*!< output level low, when counter values match with u16CmpVal_0 or u16CmpVal_2; High, when counter values match with u16CmpVal_1 or u16CmpVal_3 */
	EN_DRV_PWM_CMP_OUT_LEVEL_LOW_REG13,	/*!< output level low, when counter values match with u16CmpVal_1 or u16CmpVal_3; High, when counter values match with u16CmpVal_0 or u16CmpVal_2 */
	EN_DRV_PWM_CMP_OUT_LEVEL_NUM
}EN_DRV_PWM_CMP_OUT_LEVEL;


/*!
 * \brief
 * enumerate to indicate the trigger mode of PWM
 */
typedef enum
{
	EN_DRV_PWM_TRIGGER_DISABLE,	/*!< Trigger disabled */
	EN_DRV_PWM_TRIGGER_FALING,	/*!< Trigger falling edge */
	EN_DRV_PWM_TRIGGER_RISING,	/*!< Trigger rising edge */
	EN_DRV_PWM_TRIGGER_BOTH,	/*!< Trigger both edge */
	EN_DRV_PWM_TRIGGER_NUM
}EN_DRV_PWM_TRIGGER_MODE;


/*!
 * \brief
 * enumerate to indicate the operation mode of PWM
 */
typedef enum
{
	EN_DRV_PWM_COMPARE_MODE,	/*!< Compare mode */
	EN_DRV_PWM_CAPTRUE_MODE,	/*!< Capture mode */
	EN_DRV_PWM_MODE_NUM
}EN_DRV_PWM_MODE;

typedef enum
{
    EN_DRV_PWM_ENABLE,      /*!< Compare mode */
    EN_DRV_PWM_DISABLE,     /*!< Capture mode */
    EN_DRV_PWM_ONOFF_NUM
}EN_DRV_PWM_ON_OFF;

typedef enum
{
    EN_DRV_PWM_APB_CLOCK,   /*!< APB clock mode */
    EN_DRV_PWM_OSC_CLOCK,   /*!< 27MHz mode */
    EN_DRV_PWM_CLOCK_NUM
}EN_DRV_PWM_CLOCK_SEL;

/*!
 * \brief
 * enumerate to indicate the event type of PWM
 */
typedef enum
{
	EN_DRV_PWM_EVENT_CHANGE_CONFIG,	/*!< Config changed event */
	EN_DRV_PWM_EVENT_POWER_DOWN,	/*!< Power down event */
	EN_DRV_PWM_EVENT_TERM,			/*!< Terminate event */
	EN_DRV_PWM_EVENT_NUM
}EN_DRV_PWM_EVENT_TYPE;





/*!
 * \brief
 * enumerate to PWM power control
 */
typedef enum
{
	EN_DRV_PWM_POWER_ON,			/*!< Power on */
	EN_DRV_PWM_STANDBY,				/*!< Standby */
	EN_DRV_PWM_PWRCTRL_NUM
}EN_DRV_PWM_PWRCTRL;


typedef enum
{
	EN_DRV_PWM_0,					/*!< Indicate PWM module number 0 */
	EN_DRV_PWM_1,					/*!< Indicate PWM module number 1 */
	EN_DRV_PWM_2,					/*!< Indicate PWM module number 1 */
	EN_DRV_PWM_NUM
}EN_DRV_PWM_NO;
//#endif




typedef struct 
{
    u8                          u8CntClkDiv;            /*!< Counter clock divisor for PWM_n */
    u16                         u16SetCnt;              /*!< Counter value for PWM_n. The counter will start from this value */
    u8                          u8PulseWidth;           /*!< The values to be compared by PWM_n in compare mode */
}ST_PWM_Compare_Params, *PST_PWM_Compare_Params;



/*!
 * \brief
 * Definition of a Callback function to let the caller know when operation has completed in capture mode
 * \param	u32Handle			(Output) An open handle, as returned by the Open function
 * \param	enEventType			(Output) Callback function event type
 * \param	enStatus			(Output) PWM Operation status
 * \param	pstPara			(Output) A pointer to the data information. It's context will depend on enEventType.
 */
typedef void (* DRV_PWM_CALLBACK ) (u32 u32Handle, EN_DRV_PWM_EVENT_TYPE enEventType, ErrorCode enStatus, void *pstPara);


/*!
 * \brief
 * the configuration structure includes the PWM software setting parameters
 */

typedef struct 
{
    u32                     u32PWM_Counter_Value ;
    EN_DRV_PWM_CLOCK_SEL    enPWM_Source_Sel  ;
    u8                      u8PWM_Free_run    ;
    EN_DRV_PWM_WORKING_MODE enPWM_Mode_Sel    ;
    u8                      u8PWM_Clock_Div   ;
    u8                      u8PWM_Pulse_width ;
    u16                     u16PWM_Pre_scale  ;
}ST_PWM_Config, *PST_PWM_Config;    
//#endif


/*!
 * \brief
 * the open structure includes the PWM opening parameters
 */
typedef union 
{
	DRV_PWM_CALLBACK	pPWMCallbackFun;	/*!< A pointer to the user defined function that will be called when a callback event has occurred */
}ST_PWM_Open, *PST_PWM_Open;


/*!
 * \brief
 * the initial structure includes the device hardware setting
 */
typedef struct 
{
	os_mempool_handle	u32MemPoolHandle;				/*!< A memory pool handle for PWM module	*/
	EN_DRV_PWM_NO enPwmNo;								/*!< PWM device number						*/
}ST_PWM_Init, *PST_PWM_Init;



ErrorCode DRV_PWM_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_PWM_PWRCTRL enPwrCtrl, bool b8Force);
/*!\fn ErrorCode DRV_PWM_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_PWM_PWRCTRL enPwrCtrl, bool b8Force)
 * 
 * \brief
 * 		Control the PWM device power mode
 *  
 * \param	DeviceName		(Input) PWM device name to control
 * \param	enPwrCtrl		(Input) Setting the PWM device power mode
 * \param	b8Force			(Input) Force terminate the PWM or not
 \code
	True:	Terminate the PWM right now
	False:	wait until all handles close then terminate PWM
 \endcode
 * 
 \code
	enPwrCtrl				description
	-------------------		--------------------------
	EN_DRV_PWM_POWER_ON		PWM device in power on mode
	EN_DRV_PWM_STANDBY		PWM device in standby mode
 \endcode
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR			Operation Success
 * \retval	ERROR_BAD_PARAMETER	One or more of the parameters was invalid
 * \retval	EN_DRV_PWM_ERR_DEVICE		No such device
 */


ErrorCode DRV_PWM_Initialize (DRV_DeviceNameType DeviceName, PST_PWM_Init pstInit);
/*!\fn ErrorCode DRV_PWM_Initialize (DRV_DeviceNameType DeviceName, PST_PWM_Init pstInit)
 * 
 * \brief
 * 		Initialize the PWM device with pstInit setting
 * 
 * \param	DeviceName		(Input) PWM device name to initialize
 * \param	pstInit			(Input) Pointer to the initialization parameter structure
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER			One or more of the parameters was invalid
 * \retval	ERROR_INITIALISED	A previous Init call has not been terminated
 */


ErrorCode DRV_PWM_Open (DRV_DeviceNameType DeviceName, PST_PWM_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_PWM_Open (DRV_DeviceNameType DeviceName, PST_PWM_Open pstOpen, u32 *pu32Handle)
 * 
 * \brief
 * 		Open the PWM device and associate it with a handle
 * 
 * \param	DeviceName		(Input) PWM device name to open
 * \param	pstOpen			(Input) Pointer to the opening parameter structure
 * \param	pu32Handle		(Output) The returned handle of the opened device driver
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR			Operation Success
 * \retval	ERROR_BAD_PARAMETER	One or more of the parameters was invalid
 * \retval	EN_DRV_PWM_ERR_DEVICE		No such device
 */


ErrorCode DRV_PWM_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_PWM_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * 
 * \brief
 * 		Terminate a PWM device based on the parameters.
 * 
 * \param	DeviceName		(Input) PWM device name to terminate
 * \param	b8Force			(Input) Force terminate the PWM or not
 \code
	True:	Terminate the PWM right now
	False:	wait until all open handles close then terminate PWM
 \endcode
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR			Operation Success
 * \retval	ERROR_BAD_PARAMETER	One or more of the parameters was invalid
 * \retval	EN_DRV_PWM_ERR_DEVICE		No such device
 * \retval	ERROR_INITIALISED			The driver is not initialized
 */


ErrorCode DRV_PWM_GetConfig (u32 u32Handle, EN_DRV_PWM_MODE *penMode, PST_PWM_Config pstPara);
/*!\fn ErrorCode DRV_PWM_GetConfig (u32 u32Handle, EN_DRV_PWM_MODE *penMode, PST_PWM_Config pstPara)
 * 
 * \brief
 * 		Get the parameter of the PWM configuration in use
 * 
 * \param	u32Handle		(Input) An open handle, as returned by the Open function
 * \param	penMode			(Output) Return the PWM mode in use
 * \param	pstPara			(Output) PWM device config parameter
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR			Operation Success
 * \retval	ERROR_BAD_PARAMETER	One or more of the parameters was invalid
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 */

ErrorCode DRV_PWM_SetConfig (u32 u32Handle, EN_DRV_PWM_ON_OFF enOnOff, PST_PWM_Config pstPara) ;
//endif
/*!\fn ErrorCode DRV_PWM_SetConfig (u32 u32Handle, EN_DRV_PWM_MODE enMode, PST_PWM_Config pstPara)
 * 
 * \brief
 * 		Sets the parameter of the PWM configuration in use
 * 
 * \param	u32Handle		(Input) An open handle, as returned by the Open function
 * \param	enMode			(Input) Sets the PWM capture or compare mode in use
 * \param	pstPara			(Input) PWM device config parameter
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR			Operation Success
 * \retval	ERROR_BAD_PARAMETER	One or more of the parameters was invalid
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 */


ErrorCode DRV_PWM_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_PWM_Close (u32* pu32Handle)
 * 
 * \brief
 * 		Close the PWM device associated with a handle
 * 
 * \param	pu32Handle			(Input) Pointer to the opening handle number of the PWM device
 * 
 * \return	PWM Operation Error Code
 * \retval	ERROR_NO_ERROR			Operation Success
 * \retval	ERROR_INVALID_HANDLE		Handle invalid or not open
 */


u8* DRV_PWM_GetVersion (void);
/*!\fn u8* DRV_PWM_GetVersion (void)
 *
 * \brief
 *		Get the version info of PWM driver.
 *
 * \return	Return the version info of device driver
 */

#endif //#ifndef __DRV_PWM_H__
