#include "Bw/Base/Multithreading/Lock.h"
#include "Bw/Base/Multithreading/Mutex.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Class std functions
////////////////////////////////////////////////////////////////////////////////
Lock::Lock(Mutex& mutex) :
	m_mutex(&mutex)
{
	mutex::lock(m_mutex);
}

// -----------------------------------------------------------------------------

Lock::~Lock()
{
	mutex::unlock(m_mutex);
}

}	// namespace bw