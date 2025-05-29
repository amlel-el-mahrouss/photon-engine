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
#include <core/URL.hpp>
#include <dom/IDOMObject.hpp>
#include <js/JSVirtualMachine.hpp>
#include <layout/RenderSystem+OpenStep.hpp>
#include <sstream>
#include <string>

namespace Photon
{
#ifdef __PHOTON_APPLE__
	typedef NSWindow* PhotonWindowHandle;
#endif

	class PHOTON_API BrowserTab
	{
	private:
		URL				   m_tab_url{PHOTON_HTTPS_PROTOCOL};
		String			   m_tab_name{"Loading - Photon"};
		String			   m_html_blob{PHOTON_EMPTY_HTML};
		IDOMObject*		   m_dom{nullptr};
		IPhotonTextDOM*	   m_document_root{nullptr};
		PhotonWindowHandle m_tab_handle{nullptr};

	public:
		BrowserTab()		  = default;
		virtual ~BrowserTab() = default;

		PHOTON_COPY_DEFAULT(BrowserTab);

		bool load(URL url)
		{
			try
			{
				m_html_blob = url.fetch();
				m_tab_url	= url;

				try
				{
					m_dom = IDOMObject::make_dom_object(m_html_blob);

					if (!m_dom)
					{
						m_html_blob = get_html_document(m_html_blob);
						m_dom		= IDOMObject::make_dom_object(m_html_blob);
					}
				}
				catch (...)
				{
					m_html_blob = get_html_document(m_html_blob);
					m_dom		= IDOMObject::make_dom_object(m_html_blob);
				}

				if (m_dom)
				{
					auto html = m_dom->get_node(nullptr);

					if (auto elem = html->first_node("head"); elem)
					{
						elem = elem->first_node();

						String elem_nm;

						while (elem)
						{
							elem_nm = elem->name();

							if (elem_nm == "title")
								m_tab_name = elem->value();

							elem = elem->next_sibling();
						}
					}

					if (auto elem = html->first_node("body"); elem)
					{
						elem = elem->first_node();

						int pos_y = 730;
						int pos_x = 10;

						m_document_root = new IPhotonTextDOM();

						String elem_nm;

						while (elem)
						{
							elem_nm = elem->name();

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

								m_document_root->insert_child_element(text);
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

								m_document_root->insert_child_element(text);
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

								m_document_root->insert_child_element(text);
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

								m_document_root->insert_child_element(text);
							}
							else if (elem_nm == "br")
							{
								pos_y -= 13.28;
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

								m_document_root->insert_child_element(text);
							}
							else if (elem_nm == "button")
							{
								IPhotonButtonDOM* text = new IPhotonButtonDOM();

								text->set_content_text([NSString stringWithUTF8String:elem->value()]);
								text->set_heading(IPhotonTextDOM::kHeadingParagraph);

								pos_y -= 50;

								text->set_position(pos_x, pos_y);
								m_document_root->insert_child_element(text);
							}
							else if (elem_nm == "script" && elem->value())
							{
								
							}
							else if (elem_nm == "img")
							{
								IPhotonImageDOM* text = new IPhotonImageDOM();

								String image_src = elem->first_attribute("src")->value();

								if (!image_src.starts_with("http://") &&
									!image_src.starts_with("https://") &&
									!image_src.starts_with("file://"))
								{
									image_src = m_tab_url.protocol() + "://" + m_tab_url.get() + image_src;
								}

								text->set_image_url([[NSURL alloc] initWithString:[NSString stringWithUTF8String:image_src.c_str()]]);
								text->set_content_text([NSString stringWithUTF8String:elem->value()]);
								text->set_heading(IPhotonTextDOM::kHeadingParagraph);

								pos_y -= text->height();

								text->set_position(pos_x, pos_y);

								m_document_root->insert_child_element(text);
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

								m_document_root->insert_child_element(text);
							}

							elem = elem->next_sibling();
						}

						ShellFactory shell;

						m_tab_handle = shell.tab(m_tab_name);

#ifdef __PHOTON_APPLE__
						[m_tab_handle setSubtitle:[NSString stringWithUTF8String:url.get().c_str()]];

						NSToolbar* toolbar				= [[NSToolbar alloc] initWithIdentifier:@"NSToolbarIdentifierTab"];
						toolbar.allowsUserCustomization = YES;
						toolbar.displayMode				= NSToolbarDisplayModeIconAndLabel;

						[m_tab_handle setToolbar:toolbar];
#endif

						m_document_root->insert_element(m_tab_handle);

						return true;
					}
				}
			}
			catch (...)
			{
			}

			return false;
		}

		void release()
		{
			delete m_dom;

			delete m_document_root;
			m_document_root = nullptr;

			m_html_blob.clear();
			m_tab_name.clear();
		}
	};
} // namespace Photon
