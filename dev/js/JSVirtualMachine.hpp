/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <core/Core.hpp>
#include <js/JSVirtualMachineJIT.hpp>

#define PHOTON_JS_UNDEFINED "undefined"
#define PHOTON_JS_NULL		"null"
#define PHOTON_JS_WINDOW	"window"

/***********************************************************************************/
/** @brief This file is also about defining core js concepts. */
/***********************************************************************************/

namespace Photon
{
	class IJSVirtualMachine;

	/// @brief JavaScriptEngine class program.
	class IJSVirtualMachine final
	{
	private:
		std::vector<String> mBlob;

	public:
		explicit IJSVirtualMachine(std::vector<String> js_blob);
		~IJSVirtualMachine() = default;

	public:
		PHOTON_COPY_DEFAULT(IJSVirtualMachine);

	public:
		Bool run_script();
	};
} // namespace Photon
