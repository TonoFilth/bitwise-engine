#ifndef BW_BASE_MODULE_H
#define BW_BASE_MODULE_H

#include "Bw/Base/Assert.h"
#include "Bw/Base/AtomicTypes.h"
#include "Bw/Base/Endianness.h"
#include "Bw/Base/Export.h"
#include "Bw/Base/Preprocessor.h"
#include "Bw/Base/StackTrace.h"
#include "Bw/Base/Version.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void InitBase();
BW_BASE_API void ShutdownBase();

}	// namespace bw

#endif	// BW_BASE_MODULE_H