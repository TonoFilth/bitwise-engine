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
typedef unsigned char U8;
typedef signed   char I8;

////////////////////////////////////////////////////////////////////////////////
//  16 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned short U16;
typedef signed   short I16;

////////////////////////////////////////////////////////////////////////////////
//  32 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned int U32;
typedef signed   int I32;

////////////////////////////////////////////////////////////////////////////////
//  64 bits integer types
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
	typedef unsigned __int64 U64;
	typedef signed   __int64 I64;
#else
	typedef unsigned long long U64;
	typedef signed   long long I64;
#endif

////////////////////////////////////////////////////////////////////////////////
//  Single and double precision real types
////////////////////////////////////////////////////////////////////////////////
typedef float  F32;
typedef double F64;

#if !defined(BW_DOUBLE_AS_REAL)
    typedef F32 Real;
#else
    typedef F64 Real;
#endif

////////////////////////////////////////////////////////////////////////////////
//  Pointer types
////////////////////////////////////////////////////////////////////////////////
typedef uintptr_t UPTR;
typedef intptr_t  IPTR;

////////////////////////////////////////////////////////////////////////////////
//  Atomic type size checks
////////////////////////////////////////////////////////////////////////////////
static_assert(sizeof(U8)  == 1, "AtomicTypes.h: 'U8' size must be 1 byte");
static_assert(sizeof(U16) == 2, "AtomicTypes.h: 'U16' size must be 2 bytes");
static_assert(sizeof(U32) == 4, "AtomicTypes.h: 'U32' size must be 4 bytes");
static_assert(sizeof(U64) == 8, "AtomicTypes.h: 'U64' size must be 8 bytes");

static_assert(sizeof(I8)  == 1, "AtomicTypes.h: 'I8' size must be 1 byte");
static_assert(sizeof(I16) == 2, "AtomicTypes.h: 'I16' size must be 2 bytes");
static_assert(sizeof(I32) == 4, "AtomicTypes.h: 'I32' size must be 4 bytes");
static_assert(sizeof(I64) == 8, "AtomicTypes.h: 'I64' size must be 8 bytes");

static_assert(sizeof(F32) == 4, "AtomicTypes.h: 'F32' size must be 4 bytes");
static_assert(sizeof(F64) == 8, "AtomicTypes.h: 'F64' size must be 8 bytes");

#if !defined(BW_DOUBLE_AS_REAL)
    static_assert(sizeof(Real) == sizeof(F32), "AtomicTypes.h: 'Real' size must be 8 bytes");
#else
    static_assert(sizeof(Real) == sizeof(F64), "AtomicTypes.h: 'Real' size must be 4 bytes");
#endif

static_assert(sizeof(UPTR) == sizeof(void*), "AtomicTypes.h: 'UPTR' size must be equal to sizeof(void*)");
static_assert(sizeof(IPTR) == sizeof(void*), "AtomicTypes.h: 'IPTR' size must be equal to sizeof(void*)");

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