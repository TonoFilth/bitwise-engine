template <class T, class ...Args>
T* bw::Allocator::allocateObject(Args&& ...args)
{
    return new (allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <class T>
void bw::Allocator::deallocateObject(T* ptr)
{
    if (ptr)
    {
        ptr->~T();
        deallocate(ptr);
    }
}