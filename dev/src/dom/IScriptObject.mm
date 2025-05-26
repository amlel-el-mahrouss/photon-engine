/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <dom/IScriptObject.hpp>
#include <js/JSVirtualMachine.hpp>

namespace Photon
{
	IScriptObject::IScriptObject(rapidxml::xml_node<char>* p_node)
		: IDOMObject(p_node)
	{
	}

	Int32 IScriptObject::node_type()
	{
		return PHOTON_SCRIPT_OBJECT;
	}

	Bool IScriptObject::run_script()
	{
		if (!this->get_node(nullptr)->value())
			return false;

		std::vector<String> blob;

		String node_data;
		size_t node_index	= 0UL;
		String in_node_data = this->get_node(nullptr)->value();

		for (auto& ch : in_node_data)
		{
			if (ch == '\n')
			{
				if (in_node_data[node_index - 1] == '\'' ||
					in_node_data[node_index - 1] == '\"')
				{
					++node_index;
					node_data.push_back(ch);
					continue;
				}
				else if (in_node_data[node_index + 1] == '\'' ||
						 in_node_data[node_index + 1] == '\"')
				{
					++node_index;
					node_data.push_back(ch);
					continue;
				}

				blob.push_back(node_data);
				node_data.clear();

				++node_index;
				continue;
			}

			++node_index;
			node_data.push_back(ch);
		}

		IJSVirtualMachine prog(blob);
		return prog.run_script();
	}

	IScriptObject* IScriptObject::make_script_object(String data)
	{
		if (data.empty())
			return nullptr;

		rapidxml::xml_document<char> doc;
		doc.parse<0>(data.data());

		String name = doc.first_node()->name();

		const String kScriptMarkup = "script";

		if (name != kScriptMarkup)
		{
			return nullptr;
		}

		std::vector<String> blob;

		IScriptObject* new_dom = new IScriptObject(doc.first_node());

		if (new_dom)
		{
			PHOTON_ERROR("<script> allocation failed, probably out of memory.");
			return nullptr;
		}

		return new_dom;
	}
} // namespace Photon
