#ifndef __DRV_USB_H__
#define __DRV_USB_H__

#include "drv_gpio.h"
#include "drv_config.h"

typedef enum {
    USB_CONTROLLER_SPEED_HIGH,
    USB_CONTROLLER_SPEED_FULL   
}enUSBControllerSpeed;

ErrorCode DRV_USB_Init(u32 u32MemHandle);
bool DRV_USB_CheckConnect(void);
void DRV_USB_SetPowGPIO(u32 u32PowGPIOHandle, PST_GPIO pstPowGPIO, EN_DRV_GPIO_STATUS enActiveVal, u32 u32Port);
void DRV_USB_SetPortPower(u32 u32Port, bool bEnable);
void DRV_USB_SetPower(bool bEnable);
enUSBControllerSpeed DRV_USB_GetEHCISpeed(void);
void DRV_USB_Test_USB_PowerOn(void);
void DRV_USB_Test_USB_PowerOff(void);
void DRV_USB_SafeRemove(u32 num);

// for ESD
bool DRV_USB_CheckDeviceConnect(void);
#endif

