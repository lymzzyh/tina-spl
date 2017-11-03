/*
********************************************
*
* File    : types.h
* By      : dianguai14
* Version : v0.1
* Date    : 2013-06-25
* Descript:
********************************************
*/
#ifndef __TYPE_H
#define __TYPE_H

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef signed char         __s8;
typedef unsigned char       __u8;
typedef signed short        __s16;
typedef unsigned short      __u16;
typedef signed int          __s32;
typedef unsigned int        __u32;
typedef signed long long    __s64;
typedef unsigned long long  __u64;

typedef signed char         s8;
typedef unsigned char       u8;
typedef signed short        s16;
typedef unsigned short      u16;
typedef signed int          s32;
typedef unsigned int        u32;
typedef signed long long    s64;
typedef unsigned long long  u64;

typedef signed char         int8;
typedef unsigned char       uint8;
typedef signed short        int16;
typedef unsigned short      uint16;
typedef signed int          int32;
typedef unsigned int        uint32;
typedef signed long long    int64;
typedef unsigned long long  uint64;

typedef volatile char           __vs8;
typedef volatile unsigned int   __vu32;
typedef volatile unsigned short __vu16;
typedef volatile unsigned char  __vu8;
typedef volatile int            __vs32;
typedef volatile short          __vs16;
typedef volatile char           __vs8;

typedef unsigned int size_t;
typedef unsigned int ptrdiff_t;

#ifndef NULL
#define NULL 0
#endif


typedef signed char				s8_t;
typedef unsigned char			u8_t;

typedef signed short			s16_t;
typedef unsigned short			u16_t;

typedef signed int				s32_t;
typedef unsigned int			u32_t;

typedef signed long long		s64_t;
typedef unsigned long long		u64_t;

typedef signed int				bool_t;

typedef signed int				register_t;
typedef unsigned int			irq_flags_t;

typedef unsigned int			virtual_addr_t;
typedef unsigned int			virtual_size_t;
typedef unsigned int			physical_addr_t;
typedef unsigned int			physical_size_t;

typedef struct {
	volatile long counter;
} atomic_t;

typedef struct {
	volatile long lock;
} spinlock_t;

#endif
