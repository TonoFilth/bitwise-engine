#include <iostream>
#include <Bw/Bw.h>

using namespace std;

int main(int argc, char** argv)
{
	cout << "HelloWorld Sample" << endl;
	getchar();

	bw::Init();
	bw::Shutdown();

	return 0;
}