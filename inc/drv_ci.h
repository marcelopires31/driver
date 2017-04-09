//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide CI Control 
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

#ifndef __CI_H__
#define __CI_H__
#include "drv_config.h"
/***************************************************************************
 * Include files
 * ************************************************************************/

#include "os.h"

#include "def_type.h"
#include "def_err.h"

#include "drv_gpio.h"

/***************************************************************************
 * Definition
 * ************************************************************************/


/***************************************************************************
 * Enumeration
 * ************************************************************************/
/*!
 * \brief
 *  Enumerate to indicate the CI port number.
 */
typedef enum
{
	EN_DRV_CI_0,
	EN_DRV_CI_1,
	EN_DRV_CI_NUM
}EN_DRV_CI_NO;


/*!
 * \brief
 *  Enumerate to indicate the CI I/O address.
 */
typedef enum
{
	EN_CI_REGISTER_DATA = 0,
	EN_CI_REGISTER_COMMAND = 1,
	EN_CI_REGISTER_STATUS = 1,
	EN_CI_REGISTER_LSB = 2,
	EN_CI_REGISTER_MSB = 3,
	EN_CI_REGISTER_MAX,	
} EN_DRV_IO_ADDR;


/*!
 * \brief
 *  Specifies the Transport stream flow through the DVBCI module.
 */
typedef enum
{
	EN_DRV_CI_TS_PASSTHROUGH,								/*!< Enable the Transport Stream Flow through DVBCI Module	*/
	EN_DRV_CI_TS_BYPASS,									/*!< Disable the Transport Stream Flow through DVBCI Module	*/	
} EN_DRV_CI_TSBYPASS_MODE;

/*!
 * \brief
 *  Specifies the status of Command Interface of the DVBCI Module.
 */
typedef enum
{
	EN_DRV_CI_STS_RE = 0x01,								/*!< CI_STATUS_Read Error	*/
	EN_DRV_CI_STS_WE = 0x02,								/*!< CI_STATUS_Write Error	*/
	EN_DRV_CI_STS_FR = 0x40,								/*!< CI_STATUS_Free			*/
	EN_DRV_CI_STS_DA = 0x80,								/*!< CI_STATUS_Data Available*/
}EN_DRV_CI_STATUS;

/*!
 * \brief
 *  Specifies the command bits of Command Interface of the DVBCI Module.
 */
typedef enum
{
	EN_DRV_CI_CMD_HC = 0x01,								/*!< CI_HOST_CONTROL	*/
	EN_DRV_CI_CMD_SW = 0x02,								/*!< CI_SIZE_WRITE	*/
	EN_DRV_CI_CMD_SR = 0x04,								/*!< CI_SIZE_READ	*/
	EN_DRV_CI_CMD_RS = 0x08,								/*!< CI_RESET		*/
	EN_DRV_CI_CMD_HCSW = 0x03,								/*!< CI_HOST_CONTROL & SIZE_WRITE	*/	
}EN_DRV_CI_COMMAND;

/*!
 * \brief
 *  Enumerate to power control of CI.
 */
typedef enum
{
	EN_DRV_CI_POWER_ON_V500,								/*!< Switch on the power 5.0V to the DVBCI Module		*/
	EN_DRV_CI_POWER_ON_V330,								/*!< Switch on the power 3.3V to the DVBCI Module		*/	
	EN_DRV_CI_POWER_OFF,									/*!< Switch off the power to the DVBCI Module			*/
	EN_DRV_CI_PWRCTRL_NUM
}EN_DRV_CI_PWRCTRL;

/*!
 * \brief
 *  Enumerate to ALE mode of CI.
 */
typedef enum
{
	EN_DRV_CI_ALE_NONALEMODE,								/*!< Non ALE mode	*/		
	EN_DRV_CI_ALE_ALEMODE,									/*!< ALE mode		*/
	EN_DRV_CI_ALE_NUM
}EN_DRV_CI_ALE_MODE;

/*!
 * \brief
 *  Enumerate to Endian mode of CI.
 */
typedef enum
{
	EN_DRV_CI_ENDIAN_LITTLE,								/*!< LITTLE endian mode	*/		
	EN_DRV_CI_ENDIAN_BIG,									/*!< BIG endian mode		*/
	EN_DRV_CI_ENDIAN_NUM
}EN_DRV_CI_ENDIAN_MODE;

/*!
 * \brief
 * Enumerate to indicate the operation's error.
 */
enum 
{
	ERROR_CI_HANDLE_NOT_CLOSED = ERROR_BASE_DRV_CI,		/*!< Some handle not close			*/
	ERROR_CI_ACCESS,									/*!< Handle is lock without access	*/
	ERROR_CI_READ,										/*!< CI data read error				*/
	ERROR_CI_WRITE,										/*!< CI data write error			*/
	ERROR_CI_CIS_READ,									/*!< CI CIS read error				*/
	ERROR_CI_SWRESET,									/*!< CI Software reset error		*/
	ERROR_CI_HWRESET,									/*!< CI Hardware reset error		*/			
	ERROR_CI_NO_MODULE,									/*!< No CI CAM in slot				*/
	ERROR_CI_UNKNOW_DEVICE,								/*!< Unknow Device					*/
};

/*!
 * \brief
 *  CI event type.
 */
typedef enum
{
	EN_DRV_CI_EVT_CI0_INSERTED,							/*!< CI0_INSERTED */
	EN_DRV_CI_EVT_CI0_REMOVED,							/*!< CI0_REMOVED */
	EN_DRV_CI_EVT_CI1_INSERTED,							/*!< CI1_INSERTED */
	EN_DRV_CI_EVT_CI1_REMOVED,							/*!< CI1_INSERTED */
	EN_DRV_CI_EVT_TERMINATE_CI0,
	EN_DRV_CI_EVT_TERMINATE_CI1,
	EN_DRV_CI_EVT_CHANGE_CONFIG_CI0,
	EN_DRV_CI_EVT_CHANGE_CONFIG_CI1,
	EN_DRV_CI_EVT_CI0_IRQ,								/*!< CI0 IRQ */
	EN_DRV_CI_EVT_CI1_IRQ,								/*!< CI1 IRQ */
	EN_DRV_CI_EVT_NUM
}EN_DRV_CI_EVENT_TYPE;


/*!
 * \brief
 *  Enumerate to indicate the initial type (single or dual CI).
 */
typedef enum
{
	EN_DRV_CI_INITIAL_TYPE_SINGLE_CI0,
	EN_DRV_CI_INITIAL_TYPE_SINGLE_CI1,
	EN_DRV_CI_INITIAL_TYPE_DUAL,
	EN_DRV_CI_INITIAL_TYPE_NUM
}EN_DRV_CI_INITIAL_TYPE;

/***************************************************************************
 * Structure
 * ************************************************************************/

/*!
 * \brief
 *  CI Access Timing setting.
 */
typedef	struct
{
	u16	u16T_RCS;		/*!< Read command setup time */
	u16	u16T_RDS;		/*!< Read data	setup time */
	u16	u16T_RDH;		/*!< Read data	hold time */
	u16	u16T_RCR;		/*!< Read command recovery	time */

	u16	u16T_WCS;		/*!< Write	command	setup time */
	u16	u16T_WDS;		/*!< Write	data setup time */
	u16	u16T_WDH;		/*!< Write	data hold time */
	u16	u16T_WCR;		/*!< Write	command	recovery time */
}ST_CI_AccessTime, *PST_CI_AccessTime;

/*!
 * \brief
 *  CI initial parameters.
 */
typedef struct
{
	os_mempool_handle		u32MemPoolHandle;					/*!< A memory pool handle for CI module	*/
	EN_DRV_CI_INITIAL_TYPE	enCIInitialType;					/*!< CI initial type (single or dual CI) */
	EN_DRV_CI_ALE_MODE		enALEMode;							/*!< Enumerate to ALE mode of CI */		
	ST_GPIO					astGPIO_HwReset[EN_DRV_CI_NUM];		/*!< Hardware reset GPIO of CI, [0] for CI0, [1] for CI1*/		
	EN_DRV_CI_ENDIAN_MODE	enEndianMode;						/*!< Enumerate to Endian mode of CI	*/
}ST_CI_Init, *PST_CI_Init;
		
/*!
 * \brief
 *	The configuration structure includes the CI software setting parameters.
 */
typedef struct
{
	ST_CI_AccessTime stCIAccessTime;			/*!< CI Access Timing setting */
}ST_CI_Config, *PST_CI_Config;

/*!
 * \brief
 *  Structure of CI open.
 */
typedef struct
{
	EN_DRV_CI_NO	enCINo;				/*!< CI port number */
	u32				u32EVTHandle;		/*!< EVENT Handle */
}ST_CI_Open, *PST_CI_Open;

/***************************************************************************
 * Type definition
 * ************************************************************************/



/***************************************************************************
 * API
 * ************************************************************************/
//function prototype
//**************************************************************************
ErrorCode DRV_CI_GetVersion (u8* pu8VersionNum);
/*!\fn ErrorCode DRV_CI_GetVersion (u8* pu8VersionNum)
 * \brief
 *        Get the CI's Version number string.
 *
 * \param 	pu8VersionNum    				(Output) Version Number string
 * \return	CI Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_CI_Initialize (DRV_DeviceNameType DeviceName, ST_CI_Init* pstInit);
/*!\fn ErrorCode DRV_CI_Initialize (DRV_DeviceNameType DeviceName, ST_CI_Init* pstInit)
 * \brief
 *        Initialize the CI device with pstInit setting.
 * 
 * \param	DeviceName						(Input) CI device name to initialize
 * \param	pstInit							(Input) Pointer to the initialization parameter structure
 *
 * \return	CI Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval	ERROR_INITIALISED				A previous Init call has not been terminated
 * \retval	ERROR_INTERRUPT					Interrupt install error
 */

ErrorCode DRV_CI_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_CI_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief
 *        Terminate the CI device driver.
 * 
 * \param	DeviceName						(Input) CI device name to initialize
 * \param	b8Force							(Input) Force terminate the CI or not
 *
 * \return	CI Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval	ERROR_INITIALISED				A previous Init call has not been terminated 
 * \retval	ERROR_CI_HANDLE_NOT_CLOSED		Some handle not close
 * \retval	ERROR_CI_UNKNOW_DEVICE			Unknow Device
*/

ErrorCode DRV_CI_Open (DRV_DeviceNameType DeviceName, ST_CI_Open* pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_CI_Open (DRV_DeviceNameType DeviceName, ST_CI_Open* pstOpen, u32 *pu32Handle)
 * \brief
 *        Open the CI device and associate it with a handle.
 * 
 * \param	DeviceName						(Input) CI device name to open
 * \param	pstOpen							(Input) Pointer to the opening parameter structure
 * \param	pu32Handle						(Output) The returned handle of the opened device driver
 *  
 * \return	CI Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval	ERROR_NO_FREE_HANDLE			No free handle for the device
 * \retval	ERROR_CI_UNKNOW_DEVICE			Unknow Device 
 */

ErrorCode DRV_CI_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_CI_Close (u32* pu32Handle)
 * \brief
 *        Close CI device associated with a handle.
 * 
 * \param	pu32Handle						(Input) An open handle number of the CI device
 *  
 * \return	CI Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid
 */

ErrorCode DRV_CI_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_CI_PWRCTRL enPwrCtrl, bool b8Force);
/*!\fn ErrorCode DRV_CI_PowerControl (DRV_DeviceNameType DeviceName, EN_DRV_CI_PWRCTRL enPwrCtrl, bool b8Force)
 * \brief
 *        Control the CI device power mode. This function not support in this version.
 * 
 * \param	DeviceName						(Input) CI device name to control
 * \param	enPwrCtrl						(Input) Setting the CI device power mode
 * \code
 * 	  enPwrCtrl						description
 * 	---------------------------------------------------------------------
 * 	EN_DRV_CI_POWER_ON_V500 	Switch on the power 5.0V to the DVBCI Module
 * 	EN_DRV_CI_POWER_ON_V330 	Switch on the power 3.3V to the DVBCI Module
 * 	EN_DRV_CI_POWER_OFF 		Switch on the power to the DVBCI Module
 * 	\endcode
 * \param b8Force			(Input) Force power down the device or not
 * \code
 * 	TRUE, Power control the CI right now
 * 	FALSE, Wait until all open close then power control CI 
 * \endcode
 *    
 * \return	CI Operation Error Code
 * \retval	ERROR_NOT_SUPPORTED				The function is not supported.
 * \retval	ERROR_CI_UNKNOW_DEVICE			Unknow Device 
 */
 
ErrorCode DRV_CI_Lock (u32 u32Handle, bool b8Lock);
/*!\fn ErrorCode DRV_CI_Lock (u32 u32Handle, bool b8Lock)
 * \brief
 *		Set the CI device to protection mode.
 *		No other handle can read the CI device unless unlock.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 * \param b8Lock							(Input) Lock the CI device or not
 * \code
 * 	TRUE, Lock the CI
 * 	FALSE, Unlock the CI
 * \endcode
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */
 
ErrorCode DRV_CI_GetConfig (const u32 u32Handle, ST_CI_Config* pstPara);
/*!\fn ErrorCode DRV_CI_GetConfig (const u32 u32Handle, ST_CI_Config* pstPara)
 *
 * \brief
 * 		Get the parameter of the CI configuration in use.
 *
 * \param	u32Handle			(Input) An open handle, as returned by the Open function
 * \param	pstPara				(Output) CI device config parameter
 *
 * \return	CI Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 */

ErrorCode DRV_CI_SetConfig (const u32 u32Handle, ST_CI_Config* pstPara);
/*!\fn ErrorCode DRV_CI_SetConfig (const u32 u32Handle, ST_CI_Config* pstPara)
 *
 * \brief
 * 		Set the parameter of the CI configuration.
 *
 * \param	u32Handle			(Input) An open handle, as returned by the Open function
 * \param	pstPara				(Input) CI device config parameter
 *
 * \return	CI Operation Error Code
 * \retval	ERROR_NO_ERROR					Operation Success
 * \retval	ERROR_INVALID_HANDLE			Handle is not valid
 * \retval	ERROR_BAD_PARAMETER				Bad parameter passed
 * \retval	ERROR_CI_ACCESS					Handle is lock without access
 */
 
ErrorCode DRV_CI_ModSWReset (const u32 u32Handle);
/*!\fn ErrorCode DRV_CI_ModSWReset (const u32 u32Handle)
 * \brief
 *		This function set the Reset bit of the Command Register of the Common Interface associated with the Handle.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_CI_SWRESET					CI Software reset error
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 * \retval ERROR_CI_NO_MODULE				No CI CAM in slot
 */

ErrorCode DRV_CI_ModHWReset (const u32 u32Handle, u32 u32MSResetTime);
/*!\fn ErrorCode DRV_CI_ModHWReset (const u32 u32Handle, u32 u32MSResetTime)
 * \brief
 *		Reset the DVBCI Module associated with the Handle.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 * \param u32MSResetTime					(Input) Reset hold time
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_CI_HWRESET					CI Hardware reset error
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_Read (const u32 u32Handle, u8 *pu8Buffer, u16 u16MaxBufferSize, u16 *pu16ByteRead);
/*!\fn ErrorCode DRV_CI_Read (const u32 u32Handle, u8 *pu8Buffer, u16 *pu16ByteRead)
 * \brief
 *		Read the DVBCI module associated with a handle in the IO mode.
 *
 * \param u32Handle							(Input)  An open handle, as returned by the Open function
 * \param *pu8Buffer						(Output) Read data buffer pointer
 * \param *pu16ByteRead						(Output) The number of bytes successfully read
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_TIMEOUT					Wait Timeout
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_READ					CI data resd error
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_Write (const u32 u32Handle, u8 *pu8Buffer, u16 u16ByteToWrite, u16 *pu16ByteWrited);
/*!\fn ErrorCode DRV_CI_Write (const u32 u32Handle, u8 *pu8Buffer, u16 u16ByteToWrite, u16 *pu16ByteWrited)
 * \brief
 *		Write the DVBCI module associated with a handle in the IO mode.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 * \param pu8Buffer							(Input) Wirte data buffer pointer
 * \param *u16ByteToWrite					(Input) Number of bytes to be written from the Buffer
 * \param pu16ByteWrited					(Output) The number of bytes successfully written
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_TIMEOUT					Wait Timeout
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_WRITE					CI data write error
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_CheckCIS (const u32 u32Handle);
/*!\fn ErrorCode DRV_CI_CheckCIS (const u32 u32Handle)
 * \brief
 *		Read the Card Information Structure (CIS) and Check it with conformant of DVBCI standard, 
 *		also give the Configuration Option Register(COR) related information.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_CIS_READ				CI CIS read error
 * \retval ERROR_CI_NO_MODULE				No CI CAM in slot
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */
 
ErrorCode DRV_CI_WriteCOR (const u32 u32Handle);
/*!\fn ErrorCode DRV_CI_WriteCOR (const u32 u32Handle)
 * \brief
 *		Write to the COR location the value of the Configuration Index.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle value is not accepted 
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_ReadIO (const u32 u32Handle, EN_DRV_IO_ADDR eReg, u8 *pu8Buffer, u32 length);
/*!\fn ErrorCode DRV_CI_ReadIO (const u32 u32Handle, EN_DRV_IO_ADDR eReg, u8 *pu8Buffer, u32 length)
 * \brief
 *		Reads the I/O byte register specified by eReg and stores the value at pu8Buffer.
 *
 * \param u32Handle						    (Input)  An open handle, as returned by the Open function
 * \param eReg						           (Input)  I/O byte register address
 * \param *pu8Buffer						    (Output) Return I/O byte register buffer
 * \Param length                                                  (Input) Number of bytes to read
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_TIMEOUT					       Wait Timeout
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_READ					       CI data resd error
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_WriteIO (const u32 u32Handle, EN_DRV_IO_ADDR eReg, u8 *pu8Buffer, u32 length);
/*!\fn ErrorCode DRV_CI_WriteIO (const u32 u32Handle, EN_DRV_IO_ADDR eReg, u8 *pu8Buffer, u32 length)
 * \brief
 *		Writes the byte value pointed to by pu8Buffer to the I/O register specified by eReg.
 *
 * \param u32Handle						    (Input)  An open handle, as returned by the Open function
 * \param eReg						           (Input)  I/O byte register address
 * \param *pu8Buffer						    (Output) Return I/O byte register buffer
 * \Param length                                                  (Input) Number of bytes to read
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_TIMEOUT					       Wait Timeout
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_READ					       CI data resd error
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */
 
ErrorCode DRV_CI_MEMRead (const u32 u32Handle, u32 addr, u8 *pu8Tuple, u32 length);
/*!\fn ErrorCode DRV_CI_MEMRead (const u32 u32Handle, u32 addr, u8 *pu8Tuple, u32 length)
 *
 * \brief
 *		Read length bytes from the Attribute Memory of the current module at addr start address and stores them at pu8Tuple. 
 *		
 * \param u32Handle						    (Input)  An open handle, as returned by the Open function
 * \param addr						           (Input) Attribute Memory start address
 * \param *pu8Tuple						    (Output) Writes the byte value pointed to by pu8Tuple
 * \Param length                                                  (Input) Number of bytes to read
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_CIS_READ				       CI CIS read error
 * \retval ERROR_CI_NO_MODULE				No CI CAM in slot
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_MEMWrite (const u32 u32Handle, u32 addr, u8 *pu8Tuple, u32 length);
/*!\fn ErrorCode DRV_CI_MEMWrite (const u32 u32Handle, u32 addr, u8 *pu8Tuple, u32 length)
 *
 * \brief
 *		Write nbytes bytes from pu8Tuple to the Attribute Memory of the current module at addr start address. 
 *		
 * \param u32Handle						    (Input)  An open handle, as returned by the Open function
 * \param addr						           (Input) Attribute Memory start address
 * \param *pu8Tuple						    (Input) Source buffer pointer
 * \Param length                                                  (Input) Number of bytes to write
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_CIS_READ				       CI CIS read error
 * \retval ERROR_CI_NO_MODULE				No CI CAM in slot
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_ControlTS (const u32 u32Handle, EN_DRV_CI_TSBYPASS_MODE enTSBypassMode);
/*!\fn ErrorCode DRV_CI_ControlTS (const u32 u32Handle, EN_DRV_CI_TSBYPASS_MODE enTSBypassMode)
 * \brief
 *		Switch TS path. This function only controls GPIO for TS path. 
 *		If TS path control by DMUX module, Middleware need to handle TS path switching with DMUX module.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 * \param enTSBypassMode					(Input) Enable or Disable the TS through DVBCI Module
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle value is not accepted
 */

ErrorCode DRV_CI_SetCommand (const u32 u32Handle, EN_DRV_CI_COMMAND enCommand, bool b8Value);
/*!\fn ErrorCode DRV_CI_SetCommand (const u32 u32Handle, EN_DRV_CI_COMMAND enCommand, u8 u8Value)
 * \brief
 *		Set the CI Command Register's bits of the Command Interface.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 * \param enCommand							(Input) Command register bit to be set
 * \param b8Value							(Input) 0 or 1 to set the register bit
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle value is not accepted
 * \retval ERROR_CI_ACCESS					Handle is lock without access
 */

ErrorCode DRV_CI_GetStatus (const u32 u32Handle, EN_DRV_CI_STATUS enStatus, bool *pb8Value);
/*!\fn ErrorCode DRV_CI_GetStatus (const u32 u32Handle, EN_DRV_CI_STATUS enStatus, u8 *pu8Value)
 * \brief
 *		Read the CI Status Register of the Command Interface.
 *
 * \param u32Handle							(Input) An open handle, as returned by the Open function
 * \param enStatus							(Input) Status register bit to be checked
 * \param pb8Value							(Output) Status register bit value
 *  
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle value is not accepted
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */
 
ErrorCode DRV_CI_ModCheck (const u32 u32Handle, bool *pb8CIPresent);
/*!\fn ErrorCode DRV_CI_ModCheck (const u32 u32Handle, bool *pb8CIPresent)
 * \brief
 *		User can check the presence of Module with this API. 
 *
 * \param u32Handle							(Input)  An open handle, as returned by the Open function
 * \param pb8CIPresent						(Output) Module is present or not
 * \code
 * 	TRUE, Module is present.
 * 	FALSE, Module is not present.
 * \endcode 
 * 
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 */

ErrorCode DRV_CI_Get_ModuleBufferSize (const u32 u32Handle, u16* pu16BufSize);
/*!\fn ErrorCode DRV_CI_Get_ModuleBufferSize (const u32 u32Handle, u16* pu16BufSize)
 * \brief
 *		Get CI CAM buffer size. 
 *
 * \param u32Handle							(Input)  An open handle, as returned by the Open function
 * \param pu16BufSize						(Output) Return CI buffersize
 * 
 * \return CI Operation Error Code
 * \retval ERROR_NO_ERROR					Operation Success
 * \retval ERROR_INVALID_HANDLE				Handle is not valid
 * \retval ERROR_BAD_PARAMETER				One or more of the parameters was invalid
 * \retval ERROR_CI_NO_MODULE				No CI CAM in slot
 */
#endif //#ifndef __CI_H__
