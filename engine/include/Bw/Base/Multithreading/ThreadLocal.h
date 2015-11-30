#ifndef BW_BASE_THREAD_LOCAL_H
#define BW_BASE_THREAD_LOCAL_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Multithreading/ModuleTypes.h"

namespace bw
{
namespace thread_local
{
	BW_BASE_API ThreadLocal* create(void* value = nullptr);
	BW_BASE_API void destroy(ThreadLocal& tls);

	BW_BASE_API void  set_value(ThreadLocal& tls, void* value);
	BW_BASE_API void* get_value(ThreadLocal& tls);

}	// namespace thread_local
}	// namespace bw

#endif	// BW_BASE_THREAD_LOCAL_H