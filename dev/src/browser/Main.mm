/*
 * =====================================================================
 *
 *			Photon
 *			Copyright Amlal EL Mahrouss, all rights reserved.
 *
 * =====================================================================
 */

#include <browser/BrowserTab.hpp>
#include <core/Core.hpp>

int main(int argc, char **argv) {
  @autoreleasepool {
    [NSApplication sharedApplication];

    Photon::BrowserTab tab;
    Photon::URL url(argc == 3 ? argv[1] : PHOTON_FILE_PROTOCOL);
    url /= argc == 3 ? argv[2] : "res/pages/new_tab.html";

    tab.load(url);

    [[NSApplication sharedApplication] run];
  }

  return 0;
}