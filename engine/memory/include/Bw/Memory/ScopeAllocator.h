#ifndef BW_MEMORY_SCOPE_ALLOCATOR_H
#define BW_MEMORY_SCOPE_ALLOCATOR_H

#include "Bw/Memory/Allocator.h"
#include "Bw/Memory/Common.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	ScopeAllocator
////////////////////////////////////////////////////////////////////////////////
template <unsigned N>
class ScopeAllocator : public Allocator
{
public:
	ScopeAllocator();
	virtual ~ScopeAllocator() = default;

	void* allocate(size_t size, size_t alignment) override;
	void  deallocate(void* data) override;

	size_t allocatedSize() const override;
	size_t allocatedSize(void* data) const override;

private:
	char   m_memory[N];
	size_t m_size;
	size_t m_capacity;
	void*  m_top;
};

#include "Bw/Memory/ScopeAllocator.inl"

////////////////////////////////////////////////////////////////////////////////
//	Default typedefs
////////////////////////////////////////////////////////////////////////////////
typedef ScopeAllocator<32>   ScopeAllocator32;
typedef ScopeAllocator<64>   ScopeAllocator64;
typedef ScopeAllocator<128>  ScopeAllocator128;
typedef ScopeAllocator<256>  ScopeAllocator256;
typedef ScopeAllocator<512>  ScopeAllocator512;
typedef ScopeAllocator<1024> ScopeAllocator1024;
typedef ScopeAllocator<2048> ScopeAllocator2048;
typedef ScopeAllocator<4096> ScopeAllocator4096;

}	// namespace bw

#endif	// BW_MEMORY_SCOPE_ALLOCATOR_H