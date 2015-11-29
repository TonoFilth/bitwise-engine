#ifndef BW_BASE_COMMON_MODULE_TYPES_H
#define BW_BASE_COMMON_MODULE_TYPES_H

#include <cstddef>
#include <cstdint>
#include "Bw/Base/Common/Export.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  8 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned char u8_t;
typedef signed   char i8_t;

////////////////////////////////////////////////////////////////////////////////
//  16 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned short u16_t;
typedef signed   short i16_t;

////////////////////////////////////////////////////////////////////////////////
//  32 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned int u32_t;
typedef signed   int i32_t;

////////////////////////////////////////////////////////////////////////////////
//  64 bits integer types
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
	typedef unsigned __int64 u64_t;
	typedef signed   __int64 i64_t;
#else
	typedef unsigned long long u64_t;
	typedef signed   long long i64_t;
#endif

////////////////////////////////////////////////////////////////////////////////
//  Single and double precision real types
////////////////////////////////////////////////////////////////////////////////
typedef float  f32_t;
typedef double f64_t;

#if !defined(BW_DOUBLE_AS_REAL)
    typedef f32_t real_t;
#else
    typedef f64_t real_t;
#endif

////////////////////////////////////////////////////////////////////////////////
//  Pointer types
////////////////////////////////////////////////////////////////////////////////
typedef uintptr_t uptr_t;
typedef intptr_t  iptr_t;

////////////////////////////////////////////////////////////////////////////////
//  Atomic type size checks
////////////////////////////////////////////////////////////////////////////////
static_assert(sizeof(u8_t)  == 1, "AtomicTypes.h: 'u8_t' size must be 1 byte");
static_assert(sizeof(u16_t) == 2, "AtomicTypes.h: 'u16_t' size must be 2 bytes");
static_assert(sizeof(u32_t) == 4, "AtomicTypes.h: 'u32_t' size must be 4 bytes");
static_assert(sizeof(u64_t) == 8, "AtomicTypes.h: 'u64_t' size must be 8 bytes");

static_assert(sizeof(i8_t)  == 1, "AtomicTypes.h: 'i8_t' size must be 1 byte");
static_assert(sizeof(i16_t) == 2, "AtomicTypes.h: 'i16_t' size must be 2 bytes");
static_assert(sizeof(i32_t) == 4, "AtomicTypes.h: 'i32_t' size must be 4 bytes");
static_assert(sizeof(i64_t) == 8, "AtomicTypes.h: 'i64_t' size must be 8 bytes");

static_assert(sizeof(f32_t) == 4, "AtomicTypes.h: 'f32_t' size must be 4 bytes");
static_assert(sizeof(f64_t) == 8, "AtomicTypes.h: 'f64_t' size must be 8 bytes");

#if !defined(BW_DOUBLE_AS_REAL)
    static_assert(sizeof(real_t) == sizeof(f32_t), "AtomicTypes.h: 'real_t' size must be 8 bytes");
#else
    static_assert(sizeof(real_t) == sizeof(f64_t), "AtomicTypes.h: 'real_t' size must be 4 bytes");
#endif

static_assert(sizeof(uptr_t) == sizeof(void*), "AtomicTypes.h: 'uptr_t' size must be equal to sizeof(void*)");
static_assert(sizeof(iptr_t) == sizeof(void*), "AtomicTypes.h: 'iptr_t' size must be equal to sizeof(void*)");

////////////////////////////////////////////////////////////////////////////////
//  AssertHandler
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API AssertHandler
{
public:
	virtual ~AssertHandler() = default;
	virtual void operator()(const char* exp, const char* file, int line) = 0;
};

}	// namespace bw

#endif	// BW_BASE_COMMON_MODULE_TYPES_H