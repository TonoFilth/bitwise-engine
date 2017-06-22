#pragma once

#include "bitwise/core/macros.h"
#include "bitwise/memory/allocator.h"

namespace bw
{
////////////////////////////////////////////////////////////////////////////////
/// \brief Brief description.
/// \todo Write brief description.
////////////////////////////////////////////////////////////////////////////////
class BW_API HeapAllocator : public Allocator
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    HeapAllocator();

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    virtual ~HeapAllocator() override;

	////////////////////////////////////////////////////////////////////////////
    /// \brief Brief description.
    /// \todo Write brief description.
    ////////////////////////////////////////////////////////////////////////////
    virtual void* allocate(size_t size, size_t* allocatedSize = nullptr, size_t alignment = kDefaultAlignment) override;

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
    size_t m_allocatedSize;
};

}	// namespace bw

////////////////////////////////////////////////////////////////////////////////
/// \class bw::HeapAllocator
/// \ingroup memory
///
/// \details Detailed description.
/// \todo Write detailed description.
////////////////////////////////////////////////////////////////////////////////