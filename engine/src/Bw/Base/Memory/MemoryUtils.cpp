#include <cstdio>
#include "Bw/Base/Common/Assert.h"
#include "Bw/Base/Memory/Utils.h"

namespace bw
{

////////////////////////////////////////////////////////////////////////////////
//  Public functions
////////////////////////////////////////////////////////////////////////////////
void MemoryUtils::PrintRange(const void* start, size_t offsetEnd)
{
	const uint8_t* end = (const uint8_t*) start;
	end += offsetEnd;

	MemoryUtils::PrintRange(start, (const void*) end);
}

// -----------------------------------------------------------------------------

void MemoryUtils::PrintRange(const void* start, const void* end)
{
	const uint8_t* s = (const uint8_t*) start;
	const uint8_t* e = (const uint8_t*) end;

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