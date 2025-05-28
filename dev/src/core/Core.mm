/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

/**
@file
*/

#include <core/Core.hpp>

size_t photon_strlen(const char *buffer) {
  if (!buffer)
    return 0;

  if (*buffer == PHOTON_END_OF_BUFFER)
    return 0;

  size_t index = 0;
  while (buffer[index] != PHOTON_END_OF_BUFFER)
    ++index;

  return index;
}
