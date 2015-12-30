////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void* align_forward(void* ptr, size_t alignment)
{
    uintptr_t p = uintptr_t(ptr);
    size_t mod = p % alignment;

    if (mod)
        p += (alignment - mod);

    return (void*) p;
}

// -----------------------------------------------------------------------------

void* align_forward(void* ptr, size_t alignment, uint8_t& usedAlignmentBytes)
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

void* pointer_add(void* ptr, size_t bytes)
{
    return (void*) ((uintptr_t) ptr + bytes);
}

// -----------------------------------------------------------------------------

void* pointer_sub(void* ptr, size_t bytes)
{
    return (void*) ((uintptr_t) ptr - bytes);
}

// -----------------------------------------------------------------------------

const void* pointer_add(const void* ptr, size_t bytes)
{
    return (const void*) ((const uintptr_t) ptr + bytes);
}

// -----------------------------------------------------------------------------

const void* pointer_sub(const void* ptr, size_t bytes)
{
    return (const void*) ((const uintptr_t) ptr - bytes);
}