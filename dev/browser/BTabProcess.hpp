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
#include <core/URL.hpp>
#include <dom/IDOMObject.hpp>
#include <dom/IScriptObject.hpp>
#include <unistd.h>
#include <layout/Layout.hpp>

namespace Photon
{
	class PHOTON_API BTabProcess
	{
	private:
		URL			m_tab_url{PHOTON_HTTPS_PROTOCOL};
		String		m_tab_name{"New Tab"};
		String		m_html_blob{PHOTON_EMPTY_HTML};
		IDOMObject* m_dom{nullptr};

	public:
		BTabProcess()		   = default;
		virtual ~BTabProcess() = default;

		PHOTON_COPY_DEFAULT(BTabProcess);

		bool load(URL url) noexcept
		{
			m_html_blob = url.fetch();
			m_tab_url	= url;

			if (m_html_blob.empty())
				return false;

			m_dom = IDOMObject::make_dom_object(m_html_blob);

			m_tab_name = url.get();

			IPhotonTextDOM* kRootDOM = new IPhotonTextDOM();

			int pos_y = 700;
			int pos_x = 10;

			ShellFactory tab;

			if (m_dom)
			{
				if (auto elem = m_dom->get_node("head"); elem)
				{
					if (elem->first_node("title")->value())
						m_tab_name = elem->first_node("title")->value();
				}

				if (auto elem = m_dom->get_node("body"); elem)
				{
					elem = elem->first_node();

					while (elem)
					{
						std::string elem_nm = elem->name();

						if (elem_nm == "h1")
						{
							IPhotonTextDOM* text = new IPhotonTextDOM();

							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading(IPhotonTextDOM::kHeading1);

							char* v = elem->value();

							pos_y -= 32.0;

							while ((*v) != 0)
							{
								if (*v == '\n')
									pos_y -= 32.0;

								v = ++v;
							}

							pos_y -= 32.0;

							text->set_position(pos_x, pos_y);

							kRootDOM->insert_child_element(text);
						}
						else if (elem_nm == "h2")
						{
							IPhotonTextDOM* text = new IPhotonTextDOM();

							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading(IPhotonTextDOM::kHeading2);

							char* v = elem->value();

							pos_y -= 24.0;

							while ((*v) != 0)
							{
								if (*v == '\n')
									pos_y -= 24.0;

								v = ++v;
							}

							pos_y -= 24.0;

							text->set_position(pos_x, pos_y);

							kRootDOM->insert_child_element(text);
						}
						else if (elem_nm == "h3")
						{
							IPhotonTextDOM* text = new IPhotonTextDOM();

							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading(IPhotonTextDOM::kHeading3);

							pos_y -= 17.8;

							char* v = elem->value();

							while ((*v) != 0)
							{
								if (*v == '\n')
									pos_y -= 17.8;

								v = ++v;
							}

							pos_y -= 17.8;

							text->set_position(pos_x, pos_y);

							kRootDOM->insert_child_element(text);
						}
						else if (elem_nm == "h4" || elem_nm == "h5")
						{
							IPhotonTextDOM* text = new IPhotonTextDOM();

							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading((elem_nm == "h4") ? IPhotonTextDOM::kHeading4 : IPhotonTextDOM::kHeading5);

							pos_y -= 13.28;

							char* v = elem->value();

							while ((*v) != 0)
							{
								if (*v == '\n')
									pos_y -= 13.28;

								v = ++v;
							}

							pos_y -= 13.28;

							text->set_position(pos_x, pos_y);

							kRootDOM->insert_child_element(text);
						}
						else if (elem_nm == "h6")
						{
							IPhotonTextDOM* text = new IPhotonTextDOM();

							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading(IPhotonTextDOM::kHeading6);

							pos_y -= 12;

							char* v = elem->value();

							while ((*v) != 0)
							{
								if (*v == '\n')
									pos_y -= 12.0;

								v = ++v;
							}

							pos_y -= 12;

							text->set_position(pos_x, pos_y);

							kRootDOM->insert_child_element(text);
						}
						else if (elem_nm == "button")
						{
							IPhotonButtonDOM* text = new IPhotonButtonDOM();

							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading(IPhotonTextDOM::kHeadingParagraph);

							pos_y -= 50;

							text->set_position(pos_x, pos_y);
							kRootDOM->insert_child_element(text);
						}
						else if (elem_nm == "photon-popup" && elem->value())
						{
							(void)tab.prompt(m_tab_name, elem->value());
						}
						else if (elem_nm == "img")
						{
							IPhotonImageDOM* text = new IPhotonImageDOM();

							text->set_image_url([[NSURL alloc] initWithString:[NSString stringWithUTF8String:elem->first_attribute("src")->value()]]);
							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading(IPhotonTextDOM::kHeadingParagraph);

							pos_y -= text->height();

							text->set_position(pos_x, pos_y);

							kRootDOM->insert_child_element(text);
						}
						else if (elem_nm == "p" || elem_nm == "b" || elem_nm == "strong")
						{
							IPhotonTextDOM* text = new IPhotonTextDOM();

							text->set_content_text([NSString stringWithUTF8String:elem->value()]);
							text->set_heading((elem_nm == "b" || elem_nm == "strong") ? IPhotonTextDOM::kHeadingBold : IPhotonTextDOM::kHeadingParagraph);

							pos_y -= 16;

							char* v = elem->value();

							while ((*v) != 0)
							{
								if (*v == '\n')
									pos_y -= 16.0;

								v = ++v;
							}

							pos_y -= 16;

							text->set_position(pos_x, pos_y);

							kRootDOM->insert_child_element(text);
						}

						elem = elem->next_sibling();
					}
				}

				auto		 tab_win = tab.tab(m_tab_name);

				kRootDOM->insert_element(tab_win);

				return true;
			}

			return false;
		}

		void release()
		{
			delete m_dom;

			m_html_blob.clear();
			m_tab_name.clear();
		}
	};
} // namespace Photon
