#ifndef BW_BASE_ATOMIC_TYPES_H
#define BW_BASE_ATOMIC_TYPES_H

#include <type_traits>

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
// 8 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned char U8;
typedef signed   char I8;

////////////////////////////////////////////////////////////////////////////////
// 16 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned short U16;
typedef signed   short I16;

////////////////////////////////////////////////////////////////////////////////
// 32 bits integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned int U32;
typedef signed   int I32;

////////////////////////////////////////////////////////////////////////////////
// 64 bits integer types
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
	typedef unsigned __int64 U64;
	typedef signed   __int64 I64;
#else
	typedef unsigned long long U64;
	typedef signed   long long I64;
#endif

////////////////////////////////////////////////////////////////////////////////
// Single and double precision real types
////////////////////////////////////////////////////////////////////////////////
typedef float  F32;
typedef double F64;
typedef F32    Real;

////////////////////////////////////////////////////////////////////////////////
// Atomic type size checks
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

static_assert(sizeof(Real) == sizeof(F32) || sizeof(Real) == sizeof(F64), "AtomicTypes.h: Invalid 'Real' type size");

}	// namespace bw

#endif	// BW_BASE_ATOMIC_TYPES_H