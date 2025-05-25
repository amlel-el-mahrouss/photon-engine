/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#ifndef _WIN32

#include <core/Core.hpp>
#include <stdarg.h>
#include <sys/mman.h>

namespace Photon
{
	/// @brief Generic javascript function.
	typedef void (*photon_asm_fn_t)(void* arg, size_t arg_cnt);

	inline int photon_delete_chunk(char* fn, size_t size)
	{
		if (!fn ||
			!size)
			return 1;

		return munmap(fn, size);
	}

	inline photon_asm_fn_t photon_allocate_chunk(char* data, size_t size)
	{
		if (!data ||
			!size)
		{
			throw Photon::BrowserError("JIT_ARGUMENT_INVALID");
		}

		char* mem_exec = (char*)mmap(NULL, // address
									 4096, // size
									 PROT_READ | PROT_WRITE | PROT_EXEC,
									 MAP_PRIVATE | MAP_ANONYMOUS,
									 -1, // fd (not used here)
									 0); // offset (not used here)

		if (mem_exec == MAP_FAILED)
		{
			throw Photon::BrowserError("JIT_ERROR_OUT_OF_MEMORY");
			return nullptr;
		}

		memcpy(mem_exec, data, size);

		return (photon_asm_fn_t)mem_exec;
	}
} // namespace Photon

#endif // !_WIN32
