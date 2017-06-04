#pragma once

#include <cstddef>
#include "bitwise/core/export.h"
#include "bitwise/core/fwd.h"

namespace bw
{
namespace platform
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
BW_API int         exec(const char* program, const char* args);
BW_API size_t      page_size();
BW_API StackFrame* backtrace(int skip = 0);
BW_API void        print_backtrace(StackFrame* frame);

}   // namespace platform
}   // namespace bw