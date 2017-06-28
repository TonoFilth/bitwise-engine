#include <new>			// placement new
#include <type_traits>	// static_assert

#include "bitwise/log.h"
#include "bitwise/core/integer.h"
#include "bitwise/memory/allocator.h"
#include "bitwise/memory/global_allocators.h"
#include "bitwise/network/tcp/tcp_server.h"
#include "bitwise/network/tcp/tcp_server_config.h"
#include "bitwise/network/platform/windows/tcp/windows_tcp_types.h"

// -----------------------------------------------------------------------------
//  Private variables
// -----------------------------------------------------------------------------
static bw::TcpServerData* g_serverData = nullptr;

// -----------------------------------------------------------------------------
//  Private functions
// -----------------------------------------------------------------------------
static bool initialize_server(bw::TcpServerData& data)
{
	if (g_serverData != nullptr)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "Can't initialize TcpServer because another instance is running");
		return false;
	}

	::InitializeCriticalSection(&data.criticalSection);

	data.iocp                = INVALID_HANDLE_VALUE;
	data.listenSocket        = INVALID_SOCKET;
	data.contextList         = nullptr;
	data.contextListenSocket = nullptr;
	data.stopServer          = false;
	data.restartServer       = true;
	data.running             = false;

	// Initialize all thread handles to an invalid value
	for (int i = 0; i < bw::kMaxWorkerThreads; ++i)
	{
		data.threadHandles[i] = INVALID_HANDLE_VALUE;
	}

	SYSTEM_INFO systemInfo;
	DWORD nbThreads = 0;

	::GetSystemInfo(&systemInfo);
	nbThreads = systemInfo.dwNumberOfProcessors * 2;

	if (nbThreads > bw::kMaxWorkerThreads || nbThreads > data.config.maxThreads)
	{
		data.nbThreads = (data.config.maxThreads < bw::kMaxWorkerThreads ? data.config.maxThreads : bw::kMaxWorkerThreads);
	}
	else
	{
		data.nbThreads = nbThreads;
	}

	data.cleanupEvent[0] = ::WSACreateEvent();
	
	// Make sure that the cleanup event has been created
	if (data.cleanupEvent[0] == WSA_INVALID_EVENT)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "WSACreateEvent() failed (errcode=%d)", ::WSAGetLastError());
		return false;
	}

	// WinSock should be initialized in bw::network::initialize()
	WSADATA wsaData;
	int callResult = ::WSAStartup(MAKEWORD(2,2), &wsaData);
	if (callResult != 0)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "WSAStartup() failed: %d", callResult);
		return false;
	}

	g_serverData = &data;
	return true;
}

// -----------------------------------------------------------------------------

static void shutdown_server(bw::TcpServerData& data)
{
	::DeleteCriticalSection(&data.criticalSection);

	if (data.cleanupEvent[0] != WSA_INVALID_EVENT)
	{
		if (!::WSACloseEvent(data.cleanupEvent[0]))
		{
			BW_LOG_ERROR(bw::LogChannel::eNET, "WSACloseEvent() failed (%d)", ::WSAGetLastError());
		}

		data.cleanupEvent[0] = WSA_INVALID_EVENT;
	}

	::CloseHandle(data.serverThread);
	data.serverThread = INVALID_HANDLE_VALUE;

	// WinSock cleanup should be called in bw::network::shutdown()
	::WSACleanup();

	g_serverData = nullptr;
}

// -----------------------------------------------------------------------------

static bw::SocketContext* create_socket_context(SOCKET socket, bw::IoOperation::Enum ioOperation, bw::TcpServerData& data)
{
	bw::SocketContext* context = nullptr;

	::EnterCriticalSection(&data.criticalSection);

	bw::Allocator& allocator = bw::memory::generic_allocator();
	context = allocator.allocateObject<bw::SocketContext>();

	if (context != nullptr)
	{
		context->ioContext = allocator.allocateObject<bw::IoContext>();

		if (context->ioContext != nullptr)
		{
			context->socket = socket;
			context->next = nullptr;
			context->prev = nullptr;

			context->ioContext->overlapped.Internal = 0;
			context->ioContext->overlapped.InternalHigh = 0;
			context->ioContext->overlapped.Offset = 0;
			context->ioContext->overlapped.OffsetHigh = 0;
			context->ioContext->overlapped.hEvent = nullptr;
			context->ioContext->ioOperation = ioOperation;
			context->ioContext->next = nullptr;
			context->ioContext->totalBytes = 0;
			context->ioContext->sentBytes = 0;
			context->ioContext->wsabuf.buf = context->ioContext->buffer;
			context->ioContext->wsabuf.len = bw::kIoBufferSize;
			context->ioContext->socketAccept = INVALID_SOCKET;

			ZeroMemory(context->ioContext->wsabuf.buf, context->ioContext->wsabuf.len);
		}
		else
		{
			allocator.deallocateObject(context);
			BW_LOG_ERROR(bw::LogChannel::eNET, "allocateObject<IoContext>() failed");
		}
	}
	else
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "allocateObject<SocketContext>() failed");
	}

	::LeaveCriticalSection(&data.criticalSection);
	return context;
}

// -----------------------------------------------------------------------------

static void add_socket_context_to_list(bw::SocketContext* context, bw::TcpServerData& data)
{
	bw::SocketContext* tmp = nullptr;

	::EnterCriticalSection(&data.criticalSection);

	if (data.contextList == nullptr)
	{
		context->next    = nullptr;
		context->prev    = nullptr;
		data.contextList = context;
	}
	else
	{
		tmp = data.contextList;

		data.contextList = context;
		context->prev    = tmp;
		context->next    = nullptr;

		tmp->next = context;
	}

	::LeaveCriticalSection(&data.criticalSection);
}

// -----------------------------------------------------------------------------

static void delete_socket_context_from_list(bw::SocketContext* context, bw::TcpServerData& data)
{
	bw::SocketContext* next   = nullptr;
	bw::SocketContext* prev   = nullptr;
	bw::IoContext*     nextIO = nullptr;
	bw::IoContext*     tmpIO  = nullptr;

	::EnterCriticalSection(&data.criticalSection);

	if (context != nullptr)
	{
		next = context->next;
		prev = context->prev;

		if (next == nullptr && prev == nullptr)
		{
			data.contextList = nullptr;
		}
		else if (prev == nullptr && next != nullptr)
		{
			next->prev = nullptr;
			data.contextList = next;
		}
		else if (prev != nullptr && next == nullptr)
		{
			prev->next = nullptr;
		}
		else if (prev != nullptr && next != nullptr)
		{
			prev->next = next;
			next->prev = prev;
		}

		tmpIO = context->ioContext;

		do
		{
			nextIO = nullptr;

			if (tmpIO != nullptr)
			{
				nextIO = tmpIO->next;

				if (data.stopServer)
				{
					while (!HasOverlappedIoCompleted((LPOVERLAPPED) tmpIO))
					{
						::Sleep(0);
					}
				}

				bw::memory::generic_allocator().deallocateObject(tmpIO);
				tmpIO = nullptr;
			}

			tmpIO = nextIO;
		}
		while (nextIO != nullptr);

		bw::memory::generic_allocator().deallocateObject(context);
		context = nullptr;
	}
	else
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "SocketContext is null");
	}

	::LeaveCriticalSection(&data.criticalSection);
}

// -----------------------------------------------------------------------------

static void close_client(bw::SocketContext* context, bool graceful, bw::TcpServerData& data)
{
	::EnterCriticalSection(&data.criticalSection);

	if (context != nullptr)
	{
		BW_LOG_INFO(bw::LogChannel::eNET, "Socket %d connection closing (graceful=%s)", context->socket, (graceful ? "true" : "false"));

		if (!graceful)
		{
			LINGER lingerStruct;

			lingerStruct.l_onoff = 1;
			lingerStruct.l_linger = 0;
			
			::setsockopt(context->socket, SOL_SOCKET, SO_LINGER, (char*) &lingerStruct, sizeof(lingerStruct));
		}

		if (context->ioContext->socketAccept != INVALID_SOCKET)
		{
			::closesocket(context->ioContext->socketAccept);
			context->ioContext->socketAccept = INVALID_SOCKET;
		}

		::closesocket(context->socket);
		context->socket = INVALID_SOCKET;
		delete_socket_context_from_list(context, data);
		context = nullptr;
	}
	else
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "SocketContext is null");
	}

	::LeaveCriticalSection(&data.criticalSection);
}

// -----------------------------------------------------------------------------

static void delete_socket_context_list(bw::TcpServerData& data)
{
	bw::SocketContext* tmp1 = nullptr;
	bw::SocketContext* tmp2 = nullptr;

	::EnterCriticalSection(&data.criticalSection);

	tmp1 = data.contextList;

	while (tmp1 != nullptr)
	{
		tmp2 = tmp1->prev;
		close_client(tmp1, false, data);
		tmp1 = tmp2;
	}

	::LeaveCriticalSection(&data.criticalSection);
}

// -----------------------------------------------------------------------------

static bw::SocketContext* update_completion_port(SOCKET socket, bw::IoOperation::Enum ioOperation, bool addToList, bw::TcpServerData& data)
{
	bw::SocketContext* socketContext = create_socket_context(socket, ioOperation, data);

	if (socketContext == nullptr)
	{
		return nullptr;
	}

	data.iocp = ::CreateIoCompletionPort((HANDLE) socket, data.iocp, (DWORD_PTR) socketContext, 0);

	if (data.iocp == nullptr)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "CreateIoCompletionPort() failed: %d", ::GetLastError());

		if (socketContext->ioContext != nullptr)
		{
			bw::memory::generic_allocator().deallocateObject(socketContext->ioContext);
		}

		bw::memory::generic_allocator().deallocateObject(socketContext);
		return nullptr;
	}

	if (addToList)
	{
		add_socket_context_to_list(socketContext, data);
	}

	BW_LOG_INFO(bw::LogChannel::eNET, "Socket %d added to IOCP", socketContext->socket);

	return socketContext;
}

// -----------------------------------------------------------------------------

static SOCKET create_socket()
{
	SOCKET socket = ::WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_IP, nullptr, 0, WSA_FLAG_OVERLAPPED);

	if (socket == INVALID_SOCKET)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "WSASocket() failed: %d", ::WSAGetLastError());
		return socket;
	}

	int optval = 0;
	int callResult = ::setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char*) &optval, sizeof(optval));

	if (callResult == SOCKET_ERROR)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "setsockopt() failed: %d", ::WSAGetLastError());
		return socket;
	}

	return socket;
}

// -----------------------------------------------------------------------------

static bool create_listen_socket(bw::TcpServerData& data)
{
	int callResult = 0;
	LINGER lingerStruct;

	struct addrinfo hints = {0};
	struct addrinfo* addrlocal = nullptr;

	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_IP;

	char portNumber[6];
	bw::integer::to_string(data.config.portNumber, portNumber, 6);

	callResult = ::getaddrinfo(nullptr, portNumber, &hints, &addrlocal);

	if (callResult != 0)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "getaddrinfo() failed: %d", ::WSAGetLastError());
		return false;
	}

	if (addrlocal == nullptr)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "getaddrinfo() failed to resolve the interface");
		return false;
	}

	data.listenSocket = create_socket();

	if (data.listenSocket == INVALID_SOCKET)
	{
		::freeaddrinfo(addrlocal);
		return false;
	}

	callResult = ::bind(data.listenSocket, addrlocal->ai_addr, (int) addrlocal->ai_addrlen);

	if (callResult == SOCKET_ERROR)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "bind() failed: %d", ::WSAGetLastError());
		::freeaddrinfo(addrlocal);
		return false;
	}

	callResult = ::listen(data.listenSocket, 5);

	if (callResult == SOCKET_ERROR)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "listen() failed: %d", ::WSAGetLastError());
		::freeaddrinfo(addrlocal);
		return false;
	}

	::freeaddrinfo(addrlocal);

	return true;
}

// -----------------------------------------------------------------------------

static bool create_accept_socket(bool updateIocp, bw::TcpServerData& data)
{
	int callResult = 0;
	DWORD recvBytes = 0;
	DWORD bytes = 0;

	GUID acceptExGuid = WSAID_ACCEPTEX;

	if (updateIocp)
	{

		data.contextListenSocket = update_completion_port(data.listenSocket, bw::IoOperation::eAccept, false, data);

		if (data.contextListenSocket == nullptr)
		{
			BW_LOG_ERROR(bw::LogChannel::eNET, "Failed to update listen socket to IOCP");
			return false;
		}

		callResult = ::WSAIoctl
		(
			data.listenSocket,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&acceptExGuid,
			sizeof(acceptExGuid),
			&data.contextListenSocket->acceptEx,
			sizeof(data.contextListenSocket->acceptEx),
			&bytes,
			nullptr,
			nullptr
		);

		if (callResult == SOCKET_ERROR)
		{
			BW_LOG_ERROR(bw::LogChannel::eNET, "Failed to load AcceptEx: %d", ::WSAGetLastError());
			return false;
		}
	}

	data.contextListenSocket->ioContext->socketAccept = create_socket();

	if (data.contextListenSocket->ioContext->socketAccept == INVALID_SOCKET)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "Failed to create new accept socket");
		return false;
	}

	callResult = data.contextListenSocket->acceptEx(data.listenSocket,
		data.contextListenSocket->ioContext->socketAccept,
		(LPVOID) data.contextListenSocket->ioContext->buffer,
		bw::kIoBufferSize - (2 * (sizeof(SOCKADDR_STORAGE) + 16)),
		sizeof(SOCKADDR_STORAGE) + 16,
		sizeof(SOCKADDR_STORAGE) + 16,
		&recvBytes,
		(LPOVERLAPPED) &(data.contextListenSocket->ioContext->overlapped));

	if (callResult == SOCKET_ERROR && ::WSAGetLastError() != WSA_IO_PENDING)
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "AcceptEx() failed: %d", ::WSAGetLastError());
		return false;
	}

	return true;
}

// -----------------------------------------------------------------------------

BOOL WINAPI console_control_handler(DWORD event)
{
	switch (event)
	{
		case CTRL_BREAK_EVENT:
		{
			g_serverData->restartServer = true;
		}
		case CTRL_C_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
		case CTRL_CLOSE_EVENT:
		{
			BW_LOG_INFO(bw::LogChannel::eNET, "Closing TcpServer listening socket");
			g_serverData->stopServer = true;
			::WSASetEvent(g_serverData->cleanupEvent[0]);
			break;
		}
		default:
		{
			// Unknown type
			return false;
		}
	}

	return true;
}

// -----------------------------------------------------------------------------

static DWORD WINAPI worker_thread(void* userData)
{
	bw::TcpServerData& data = *(bw::TcpServerData*) userData;
	bool success = false;
	int callResult = 0;
	LPWSAOVERLAPPED overlapped = nullptr;
	bw::SocketContext* socketContext = nullptr;
	bw::SocketContext* acceptSocketContext = nullptr;
	bw::IoContext* ioContext = nullptr;
	WSABUF buffRecv;
	WSABUF buffSend;
	DWORD nbRecvBytes = 0;
	DWORD nbSendBytes = 0;
	DWORD flags = 0;
	DWORD ioSize = 0;
	HRESULT ret;

	while (true)
	{
		success = ::GetQueuedCompletionStatus(data.iocp, &ioSize, (PDWORD_PTR) &socketContext, (LPOVERLAPPED*) &overlapped, INFINITE);

		if (!success)
		{
			BW_LOG_ERROR(bw::LogChannel::eNET, "GetQueuedCompletionStatus() failed: %d", ::GetLastError());
		}

		if (socketContext == nullptr)
		{
			return 0;
		}

		if (data.stopServer)
		{
			return 0;
		}

		ioContext = (bw::IoContext*) overlapped;

		if (ioContext->ioOperation != bw::IoOperation::eAccept)
		{
			if (!success || (success && ioSize == 0))
			{
				close_client(socketContext, false, data);
				continue;
			}
		}

		switch (ioContext->ioOperation)
		{
			case bw::IoOperation::eAccept :
			{
				callResult = ::setsockopt(socketContext->ioContext->socketAccept,
					SOL_SOCKET,
					SO_UPDATE_ACCEPT_CONTEXT,
					(char*) &data.listenSocket,
					sizeof(data.listenSocket));

				if (callResult == SOCKET_ERROR)
				{
					BW_LOG_ERROR(bw::LogChannel::eNET, "setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed to update accept socket");
					::WSASetEvent(data.cleanupEvent[0]);
					return 0;
				}

				acceptSocketContext = update_completion_port(socketContext->ioContext->socketAccept, bw::IoOperation::eAccept, true, data);

				if (acceptSocketContext == nullptr)
				{
					BW_LOG_ERROR(bw::LogChannel::eNET, "Failed to update accept socket to IOCP");
					::WSASetEvent(data.cleanupEvent[0]);
					return 0;
				}

				if (ioSize > 0)
				{
					acceptSocketContext->ioContext->ioOperation = bw::IoOperation::eWrite;
					acceptSocketContext->ioContext->totalBytes = ioSize;
					acceptSocketContext->ioContext->sentBytes = 0;
					acceptSocketContext->ioContext->wsabuf.len = ioSize;

					ret = ::memcpy_s(acceptSocketContext->ioContext->buffer, bw::kIoBufferSize, socketContext->ioContext->buffer, bw::kIoBufferSize);
					acceptSocketContext->ioContext->wsabuf.buf = acceptSocketContext->ioContext->buffer;

					callResult = ::WSASend(socketContext->ioContext->socketAccept,
						&acceptSocketContext->ioContext->wsabuf,
						1,
						&nbSendBytes,
						0,
						&(acceptSocketContext->ioContext->overlapped),
						nullptr);

					if (callResult == SOCKET_ERROR && ::WSAGetLastError() != WSA_IO_PENDING)
					{
						BW_LOG_ERROR(bw::LogChannel::eNET, "WSASend() failed: %d", ::WSAGetLastError());
						close_client(acceptSocketContext, false, data);
					}

					BW_LOG_INFO(bw::LogChannel::eNET, "WorkerThread %d: Socket(%d) AcceptEx completed (%d bytes), Send posted", 
						   GetCurrentThreadId(), socketContext->socket, ioSize);
				}
				else
				{
					acceptSocketContext->ioContext->ioOperation = bw::IoOperation::eRead;
					nbRecvBytes = 0;
					flags = 0;
					buffRecv.buf = acceptSocketContext->ioContext->buffer;
					buffRecv.len = bw::kIoBufferSize;

					callResult = ::WSARecv(acceptSocketContext->socket,
						&buffRecv,
						1,
						&nbRecvBytes,
						&flags,
						&acceptSocketContext->ioContext->overlapped,
						nullptr);

					if (callResult == SOCKET_ERROR && ::WSAGetLastError() != WSA_IO_PENDING)
					{
						BW_LOG_ERROR(bw::LogChannel::eNET, "WSARecv() failed: %d", ::WSAGetLastError());
						close_client(acceptSocketContext, false, data);
					}
				}

				if (!create_accept_socket(false, data))
				{
					BW_LOG_ERROR(bw::LogChannel::eNET, "Please shut down and reboot the server.");
					::WSASetEvent(data.cleanupEvent[0]);
					return 0;
				}

				break;
			}
			case bw::IoOperation::eRead :
			{
				ioContext->ioOperation = bw::IoOperation::eWrite;
				ioContext->totalBytes = ioSize;
				ioContext->sentBytes = 0;
				ioContext->wsabuf.len = ioSize;
				flags = 0;

				callResult = ::WSASend(socketContext->socket,
					&ioContext->wsabuf,
					1,
					&nbSendBytes,
					flags,
					&(ioContext->overlapped),
					nullptr);

				if (callResult == SOCKET_ERROR && ::WSAGetLastError() != WSA_IO_PENDING)
				{
					BW_LOG_ERROR(bw::LogChannel::eNET, "WSASend() failed: %d", ::WSAGetLastError());
					close_client(socketContext, false, data);
				}
				else
				{
					BW_LOG_INFO(bw::LogChannel::eNET, "WorkerThread %d: Socket(%d) Recv completed (%d bytes), Send posted",
						GetCurrentThreadId(), socketContext->socket, ioSize);
				}

				break;
			}
			case bw::IoOperation::eWrite :
			{
				ioContext->ioOperation = bw::IoOperation::eWrite;
				ioContext->sentBytes += ioSize;
				flags = 0;

				if (ioContext->sentBytes < ioContext->totalBytes)
				{
					buffSend.buf = ioContext->buffer + ioContext->sentBytes;
					buffSend.len = ioContext->totalBytes - ioContext->sentBytes;

					callResult = ::WSASend(socketContext->socket,
						&buffSend,
						1,
						&nbSendBytes,
						flags,
						&(ioContext->overlapped),
						nullptr);

					if (callResult == SOCKET_ERROR && ::WSAGetLastError() != WSA_IO_PENDING)
					{
						BW_LOG_ERROR(bw::LogChannel::eNET, "WSASend() failed: %d", ::WSAGetLastError());
						close_client(socketContext, false, data);
					}
					else
					{
						BW_LOG_INFO(bw::LogChannel::eNET, "WorkerThread %d: Socket(%d) Send partially completed (%d bytes), Recv posted",
							GetCurrentThreadId(), socketContext->socket, ioSize);
					}
				}
				else
				{
					ioContext->ioOperation = bw::IoOperation::eRead;
					nbRecvBytes = 0;
					flags = 0;
					buffRecv.buf = ioContext->buffer;
					buffRecv.len = bw::kIoBufferSize;

					callResult = ::WSARecv(socketContext->socket,
						&buffRecv,
						1,
						&nbRecvBytes,
						&flags,
						&ioContext->overlapped,
						nullptr);

					if (callResult == SOCKET_ERROR && ::WSAGetLastError() != WSA_IO_PENDING)
					{
						BW_LOG_ERROR(bw::LogChannel::eNET, "WSARecv() failed: %d", ::WSAGetLastError());
						close_client(socketContext, false, data);
					}
					else
					{
						BW_LOG_INFO(bw::LogChannel::eNET, "WorkerThread %d: Socket(%d) Send completed (%d bytes), Recv posted",
							GetCurrentThreadId(), socketContext->socket, ioSize);
					}
				}

				break;
			}
		}
	};

	return 0;
}

// -----------------------------------------------------------------------------

static DWORD WINAPI server_thread(void* userData)
{
	bw::TcpServerData& data = *(bw::TcpServerData*) userData;
	
	if (!::SetConsoleCtrlHandler(console_control_handler, true))
	{
		BW_LOG_ERROR(bw::LogChannel::eNET, "SetConsoleCtrlHandler() failed to install console handler (%d)", ::GetLastError());
		return 0;
	}

	while (data.restartServer)
	{
		data.restartServer = false;
		data.stopServer    = false;

		if (!::WSAResetEvent(data.cleanupEvent[0]))
		{
			BW_LOG_ERROR(bw::LogChannel::eNET, "WSAResetEvent() failed (%d)", ::WSAGetLastError());
			return 0;
		}

		__try
		{
			data.iocp = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);

			if (data.iocp == nullptr)
			{
				BW_LOG_ERROR(bw::LogChannel::eNET, "CreateIoCompletionPort() failed (%d)", ::GetLastError());
				return 0;
			}

			// Create the worker threads
			for (size_t i = 0; i < data.nbThreads; ++i)
			{
				HANDLE thread = INVALID_HANDLE_VALUE;
				DWORD threadId;

				thread = ::CreateThread(nullptr, 0, worker_thread, &data, 0, &threadId);

				if (thread == nullptr)
				{
					BW_LOG_ERROR(bw::LogChannel::eNET, "CreateThread() failed (%d)", ::GetLastError());
					return 0;
				}

				data.threadHandles[i] = thread;
			}

			if (!create_listen_socket(data))
			{
				BW_LOG_ERROR(bw::LogChannel::eNET, "create_listen_socket() failed");
				return 0;
			}

			if (!create_accept_socket(true, data))
			{
				BW_LOG_ERROR(bw::LogChannel::eNET, "create_accept_socket() failed");
				return 0;
			}

			::WSAWaitForMultipleEvents(1, data.cleanupEvent, true, WSA_INFINITE, false);
		}
		__finally
		{
			data.stopServer = true;

			if (data.iocp != nullptr)
			{
				for (DWORD i = 0; i < data.nbThreads; ++i)
				{
					::PostQueuedCompletionStatus(data.iocp, 0, 0, nullptr);
				}
			}

			if (::WaitForMultipleObjects(data.nbThreads, data.threadHandles, true, 1000) != WAIT_OBJECT_0)
			{
				BW_LOG_ERROR(bw::LogChannel::eNET, "WaitForMultipleObjects() failed: %d", ::GetLastError());
			}
			else
			{
				for (DWORD i = 0; i < data.nbThreads; ++i)
				{
					if (data.threadHandles[i] != INVALID_HANDLE_VALUE)
					{
						::CloseHandle(data.threadHandles[i]);
					}

					data.threadHandles[i] = INVALID_HANDLE_VALUE;
				}
			}

			if (data.listenSocket != INVALID_SOCKET)
			{
				::closesocket(data.listenSocket);
				data.listenSocket = INVALID_SOCKET;
			}

			if (data.contextListenSocket != nullptr)
			{
				/*while (!HasOverlappedIoCompleted((LPOVERLAPPED) &data.contextListenSocket->ioContext->overlapped))
				{
					::Sleep(0);
				}*/

				if (data.contextListenSocket->ioContext != nullptr)
				{
					if (data.contextListenSocket->ioContext->socketAccept != INVALID_SOCKET)
					{
						::closesocket(data.contextListenSocket->ioContext->socketAccept);
						data.contextListenSocket->ioContext->socketAccept = INVALID_SOCKET;
					}

					bw::memory::generic_allocator().deallocateObject(data.contextListenSocket->ioContext);
					data.contextListenSocket->ioContext = nullptr;
				}

				bw::memory::generic_allocator().deallocateObject(data.contextListenSocket);
				data.contextListenSocket = nullptr;
			}

			delete_socket_context_list(data);

			if (data.iocp != nullptr)
			{
				::CloseHandle(data.iocp);
				data.iocp = nullptr;
			}
		}
	}

    data.running = false;

	return 0;
}

namespace bw
{

// -----------------------------------------------------------------------------
//  Constructors & destructor
// -----------------------------------------------------------------------------
TcpServer::TcpServer(const TcpServerConfig& config)
{
	static_assert(internal::network::kTcpServerSize >= sizeof(TcpServerData), "TcpServerData must be incremented");

	TcpServerData* data = new (m_impl) TcpServerData();
	data->config = config;
}

// -----------------------------------------------------------------------------

TcpServer::~TcpServer()
{
	TcpServerData* data = (TcpServerData*) m_impl;

	if (data->running)
	{
		shutdown_server(*data);
	}

	(*data).~TcpServerData();
}

// -----------------------------------------------------------------------------
//  Public methods
// -----------------------------------------------------------------------------
void TcpServer::run()
{
	TcpServerData* data = (TcpServerData*) m_impl;
	
	if (initialize_server(*data))
	{
		DWORD threadId;
		data->serverThread = ::CreateThread(nullptr, 0, server_thread, data, 0, &threadId);

		if (data->serverThread != nullptr)
		{
			BW_LOG_INFO(LogChannel::eNET, "Created TcpServer thread %d", threadId);
			data->running = true;
		}
		else
		{
			BW_LOG_ERROR(LogChannel::eNET, "Can't create TcpServer thread (%d)", ::GetLastError());
		}
	}
}

// -----------------------------------------------------------------------------

void TcpServer::stop()
{
	TcpServerData* data = (TcpServerData*) m_impl;

	if (data->running)
	{
		BW_LOG_INFO(LogChannel::eNET, "Stopping TcpServer ...");

		data->stopServer    = true;
		data->restartServer = false;

		::WSASetEvent(data->cleanupEvent[0]);
		::WaitForSingleObject(data->serverThread, INFINITE);

		shutdown_server(*data);

		data->running = false;

		BW_LOG_INFO(LogChannel::eNET, "TcpServer stopped");
	}
}

// -----------------------------------------------------------------------------

void TcpServer::restart()
{
	TcpServerData* data = (TcpServerData*) m_impl;

	BW_LOG_INFO(LogChannel::eNET, "Restarting TcpServer ...");

	stop();
	run();

	BW_LOG_INFO(LogChannel::eNET, "TcpServer restarted");
}

// -----------------------------------------------------------------------------

bool TcpServer::isRunning() const
{
	return ((TcpServerData*) m_impl)->running;
}

}	// namespace bw