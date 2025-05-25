/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <js/JSSpecs.hpp>

using namespace Photon;

IJSVirtualMachine::IJSVirtualMachine(std::vector<String> js_blob)
	: mBlob(js_blob)
{
    PHOTON_INFO("Allocated JavaScript Context!");
}

Bool IJSVirtualMachine::run_script()
{
    PHOTON_INFO("Running script...");

    for (auto& line : mBlob)
    {
        
    }

    return true;
}
