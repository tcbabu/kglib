#!/bin/sh
# -*- shell-script -*-
# Copyright (C) 2003-2019 GraphicsMagick Group
#
# This program is covered by multiple licenses, which are described in
# Copyright.txt. You should have received a copy of Copyright.txt with this
# package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
#
# Execute a program with the environment required to execute it using
# files from the source and build directory.  This helps avoid needing to
# install GraphicsMagick before testing it.
#
# Written by Bob Friesenhahn <bfriesen@simple.dallas.tx.us> December 2003
#

top_srcdir='/home/kulina/BUILD/kglib/OpenSource/GraphicsMagick-1.3.36'
top_builddir='/home/kulina/BUILD/kglib/OpenSource/GraphicsMagick-1.3.36'

MAGICK_CODER_MODULE_PATH="${top_builddir}/coders"
MAGICK_CONFIGURE_SRC_PATH="${top_srcdir}/config"
MAGICK_CONFIGURE_BUILD_PATH="${top_builddir}/config"
MAGICK_FILTER_MODULE_PATH="${top_builddir}/filters"
#DIRSEP=':'
DIRSEP=':'

PATH="${top_builddir}/utilities:${PATH}"

if test -n "$VERBOSE"
then
  echo "$@"
fi
env \
  LD_LIBRARY_PATH="${top_builddir}/magick/.libs:${LD_LIBRARY_PATH}" \
  MAGICK_CODER_MODULE_PATH="${MAGICK_CODER_MODULE_PATH}" \
  MAGICK_CONFIGURE_PATH="${MAGICK_CONFIGURE_BUILD_PATH}${DIRSEP}${MAGICK_CONFIGURE_SRC_PATH}" \
  MAGICK_FILTER_MODULE_PATH="${MAGICK_FILTER_MODULE_PATH}" \
  PATH="${PATH}" \
  "$@"
