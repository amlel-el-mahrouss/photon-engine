/*
 * =====================================================================
 *
 *			Photon
 *
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <Config.hpp>
#include <Macros.hpp>
#include <cerrno>
#include <cstdlib>

#ifdef PHOTON_END_OF_BUFFER
#undef PHOTON_END_OF_BUFFER
#endif // PHOTON_END_OF_BUFFER

#define PHOTON_END_OF_BUFFER '\0'

#define PHOTON_EMPTY_HTML "<!doctype html>\r\n<html>\r\n<head>\r\n</head>\r\n<body>\r\n</body>\r\n</html>\r\n"

PHOTON_API void	  photon_log(const char* str);
PHOTON_API size_t photon_strlen(const char* str);
PHOTON_API time_t photon_get_epoch();
PHOTON_API FILE*  photon_get_logger();
PHOTON_API bool	  photon_open_logger();

namespace Photon
{
	namespace FS = std::filesystem;

	using Thread = std::thread;
	using String = std::string;

	template <typename CharType>
	using BasicString = std::basic_string<CharType>;

	using PChar = wchar_t;

	using PString = BasicString<PChar>;

	class PHOTON_API BrowserError : public std::runtime_error
	{
	public:
		BrowserError(const char* error = "ERROR_UNKNOWN")
			: std::runtime_error(error)
		{
		}
		~BrowserError() = default; // let the ABI define that.

		BrowserError& operator=(const BrowserError&) = default;
		BrowserError(const BrowserError&)			 = default;
	};

	inline String photon_replace_format(String fmt, String output, String with)
	{
		auto err_pos = output.find("{{ " + fmt + " }}");

		if (err_pos != String::npos)
		{
			output.replace(err_pos, ("{{ " + fmt + " }}").size(), with);
		}

		return output;
	}

	class PHOTON_API ShellFactory final
	{
	public:
		explicit ShellFactory() = default;
		~ShellFactory()			= default;

		ShellFactory& operator=(const ShellFactory&) = default;
		ShellFactory(const ShellFactory&)			 = default;

	private:
		NSWindow*	window{nullptr};
		NSScroller* scroller{nullptr};

		/// @internal
		void scroller_moved_(NSScroller* sender)
		{
			(void)sender;

			double	val			  = [scroller doubleValue]; // 0.0 (top) to 1.0 (bottom)
			CGFloat contentHeight = NSHeight([window.contentView frame]);
			CGFloat maxOffset	  = contentHeight;

			NSRect f				   = [window.contentView frame];
			f.origin.y				   = -val * maxOffset;
			[window.contentView frame] = f;
		}

	public:
		NSWindow* tab(const String text)
		{
			if (window)
				return window;

			window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 1280, 720)
												 styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
												   backing:NSBackingStoreBuffered
													 defer:NO];

			[window setTitle:[NSString stringWithUTF8String:((!text.empty()) ? text.c_str() : "Untitled - Photon")]];
			[window center];

			[window setBackgroundColor:[NSColor whiteColor]];

			[window makeKeyAndOrderFront:nil];
			[window setLevel:NSStatusWindowLevel];

			scroller = [[NSScroller alloc] initWithFrame:NSMakeRect(0, 0, 1280, 720)];

			[scroller setTarget:window];
			[scroller setKnobProportion:0.2];
			[scroller setDoubleValue:0.0];
			[scroller setAction:@selector(scroller_moved_)];
			[window.contentView addSubview:scroller];

			return window;
		}

		String prompt(const String text)
		{
			NSWindow* modal_window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 400, 200)
																 styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable)
																   backing:NSBackingStoreBuffered
																	 defer:NO];
			[modal_window setTitle:[NSString stringWithUTF8String:((!text.empty()) ? text.c_str() : "Photon")]];
			[modal_window center];

			NSInteger result = [[NSApplication sharedApplication] runModalForWindow:modal_window];

			return "NO";
		}

		bool grant_or_fail(const String permission_name)
		{
			static std::vector<String> kPermsList;

			if (std::find(kPermsList.cbegin(), kPermsList.cend(), permission_name) != kPermsList.end())
				return true;

			if (this->prompt("The page is asking for: " + permission_name + "\nAccept?") == "NO")
				return false;

			kPermsList.push_back(permission_name);
			return true;
		}

		int open(const char* app_name)
		{
			if (!app_name)
				return ENOENT;

			String cmd = "open -a ";
			cmd += app_name;

			return std::system(cmd.c_str());
		}
	};
} // namespace Photon

#define PHOTON_CRITICAL(...) spdlog::critical(__VA_ARGS__)
#define PHOTON_ERROR(...)	 spdlog::error(__VA_ARGS__)
#define PHOTON_INFO(...)	 spdlog::info(__VA_ARGS__)
#define PHOTON_WARN(...)	 spdlog::warn(__VA_ARGS__)
