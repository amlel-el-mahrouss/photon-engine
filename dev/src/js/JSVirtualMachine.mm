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

IJSVirtualMachine::IJSVirtualMachine(std::vector<String> js_blob)
    : mBlob(js_blob) {
  PHOTON_INFO("Allocated JavaScript VM...");
}

Bool IJSVirtualMachine::run_script() {
  if (mBlob.empty())
    return false;

  BOOL comment = NO;

  for (auto &line : mBlob) {
    // JSPP
    if (comment) {
      if (line.starts_with("*/") || line.ends_with("*/"))
        continue;
    }

    if (line.starts_with("//"))
      continue;

    if (line.starts_with("/*")) {
      comment = YES;
      continue;
    }

    // JSCC
    PHOTON_INFO("Evaluating JavaScript...");
  }

  return true;
}