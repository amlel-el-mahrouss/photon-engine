/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 *			File: Macros.h
 *			Purpose:
 *
 * =====================================================================
 */

#pragma once

#ifndef PHOTON_GET_DATA_DIR
#ifdef PHOTON_WINDOWS
#define PHOTON_GET_DATA_DIR(DIR)            \
	Photon::String DIR = getenv("APPDATA"); \
	DIR += "/.zka/";

#else
#define PHOTON_GET_DATA_DIR(DIR)         \
	Photon::String DIR = getenv("HOME"); \
	DIR += "/.zka/";

#endif

#ifdef PHOTON_PHOTON_OS
#define PHOTON_GET_DATA_DIR(DIR)            \
	Photon::String DIR = EnvGetVar("HOME"); \
	DIR += "\\.zka\\";

#else
#define PHOTON_GET_DATA_DIR(DIR)         \
	Photon::String DIR = getenv("HOME"); \
	DIR += "/.zka/";

#endif
#endif // ifndef PHOTON_GET_DATA_DIR
