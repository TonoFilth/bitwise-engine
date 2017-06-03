#pragma once

#include "bitwise/core/export.h"

namespace bw
{
namespace console
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
BW_API void write       (const char* text);
BW_API void write_line  (const char* text);
BW_API void write_format(const char* format, ...);

}   // namespace console
}   // namespace bw