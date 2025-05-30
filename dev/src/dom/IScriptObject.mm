/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <dom/IScriptObject.hpp>
#include <memory>

namespace Photon {
IScriptObject::IScriptObject(rapidxml::xml_node<char> *p_node)
    : IDOMObject(p_node) {}

Int32 IScriptObject::node_type() { return PHOTON_SCRIPT_OBJECT; }

Bool IScriptObject::execute() {
  if (!m_vm)
    return false;

  return m_vm->execute();
}

IScriptObject *IScriptObject::make_script_object(String data) {
  if (data.empty())
    return nullptr;

  try {
    std::vector<String> blob;
    String node_data;

    for (auto &ch : data) {
      if (ch == '\n') {
        blob.push_back(node_data);
        node_data.clear();
        continue;
      }

      node_data.push_back(ch);
    }

    String new_data = "<script>";
    new_data += data;
    new_data += "</script>";

    rapidxml::xml_document<char> doc;
    doc.parse<0>(new_data.data());

    String name = doc.first_node()->name();

    const String kScriptMarkup = "script";

    if (name != kScriptMarkup) {
      return nullptr;
    }

    IScriptObject *new_dom = new IScriptObject(doc.first_node());

    new_dom->m_vm = std::make_unique<JSVirtualMachine>(blob);

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
