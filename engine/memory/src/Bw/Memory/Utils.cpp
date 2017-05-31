#include "Bw/Memory/Utils.h"
#include "Bw/Base/Assert.h"
#include "Bw/Base/Console.h"

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

	Console::WriteFormat("%p - ", s);

	while (s < e)
	{
		Console::WriteFormat("%.2X ", *s);
		
		++count;
		++s;

		if (count > 0 && count % 4 == 0)
			Console::WriteFormat(" | ");

		if (count % 8 == 0)
		{
			if (s < e)
				Console::WriteFormat("\n%p - ", s);
			else
				Console::WriteFormat("\n");
		}
	}
}

}	// namespace bw