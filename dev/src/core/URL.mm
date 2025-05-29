/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 *			File: Uri.cpp
 *			Purpose: Photon URI parser
 *
 * =====================================================================
 */

/**
@file
*/

#include <core/IURLLoader.hpp>
#include <core/URL.hpp>
#include <string>

namespace Photon {
URL::URL(const char *protocol) {
  m_protocol = protocol;

  if (m_protocol.find(":") != String::npos)
    m_protocol.erase(m_protocol.find(":"));
}

URL::~URL() = default;

String URL::get() noexcept { return m_data; }

URL &URL::operator/=(const String &uri) {
  this->operator/=(uri.c_str());

  return *this;
}

URL &URL::operator/=(const char *uri) {
  if (!uri || *uri == 0)
    return *this;

  String uri_str = uri;

  if (uri_str.find(":") != String::npos) {
    m_data = uri_str.substr(0, uri_str.find(":"));
    m_port = uri_str.substr(uri_str.find(":") + 1);
  } else {
    m_data = uri_str;
  }

  return *this;
}

String URL::port() noexcept { return m_port; }

String URL::protocol() noexcept { return m_protocol; }

String URL::send(String data) {
  if (this->protocol() == PHOTON_HTTPS_PROTOCOL ||
      this->protocol() == PHOTON_HTTP_PROTOCOL) {
    try {
      if (this->protocol() == PHOTON_HTTP_PROTOCOL) {
        Photon::HTTP::PHOTON_HTTP_PORT = PHOTON_USE_HTTP;
      } else {
        Photon::HTTP::PHOTON_HTTP_PORT = PHOTON_USE_HTTPS;
      }

      URL url(this->protocol().c_str());
      IURLLoader url_loader;

      String root = "/";

      String content = this->get();

      if (content.find("/") != std::string::npos) {
        url_loader.set_endpoint(content.substr(0, content.find("/")));

        root = content.substr(content.find("/"));

        // remove port.
        if (root.find(":") != String::npos)
          root.erase(root.find(":"));
      } else {
        url_loader.set_endpoint(content);
      }

      url /= root;

      auto http = url_loader.post(url, data, true);

      if (http.find("\r\n\r\n") != String::npos) {
        auto body = http.substr(http.find("\r\n\r\n") + strlen("\r\n\r\n"));
        return body;
      }
    } catch (BrowserError err) {
      return "";
    }
  }

  return "";
}

String URL::fetch() {
  if (this->protocol() == PHOTON_HTTPS_PROTOCOL ||
      this->protocol() == PHOTON_HTTP_PROTOCOL) {
    try {
      if (this->protocol() == PHOTON_HTTP_PROTOCOL) {
        Photon::HTTP::PHOTON_HTTP_PORT = PHOTON_USE_HTTP;

        ShellFactory shell;
        if (shell.prompt("HTTP Warning - Photon",
                         "Photon is currently connecting via an HTTP route, "
                         "are you sure to continue?") == "NO") {
          return PHOTON_EMPTY_HTML;
        }
      } else {
        Photon::HTTP::PHOTON_HTTP_PORT = PHOTON_USE_HTTPS;
      }

      URL url(this->protocol().c_str());
      IURLLoader url_loader;

      String root = "/";

      String content = this->get();

      if (content.find("/") != std::string::npos) {
        url_loader.set_endpoint(content.substr(0, content.find("/")));

        root = content.substr(content.find("/"));

        // remove port.
        if (root.find(":") != String::npos)
          root.erase(root.find(":"));
      } else {
        url_loader.set_endpoint(content);
      }

      url /= root;

      auto http = url_loader.get(url, false);

      if (http.find("\r\n\r\n") != String::npos) {
        auto body = http.substr(http.find("\r\n\r\n") + strlen("\r\n\r\n"));
        return body;
      }
    } catch (BrowserError err) {
      return PHOTON_EMPTY_HTML;
    }

    return PHOTON_EMPTY_HTML;
  } else if (this->protocol() == PHOTON_FILE_PROTOCOL) {
    std::basic_ifstream<char> file(this->get(), std::ios::binary);

    if (!file.good()) {
      return PHOTON_EMPTY_HTML;
    }

    std::stringstream ss;
    ss << file.rdbuf();

    auto body = ss.str();

    std::cout << body;

    return body;
  } else if (this->protocol() == PHOTON_MAIL_PROTOCOL) {
    return PHOTON_EMPTY_HTML;
  } else if (this->protocol() == PHOTON_PHOTON_PROTOCOL) {
    return PHOTON_EMPTY_HTML;
  } else if (this->protocol() == PHOTON_JS_PROTOCOL) {
    return PHOTON_EMPTY_HTML;
  }

  return PHOTON_EMPTY_HTML;
}

URL &URLError::get() { return m_uri; }

} // namespace Photon
