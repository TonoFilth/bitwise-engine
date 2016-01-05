#include <Bw/Base.h>
#include "Test.h"

int main(int argc, char** argv)
{
	bw::Console::WriteFormat("Int8Max:   %u\n", bw::Integer::kInt8Max);
	bw::Console::WriteFormat("Int16Max:  %u\n", bw::Integer::kInt16Max);
	bw::Console::WriteFormat("Int32Max:  %u\n", bw::Integer::kInt32Max);
	bw::Console::WriteFormat("Int64Max:  %u\n", bw::Integer::kInt64Max);
	bw::Console::WriteFormat("Uint64Max: %u\n", bw::Integer::kUint64Max);
	bw::Console::WriteFormat("SizeMax:   %u\n", bw::Integer::kSizeMax);

	auto print = [] (const char* str)
	{
		bw::Console::WriteLine(str);
	};

	print("Hello");
	print("World");

	return 0;
}