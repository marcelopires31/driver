//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide FP Control 
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

#ifndef __DRV_FPANEL_H__
#define __DRV_FPANEL_H__

#include "os.h"
#include "def_type.h"
#include "drv_gpio.h"

/**
 * \brief
 *  Enumerate to indicate the device number of front panel
 */
typedef enum
{
	EN_DRV_FP_0,
	EN_DRV_FP_NUM
}EN_DRV_FP_NO;

/**
 * \brief
 * Enumerate to indicate the FP operation error
 */
enum 
{
	ERROR_DRV_FP_DEVICE = ERROR_BASE_DRV_KEYPAD,	
	ERROR_DRV_FP_UNKNOW_DEVICE,	
};

/**
 * \brief
 * Enumerate to indicate the trigger of FP
 */ 
typedef enum
{
	EN_DRV_FP_TRIGGER_LEVEL_LOW,
	EN_DRV_FP_TRIGGER_LEVEL_HIGH,
	EN_DRV_FP_TRIGGER_LEVEL_NUM
}EN_DRV_FP_TRIGGER_LEVEL;

/**
 * \brief
 * Enumerate to indicate the mode of FP
 */
typedef enum
{
	EN_DRV_FP_HARDWARE_MODE,				/*!<  Fpanel is Hardware mode									*/
	EN_DRV_FP_SOFTWARE_MODE,				/*!<  Fpanel is Software mode									*/
	EN_DRV_FP_MODE_NUM
}EN_DRV_FP_MODE;

/**
 * \brief
 * Enumerate to indicate the display outmode of FP
 */
typedef enum
{
	EN_DRV_FP_DISP_OUTMODE_NORMAL,
	EN_DRV_FP_DISP_OUTMODE_OPEN_COLLECTOR,
	EN_DRV_FP_DISP_OUTMODE_NUM
}EN_DRV_FP_DISP_OUTMODE;

/**
 * \brief
 * Enumerate to indicate the keypad mode of FP
 */
typedef enum
{
	EN_DRV_FP_KD_MODE_1_8,						/*!<  KEY PAD MODE: Keypad 1x8 mode.							*/
	EN_DRV_FP_KD_MODE_3_5,						/*!<  KEY PAD MODE: Keypad 3x5 mode.							*/
	EN_DRV_FP_KD_MODE_ADC,						/*!<  KEY PAD MODE: ADC(Analog-to-digital converter) key pad	*/
	EN_DRV_FP_KD_MODE_NUM						// KEY PAD MODE: The last element of enumeration.
}EN_DRV_FP_KD_MODE;

/**
 * \brief
 * Enumerate to indicate the scan speed of FP
 */
typedef enum
{
	EN_DRV_FP_LED_SCAN_SPEED_1M = 1,
	EN_DRV_FP_LED_SCAN_SPEED_2M,
	EN_DRV_FP_LED_SCAN_SPEED_3M,
	EN_DRV_FP_LED_SCAN_SPEED_4M,
	EN_DRV_FP_LED_SCAN_SPEED_5M,
	EN_DRV_FP_LED_SCAN_SPEED_6M,
	EN_DRV_FP_LED_SCAN_SPEED_7M,
	EN_DRV_FP_LED_SCAN_SPEED_8M,
	EN_DRV_FP_LED_SCAN_SPEED_9M,
	EN_DRV_FP_LED_SCAN_SPEED_10M,
	EN_DRV_FP_LED_SCAN_SPEED_11M,
	EN_DRV_FP_LED_SCAN_SPEED_12M,
	EN_DRV_FP_LED_SCAN_SPEED_13M,
	EN_DRV_FP_LED_SCAN_SPEED_14M,
	EN_DRV_FP_LED_SCAN_SPEED_15M,
	EN_DRV_FP_LED_SCAN_SPEED_16M,
	EN_DRV_FP_LED_SCAN_SPEED_17M,
	EN_DRV_FP_LED_SCAN_SPEED_18M,
	EN_DRV_FP_LED_SCAN_SPEED_19M,
	EN_DRV_FP_LED_SCAN_SPEED_20M,
	EN_DRV_FP_LED_SCAN_SPEED_21M,
	EN_DRV_FP_LED_SCAN_SPEED_22M,
	EN_DRV_FP_LED_SCAN_SPEED_23M,
	EN_DRV_FP_LED_SCAN_SPEED_24M,
	EN_DRV_FP_LED_SCAN_SPEED_NUM
}EN_DRV_FP_LED_SCAN_SPEED;

/**
 * \brief
 *  Enumerate to indicate EventID definition.
 */
typedef enum
{
	EN_DRV_FP_EVENT_RX,
	EN_DRV_FP_EVENT_TX,
	EN_DRV_FP_EVENT_INTR,
	EN_DRV_FP_EVENT_DEBOUNCE,	
	EN_DRV_FP_EVENT_CHANGE_CONFIG,
	EN_DRV_FP_EVENT_CLOSE,
	EN_DRV_FP_EVENT_TERM,
	EN_DRV_FP_EVENT_NUM
}EN_DRV_FP_EVENT_TYPE;

/**
 * \brief
 * structure of configure setting 
 */
typedef struct 
{
	os_mempool_handle			u32MemPoolHandle;				/*!< A memory pool handle for FrontPanel module	*/
	ST_GPIO_Open				stGPIO_OpenLED;		
	ST_GPIO_Open				stGPIO_OpenKP;		
	EN_DRV_FP_NO				enFPNo;
	u8							u8DispClkActPolarity;			/*!<  Set active polarity of DispClk.										*/
	u8							u8DispClkPolarity;				/*!<  Set polarity of DispClk. 0:Inverse 1:Direst		    				*/
	u8							u8CommPortNum;					/*!<  (Number of common port) - 1.											*/
	u16							u16DispCmPeriod;				/*!<  Active period of scanning 7-seg displays								*/
	EN_DRV_FP_TRIGGER_LEVEL		enDispTriggerPolarity;			/*!<  Set active polarity of pins Disp.										*/
	EN_DRV_FP_TRIGGER_LEVEL		enDispCmTriggerPolarity;		/*!<  Set active polarity of pins DispCm									*/
	EN_DRV_FP_DISP_OUTMODE		enDispOutputMode;				/*!<  Output mode of common ports. 0 : Normal mode. 1 : Open collector mode.*/
	EN_DRV_FP_LED_SCAN_SPEED	enDispPeriod;					/*!<  Active period of common port.											*/

	EN_DRV_FP_KD_MODE			enKeyPadMode;					/*!<  Key mode. 0 : 1-dimension mode (1x8) 1 : 2-dimension mode (3x5)		*/
	EN_DRV_FP_TRIGGER_LEVEL		enKeyPadTriggerPolarity;		/*!<  Set active polarity of keypad detection								*/

	EN_DRV_FP_MODE				enFPMode;						/*!<  Fpanel Software mode or Hardware mode control							*/
	struct {

		ST_GPIO				st7SegLEDM0;					/*!<  Software FrontPanel LED0 GPIO pin 									*/
		ST_GPIO				st7SegLEDM1;					/*!<  Software FrontPanel LED1 GPIO pin										*/
		ST_GPIO				st7SegLEDM2;					/*!<  Software FrontPanel LED2 GPIO pin										*/
		ST_GPIO				st7SegLEDM3;					/*!<  Software FrontPanel LED3 GPIO pin										*/
		ST_GPIO				st7SegLEDM4;					/*!<  Software FrontPanel LED4 GPIO pin										*/
		ST_GPIO				st7SegData;						/*!<  Software FrontPanel Data GPIO pin										*/
		ST_GPIO				st7SegClock;					/*!<  Software FrontPanel Clock GPIO pin									*/

		ST_GPIO				stKeyScan0;						/*!<  Software KeyPad Scan 0 GPIO pin										*/
		ST_GPIO				stKeyScan1;						/*!<  Software KeyPad Scan 1 GPIO pin										*/
		ST_GPIO				stKeyScan2;						/*!<  Software KeyPad Scan 2 GPIO pin										*/	
	};
}ST_FP_Init, *PST_FP_Init;

/*!
 * \brief
 * Definition of a Callback function to let the caller know when operation has completed in capture mode
 * \param	u32Handle			(Output) An open handle, as returned by the Open function
 * \param	enEventType			(Output) Callback function event type
 * \param	enStatus			(Output) FP Operation status
 * \param	pu32para			(Output) A pointer to the data information. It's context will depend on enEventType.
 */
typedef void (*DRV_FP_CALLBACK)(u32 u32Handle, EN_DRV_FP_EVENT_TYPE enEventType, ErrorCode enStatus, u32* pu32para);

/**
 * \brief
 *  Structure of FP open
 */
typedef struct 
{
	DRV_FP_CALLBACK		fnFPCallback;			/*!< A pointer to the user defined function that will be called when a callback event has occurred */
	u32					u32EvtHandle;			/*!< Event handle for FP 									*/
}ST_FP_Open, *PST_FP_Open;

/**
 * \brief
 *  Structure of FP config
 */ 
typedef struct 
{
}ST_FP_Config, *PST_FP_Config;


ErrorCode DRV_FP_GetVersion (u8* pu8VersionNum);
/*!\fn ErrorCode DRV_FP_GetVersion (u8* pu8VersionNum)
 * \brief 
 *        	Get the Fpanel's Version number        
 * 
 * \param 	pu8VersionNum        			(Output) Version string of FP
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_Initialize (DRV_DeviceNameType DeviceName, PST_FP_Init pstInit);
/*!\fn ErrorCode DRV_FP_Initialize (DRV_DeviceNameType DeviceName, PST_FP_Init pstInit)
 * \brief 
 *        Initial the Fpanel device with PST_FP_Init setting    
 * 
 * \param 	DeviceName        				(Input) Device name of FP
 * \param 	pstInit           				(Input) Fpanel device init parameter
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_FP_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief 
 *        	Terminate the use of the Fpanel device    
 * 
 * \param 	DeviceName        				(Input) Device name of FP
 * \param 	b8Force            				(Input) Force power down the device or not
 * \code
			TRUE							Terminate the Fpanel right now
			FALSE							Wait until all open handles close then terminate
   \endcode
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_Open (DRV_DeviceNameType DeviceName, PST_FP_Open pstOpen, u32 *pu32Handle);
/*!\fn ErrorCode DRV_FP_Open (DRV_DeviceNameType DeviceName, PST_FP_Open pstOpen, u32 *pu32Handle)
 * \brief 
 *        	Open the FP device and associate it with a handle  
 * 
 * \param 	DeviceName        				(Input) Device name of FP
 * \param 	pstOpen							(Input) Fpanel open parameter
 * \param 	pu32Handle        				(Output) The returned handle of the opened FP driver
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_Close (u32* pu32Handle);
/*!\fn ErrorCode DRV_FP_Close (u32* pu32Handle);
 * \brief 
 *        	Close FP device associated with a handle     
 * 
 * \param 	pu32Handle						(Input) Pointer to the opening handle number of the FP device
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_GetConfig (u32 u32Handle, PST_FP_Config pstPara);
/*!\fn ErrorCode DRV_FP_GetConfig (u32 u32Handle, PST_FP_Config pstPara)
 * \brief 
 *        	Get the Fpanel configure Parameter    
 * 
 * \param u32Handle          				(Input) An open handle, as returned by the Open function
 * \param pstPara            				(Output) Return the config parameter of FP device
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_SetConfig (u32 u32Handle, PST_FP_Config pstPara);
/*!\fn ErrorCode DRV_FP_SetConfig (u32 u32Handle, PST_FP_Config pstPara)
 * \brief 
 *        	Set the Fpanel configure Parameter    
 * 
 * \param 	u32Handle          				(Input) An open handle, as returned by the Open function
 * \param 	pstPara            				(Input) Fpanel device configure parameter
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_DisplayChar (u32 u32Handle, u8 u8ASCII, u8 u8DigitNo);
/*!\fn ErrorCode DRV_FP_DisplayChar (u32 u32Handle, u8 u8ASCII, u8 u8DigitNo)
 * \brief 
 *        	Display a word on 7Seg LED 
 * 
 * \param 	u32Handle          				(Input) An open handle, as returned by the Open function
 * \param 	u8ASCII          	 			(Input) ASCII char that want show on front panel
 * \param 	u8DigitNo          				(Input) The number of location the 7Seg LED will show
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_DisplayStr (u32 u32Handle, u8 *pu8String);
/*!\fn ErrorCode DRV_FP_DisplayStr (u32 u32Handle, u8 *pu8String)
 * \brief 
 *        	Show the String on the Panel if the string longer than the Panel, the Panel will like scrolling text
 * 
 * \param 	u32Handle          				(Input) An open handle, as returned by the Open function
 * \param 	pu8String          				(Input) The string want show on Panel
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_DisplayNum (u32 u32Handle, u32 u32Num);
/*!\fn ErrorCode DRV_FP_DisplayNum (u32 u32Handle, u32 u32Num)
 * \brief 
 *        	Display a Number on the Panel  
 * 
 * \param 	u32Handle          				(Input) An open handle, as returned by the Open function
 * \param 	u32Num             				(Input) The Number want show on Panel
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

ErrorCode DRV_FP_Display7SegBit (u32 u32Handle, u8 u8BitShow, u8 u8DigitNo, bool b8BitClear);
/*!\fn ErrorCode DRV_FP_Display7SegBit (u32 u32Handle, u8 u8BitShow, u8 u8DigitNo, bool b8BitClear)
 * \brief 
 *        	Display the bitmap on 7Seg
 * \code
	   	bit7
	      +=====+
	bit2  |     |  bit6
	      |bit1 |
	      +=====+
	bit3  |     |  bit5
	      |     |
	      +=====+ * bit0
	       bit4
   \endcode
 * 
 * \param 	u32Handle          				(Input) An open handle, as returned by the Open function
 * \param 	u8BitShow          				(Input) The bit map on the focus 7Seg LED
 * \param 	u8DigitNo          				(Input) The number of location the 7Seg LED want show
 * \param 	b8BitClear          			(Input) To Clear all bits or not
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 * 
 */

ErrorCode DRV_FP_KP_Enable (u32 u32Handle, bool b8Enable);
/*!\fn ErrorCode DRV_FP_KP_Enable (u32 u32Handle, bool b8Enable)
 * \brief 
 *        	Enable the key pad of front panel event callback  associated with a handle.    
 * 
 * \param 	u32Handle          				(Input) An open handle, as returned by the Open function
 * \param 	b8Enable           				(Input) Enable or Disable the key pad interrupt function callback
 * \code
			TRUE 							Enable the event callback
			FALSE 							Disable the event callback
   \endcode
 * 
 * \return 	FPanel Operation Error Code
 * \retval 	ERROR_NO_ERROR        			Operation Success
 * \retval 	ERROR_BAD_PARAMETER  			One or more of the parameters was invalid
 */

#endif //#ifndef __DRV_FPANEL_H__
