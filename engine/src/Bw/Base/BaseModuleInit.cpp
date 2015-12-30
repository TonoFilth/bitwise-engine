#include <cstdlib>
#include "Bw/Base/ModuleInit.h"
#include "Bw/Base/Memory/ModuleInit.h"
#include "Bw/Base/Multithreading/ModuleInit.h"
#include "Bw/Base/Detail/PointerHashTable.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void init_base()
{
    init_memory_system();
	init_multithreading_system();

	// Call the following functions once all static and
	// global variables are deleted
	// IMPORTANT: These functions are called in REVERSE order
	// of registration
	atexit(shutdown_memory_system);
	atexit(shutdown_multithreading_system);

	PointerHashTable<int, 7U> hashTable(-1);

	Allocator* alloc = &(memory::page_allocator());

	uintptr_t k0 = uintptr_t(alloc);
	uintptr_t k1 = k0 + 0xFF;
	uintptr_t k2 = k1 + 0xFF;
	uintptr_t k3 = k2 + 0xFF;
	uintptr_t k4 = k3 + 0xFF;
	uintptr_t k5 = k4 + 0xFF;
	uintptr_t k6 = k5 + 0xFF;
	uintptr_t k7 = k6 + 0xFF;

	hashTable.put(k0, 5);
	hashTable.put(k1, 10);
	hashTable.put(k2, 15);
	hashTable.put(k3, 20);
	hashTable.put(k4, 25);
	hashTable.put(k5, 30);
	hashTable.put(k6, 35);
	hashTable.put(k7, 40);

	int v0 = hashTable.get(k0);
	int v1 = hashTable.get(k1);
	int v2 = hashTable.get(k2);
}

// -----------------------------------------------------------------------------

void shutdown_base()
{
}

}	// namespace bw