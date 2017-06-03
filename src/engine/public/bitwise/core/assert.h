#pragma once

#include "bitwise/core/assert_handler.h"
#include "bitwise/core/export.h"

namespace bw
{
namespace assert
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
BW_API AssertHandler& get_handler();
BW_API AssertHandler& set_handler(AssertHandler* handler);

}   // namespace assert
}   // namespace bw

// -----------------------------------------------------------------------------
//  Macros
// -----------------------------------------------------------------------------
#if defined(BW_DEBUG)
    #define BW_ASSERT(exp, ...) do { if (!(exp)) bw::assert::get_handler()(#exp, __FILE__, __LINE__); } while(0)
#else
    #define BW_ASSERT(expr, ...) do {} while(0)
#endif