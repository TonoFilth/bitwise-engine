////////////////////////////////////////////////////////////////////////////////
//  Template function definitions
////////////////////////////////////////////////////////////////////////////////
template <class T, class ...Args>
T* Allocator::allocateObject(Args&& ...args)
{
    return new (allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <class T>
void Allocator::deallocateObject(T* ptr)
{
    if (ptr)
    {
        ptr->~T();
        deallocate(ptr);
    }
}