/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <dom/IScriptObject.hpp>
#include <js/JSVirtualMachine.hpp>

namespace Photon {
IScriptObject::IScriptObject(rapidxml::xml_node<char> *p_node)
    : IDOMObject(p_node) {}

Int32 IScriptObject::node_type() { return PHOTON_SCRIPT_OBJECT; }

Bool IScriptObject::run_script() {
  std::vector<String> blob;

  String node_data;
  String in_node_data = this->value();

  std::cout << in_node_data;

  for (auto &ch : in_node_data) {
    if (ch == '\n') {
      blob.push_back(node_data);
      node_data.clear();
      continue;
    }

    node_data.push_back(ch);
  }

  IJSVirtualMachine prog(blob);
  return prog.run_script();
}

IScriptObject *IScriptObject::make_script_object(String data) {
  if (data.empty())
    return nullptr;

  try {
    rapidxml::xml_document<char> doc;
    doc.parse<0>(data.data());

    String name = doc.first_node()->name();

    const String kScriptMarkup = "script";

    if (name != kScriptMarkup) {
      return nullptr;
    }

    std::vector<String> blob;

    IScriptObject *new_dom = new IScriptObject(doc.first_node());

    if (!new_dom) {
      PHOTON_ERROR("Script DOM couldn't be allocated, probably out of memory.");
      return nullptr;
    }

    return new_dom;
  } catch (...) {
    return nullptr;
  }
}
} // namespace Photon
