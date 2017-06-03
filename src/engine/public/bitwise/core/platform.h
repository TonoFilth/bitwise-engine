#pragma once

#include "bitwise/core/export.h"
#include <cstddef>

namespace bw
{
namespace platform
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
BW_API int    exec(const char* program, const char* args);
BW_API size_t page_size();

}   // namespace platform
}   // namespace bw