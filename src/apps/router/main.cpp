#include <bitwise.h>
#include <Windows.h>

int main(int argc, char** argv)
{
	bw::initialize(argc, argv);

	bw::TcpServerConfig config;
	config.maxThreads = 16;
	config.portNumber = 10666;

	bw::TcpServer server(config);
	server.run();

	while (server.isRunning())
	{
		::Sleep(5000);
	};

	bw::shutdown();

	return 0;
}