/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <core/IHTTPProtocol.hpp>
#include <iostream>
#include <js/JSVirtualMachine.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

using namespace Photon;

JSVirtualMachine::JSVirtualMachine(std::vector<String> script)
    : m_script(script) {
  PHOTON_INFO("Allocated JavaScript VM...");
}

Bool JSVirtualMachine::execute() {
  if (m_script.empty())
    return false;

  BOOL comment = NO;

  for (auto &line : m_script) {
    if (line.empty())
      continue;

    PHOTON_INFO("Evaluating JavaScript: " + line);

    if (this->pre_eval(line, comment))
      continue;

    //this->eval(op);
  }

  return true;
}

Bool JSVirtualMachine::pre_eval(const String &line, BOOL &comment_ctrl) {
  if (comment_ctrl) {
    if (line.starts_with("*/") || line.ends_with("*/")) {
      comment_ctrl = false;
      return true;
    }
  }

  if (line.starts_with("//"))
    return true;

  if (line.starts_with("/*")) {
    comment_ctrl = YES;
    return true;
  }

  return false;
}

Bool JSVirtualMachine::eval(JSInstruction &opcode) {
  switch (opcode.m_op) {
  case kJSLoadConst:
  case kJSLoadVar:
    m_stack.push_back(m_variables[opcode.m_index]);

    break;
  case kJSStoreVar: {
    JSValue val = m_stack.back();
    m_stack.pop_back();

    if (opcode.m_index < m_variables.size()) {
      m_variables[opcode.m_index] = val;
    } else {
      m_variables.push_back(val);
      opcode.m_index = m_variables.size();
    }

    break;
  }
  case kJSAddExpr: {
    JSValue b = m_stack.back();
    m_stack.pop_back();

    JSValue a = m_stack.back();

    if (std::holds_alternative<Real>(a) && std::holds_alternative<Real>(b))
      m_stack.push_back(std::get<Real>(a) + std::get<Real>(b));
    else if (std::holds_alternative<String>(a) &&
             std::holds_alternative<String>(b))
      m_stack.push_back(std::get<String>(a) + std::get<String>(b));
    else
      throw BrowserError("VM: BUG: Unknown type.");

    break;
  }
  case kJSCallNative: {
    JSValue arg = m_stack.back();
    m_stack.pop_back();

    break;
  }
  case kJSSetProp: {
    JSValue val = m_stack.back();
    m_stack.pop_back();

    break;
  }
  default:
    return false;
  }

  return true;
}