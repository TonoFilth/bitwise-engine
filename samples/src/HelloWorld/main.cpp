#include <iostream>
#include <cstdio>
#include <csignal>
#include <Bw/Bw.h>

using namespace std;

void MySignalHandler(bw::Signal::Enum signal)
{
	cout << "Signal: " << bw::Signal::ToString(signal) << endl;
}

int main(int argc, char** argv)
{
	cout << "HelloWorld Sample" << endl;

	bw::Init();

	for (int i = 0; i < bw::Signal::eCOUNT; ++i)
		bw::SetSignalHandler((bw::Signal::Enum) i, MySignalHandler);
	

	raise(SIGABRT);
	raise(SIGFPE);
	raise(SIGILL);
	raise(SIGINT);
	raise(SIGSEGV);
	raise(SIGTERM);

    bw::Shutdown();

	return 0;
}