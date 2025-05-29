/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

/// @file IScriptObject.hpp
/// @brief <script> element.

#include <dom/IDOMObject.hpp>
#include <js/JSVirtualMachine.hpp>

#define PHOTON_SCRIPT_OBJECT (1)

namespace Photon
{
	class IScriptObject;

	class IScriptObject final : public IDOMObject
	{
  		std::unique_ptr<IJSVirtualMachine> m_vm;

		explicit IScriptObject(rapidxml::xml_node<char>* p_node);

	public:
		~IScriptObject() override = default;

		Int32				  node_type() override;
		static IScriptObject* make_script_object(String data);

		Bool run_script();
	};
} // namespace Photon
