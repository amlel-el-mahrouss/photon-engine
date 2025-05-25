/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <Core.hpp>
#include <fcntl.h>

#ifdef PHOTON_WINDOWS

#define PHOTON_SOCKET	socket
#define PHOTON_CLOSE	closesocket
#define PHOTON_SHUTDOWN shutdown
#define PHOTON_ACCEPT	accept
#define PHOTON_CONNECT	connect
#define PHOTON_IOCTL	ioctlsocket

#else

#ifndef PHOTON_WINDOWS
#define SOCKET_ERROR	  -1
#define WSAECONNRESET	  ECONNRESET
#define WSAEWOULDBLOCK	  EWOULDBLOCK
#define WSAGetLastError() errno
#endif

#ifdef _WIN32
#define s_addr S_un.S_addr
#endif

#define PHOTON_SOCKET	socket
#define PHOTON_CLOSE	close
#define PHOTON_SHUTDOWN shutdown
#define PHOTON_ACCEPT	accept
#define PHOTON_CONNECT	connect
#define PHOTON_IOCTL	ioctl

#define FIONBIO	 FNONBLOCK
#define FIOASYNC FASYNC

#endif // PHOTON_WINDOWS

namespace Photon
{
	enum class SOCKET_FLAG : std::int64_t
	{
		NON_BLOCKING = FIONBIO,
		ASYNC		 = FIOASYNC,
	};
} // namespace Photon

namespace Photon::Network
{
	enum class SOCKET_TYPE
	{
		TCP,
		UDP,
		COUNT,
	};

	using CSocket = uintptr_t;

	class PHOTON_API Socket final
	{
	public:
		explicit Socket(const SOCKET_TYPE type);
		~Socket();

		Socket& operator=(const Socket&) = default;
		Socket(const Socket&)			 = default;

	public:
		operator bool() noexcept;

	public:
		template <typename Data, size_t Size = sizeof(Data)>
		void send(Data ptr, std::size_t sz = 0);

		template <typename Data, size_t Size = sizeof(Data)>
		void recv(Data ptr, std::size_t sz = 0);

	public:
		CSocket PublicSocket;
	};
} // namespace Photon::Network

#include <Socket.inl>
