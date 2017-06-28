#include <bitwise.h>
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <strsafe.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

static const char* const kHost = "127.0.0.1";
static const char* const kPort = "10666";
static const size_t kBufferSize = 4096;

SOCKET g_socket;

static SOCKET create_socket()
{
	int callResult = 0;
	struct addrinfo hints = {0};
	struct addrinfo* addrServer = NULL;

	hints.ai_flags = 0;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	callResult = ::getaddrinfo(kHost, kPort, &hints, &addrServer);

	if (callResult != 0)
	{
		bw::console::write_format("getaddrinfo() failed: %d\n", callResult);
		return INVALID_SOCKET;
	}

	if (addrServer == NULL)
	{
		bw::console::write_line("getaddrinfo() failed to resolve/convert the interface");
		return INVALID_SOCKET;
	}

	SOCKET socket = ::socket(addrServer->ai_family, addrServer->ai_socktype, addrServer->ai_protocol);

	if (socket == INVALID_SOCKET)
	{
		::freeaddrinfo(addrServer);
		bw::console::write_format("socket() failed: %d\n", ::WSAGetLastError());
		return INVALID_SOCKET;
	}

	callResult = ::connect(socket, addrServer->ai_addr, (int) addrServer->ai_addrlen);

	if (callResult == SOCKET_ERROR)
	{
		::freeaddrinfo(addrServer);
		bw::console::write_format("connect() failed: %d\n", ::WSAGetLastError());
		return INVALID_SOCKET;
	}

	bw::console::write_line("Connected");
	::freeaddrinfo(addrServer);

	return socket;
}

static bool send_buffer(char* outBuffer)
{
	size_t totalSend = 0;
	char* buff = outBuffer;

	while (totalSend < kBufferSize)
	{
		int send = ::send(g_socket, buff, kBufferSize - totalSend, 0);

		if (send == SOCKET_ERROR)
		{
			bw::console::write_format("send() failed: %d\n", ::WSAGetLastError());
			return false;
		}
		else if (send == 0)
		{
			bw::console::write_line("Connection closed");
			return false;
		}
		else
		{
			totalSend += send;
			buff += send;
		}
	}

	return true;
}

static bool receive_buffer(char* inBuffer)
{
	size_t totalRecv = 0;
	char* buff = inBuffer;

	while (totalRecv < kBufferSize)
	{
		int recv = ::recv(g_socket, buff, kBufferSize - totalRecv, 0);

		if (recv == SOCKET_ERROR)
		{
			bw::console::write_format("recv() failed: %d\n", ::WSAGetLastError());
			return false;
		}
		else if (recv == 0)
		{
			bw::console::write_line("Connection closed");
			return false;
		}
		else
		{
			totalRecv += recv;
			buff += recv;
		}
	}

	return true;
}

int main(int argc, char** argv)
{
	bw::initialize(argc, argv);

	bw::TcpServerConfig config;
	bw::TcpServer server(config);

	WSAData wsaData;
	int callResult = 0;
	
	callResult = ::WSAStartup(MAKEWORD(2,2), &wsaData);

	if (callResult != 0)
	{
		bw::console::write_format("WSAStartup() failed: %d\n", callResult);
		return 1;
	}

	g_socket = create_socket();

	if (g_socket == INVALID_SOCKET)
	{
		::WSACleanup();
		return 1;
	}

	char inBuffer[kBufferSize];
	char outBuffer[kBufferSize];

	bw::cstring::copy(outBuffer, kBufferSize, "Hello World");

	if (send_buffer(outBuffer) && receive_buffer(inBuffer))
	{
		bw::console::write_line(inBuffer);
	}

	::WSACleanup();
	bw::shutdown();

	return 0;
}

//#include "bitwise.h"
//
//#ifndef WIN32_LEAN_AND_MEAN
//#define WIN32_LEAN_AND_MEAN
//#endif
//
//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//
//#pragma comment(lib, "Ws2_32.lib")
//
//int main(int argc, char** argv)
//{
//    bw::initialize(argc, argv);
//
//	WSADATA wsaData;
//
//	int wsaResult = ::WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//	if (wsaResult != 0)
//	{
//		bw::console::write_format("WSAStartup() failed: %d\n", wsaResult);
//		return 1;
//	}
//
//	struct addrinfo* result = NULL;
//	struct addrinfo* ptr    = NULL;
//	struct addrinfo  hints;
//
//	ZeroMemory(&hints, sizeof(hints));
//
//	hints.ai_family   = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = IPPROTO_TCP;
//
//	wsaResult = ::getaddrinfo("127.0.0.1", "10666", &hints, &result);
//
//	if (wsaResult != 0)
//	{
//		bw::console::write_format("getaddrinfo() failed: %d\n", wsaResult);
//		::WSACleanup();
//		return 1;
//	}
//
//	SOCKET socket = INVALID_SOCKET;
//
//	ptr = result;
//	socket = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
//
//	if (socket == INVALID_SOCKET)
//	{
//		bw::console::write_format("socket() failed: %d\n", ::WSAGetLastError());
//		::freeaddrinfo(result);
//		::WSACleanup();
//		return 1;
//	}
//
//	wsaResult = ::connect(socket, ptr->ai_addr, (int) ptr->ai_addrlen);
//
//	if (wsaResult == SOCKET_ERROR)
//	{
//		::closesocket(socket);
//		socket = INVALID_SOCKET;
//
//		wsaResult = ::connect(socket, ptr->ai_next->ai_addr, (int) ptr->ai_next->ai_addrlen);
//
//		if (wsaResult == SOCKET_ERROR)
//		{
//			bw::console::write_line("Unable to connect to server");
//
//			::closesocket(socket);
//			::freeaddrinfo(result);
//			::WSACleanup();
//			return 1;
//		}
//	}
//
//	::freeaddrinfo(result);
//
//	// Do stuff ...
//	char recvBuffer[512];
//	char sendBuffer[512];
//
//	bw::cstring::copy(sendBuffer, 512, "Hello World!");
//
//	int sendResult = 0;
//	int recvResult = 0;
//
//	sendResult = ::send(socket, sendBuffer, static_cast<int>(bw::cstring::length(sendBuffer)), 0);
//
//	if (sendResult == SOCKET_ERROR)
//	{
//		bw::console::write_format("send() failed: %d\n", ::WSAGetLastError());
//		::closesocket(socket);
//		::WSACleanup();
//		return 1;
//	}
//
//	bw::console::write_format("%d bytes sent\n", sendResult);
//
//	wsaResult = ::shutdown(socket, SD_SEND);
//
//	if (wsaResult == SOCKET_ERROR)
//	{
//		bw::console::write_format("shutdown() failed: %d\n", ::WSAGetLastError());
//		::closesocket(socket);
//		::WSACleanup();
//		return 1;
//	}
//
//	do
//	{
//		recvResult = ::recv(socket, recvBuffer, 512, 0);
//
//		if (recvResult > 0)
//		{
//			recvBuffer[recvResult] = '\0';
//
//			bw::console::write_format("%d bytes received\n", recvResult);
//			bw::console::write_format("recvBuffer: \"%s\"\n", recvBuffer);
//		}
//		else if (recvResult == 0)
//		{
//			bw::console::write_line("Connection closed");
//		}
//		else
//		{
//			bw::console::write_format("recv() failed: %d\n", ::WSAGetLastError());
//		}
//	}
//	while (recvResult > 0);
//
//	::closesocket(socket);
//	::WSACleanup();
//
//    bw::shutdown();
//
//    return 0;
//}