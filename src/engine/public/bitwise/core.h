#pragma once

#include "bitwise/core/macros.h"
#include "bitwise/core/export.h"
#include "bitwise/core/assert.h"
#include "bitwise/core/cstring.h"
#include "bitwise/core/console.h"
#include "bitwise/core/platform.h"
#include "bitwise/core/backtrace.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Public functions
// -----------------------------------------------------------------------------
BW_API void initialize();
BW_API void shutdown();

}   // namespace bw