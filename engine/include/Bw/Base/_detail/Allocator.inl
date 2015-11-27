////////////////////////////////////////////////////////////////////////////////
//  Template function definitions
////////////////////////////////////////////////////////////////////////////////
template <class T, class ...Args>
T* Allocator::makeNew(Args&& ...args)
{
    return new (allocate(sizeof(T), alignof(T))) T(std::forward<Args>(args)...);
}

// -----------------------------------------------------------------------------

template <class T>
void Allocator::makeDelete(T* ptr)
{
    if (ptr)
    {
        ptr->~T();
        deallocate(ptr);
    }
}