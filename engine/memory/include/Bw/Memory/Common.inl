////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void* bw::Memory::AlignForward(void* ptr, size_t alignment)
{
    uintptr_t p = uintptr_t(ptr);
    size_t mod = p % alignment;

    if (mod)
        p += (alignment - mod);

    return (void*) p;
}

// -----------------------------------------------------------------------------

void* bw::Memory::AlignForward(void* ptr, size_t alignment, uint8_t& usedAlignmentBytes)
{
    uintptr_t p = uintptr_t(ptr);
    usedAlignmentBytes = 0;

    size_t mod = p % alignment;

    if (mod)
    {
        usedAlignmentBytes = static_cast<uint8_t>(alignment - mod);
        p += usedAlignmentBytes;
    }

    return (void*) p;
}

// -----------------------------------------------------------------------------

void* bw::Memory::PointerAdd(void* ptr, size_t bytes)
{
    return (void*) ((uintptr_t) ptr + bytes);
}

// -----------------------------------------------------------------------------

void* bw::Memory::PointerSub(void* ptr, size_t bytes)
{
    return (void*) ((uintptr_t) ptr - bytes);
}

// -----------------------------------------------------------------------------

const void* bw::Memory::PointerAdd(const void* ptr, size_t bytes)
{
    return (const void*) ((const uintptr_t) ptr + bytes);
}

// -----------------------------------------------------------------------------

const void* bw::Memory::PointerSub(const void* ptr, size_t bytes)
{
    return (const void*) ((const uintptr_t) ptr - bytes);
}

// -----------------------------------------------------------------------------

bool bw::Memory::IsAligned(const void* addr, size_t alignment)
{
	return ((uintptr_t(addr) & (alignment - 1)) == 0);

}