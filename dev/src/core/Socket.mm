/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <core/Socket.hpp>

namespace Photon::Network {
Socket::Socket(const SOCKET_TYPE type) : PublicSocket(SOCKET_ERROR) {
  if (type == SOCKET_TYPE::TCP) {
    this->PublicSocket = PHOTON_SOCKET(AF_INET, SOCK_STREAM, 0);
  } else if (type == SOCKET_TYPE::UDP) {
    this->PublicSocket = PHOTON_SOCKET(AF_INET, SOCK_DGRAM, 0);
  }

  PHOTON_ASSERT(this->PublicSocket != SOCKET_ERROR);
}

Socket::~Socket() {
  if (PHOTON_SHUTDOWN(this->PublicSocket, SD_BOTH))
    PHOTON_CLOSE(this->PublicSocket);
}

Socket::operator bool() noexcept { return this->PublicSocket != SOCKET_ERROR; }
} // namespace Photon::Network
