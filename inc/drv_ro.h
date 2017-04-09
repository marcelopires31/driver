//**************************************************************************
//			Copyright (c) , Inc . All rights reserved.
//			STB/SA, all right reserved.
//
//	Product	: STB Firmware
//
//	Date	: 
//	Author	: 
//	Purpose	: Provide RO APIs
//	Sources	: 
//**************************************************************************
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
//	----------------------------------------		-------------------

#ifndef __DRV_RO_H__
#define __DRV_RO_H__

/*-----------------------------------------------------------------------------*/
/* Including Files                                                             */
/*-----------------------------------------------------------------------------*/
#include "def_type.h"
#include "def_err.h"

/*-----------------------------------------------------------------------------*/
/* Constant Definitions                                                        */
/*-----------------------------------------------------------------------------*/
#define SIZE_OF_RO_HEADER_TAG 			4 		/*!< The size of header tag, ex: "GzRo"        	*/
#define SIZE_OF_RO_HEADER_VERSION 		4 		/*!< The size of header version, ex:"101a"      */
#define SIZE_OF_SYMBOL_NAME 			8 		/*!< The size of symbol name 					*/
#define SIZE_OF_SYMBOL_MAGIC 			4 		/*!< The size of symbol magic, 					*/
#define SIZE_OF_SYMBOL_ID 				(SIZE_OF_SYMBOL_NAME + SIZE_OF_SYMBOL_MAGIC+4) 
#define SIZE_OF_SYMBOL_HEADER 			(sizeof(ST_RO_SymbolHeader))

/**
 * \brief
 * enumurate to indicate the error of system
 */
enum
{
	ERROR_RO_OUT_OF_RANGE = ERROR_BASE_DRV_RO,		/*!< Out of range							*/
	ERROR_RO_UNKNOW_DEVICE,
	ERROR_RO_TAG_FAIL,								/*!< Ro Tag is not equal "GzRo"				*/
	ERROR_RO_SEARCH_FAIL,	 						/*!< Search Ro faily						*/	
	ERROR_RO_FLASH_OP_FAIL,							/*!< Flash operate faily 					*/	
	ERROR_RO_OTHERS,								/*!< Other error							*/
	ERROR_RO_TOTAL,
};

typedef struct
{
	u32		u32ImgStampInfoSize; 						/*!< Stamp information struct size   	   */
	u32		u32FlashStartAddrOfAppImg; 					/*!< Flash start address of App image      */	
} ST_DRV_RO_INIT_PARAMS, *PST_DRV_RO_INIT_PARAMS;


typedef struct
{
	char	strTag[SIZE_OF_RO_HEADER_TAG]; 				/*!< The header tag, ex:"GzRo"      */
	char	strVersion[SIZE_OF_RO_HEADER_VERSION]; 		/*!< The header version, ex:"101a"      */
	u32		u32SymbolNum; 								/*!< Symbol number, the value indicate how much ro files in flash     */
} ST_RO_StartHeader, *PST_RO_StartHeader;


typedef struct
{
	char	strSymbolName[SIZE_OF_SYMBOL_NAME]; 		/*!< Symbol name, ex:"GZ", "Wma", "Mpg"...      */
	u8		au8MagicNumber[SIZE_OF_SYMBOL_MAGIC]; 		/*!< Symbol magic number, this is a digest of symbol content      */
	u32		u32Size; 									/*!< Content size      */
	u32		u32Offset; 									/*!< Offset address from header start point      */
} ST_RO_SymbolHeader, *PST_RO_SymbolHeader;


ErrorCode DRV_RO_Open (u32 *pu32Handle);
/*!\fn ErrorCode DRV_RO_Open (u32 *pu32Handle)
 * \brief 
 * 		Open the flash operation of Ro module.
 * 
 * \param pu32Handle					(Input)	An open handle, as returned by the Open function
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

ErrorCode DRV_RO_Close (u32 *pu32Handle);
/*!\fn ErrorCode DRV_RO_Close (u32 *pu32Handle)
 * \brief 
 * 		Close the flash operation of Ro module.
 * 
 * \param pu32Handle					(Input)	An open handle, as returned by the Open function
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

ErrorCode DRV_RO_ReadFlash (u32 u32Handle, u32 u32Offset, u32 u32size, u8* pu8Buf);
/*!\fn ErrorCode DRV_RO_ReadFlash (u32 u32Handle, u32 u32Offset, u32 u32size, u8* pu8Buf)
 * \brief 
 * 		Read data from flash.
 * 
 * \param pu32Handle					(Input)	An open handle, as returned by the Open function
 * \param u32Offset						(Input)	offset address
 * \param u32size						(Input)	data size
 * \param pu8Buf						(Output) data buffer, user need assigned it a memory address
 *
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

ErrorCode DRV_RO_ProtectFlash (u32 u32Handle, bool b8EnProtect);
/*!\fn ErrorCode DRV_RO_ProtectFlash (u32 u32Handle, bool b8EnProtect)
 * \brief 
 * 		Set the attributes of lock.
 * 
 * \param pu32Handle					(Input)	An open handle, as returned by the Open function
   \code
	True, Lock the resource
	False, Unlock the resource
   \endcode
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

ErrorCode DRV_RO_GetFlashPhysicalAddr (u32 u32Handle, u32 u32Offset, u32* pu32PhysicalAddr);
/*!\fn ErrorCode DRV_RO_GetFlashPhysicalAddr (u32 u32Handle, u32 u32Offset, u32* pu32PhysicalAddr)
 * \brief 
 * 		Get the physical address of flash. This API will call an API of drv_flash to get the physical address.
 * 
 * \param pu32Handle					(Input)	An open handle, as returned by the Open function
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

ErrorCode DRV_RO_Init (PST_DRV_RO_INIT_PARAMS pstRoInitParam);
/*!\fn void DRV_RO_Init(PST_DRV_RO_INIT_PARAMS pstRoInitParam)
 * \brief 
 * 		RO initialization API, set up the start address of APP image and the header size of App stamp information.
 * 
 * \param pstRoInitParam				(Input)  the parameter structure of RO.
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INITIALISED			A previous Init call has not been terminated
 * 
 */

ErrorCode DRV_RO_Terminate (void);
/*!\fn ErrorCode DRV_RO_Terminate (void)
 * \brief 
 * 		Terminate API, Close Ro module and clear the parameter data of RO module
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_INITIALISED			A previous Init call has not been terminated
 * 
 */

ErrorCode DRV_RO_GetRoStartHeader (u32 u32Handle, PST_RO_StartHeader pstRoStartHeader, u32* pu32RoStartHeaderOffset);
/*!\fn ErrorCode DRV_RO_GetRoStartHeader (u32 u32Handle, PST_RO_StartHeader pstRoStartHeader, u32* pu32RoStartHeaderOffset)
 * \brief 
 * 		Geting the start header of RO.
 *
 * \param u32Handle						(Input)	An open handle, as returned by the Open function
 * \param pstRoStartHeader				(Output) An ro start header structure pointer, user needs assigning it a memory address.
 * \param pu32RoStartHeaderOffset		(Output) the offset address of ro start header.

 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_INITIALISED			A previous Init call has not been terminated
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_RO_TAG_FAIL 			Ro tag error
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

ErrorCode DRV_RO_SearchSymbolHeaderByIdx (u32 u32Handle, u32 u32RoSymbolIdx, PST_RO_SymbolHeader pstRoSymbolHeader, u32* pu32RoSymbolOffset);
/*!\fn ErrorCode DRV_RO_SearchSymbolHeaderByIdx (u32 u32Handle, u32 u32RoSymbolIdx, PST_RO_SymbolHeader pstRoSymbolHeader, u32* pu32RoSymbolOffset)
 * \brief 
 * 		Search Ro symbol header by symbol index.
 * 
 * \param u32Handle						(Input)	An open handle, as returned by the Open function
 * \param u32RoSymbolIdx				(Intput)  An ro symbol header index
 * \param pstRoSymbolHeader				(Output)  An ro symbol header pointer, user needs assigning it a memory address.
 * \param pu32RoSymbolOffset			(Output)  the offset address of ro symbol header.
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INITIALISED			A previous Init call has not been terminated
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

ErrorCode DRV_RO_SearchRoZip (u32 u32Handle, u8 *pu8ID, u32 *pu32FlashAddress, u32 *pu32ROSize);
/*!\fn ErrorCode DRV_RO_SearchRoZip (u32 u32Handle, u8 *pu8ID, u32 *pu32FlashAddress, u32 *pu32ROSize)
 * \brief 
 * 		Search the Ro zip.
 * 
 * \param u32Handle						(Input)	An open handle, as returned by the Open function
 * \param pu8ID							(Intput)  Ro ID pointer, this ID includes symbol name, magic number and size 
 * \param pu32FlashAddress				(Output)  Ro data address, this address is on flash.
 * \param pu32ROSize					(Output)  Ro data size.
 * 
 * \return System Error Code
 * \retval ERROR_NO_ERROR				Success
 * \retval ERROR_BAD_PARAMETER			Parameter error
 * \retval ERROR_INITIALISED			A previous Init call has not been terminated
 * \retval ERROR_RO_TAG_FAIL 			Ro tag error.
 * \retval ERROR_RO_SEARCH_FAIL 		Search Ro faily. all Ros don't match the ID
 * \retval ERROR_RO_FLASH_OP_FAIL		Flash operation fail.
 * 
 */

#endif// _DRV_RO_H_
