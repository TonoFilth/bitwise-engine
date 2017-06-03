#pragma once

#include "bitwise/core/macros.h"

#if defined(BW_EXPORT)
#   define BW_API BW_API_EXPORT
#else
#   define BW_API BW_API_IMPORT
#endif