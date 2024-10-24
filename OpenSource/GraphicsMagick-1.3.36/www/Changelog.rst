2020-12-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: Updates in preparation for the 1.3.36 release.

  - bootstrap: Fix config.guess and config.sub download URLs.

2020-12-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - design/pixel-cache.dot: Fix reported syntax errors.

  - coders/mpc.c (ReadMPCImage): Report correct exception reason.

  - coders/miff.c (ReadMIFFImage): Arbitrarily limit the number of
    header keywords to avoid DOS attempts.
    (ReadMIFFImage): Finish updates to use resource-limited memory
    allocator.
    (WriteMIFFImage): Finish updates to use resource-limited memory
    allocator.

  - coders/mpc.c (ReadMPCImage): Arbitrarily limit the number of
    header keywords to avoid DOS attempts.  Fixes oss-fuzz 28956
    "Timeout - coder\_MPC\_fuzzer".

2020-12-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (AffineEdge): Use MagickDoubleToLong();

  - magick/utility.c (MagickDoubleToLong): New private function to
    convert a 'double' to a 'long' with the minimum amount of harm.

  - magick/segment.c (Classify): Remove variables from function
    global scope that don't need outer scope.

  - coders/jp2.c: JasPer changed its jas\_stream\_ops\_t callback
    interfaces in releases 2.0.19 and 2.0.20.  Revert to providing the
    older interfaces by default, but use a
    MAGICK\_JP2\_NEW\_STREAM\_INTERFACE pre-processor definition to
    support selecting the new interfaces.  We don't know how to
    usefully tell the JasPer version at compile time!  Luckily, using
    the older interfaces only causes a compiler warning rather than a
    run-time issue.

  - coders/mac.c (ReadMACImage): Use size\_t type for 'ldblk' to
    avoid possible overflow.

2020-12-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news to the date December 23, 2020.

2020-12-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/image.c (AllocateImage): Satisfy conditions for
    DestroyImage() as soon as possible and use it for clean-up on
    error.  Added more error checks.
    (CloneImage): Satisfy conditions for DestroyImage() as soon as
    possible and use it for clean-up on error.  Don't attempt to copy
    colormap if colors is zero.  Added more error checks.
    (DestroyImage): Assure that we can destroy a partially-constructed
    Image.

  - magick/effect.c (BlurImage): Fix null pointer dereference if
    image failed to be created.
    (DespeckleImage): Fix null pointer dereference if image failed to
    be created.
    (EnhanceImage): Fix null pointer dereference if image failed to be
    created.
    (GaussianBlurImage): Fix null pointer dereference if image failed
    to be created.
    (MedianFilterImage): Fix null pointer dereference if image failed
    to be created.
    (MotionBlurImage): Fix null pointer dereference if image failed to
    be created.
    (ReduceNoiseImage): Fix null pointer dereference if image failed to
    be created.
    (ShadeImage): Fix null pointer dereference if image failed to be
    created.
    (SharpenImage): Fix null pointer dereference if image failed to be
    created.
    (SpreadImage): Fix null pointer dereference if image failed to be
    created.

2020-12-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/jp2.c (BlobWrite): Update Jasper stream OPs callback
    function signatures to exactly match latest jas\_stream\_ops\_t
    definition.  This avoids an annoying warning when using Jasper
    2.0.23 but now causes annoying warnings when using 2.0.12 or
    1.900.1. There does not appear to be a useful way to determine the
    Jasper numeric version (only a C string is available) from its
    header files.

  - magick/decorate.c (FrameImage): Skip attempting to render top or
    bottom of ornamental border if its height is zero.

  - magick/image.c (CloneImage): Set image signature right away in
    case it needs to be destroyed while it is being constructed.

  - wand/drawtest.c (main): MagickGetFilename() allocates a new
    string so make sure to free it.

  - tests/constitute.c (main): Destroy ExceptionInfo to avoid memory
    leak if an exception was thrown.

  - magick/effect.c (EdgeImage): Fix null pointer dereference if
    edge image failed to be created.

  - magick/compress.c (HuffmanEncode2Image): Fix error handling
    issues.

  - magick/command.c (CompareImageCommand): Fix memory leaks when an
    input image failed to be read.
    (CompositeImageCommand): Fix memory leaks when an input image
    failed to be read.

  - coders/fax.c (WriteFAXImage): Fix error handling.

  - coders/mpc.c (ReadMPCImage): Use correct deallocator for page
    geometry.  Fixes oss-fuzz 28853 "Heap-buffer-overflow READ {\*} -
    \_MagickReallocateResourceLimitedMemory".

2020-12-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/yuv.c: Use resource-limited memory allocator.

  - coders/xwd.c: Use resource-limited memory allocator.

  - coders/xpm.c: Use resource-limited memory allocator.

  - coders/xcf.c: Use resource-limited memory allocator.

  - coders/xbm.c: Use resource-limited memory allocator.

  - coders/wpg.c: Use resource-limited memory allocator.

  - coders/viff.c: Use resource-limited memory allocator.

  - coders/vicar.c: Use resource-limited memory allocator.

  - coders/uil.c: Use resource-limited memory allocator.

  - coders/txt.c: Use resource-limited memory allocator.

  - coders/topol.c: Use resource-limited memory allocator.

  - coders/tim.c: Use resource-limited memory allocator.

  - coders/tiff.c: Use resource-limited memory allocator.

  - coders/tga.c: Use resource-limited memory allocator.

  - coders/sun.c: Use resource-limited memory allocator.

  - coders/sgi.c: Use resource-limited memory allocator.

  - coders/sfw.c: Use resource-limited memory allocator.

  - coders/rle.c: Use resource-limited memory allocator.

  - coders/rla.c: Use resource-limited memory allocator.

  - coders/rgb.c: Use resource-limited memory allocator.

  - coders/psd.c: Use resource-limited memory allocator.

  - coders/ps3.c: Use resource-limited memory allocator.

  - coders/ps2.c: Use resource-limited memory allocator.

  - coders/pnm.c: Use resource-limited memory allocator.

  - coders/pdf.c: Use resource-limited memory allocator.

  - coders/pdb.c: Use resource-limited memory allocator.

  - coders/pcl.c: Use resource-limited memory allocator.

  - coders/pcd.c: Use resource-limited memory allocator.

  - coders/palm.c: Use resource-limited memory allocator.

  - coders/mtv.c: Use resource-limited memory allocator.

  - coders/mpc.c: Use resource-limited memory allocator.

  - coders/meta.c: Use resource-limited memory allocator.

  - coders/map.c: Use resource-limited memory allocator.

  - coders/jpeg.c: Use resource-limited memory allocator.

  - coders/jp2.c: Use resource-limited memory allocator.

  - coders/jnx.c: Use resource-limited memory allocator.

  - coders/icon.c: Use resource-limited memory allocator.

  - coders/hrz.c: Use resource-limited memory allocator.

  - coders/histogram.c: Use resource-limited memory allocator.

  - coders/gray.c: Use resource-limited memory allocator.

  - coders/fpx.c: Use resource-limited memory allocator.

  - coders/emf.c: Use resource-limited memory allocator.

  - coders/dpx.c: Use resource-limited memory allocator.

  - coders/dps.c: Use resource-limited memory allocator.

  - coders/dcm.c: Use resource-limited memory allocator.

  - coders/cut.c: Use resource-limited memory allocator.

  - coders/cmyk.c: Use resource-limited memory allocator.

  - coders/cineon.c: Use resource-limited memory allocator.

  - coders/avs.c: Use resource-limited memory allocator.

  - coders/art.c: Use resource-limited memory allocator.

  - coders/pcx.c: Use resource-limited memory allocator.

  - coders/mac.c: Use resource-limited memory allocator.

  - coders/pict.c: Use resource-limited memory allocator.

  - magick/memory.c (\_MagickReallocateResourceLimitedMemory): Add a
    'clear' parameter which indicates that freshly allocated memory
    should be zeroed.  Added "Cleared" versions of the private managed
    memory macros and updated all managed memory macros to exclusively
    use this function.

2020-12-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - Update Automake to 1.16.3 and bootstrap to pick up latest
    config.guess and config.sub.

2020-12-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ImportRLEPixels): Change from C assertion to
    exception report.  Fixes oss-fuzz 28703 "ASSERT · ((quantum\_type
    == IndexQuantum) && (image->storage\_class ...".
    (ReadMIFFImage): Read Gray DirectClass image as PseudoClass so it
    has a colormap, and we have a RLE decode implementation for it.

2020-12-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/paint.c (OpaqueImage): Changing the image storage class
    is not required.

2020-12-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/paint.c (OpaqueImage): Assure that image type is promoted
    as required based on fill color.  Fixes unexpected results
    discovered by Stuart McDonagh and reported via the
    graphicsmagick-help mailing list on December 14, 2020.

2020-12-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Set '[MVG]' image attribute at
    appropriate places outside of DrawImage() since DrawImage()
    sometimes recurses into itself, trashing the image attribute.  One
    example of recursion is in the text annotation code.

  - coders/svg.c (ReadSVGImage): Properly support 'ping' mode so
    'identify' works as expected.

  - magick/render.c (InsertAttributeIntoInputStream): Provide a more
    useful diagnostic for when a "use" or "class" argument id is not
    defined.

2020-12-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Fix regression when parsing "mask"
    which was added by changeset 16305:f33a0fb3d8e4 on July 15, 2020
    since the last formal release.  This impacts MVG and SVG.

2020-12-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/INSTALL-unix.rst: Document the '--disable-compressed-files'
    configure option, which was added on July 15th.

2020-12-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magic.c: Don't send files which test positive for PCL to
    the HPGL delegate, which is normally 'hp2xx'.  Fixes SourceForge
    bug 607 "Slow to convert HP PCL printer data".

2020-12-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Use unique image attribute space
    for MVG symbols.  Fixes oss-fuzz 28111 "Timeout -
    coder\_MVG\_fuzzer", oss-fuzz 28170 "Stack-overflow - DrawImage",
    and oss-fuzz 28292 "Integer-overflow - DrawPolygonPrimitive".

2020-12-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Verify that affine scaling factors
    are not zero.  Fixes oss-fuzz 28293 "Divide-by-zero -
    InverseAffineMatrix".
    (DrawPolygonPrimitive): Thread error status check was at wrong
    scope, resulting in code executing when it should have quit.

2020-12-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick\_types.h.in: Stop trying to define PTRDIFF\_MAX.

2020-11-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick\_types.h.in: Provide PTRDIFF\_MAX for Visual Studio
    if it is missing.

  - fuzzing/oss-fuzz-build.sh: Disable old JPEG support in libtiff.

  - coders/mat.c (ReadMATImage): Use resource-limited memory
    allocator.
    (WriteMATLABImage): Use resource-limited memory allocator.

2020-11-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news to the date November 28, 2020.

  - coders/png.c (ReadOneJNGImage): Verify and enforce
    Alpha\_compression\_method values.  Request that color and alpha
    decoders return just one frame.  Force decoder format to disable
    auto-detection.  Assume that coder messed up and might have
    returned more than one frame.  Fixes oss-fuzz 28013 "Indirect-leak
    . MagickMalloc".

  - magick/memory-private.h (MagickReallocateResourceLimitedMemory):
    Fix typo in macro definition which resulted in a memory
    reallocation leak!

  - Magick++/lib/Magick++/Drawable.h: Decided to continue using
    std::unary\_function if C++ version is less than C++'17 since
    otherwise it may be changing an interface.

2020-11-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/gif.c (ReadGIFImage): Use resource-limited memory
    allocator when reading the comment extension.

  - Magick++/lib/Magick++/Drawable.h: Remove inheritance from
    std::unary\_function, which was removed in C++'17.

  - coders/webp.c (ReadWEBPImage): Use resource-limited memory
    allocator.
    (WriteWEBPImage): Use resource-limited memory allocator.

  - coders/jbig.c (WriteJBIGImage): Use resource-limited memory
    allocator.

  - coders/fits.c (ReadFITSImage): Use resource-limited memory
    allocator.
    (WriteFITSImage): Use resource-limited memory allocator.

  - coders/dib.c (ReadDIBImage): Use resource-limited memory
    allocator.
    (WriteDIBImage): Use resource-limited memory allocator.

  - coders/bmp.c (ReadBMPImage): Use resource-limited memory
    allocator.
    (WriteBMPImage): Use resource-limited memory allocator.

2020-11-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Improve RGBATiledMethod progress
    monitor so it reports more steps.
    (ReadTIFFImage): Improve TiledMethod progress monitor so it
    reports more steps.

  - fuzzing/utils.cc (class MagickState): Enable tracing of
    exception events in order to help discover the origin of errors.
    If too much output comes out, then this will be removed.

  - magick/render.c (ConvertPathToPolygon): Attempt to fix leak of
    'points' on memory allocation failure.

2020-11-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (ConvertPathToPolygon): Make sure not to leak
    points from added Edge.  Fixes oss-fuzz 27608 "Direct-leak in
    \_MagickReallocateResourceLimitedMemory".
    (DrawDashPolygon): Place an aribrary limit on stroke dash polygon
    unit maximum length in order to avoid possibly rendering
    "forever".  Addresses oss-fuzz 24236 "Timeout in
    coder\_MVG\_fuzzer".

2020-11-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawPolygonPrimitive): Try to minimize the
    impact of too many threads due to replicated data until such time
    as the data structures can be re-designed to directly support
    threading.

2020-11-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/Hg.rst: Describe how to clone the repository from
    SourceForge using the ssh protocol rather than https.

  - coders/ps.c (WritePSImage): Fix problem when writing PseudoClass
    image with a colormap larger than two entries as bilevel.
    Previous implementation was assuming that the colormap would only
    include two entries for a monochrome image, but many entries may
    exist in the colormap which were never used.  Fixes SourceForge
    issue #635 "gm convert failure from .pgm to .eps".

2020-11-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/utils.cc (class MagickState): Set DiskResource limit to
    zero so that pixel cache won't spill over to using temporary
    files.

2020-11-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update the news to the date November 16, 2020.

2020-11-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/svg.c (ReadSVGImage): Fix memory leak due to CDATA block,
    and some other possible small leaks.

  - magick/magick.c (InitializeMagickEx): Set C pre-processor
    definition USE\_GLIBC\_MTRACE to 1 in order to enable Linux mtrace
    support.

  - magick/render.c (ConvertPathToPolygon): Fix memory leak upon
    memory reallocation failure.  Addresses oss-fuzz 27351
    "Direct-leak in \_MagickReallocateResourceLimitedMemory".

  - magick/memory.c (\_MagickReallocateResourceLimitedMemory): Return
    pointer to the allocation similar to realloc() and do not
    automatically free existing memory upon allocation failure.

2020-11-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - common.shi.in: Apply some resource limits while running the test
    suite.
    (Q8\_MEMORY\_LIMIT): Set the test suite memory limit to 128MB for
    Q8, or 256MB for Q16, or 512MB for the Q32 build.
    (MAGICK\_LIMIT\_DISK): Set the test suite disk space limit to 0 to
    avoid spilling over into disk files when the memory limit runs
    out.

  - coders/miff.c (WriteMIFFImage): Update to use resource-limit
    respecting memory allocators.

2020-11-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/miff.c (ReadMIFFImage): Update to use resource-limit
    respecting memory allocators.

  - magick/render.c (DrawImage): Update to use resource-limit
    respecting memory allocators.

  - magick/memory.c (\_MagickReallocateResourceLimitedMemory): Add
    new private interfaces for allocating private memory while
    respecting resource limits.

2020-10-25  Bob Friesenhahn  <bfriesen@bobsdell>

  - magick/render.c (DrawImage): Reject pattern image with a
    dimension of zero.  Fixes oss-fuzz issue 26382
    "graphicsmagick:coder\_MVG\_fuzzer: Floating-point-exception in
    DrawPrimitive".

2020-10-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ConstituteImage): Set image depth
    appropriately based on the storage size specified by StorageType
    and QuantumDepth.

2020-10-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawPrimitive): Use DestroyImageList() to
    destroy composite\_image since it may be a list.  Fixes oss-fuzz
    25247 "Indirect-leak in MagickMalloc".
    (DrawPrimitive): Add ImageInfo properties to request only
    returning the first frame if the in-line image is a list.  Also,
    add a missing DestroyImageList() request if multiple-frames were
    returned.

  - magick/transform.c (TransformImage): Use ReplaceImageInList()
    replace transformed image in list.

  - magick/list.c (ReplaceImageInList): Remove previous and next
    references from removed image before destroying it.

  - magick/render.c (DrawClipPath): Remove break statement so that
    added clip-mask image is initialized properly and rendered-on as
    expected.  Thanks to László Böszörményi for reporting this problem
    prior to release.

2020-10-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac (AC\_PROG\_CC\_STDC): AC\_PROG\_CC\_STDC is no longer
    required since AC\_PROG\_CC now provides its useful function.
    AC\_PROG\_CC\_STDC is marked as obsolete after Autoconf 2.69.
    Quote all arguments to m4 macros.

2020-09-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Update syntax to avoid using deprecated syntax
    according to Autoconf 2.69.

2020-09-21  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/webp.c (ReadWEBPImage): Use SetImageProfile() rather than
    AppendImageProfile().

2020-09-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/magick\_wand.c (MagickSetSamplingFactors): Correct
    formatting of sampling factors string.  Fixes SourceForge issue
    633 "MagickSetSamplingFactors() API mismatch - comma separated
    values instead of 1x1 ".

2020-09-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawPrimitive): Improve error checking related
    to ImagePrimitive.

  - magick/resize.c (ResizeImage): If CloneImage() of resize\_image
    to source\_image fails then free source\_image allocation before
    returning in order to prevent memory leak.

  - magick/image.c (CloneImage): Free clone\_image allocation if
    ImgExtra allocation fails in order to prevent memory leak.  Fixes
    oss-fuzz 25342 "Indirect-leak in MagickMalloc".
    (SetImageOpacity): SetImageOpacity() now returns error status
    since it is possible for it to fail.

2020-09-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Ignore corrupt whitepoint and
    primary chromaticities tags.  Fixes oss-fuzz issue 25507
    "Divide-by-zero in DoubleToRational".  The divide by zero is
    actually in libtiff, but the bad values from the input file were
    propagated through GraphicsMagick.

2020-09-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/analyze.c (GetImageBoundingBox): Use solution proposed by
    Troy Patteson to solve SourceForge issue 345 "MagickTrimImage with
    extreme fuzz can produce image with negative width".

2020-08-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (ReadTIFFImage): Apply the same resource limits to
    TIFF tile sizes as apply to the image itself.  Fixes oss-fuzz
    issues 24523 "Timeout in coder\_TIFF\_fuzzer" and 24810 "Timeout in
    coder\_PTIF\_fuzzer".

2020-08-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Add --without-gdi32 configure option to support
    disabling use of the Microsoft Windows gdi32 library if it is not
    wanted.

2020-08-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Remove the assumption that a native Windows build
    means that Ghostscript may be available so that MinGW tests which
    depend on Ghostcript are attributed proper XFAIL status by the
    test suite.

2020-08-10  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.c (MagickCondSignal): Explicitly initialize 'oact'
    prior to calling sigaction() in order to attempt to surmount
    apparent oss-fuzz framework issue.

2020-08-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/delegate.c, magick/magick.c, magick/nt\_base.c: Fix
    compilation errors under MinGW when Ghostscript support is
    disabled.

2020-08-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/nt\_base.c: Fix compilation issue noticed under MinGW.

  - magick/render.c (DrawImage): Handle the case that
    ExtractTokensBetweenPushPop() can return NULL.  Fixes oss-fuzz
    24659 "Null-dereference READ in DrawImage".

  - magick/magick.c (MagickCondSignal): Re-implement to handle the
    case where a new-style 'siginfo' signal handler was previously
    registered, as well as the legacy type.  This may address oss-fuzz
    24690 "Use-of-uninitialized-value in MagickCondSignal".

2020-07-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - wand/drawtest.c: Use structured error handling and report all
    output to stderr so it does not screw up TAP tests.

  - magick/render.c (DTOLONG\_MIN): Correct 32-bit definition of
    DTOLONG\_MIN.

  - wand/wandtests.tap: Wand drawtest requires FreeType.

  - NEWS.txt: Update with changes up to 2020-07-26.

  - VisualMagick/magick/magick\_config.h.in (HasGS): Default HasGS to
    enabled.

  - configure.ac: Add a --without-gs configure option to disable
    reading PS, EPS, and PDF formats via an external Ghostscript
    delegate program.  This is intended as an absolute security
    measure for sites that want to be assured to avoid executing
    Ghostscript even though it is installed on the system.  Removal of
    PS and PDF reading support breaks reading other formats which are
    handled by executing an external program to first convert to PS or
    PDF formats.

  - magick/delegate.c (InvokePostscriptDelegate): Use HasGS to
    enable use of the Ghostscript delegate.  Change the existing
    legacy HasGS ifdefs to HasGSLIB.

2020-07-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Fix compilation error when
    COMPRESSION\_WEBP is not defined.

2020-07-20  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - configure.ac: Fix enableval syntax for
    --disable-compressed-files.

2020-07-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (CompareImageCommand): Merge changeset by
    谢致邦 (XIE Zhibang) which adds 'matte' support to the compare
    command. However, substantially reduce the amount of changes
    by avoiding adding a new public function.  Documentation
    regarding how 'compare' uses this option is also added.

  - magick/command.c: Merge changeset by谢致邦 (XIE Zhibang)
    regarding Some duplicate "verbose" should be "version".

  - configure.ac, magick/blob.c: Merge changeset by Przemysław
    Sobala regarding "Configure: add --with(out)-compressed-files
    option".  The configure option was changed to
    --disable-compressed-files during the merge since it is more
    appropriate.

2020-07-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update with changes up to 2020-07-15.

  - magick/render.c (DrawImage): Improve error handling so errors
    are returned when they should be.  Fixes oss-fuzz 24117
    "Stack-overflow in DrawImage" and oss-fuzz 24126 "Timeout in
    coder\_MVG\_fuzzer".  Restore the original behavior of
    DrawClipPath() when there is no matching clip-path attribute.

2020-07-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update with changes up to 2020-07-12.

2020-07-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/xwindow.c (MagickXVisualColormapSize): Fix UBSAN integer
    overflow warning.

  - magick/render.c (DrawClipPath): Report only a warning if there
    is no clip mask.
    (ExtractTokensBetweenPushPop): Verify that the expected/required
    pop statement is indeed found.  Fixes oss-fuzz 23498 "Timeout in
    coder\_MVG\_fuzzer".

2020-06-14  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/constitute.c (ReadImage): Improve error handling related
    to ImageToFile().

  - magick/image.c (SetImageInfo): Improve error handling related to
    ImageToFile().

  - coders/mat.c: Check MagickFindRawImageMinMax() return status.

  - magick/constitute.c (MagickFindRawImageMinMax): Verify that the
    original seek position was restored.

2020-06-13  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Apply stricter range limits when
    converting a double to a long in order to avoid integer overflow.
    Fixes oss-fuzz 23304 "Integer-overflow in DrawImage".
    (DrawClipPath): If there is no matching clip-path attribute then
    return an informative error.  Fixes oss-fuzz 23187 "Stack-overflow
    in DrawImage" which is actually a case of DrawImage() /
    DrawClipPath() recursion.

2020-06-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (UnpackWPGRaster): Fix oss-fuzz 23042
    "Heap-buffer-overflow in ImportGrayQuantumType" and oss-fuzz
    "Heap-buffer-overflow in InsertRow" which are both from the same
    cause.

2020-06-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (ClipCacheNexus): Change x and y variables
    to unsigned type.

2020-05-31  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): WebP compression only supports a
    depth of 8.  Fixes oss-fuzz 22560 "Use-of-uninitialized-value in
    GammaToLinear".

2020-05-30  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/wpg.c (ReadWPGImage): Terminate reading when a pixel
    cache resource limit is hit rather than moving on to heap buffer
    overflow.  Fixes oss-fuzz 20045, 20318, 21956

  - coders/png.c (ReadMNGImage): If the image width is 1, then X
    magnification is done by by simple pixel replication.  If the
    image height is 1, then Y magnification is done by simple pixel
    replication.  Fixes oss-fuzz issue 19025 "Heap-buffer-overflow in
    ReadMNGImage" and oss-fuzz issue 19026 "ASSERT: yy < (long)
    large\_image->rows". It appears that CERT has assigned
    CVE-2020-12672 for oss-fuzz issue 19025.  Note that the heap
    overwrite is only one byte.

2020-05-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update with changes up to 2020-04-23.

2020-04-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadDPXImage): Support dpx:swap-samples-read
    define which behaves similar to dpx:swap-samples, but is only
    applied when reading.  This provides for use when there is both
    reading and writing in the same operation.
    (WriteDPXImage): Support dpx:swap-samples-write define which
    behaves similar to dpx:swap-samples, but is only applied when
    writing.  This provides for use when there is both reading and
    writing in the same operation.

2020-04-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick: Fix remaining GCC 10 warnings.

2020-04-17  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/transform.c (GetImageMosaicDimensions): Mark function as pure.

  - magick/effect.c (GetNonpeakMedianList): Mark function as pure.

  - coders/fits.c (InsertRowHDU): Fix scary-sounding GCC 10 warning,
    which is actually benign.

  - config/config.sub: Update to latest config.sub

  - config/config.guess: Update to latest config.guess.

  - Makefile.am: Update to Automake 1.16.2

2020-04-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (ReadRowSamples): Simplify 10-bit packed decoding.
    (WriteRowSamples): Simplify 10-bit packed encoding.

  - coders/locale.c (ReadConfigureFile): Ignore comment element if
    it was not found or is too short.

  - magick/pixel\_cache.c (ReadCacheIndexes): If SetNexus() has
    previously failed to allocate the staging buffer and thus reported
    an exception to the user, then ReadCacheIndexes() should report an
    error rather than blundering into copying indexes data to a null
    pointer.

  - magick/effect.c (AdaptiveThresholdImage): Assure that we don't
    attempt to write to output pixels if they have not been selected
    yet.

  - magick/utility.c (ExpandFilenames): Properly handle NULL
    filelist and NULL filelist entries.
    (GetGeometry): Assure that there is no one-character stack read
    overflow when reading the geometry buffer.

2020-03-29  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Restore xz to oss-fuzz build due to
    build problems getting worked out.

2020-03-28  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh (MAGICK\_LIBS): Remove mention of
    liblzma.a in the oss-fuzz build until its build problems get
    worked out.

2020-03-27  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - fuzzing/oss-fuzz-build.sh: Skip building xz in the oss-fuzz
    build until its build problems get worked out.

2020-03-25  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/log.c (InitializeLogInfoPost): Don't load log.mgk if
    logging is already configured to use MethodOutput.

2020-03-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/log.c (InitializeLogInfoPost): Mark that logging is
    configured, regardless of if "log.mgk" was discovered.

2020-03-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - VisualMagick/magick/magick\_config.h.in: ProvideDllMain is now
    disabled by default since it causes InitializeMagick() to be
    invoked prior to when the program's main() routine is called,
    thereby blocking configuration activities or use of
    InitializeMagickEx().  With this change it is even more imperative
    that InitializeMagick() be explicitly invoked by all programs
    using GraphicsMagick.

  - magick/log.c (LogMagickEventList): Always use/respect the
    configured log format as might be obtained from "log.mgk" or
    SetLogDefaultFormat().

  - magick/utility.c (MagickFormatString): Return the size of the
    formatted string.
    (MagickFormatStringList): Return the size of the formatted string.
    (FormatString): Return the size of the formatted string.
    (FormatStringList): Return the size of the formatted string.

2020-03-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/api/types.rst: Improved types documentation and added more
    hyperlinks.

  - scripts/format\_c\_api\_doc.py: Add hyperlinks for 'LogMethod' and
    'LogOutputType' type documentation.

  - Magick++/lib/Image.cpp (SetLogDefaultEventType): New C++ function to
    forward to C interface.
    (SetLogDefaultGenerations): New C++ function to forward to C
    interface.
    (SetLogDefaultLimit): New C++ function to forward to C interface.
    (SetLogDefaultFormat(): New C++ function to forward to C
    interface.
    (SetLogDefaultLogMethod): New C++ function to forward to C
    interface.
    (SetLogDefaultFileName): New C++ function to forward to C
    interface.
    (SetLogDefaultOutputType): New C++ function to forward to C
    interface.

  - magick/log.c (SetLogDefaultEventType): New function to support
    setting the default set of events which will result in a log
    event.
    (SetLogDefaultGenerations): New function to specify the maximum
    number of log files maintain before circulating back to overwrite
    the first name.
    (SetLogDefaultLimit): New function to specify the maximum number
    of logging events which may occur before creating a new log file.
    (SetLogDefaultLogMethod): New function to provide a call-back
    function to be invoked for each log event when the logging method
    type is MethodOutput.
    (SetLogDefaultOutputType): New function to set the logging output
    destination.
    (SetLogDefaultFormat): New function to provide the format of the
    logging output.
    (SetLogDefaultFileName): New function to provide the file name,
    or file path, to be written to for each log event.
    (InitializeLogInfo): If a default logging callback was provided
    via SetLogDefaultLogMethod() then skip searching for "log.mgk".
    In this case it is assumed that the API user has already changed
    any other logging default which would have been updated by
    "log.mgk" so it would be harmful to search for it, or read from
    it.

2020-03-10  Troy Patteson  <troyp@ieee.org>

  - coders/png.c (WriteOnePNGImage): Don't skip optional Exif
    identifier code if it isn't present.

2020-03-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/pixel\_cache.c (ModifyCache): Destroy clone\_image.cache if
    ClonePixelCache() reports failure.  Fixes oss-fuzz 20871
    "graphicsmagick:coder\_MVG\_fuzzer: Direct-leak in
    MagickMallocAligned".

  - magick/log.c (LogMagickEventList): Prepare source module base
    name more efficiently.  Move MethodOutput implementation to the
    front so it is not filtered by other active blocks.
    (LogMagickEventList): Cache broken-down time structure in LogInfo
    and recompute only when needed.

2020-03-07  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/resize.c (HorizontalFilter): Improve tracing.
    (VerticalFilter): Improve tracing.
    (ResizeImage): Improve tracing.

  - www/api/api.rst: Add functions from log.c and render.c.

  - magick/log.c (DestroyLogInfo): DestroyLogInfo is no longer
    marked MagickExport.

2020-03-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/api.h: Add "magick/enum\_strings.h" to API headers.
    Requested by Przemysław Sobala via posting to the
    graphicsmagick-help mailing list on 2020-02-27.

  - scripts/html\_fragments.py: Automatically generate HTML footer
    content and include commented HTML fragment which may be
    substituted with SF tracker for SourceForge web site.

2020-02-23  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - version.sh: Updates in preparation for the 1.3.35 release.

  - www/INSTALL-windows.rst: Update Windows installation and build
    documentation.

2020-02-22  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - NEWS.txt: Update with News since previous release.

  - magick/magick.c (InitializeMagickSignalHandlers): This private
    implementation function is now a static function as it should have
    been.
    (InitializeMagickEx): New function which may be used in place of
    InitializeMagick() to initialize GraphicsMagick.  This
    initialization function returns an error status value, may update
    a passed ExceptionInfo structure with error information, and
    provides an options parameter which supports simple bit-flags to
    tailor initialization.  The signal handler registrations are
    skipped if the MAGICK\_OPT\_NO\_SIGNAL\_HANDER flag is set in the
    options.

2020-02-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/magick.c (MagickToMime): Add a MIME translation for
    "jpg".  Issue reported by Pro Turm.

2020-02-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - www/INSTALL-windows.rst: Add quoting to avoid losing backslashes
    in Windows paths.

2020-02-16  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/common.h: Add missing unsupported handling for some
    recently added GCC/Clang attributes.

  - magick/: Move all remaining private implementation code in
    public headers which is guarded by MAGICK\_IMPLEMENTATION into
    private headers, which are never installed.

2020-02-15  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/tiff.c (WriteTIFFImage): Evidence suggests that large
    strip sizes improve performance by reducing the number of I/Os.
    The defaults suggested by libtiff are way to small for today's
    images and computers.  Default TIFF strip sizes so that each
    uncompressed strip consumes up to 1MiB of memory, or 4MiB for FAX
    oriented codecs, or based on LZMA compression level when using
    LZMA compression.  The default size may be adjusted via the
    TIFF\_BYTES\_PER\_STRIP preprocessor definition.

2020-02-09  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c ZeroFillMissing data will never been triggered when
    y>=image->rows.

2020-02-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Limit pattern dimensions by
    LONG\_MAX rather than ULONG\_MAX since this seems more likely to
    avoid arithmetic overflows later on.

2020-02-09  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - coders/wpg.c Check for exception in image.

2020-02-09  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/command.c (VersionCommand): Add Google perftools tcmalloc
    to the available feature support.

  - www/INSTALL-unix.rst: Include some information about building
    with MSYS2.

  - coders/png.c (ReadOnePNGImage): Eliminate compilation warnings
    about signed/unsigned comparisons.

  - magick/image.c: Remove private global string constants, and one
    private global unsigned long constant, from the library ABI.
    Since the global constants were declared via a private header and
    only used within the GraphicsMagick build, removing these does not
    impact the public ABI.  The globals removed are BackgroundColor,
    BorderColor, DefaultTileFrame, DefaultTileGeometry,
    DefaultTileLabel, ForegroundColor, HighlightColor, MatteColor,
    PSDensityGeometry, PSPageGeometry, and DefaultCompressionQuality.

2020-02-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Apply draconian pattern
    specification offset and dimension validations.  Hopefully there
    is no impact to usability.  If so please report it as a bug.
    Fixes oss-fuzz 20586 "graphicsmagick:coder\_MVG\_fuzzer:
    Integer-overflow in DrawPolygonPrimitive".

  - coders/svg.c (ReadSVGImage): Fix dereference of NULL pointer
    when stopping image timer.

2020-02-06  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c (DecodeImage): Allocate extra scanline memory to
    allow small RLE overrun.  Fixes oss-fuzz 20271
    "graphicsmagick:coder\_PICT\_fuzzer: Heap-buffer-overflow in
    ExpandBuffer" and 20272 "graphicsmagick:coder\_PICT\_fuzzer:
    Heap-buffer-overflow in DecodeImage".

  - PerlMagick/t/wmf/read.t: Update WMF reference images.  Relax
    test requirements for ski.wmf.

  - locale/C.mgk: Correct error message associated with
    "UnsupportedNumberOfRows".  Patch was submitted by Thorsten
    Alteholz via private email on 2020-02-05.

2020-02-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/topol.c: Include magick/magick\_endian.h.

2020-02-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick, coders, wand: Added copious casts to avoid possible
    integer overflows in the Microsoft Windows 64-bit build, where
    sizeof(long) < sizeof(size\_t).

2020-01-26  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.h ("PrimitiveInfo"): Change PrimitiveInfo
    coordinates from type 'unsigned long' to 'size\_t'.

2020-01-24  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/gradient.c (GradientImage): Warnings reduction, plus note
    about incorrect diagonal gradients math.

2020-01-20  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - VisualMagick\configure\configure.cpp Option /arch:SSE2 is
    available only for 32 bit build.

2020-01-19  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pcd.c (DecodeImage): Assure that pcd\_length gets
    initialized with something.

  - Magick++/lib/Options.cpp (strokeDashArray): Add needless check
    for \_drawInfo->dash\_pattern null in order to make static analysis
    happy.

  - magick/render.c (DestroyPolygonInfo): Make sure to not
    dereference a null edges pointer.

  - coders/pdb.c (WritePDBImage): Make sure that null comment value
    is not dereferenced.

  - coders/vid.c (ReadVIDImage): Make sure that
    ThrowVIDReaderException does not dereference a null pointer.

  - magick/quantize.c (ClassifyImageColors): Fix error handling so a
    null pointer won't be consumed after a memory allocation failure.
    Changed the location of some variable declarations and added some
    comments.

2020-01-18  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/caption.c (ReadCAPTIONImage): Assure that metrics are
    initialized.

  - magick/pixel\_cache.c (DestroyThreadViewSet): Check if views
    pointer is not null before destroying views.

  - coders/xpm.c (ReadXPMImage): Properly detect the case where the
    XPM colormap is not fully initialized.

  - coders/pict.c (DecodeImage): Fix heap buffer over-reads. Fixes
    oss-fuzz issue 20053 "graphicsmagick:coder\_PICT\_fuzzer:
    Heap-buffer-overflow in ExpandBuffer" and oss-fuzz issue 20048
    "graphicsmagick:coder\_PICT\_fuzzer: Heap-buffer-overflow in
    DecodeImage".  Both of these oss-fuzz issues appeared due to
    recent changes since the last release.

  - coders/meta.c (WriteMETAImage): Assure that 'iptc\_offset' is
    initialized and valid.

  - coders/jpeg.c (ReadJPEGImage): Assure that evaluating the
    embedded profile length does not suffer from undefined behavior.

2020-01-12  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/render.c (DrawImage): Add more MVG parser validations.

2020-01-11  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/histogram.c (WriteHISTOGRAMImage): Histogram coder was
    relying on the previously removed '@' file inclusion feature to
    insert the histogram comment text.  Write a PseudoClass MIFF image
    with RLE compression.  Fixes SourceForge issue #622 "Histogram
    produces incorrect color table attribute ".

  - magick/pixel\_cache.c (ModifyCache): Re-open the pixel cache if
    the cache rows/columns do not match the owning image rows/columns.

  - magick/transform.c (TransformImage): TransformImage now returns
    a MagickPassFail return status value rather than void.

  - coders/pict.c (ReadPICTImage): Fix some over-strict validations
    which were preventing some PICT files which were previously read
    successfully from being accepted. Fix problems which occurred when
    the clipping rectangle changed the image size. Improve reading
    embedded JPEG blobs.  Now successfully reads all raster PICT files
    I have available.

2020-01-08  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/pict.c (ReadPICTImage): Be more strict about PICT
    rectangle by treating rectangle dimensions as if they are a 16-bit
    signed type and not allowing negative values.  Avoid GCC warnings
    which sprung up similar to "warning: comparison is always false
    due to limited range of data type".

2020-01-05  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/sfw.c (ReadSFWImage): Restore a DestroyImage() statement
    which was accidentally deleted by recent edits.  Fixes oss-fuzz
    "Issue 19819 in oss-fuzz: graphicsmagick:coder\_SFW\_fuzzer:
    Indirect-leak in AllocateImage".

  - coders/png.c (WriteOneJNGImage): Detect when JPEG encoder has
    failed, and throw exception.  Fix image dimension limit
    validations.  Stop discarding exception report.  Fixes SourceForge
    bug #621 "Assertion in WriteBlob at magick/blob.c:4937" which was
    reported by Suhwan Song.

  - coders/pict.c (WritePICTImage): Eliminating small buffer overrun
    when run-length encoding pixels.  Fixes SourceForge bug #620
    "heap-buffer-overflow in EncodeImage at coders/pict.c:1114" which
    was reported by Suhwan Song.

  - coders/logo.c (ReadLOGOImage): PATTERN error handling was
    incomplete.  Add appropriate error handling.
    (ReadLOGOImage): Switch to using ConstituteTextureImage() rather
    than TextureImage() since it is more appropriate for this purpose.
    (ReadLOGOImage): Oops!  Accidental change of behavior. When size
    is not supplied, simply return the pattern image.

2020-01-04  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/\*.c (ReadFOOImage): Stop image timer just before
    returning from reader so that reported timings are correct when
    used in the future.

2020-01-03  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - magick/timer.c (StartTimer): Expose previously existing
    StartTimer() function.
    (StopTimer): Expose previously existing StartTimer() function.

  - magick/constitute.c (WriteImage): Don't over-write time-stamp
    when output is to INFO format.

2020-01-03  Fojtik Jaroslav  <JaFojtik@seznam.cz>

  - VisualMagick\configure\configure.exe: Should not depend on mfcr90.dll.
    It is too bad when end user cannot run this tool because of missing DLL.

  - VisualMagick\configure\configure.cpp Make speed optimisation as default
    option.

  - VisualMagick\configure\configure.vcproj Give different filename to debug
    build to avoid accidental committing debug build to repository.

2020-01-01  Bob Friesenhahn  <bfriesen@simple.dallas.tx.us>

  - coders/dpx.c (GenerateDPXTimeStamp): Use reentrant localtime\_r()
    function if it is available.

  - magick/log.c (LogMagickEventList): Use reentrant
    localtime\_r() function if it is available.

  - coders/cineon.c (GenerateCineonTimeStamp): Use reentrant
    localtime\_r() function if it is available.

  - coders/mat.c (WriteMATLABImage): Use reentrant localtime\_r()
    function if it is available.

  - coders/pdf.c (WritePDFImage): Use reentrant localtime\_r()
    function if it is available.

  - coders/ps.c (WritePSImage): Use reentrant ctime\_r() function
    if it is available.

  - coders/ps2.c (WritePS2Image): Use reentrant ctime\_r() function
    if it is available.

  - coders/ps3.c (WritePS3Image): Use reentrant ctime\_r() function
    if it is available.

  - configure.ac: Test for getpwnam\_r().

  - magick/utility.c (ExpandFilename): Use reentrant getpwnam\_r()
    function if it is available.

  - magick/magick.c (InitializeMagickSignalHandlers): Use the normal
    termination signal handler for SIGXCPU and SIGXFSZ so that ulimit
    or setrlimit(2) may be used to apply CPU (RLIMIT\_CPU) and output
    file size (RLIMIT\_FSIZE) limits with the normal cleanup, and
    without dumping core.  Note that any output files currently being
    written may be truncated and files being written by external
    programs (e.g. Ghostscript) might be left behind unless they are
    to a temporary file assigned by GraphicsMagick.

  - coders/xpm.c (ReadXPMImage): Promote a color-lookup
    warning to an error.

  - coders/xc.c (ReadXCImage): Promote a color-lookup
    warning to an error.

  - coders/null.c (ReadNULLImage): Promote a color-lookup
    warning to an error.

  - Makefile.am: Rotate ChangeLogs for the new year.

  - coders/gradient.c (ReadGRADIENTImage): Promote a color-lookup
    warning to an error.
