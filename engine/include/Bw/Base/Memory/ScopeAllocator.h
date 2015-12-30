#ifndef BW_BASE_SCOPE_ALLOCATOR_H
#define BW_BASE_SCOPE_ALLOCATOR_H

#include "Bw/Base/Memory/Allocator.h"
#include "Bw/Base/Memory/PointerArithmetic.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//	ScopeAllocator
////////////////////////////////////////////////////////////////////////////////
template <unsigned N>
class BW_BASE_API ScopeAllocator : public Allocator
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

#include "Bw/Base/Detail/ScopeAllocator.inl"

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

#endif	// BW_BASE_SCOPE_ALLOCATOR_H