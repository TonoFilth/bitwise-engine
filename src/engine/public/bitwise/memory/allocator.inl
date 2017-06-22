template <class T, class ...Args>
T* bw::Allocator::allocateObject(Args&& ...args)
{
    return new (allocate(sizeof(T), nullptr, alignof(T))) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <class T, class ...Args>
T* bw::Allocator::allocateObject(size_t* allocatedSize, Args&& ...args)
{
    return new (allocate(sizeof(T), allocatedSize, alignof(T))) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <class T>
void bw::Allocator::deallocateObject(T* memory)
{
    if (memory != nullptr)
    {
        memory->~T();
        deallocate(memory);
    }
}