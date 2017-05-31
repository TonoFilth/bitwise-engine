#ifndef BW_MEMORY_POOL_ALLOCATOR_H
#define BW_MEMORY_POOL_ALLOCATOR_H

#include "Bw/Base/Assert.h"
#include "Bw/Base/Integer.h"
#include "Bw/Base/System.h"
#include "Bw/Memory/Allocator.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  PoolAllocator
////////////////////////////////////////////////////////////////////////////////
template <class T>
class PoolAllocator : public Allocator
{
public:
	PoolAllocator(size_t poolSize = System::GetPageSize() / sizeof(T));
	virtual ~PoolAllocator();

	void* allocate(size_t size, size_t alignment) override;
	void  deallocate(void* data) override;

	template <class ...Args>
	T* next(Args&& ...args);
	void collect(T* obj);

	size_t allocatedSize() const override;
	size_t allocatedSize(void* data) const override;

	static const size_t OFFSET_MAX = Integer::kUint16Max;

private:
	void*  m_pool;
	void*  m_free;
	size_t m_poolSize;
	size_t m_used;

private:
	// Private structures and types
	typedef uint16_t offset_t;
	
	struct FreeNode
	{
		offset_t _next;
	};

private:
	void createPool();
};

#include "Bw/Memory/PoolAllocator.inl"

}	// namespace bw

#endif	// BW_MEMORY_POOL_ALLOCATOR_H