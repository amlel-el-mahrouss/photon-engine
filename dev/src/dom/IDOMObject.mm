/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <dom/IDOMObject.hpp>
#include <layout/RenderSystem+OpenStep.hpp>

#include <libxml/HTMLparser.h>
#include <libxml/xmlsave.h>

extern int Photon_SummonTab(int argc, Photon::IPhotonDOM *argv[]);

namespace Photon {
bool is_html_document(String data) noexcept {
  std::transform(data.begin(), data.end(), data.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  const auto kPhotonXMLMarkup = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";

  return data.find(PHOTON_HTML_MARKUP) != String::npos &&
         data.find(PHOTON_HTML_START) != String::npos &&
         data.find(kPhotonXMLMarkup) == String::npos;
}

/// @Brief Get the HTML document.
String get_html_document(String data) {
  if (!is_html_document(data)) {
    return data;
  }

  auto html = data.c_str();

  htmlDocPtr doc = htmlReadMemory(html, strlen(html), "input.html", NULL,
                                  HTML_PARSE_RECOVER | HTML_PARSE_NOERROR |
                                      HTML_PARSE_NOWARNING);

  if (!doc) {
    return PHOTON_EMPTY_HTML;
  }

  // Step 2: Dump as well-formed XML (XHTML)
  xmlChar *xhtmlBuf = nullptr;
  int xhtmlSize = 0;
  xmlDocDumpMemoryEnc(doc, &xhtmlBuf, &xhtmlSize, "UTF-8");

  std::cout << xhtmlBuf << std::endl;

  auto new_str = String(reinterpret_cast<const char *>(xhtmlBuf), xhtmlSize);

  xmlFree(xhtmlBuf);
  xmlFreeDoc(doc);
  xmlCleanupParser();

  xhtmlBuf = nullptr;
  doc = nullptr;

  if (xhtmlSize < 1) {
    return PHOTON_EMPTY_HTML;
  }

  return new_str;
}

IDOMObject *IDOMObject::make_dom_object(String data) {
  if (data.empty())
    return nullptr;

  try {
    std::vector<char> buffer(data.begin(), data.end());
    buffer.push_back('\0'); // Null-terminate the string for rapidxml

    rapidxml::xml_document<char> doc;

    doc.parse<0>(buffer.data());

    IDOMObject *new_dom = new IDOMObject(doc.document());

    if (!new_dom) {
      PHOTON_ERROR("DOM couldn't be allocated, probably out of memory.");
      return nullptr;
    }

    return new_dom;
  } catch (...) {
    return nullptr;
  }
}
} // namespace Photon
