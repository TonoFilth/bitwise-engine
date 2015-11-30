#ifndef BW_BASE_MULTITHREADING_MODULE_TYPES_H
#define BW_BASE_MULTITHREADING_MODULE_TYPES_H

namespace bw
{

struct Mutex;
class  Lock;
struct Thread;
struct ThreadLocal;

typedef void (*ThreadFunction) (void* data);

}	// namespace bw

#endif	// BW_BASE_MULTITHREADING_MODULE_TYPES_H