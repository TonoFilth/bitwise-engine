#ifndef BW_BASE_MUTEX_H
#define BW_BASE_MUTEX_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Multithreading/ModuleTypes.h"

namespace bw
{
namespace mutex
{
	BW_BASE_API Mutex* create();
	BW_BASE_API void   destroy(Mutex* mutex);

	BW_BASE_API void lock(Mutex* mutex);
	BW_BASE_API void unlock(Mutex* mutex);

}	// namespace mutex
}	// namespace bw

#endif	// BW_BASE_MUTEX_H