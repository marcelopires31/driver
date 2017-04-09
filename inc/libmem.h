//**************************************************************************
//      Copyright (c) 2004, Cheertek Inc . All rights reserved.
//      J500, all right reserved.
//
//      Product : CheerDVD Firmware
//      Date    : 2006.3.8
//      Author  : Cheertek (J500 Ism Hong)
//      Purpose : replacement of malloc() free() etc. in Standard Library
//      Sources : lib_mem.c / lib_mem.h
//***************************************************************************

// Modification use :
//**************************************************************************
//      Update
//      Date    : 2006.3.8
//      Name    : Cheertek (J500 Ism Hong)
//      Description     :
//
//                      Item                    Source
//      -----------------------------------------------------------

#ifndef __LIBMEM_H__
#define __LIBMEM_H__

//**************************************************************************
//      Functions:
//              1.LIBMEM_Set_Memory_Region(void *buffer, bufsize len)
//                      Setting memory region for memory allocator
//              2.LIBMEM_Malloc(bufsize size)
//                      Just like malloc() in stdlib
//              3.LIBMEM_Free(void *buf)
//                      Just like free() in stdlib
//              4.LIBMEM_Memory_State(bufsize *curalloc, bufsize *totfree, bufsize *maxfree, long *nget, long *nrel)
//                      The amount      of  space  currently  allocated  is  stored  into  the
//                      variable  pointed  to by <curalloc>.  The total free space (sum of
//                      all free blocks in the pool) is stored into the  variable  pointed
//                      to      by  <totfree>, and the size of the largest single block in the
//                      free space      pool  is  stored  into  the  variable  pointed  to  by
//                      <maxfree>.       The  variables  pointed  to  by <nget> and <nrel> are
//                      filled, respectively, with      the  number  of  successful  (non-NULL
//              return) LIBMEM_Malloc() calls and the number of LIBMEM_Free() calls.
//****************************************************************************
#define LIBMEM_Set_Memory_Region(x,y) bpool(x,y)
#define LIBMEM_Malloc(x) bget(x)
#define LIBMEM_Free(x) brel(x)
#define LIBMEM_Memory_State(a,b,c,d,e) bstats(a,b,c,d,e)

typedef long bufsize;
void    bpool(void *buffer, bufsize len);
void    *bget(bufsize size);
void     *bgetz(bufsize size);
void    *bgetr(void *buffer, bufsize newsize);
void    brel(void *buf);
void    bectl(int (*compact)(bufsize sizereq, int sequence),
       void *(*acquire)(bufsize size),
       void (*release)(void *buf), bufsize pool_incr);
void    bstats(bufsize *curalloc, bufsize *totfree, bufsize *maxfree,
       long *nget, long *nrel);
void    bstatse(bufsize *pool_incr, long *npool, long *npget,
                       long *nprel, long *ndget, long *ndrel);
void    bufdump(void *buf);
void    bpoold(void *pool, int dumpalloc, int dumpfree);
int     bpoolv(void *pool);

#endif  //__LIB_MEM_H
