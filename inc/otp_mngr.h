#ifndef _OTP_MNGR_H_
#define _OTP_MNGR_H_

//Init OTP, bTest--for test, nOrderID-- order ID
//must run first
void OTP_MngrInit(BOOL bTest,UINT32 nOrderID);

BOOL OTP_IsCstmSpaceEmpty(void);

// Get TunerType, 8bytes
int OTP_ReadTunerType(unsigned char *buffer);
// Get OTP MAC Address, 6bytes
int OTP_ReadMacAddr(unsigned char *buffer);
// Get OTP customer ID, 3bytes
int OTP_ReadCustomerId(unsigned char *buffer);
// Get OTP orderID, 3bytes
int OTP_ReadOrderId(unsigned char *buffer);
// Get OTP expired date, 3bytes
int OTP_ReadExpiredDate(unsigned char *buffer);

//verify the OTP, if OK then run APP, otherwise need to burn OTP
void OTP_MainTask(void);

#if 0
void OTP_Test_Flash_Write_Read(void);
void OTP_UART_TEST(void);
#endif
#endif

