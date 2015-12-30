////////////////////////////////////////////////////////////////////////////////
//  Inline function definitions
////////////////////////////////////////////////////////////////////////////////
template <class T>
Thread* create(T functor, void* data)
{
	using namespace internal;

	auto& allocator = internal::multithreading_allocator();
	ThreadEntryPoint* entryPoint = allocator.allocateObject<ThreadEntryPointFunctor<T>>(functor, data);
	return internal::create_thread(*entryPoint);
}

// -----------------------------------------------------------------------------

template <class T>
Thread* create(void (T::*function)(void*), void* data, T* object)
{
	using namespace internal;

	auto& allocator = internal::multithreading_allocator();
	ThreadEntryPoint* entryPoint = allocator.allocateObject<ThreadEntryPointMember<T>>(function, data, object);
	return internal::create_thread(*entryPoint);
}