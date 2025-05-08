/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 *			File: Socket.inl
 *			Purpose: C++ Socket Wrapper
 *
 * =====================================================================
 */

/// <summary>
/// Socket ::send wrapper
/// </summary>
/// <typeparam name="Data">Data type</typeparam>
/// <param name="ptr">Data pointer</param>

template <typename Data, size_t Size>
void Photon::Network::Socket::send(Data ptr, size_t sz)
{
	::send(this->PublicSocket, (const char*)ptr, sz < 1 ? Size : sz, 0);
}

/// <summary>
/// Socket ::recv wrapper
/// </summary>
/// <typeparam name="Data"></typeparam>
/// <param name="ptr"></param>

template <typename Data, size_t Size>
void Photon::Network::Socket::recv(Data ptr, size_t sz)
{
	::recv(this->PublicSocket, (char*)ptr, sz < 1 ? Size : sz, 0);
}
