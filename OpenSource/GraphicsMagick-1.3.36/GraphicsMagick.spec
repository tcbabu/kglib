# Allow for selectively disabling from commandline
%{!?quant:%define quant 8}
%{!?perlm:%define perlm 1}
%{!?cplus:%define cplus 1}

%define base_version 1.3.36

# This is a one line description of the package.
Summary: An X application for displaying and manipulating images.
# This must be the name string from the rpm filename you plan to use.
Name: GraphicsMagick
# This must be the version string from the rpm filename you plan to use.
Version: 1.3.36
# This is the release number for a package of the same version (ie. if
# we make a package and find it to be slightly broken and need to make
# it again, the next package would be release number 2).
Release: 1
License: MIT
# This is a group that the package belongs to in a higher level
# package tool or the Red Hat installer.
Group: X11/Applications/Graphics
# This line points at the HOME location of the pristine source
# file. It is used if you ever want to get the source again or check
# for newer versions.
Source: ftp://ftp.GraphicsMagick.org/pub/%{name}/%{name}-%{version}.tar.bz2
Url: http://www.GraphicsMagick.org/
# This line allows you to specify a directory as the "root" for
# building and installing the new package. You can use this to help
# test your package before having it installed on your machine.
Buildroot: %{_tmppath}/%{name}-%{version}-root
BuildRequires: bzip2-devel, freetype-devel, libjpeg-devel, libpng-devel
BuildRequires: libtiff-devel, zlib-devel
BuildRequires: freetype-devel >= 2.0.1
BuildRequires: libwebp-devel
Requires: bzip2, freetype, libjpeg, libpng, libwebp, zlib

%description
GraphicsMagick(TM) provides a powerful image manipulation and
translation utility. It is capable of displaying still images and
animations using the X Window system, provides a simple interface for
interactively editing images, and is capable of importing selected
windows or the entire desktop. GraphicsMagick can read and write over
88 image formats, including JPEG, TIFF, WMF, SVG, PNG, PNM, GIF, and
Photo CD. It can resize, rotate, sharpen, color reduce, or add special
effects to the image and save the result to any supported format.
GraphicsMagick may be used to create animated or transparent .gifs,
create composite images, create thumbnail images, and much, much,
more.

GraphicsMagick is one of your choices if you need a program to manipulate
and display images. If you want to develop your own applications
which use GraphicsMagick code or APIs, you need to install
GraphicsMagick-devel as well.

%package devel
Summary: Static libraries and header files for GraphicsMagick app development.
Group: X11/Development/Libraries
Requires: %{name} = %{version}-%{release}

%description devel
GraphicsMagick-devel contains the static libraries and header files you'll
need to develop GraphicsMagick applications. GraphicsMagick is an image
manipulation program.

If you want to create applications that will use GraphicsMagick code or
APIs, you need to install GraphicsMagick-devel as well as GraphicsMagick.
You do not need to install it if you just want to use GraphicsMagick,
however.

%if %{perlm}
%package perl
Summary: GraphicsMagick perl bindings
Group: System Environment/Libraries
BuildRequires: perl >= 5.6.0
Requires: %{name} = %{version}-%{release}, perl >= 5.6.0

%description perl
Perl bindings to GraphicsMagick.

Install GraphicsMagick-perl if you want to use any perl scripts that use
GraphicsMagick.
%endif

%if %{cplus}
%package c++
Summary: GraphicsMagick Magick++ library (C++ bindings)
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}

%description c++
This package contains the Magick++ library, a C++ binding to the GraphicsMagick
graphics manipulation library.

Install GraphicsMagick-c++ if you want to use any applications that use
Magick++.

%package c++-devel
Summary: C++ bindings for the GraphicsMagick library
Group: Development/Libraries
Requires: %{name} = %{version}, %{name}-c++ = %{version}
Requires: %{name}-devel = %{version}, bzip2-devel, freetype-devel
Requires: libjpeg-devel, libpng-devel, libtiff-devel, zlib-devel, libxml2-devel

%description c++-devel
GraphicsMagick-devel contains the static libraries and header files you'll
need to develop GraphicsMagick applications using the Magick++ C++ bindings.
GraphicsMagick is an image manipulation program.

If you want to create applications that will use Magick++ code or APIs,
you'll need to install GraphicsMagick-c++-devel, GraphicsMagick-devel and
GraphicsMagick.  You don't need to install it if you just want to use
GraphicsMagick, or if you want to develop/compile applications using the
GraphicsMagick C interface, however.
%endif

%prep
%setup -q

%build
# If you have trouble during the installation phase, then
# uncomment the two lines below.  You may be using an older
# libtool that sometimes has trouble linking the files.

%if %{perlm}
# Maybe this will fix perl installation issues.
if [ -z "`perl -v | grep 5.8`" ]; then
    export PERLOPTS="PREFIX=$RPM_BUILD_ROOT%{_prefix}"
fi
%endif

# This shouldn't be there yet.
rm -f PerlMagick/Makefile.PL

%configure --with-included-ltdl \
        --enable-shared \
	--with-modules --with-frozenpaths \
	--docdir=%{_datadir}/doc/%{name}-%{base_version} \
%if %{perlm}
	--with-perl \
	--with-perl-options="$PERLOPTS" \
%else
	--without-perl \
%endif
%if %{cplus}
	--with-magick-plus-plus \
%else
	--without-magick-plus-plus \
%endif
	--with-quantum-depth=%{quant}
make
%if %{perlm}
make all-perl
%endif

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%if %{perlm}
make DESTDIR=$RPM_BUILD_ROOT install-exec-perl
# Remove unpackaged files.
rm -f `find $RPM_BUILD_ROOT%{_libdir}/perl*/ -name perllocal.pod -type f`
rm -f `find $RPM_BUILD_ROOT%{_libdir}/perl*/ -name .packlist -type f`
%endif

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(644, root, root, 755)
%doc %{_datadir}/%{name}-%{base_version}
%{_libdir}/lib%{name}.so.*
%{_libdir}/lib%{name}Wand.so.*
%dir %{_libdir}/%{name}-%{base_version}
%{_libdir}/%{name}-%{base_version}/config/*.mgk
%dir %{_libdir}/%{name}-%{base_version}/modules-Q%{quant}
%{_libdir}/%{name}-%{base_version}/modules-Q%{quant}/*/*.so
%{_libdir}/%{name}-%{base_version}/modules-Q%{quant}/*/*.la
%attr(755, root, root) %{_bindir}/gm
%attr(644, root, man) %{_mandir}/man1/gm.1.gz
%attr(644, root, man) %{_mandir}/man4/*gz
%attr(644, root, man) %{_mandir}/man5/*gz
%docdir %{_datadir}/doc/%{name}-%{base_version}
%{_datadir}/doc/%{name}-%{base_version}/*

%files devel
%defattr(644, root, root, 755)
%dir %{_includedir}/%{name}/wand
%{_includedir}/%{name}/wand/*
%dir %{_includedir}/%{name}/magick
%{_includedir}/%{name}/magick/*
%{_libdir}/lib%{name}Wand.*a
%{_libdir}/lib%{name}Wand.so
%{_libdir}/lib%{name}.*a
%{_libdir}/lib%{name}.so
%dir %{_libdir}/%{name}-%{base_version}/modules-Q%{quant}
%{_libdir}/pkgconfig/%{name}.pc
%{_libdir}/pkgconfig/%{name}Wand.pc
#%{_bindir}/%{name}-config
%attr(755, root, root) %{_bindir}/%{name}-config
#%{_bindir}/%{name}Wand-config
%attr(755, root, root) %{_bindir}/%{name}Wand-config
%attr(644, root, man) %{_mandir}/man1/%{name}-config.1.gz
%attr(644, root, man) %{_mandir}/man1/%{name}Wand-config.1.gz

%if %{perlm}
%files perl
%defattr(644, root, root, 755)
%dir %{_libdir}/perl*/site_perl/*/*/Graphics
%{_libdir}/perl*/site_perl/*/*/Graphics/Magick.pm
%dir %{_libdir}/perl*/site_perl/*/*/auto/Graphics/Magick
%{_libdir}/perl*/site_perl/*/*/auto/Graphics/Magick/*
%attr(644, root, man) %{_mandir}/man3/*gz
%endif

%if %{cplus}
%files c++
%defattr(644, root, root, 755)
%{_libdir}/lib%{name}++.so.*

%files c++-devel
%defattr(644, root, root, 755)
%{_includedir}/%{name}/Magick++.h
%dir %{_includedir}/%{name}/Magick++
%{_includedir}/%{name}/Magick++/*
%{_libdir}/lib%{name}++.*a
%{_libdir}/lib%{name}++.so
%{_libdir}/pkgconfig/%{name}++.pc
#%{_bindir}/%{name}++-config
%attr(755, root, root) %{_bindir}/%{name}++-config
%attr(644, root, man) %{_mandir}/man1/%{name}++-config.1.gz
%endif

%changelog
* Fri Apr 16 2010 Bob Friesenhahn <bfriesen@graphicsmagick.org> 1.3.13
- Avoided duplicate copies of documentation files.  Put documentation
  into a versioned directory as used by Red Hat and CentOS.  Include
  archive libraries in developer package.

* Tue Apr 13 2010 Bob Friesenhahn <bfriesen@graphicsmagick.org> 1.3.13
- Fixed PerlMagick build and install which was broken by Makefile
  changes.

* Wed Jan 23 2009 Bob Friesenhahn <bfriesen@graphicsmagick.org> 1.3
- The module .la files need to be installed as part of the base
  install or else the modules will fail to load.

* Wed Jan 21 2009 Bob Friesenhahn <bfriesen@graphicsmagick.org> 1.3
-  --enable-lzw option is not longer needed

* Tue Nov 11 2008 Giacomo Tenaglia 1.3 <gtenagli at sf . net>.
- The *-config scripts were listed twice.
- Add definition for %{_datadir}/doc directory

* Wed Jun 02 2004 Bob Friesenhahn <bfriesen@graphicsmagick.org> 1.2
- Install *-config scripts with mode 755 rather than default 644.

* Sat Feb 21 2004 Bob Friesenhahn <bfriesen@graphicsmagick.org> 1.1-1
- Added some comments.
- Eliminated DATE variable.
- Support creating RPMs of snapshots packages.
- Don't remove /usr/include/magick or %{_datadir}/%{name} since they
  are not created anymore.
- Fixed location of .mgk files.

* Mon Jul 28 2003 Bob Friesenhahn <bfriesen@graphicsmagick.org> 1.1-1
- Changed default quantum depth to 8 bits.

* Mon Jun 28 2003 Troy Edwards <vallimar@sexorcisto.net> 1.1-20030628
- Updated to CVS build, added the GraphicsMagickWand files to the spec.
- Only try to remove the unneeded perl package files if we are using
  PerlMagick.

* Mon Jun 09 2003 Troy Edwards <vallimar@sexorcisto.net> 1.0.2-3
- removed libungif as a dependancy
- changed with/without-magick_plus_plus -> with/without-magick-plus-plus
- Use --with-perl-options instead of patching Makefile.in
- Only set a perl prefix if we aren't using perl >= 5.8.0

* Sat Jun 07 2003 Troy Edwards <vallimar@sexorcisto.net> 1.0.2-2
- patch to pass DESTDIR to install-exec-perl since some users
  reported problems

* Sat Jun 07 2003 Troy Edwards <vallimar@sexorcisto.net> 1.0.2-1
- updated to 1.0.2

* Tue May 05 2003 Troy Edwards <vallimar@sexorcisto.net> 1.0-1
- updated to 1.0 Final

* Fri Apr 25 2003 Troy Edwards <vallimar@sexorcisto.net> 1.0-Beta1-1
- updated to 1.0-Beta1

* Mon Oct 22 2002 Troy Edwards <vallimar@sexorcisto.net>
- updated to 1.0.0pre
