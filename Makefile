# kglib/kgdevelop  Makefile
#
#
# This file is part of kulinagraphics
#


###### variable declarations #######

# local fallbacks for missing operating system features
SHELL	:= /bin/bash
PREFIX=/usr
export CFLAGS=-I$(PWD)/include
export LDFLAGS=-L$(PWD)/lib
X11_CFLAGS	="-I$(PWD)/include $(shell pkg-config --cflags x11)"
X11_LIBS 	="$(shell pkg-config --libs x11)"
PKG_CONFIG_PATH_OLD	:=$(PKG_CONFIG_PATH)
PKG_CONFIG_PATH	:=$(PWD)/lib/pkgconfig:/usr/X11R76/lib/pkgconfig
PATH_OLD	:=$(PATH)
PATHNEW	:=$(PWD)/bin:$(PATH_OLD)
PKG_CONFIG_PATH_NEW	:=$(PWD)/lib/pkgconfig:$(PKG_CONFIG_PATH_OLD):/usr/X11R76/lib/pkgconfig


GMFILES = $(foreach part, OpenSource, $(wildcard $(addprefix $(part)/,*.gz)))
GMFILES += $(foreach part, OpenSource, $(wildcard $(addprefix $(part)/,*.bz2)))
GMFILES += $(foreach part, OpenSource, $(wildcard $(addprefix $(part)/,*.xz)))

KGLIBFILES = $(foreach part, kglib, $(wildcard $(addprefix $(part)/,*.[ch])))
KGDEVELOPFILES = $(foreach part, kgdevelop, $(wildcard $(addprefix $(part)/,*.[ch])))

all	: kgdevelop/kgdevelop lib/libkulina.a lib/libgm.a 

lib/libkulina.a	: lib/libgm.a $(KGLIBFILES) 
	echo "PREFIX=$(PWD)">kglib/config.mak
	echo "KULINA=$(PWD)">>kglib/config.mak
	echo "export X11_CFLAGS=\"$(X11_CFLAGS)\"">>kglib/config.mak
	echo "export X11_LIBS=\"$(X11_LIBS)\"">>kglib/config.mak
	$(MAKE) -C kglib 
	$(MAKE) -C kglib  install

lib/libgm.a	: $(GMFILES)
	echo "PREFIX=$(PWD)">OpenSource/config.mak
	echo "KULINA=$(PWD)">>OpenSource/config.mak
	echo "export X11_CFLAGS=\"$(X11_CFLAGS)\"">>OpenSource/config.mak
	echo "export X11_LIBS=\"$(X11_LIBS)\"">>OpenSource/config.mak
	echo "export PKG_CONFIG_PATH=$(PWD)/lib/pkgconfig:/usr/X11R76/lib/pkgconfig">>OpenSource/config.mak
	$(MAKE) -C OpenSource 
	$(MAKE) -C OpenSource install
kgdevelop/kgdevelop	: lib/libgm.a lib/libkulina.a $(KGDEVELOPFILES)
	echo "PREFIX=$(PWD)">kgdevelop/config.mak
	echo "KULINA=$(PWD)">>kgdevelop/config.mak
	$(MAKE) -C kgdevelop
	$(MAKE) -C kgdevelop install

install	: bin/kgdevelop lib/libkulina.a lib/libgm.a
	  mkdir -p /usr/share/kulina
	  cp demo.tar /usr/share/kulina/
	  install -m 755 bin/kgdevelop   /usr/bin
	  install -m 755 lib/libkulina.a /usr/lib
	  install -m 755 lib/libkulina.a /usr/lib
	  install -m 755 lib/libgm.a /usr/lib
	  install -m 755 include/kulina.h /usr/include

tarball	: bin/kgdevelop
	  install -m 755  bin/kgdevelop TARBALL/
	  install -m 755  lib/libkulina.a TARBALL/
	  install -m 755  lib/libgm.a TARBALL/
	  install -m 755  include/kulina.h  TARBALL/
	  cp demo.tar TARBALL/
	  mv TARBALL kulinagraphics
	  tar czf kulinagraphics.tgz  kulinagraphics
	  mv kulinagraphics TARBALL
	  rm -f TARBALL/kgdevelop
	  rm -f TARBALL/libkulina.a
	  rm -f TARBALL/libgm.a
	  rm -f TARBALL/kulina.h
clean	:
	 rm -rf lib/* share/* bin/* man/* include/*
	$(MAKE) -C OpenSource clean
	$(MAKE) -C kglib clean
	$(MAKE) -C kgdevelop clean
	rm -f  TARBALL/kulina.h TARBALL/libgm.a TARBALL/kgdevelop TARBALL/libkulina.a kulinagraphics.tgz
