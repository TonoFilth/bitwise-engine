#ifndef BW_BASE_MODULE_H
#define BW_BASE_MODULE_H

#include "Bw/Base/Common.h"
#include "Bw/Base/Config.h"
#include "Bw/Base/Memory.h"
#include "Bw/Base/Multithreading.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//  Library initialization and shutdown
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void InitBase();
BW_BASE_API void QuitBase();

}	// namespace Internal
}	// namespace bw

#endif	// BW_BASE_MODULE_H