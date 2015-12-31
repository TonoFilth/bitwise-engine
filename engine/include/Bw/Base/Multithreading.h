#ifndef BW_BASE_MULTITHREADING_MODULE_H
#define BW_BASE_MULTITHREADING_MODULE_H

#include "Bw/Base/Multithreading/Lock.h"
#include "Bw/Base/Multithreading/Mutex.h"
#include "Bw/Base/Multithreading/Thread.h"
#include "Bw/Base/Multithreading/ThreadLocal.h"
#include "Bw/Base/Multithreading/Types.h"

namespace bw
{
namespace Internal
{

////////////////////////////////////////////////////////////////////////////////
//  Initialization & shutdown
////////////////////////////////////////////////////////////////////////////////
BW_BASE_API void InitMultithreading();
BW_BASE_API void QuitMultithreading();

}	// namespace Internal
}	// namespace bw

#endif	// BW_BASE_MULTITHREADING_MODULE_H