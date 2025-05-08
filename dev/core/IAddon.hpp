/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#pragma once

#include <core/Engine.hpp>

namespace Photon
{
	class IAddon;
	class IAddonProvider;

	class IAddon
	{
		explicit IAddon() = default;
		virtual ~IAddon() = default;

		virtual Bool on_load(IAddonProvider*)	= 0;
		virtual Bool on_unload(IAddonProvider*) = 0;

		virtual Bool on_action(IAddonProvider*) = 0;

		virtual Bool on_start(IAddonProvider*) = 0;
		virtual Bool on_exit(IAddonProvider*)  = 0;
	};
} // namespace Photon
