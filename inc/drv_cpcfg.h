#ifndef _DRV_CPCFG_H_
#define _DRV_CPCFG_H_

/*******************************************************************************************/
#include "def_type.h"
#include "def_err.h"



/*!
 *  Enumeration of CAP mode.
 */
typedef enum
{
	EN_DRV_CPCFG_CAP_MODE_UNSUPPORT,     
	EN_DRV_CPCFG_CAP_MODE_SUPPORT,    
}EN_DRV_CPCFG_CAP_MODE;

/*!
 *  Enumeration of CAP type
 */
typedef enum _EN_DRV_CPCFG_CAP_TYPE
{
	EN_DRV_CPCFG_CAP_TYPE_NULL = -1,		/*!< NULL type */
	EN_DRV_CPCFG_CAP_TYPE_DIVX_HD,			/*!< DivX HD type */
	EN_DRV_CPCFG_CAP_TYPE_DIVX_PLUS_HD,		/*!< DivX HD Plus type */
	EN_DRV_CPCFG_CAP_TYPE_DRA,				/*!< DRA type */
	EN_DRV_CPCFG_CAP_TYPE_MS11,				/*!< MS11 type */
	EN_DRV_CPCFG_CAP_TYPE_DTS,				/*!< DTS type */
	EN_DRV_CPCFG_CAP_TYPE_RMVB,				/*!< RMVB type */
	EN_DRV_CPCFG_CAP_TYPE_SRS,				/*!< SRS type */
	EN_DRV_CPCFG_CAP_TYPE_VC1,				/*!< VC-1 type */
	EN_DRV_CPCFG_CAP_TYPE_AC3,				/*!< AC-3 type */
	EN_DRV_CPCFG_CAP_TYPE_DD_PLUS,			/*!< DD+ type */
	EN_DRV_CPCFG_CAP_TYPE_MS10,				/*!< MS10 type */
	EN_DRV_CPCFG_CAP_TYPE_DIVX3_11,			/*!< DIVX3.11 type */
	EN_DRV_CPCFG_CAP_TYPE_AVS,				/*!< AVS type */
	EN_DRV_CPCFG_CAP_TYPE_CI_PLUS,			/*!< CI+ type */
	EN_DRV_CPCFG_CAP_TYPE_HBBTV,			/*!< HbbTV type */
	EN_DRV_CPCFG_CAP_TYPE_FREEVIEW_HD,		/*!< Freeview HD type */
	EN_DRV_CPCFG_CAP_TYPE_DDCO,				/*!< DDCO type */
	EN_DRV_CPCFG_CAP_TYPE_TOTAL				/*!< Count of total, just for reference, not a real type */
} EN_DRV_CPCFG_CAP_TYPE;

/*!\fn ErrorCode DRV_CPCFG_UID_Query(u32 *pu32UniqueID)
 * \brief
 *		Query the UniqueID for customer
 *
 * \param pu32UniqueID								(Output) Unique ID
 *
 * \return Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval ERROR_HARDWARE_FAIL					HW Fail
 */
ErrorCode DRV_CPCFG_UID_Query(u32 *pu32UniqueID);

/*!\fn ErrorCode DRV_CPCFG_CID_Query(u32 *pu32CustomerID)
 * \brief
 *		Query the PartID for customer
 *
 * \param pu32CustomerID								(Output) Customer ID
 *
 * \return Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval ERROR_HARDWARE_FAIL					HW Fail
 */
ErrorCode DRV_CPCFG_CID_Query(u32 *pu32CustomerID);


/*!\fn ErrorCode PLAT_CPCFG_CAP_Query(EN_DRV_CPCFG_CAP_TYPE enCapType, EN_DRV_CPCFG_CAP_MODE *penCapMode)
 * \brief
 *		Query the CAP
 *
 * \param enCapType								(Input) Cap Type
 * \param penCapMode							(Ouput) Capability
 *
 * \return Operation Error Code
 * \retval ERROR_NO_ERROR						no error
 * \retval ERROR_HARDWARE_FAIL					HW Fail
 */
ErrorCode PLAT_CPCFG_CAP_Query(EN_DRV_CPCFG_CAP_TYPE enCapType, EN_DRV_CPCFG_CAP_MODE *penCapMode);


/*******************************************************************************************/
#endif //#ifndef _DRV_CPCFG_H_
