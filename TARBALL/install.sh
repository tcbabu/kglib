#!/bin/bash
  mkdir -p /usr/share/kulina
  cp demo.tar /usr/share/kulina/
  install -m 755  kgdevelop /usr/bin
  install -m 644  libkulina.a /usr/lib/
  install -m 644  libgm.a     /usr/lib/
  install -m 644  kulina.h /usr/include/
