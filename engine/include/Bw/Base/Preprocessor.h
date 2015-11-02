#ifndef BW_BASE_PREPROCESSOR_H
#define BW_BASE_PREPROCESSOR_H

////////////////////////////////////////////////////////////////////////////////
// Debug macro
////////////////////////////////////////////////////////////////////////////////
#if !defined(NDEBUG)
#	define BW_DEBUG
#endif

////////////////////////////////////////////////////////////////////////////////
// Endianess (Reference: http://www.libsdl.org/)
////////////////////////////////////////////////////////////////////////////////
#define BW_SYSTEM_LE 1234
#define BW_SYSTEM_BE 4321

#if defined(__i386__)  || defined(__ia64__)                   || \
    defined(_M_IX86)   || defined(_M_IA64) || defined(_M_X64) || \
   (defined(__alpha__) || defined(__alpha))                   || \
    defined(__arm__)   || defined(ARM)                        || \
   (defined(__mips__)  && defined(__MIPSEL__))                || \
    defined(__SYMBIAN32__)                                    || \
    defined(__x86_64__)                                       || \
    defined(__LITTLE_ENDIAN__)
#   define BW_SYSTEM_BYTEORDER BW_SYSTEM_LE
#else
#   define BW_SYSTEM_BYTEORDER BW_SYSTEM_BE
#endif

////////////////////////////////////////////////////////////////////////////////
// Compiler detection (Reference: http://goo.gl/2EVxN4)
////////////////////////////////////////////////////////////////////////////////
#if defined(__clang__) //                                                  Clang
#   define BW_COMPILER_CLANG
#   if !defined(__GNUG__)
#       define BW_COMPILER_NAME "Clang/LLVM C"
#   else
#       define BW_COMPILER_NAME "Clang/LLVM C++"
#   endif
// -----------------------------------------------------------------------------
#elif defined(__GNUC__) || defined(__GNUG__) //                              GNU
#   define BW_COMPILER_GNU
#   if !defined(__GNUG__)
#       define BW_COMPILER_NAME "GNU gcc"
#   else
#       define BW_COMPILER_NAME "GNU g++"
#   endif
// -----------------------------------------------------------------------------
#elif defined(_MSC_VER) //                                             Microsoft
#   define BW_COMPILER_VC
#	if defined(__cplusplus)
#		define BW_COMPILER_NAME "Microsoft Visual C++"
#	else
#		error "Microsoft Visual C compiler not supported"
#	endif
// -----------------------------------------------------------------------------
#else //                                                                 Unknown
#	error "Compiler couldn't be detected'"
#endif

////////////////////////////////////////////////////////////////////////////////
// System detection (Reference: http://goo.gl/8omej3)
////////////////////////////////////////////////////////////////////////////////
#if defined(__APPLE__) && defined(__MACH__) //                            Mac OS
#   include <TargetConditionals.h>
#   if TARGET_OS_MAC == 1
#       define BW_SYSTEM_MACOS
#	else
#		error "This Apple system is not supported by Bitwise Engine"
#   endif
// -----------------------------------------------------------------------------
#elif defined(_WIN32) //                                                 Windows
#   define BW_SYSTEM_WINDOWS
#   if !defined(NOMINMAX)
#		define NOMINMAX
#	endif
#	if !defined(WIN32_LEAN_AND_MEAN)
#		define WIN32_LEAN_AND_MEAN
#	endif 
// -----------------------------------------------------------------------------
#elif defined(__linux__) //                                                Linux
#   define BW_SYSTEM_LINUX
// -----------------------------------------------------------------------------
#elif defined(__unix__) //                                               FreeBSD
#   include <sys/param.h>
#   if defined(BSD) && defined(__FreeBSD__)
#       define BW_SYSTEM_FREE_BSD
#	else
#		error "This Unix system is not supported by Bitwise Engine"
#   endif
#else
// -----------------------------------------------------------------------------
#	error "This operating system is not supported by Bitwise Engine"
#endif

////////////////////////////////////////////////////////////////////////////////
// Api visibility
////////////////////////////////////////////////////////////////////////////////
#if !defined(BW_STATIC_LIB)
#	if defined(BW_SYSTEM_WINDOWS)
#   	define BW_API_EXPORT __declspec(dllexport)
#       define BW_API_IMPORT __declspec(dllimport)
#
#		if defined(_MSC_VER)
#			pragma warning(disable: 4251)
#		endif
#   else
#		if __GNUC__ >= 4
#			define BW_API_EXPORT __attribute__ ((__visibility__ ("default")))
#			define BW_API_IMPORT __attribute__ ((__visibility__ ("default")))
#		else
#			define BW_API_EXPORT
#			define BW_API_IMPORT
#		endif
#   endif
#else
#	define BW_API_EXPORT
#	define BW_API_IMPORT
#endif

////////////////////////////////////////////////////////////////////////////////
// Inline macros
////////////////////////////////////////////////////////////////////////////////
#if defined(BW_SYSTEM_WINDOWS) //		                                  Inline
#	define BW_INLINE inline
#	pragma inline_depth( 255 )
#else
#	define BW_INLINE inline
#endif
// -----------------------------------------------------------------------------
#if defined(BW_COMPILER_VC) //		                                Force inline
#	define BW_FORCE_INLINE __forceinline
#elif defined(BW_COMPILER_GNU)
#	define BW_FORCE_INLINE inline __attribute__((always_inline))
#else
#	define BW_FORCE_INLINE inline
#endif
// -----------------------------------------------------------------------------
#if defined(BW_SYSTEM_WINDOWS) //                                      No inline
#	define BW_NOINLINE __declspec(noinline)
#elif defined(BW_COMPILER_GNU)
#	define BW_NOINLINE __attribute__ ((noinline))
#else
#	define BW_NOINLINE
#endif

////////////////////////////////////////////////////////////////////////////////
// Token stringification
////////////////////////////////////////////////////////////////////////////////
#define BW_XSTR(str) BW_STR(str)
#define BW_STR(str) #str

////////////////////////////////////////////////////////////////////////////////
// This macro creates a version string
////////////////////////////////////////////////////////////////////////////////
#define BW_GET_VERSION_STRING(prefix, major, minor, patch, postfix) prefix BW_XSTR(major) "." BW_XSTR(minor) "." BW_XSTR(patch) postfix

#endif	// BW_BASE_PREPROCESSOR_H