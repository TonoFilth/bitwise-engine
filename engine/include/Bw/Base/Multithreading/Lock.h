#ifndef BW_BASE_LOCK_H
#define BW_BASE_LOCK_H

#include "Bw/Base/Common/Module.h"
#include "Bw/Base/Multithreading/ModuleTypes.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	Lock
////////////////////////////////////////////////////////////////////////////////
class BW_BASE_API Lock
{
public:
	explicit Lock(Mutex& mutex);
	~Lock();

private:
	Lock(const Lock& toCopy)            = delete;
	Lock& operator=(const Lock& toCopy) = delete;

private:
	Mutex* m_mutex;
};

}	// namespace bw

#endif	// BW_BASE_LOCK_H