#include <Bw/Bw.h>

int main(int argc, char** argv)
{
	bw::Init();

	bw::PoolAllocator<int> intPool;
	bool is = bw::IsMultipleOf(4, 16);

	bw::Quit();

	return 0;
}