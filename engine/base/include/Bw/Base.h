#ifndef BW_BASE_MODULE_H
#define BW_BASE_MODULE_H

#include "Bw/Base/Assert.h"
#include "Bw/Base/CharArray.h"
#include "Bw/Base/Console.h"
#include "Bw/Base/Constants.h"
#include "Bw/Base/Export.h"
#include "Bw/Base/Integer.h"
#include "Bw/Base/Macros.h"
#include "Bw/Base/PImpl.h"
#include "Bw/Base/Pointer.h"
#include "Bw/Base/Real.h"
#include "Bw/Base/System.h"
#include "Bw/Base/Types.h"
#include "Bw/Base/Version.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//	Public functions
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void InitializeBaseModule();
BW_BASE_API void ShutdownBaseModule();

}	// namespace Internal
}	// namespace bw

#endif	// BW_BASE_MODULE_H