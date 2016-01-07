#include <Bw/Bw.h>
#include "Test.h"

struct MyData
{
	MyData(int d) :
		data(d)
	{
	}

	~MyData()
	{
		data = 0;
	}

	int data;
};

// Static initialization
MyData* g_MyData = BW_NEW(MyData, 100);

int main(int argc, char** argv)
{
	bw::Initialize();

	bw::Console::WriteFormat("g_MyData -> %d\n", g_MyData->data);

	BW_DELETE(g_MyData);

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

	bw::Shutdown();

	g_MyData = BW_NEW(MyData, 50);

	bw::Console::WriteFormat("g_MyData -> %d\n", g_MyData->data);

	return 0;
}