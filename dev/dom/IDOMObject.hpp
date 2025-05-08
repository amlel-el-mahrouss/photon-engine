/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <core/Engine.hpp>
#include <rapidxml/rapidxml.hpp>

#define PHOTON_DOM_OBJECT	 (0U)
#define PHOTON_HTML_DOCTYPE	 "<!doctype html>"
#define PHOTON_XHTML_DOCTYPE "<html xmlns=\"http://www.w3.org/1999/xhtml\">"

namespace Photon
{
	class IDOMObject;

	class IDOMObject
	{
	protected:
		explicit IDOMObject(rapidxml::xml_node<char>* p_node)
			: m_node(p_node)
		{
			PHOTON_ASSERT(m_node);
		}

	public:
		virtual ~IDOMObject() = default;

		PHOTON_COPY_DEFAULT(IDOMObject);

	public:
		virtual Int32 node_type()
		{
			return PHOTON_DOM_OBJECT;
		}

		virtual bool is_element()
		{
			PHOTON_ASSERT(m_node);
			return rapidxml::node_element == m_node->type();
		}

		virtual bool is_data()
		{
			PHOTON_ASSERT(m_node);
			return rapidxml::node_data == m_node->type();
		}

		virtual bool is_comment()
		{
			PHOTON_ASSERT(m_node);
			return rapidxml::node_comment == m_node->type();
		}

		virtual bool is_doc_type()
		{
			PHOTON_ASSERT(m_node);
			return rapidxml::node_doctype == m_node->type();
		}

		virtual String type()
		{
			if (auto type = this->get_attribute("type"); type)
				return type->value();

			return "";
		}

		virtual String src()
		{
			if (auto type = this->get_attribute("src"); type)
				return type->value();

			return "";
		}

		virtual String value()
		{
			return this->get_node(nullptr)->value();
		}

		virtual rapidxml::xml_attribute<char>* get_attribute(const char* attrib_name)
		{
			PHOTON_ASSERT(m_node);
			return m_node->first_attribute(attrib_name, strlen(attrib_name));
		}

		virtual rapidxml::xml_node<char>* get_node(const char* attrib_name)
		{
			PHOTON_ASSERT(m_node);

			if (!attrib_name)
				return m_node;

			return m_node->first_node(attrib_name);
		}

	public:
		static IDOMObject* make_dom_object(String data);

	private:
		rapidxml::xml_node<char>* m_node{nullptr};
	};

	/// @brief Check if xml is HTML.
	bool is_html_document(String the_xml_blob) noexcept;

	/// @brief Check if xml is XHTML document.
	bool is_xhtml_document(String the_xml_blob) noexcept;

	/// @brief Get HTML document from xml blob.
	String get_html_document(String the_xml_blob) noexcept;

	/// @brief Get HTML document from xml blob.
	String get_xhtml_document(String the_xml_blob) noexcept;
} // namespace Photon
