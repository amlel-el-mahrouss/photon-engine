/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */
 
#include <js/JSVirtualMachine.hpp>
#include <core/IHTTPProtocol.hpp>
#include <variant>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>

using namespace Photon;

IJSVirtualMachine::IJSVirtualMachine(std::vector<String> js_blob)
    : mBlob(js_blob) {
  PHOTON_INFO("Allocated JavaScript Context!");
}

Bool IJSVirtualMachine::run_script() {
    if (mBlob.empty()) return false;

    for (auto& line : mBlob) {
      
    }

    return true;
}