#ifndef BW_BASE_MULTITHREADING_TYPES_H
#define BW_BASE_MULTITHREADING_TYPES_H

#include "Bw/Base/Config.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Multithreading types
////////////////////////////////////////////////////////////////////////////////
struct Mutex;
class  Lock;
struct Thread;

typedef uint64_t ThreadLocalIndex;

}	// namespace bw

#endif	// BW_BASE_MULTITHREADING_TYPES_H