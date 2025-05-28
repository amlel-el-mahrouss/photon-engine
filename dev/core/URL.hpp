/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 *			File: URL.hpp
 *			Purpose: Photon URI parser
 *
 * =====================================================================
 */

#pragma once

#include <core/Core.hpp>

#ifndef PHOTON_HTTPS_PROTOCOL
#define PHOTON_HTTPS_PROTOCOL ("https")
#endif // !PHOTON_HTTPS_PROTOCOL

#ifndef PHOTON_HTTP_PROTOCOL
#define PHOTON_HTTP_PROTOCOL ("http")
#endif // !PHOTON_HTTP_PROTOCOL

#ifndef PHOTON_FILE_PROTOCOL
#define PHOTON_FILE_PROTOCOL ("file")
#endif // !PHOTON_FILE_PROTOCOL

#ifndef PHOTON_MAIL_PROTOCOL
#define PHOTON_MAIL_PROTOCOL ("mailto")
#endif // !PHOTON_MAIL_PROTOCOL

#ifndef PHOTON_JS_PROTOCOL
#define PHOTON_JS_PROTOCOL ("javascript")
#endif // !PHOTON_JS_PROTOCOL

#ifndef PHOTON_PHOTON_PROTOCOL
#define PHOTON_PHOTON_PROTOCOL ("photon")
#endif // !PHOTON_PHOTON_PROTOCOL

namespace Photon
{
	class PHOTON_API URL final
	{
	public:
		URL(const char* protocol);
		virtual ~URL();

		URL& operator=(const URL&) = default;
		URL(const URL&)			   = default;

		String port() noexcept;
		String protocol() noexcept;
		String get() noexcept;

	public:
		String send(String data);
		String fetch();

	public:
		URL& operator/=(const String& uri);
		URL& operator/=(const char* uri);

	private:
		String m_data;
		String m_protocol;
		String m_port;
	};

	class PHOTON_API URLError final : public BrowserError
	{
	public:
		URLError(URL& uri)
			: BrowserError("INVALID_URL_AT_DEST"), m_uri(uri)
		{
		}

		~URLError() = default; // let the ABI define that.

		URLError& operator=(const URLError&) = default;
		URLError(const URLError&)			 = default;

		URL& get();

	private:
		URL m_uri;
	};
} // namespace Photon
