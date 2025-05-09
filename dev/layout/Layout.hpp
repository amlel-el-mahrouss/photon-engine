/*
 * =====================================================================
 *
 *            Photon
 *            Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <core/Engine.hpp>

namespace Photon
{
	inline NSRect PTMakeRect(NSInteger x, NSInteger y, NSInteger w, NSInteger h)
	{
		NSRect rect{};
		rect.origin.x	 = x;
		rect.origin.y	 = y;
		rect.size.width	 = w;
		rect.size.height = h;

		return rect;
	}

	class IPhotonDOM
	{
	public:
		explicit IPhotonDOM() = default;
		virtual ~IPhotonDOM() = default;

		IPhotonDOM& operator=(const IPhotonDOM&) = default;
		IPhotonDOM(const IPhotonDOM&)			 = default;

		virtual bool insert_element(NSWindow* window) = 0;
		virtual bool remove_element()				  = 0;

		virtual bool insert_child_element(IPhotonDOM* dom_elem) = 0;
		virtual bool remove_child_element(IPhotonDOM* dom_elem) = 0;

	public:
		virtual void set_content_text(NSString* text)
		{
			h_markup_content = text;
		}

		virtual void set_position(CGFloat x, CGFloat y)
		{
			h_x = x;
			h_y = y;
		}

	public:
		enum
		{
			kHeadingInvalid = 0,
			kHeading1		= 100,
			kHeading2,
			kHeading3,
			kHeading4,
			kHeading5,
			kHeading6,
			kHeadingParagraph,
			kHeadingBold = kHeading5,
			kHeadingItalic,
		};

		void set_heading(int32_t text)
		{
			switch (text)
			{
			case kHeading1:
				h_font_sz = 32.0;
				break;
			case kHeading2:
				h_font_sz = 24.0;
				break;
			case kHeading3:
				h_font_sz = 17.8;
				break;
			case kHeading4:
			case kHeading5:
				h_font_sz = 13.28;
				break;
			case kHeading6:
				h_font_sz = 12;
				break;
			case kHeadingParagraph:
				h_font_sz = 16;
				break;
			default:
				break;
			}
		}

		virtual bool is_text_node()
		{
			return false;
		}

	protected:
		std::vector<IPhotonDOM*> h_child_element;
		bool					 h_renderable{true};
		CGFloat					 h_x{0};
		CGFloat					 h_y{0};

	protected:
		NSString* h_font{@"FreeMono"};
		NSString* h_font_bold{@"FreeMonoBold"};
		NSString* h_markup_content{@""};
		CGFloat	  h_font_sz{16.0f};
	};

	class IPhotonTextDOM : public IPhotonDOM
	{
	protected:
		NSTextView* h_content{nullptr};

	public:
		explicit IPhotonTextDOM() = default;
		virtual ~IPhotonTextDOM() = default;

		IPhotonTextDOM& operator=(const IPhotonTextDOM&) = default;
		IPhotonTextDOM(const IPhotonTextDOM&)			 = default;

	public:
		bool insert_child_element(IPhotonDOM* dom_elem) override
		{
			if (!dom_elem)
				return false;

			this->h_child_element.push_back(dom_elem);
			return true;
		}

		bool is_text_node() override
		{
			return true;
		}

		bool remove_child_element(IPhotonDOM* dom_elem) override
		{
			if (!dom_elem)
				return false;

			auto elem = std::find(this->h_child_element.begin(),
								  this->h_child_element.end(), dom_elem);

			if (elem != this->h_child_element.end())
			{
				this->h_child_element.erase(elem);
				return true;
			}

			return false;
		}

		bool remove_element() override
		{
			if (h_content)
			{
				[h_content removeFromSuperview];

				for (auto& elem : h_child_element)
				{
					elem->remove_element();
				}

				return true;
			}

			return false;
		}

		bool insert_element(NSWindow* window) override
		{
			if (!h_renderable || !window || h_content)
				return false;

			h_content = [[NSTextView alloc]
				initWithFrame:NSMakeRect(this->h_x, this->h_y,
										 this->h_font_sz *
											 [this->h_markup_content length],
										 this->h_font_sz)];

			[h_content setTextColor:[NSColor blackColor]];
			[h_content setBackgroundColor:[NSColor clearColor]];
			[h_content setString:h_markup_content];

			if (h_font_sz <= 13.28)
			{
				[h_content
					setFont:[NSFont fontWithName:this->h_font_bold size:this->h_font_sz]];
			}
			else
			{
				[h_content
					setFont:[NSFont fontWithName:this->h_font size:this->h_font_sz]];
			}

			[[window contentView] addSubview:h_content];

			for (auto& elem : h_child_element)
			{
				elem->insert_element(window);
			}

			return true;
		}
	};

	class IPhotonImageDOM : public IPhotonTextDOM
	{
	protected:
		NSTextView*	 h_placeholder_content{nullptr};
		NSURL*		 h_image_path{nullptr};
		NSImage*	 h_image_content{nullptr};
		NSImageView* h_image_view{nullptr};

	public:
		explicit IPhotonImageDOM() = default;
		virtual ~IPhotonImageDOM() = default;

		IPhotonImageDOM& operator=(const IPhotonImageDOM&) = default;
		IPhotonImageDOM(const IPhotonImageDOM&)			   = default;

		bool set_image_url(NSURL* url_img)
		{
			if (!url_img)
				return false;

			h_image_path = url_img;

			if (h_image_content)
			{
				[h_image_content release];
			}

			h_image_content = [[NSImage alloc] initWithContentsOfURL:h_image_path];

			return true;
		}

		bool insert_child_element(IPhotonDOM* dom_elem) override
		{
			if (!dom_elem)
				return false;

			this->h_child_element.push_back(dom_elem);

			return true;
		}

		bool is_text_node() override
		{
			return false;
		}

		size_t width()
		{
			return h_image_content.size.width;
		}

		size_t height()
		{
			return h_image_content.size.height;
		}

		bool remove_child_element(IPhotonDOM* dom_elem) override
		{
			if (!dom_elem)
				return false;

			auto elem = std::find(this->h_child_element.begin(),
								  this->h_child_element.end(), dom_elem);

			if (elem != this->h_child_element.end())
			{
				this->h_child_element.erase(elem);
				return true;
			}

			return false;
		}

		bool remove_element() override
		{
			if (h_image_content)
			{
				[h_image_view removeFromSuperview];

				for (auto& elem : h_child_element)
				{
					elem->remove_element();
				}

				return true;
			}

			return false;
		}

		bool insert_element(NSWindow* window) override
		{
			if (!h_renderable || !window)
				return false;

			if (!h_image_content)
			{
				h_placeholder_content = [[NSTextView alloc]
					initWithFrame:NSMakeRect(this->h_x, this->h_y,
											 this->h_font_sz *
												 [this->h_markup_content length],
											 this->h_font_sz)];

				[h_placeholder_content setTextColor:[NSColor blackColor]];
				[h_placeholder_content setBackgroundColor:[NSColor clearColor]];
				[h_placeholder_content setString:h_markup_content];

				if (h_font_sz <= 13.28)
				{
					[h_placeholder_content setFont:[NSFont fontWithName:this->h_font_bold
																   size:this->h_font_sz]];
				}
				else
				{
					[h_placeholder_content
						setFont:[NSFont fontWithName:this->h_font size:this->h_font_sz]];
				}

				[[window contentView] addSubview:h_placeholder_content];
			}
			else
			{
				h_image_view = [[NSImageView alloc]
					initWithFrame:NSMakeRect(this->h_x, this->h_y,
											 [h_image_content size].width,
											 [h_image_content size].height)];

				[h_image_view setImage:h_image_content];

				[[window contentView] addSubview:h_image_view];
			}

			for (auto& elem : h_child_element)
			{
				elem->insert_element(window);
			}

			return true;
		}
	};

	class IPhotonButtonDOM : public IPhotonTextDOM
	{
	protected:
		NSButton* h_button_content{nullptr};

	public:
		explicit IPhotonButtonDOM() = default;
		virtual ~IPhotonButtonDOM() = default;

		IPhotonButtonDOM& operator=(const IPhotonButtonDOM&) = default;
		IPhotonButtonDOM(const IPhotonButtonDOM&)			 = default;

		bool insert_child_element(IPhotonDOM* dom_elem) override
		{
			if (!dom_elem)
				return false;

			this->h_child_element.push_back(dom_elem);
			return true;
		}

		bool is_text_node() override
		{
			return false;
		}

		bool remove_child_element(IPhotonDOM* dom_elem) override
		{
			if (!dom_elem)
				return false;

			auto elem = std::find(this->h_child_element.begin(),
								  this->h_child_element.end(), dom_elem);

			if (elem != this->h_child_element.end())
			{
				this->h_child_element.erase(elem);
				return true;
			}

			return false;
		}

		bool remove_element() override
		{
			if (h_button_content)
			{
				[h_button_content removeFromSuperview];

				for (auto& elem : h_child_element)
				{
					elem->remove_element();
				}

				return true;
			}

			return false;
		}

		bool insert_element(NSWindow* window) override
		{
			if (!h_renderable || !window || h_button_content)
				return false;

			h_button_content = [[NSButton alloc]
				initWithFrame:NSMakeRect(this->h_x, this->h_y, 200, 50)];

			[h_button_content setTarget:[window contentView]];
			[h_button_content setEnabled:YES];
			[h_button_content setTransparent:NO];

			NSMutableParagraphStyle* style = [[NSMutableParagraphStyle alloc] init];
			[style setAlignment:NSTextAlignmentCenter];

			NSDictionary* attrsDictionary = [NSDictionary
				dictionaryWithObjectsAndKeys:[NSColor blackColor],
											 NSForegroundColorAttributeName, style,
											 NSParagraphStyleAttributeName, nil];

			NSAttributedString* attrString =
				[[NSAttributedString alloc] initWithString:h_markup_content
												attributes:attrsDictionary];
			[h_button_content setAttributedTitle:attrString];

			if (h_font_sz <= 13.28)
			{
				[h_button_content
					setFont:[NSFont fontWithName:this->h_font_bold size:this->h_font_sz]];
			}
			else
			{
				[h_button_content
					setFont:[NSFont fontWithName:this->h_font size:this->h_font_sz]];
			}

			[[window contentView] addSubview:h_button_content];

			for (auto& elem : h_child_element)
			{
				elem->insert_element(window);
			}

			return true;
		}
	};
} // namespace Photon