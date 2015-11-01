#include <iostream>
#include <Bw/Bw.h>

using namespace std;
using namespace bw;

int main(int argc, char** argv)
{
	cout << "Foundation Sample" << endl;
	cout << "Compiler: " << BW_COMPILER_NAME << endl;
	getchar();

	bw::Init();

	BW_ASSERT(1 != 1, "Hey");

	bw::Shutdown();

	return 0;
}