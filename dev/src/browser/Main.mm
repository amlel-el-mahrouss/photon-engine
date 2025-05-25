#include <browser/BTab.hpp>
#include <core/Core.hpp>
#include <layout/Layout.hpp>

int main(int argc, char **argv) {
  @autoreleasepool {
    [NSApplication sharedApplication];

      Photon::BTab tab;
      Photon::URL url(argc == 3 ? argv[1] : PHOTON_FILE_PROTOCOL);
      url /= argc == 3 ? argv[2] : "res/pages/new_tab.xhtml";

      tab.load(url);
    
    [[NSApplication sharedApplication] run];
  }

  return 0;
}