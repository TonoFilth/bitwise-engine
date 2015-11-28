#include <cstdio>
#include "Bw/Base/Memory/MemoryUtils.h"
#include "Bw/Base/Memory/PointerArithmetic.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void memory::print_range(const void* start, size_t offsetEnd)
{
	const U8* end = (const U8*) start;
	end += offsetEnd;

	memory::print_range(start, (const void*) end);
}

// -----------------------------------------------------------------------------

void memory::print_range(const void* start, const void* end)
{
	const U8* s = (const U8*) start;
	const U8* e = (const U8*) end;

	BW_ASSERT(e > s);

	size_t count = 0;

	printf("%p - ", s);

	while (s < e)
	{
		printf("%.2X ", *s);
		
		++count;
		++s;

		if (count > 0 && count % 4 == 0)
			printf(" | ");

		if (count % 8 == 0)
		{
			if (s < e)
				printf("\n%p - ", s);
			else
				printf("\n");
		}
	}
}

}	// namespace bw