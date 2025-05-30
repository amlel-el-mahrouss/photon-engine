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
#include <unordered_map>
#include <variant>
#include <js/JSVirtualMachineJIT.hpp>
#include <vector>

#define PHOTON_JS_UNDEFINED "undefined"
#define PHOTON_JS_NULL		"null"
#define PHOTON_JS_WINDOW	"window"

/***********************************************************************************/
/** @brief This file is also about defining core js concepts. */
/***********************************************************************************/

namespace Photon
{
	class JSVirtualMachine;
	struct JSEnvironment;

	using JSValue = std::variant<std::monostate, Real, std::string, bool>;


	struct JSObject final
	{
		std::unordered_map<String, JSValue> properties;
	};

	enum JSOpcode
	{
		kJSInvalid	 = 0,
		kJSLoadConst = 100,
		kJSStoreVar,
		kJSLoadVar,
		kJSAddExpr,
		kJSCallNative,
		kJSSetProp
	};

	struct JSInstruction final
	{
		enum JSOpcode m_op
		{
			kJSInvalid
		};

		String m_operand;
		size_t m_index = 0;
	};

	/// @brief JavaScriptEngine class program.
	class JSVirtualMachine final
	{
	private:
		std::vector<String>					m_script;
		std::unordered_map<String, JSValue> m_objects;
		std::vector<JSValue>				m_stack;
		std::vector<JSValue>				m_variables;

	public:
		explicit JSVirtualMachine(std::vector<String> js_blob);
		~JSVirtualMachine() = default;

	public:
		PHOTON_COPY_DEFAULT(JSVirtualMachine);

	public:
		Bool execute();

	public:
		Bool pre_eval(const String& line, BOOL& comment_ctrl);
		Bool eval(JSInstruction& opcode);
	};
} // namespace Photon
