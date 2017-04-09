//**************************************************************************
//         Copyright (c) , Inc . All rights reserved.
//         STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date		: 
//	Author		: 
//	Purpose	: Provide EVENT Control 
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

#ifndef __DRV_EVENT_H__
#define __DRV_EVENT_H__

#include "def_type.h"
#include "def_err.h"
#include "os.h"

/*
 * Brief: DRV_TSPU global define.
 */
#define DRV_EVENT_MAX_EVENT_ID_NUM 				           (32)                     /*!< The maximum number of Event ID     */

/**
 * \brief
 * enumerate to indicate the error of operation
 */
enum
{ 
    ERROR_EVENT_HANDLE_NOT_CLOSED               = ERROR_BASE_DRV_EVENT,             /*!< Event Handle not closed                */ 
    ERROR_EVENT_DUPLICATE_DEVICE_NAME,                                              /*!< Duplicate Device Name                  */ 
    ERROR_EVENT_DUPLICATE_EVENT_NAME,                                               /*!< Duplicate Event Name                   */  
    ERROR_EVENT_INVALID_DEVICE_NAME,                                                /*!< Invalid Device Name                    */
    ERROR_EVENT_INVALID_EVENT_NAME,                                                 /*!< Invaild Event Name                     */
    ERROR_EVENT_ALREADY_SUBSCRIBE,                                                  /*!< Notify already been subseribed         */
    ERROR_EVENT_NOT_SUBSCRIBE,                                                      /*!< Notify not subscribe                   */
    ERROR_EVENT_DEVICE_RESOURCE,                                                    /*!< Event don't have device resource       */    
};
 
/**
 * \brief
 * enumerate to indicate the EVENT PRIORITY
 */ 
typedef enum
{
	EN_DRV_EVENT_PRIORITY_LOW,                                                      /*!< Low Priority                           */
	EN_DRV_EVENT_PRIORITY_HIGH,                                                     /*!< High Priority                          */
	EN_DRV_EVENT_PRIORITY_REALTIME,                                                 /*!< Real Time Priority                     */
	EN_DRV_EVENT_PRIORITY_NUM
}EN_DRV_EVENT_PRIORITY;
 
 
/*!
 * \brief
 * Definition of event notify function pointer to let the caller know when operation has completed in capture mode
 * \param	u32EVTHandle		(Output) An open handle, as returned by the Open function
 * \param	u32EventID			(Output) Enumerate to indicate the event of device
 * \param	u32Data				(Output) The data information.
 */ 
typedef void (* DRV_EVENTT_NOTIFY_FN ) (u32 u32EVTHandle, u32 u32EventID, u32 u32Data);
 
/**
 * \brief
 *  the Event subscribe structure
 */  
typedef struct
{
	EN_DRV_EVENT_PRIORITY		    enEvtPriority;                                  /*!< Notify Prority                         */
	DRV_EVENTT_NOTIFY_FN	  		pfnNotify;	                                    /*!< Notify function pointer                */
} ST_DRV_EVENT_SUBSCRIBE_PARAMS, *PST_DRV_EVENT_SUBSCRIBE_PARAMS;
 

/**
 * \brief
 *  the Event Initial structure
 */
typedef struct
{
	os_mempool_handle	u32MemPoolHandle;				                            /*!<  memory pool handle for event module   */
}ST_DRV_EVENT_INIT_PARAMS, *PST_DRV_EVENT_INIT_PARAMS;
 
  
//function define
u8* DRV_EVENT_GetVersion (void);
/*!\fn u8* DRV_EVENT_GetVersion (void)
 *
 * \brief
 * 		Get info of the module version
 *
 *
 * \return DRV_EVENT Version String
 *
 */


ErrorCode DRV_EVENT_Initialize (DRV_DeviceNameType DeviceName, PST_DRV_EVENT_INIT_PARAMS pstParams);
/*!\fn ErrorCode DRV_EVENT_Initialize (DRV_DeviceNameType DeviceName, PST_DRV_EVENT_INIT_PARAMS pstParams)
 * \brief 
 *		  Initial the Target device with ST_DRV_EVENT_INIT_PARAMS setting	
 *
 * \param DeviceName	                    (Input)	The name of device, length must less 16 byte
 * \param pstParams			                (Input) Pointer of initial parameter
 * 
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR					No error	
 * \retval ERROR_BAD_PARAMETER				Bad parameter
 * \retval ERROR_INITIALISED				This EVENT have initialled
 * \retval ERROR_EVENT_DEVICE_RESOURCE	    Event don't have device resource
 * 
 */
 
ErrorCode DRV_EVENT_Terminate (DRV_DeviceNameType DeviceName, bool b8Force);
/*!\fn ErrorCode DRV_EVENT_Terminate (DRV_DeviceNameType DeviceName, bool b8Force)
 * \brief
 *		  Terminate the usage of specific device
 *
 * \param  DeviceName			            (Input) The name of device, length must less 16 byte
 * \param  b8Force			                (Input) Force terminate the device or not
 * \code
	TRUE,  Terminate the device right now
	FALSE, Wait until all open handles close then terminate
   \endcode
 *
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR					No error
 * \retval ERROR_BAD_PARAMETER				Bad parameter
 * \retval ERROR_EVENT_INVALID_DEVICE_NAME	Invalid Device Name
 * \retval ERROR_EVENT_HANDLE_NOT_CLOSED	Operation invalid, because handle not close
 */

ErrorCode DRV_EVENT_Open (DRV_DeviceNameType DeviceName, DRV_DeviceNameType EventName, u32 *pu32EvtHandle);
/*!\fn ErrorCode DRV_EVENT_Open (DRV_DeviceNameType DeviceName, DRV_DeviceNameType EventName, u32 *pu32EvtHandle)
 * \brief
 *		   To open a device handle, user control the device through this handle
 * \param  DeviceName                       (Input)	The name of device, length must less 16 byte
 * \param  EventName		                (Input)	The name of EVT Handle, length must less 16 byte
 * \param  pu32EvtHandle	                (Output)The returned EVT handle of the opened device driver
 *
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR					No error
 * \retval ERROR_BAD_PARAMETER				Bad parameter
 * \retval ERROR_EVENT_INVALID_DEVICE_NAME	Invalid Device Name
 * \retval ERROR_EVENT_DUPLICATE_EVENT_NAME	Duplicate Event Name
 * \retval ERROR_NO_MEMORY				    The memory allocate is fail 
 */

ErrorCode DRV_EVENT_Close (u32* pu32EvtHandle);
/*!\fn ErrorCode DRV_EVENT_Close (u32* pu32EvtHandle)
 * \brief
 * 		Release resource associated with a previous opened handle
 *
 * \param	pu32EvtHandle     	            (Input) Pointer to the opening handle number of the Target device
 *
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR                   No error
 * \retval ERROR_BAD_PARAMETER		        Bad parameter
 * \retval ERROR_INVALID_HANDLE             Handle is not valid
 */ 
 
ErrorCode DRV_EVENT_Subscribe (u32 u32EvtHandle, u32 u32EventID, PST_DRV_EVENT_SUBSCRIBE_PARAMS pstParams);
/*!\fn ErrorCode DRV_EVENT_Subscribe (u32 u32EvtHandle, u32 u32EventID, PST_DRV_EVENT_SUBSCRIBE_PARAMS pstParams)
 * \brief
 *		  To set the notify by event handle and event id
 *
 * \param  u32EvtHandle		                (Input) An open handle, as returned by the Open function 
 * \param  u32EventID		                (Input) The constant of EVENT
 * \param  pstParams		                (Input) Pointer of subscribe parameter
 *
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR					No error 
 * \retval ERROR_BAD_PARAMETER				Bad parameter
 * \retval ERROR_INVALID_HANDLE         	Handle is not valid
 * \retval ERROR_EVENT_ALREADY_SUBSCRIBE   	Notify already been subseribed
 * \retval ERROR_NO_MEMORY				    The memory allocate is fail 
 */

ErrorCode DRV_EVENT_Unsubscribe (u32 u32EvtHandle, u32 u32EventID, PST_DRV_EVENT_SUBSCRIBE_PARAMS pstParams);
/*!\fn ErrorCode DRV_EVENT_Unsubscribe (u32 u32EvtHandle, u32 u32EventID, PST_DRV_EVENT_SUBSCRIBE_PARAMS pstParams)
 * \brief
 *		  To release the notify by event handle and event id
 *
 * \param  u32EvtHandle		                (Input) An open handle, as returned by the Open function
 * \param  u32EventID		                (Input) The constant of EVENT
 * \param  pstParams		                (Input) Pointer of subscribe parameter
 *
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR					No error 
 * \retval ERROR_BAD_PARAMETER				Bad parameter
 * \retval ERROR_INVALID_HANDLE         	Handle is not valid
 * \retval ERROR_EVENT_NOT_SUBSCRIBE	    Notify not subscribe
 */

ErrorCode DRV_EVENT_Notify (u32 u32EvtHandle, u32 u32EventID, u32 u32Data);
/*!\fn ErrorCode DRV_EVENT_Notify (u32 u32EvtHandle, u32 u32EventID, u32 u32Data)
 * \brief
 *		  To trigger the notify by event ID
 *
 * \param  u32EvtHandle		                (Input) An open handle, as returned by the Open function
 * \param  u32EventID		                (Input) The ID of EVENT
 * \param  u32Data       	                (Input) The data information.
 *
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR					No error 
 * \retval ERROR_BAD_PARAMETER				Bad parameter
 * \retval ERROR_INVALID_HANDLE         	Handle is not valid
 * \retval ERROR_NO_MEMORY				    The memory allocate is fail 
 */

ErrorCode DRV_EVENT_Get_Handle_By_Name (DRV_DeviceNameType EventName, u32 *pu32EvtHandle);
/*!\fn ErrorCode DRV_EVENT_Get_Handle_By_Name (DRV_DeviceNameType EventName, u32 *pu32EvtHandle)
 * \brief
 *		  To get the Event Handle by Event Name
 *
 * \param  EventName		                (Input)	The name of EVT Handle, length must less 16 byte
 * \param  pu32EvtHandle		            (Output)The returned EVT handle of the opened device driver
 *
 * \return EVENT Operation Error Code
 * \retval ERROR_NO_ERROR					No error 
 * \retval ERROR_BAD_PARAMETER				Bad parameter
 * \retval ERROR_EVENT_INVALID_EVENT_NAME   Invaild Event Name
 */

#endif //#ifndef __DRV_EVENT_H__
