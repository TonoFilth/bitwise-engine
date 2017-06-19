#pragma once

#include "bitwise/memory/allocator.h"

namespace bw
{
////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description.
////////////////////////////////////////////////////////////////////////////////
class BW_API TraceAllocator : public Allocator
{
    static const size_t kMaxAllocatorName = 32;

public:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    TraceAllocator(Allocator& allocator, const char* allocatorName);

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    virtual ~TraceAllocator() override;

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
    char m_name[kMaxAllocatorName];
    Allocator* m_allocator;
    size_t m_allocationCount;
};

}	// namespace bw

////////////////////////////////////////////////////////////////////////////////
/// \class bw::TraceAllocator
/// \ingroup memory
///
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////