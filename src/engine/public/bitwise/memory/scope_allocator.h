#pragma once

#include "bitwise/core/pointer.h"
#include "bitwise/core/assert.h"
#include "bitwise/memory/allocator.h"

namespace bw
{
////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description.
////////////////////////////////////////////////////////////////////////////////
template <unsigned N>
class ScopeAllocator : public Allocator
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    ScopeAllocator();

	////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    virtual void* allocate(size_t size, size_t alignment = kDefaultAlignment) override;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    virtual void deallocate(void* memory) override;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    virtual size_t allocatedSize() const override;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    virtual size_t allocatedSize(void* memory) const override;

private:
    char   m_memory[N];
	size_t m_size;
	size_t m_capacity;
	void*  m_top;
};

}	// namespace bw

#include "bitwise/memory/scope_allocator.inl"

namespace bw
{
    // -------------------------------------------------------------------------
    //  Default template instantiations
    // -------------------------------------------------------------------------
    typedef ScopeAllocator<32>   ScopeAllocator32;
    typedef ScopeAllocator<64>   ScopeAllocator64;
    typedef ScopeAllocator<128>  ScopeAllocator128;
    typedef ScopeAllocator<256>  ScopeAllocator256;
    typedef ScopeAllocator<512>  ScopeAllocator512;
    typedef ScopeAllocator<1024> ScopeAllocator1024;
    typedef ScopeAllocator<2048> ScopeAllocator2048;
    typedef ScopeAllocator<4096> ScopeAllocator4096;

}   // namespace bw

////////////////////////////////////////////////////////////////////////////////
/// \class bw::ScopeAllocator
/// \ingroup memory
///
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////