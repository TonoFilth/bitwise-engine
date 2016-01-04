#ifndef BW_BASE_COMMON_TYPES_H
#define BW_BASE_COMMON_TYPES_H

#include "Bw/Base/Macros.h"
#include "Bw/Base/Export.h"

////////////////////////////////////////////////////////////////////////////////
//  8 bit integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned char uint8_t;
typedef signed   char int8_t;

////////////////////////////////////////////////////////////////////////////////
//  16 bit integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned short uint16_t;
typedef signed   short int16_t;

////////////////////////////////////////////////////////////////////////////////
//  32 bit integer types
////////////////////////////////////////////////////////////////////////////////
typedef unsigned int uint32_t;
typedef signed   int int32_t;

////////////////////////////////////////////////////////////////////////////////
//  64 bit integer types
////////////////////////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
	typedef unsigned __int64 uint64_t;
	typedef signed   __int64 int64_t;
#else
	typedef unsigned long long uint64_t;
	typedef signed   long long int64_t;
#endif

////////////////////////////////////////////////////////////////////////////////
//  Pointer types
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_64BIT)

	typedef uint64_t uintptr_t;
	typedef int64_t  intptr_t;

#elif defined(BW_32BIT)
	
	typedef uint32_t uintptr_t;
	typedef int32_t  intptr_t;

#else
	#error "Bw: This architecture is not suported"
#endif

typedef intptr_t  ptrdiff_t;
typedef uintptr_t size_t;

////////////////////////////////////////////////////////////////////////////////
//  Single and double precision real types
////////////////////////////////////////////////////////////////////////////////
typedef float  f32_t;
typedef double f64_t;

// Make sure real_t is not defined by another library in the global scope
#if defined(real_t)
#	error "Bw: real_t already defined in the global scope"
#endif

#if !defined(BW_DOUBLE_PRECISION)
	typedef f32_t real_t;
#else
	typedef f64_t real_t;
#endif

////////////////////////////////////////////////////////////////////////////////
//  Atomic type size checks
////////////////////////////////////////////////////////////////////////////////
static_assert(sizeof(uint8_t)  == 1, "AtomicTypes.h: 'uint8_t' size must be 1 byte");
static_assert(sizeof(uint16_t) == 2, "AtomicTypes.h: 'uint16_t' size must be 2 bytes");
static_assert(sizeof(uint32_t) == 4, "AtomicTypes.h: 'uint32_t' size must be 4 bytes");
static_assert(sizeof(uint64_t) == 8, "AtomicTypes.h: 'uint64_t' size must be 8 bytes");

static_assert(sizeof(int8_t)  == 1, "AtomicTypes.h: 'int8_t' size must be 1 byte");
static_assert(sizeof(int16_t) == 2, "AtomicTypes.h: 'int16_t' size must be 2 bytes");
static_assert(sizeof(int32_t) == 4, "AtomicTypes.h: 'int32_t' size must be 4 bytes");
static_assert(sizeof(int64_t) == 8, "AtomicTypes.h: 'int64_t' size must be 8 bytes");

static_assert(sizeof(f32_t) == 4, "AtomicTypes.h: 'f32_t' size must be 4 bytes");
static_assert(sizeof(f64_t) == 8, "AtomicTypes.h: 'f64_t' size must be 8 bytes");

#if defined(BW_DOUBLE_PRECISION)
	static_assert(sizeof(real_t) == sizeof(f64_t), "AtomicTypes.h: 'real_t' size must be 8 bytes");
#else
	static_assert(sizeof(real_t) == sizeof(f32_t), "AtomicTypes.h: 'real_t' size must be 4 bytes");
#endif

static_assert(sizeof(uintptr_t) == sizeof(void*),    "AtomicTypes.h: 'uintptr_t' size must be equal to sizeof(void*)");
static_assert(sizeof(intptr_t)  == sizeof(void*),    "AtomicTypes.h: 'intptr_t' size must be equal to sizeof(void*)");
static_assert(sizeof(ptrdiff_t) == sizeof(intptr_t), "AtomicTypes.h: 'ptrdiff_t' size must be equal to sizeof(intptr_t)");

namespace bw
{

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

#endif	// BW_BASE_COMMON_TYPES_H