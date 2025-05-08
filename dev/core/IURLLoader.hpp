/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <IHTTPProtocol.hpp>
#include <URL.hpp>

#define PHOTON_URL_PROTO "HTTP"

namespace Photon
{
	/*
	 *	@brief IURLLoader
	 *	@brief Interface for loading HTTP/HTTPS urls, this is the base class for loading stuff as well.
	 */

	class PHOTON_API IURLLoader
	{
	public:
		IURLLoader()		  = default;
		virtual ~IURLLoader() = default;

	public:
		PHOTON_COPY_DEFAULT(IURLLoader);

	public:
		virtual String post(URL& url, String data, bool cache_data = false);
		virtual String put(URL& url, String data, bool cache_data = false);
		virtual String del(URL& url, String data, bool cache_data = false);
		virtual String get(URL& url, bool cache_data = false);
		virtual void   set_endpoint(const String& endpoint) noexcept;
		virtual String get_endpoint() noexcept;
		virtual String get_protocol() noexcept;

	protected:
		//! HTTP endpoint.
		String mEndpoint;
	};
} // namespace Photon
