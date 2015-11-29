////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void* align_forward(void* ptr, size_t alignment)
{
    uptr_t p = uptr_t(ptr);
    size_t mod = p % alignment;

    if (mod)
        p += (alignment - mod);

    return (void*) p;
}

// -----------------------------------------------------------------------------

void* align_forward(void* ptr, size_t alignment, u8_t& usedAlignmentBytes)
{
    uptr_t p = uptr_t(ptr);
    usedAlignmentBytes = 0;

    size_t mod = p % alignment;

    if (mod)
    {
        usedAlignmentBytes = static_cast<u8_t>(alignment - mod);
        p += usedAlignmentBytes;
    }

    return (void*) p;
}

// -----------------------------------------------------------------------------

void* pointer_add(void* ptr, size_t bytes)
{
    return (void*) ((uptr_t) ptr + bytes);
}

// -----------------------------------------------------------------------------

void* pointer_sub(void* ptr, size_t bytes)
{
    return (void*) ((uptr_t) ptr - bytes);
}

// -----------------------------------------------------------------------------

const void* pointer_add(const void* ptr, size_t bytes)
{
    return (const void*) ((const uptr_t) ptr + bytes);
}

// -----------------------------------------------------------------------------

const void* pointer_sub(const void* ptr, size_t bytes)
{
    return (const void*) ((const uptr_t) ptr - bytes);
}