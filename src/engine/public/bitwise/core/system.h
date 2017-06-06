#pragma once

#include <cstddef>
#include "bitwise/core/export.h"

namespace bw
{
namespace system
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
BW_API int    exec(const char* program, const char* args);
BW_API size_t page_size();

}   // namespace system
}   // namespace bw