/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <cstddef>
#include <dom/IDOMObject.hpp>
#include <layout/Layout.hpp>

extern int Photon_SummonTab(int argc, Photon::IPhotonDOM* argv[]);

namespace Photon
{
	bool is_html_document(String data) noexcept
	{
		std::transform(data.begin(), data.end(), data.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		return data.find(PHOTON_HTML_DOCTYPE) != String::npos &&
			   data.find(PHOTON_XHTML_DOCTYPE) == String::npos;
	}

	/// @brief Check if xml is XHTML document.
	bool is_xhtml_document(String data) noexcept
	{
		return data.find(PHOTON_XHTML_DOCTYPE) != String::npos;
	}

	/// @brief Get HTML document from xml blob.
	String get_xhtml_document(String data) noexcept
	{
		if (!is_xhtml_document(data))
		{
			return PHOTON_EMPTY_HTML;
		}

		std::transform(data.begin(), data.end(), data.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		if (data.find(PHOTON_HTML_DOCTYPE) != String::npos)
		{
			return data.substr(data.find(PHOTON_HTML_DOCTYPE) + strlen(PHOTON_HTML_DOCTYPE));
		}
		else
		{
			String doc_type = data.substr(0, strlen(PHOTON_HTML_DOCTYPE));

			std::transform(doc_type.begin(), doc_type.end(), doc_type.begin(),
						   [](unsigned char c) { return std::tolower(c); });

			return data.substr(data.find(doc_type) + doc_type.size());
		}
	}

	/// @Brief Get HTML document.
	String get_html_document(String data) noexcept
	{
		if (!is_html_document(data))
		{
			return PHOTON_EMPTY_HTML;
		}

		std::transform(data.begin(), data.end(), data.begin(),
					   [](unsigned char c) { return std::tolower(c); });

		if (data.find(PHOTON_HTML_DOCTYPE) != String::npos)
		{
			return data.substr(data.find(PHOTON_HTML_DOCTYPE) + strlen(PHOTON_HTML_DOCTYPE));
		}
		else
		{
			String doc_type = data.substr(0, strlen(PHOTON_HTML_DOCTYPE));

			std::transform(doc_type.begin(), doc_type.end(), doc_type.begin(),
						   [](unsigned char c) { return std::tolower(c); });

			return data.substr(data.find(doc_type) + doc_type.size());
		}
	}

	IDOMObject* IDOMObject::make_dom_object(String data)
	{
		if (data.empty())
			return nullptr;

		rapidxml::xml_document<char> doc;
		doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(data.data());

		IDOMObject* new_dom = new IDOMObject(doc.first_node("html"));

		if (!new_dom)
		{
			PHOTON_ERROR("DOM allocation failure, probably out of memory.");
			return nullptr;
		}

		return new_dom;
	}
} // namespace Photon
