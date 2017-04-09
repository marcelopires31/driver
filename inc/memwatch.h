/*
************************************************************************
**
** Format of error messages in MEMWATCH.LOG:
**  message: <sequence-number> filename(linenumber), information
**
** Errors caught by MemWatch, when they are detected, and any
** actions taken besides writing to the log file MEMWATCH.LOG:
**
**  Double-freeing:
**      A pointer that was recently freed and has not since been
**      reused was freed again. The place where the previous free()
**      was executed is displayed.
**      Detect: delete or free() using the offending pointer.
**      Action: The delete or free() is cancelled, execution continues.
**  Underflow:
**      You have written just ahead of the allocated memory.
**      The size and place of the allocation is displayed.
**      Detect: delete or free() of the damaged buffer.
**      Action: The buffer is freed, but there may be secondary damage.
**  Overflow:
**      Like underflow, but you've written after the end of the buffer.
**      Detect: see Underflow.
**      Action: see Underflow.
**  WILD free:
**      An unrecognized pointer was passed to delete or free().
**      The pointer may have been returned from a library function;
**      in that case, use mwFree_() to force free() of it.
**      Also, this may be a double-free, but the previous free was
**      too long ago, causing MEMWATCH to 'forget' it.
**      Detect: delete or free() of the offending pointer.
**      Action: The delete or free() is cancelled, execution continues.
**  NULL free:
**      It's unclear to me whether or not freeing of NULL pointers
**      is legal in ANSI C, therefore a warning is written to the log file,
**      but the error counter remains the same. This is legal using C++,
**      so the warning does not appear with delete.
**      Detect: When you free(NULL).
**      Action: The free() is cancelled.
**  Failed:
**      A request to allocate memory failed. If the allocation is
**      small, this may be due to memory depletion, but is more likely
**      to be memory fragmentation problems. The amount of memory
**      allocated so far is displayed also.
**      Detect: When you new, malloc(), realloc() or calloc() memory.
**      Action: NULL is returned.
**  Realloc:
**      A request to re-allocate a memory buffer failed for reasons
**      other than out-of-memory. The specific reason is shown.
**      Detect: When you realloc()
**      Action: realloc() is cancelled, NULL is returned
**  Wild pointer:
**      A no-mans-land buffer has been written into. MEMWATCH can
**      allocate and distribute chunks of memory solely for the
**      purpose of trying to catch random writes into memory.
**      Detect: Always on CHECK(), but can be detected in several places.
**      Action: The error is logged, and if an ARI handler is installed,
**              it is executed, otherwise, execution continues.
**  Unfreed:
**      A memory buffer you allocated has not been freed.
**      You are informed where it was allocated, and whether any
**      over or underflow has occured. MemWatch also displays up to
**      16 bytes of the data, as much as it can, in hex and text.
**      Detect: When MemWatch terminates.
**      Action: The buffer is freed.
**
**
************************************************************************
*/

#ifndef __MEMWATCH_H
#define __MEMWATCH_H

/* Make sure that malloc(), realloc(), calloc() and free() are declared. */
/*lint -save -e537 */
#include <stdlib.h>
#include <string.h>

#include "os.h"
#include "drv_config.h"

#if (CONFIG_MEMORY_WATCH==1)
#define MEMWATCH
#define MW_STDIO
#endif //#if (CONFIG_MEMORY_WATCH==1)

/*lint -restore */

#ifdef __cplusplus
extern "C" {
#endif


/*
** Constants used
**  All MEMWATCH constants start with the prefix MW_, followed by
**  a short mnemonic which indicates where the constant is used,
**  followed by a descriptive text about it.
*/

#define MW_STAT_GLOBAL  0       /* only global statistics collected */
#define MW_STAT_MODULE  1       /* collect statistics on a module basis */
#define MW_STAT_LINE    2       /* collect statistics on a line basis */
#define MW_STAT_DEFAULT 0       /* the default statistics setting */

/*
** Exported variables
**  In case you have to remove the 'const' keyword because your compiler
**  doesn't support it, be aware that changing the values may cause
**  unpredictable behaviour.
**  - mwCounter contains the current action count. You can use this to
**      place breakpoints using a debugger, if you want.
*/
#ifndef __MEMWATCH_C
extern const unsigned long mwCounter;
#endif

void mwStatReport( void );
void mwReport( void );

/*
** Setup functions
**  These functions control the operation of MEMWATCH's protective features.
**  - mwStatistics() sets the behaviour of the statistics collector. See
**      the MW_STAT_xxx defines for more information. Default MW_STAT_DEFAULT.
*/
void        mwStatistics( int level );


/*
** User I/O functions
**  - mwSetOutFunc() allows you to give the adress of a function
**      where all user output will go. (exeption: see mwSetAriFunc)
**      Specifying NULL will direct output to the log file.
*/
void  mwSetOutFunc( void (*func)(int) );


/*
** Allocation/deallocation functions
**  These functions are the ones actually to perform allocations
**  when running MEMWATCH, for both C and C++ calls.
**  - mwMalloc() debugging allocator
**  - mwRealloc() debugging re-allocator
**  - mwCalloc() debugging allocator, fills with zeros
**  - mwFree() debugging free. Can only free memory which has
**      been allocated by MEMWATCH.
*/
void* mwMalloc( size_t, const char*, int );
void* mwRealloc( void *, size_t, const char*, int );
void* mwCalloc( size_t, size_t, const char*, int );
void  mwFree( void*, const char*, int );
char* mwStrdup( const char *, const char*, int );

/*
** Enable/disable precompiler block
**  This block of defines and if(n)defs make sure that references
**  to MEMWATCH is completely removed from the code if the MEMWATCH
**  manifest constant is not defined.
*/
#ifndef __MEMWATCH_C
#ifdef MEMWATCH

/* some compilers use a define and not a function */
/* for strdup(). */
#ifdef strdup
#undef strdup
#endif

#define OUT_FUNC(f)		mwSetOutFunc(f)
#define STATICS(n)		mwStatistics(n)
#define REPORT()		mwReport()
#define malloc(n)       mwMalloc(n,__FILE__,__LINE__)
#define strdup(p)       mwStrdup(p,__FILE__,__LINE__)
#define realloc(p,n)    mwRealloc(p,n,__FILE__,__LINE__)
#define calloc(n,m)     mwCalloc(n,m,__FILE__,__LINE__)
#define free(p)         mwFree(p,__FILE__,__LINE__)

#define OS_MemAlloc(h, s, w)	os_malloc(h, s, w, __FILE__, __LINE__)
#define OS_MemFree(h, p)		os_free(h, p, __FILE__, __LINE__)

#else /* MEMWATCH */

#define OUT_FUNC(f)
#define STATICS(n)
#define REPORT()
/*lint -restore */

#endif /* MEMWATCH */
#endif /* !__MEMWATCH_C */

#ifdef __cplusplus
    }
#endif


#endif /* __MEMWATCH_H */

/* EOF MEMWATCH.H */
