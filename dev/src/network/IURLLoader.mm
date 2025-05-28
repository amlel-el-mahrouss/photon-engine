/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

/// @file IURLLoader.cc

#include <core/IURLLoader.hpp>

namespace Photon {
constexpr size_t PHOTON_MAX_BUF = 1000000000UL;

String IURLLoader::put(URL &url, String data, bool cache_data) {
  HTTP::HTTPWriter http_req(HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS);

  if (HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS &&
      url.protocol() != PHOTON_HTTPS_PROTOCOL) {
    PHOTON_WARN("Trying to use HTTPS on a HTTP route.");
    throw BrowserError("HTTPS_ON_HTTP");
  } else if (HTTP::PHOTON_HTTP_PORT != PHOTON_USE_HTTPS &&
             url.protocol() == PHOTON_HTTPS_PROTOCOL) {
    PHOTON_ERROR("Trying to use HTTP on a HTTPS route.");
    throw BrowserError("HTTP_ON_HTTPS");
  }

  std::vector<std::pair<std::string, std::string>> headers;

  if (!cache_data) {
    headers.push_back({"Pragma", "no-cache"});
    headers.push_back({"Cache-Control", "no-cache"});
  }

  auto http_request = HTTP::IHTTPHelper::form_request(
      url.get(), mEndpoint, HTTP::PHOTON_HTTP_PUT, data.size(), headers, data);

  auto sock = http_req.create_and_connect(mEndpoint);

  if (!sock)
    return PHOTON_EMPTY_HTML;

  if (!http_req.send_from_socket(sock, http_request.c_str(),
                                 http_request.size()))
    return PHOTON_EMPTY_HTML;

  char *bytes = new char[PHOTON_MAX_BUF];
  PHOTON_ASSERT(bytes);

  memset(bytes, 0, PHOTON_MAX_BUF);

  if (bytes) {
    http_req.read_from_socket(sock, bytes, PHOTON_MAX_BUF);

    String result = bytes;

    http_req.close_socket();

    delete[] bytes;
    bytes = nullptr;

    return result;
  }

  http_req.close_socket();

  return PHOTON_EMPTY_HTML;
}

String IURLLoader::del(URL &url, String data, bool cache_data) {
  HTTP::HTTPWriter http_req(HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS);

  if (HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS &&
      url.protocol() != PHOTON_HTTPS_PROTOCOL) {
    PHOTON_WARN("Trying to use HTTPS on a HTTP route.");
    throw BrowserError("HTTPS_ON_HTTP");
  } else if (HTTP::PHOTON_HTTP_PORT != PHOTON_USE_HTTPS &&
             url.protocol() == PHOTON_HTTPS_PROTOCOL) {
    PHOTON_ERROR("Trying to use HTTP on a HTTPS route.");
    throw BrowserError("HTTP_ON_HTTPS");
  }

  std::vector<std::pair<std::string, std::string>> headers;

  if (!cache_data) {
    headers.push_back({"Pragma", "no-cache"});
    headers.push_back({"Cache-Control", "no-cache"});
  }

  auto http_request = HTTP::IHTTPHelper::form_request(
      url.get(), mEndpoint, HTTP::PHOTON_HTTP_DELETE, data.size(), headers,
      data);

  auto sock = http_req.create_and_connect(mEndpoint);

  if (!sock)
    return PHOTON_EMPTY_HTML;

  if (!http_req.send_from_socket(sock, http_request.c_str(),
                                 http_request.size()))
    return PHOTON_EMPTY_HTML;

  char *bytes = new char[PHOTON_MAX_BUF];
  PHOTON_ASSERT(bytes);

  memset(bytes, 0, PHOTON_MAX_BUF);

  if (bytes) {
    http_req.read_from_socket(sock, bytes, PHOTON_MAX_BUF);

    String result = bytes;

    http_req.close_socket();

    delete[] bytes;
    bytes = nullptr;

    return result;
  }

  http_req.close_socket();

  return PHOTON_EMPTY_HTML;
}

String IURLLoader::post(URL &url, String data, bool cache_data) {
  HTTP::HTTPWriter http_req(HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS);

  if (HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS &&
      url.protocol() != PHOTON_HTTPS_PROTOCOL) {
    PHOTON_WARN("Trying to use HTTPS on a HTTP route.");
    throw BrowserError("HTTPS_ON_HTTP");
  } else if (HTTP::PHOTON_HTTP_PORT != PHOTON_USE_HTTPS &&
             url.protocol() == PHOTON_HTTPS_PROTOCOL) {
    PHOTON_ERROR("Trying to use HTTP on a HTTPS route.");
    throw BrowserError("HTTP_ON_HTTPS");
  }

  std::vector<std::pair<std::string, std::string>> headers;

  if (!cache_data) {
    headers.push_back({"Pragma", "no-cache"});
    headers.push_back({"Cache-Control", "no-cache"});
  }

  auto http_request = HTTP::IHTTPHelper::form_request(
      url.get(), mEndpoint, HTTP::PHOTON_HTTP_POST, data.size(), headers, data);

  auto sock = http_req.create_and_connect(mEndpoint);

  if (!sock)
    return PHOTON_EMPTY_HTML;

  if (!http_req.send_from_socket(sock, http_request.c_str(),
                                 http_request.size()))
    return PHOTON_EMPTY_HTML;

  char *bytes = new char[PHOTON_MAX_BUF];
  PHOTON_ASSERT(bytes);

  memset(bytes, 0, PHOTON_MAX_BUF);

  if (bytes) {
    http_req.read_from_socket(sock, bytes, PHOTON_MAX_BUF);

    String result = bytes;

    http_req.close_socket();

    delete[] bytes;
    bytes = nullptr;

    return result;
  }

  http_req.close_socket();

  return PHOTON_EMPTY_HTML;
}

String IURLLoader::get(URL &url, bool cache_data) {
  HTTP::HTTPWriter http_probe(HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS);

  if (HTTP::PHOTON_HTTP_PORT == PHOTON_USE_HTTPS &&
      url.protocol() != PHOTON_HTTPS_PROTOCOL) {
    PHOTON_WARN("Trying to use HTTPS on a HTTP route.");
    throw BrowserError("HTTPS_ON_HTTP");
  } else if (HTTP::PHOTON_HTTP_PORT != PHOTON_USE_HTTPS &&
             url.protocol() == PHOTON_HTTPS_PROTOCOL) {
    PHOTON_ERROR("Trying to use HTTP on a HTTPS route.");
    throw BrowserError("HTTP_ON_HTTPS");
  }

  std::vector<std::pair<std::string, std::string>> headers;

  if (!cache_data) {
    headers.push_back({"Pragma", "no-cache"});
    headers.push_back({"Cache-Control", "no-cache"});
  }

  PHOTON_INFO("Forming HTTP request...");

  auto http_request = HTTP::IHTTPHelper::form_request(
      url.get(), mEndpoint, HTTP::PHOTON_HTTP_GET, 0, headers);

  auto sock = http_probe.create_and_connect(mEndpoint);

  if (!sock)
    return PHOTON_EMPTY_HTML;

  if (!http_probe.send_from_socket(sock, http_request.c_str(),
                                   http_request.size()))
    return PHOTON_EMPTY_HTML;

  char *bytes = new char[PHOTON_MAX_BUF];
  PHOTON_ASSERT(bytes);

  memset(bytes, 0, PHOTON_MAX_BUF);

  if (bytes) {
    http_probe.read_from_socket(sock, bytes, PHOTON_MAX_BUF);

    String result = bytes;

    http_probe.close_socket();

    delete[] bytes;
    bytes = nullptr;

    return result;
  }

  http_probe.close_socket();

  return PHOTON_EMPTY_HTML;
}

void IURLLoader::set_endpoint(const String &endpoint) noexcept {
  if (!endpoint.empty())
    mEndpoint = endpoint;
}

String IURLLoader::get_endpoint() noexcept { return mEndpoint; }

String IURLLoader::get_protocol() noexcept { return PHOTON_URL_PROTO; }
} // namespace Photon
