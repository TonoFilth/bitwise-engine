#pragma once

#include "bitwise/core/macros.h"
#include "bitwise/core/cstring.h"

namespace bw
{
////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description.
////////////////////////////////////////////////////////////////////////////////
namespace assert
{
    ////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    typedef void (*AssertHandler)(const char* expression, const char* message, const char* file, int line, bool callstack, bool halt);

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API AssertHandler get_handler();

	////////////////////////////////////////////////////////////////////////////
	/// \brief Brief description.
	/// \todo Write brief description.
	////////////////////////////////////////////////////////////////////////////
    BW_API AssertHandler set_handler(AssertHandler handler);

#if !defined(BW_DOXYPRESS) && defined(BW_DEBUG)
    class RecursionScopeMarker
	{
	public: 
		RecursionScopeMarker(unsigned& counter) : m_counter(counter) { ++m_counter; }
		~RecursionScopeMarker() { --m_counter; }
	private:
		unsigned& m_counter;
	};
#endif

}   // namespace assert
}   // namespace bw

// -----------------------------------------------------------------------------
//  Macros
// -----------------------------------------------------------------------------
#if defined(BW_DEBUG)
#   define BW_ASSERT(expr, fmt, ...)                                              \
{                                                                                 \
    if (!(expr))                                                                  \
    {                                                                             \
        char buffer[4096];                                                        \
        bw::cstring::format(buffer, 4096, fmt, __VA_ARGS__);                      \
        bw::assert::get_handler()(#expr, buffer, __FILE__, __LINE__, true, true); \
    }                                                                             \
}
#   define BW_CALL_ONCE()                                                \
{                                                                        \
    static bool __callOnce = false;                                      \
    BW_ASSERT(!__callOnce, "Enclosing block was called more than once"); \
    __callOnce = true;                                                   \
}
#
#   define BW_NO_RECURSION()                                                       \
    static unsigned __recursionCounter = 0;                                        \
    BW_ASSERT(__recursionCounter == 0, "Enclosing block was entered recursively"); \
    const bw::assert::RecursionScopeMarker __scopeMarker(__recursionCounter)
#
#   define BW_NO_ENTRY()      { BW_ASSERT(false, "Unexpected code path reached");  }
#   define BW_UNIMPLEMENTED() { BW_ASSERT(false, "Unimplemented function called"); }
#
#else
#   define BW_ASSERT(expr, fmt, ...)
#   define BW_CALL_ONCE()
#   define BW_NO_RECURSION()
#   define BW_NO_ENTRY()
#   define BW_UNIMPLEMENTED()
#endif

////////////////////////////////////////////////////////////////////////////////
/// \namespace bw::assert
/// \ingroup core
///
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////