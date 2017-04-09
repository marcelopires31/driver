#ifndef _DRV_MMEM_H_
#define _DRV_MMEM_H_

#include "def_type.h"
#include "def_err.h"

void *DRV_MEM_memalign(u32 u32Alignment, void *pMemBuff);
/*!\fn void *DRV_MEM_memalign(u32 u32Alignment, void *pMemBuff)
 * \brief
 *
 * \param    u32Alignment              (Input) A alignment number
 * \param    pMemBuff                  (Input) Memory address
 *
 * \return   The point address of aligned memory or invalid value(0)
 *
 */

void *DRV_MEM_malloc(os_mempool_handle u32MemPoolHandle, u32 u32Alignment, u32 u32Size);
/*!\fn void *DRV_MEM_malloc(os_mempool_handle u32MemPoolHandle, u32 u32Alignment, u32 u32Size)
 * \brief
 *
 * \param    u32MemPoolHandle          (Input) Handle of Mempool
 * \param    u32Alignment              (Input) A alignment number
 * \param    u32Size                   (Input) The allocating memory range
 *
 * \return   The point of memory base address or invalid value(0)
 *
 */

ErrorCode DRV_MEM_free(os_mempool_handle u32MemPoolHandle, void *pMemBuff);
/*!\fn ErrorCode DRV_MEM_free(os_mempool_handle u32MemPoolHandle, void *pMemBuff)
 * \brief
 *
 * \param    u32MemPoolHandle          (Input) Handle of Mempool
 * \param    pMemBuff                  (Input) Memory address
 *
 * \return   System Operation Error Code
 *
 * \retval ERROR_NO_ERROR              Operation success
 * \retval OS_ERR_MEMPOOL_EINVAL       Invalid argument
 * \retval OS_ERR_MEMPOOL_ENOENT       No such entity
 *
 */

void *DRV_MEM_mallocz(os_mempool_handle u32MemPoolHandle, u32 u32Alignment, u32 u32Size);
/*!\fn void *DRV_MEM_mallocz(os_mempool_handle u32MemPoolHandle, u32 u32Alignment, u32 u32Size)
 * \brief
 *
 * \param    u32MemPoolHandle          (Input) Handle of Mempool
 * \param    u32Alignment              (Input) A alignment number
 * \param    u32Size                   (Input) The allocating memory range
 *
 * \return   The point of memory base address or invalid value(0)
 *
 */

#endif /* _DRV_MMEM_H_ */
