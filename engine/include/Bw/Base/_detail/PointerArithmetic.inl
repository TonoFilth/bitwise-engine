////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
void* align_forward(void* ptr, size_t alignment)
{
    UPTR p = UPTR(ptr);
    size_t mod = p % alignment;

    if (mod)
        p += (alignment - mod);

    return (void*) p;
}

// -----------------------------------------------------------------------------

void* align_forward(void* ptr, size_t alignment, U8& usedAlignmentBytes)
{
    UPTR p = UPTR(ptr);
    usedAlignmentBytes = 0;

    size_t mod = p % alignment;

    if (mod)
    {
        usedAlignmentBytes = static_cast<U8>(alignment - mod);
        p += usedAlignmentBytes;
    }

    return (void*) p;
}

// -----------------------------------------------------------------------------

void* pointer_add(void* ptr, size_t bytes)
{
    return (void*) ((UPTR) ptr + bytes);
}

// -----------------------------------------------------------------------------

void* pointer_sub(void* ptr, size_t bytes)
{
    return (void*) ((UPTR) ptr - bytes);
}

// -----------------------------------------------------------------------------

const void* pointer_add(const void* ptr, size_t bytes)
{
    return (const void*) ((const UPTR) ptr + bytes);
}

// -----------------------------------------------------------------------------

const void* pointer_sub(const void* ptr, size_t bytes)
{
    return (const void*) ((const UPTR) ptr - bytes);
}