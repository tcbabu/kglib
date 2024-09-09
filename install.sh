#!/bin/bash
  install -m 755  usr/bin/kgdevelop /usr/bin
  install -m 755  usr/lib/libkulina.a /usr/lib/
  install -m 755  usr/lib/libgm.a     /usr/lib/
  install -m 755  usr/include/kulina.h /usr/include/
  tar xzvf fonts.tar -C /usr/share/fonts
