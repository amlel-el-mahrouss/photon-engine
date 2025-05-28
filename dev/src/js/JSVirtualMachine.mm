/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <js/JSVirtualMachine.hpp>

using namespace Photon;

IJSVirtualMachine::IJSVirtualMachine(std::vector<String> js_blob)
    : mBlob(js_blob) {
  PHOTON_INFO("Allocated JavaScript Context!");
}

Bool IJSVirtualMachine::run_script() {
  if (mBlob.empty()) {
    PHOTON_ERROR("No JavaScript code to run!");
    return false;
  }

  PHOTON_INFO("Running JavaScript code...");

  for (auto &line : mBlob) {
  }

  return true;
}
