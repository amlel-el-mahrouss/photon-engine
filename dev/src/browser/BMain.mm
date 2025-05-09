#include <browser/BTabProcess.hpp>
#include <core/Engine.hpp>
#include <layout/Layout.hpp>

int main(int argc, char **argv) {
  @autoreleasepool {
	[NSApplication sharedApplication];

    Photon::BTabProcess tab;
    Photon::URL url(argc == 3 ? argv[1] : PHOTON_HTTPS_PROTOCOL);
    url /= argc == 3 ? argv[2] : "homepage.cs.uiowa.edu/~slonnegr/wpj/example.html";

    tab.load(url);
  
	[[NSApplication sharedApplication] run];
  }

  return 0;
}