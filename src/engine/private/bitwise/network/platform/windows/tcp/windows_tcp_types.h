#if !defined(BW_DOXYPRESS)
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <mswsock.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>

#include "bitwise/network/tcp/tcp_server_config.h"

namespace bw
{

// -----------------------------------------------------------------------------
//  Constants
// -----------------------------------------------------------------------------
const size_t kIoBufferSize     = 8192;
const size_t kMaxWorkerThreads = 16;

// -----------------------------------------------------------------------------
//  IoOperation
// -----------------------------------------------------------------------------
struct IoOperation
{
	enum Enum
	{
		eAccept,
		eRead,
		eWrite
	};
};

// -----------------------------------------------------------------------------
//  IoContext
// -----------------------------------------------------------------------------
struct IoContext
{
	WSAOVERLAPPED overlapped;
	char buffer[kIoBufferSize];
	WSABUF wsabuf;
	size_t totalBytes;
	size_t sentBytes;
	IoOperation::Enum ioOperation;
	SOCKET socketAccept;

	IoContext* next;
};

// -----------------------------------------------------------------------------
//  SocketContext
// -----------------------------------------------------------------------------
struct SocketContext
{
	SOCKET        socket;
	LPFN_ACCEPTEX acceptEx;

	IoContext* ioContext;

	SocketContext* next;
	SocketContext* prev;
};

// -----------------------------------------------------------------------------
//  TcpServerData
// -----------------------------------------------------------------------------
struct TcpServerData
{
	HANDLE           iocp;
	SOCKET           listenSocket;
	CRITICAL_SECTION criticalSection;

	SocketContext* contextList;
	SocketContext* contextListenSocket;

	HANDLE   serverThread;
	HANDLE   threadHandles[kMaxWorkerThreads];
	size_t   nbThreads;
	WSAEVENT cleanupEvent[1];

	TcpServerConfig config;

	bool stopServer;
	bool restartServer;
	bool running;
};

}	// namespace bw

#endif