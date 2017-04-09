//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide SAR-ADC Control 
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

#ifndef __ADC_H__
#define __ADC_H__

/***************************************************************************
 * Include files
 * ************************************************************************/

#include "def_type.h"
#include "def_err.h"

/***************************************************************************
 * Definition
 * ************************************************************************/

/***************************************************************************
 * Enumeration
 * ************************************************************************/

/*!
 * \brief
 * Enumerate to indicate the operation's error
 */
enum
{
	ERROR_ADC_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_ADC,		/*!< Some handle not close			*/
	ERROR_ADC_ACCESS,										/*!< Handle is lock without access	*/	
	ERROR_ADC_POWER_DOWN,									/*!< ADC in power down mode			*/
	ERROR_ADC_UNKNOW_DEVICE,								/*!< Unknow Device					*/		
};

/*!
 * \brief
 * Defines the ADC port.
 */

typedef enum
{
    EN_DRV_ADC_PORT_0  = 0,									/*!< SAR_ADC port0			*/
    EN_DRV_ADC_PORT_1,										/*!< SAR_ADC port1			*/
    EN_DRV_ADC_PORT_2,										/*!< SAR_ADC port2			*/
    EN_DRV_ADC_PORT_3,										/*!< SAR_ADC port3			*/
	EN_DRV_ADC_PORT_NUM,
    EN_DRV_ADC_PORT_ERROR,
}EN_DRV_ADC_PORT;

/*!
 * \brief
 *  Enumerate to power control of SAR-ADC
 */
typedef enum
{
	EN_DRV_ADC_POWER_ON,									/*!< Switch on the power of SAR-ADC Module		*/	
	EN_DRV_ADC_POWER_OFF,									/*!< Switch off the power of SAR-ADC Module		*/	
	EN_DRV_ADC_PWRCTRL_NUM
}EN_DRV_ADC_PWRCTRL;

/***************************************************************************
 * Structure
 * ************************************************************************/
/*!
 * \brief
 *  The ADC open structure
 */
typedef struct
{
	EN_DRV_ADC_PORT	enADCNo;								/*!< SAR_ADC port	*/
}ST_DRV_ADC_OpenParams, *PST_DRV_ADC_OpenParams;

/*!
 * \brief
 *  The ADC initial structure
 */
typedef struct
{

}ST_DRV_ADC_InitParams, *PST_DRV_ADC_InitParams;


/***************************************************************************
 * API
 * ************************************************************************/
/*****************
//Common Functions
*****************/
ErrorCode DRV_ADC_GetVersion (u8* pu8VersionNum);
/*!\fn ErrorCode DRV_ADC_GetVersion (u8* pu8VersionNum)
 * \brief
 *        Get the SAR-ADC Version number string.
 *
 * \param 	pu8VersionNum    				(Output) Version Number string
 *
 * \return	SAR-ADC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_ADC_Initialize (DRV_DeviceNameType DeviceName, ST_DRV_ADC_InitParams* pstInitParams);
/*!\fn ErrorCode DRV_ADC_Initialize (DRV_DeviceNameType DeviceName, ST_DRV_ADC_InitParams* pstInitParams)
 * \brief
 *        Initialize the ADC device with pstInitParams setting.
 * 
 * \param	DeviceName						(Input) Name of the ADC device to initialize
 * \param	pstInitParams					(Input) Pointer to the initialization parameter structure
 *
 * \return	SAR-ADC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval	ERROR_INITIALISED				A previous Init call has not been terminated
 */

ErrorCode DRV_ADC_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_ADC_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief
 *        Terminate the ADC device driver.
 * 
 * \param	DeviceName						(Input) Name of an initialized audio device
 * \param	b8Force							(Input) Force terminate the SAR-ADC or not
 *
 * \return	SAR-ADC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval	ERROR_INITIALISED				A previous Init call has not been terminated 
 * \retval	ERROR_ADC_HANDLE_NOT_CLOSED		Some handle not close
 * \retval	ERROR_ADC_UNKNOW_DEVICE			Unknow Device
 */

ErrorCode DRV_ADC_Open (DRV_DeviceNameType DeviceName, ST_DRV_ADC_OpenParams* pstOpenParams, u32* pu32Handle);
/*!\fn ErrorCode DRV_ADC_Open (DRV_DeviceNameType DeviceName, ST_DRV_ADC_OpenParams* pstOpenParams, u32* pu32Handle)
 * \brief
 *        Open the ADC device and associate it with a handle.
 * 
 * \param	DeviceName						(Input) ADC device name to open
 * \param	pstOpenParams					(Input) Pointer to the opening parameter structure
 * \param	pu32Handle						(Output) The returned handle of the opened device driver
 *  
 * \return	SAR-ADC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval	ERROR_NO_FREE_HANDLE			No free handle for the device
 * \retval	ERROR_ADC_UNKNOW_DEVICE			Unknow Device
 */

ErrorCode DRV_ADC_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_ADC_Close (u32* pu32Handle)
 * \brief
 *        Close an opend device associated with a handle.
 * 
 * \param	pu32Handle						(Input) An open handle number of the audio device
 *  
 * \return	SAR-ADC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid
 * \retval	ERROR_ADC_ACCESS				Handle is lock without access
 */

ErrorCode DRV_ADC_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_ADC_PWRCTRL enPwrCtrl, bool b8Force);
/*!\fn ErrorCode DRV_ADC_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_ADC_PWRCTRL enPwrCtrl, bool b8Force)
 * \brief
 *        Control the CI device power mode.
 * 
 * \param	DeviceName						(Input) CI device name to control
 * \param	enPwrCtrl						(Input) Setting the CI device power mode
 * \code
 *	enPwrCtrl					description
 *	---------------------------------------------------------------------
 *	EN_DRV_ADC_POWER_ON			Switch on the power for the SAR-ADC Module
 *	EN_DRV_ADC_POWER_OFF		Switch off the power for the SAR-ADC Module
 * \endcode
 * \param b8Force			(Input) Force power down the device or not
 * \code
 * 	TRUE, Power control the ADC right now
 * 	FALSE, Wait until all open close then power control ADC 
 * \endcode
 *    
 * \return	SAR-ADC Operation Error Code
 * \retval	ERROR_NOT_SUPPORTED					The function is not supported.
 * \retval	ERROR_ADC_UNKNOW_DEVICE				Unknow Device
 */

ErrorCode DRV_ADC_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_ADC_Lock (u32 u32Handle, bool b8Lock)
 * \brief
 *		Set the ADC device to protection mode.
 *		No other handle can read the ADC device unless unlock.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 * \param b8Lock							(Input) Lock the CI device or not
 * \code
 * 	TRUE, Lock the ADC
 * 	FALSE, Unlock the ADC
 * \endcode
 *  
 * \return SAR-ADC Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_ADC_ACCESS					Handle is lock without access 
 */

/*****************
//ADC Function
*****************/
ErrorCode DRV_ADC_GetValue ( u32 u32Handle, u32* pu32Value);
/*!\fn ErrorCode DRV_ADC_GetValue ( u32 u32Handle, u32* pu32Value)
 * \brief
 *        Get the ADC value by handle.
 *
 * \param	u32Handle						(Input) An open handle number of the audio device
 * \param 	pu32Value						(Output) Return ADC result
 *
 * \return	SAR-ADC Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval	ERROR_ADC_POWER_DOWN			ADC in power down mode
 * \retval	ERROR_ADC_ACCESS				Handle is lock without access
 */

#endif // end of __ADC_H__

