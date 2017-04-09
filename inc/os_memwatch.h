#ifndef OS_MEM_WATCH_H
#define OS_MEM_WATCH_H

#if (OS_MEM_WATCH == 1)

#include "os.h"
#include "drv_mmem.h"

void *OS_MemWatchAlloc(os_mempool_handle u32MemPoolHandle, u32 u32Size, u32 u32WaitTime, const char *file, int line);
ErrorCode OS_MemWatchFree(os_mempool_handle u32MemPoolHandle, void *pMem, const char *file, int line);
void *DRV_MemWatch_malloc(os_mempool_handle u32MemPoolHandle, u32 u32Alignment, u32 u32Size, const char *file, int line);
ErrorCode DRV_MemWatch_free(os_mempool_handle u32MemPoolHandle, void *pMemBuff, const char *file, int line);

#define OS_MemAlloc(h, s, t)			OS_MemWatchAlloc(h, s, t, __FILE__, __LINE__)
#define OS_MemFree(h, p)				OS_MemWatchFree(h, p, __FILE__, __LINE__)
#define DRV_MEM_malloc(h, s, t)			DRV_MemWatch_malloc(h, s, t, __FILE__, __LINE__)
#define DRV_MEM_free(h, p)				DRV_MemWatch_free(h, p, __FILE__, __LINE__)

#endif /* OS_MEM_WATCH */

#endif /* OS_MEM_WATCH_H */
