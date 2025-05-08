/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
#endif // ifdef _WIN32

#include <ctime>
#include <cstdio>
#include <clocale>
#include <cstring>
#include <codecvt>
#include <cassert>
#include <cstdlib>
#include <cstdint>

#include <spdlog/spdlog.h>
#include <uuid/uuid.h>

#include <uuid/uuid.h>

typedef uint16_t uuid_string_t[37];

#import <AppKit/AppKit.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#define SD_BOTH SHUT_RDWR
#define SD_SEND SHUT_WR
#define SD_READ SHUT_RD

#define INVALID_SOCKET ((uintptr_t) - 1)

#include <tuple>
#include <array>
#include <thread>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <concepts>
#include <stdexcept>
#include <algorithm>
#include <filesystem>

#ifdef __GNUC__
#define PHOTON_GCC			(0x0001)
#define PHOTON_CXX_COMPILER "G++"
#define PHOTON_CXX			PHOTON_GCC
#endif

#define PHOTON_API

#ifndef PHOTON_ENV
#define PHOTON_ENV getenv
#endif // PHOTON_ENV

#define PHOTON_COPY_DELETE(KLASS)            \
	KLASS& operator=(const KLASS&) = delete; \
	KLASS(const KLASS&)			   = delete;

#define PHOTON_COPY_DEFAULT(KLASS)            \
	KLASS& operator=(const KLASS&) = default; \
	KLASS(const KLASS&)			   = default;

#define PHOTON_MOVE_DELETE(KLASS)       \
	KLASS& operator=(KLASS&&) = delete; \
	KLASS(KLASS&&)			  = delete;

#define PHOTON_MOVE_DEFAULT(KLASS)       \
	KLASS& operator=(KLASS&&) = default; \
	KLASS(KLASS&&)			  = default;

#ifndef PHOTON_SLEEP
#define PHOTON_SLEEP sleep
#endif /* PHOTON_SLEEP */

namespace Photon
{
	typedef double Double;
	typedef float  Real;

	typedef std::int32_t  Int32;
	typedef std::uint32_t UInt32;

	typedef std::int64_t  Int64;
	typedef std::uint64_t UInt64;

	typedef bool Bool;
} // namespace Photon

typedef unsigned short uuid_string_t[37];

#define PHOTON_ASSERT(expression) assert(expression)