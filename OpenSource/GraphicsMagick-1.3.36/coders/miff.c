/*
% Copyright (C) 2003-2020 GraphicsMagick Group
% Copyright (C) 2002 ImageMagick Studio
% Copyright 1991-1999 E. I. du Pont de Nemours and Company
%
% This program is covered by multiple licenses, which are described in
% Copyright.txt. You should have received a copy of Copyright.txt with this
% package; otherwise see http://www.graphicsmagick.org/www/Copyright.html.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                        M   M  IIIII  FFFFF  FFFFF                           %
%                        MM MM    I    F      F                               %
%                        M M M    I    FFF    FFF                             %
%                        M   M    I    F      F                               %
%                        M   M  IIIII  F      F                               %
%                                                                             %
%                                                                             %
%                      Read/Write MIFF Image Format.                          %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

/*
  Include declarations.
*/
#include "magick/studio.h"
#include "magick/attribute.h"
#include "magick/blob.h"
#include "magick/color.h"
#include "magick/color_lookup.h"
#include "magick/colormap.h"
#include "magick/compress.h"
#include "magick/constitute.h"
#include "magick/enum_strings.h"
#include "magick/log.h"
#include "magick/magick.h"
#include "magick/monitor.h"
#include "magick/pixel_cache.h"
#include "magick/profile.h"
#include "magick/utility.h"
#include "magick/version.h"
#if defined(HasZLIB)
#  include "zlib.h"
#endif
#if defined(HasBZLIB)
#  include "bzlib.h"
#endif

/*
  Forward declarations.
*/
static unsigned int
  WriteMIFFImage(const ImageInfo *,Image *);

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   I s M I F F                                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method IsMIFF returns True if the image format type, identified by the
%  magick string, is MIFF.
%
%  The format of the IsMIFF method is:
%
%      unsigned int IsMIFF(const unsigned char *magick,const size_t length)
%
%  A description of each parameter follows:
%
%    o status:  Method IsMIFF returns True if the image format type is MIFF.
%
%    o magick: This string is generally the first few bytes of an image file
%      or blob.
%
%    o length: Specifies the length of the magick string.
%
%
*/
static unsigned int IsMIFF(const unsigned char *magick,const size_t length)
{
  if (length < 14)
    return(False);
  if (LocaleNCompare((char *) magick,"id=ImageMagick",14) == 0)
    return(True);
  return(False);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d M I F F I m a g e                                                 %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadMIFFImage reads a MIFF image file and returns it.  It
%  allocates the memory necessary for the new Image structure and returns a
%  pointer to the new image.
%
%  The format of the ReadMIFFImage method is:
%
%      Image *ReadMIFFImage(const ImageInfo *image_info,
%        ExceptionInfo *exception)
%
%  Decompression code contributed by Kyle Shorter.
%
%  A description of each parameter follows:
%
%    o image: Method ReadMIFFImage returns a pointer to the image after
%      reading.  A null image is returned if there is a memory shortage or
%      if the image cannot be read.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o exception: return any errors or warnings in this structure.
%
%
*/


static MagickPassFail
ImportRLEPixels(Image *image,
                const QuantumType quantum_type,
                const unsigned int quantum_size,
                const unsigned char *source)
{

  register const unsigned char
    *p;

  register unsigned int
    index,
    quantum;

  register int
    length;

  register IndexPacket
    *indexes;

  register long
    x;

  PixelPacket
    pixel;

  register PixelPacket
    *q;

  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(source != (const unsigned char *) NULL);

  /*
    FIXME: gray DirectClass pixels (quantum_type=GrayQuantum and
    GrayAlphaQuantum ) should be properly supported with RLE since
    modern ImageMagick supports it.  For the moment we support it by
    reading as PseudoClass using IndexQuantum.
   */
  assert((quantum_size == 8) || (quantum_size == 16) || (quantum_size == 32));
  if (!(((quantum_type == IndexQuantum) && (image->storage_class == PseudoClass)) ||
        ((quantum_type == IndexAlphaQuantum) && (image->storage_class == PseudoClass)) ||
        /*  ((quantum_type == GrayQuantum) && (image->storage_class == DirectClass) && !image->matte) ||*/
        /*  ((quantum_type == GrayAlphaQuantum) && (image->storage_class == DirectClass) && image->matte) ||*/
        ((quantum_type == CMYKAQuantum) && (image->storage_class == DirectClass) && image->matte) ||
        ((quantum_type == CMYKQuantum) && (image->storage_class == DirectClass) && !image->matte) ||
        ((quantum_type == RGBAQuantum) && (image->storage_class == DirectClass) && image->matte) ||
        ((quantum_type == RGBQuantum) && (image->storage_class == DirectClass) && !image->matte)))
    {
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                            "RLE decompression not supported for QuantumType=%s, ClassType=%s, Matte=%s",
                            QuantumTypeToString(quantum_type),ClassTypeToString(image->storage_class),
                            image->matte ? "True" : "False");
      ThrowBinaryException(CoderError,RLECompressionNotSupported,image->filename);
    }

  p=source;
  q=AccessMutablePixels(image);
  length=0;
  index=0;
  indexes=AccessMutableIndexes(image);

  pixel.red=0;
  pixel.green=0;
  pixel.blue=0;
  pixel.opacity=TransparentOpacity;

  switch (quantum_type)
    {
    case IndexQuantum:
      {
        /*
          PseudoClass
        */
        switch (quantum_size)
          {
          case 8:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      index=((unsigned int) *p++);
                      VerifyColormapIndex(image,index);
                      pixel=image->colormap[index];
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                *q++=pixel;
                }
              break;
            }
          case 16:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      index =((unsigned int) *p++ << 8);
                      index|=((unsigned int) *p++);
                      VerifyColormapIndex(image,index);
                      pixel=image->colormap[index];
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                  *q++=pixel;
                }
              break;
            }
          case 32:
            {
              /*
                This case should never actually be used.
              */
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      index =((unsigned int) *p++ << 24);
                      index|=((unsigned int) *p++ << 16);
                      index|=((unsigned int) *p++ << 8);
                      index|=((unsigned int) *p++);
                      VerifyColormapIndex(image,index);
                      pixel=image->colormap[index];
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                  *q++=pixel;
                }
              break;
            }
          }
        break;
      }
    case IndexAlphaQuantum:
      {
        /*
          PseudoClass plus alpha channel
        */
        switch (quantum_size)
          {
          case 8:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      index=((unsigned int) *p++);
                      VerifyColormapIndex(image,index);
                      pixel=image->colormap[index];
                      quantum=((unsigned int) *p++);
                      pixel.opacity=MaxRGB-ScaleCharToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                *q++=pixel;
                }
              break;
            }
          case 16:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      index =((unsigned int) *p++ << 8);
                      index|=((unsigned int) *p++);
                      VerifyColormapIndex(image,index);
                      pixel=image->colormap[index];
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=MaxRGB-ScaleShortToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                  *q++=pixel;
                }
              break;
            }
          case 32:
            {
              /*
                This case should never actually be used.
              */
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      index =((unsigned int) *p++ << 24);
                      index|=((unsigned int) *p++ << 16);
                      index|=((unsigned int) *p++ << 8);
                      index|=((unsigned int) *p++);
                      VerifyColormapIndex(image,index);
                      pixel=image->colormap[index];
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=MaxRGB-ScaleLongToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                  *q++=pixel;
                }
              break;
            }
          }
        break;
      }
    case CMYKAQuantum:
      {
        /*
          Directclass CMYK & matte
        */
        switch (quantum_size)
          {
          case 8:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      pixel.red=ScaleCharToQuantum(*p++);
                      pixel.green=ScaleCharToQuantum(*p++);
                      pixel.blue=ScaleCharToQuantum(*p++);
                      pixel.opacity=ScaleCharToQuantum(*p++);
                      index=(IndexPacket) MaxRGB-ScaleCharToQuantum(*p++);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                  *q++=pixel;
                }
              break;
            }
          case 16:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum= ((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleShortToQuantum(quantum);
                      quantum= ((unsigned int) *p++ << 8);
                      quantum|=(*p++);
                      pixel.green=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      index=(IndexPacket) MaxRGB-ScaleShortToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                  *q++=pixel;
                }
              break;
            }
          case 32:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.green=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      index=(IndexPacket) MaxRGB-ScaleLongToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *indexes++=index;
                  *q++=pixel;
                }
              break;
            }
          }
        break;
      }
    case CMYKQuantum:
      {
        /*
          Directclass CMYK without matte
        */
        switch (quantum_size)
          {
          case 8:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      pixel.red=ScaleCharToQuantum(*p++);
                      pixel.green=ScaleCharToQuantum(*p++);
                      pixel.blue=ScaleCharToQuantum(*p++);
                      pixel.opacity=ScaleCharToQuantum(*p++);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          case 16:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.green=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=ScaleShortToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          case 32:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.green=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=ScaleLongToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          }
        break;
      }
    case RGBAQuantum:
      {
        /*
          Directclass RGB with matte
        */
        switch (quantum_size)
          {
          case 8:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      pixel.red=ScaleCharToQuantum(*p++);
                      pixel.green=ScaleCharToQuantum(*p++);
                      pixel.blue=ScaleCharToQuantum(*p++);
                      pixel.opacity=MaxRGB-ScaleCharToQuantum(*p++);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          case 16:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.green=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=MaxRGB-ScaleShortToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          case 32:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.green=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.opacity=MaxRGB-ScaleLongToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          }
        break;
      }
    case RGBQuantum:
      {
        /*
          Directclass RGB without matte
        */
        switch (quantum_size)
          {
          case 8:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      pixel.red=ScaleCharToQuantum(*p++);
                      pixel.green=ScaleCharToQuantum(*p++);
                      pixel.blue=ScaleCharToQuantum(*p++);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          case 16:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.green=ScaleShortToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleShortToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
              break;
            }
          case 32:
            {
              for (x=(long) image->columns; x > 0; x--)
                {
                  if (length == 0)
                    {
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.red=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.green=ScaleLongToQuantum(quantum);
                      quantum =((unsigned int) *p++ << 24);
                      quantum|=((unsigned int) *p++ << 16);
                      quantum|=((unsigned int) *p++ << 8);
                      quantum|=((unsigned int) *p++);
                      pixel.blue=ScaleLongToQuantum(quantum);
                      length=((int) *p++)+1;
                    }
                  length--;
                  *q++=pixel;
                }
            }
            break;
          }
        break;
      }
    default:
      {
      }
    }
  return(MagickPass);
}

#if 0
static void *BZLIBAllocFunc(void *opaque, int items, int size)
{
  ARG_NOT_USED(opaque);
  return MagickMallocCleared((size_t) items*size);
}
static void BZLIBFreeFunc(void *opaque, void *address)
{
  ARG_NOT_USED(opaque);
  MagickFree(address);
}
#endif

#if defined(HasZLIB)
static voidpf ZLIBAllocFunc(voidpf opaque, uInt items, uInt size) MAGICK_FUNC_MALLOC;
static voidpf ZLIBAllocFunc(voidpf opaque, uInt items, uInt size)
{
  ARG_NOT_USED(opaque);
  return MagickMallocCleared(MagickArraySize(items,size));
}
static void ZLIBFreeFunc(voidpf opaque, voidpf address)
{
  ARG_NOT_USED(opaque);
  MagickFree(address);
}
#endif /* defined(HasZLIB) */

#define ThrowMIFFReaderException(code_,reason_,image_) \
do { \
  MagickFreeResourceLimitedMemory(comment); \
  MagickFreeResourceLimitedMemory(values); \
  if (number_of_profiles > 0) \
    { \
      unsigned int _index; \
      for (_index=0; _index < number_of_profiles; _index++) \
        { \
          MagickFreeMemory(profiles[_index].name); \
          MagickFreeResourceLimitedMemory(profiles[_index].info); \
        } \
      MagickFreeResourceLimitedMemory(profiles); \
      number_of_profiles=0; \
    } \
  MagickFreeResourceLimitedMemory(pixels); \
  MagickFreeResourceLimitedMemory(compress_pixels); \
  ThrowReaderException(code_,reason_,image_); \
} while (0);

#define ReadMIFFMaxKeyWordCount 256 /* Arbitrary limit on keywords in one MIFF frame */

static Image *ReadMIFFImage(const ImageInfo *image_info,
  ExceptionInfo *exception)
{
#if defined(HasBZLIB)
  bz_stream
    bzip_info;
#endif

  char
    id[MaxTextExtent],
    keyword[MaxTextExtent];

  double
    version;

  Image
    *image;

  int
    c;

  size_t
    compressed_length,
    length,
    pixels_size;

  long
    y;

  QuantumType
    quantum_type;

  register long
    i;

  register PixelPacket
    *q;

  register unsigned char
    *p;

  unsigned char
    *compress_pixels = (unsigned char *) NULL,
    *pixels = (unsigned char *) NULL;

  void
    *pixels_p;

  MagickPassFail
    status;

  unsigned int
    colors,
    comment_count,
    depth,
    keyword_count,
    packet_size,
    quantum_size;

  ProfileInfo
    *profiles=0;

  unsigned int
    number_of_profiles=0;

  char
    *comment = NULL,
    *values = NULL;

#if defined(HasZLIB)
  z_stream
    zip_info;
#endif

  /*
    Open image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(exception != (ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  image=AllocateImage(image_info);
  status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
  if (status == MagickFail)
    ThrowReaderException(FileOpenError,UnableToOpenFile,image);
  /*
    Decode image header;  header terminates one character beyond a ':'.
  */
  c=ReadBlobByte(image);
  if (c == EOF)
    {
      DestroyImage(image);
      return((Image *) NULL);
    }
  *id='\0';
  version=0.0;
  do
  {
    /*
      Decode image header;  header terminates one character beyond a ':'.
    */
    colors=0;
    image->depth=8;
    image->compression=NoCompression;
    image->storage_class=DirectClass;
    comment_count=0;
    keyword_count=0;
    while (isgraph(c) && (c != ':'))
    {
      register char
        *p;

      if (c == '{')
        {
          size_t
            comment_length;

          /*
            Insist that format is identified prior to any comments.
          */
          if (id[0] == '\0')
            {
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Comment precedes format identifier (id=ImageMagick)");
              ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);
            }

          /*
            Insist that only one comment is provided
          */
          if (comment_count > 0)
            {
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                    "Too many comments!");
              ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);
            }

          /*
            Read comment-- any text between { }.
          */
          comment_length=MaxTextExtent;
          comment=MagickAllocateResourceLimitedMemory(char *,comment_length);
          if (comment == (char *) NULL)
            ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,
              image);
          p=comment;
          for ( ; comment != (char *) NULL; p++)
          {
            c=ReadBlobByte(image);
            if ((c == EOF) || (c == '}'))
              break;
            if ((size_t) (p-comment+1) >= comment_length)
              {
                char
                  *new_comment;

                *p='\0';
                comment_length<<=1;
                new_comment=MagickReallocateResourceLimitedMemory(char *,comment,comment_length);
                if (new_comment == (char *) NULL)
                  {
                    MagickFreeResourceLimitedMemory(comment);
                    break;
                  }
                comment=new_comment;
                p=comment+strlen(comment);
              }
            *p=c;
          }
          if (comment == (char *) NULL)
            ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,
              image);
          *p='\0';
          (void) LogMagickEvent(CoderEvent,GetMagickModule(),"Comment: \"%s\"", comment);
          (void) SetImageAttribute(image,"comment",comment);
          comment_count++;
          MagickFreeResourceLimitedMemory(comment);
          c=ReadBlobByte(image);
        }
      else
        if (isalnum(c))
          {
            size_t
              values_length;

            MagickBool
              in_brace=MagickFalse;

            /*
              Get keyword.
            */
            keyword[0]='\0';
            p=keyword;
            do
            {
              if ((p-keyword) < (MaxTextExtent-1))
                *p++=c;
              c=ReadBlobByte(image);
            } while ((c != '=') && (c != EOF));
            *p='\0';
            if (c == EOF)
              ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);

            /*
              Insist that the first keyword must be 'id' (id=ImageMagick)
            */
            if ((keyword_count == 0) && (LocaleCompare(keyword,"id") != 0))
              {
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "First keyword must be 'id' (have '%s')",
                                      keyword);
                ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);
              }
            /*
              Get values.

              Values not containing spaces are terminated by the first
              white-space (or new-line) enountered.  Values containing
              spaces and/or new-lines must be surrounded by braces.
            */
            values_length=MaxTextExtent;
            values=MagickAllocateResourceLimitedMemory(char *,values_length);
            if (values == (char *) NULL)
              ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
            values[0]='\0';
            c=ReadBlobByte(image);
            in_brace=(c == '{');
            if (in_brace)
              c=ReadBlobByte(image);
            p=values;
            while ((((!in_brace) && (c != '\n')) ||
                     ((in_brace) && (c != '}'))) &&
                   (c != EOF))
              {
                if ((size_t) (p-values+1) >= values_length)
                  {
                    char
                      *new_values;

                    *p='\0';
                    values_length<<=1;
                    new_values=MagickReallocateResourceLimitedMemory(char *,values,values_length);
                    if (new_values == (char *) NULL)
                      {
                        MagickFreeResourceLimitedMemory(values);
                        break;
                      }
                    values=new_values;
                    p=values+strlen(values);
                  }
                if (values == (char *) NULL)
                  ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
                *p++=c;
                c=ReadBlobByte(image);
                if (!in_brace)
                  if (isspace(c))
                    break;
              }
            *p='\0';
            keyword_count++;
            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                  "keyword[%u]=\"%s\" values=\"%s\"",keyword_count,keyword,values);
            /*
              Insist that the first keyword value must be 'ImageMagick' (id=ImageMagick)
            */
            if ((keyword_count == 1) && (LocaleCompare(values,"ImageMagick") != 0))
              {
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "First keyword/value must be 'id=ImageMagick'");
                ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);
              }
            /*
              Arbitrarily limit the number of header keywords to avoid DOS attempts.
            */
            if (keyword_count > ReadMIFFMaxKeyWordCount)
              {
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                      "Excessive key word count %u"
                                      " (Denial of service attempt?)",keyword_count);
                ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);
              }
            /*
              Assign a value to the specified keyword.
            */
            switch (*keyword)
            {
              case 'b':
              case 'B':
              {
                if (LocaleCompare(keyword,"background-color") == 0)
                  {
                    (void) QueryColorDatabase(values,&image->background_color,
                      exception);
                    break;
                  }
                if (LocaleCompare(keyword,"blue-primary") == 0)
                  {
                    (void) sscanf(values,"%lf,%lf",
                      &image->chromaticity.blue_primary.x,
                      &image->chromaticity.blue_primary.y);
                    break;
                  }
                if (LocaleCompare(keyword,"border-color") == 0)
                  {
                    (void) QueryColorDatabase(values,&image->border_color,
                      exception);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'c':
              case 'C':
              {
                if (LocaleCompare(keyword,"class") == 0)
                  {
                    image->storage_class=UndefinedClass;
                    if (LocaleCompare(values,"PseudoClass") == 0)
                      image->storage_class=PseudoClass;
                    else
                      if (LocaleCompare(values,"DirectClass") == 0)
                        image->storage_class=DirectClass;
                    break;
                  }
                /* Legacy ImageMagick 4.2.9 used keyword "color-profile" for ICC profile */
                if (LocaleCompare(keyword,"color-profile") == 0)
                  {
                    ProfileInfo
                      *new_profiles;

                    if (MagickAtoL(values) <= 0)
                      ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);
                    i=(long) number_of_profiles;
                    new_profiles=MagickReallocateResourceLimitedArray(ProfileInfo *,profiles,
                                                                      (size_t) i+1,sizeof(ProfileInfo));
                    if (new_profiles == (ProfileInfo *) NULL)
                      {
                        for (i=0; i < number_of_profiles; i++)
                          {
                            MagickFreeMemory(profiles[i].name);
                            MagickFreeResourceLimitedMemory(profiles[i].info);
                          }
                        MagickFreeResourceLimitedMemory(profiles);
                        MagickFreeResourceLimitedMemory(values);
                        ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
                      }
                    profiles=new_profiles;
                    profiles[i].name=AllocateString("icc");
                    profiles[i].length=MagickAtoL(values);
                    profiles[i].info=(unsigned char *) NULL;
                    number_of_profiles++;
                    break;
                  }
                if (LocaleCompare(keyword,"colors") == 0)
                  {
                    colors=MagickAtoL(values);
                    break;
                  }
                if (LocaleCompare(keyword,"colorspace") == 0)
                  {
                    /*
                      ImageMagick now uses colorspace=sRGB for ordinary RGB images.
                    */
                    if (LocaleCompare(values,"sRGB") == 0)
                      image->colorspace=RGBColorspace;
                    else
                      image->colorspace=(StringToColorspaceType(values));
                    break;
                  }
                if (LocaleCompare(keyword,"compression") == 0)
                  {
                    image->compression=NoCompression;
                    if (LocaleCompare(values,"None") == 0)
                      image->compression=NoCompression;
                    else
                      if (LocaleCompare(values,"Zip") == 0)
                        image->compression=ZipCompression;
                      else
                        if (LocaleCompare(values,"BZip") == 0)
                          image->compression=BZipCompression;
                        else
                          if ((LocaleCompare(values,"RLE") == 0) ||
                              (LocaleCompare(values,"RunlengthEncoded") == 0))
                            image->compression=RLECompression;
                    break;
                  }
                if (LocaleCompare(keyword,"columns") == 0)
                  {
                    image->columns= MagickAtoL(values);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'd':
              case 'D':
              {
                if (LocaleCompare(keyword,"delay") == 0)
                  {
                    image->delay=MagickAtoL(values);
                    break;
                  }
                if (LocaleCompare(keyword,"depth") == 0)
                  {
                    image->depth=MagickAtoL(values);
                    break;
                  }
                if (LocaleCompare(keyword,"dispose") == 0)
                  {
                    image->dispose=(DisposeType) MagickAtoL(values);
                    if (LocaleCompare(values,"Background") == 0)
                      image->dispose=BackgroundDispose;
                    else
                      if (LocaleCompare(values,"None") == 0)
                        image->dispose=NoneDispose;
                      else
                        if (LocaleCompare(values,"Previous") == 0)
                          image->dispose=PreviousDispose;
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'g':
              case 'G':
              {
                if (LocaleCompare(keyword,"gamma") == 0)
                  {
                    image->gamma=MagickAtoF(values);
                    break;
                  }
                if (LocaleCompare(keyword,"green-primary") == 0)
                  {
                    (void) sscanf(values,"%lf,%lf",
                      &image->chromaticity.green_primary.x,
                      &image->chromaticity.green_primary.y);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'i':
              case 'I':
              {
                if (LocaleCompare(keyword,"id") == 0)
                  {
                    (void) strlcpy(id,values,MaxTextExtent);
                    break;
                  }
                if (LocaleCompare(keyword,"iterations") == 0)
                  {
                    image->iterations=MagickAtoL(values);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'm':
              case 'M':
              {
                if (LocaleCompare(keyword,"matte") == 0)
                  {
                    image->matte=(LocaleCompare(values,"True") == 0) ||
                      (LocaleCompare(values,"true") == 0);
                    break;
                  }
                if (LocaleCompare(keyword,"matte-color") == 0)
                  {
                    (void) QueryColorDatabase(values,&image->matte_color,
                      exception);
                    break;
                  }
                if (LocaleCompare(keyword,"montage") == 0)
                  {
                    (void) CloneString(&image->montage,values);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'o':
              case 'O':
              {
                if (LocaleCompare(keyword,"opaque") == 0)
                  {
                    image->matte=(LocaleCompare(values,"True") == 0) ||
                      (LocaleCompare(values,"true") == 0);
                    break;
                  }
                if (LocaleCompare(keyword,"orientation") == 0)
                  {
                    image->orientation=StringToOrientationType(values);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'p':
              case 'P':
              {
                if (LocaleCompare(keyword,"page") == 0)
                  {
                    char
                      *geometry;

                    geometry=GetPageGeometry(values);
                    (void) GetGeometry(geometry,&image->page.x,&image->page.y,
                      &image->page.width,&image->page.height);
                    MagickFreeMemory(geometry);
                    break;
                  }
                if ((LocaleNCompare(keyword,"profile-",8) == 0) ||
                    (LocaleNCompare(keyword,"profile:",8) == 0))
                  {
                    ProfileInfo
                      *new_profiles;

                    if (MagickAtoL(values) <= 0)
                      ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,image);
                    i=(long) number_of_profiles;
                    new_profiles=MagickReallocateResourceLimitedArray(ProfileInfo *,profiles,
                                                                      (size_t) i+1,sizeof(ProfileInfo));
                    if (new_profiles == (ProfileInfo *) NULL)
                      {
                        for (i=0; i < number_of_profiles; i++)
                          {
                            MagickFreeMemory(profiles[i].name);
                            MagickFreeResourceLimitedMemory(profiles[i].info);
                          }
                        MagickFreeResourceLimitedMemory(profiles);
                        MagickFreeResourceLimitedMemory(values);
                        ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
                      }
                    profiles=new_profiles;
                    profiles[i].name=AllocateString(keyword+8);
                    profiles[i].length=MagickAtoL(values);
                    profiles[i].info=(unsigned char *) NULL;
                    number_of_profiles++;
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'r':
              case 'R':
              {
                if (LocaleCompare(keyword,"red-primary") == 0)
                  {
                    (void) sscanf(values,"%lf,%lf",
                      &image->chromaticity.red_primary.x,
                      &image->chromaticity.red_primary.y);
                    break;
                  }
                if (LocaleCompare(keyword,"rendering-intent") == 0)
                  {
                    image->rendering_intent=UndefinedIntent;
                    if (LocaleCompare(values,"Saturation") == 0)
                      image->rendering_intent=SaturationIntent;
                    else
                      if (LocaleCompare(values,"perceptual") == 0)
                        image->rendering_intent=PerceptualIntent;
                      else
                        if (LocaleCompare(values,"absolute") == 0)
                          image->rendering_intent=AbsoluteIntent;
                        else
                          if (LocaleCompare(values,"relative") == 0)
                            image->rendering_intent=RelativeIntent;
                    break;
                  }
                if (LocaleCompare(keyword,"resolution") == 0)
                  {
                    (void) GetMagickDimension(values,&image->x_resolution,
                                              &image->y_resolution,NULL,NULL);
                    break;
                  }
                if (LocaleCompare(keyword,"rows") == 0)
                  {
                    image->rows= MagickAtoL(values);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 's':
              case 'S':
              {
                if (LocaleCompare(keyword,"scene") == 0)
                  {
                    image->scene=MagickAtoL(values);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'u':
              case 'U':
              {
                if (LocaleCompare(keyword,"units") == 0)
                  {
                    image->units=UndefinedResolution;
                    if (LocaleCompare(values,"pixels-per-inch") == 0)
                      image->units=PixelsPerInchResolution;
                    else
                      if (LocaleCompare(values,"pixels-per-centimeter") == 0)
                        image->units=PixelsPerCentimeterResolution;
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'v':
              case 'V':
              {
                if (LocaleCompare(keyword,"version") == 0)
                  {
                    version=MagickAtoF(values);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              case 'w':
              case 'W':
              {
                if (LocaleCompare(keyword,"white-point") == 0)
                  {
                    (void) sscanf(values,"%lf,%lf",
                      &image->chromaticity.white_point.x,
                      &image->chromaticity.white_point.y);
                    break;
                  }
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
              default:
              {
                (void) SetImageAttribute(image,keyword,
                  *values == '{' ? values+1 : values);
                break;
              }
            }
            MagickFreeResourceLimitedMemory(values);
          }
        else
          {
            c=ReadBlobByte(image);
          }
      while (isspace(c))
        c=ReadBlobByte(image);
    }
    (void) ReadBlobByte(image);

    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "id=\"%s\" version=%g class=%s colorspace=%s compression=%s matte=%s "
                          "columns=%lu rows=%lu depth=%u",
                          id,version,
                          ClassTypeToString(image->storage_class),
                          ColorspaceTypeToString(image->colorspace),
                          CompressionTypeToString(image->compression),
                          MagickBoolToString(image->matte),
                          image->columns, image->rows, image->depth);

    /*
      Verify that required image information is defined.
    */
    if ((LocaleCompare(id,"ImageMagick") != 0) ||
        (image->storage_class == UndefinedClass) ||
        (image->compression == UndefinedCompression) ||
        (image->colorspace == UndefinedColorspace) ||
        (image->columns == 0) ||
        (image->rows == 0) ||
        (image->depth == 0) || (image->depth > 32))
      {
        if (image->previous)
          {
            DeleteImageFromList(&image);
            ThrowException(exception,CorruptImageWarning,ImproperImageHeader,image->filename);
            break;
          }
        else
          {
            ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,
              image);
          }
      }

    /*
      Create a normalized version of depth.
    */
    if (image->depth <= 8)
      depth=8;
    else if (image->depth <= 16)
      depth=16;
    else
      depth=32;

    if (image->montage != (char *) NULL)
      {
        register char
          *p;

        size_t
          directory_length;

        /*
          Image directory.
        */
        image->directory=MagickAllocateMemory(char *,MaxTextExtent);
        if (image->directory == (char *) NULL)
          ThrowMIFFReaderException(CorruptImageError,UnableToReadImageData,image);
        p=image->directory;
        directory_length=0;
        do
        {
          *p='\0';
          if (((directory_length+1) % MaxTextExtent) == 0)
            {
              /*
                Allocate more memory for the image directory.
              */
              MagickReallocMemory(char *,image->directory,
                (directory_length+MaxTextExtent+1));
              if (image->directory == (char *) NULL)
                ThrowMIFFReaderException(CorruptImageError,UnableToReadImageData,
                  image);
              p=image->directory+directory_length;
            }
          c=ReadBlobByte(image);
          if (c == EOF)
            break;
          *p++=c;
          ++directory_length;
        } while (c != '\0');
      }

    /*
      Attached profiles.
    */
    if (number_of_profiles > 0)
      {
        for (i=0; i < (long) number_of_profiles; i++)
        {
          if (profiles[i].length > 0)
            {
              if ((((magick_off_t) profiles[i].length) > 0) &&
                  ((BlobIsSeekable(image)
                    && (GetBlobSize(image) - TellBlob(image)) >
                    (magick_off_t) profiles[i].length) ||
                   (profiles[i].length < 15*1024*1024)))
                {
                  profiles[i].info=MagickAllocateResourceLimitedMemory(unsigned char *,profiles[i].length);
                  if (profiles[i].info == (unsigned char *) NULL)
                    ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,
                                             image);
                  if (ReadBlob(image,profiles[i].length,profiles[i].info)
                      != profiles[i].length)
                    ThrowMIFFReaderException(CorruptImageError,
                                             UnexpectedEndOfFile,
                                             image);
                  (void) SetImageProfile(image,profiles[i].name,profiles[i].info,profiles[i].length);
                }
              else
                {
                  (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                        "Profile size %" MAGICK_SIZE_T_F "u is excessively large",
                                        (MAGICK_SIZE_T ) profiles[i].length);
                  ThrowMIFFReaderException(CorruptImageError,ImproperImageHeader,
                                           image);
                }
            }
          MagickFreeMemory(profiles[i].name);
          MagickFreeResourceLimitedMemory(profiles[i].info);
        }
        MagickFreeResourceLimitedMemory(profiles);
        number_of_profiles=0;
      }

    if (image->storage_class == PseudoClass)
      {
        /*
          Create image colormap.
        */
        if (!AllocateImageColormap(image,colors != 0 ? colors : 256))
          ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,
            image);
        if (colors != 0)
          {
            unsigned char
              *colormap;

            unsigned int
              packet_size,
              pixel;

            /*
              Read image colormap from file.
            */
            packet_size=3*depth/8;
            colormap=MagickAllocateResourceLimitedArray(unsigned char *,packet_size,image->colors);
            if (colormap == (unsigned char *) NULL)
              ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,
                image);
            (void) ReadBlob(image,packet_size*image->colors,colormap);
            p=colormap;
            switch (depth)
              {
              case 8:
                {
                  for (i=0; i < (long) image->colors; i++)
                    {
                      image->colormap[i].red=ScaleCharToQuantum(*p++);
                      image->colormap[i].green=ScaleCharToQuantum(*p++);
                      image->colormap[i].blue=ScaleCharToQuantum(*p++);
                    }
                  break;
                }
              case 16:
                {
                  for (i=0; i < (long) image->colors; i++)
                    {
                      pixel=((unsigned int) *p << 8) | (unsigned int) *(p+1);
                      image->colormap[i].red=ScaleShortToQuantum(pixel);
                      p+=2;
                      pixel=((unsigned int) *p << 8) | (unsigned int) *(p+1);
                      image->colormap[i].green=ScaleShortToQuantum(pixel);
                      p+=2;
                      pixel=((unsigned int) *p << 8) | (unsigned int) *(p+1);
                      image->colormap[i].blue=ScaleShortToQuantum(pixel);
                      p+=2;
                    }
                  break;
                }
              case 32:
                {
                  for (i=0; i < (long) image->colors; i++)
                    {
                      pixel=((unsigned int) *p << 24) |
                        ((unsigned int) *(p+1) << 16) |
                        ((unsigned int) *(p+2) << 8) |
                        (unsigned int) *(p+3);
                      image->colormap[i].red=ScaleLongToQuantum(pixel);
                      p+=4;
                      pixel=((unsigned int) *p << 24) |
                        ((unsigned int) *(p+1) << 16) |
                        ((unsigned int) *(p+2) << 8) |
                        (unsigned int) *(p+3);
                      image->colormap[i].green=ScaleLongToQuantum(pixel);
                      p+=4;
                      pixel=((unsigned int) *p << 24) |
                        ((unsigned int) *(p+1) << 16) |
                        ((unsigned int) *(p+2) << 8) |
                        (unsigned int) *(p+3);
                      image->colormap[i].blue=ScaleLongToQuantum(pixel);
                      p+=4;
                    }
                }
              } /* switch (depth) */
            MagickFreeResourceLimitedMemory(colormap);
          }
      }
    if (image_info->ping && (image_info->subrange != 0))
      if (image->scene >= (image_info->subimage+image_info->subrange-1))
        break;

    if (CheckImagePixelLimits(image, exception) != MagickPass)
      ThrowMIFFReaderException(ResourceLimitError,ImagePixelLimitExceeded,image);

    /*
      Determine import properties
    */
    quantum_size=0;
    if (image->storage_class == PseudoClass)
      {
        quantum_type=image->matte ? IndexAlphaQuantum : IndexQuantum;
        if (image->colors <= 256)
          quantum_size=8;
        else if (image->colors <= 65535)
          quantum_size=16;
        else
          quantum_size=32;
      }
    else
      {
        quantum_type=RGBQuantum;
        quantum_size=depth;
        if IsGrayColorspace(image->colorspace)
          {
            quantum_type=GrayQuantum;
            if (image->matte)
              quantum_type=GrayAlphaQuantum;
          }
        else if (image->colorspace == CMYKColorspace)
          {
            quantum_type=CMYKQuantum;
            if (image->matte)
              quantum_type=CMYKAQuantum;
          }
        else
          {
            quantum_type=RGBQuantum;
            if (image->matte)
              quantum_type=RGBAQuantum;
          }
      }
    if ((quantum_type == GrayQuantum) && (MaxValueGivenBits(depth) <= MaxMap))
      {
        /*
          Create image colormap and read grey image as PseudoClass.
        */
        if (!AllocateImageColormap(image,MaxValueGivenBits(depth)+1))
          ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,
                                   image);
        quantum_type=IndexQuantum;
      }

     /*
      Allocate image pixels.
    */
    packet_size=quantum_size/8;
    if ((image->storage_class == DirectClass) &&
        (!IsGrayColorspace(image->colorspace)))
      packet_size=3*quantum_size/8;
    if (image->colorspace == CMYKColorspace)
      packet_size+=quantum_size/8;
    if (image->matte)
      packet_size+=quantum_size/8;
    if (image->compression == RLECompression)
      packet_size++;
    pixels_size=MagickArraySize(packet_size,image->columns);
    if (pixels_size == 0)
      ThrowMIFFReaderException(CoderError,ArithmeticOverflow,image);
    pixels=MagickAllocateResourceLimitedMemory(unsigned char *,pixels_size);
    if (pixels == (unsigned char *) NULL)
      ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    length=(size_t) (1.01*pixels_size);
    if (length < pixels_size)
      ThrowMIFFReaderException(CoderError,ArithmeticOverflow,image);
    if (~((size_t) 0) - length > 600)
      length += 600;
    else
      ThrowMIFFReaderException(CoderError,ArithmeticOverflow,image);
    compressed_length = length;
    compress_pixels=MagickAllocateResourceLimitedMemory(unsigned char *,compressed_length);
    if (compress_pixels == (unsigned char *) NULL)
      ThrowMIFFReaderException(ResourceLimitError,MemoryAllocationFailed,image);
    /*
      Read image pixels.
    */
   length=0;
    switch (image->compression)
      {
#if defined(HasZLIB)
      case ZipCompression:
        {
          int
            code=0;

          for (y=0; y < (long) image->rows; y++)
            {
              q=SetImagePixels(image,0,y,image->columns,1);
              if (q == (PixelPacket *) NULL)
                break;
              if (y == 0)
                {
                  zip_info.zalloc=ZLIBAllocFunc;
                  zip_info.zfree=ZLIBFreeFunc;
                  zip_info.opaque=(voidpf) NULL;
                  code=inflateInit(&zip_info);
                  status|=code >= 0;
                  zip_info.avail_in=0;
                }
              zip_info.next_out=pixels;
              zip_info.avail_out=(uInt) (packet_size*image->columns);
              do
                {
                  int
                    zip_status;

                  if (zip_info.avail_in == 0)
                    {
                      zip_info.next_in=compress_pixels;
                      if (version == 0)
                        {
                          length=(int) (1.01*pixels_size+12);
                          if (image->logging)
                            (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                                  "length = %"MAGICK_SIZE_T_F"u",
                                                  (MAGICK_SIZE_T) length);
                          zip_info.avail_in=(uInt) ReadBlob(image,length,zip_info.next_in);
                        }
                      else
                        {
                          length=ReadBlobMSBLong(image);
                          if (length > compressed_length)
                            {
                              (void) inflateEnd(&zip_info);
                              ThrowMIFFReaderException(CorruptImageError,
                                                       LengthAndFilesizeDoNotMatch,
                                                       image);
                            }
                          zip_info.avail_in=(uInt) ReadBlob(image,length,zip_info.next_in);
                          if ((size_t) zip_info.avail_in != length)
                            {
                              (void) inflateEnd(&zip_info);
                              ThrowMIFFReaderException(CorruptImageError,
                                                       UnexpectedEndOfFile,
                                                       image);
                            }
                        }
                    }
                  if (zip_info.avail_in <= 0)
                    {
                      (void) inflateEnd(&zip_info);
                      ThrowMIFFReaderException(CorruptImageError,UnexpectedEndOfFile,
                                               image);
                    }
                  zip_status=inflate(&zip_info,Z_NO_FLUSH);
                  if (zip_status == Z_STREAM_END)
                    {
                      if (image->logging)
                        (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                                              "zip_status == Z_STREAM_END");
                    break;
                    }
                  else if (zip_status != Z_OK)
                    {
                      (void) inflateEnd(&zip_info);
                      ThrowMIFFReaderException(CorruptImageError,UnableToUncompressImage,
                                           image);
                    }
                } while (zip_info.avail_out != 0);
              if (y == (long) (image->rows-1))
                {
                  if (version == 0)
                    (void) SeekBlob(image,-((ExtendedSignedIntegralType)
                                            zip_info.avail_in),SEEK_CUR);
                  code=inflateEnd(&zip_info);
                  status|=code >= 0;
                }
              if ((size_t) (zip_info.next_out-pixels) < pixels_size)
                {
                  (void) inflateEnd(&zip_info);
                  ThrowMIFFReaderException(CorruptImageError,UnexpectedEndOfFile,
                                           image);
                }
              if (!ImportImagePixelArea(image,quantum_type,quantum_size,pixels,0,0))
                break;
              if (!SyncImagePixels(image))
                break;
              if (image->previous == (Image *) NULL)
                if (QuantumTick(y,image->rows))
                  if (!MagickMonitorFormatted(y,image->rows,exception,
                                              LoadImageText,image->filename,
                                              image->columns,image->rows))
                    break;
            }
          break;
        } /* End case ZipCompression */
#endif
#if defined(HasBZLIB)
      case BZipCompression:
        {
          int
            code=0;

          for (y=0; y < (long) image->rows; y++)
            {
              q=SetImagePixels(image,0,y,image->columns,1);
              if (q == (PixelPacket *) NULL)
                break;
              if (y == 0)
                {
                  bzip_info.bzalloc=NULL;
                  bzip_info.bzfree=NULL;
                  bzip_info.opaque=NULL;
                  code=BZ2_bzDecompressInit(&bzip_info,image_info->verbose,False);
                  status|=code >= 0;
                  bzip_info.avail_in=0;
                }
              bzip_info.next_out=(char *) pixels;
              bzip_info.avail_out=(unsigned int) (pixels_size);
              do
                {
                  int
                    bz_status;

                  if (bzip_info.avail_in == 0)
                    {
                      bzip_info.next_in=(char *) compress_pixels;
                      if (version == 0)
                        {
                          length=(int) (1.01*pixels_size+600);
                          bzip_info.avail_in=(unsigned int) ReadBlob(image,length,bzip_info.next_in);
                        }
                      else
                        {
                          length=ReadBlobMSBLong(image);
                          bzip_info.avail_in=(unsigned int) ReadBlob(image,length,bzip_info.next_in);
                          if ((size_t) bzip_info.avail_in != length)
                            {
                              ThrowMIFFReaderException(CorruptImageError,UnexpectedEndOfFile,
                                                   image);
                            }
                        }
                    }
                  bz_status=BZ2_bzDecompress(&bzip_info);
                  if (bz_status == BZ_STREAM_END)
                    break;
                  else if (bz_status != BZ_OK)
                    {
                      (void) BZ2_bzDecompressEnd(&bzip_info);
                      ThrowMIFFReaderException(CorruptImageError,UnableToUncompressImage,
                                           image);
                    }
                } while (bzip_info.avail_out != 0);
              if (y == (long) (image->rows-1))
                {
                  if (version == 0)
                    (void) SeekBlob(image,-((ExtendedSignedIntegralType)
                                            bzip_info.avail_in),SEEK_CUR);
                  code=BZ2_bzDecompressEnd(&bzip_info);
                  status|=code >= 0;
                }
              if ((size_t) (((magick_uint64_t) bzip_info.total_out_hi32 << 32) |
                            bzip_info.total_out_lo32) < pixels_size)
                {
                  (void) BZ2_bzDecompressEnd(&bzip_info);
                  ThrowMIFFReaderException(CorruptImageError,UnexpectedEndOfFile,
                                           image);
                }
              if (!ImportImagePixelArea(image,quantum_type,quantum_size,pixels,0,0))
                break;
              if (!SyncImagePixels(image))
                break;
              if (image->previous == (Image *) NULL)
                if (QuantumTick(y,image->rows))
                  if (!MagickMonitorFormatted(y,image->rows,exception,
                                              LoadImageText,image->filename,
                                              image->columns,image->rows))
                    break;
            }
          break;
        } /* End case BZipCompression */
#endif
      case RLECompression:
        {
          for (y=0; y < (long) image->rows; y++)
            {
              q=SetImagePixels(image,0,y,image->columns,1);
              if (q == (PixelPacket *) NULL)
                break;
              /*
                Collect one pixel row
              */
              p=pixels;
              for (length=0; length < image->columns; )
                {
                  size_t
                    bytes_read;

                  if ((bytes_read=ReadBlob(image,packet_size,p)) != packet_size)
                    ThrowMIFFReaderException(CorruptImageError,UnexpectedEndOfFile,
                                             image);
                  p+=bytes_read;
                  length+=(size_t) *(p-1)+1;
                }

              if (!ImportRLEPixels(image,quantum_type,quantum_size,pixels))
                break;
              if (!SyncImagePixels(image))
                break;
              if (image->previous == (Image *) NULL)
                if (QuantumTick(y,image->rows))
                  if (!MagickMonitorFormatted(y,image->rows,exception,
                                              LoadImageText,image->filename,
                                              image->columns,image->rows))
                    break;

            }
          break;
        } /* End case RLECompression */
      default:
        {
          for (y=0; y < (long) image->rows; y++)
            {
              q=SetImagePixels(image,0,y,image->columns,1);
              if (q == (PixelPacket *) NULL)
                break;
              pixels_p=pixels;
              if (ReadBlobZC(image,packet_size*image->columns,&pixels_p)
                  != (size_t) packet_size*image->columns)
                ThrowMIFFReaderException(CorruptImageError,UnexpectedEndOfFile,
                                         image);
              if (!ImportImagePixelArea(image,quantum_type,quantum_size,
                                        (const unsigned char*) pixels_p,0,0))
                break;
              if (!SyncImagePixels(image))
                break;
              if (image->previous == (Image *) NULL)
                if (QuantumTick(y,image->rows))
                  if (!MagickMonitorFormatted(y,image->rows,exception,
                                              LoadImageText,image->filename,
                                              image->columns,image->rows))
                    break;
            }
          break;
        }
      } /* End switch (image->compression) */

    MagickFreeResourceLimitedMemory(pixels);
    MagickFreeResourceLimitedMemory(compress_pixels);

    if (EOFBlob(image))
      {
        ThrowException(exception,CorruptImageError,UnexpectedEndOfFile,
          image->filename);
        status=MagickFail;
      }
    /*
      Verify that pixel transfer loops completed
    */
    if (y != (long) image->rows)
      status=MagickFail;

    if (status == MagickFail)
      {
        GetImageException(image,exception);
        CloseBlob(image);
        DestroyImageList(image);
        return((Image *) NULL);
      }
    StopTimer(&image->timer);
    /*
      Proceed to next image.
    */
    if (image_info->subrange != 0)
      if (image->scene >= (image_info->subimage+image_info->subrange-1))
        break;
    do
    {
      c=ReadBlobByte(image);
    } while (!isgraph(c) && (c != EOF));
    if (c != EOF)
      {
        /*
          Allocate next image structure.
        */
        AllocateNextImage(image_info,image);
        if (image->next == (Image *) NULL)
          {
            DestroyImageList(image);
            return((Image *) NULL);
          }
        image=SyncNextImageInList(image);
        status=MagickMonitorFormatted(TellBlob(image),GetBlobSize(image),
                                      exception,LoadImagesText,
                                      image->filename);
        if (status == MagickFail)
          break;
      }
  } while (c != EOF);
  while (image->previous != (Image *) NULL)
    image=image->previous;
  CloseBlob(image);
  return(image);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e g i s t e r M I F F I m a g e                                         %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method RegisterMIFFImage adds attributes for the MIFF image format to
%  the list of supported formats.  The attributes include the image format
%  tag, a method to read and/or write the format, whether the format
%  supports the saving of more than one frame to the same file or blob,
%  whether the format supports native in-memory I/O, and a brief
%  description of the format.
%
%  The format of the RegisterMIFFImage method is:
%
%      RegisterMIFFImage(void)
%
*/
ModuleExport void RegisterMIFFImage(void)
{
  /* GraphicsMagick 1.4, Zlib 1.2.3, BZlib */
  static const char
    version[]= MagickPackageName " " MagickLibVersionText
#if defined(ZLIB_VERSION)
    ", Zlib " ZLIB_VERSION
#endif
#if defined(HasBZLIB)
    ", BZlib"
#endif
    ;

  MagickInfo
    *entry;

  entry=SetMagickInfo("MIFF");
  entry->decoder=(DecoderHandler) ReadMIFFImage;
  entry->encoder=(EncoderHandler) WriteMIFFImage;
  entry->magick=(MagickHandler) IsMIFF;
  entry->description="Magick Image File Format";
  entry->seekable_stream=MagickTrue;
  entry->version=version;
  entry->module="MIFF";
  entry->coder_class=PrimaryCoderClass;
  (void) RegisterMagickInfo(entry);
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   U n r e g i s t e r M I F F I m a g e                                     %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method UnregisterMIFFImage removes format registrations made by the
%  MIFF module from the list of supported formats.
%
%  The format of the UnregisterMIFFImage method is:
%
%      UnregisterMIFFImage(void)
%
*/
ModuleExport void UnregisterMIFFImage(void)
{
  (void) UnregisterMagickInfo("MIFF");
}

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   W r i t e M I F F I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method WriteMIFFImage writes a MIFF image to a file.
%
%  The format of the WriteMIFFImage method is:
%
%      unsigned int WriteMIFFImage(const ImageInfo *image_info,Image *image)
%
%  Compression code contributed by Kyle Shorter.
%
%  A description of each parameter follows:
%
%    o status: Method WriteMIFFImage return True if the image is written.
%      False is returned if there is a memory shortage or if the image file
%      fails to write.
%
%    o image_info: Specifies a pointer to a ImageInfo structure.
%
%    o image: A pointer to an Image structure.
%
%
*/
static void WriteRunlengthPacket(const Image *image,
                                 const unsigned int quantum_size,
                                 const PixelPacket *pixel,
                                 const size_t length,
                                 unsigned char **qp,
                                 const IndexPacket index)
{
  register unsigned char
    *q;

  unsigned int
    value;

  assert((quantum_size == 8) || (quantum_size == 16) || (quantum_size == 32));

  q = *qp;

  if (image->storage_class != DirectClass)
    {
      value=index;
      /*
        Fall-through logic
      */
      switch (quantum_size)
        {
        case 32:
          {
            *q++=(unsigned char) (value >> 24);
            *q++=(unsigned char) (value >> 16);
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            break;
          }
        case 16:
          {
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            break;
          }
        case 8:
          {
            *q++=(unsigned char) value;
            break;
          }
        } /* switch (quantum_size) */
      if (image->matte)
        {
          value=MaxRGB-pixel->opacity;
          switch (quantum_size)
            {
            case 32:
              {
                *q++=(unsigned char) (value >> 24);
                *q++=(unsigned char) (value >> 16);
                *q++=(unsigned char) (value >> 8);
                *q++=(unsigned char) value;
                break;
              }
            case 16:
              {
                *q++=(unsigned char) (value >> 8);
                *q++=(unsigned char) value;
                break;
              }
            case 8:
              {
                *q++=(unsigned char) value;
                break;
              }
            } /* switch (quantum_size) */
        }
    }
  else
    {
      switch (quantum_size)
        {
        case 8:
          {
            *q++=ScaleQuantumToChar(pixel->red);
            *q++=ScaleQuantumToChar(pixel->green);
            *q++=ScaleQuantumToChar(pixel->blue);
            if (image->colorspace == CMYKColorspace)
              {
                *q++=ScaleQuantumToChar(pixel->opacity);
                if (image->matte)
                  *q++=ScaleQuantumToChar(index);
              }
            else
              if (image->matte)
                *q++=ScaleQuantumToChar(MaxRGB-pixel->opacity);
            break;
          }
        case 16:
          {
            value=ScaleQuantumToShort(pixel->red);
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            value=ScaleQuantumToShort(pixel->green);
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            value=ScaleQuantumToShort(pixel->blue);
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            if (image->colorspace == CMYKColorspace)
              {
                value=ScaleQuantumToShort(pixel->opacity);
                *q++=(unsigned char) (value >> 8);
                *q++=(unsigned char) value;
                if (image->matte)
                  {
                    value=ScaleQuantumToShort(MaxRGB-index);
                    *q++=(unsigned char) (value >> 8);
                    *q++=(unsigned char) value;
                  }
              }
            else
              if (image->matte)
                {
                  value=ScaleQuantumToShort(MaxRGB-pixel->opacity);
                  *q++=(unsigned char) (value >> 8);
                  *q++=(unsigned char) value;
                }
            break;
          }
        case 32:
          {
            value=ScaleQuantumToLong(pixel->red);
            *q++=(unsigned char) (value >> 24);
            *q++=(unsigned char) (value >> 16);
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            value=ScaleQuantumToLong(pixel->green);
            *q++=(unsigned char) (value >> 24);
            *q++=(unsigned char) (value >> 16);
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            value=ScaleQuantumToLong(pixel->blue);
            *q++=(unsigned char) (value >> 24);
            *q++=(unsigned char) (value >> 16);
            *q++=(unsigned char) (value >> 8);
            *q++=(unsigned char) value;
            if (image->colorspace == CMYKColorspace)
              {
                value=ScaleQuantumToLong(pixel->opacity);
                *q++=(unsigned char) (value >> 24);
                *q++=(unsigned char) (value >> 16);
                *q++=(unsigned char) (value >> 8);
                *q++=(unsigned char) value;
                if (image->matte)
                  {
                    value=ScaleQuantumToLong(MaxRGB-index);
                    *q++=(unsigned char) (value >> 24);
                    *q++=(unsigned char) (value >> 16);
                    *q++=(unsigned char) (value >> 8);
                    *q++=(unsigned char) value;
                  }
              }
            else
              if (image->matte)
                {
                  value=ScaleQuantumToLong(MaxRGB-pixel->opacity);
                  *q++=(unsigned char) (value >> 24);
                  *q++=(unsigned char) (value >> 16);
                  *q++=(unsigned char) (value >> 8);
                  *q++=(unsigned char) value;
                }
          }
        }  /* switch (quantum_size) */
    }
  *q++=(unsigned char) length;
  *qp=q;
}

#define ThrowMIFFWriterException(code_,reason_,image_) \
{ \
  MagickFreeResourceLimitedMemory(compress_pixels) \
  MagickFreeResourceLimitedMemory(pixels); \
  ThrowWriterException(code_,reason_,image_); \
}

static unsigned int WriteMIFFImage(const ImageInfo *image_info,Image *image)
{

#if defined(HasBZLIB)
  bz_stream
    bzip_info;
#endif

  char
    buffer[MaxTextExtent];

  CompressionType
    compression;

  const ImageAttribute
    *attribute;

  IndexPacket
    index;

  long
    y;

  PixelPacket
    pixel;

  QuantumType
    quantum_type;

  register const PixelPacket
    *p;

  register const IndexPacket
    *indexes;

  register long
    i,
    x;

  unsigned char
    *q;

  size_t
    length;

  unsigned char
    *compress_pixels = (unsigned char *) NULL,
    *pixels = (unsigned char *) NULL;

  unsigned int
    depth,
    status,
    quantum_size;

  unsigned long
    packet_size,
    scene;

  ImageProfileIterator
    profile_iterator;

  const char
    *profile_name;

  const unsigned char
    *profile_info;

  size_t
    profile_length;

#if defined(HasZLIB)
  z_stream
    zip_info;
#endif

  size_t
    image_list_length;

  /*
    Open output image file.
  */
  assert(image_info != (const ImageInfo *) NULL);
  assert(image_info->signature == MagickSignature);
  assert(image != (Image *) NULL);
  assert(image->signature == MagickSignature);
  image_list_length=GetImageListLength(image);
  status=OpenBlob(image_info,image,WriteBinaryBlobMode,&image->exception);
  if (status == False)
    ThrowWriterException(FileOpenError,UnableToOpenFile,image);
  compression=image->compression;
  if (image_info->compression != UndefinedCompression)
    compression=image_info->compression;
  scene=0;
  do
  {
    /*
      Transform colorspace if necessary.
    */
    if (((image_info->colorspace != UndefinedColorspace) ||
         (image->colorspace != CMYKColorspace)) &&
         (image_info->colorspace != CMYKColorspace))
      (void) TransformColorspace(image,RGBColorspace);
    else
      (void) TransformColorspace(image,CMYKColorspace);
    /*
      Valid depths are 8/16/32
    */
    if (image->depth > 16)
      depth=32;
    else if (image->depth > 8)
      depth=16;
    else
      depth=8;
    if (image->storage_class != DirectClass)
      {
        if (image->colors > 65536)
          quantum_size=32;
        else if (image->colors > 256)
          quantum_size=16;
        else
          quantum_size=8;
      }
    else
      {
        quantum_size=depth;
      }
    /*
      Allocate image pixels.
    */
    packet_size=quantum_size/8;
    if (image->storage_class == DirectClass)
      packet_size=3*quantum_size/8;
    if (image->colorspace == CMYKColorspace)
      packet_size+=quantum_size/8;
    if (image->matte)
      packet_size+=quantum_size/8;
    if (compression == RLECompression)
      packet_size+=quantum_size/8;
    length=packet_size*image->columns;
    pixels=MagickAllocateResourceLimitedMemory(unsigned char *,length);
    length=(size_t) (1.01*packet_size*image->columns+600);
    if ((compression == BZipCompression) || (compression == ZipCompression))
      if (length != (unsigned int) length)
        compression=NoCompression;
    compress_pixels=MagickAllocateResourceLimitedMemory(unsigned char *,length);
    if ((pixels == (unsigned char *) NULL) ||
        (compress_pixels == (unsigned char *) NULL))
      ThrowMIFFWriterException(ResourceLimitError,MemoryAllocationFailed,image);
    /*
      Write MIFF header.
    */
    (void) WriteBlobString(image,"id=ImageMagick  version=1.0\n");
    if (image->storage_class == PseudoClass)
      FormatString(buffer,"class=PseudoClass  colors=%u  matte=%.1024s\n",
                   image->colors,MagickBoolToString(image->matte));
    else
      if (image->colorspace == CMYKColorspace)
        FormatString(buffer,
                     "class=DirectClass  colorspace=CMYK  matte=%.1024s\n",
                     MagickBoolToString(image->matte));
      else
        FormatString(buffer,"class=DirectClass  matte=%.1024s\n",
                     MagickBoolToString(image->matte));
    (void) WriteBlobString(image,buffer);
    *buffer='\0';
    switch(compression)
      {
      case NoCompression:
      default:
        compression=NoCompression;
        break;
      case RLECompression:
        FormatString(buffer,"compression=RLE\n");
        break;
#if defined(HasBZLIB)
      case BZipCompression:
        FormatString(buffer,"compression=BZip\n");
        break;
#endif /* defined(HasBZLIB) */
#if defined(HasZLIB)
      case ZipCompression:
        FormatString(buffer,"compression=Zip\n");
        break;
#endif /* defined(HasZLIB) */
      }
    if (*buffer != '\0')
      (void) WriteBlobString(image,buffer);
    FormatString(buffer,"columns=%lu  rows=%lu  depth=%u\n",image->columns,
      image->rows,depth);
    (void) WriteBlobString(image,buffer);
    if ((image->x_resolution != 0) && (image->y_resolution != 0))
      {
        char
          units[MaxTextExtent];

        /*
          Set image resolution.
        */
        (void) strcpy(units,"undefined");
        if (image->units == PixelsPerInchResolution)
          (void) strcpy(units,"pixels-per-inch");
        if (image->units == PixelsPerCentimeterResolution)
          (void) strcpy(units,"pixels-per-centimeter");
        FormatString(buffer,"Resolution=%gx%g  units=%.1024s\n",
          image->x_resolution,image->y_resolution,units);
        (void) WriteBlobString(image,buffer);
      }
    if ((image->page.width != 0) && (image->page.height != 0))
      {
        FormatString(buffer,"page=%lux%lu%+ld%+ld\n",image->page.width,
          image->page.height,image->page.x,image->page.y);
        (void) WriteBlobString(image,buffer);
      }
    if ((image->next != (Image *) NULL) || (image->previous != (Image *) NULL))
      {
        if (image->scene == 0)
          FormatString(buffer,"iterations=%lu  delay=%lu\n",image->iterations,
            image->delay);
        else
          FormatString(buffer,"scene=%lu  iterations=%lu  delay=%lu\n",
            image->scene,image->iterations,image->delay);
        (void) WriteBlobString(image,buffer);
      }
    else
      {
        if (image->scene != 0)
          {
            FormatString(buffer,"scene=%lu\n",image->scene);
            (void) WriteBlobString(image,buffer);
          }
        if (image->iterations != 0)
          {
            FormatString(buffer,"iterations=%lu\n",image->iterations);
            (void) WriteBlobString(image,buffer);
          }
        if (image->delay != 0)
          {
            FormatString(buffer,"delay=%lu\n",image->delay);
            (void) WriteBlobString(image,buffer);
          }
      }
    if (image->dispose != UndefinedDispose)
      {
        if (image->dispose == BackgroundDispose)
          (void) strcpy(buffer,"dispose=background\n");
        else
          if (image->dispose == NoneDispose)
            (void) strcpy(buffer,"dispose=none\n");
          else
            (void) strcpy(buffer,"dispose=previous\n");
        (void) WriteBlobString(image,buffer);
      }
    if (image->rendering_intent != UndefinedIntent)
      {
        if (image->rendering_intent == SaturationIntent)
          (void) strcpy(buffer,"rendering-intent=saturation\n");
        else
          if (image->rendering_intent == PerceptualIntent)
            (void) strcpy(buffer,"rendering-intent=perceptual\n");
          else
            if (image->rendering_intent == AbsoluteIntent)
              (void) strcpy(buffer,"rendering-intent=absolute\n");
            else
              (void) strcpy(buffer,"rendering-intent=relative\n");
        (void) WriteBlobString(image,buffer);
      }
    if (image->gamma != 0.0)
      {
        FormatString(buffer,"gamma=%g\n",image->gamma);
        (void) WriteBlobString(image,buffer);
      }
    if (image->chromaticity.white_point.x != 0.0)
      {
        /*
          Note chomaticity points.
        */
        FormatString(buffer,
          "red-primary=%g,%g  green-primary=%g,%g  blue-primary=%g,%g\n",
          image->chromaticity.red_primary.x,image->chromaticity.red_primary.y,
          image->chromaticity.green_primary.x,
          image->chromaticity.green_primary.y,
          image->chromaticity.blue_primary.x,
          image->chromaticity.blue_primary.y);
        (void) WriteBlobString(image,buffer);
        FormatString(buffer,"white-point=%g,%g\n",
          image->chromaticity.white_point.x,image->chromaticity.white_point.y);
        (void) WriteBlobString(image,buffer);
      }
    if (image->orientation != UndefinedOrientation)
      {
        FormatString(buffer,"orientation=%s\n",
                     OrientationTypeToString(image->orientation));
        (void) WriteBlobString(image,buffer);
      }
    /*
      Old MIFF readers (including GM 1.1) expect the ICC profile,
      followed by the IPTC profile, followed by any remaining
      profiles.
    */
    if ((GetImageProfile(image,"ICM",&profile_length)))
      {
        FormatString(buffer,"profile-icc=%lu\n",(unsigned long)
                     profile_length);
        (void) WriteBlobString(image,buffer);
      }
    if ((GetImageProfile(image,"IPTC",&profile_length)))
      {
        FormatString(buffer,"profile-iptc=%lu\n",(unsigned long)
                     profile_length);
        (void) WriteBlobString(image,buffer);
      }

    /*
      Generic profiles.
    */
    profile_iterator=AllocateImageProfileIterator(image);
    if (profile_iterator)
      {
        while(NextImageProfile(profile_iterator,&profile_name,&profile_info,
                               &profile_length) != MagickFail)
          {
            if ((LocaleCompare(profile_name,"ICC") == 0) ||
                (LocaleCompare(profile_name,"ICM") == 0) ||
                (LocaleCompare(profile_name,"IPTC") == 0) ||
                (LocaleCompare(profile_name,"8BIM") == 0))
              continue;
            FormatString(buffer,"profile-%.1024s=%lu\n",
                         profile_name,(unsigned long) profile_length);
            (void) WriteBlobString(image,buffer);
          }
        DeallocateImageProfileIterator(profile_iterator);
      }

    if (image->montage != (char *) NULL)
      {
        FormatString(buffer,"montage=%.1024s\n",image->montage);
        (void) WriteBlobString(image,buffer);
      }
    attribute=GetImageAttribute(image,(char *) NULL);
    for ( ; attribute != (ImageAttribute *) NULL; attribute=attribute->next)
    {
      size_t attribute_length;
      if (*attribute->key == '[')
        continue;
      FormatString(buffer,"%.1024s=",attribute->key);
      (void) WriteBlobString(image,buffer);
      attribute_length=strlen(attribute->value);
      for (i=0; i < (long) attribute_length; i++)
        if (isspace((int) attribute->value[i]))
          break;
      if (i < (long) attribute_length)
        (void) WriteBlobByte(image,'{');
      (void) WriteBlob(image,attribute_length,attribute->value);
      if (i < (long) attribute_length)
        (void) WriteBlobByte(image,'}');
      (void) WriteBlobByte(image,'\n');
    }
    (void) WriteBlobString(image,"\f\n:\032");
    if (image->montage != (char *) NULL)
      {
        /*
          Write montage tile directory.
        */
        if (image->directory != (char *) NULL)
          (void) WriteBlob(image,strlen(image->directory),image->directory);
        (void) WriteBlobByte(image,'\0');
      }
    /*
      Color profile.
    */
    if ((profile_info=GetImageProfile(image,"ICM",&profile_length)))
      (void) WriteBlob(image,profile_length, (const char *) profile_info);
    /*
      IPTC profile.
    */
    if ((profile_info=GetImageProfile(image,"IPTC",&profile_length)))
      (void) WriteBlob(image,profile_length,(const char *) profile_info);
    /*
      Generic profiles.
    */
    profile_iterator=AllocateImageProfileIterator(image);
    while(NextImageProfile(profile_iterator,&profile_name,&profile_info,
                           &profile_length) != MagickFail)
      {
        if ((LocaleCompare(profile_name,"ICC") == 0) ||
            (LocaleCompare(profile_name,"ICM") == 0) ||
            (LocaleCompare(profile_name,"IPTC") == 0) ||
            (LocaleCompare(profile_name,"8BIM") == 0))
          continue;

        (void) WriteBlob(image,profile_length,(const char *) profile_info);
      }
    DeallocateImageProfileIterator(profile_iterator);

    if (image->storage_class == PseudoClass)
      {
        unsigned char
          *colormap;

        unsigned int
          packet_size;

        /*
          Allocate colormap.
        */
        packet_size=3*depth/8;
        colormap=MagickAllocateResourceLimitedArray(unsigned char *,packet_size,image->colors);
        if (colormap == (unsigned char *) NULL)
          ThrowMIFFWriterException(ResourceLimitError,MemoryAllocationFailed,
                                   image);
        /*
          Write colormap to file.
        */
        q=colormap;
        switch (depth)
          {
          case 8:
            {
              for (i=0; i < (long) image->colors; i++)
                {
                  *q++=ScaleQuantumToChar(image->colormap[i].red);
                  *q++=ScaleQuantumToChar(image->colormap[i].green);
                  *q++=ScaleQuantumToChar(image->colormap[i].blue);
                }
              break;
            }
#if QuantumDepth > 8
          case 16:
            {
              for (i=0; i < (long) image->colors; i++)
                {
                  *q++=ScaleQuantumToShort(image->colormap[i].red) >> 8;
                  *q++=ScaleQuantumToShort(image->colormap[i].red);
                  *q++=ScaleQuantumToShort(image->colormap[i].green) >> 8;
                  *q++=ScaleQuantumToShort(image->colormap[i].green);
                  *q++=ScaleQuantumToShort(image->colormap[i].blue) >> 8;
                  *q++=ScaleQuantumToShort(image->colormap[i].blue);
                }
              break;
            }
#endif /* QuantumDepth > 8 */
#if QuantumDepth > 16
          case 32:
            {
              for (i=0; i < (long) image->colors; i++)
                {
                  *q++=image->colormap[i].red >> 24;
                  *q++=image->colormap[i].red >> 16;
                  *q++=image->colormap[i].red >> 8;
                  *q++=image->colormap[i].red;
                  *q++=image->colormap[i].green >> 24;
                  *q++=image->colormap[i].green >> 16;
                  *q++=image->colormap[i].green >> 8;
                  *q++=image->colormap[i].green;
                  *q++=image->colormap[i].blue >> 24;
                  *q++=image->colormap[i].blue >> 16;
                  *q++=image->colormap[i].blue >> 8;
                  *q++=image->colormap[i].blue;
                }
              break;
            }
#endif /* QuantumDepth > 16 */
          } /* switch (depth) */
        (void) WriteBlob(image,packet_size*image->colors,colormap);
        MagickFreeResourceLimitedMemory(colormap);
      }
    /*
      Write image pixels to file.
    */
    quantum_type=RGBQuantum;
    if (image->storage_class == PseudoClass)
      {
        quantum_type=IndexAlphaQuantum;
        if (!image->matte)
          quantum_type=IndexQuantum;
      }
    else
      if (image->colorspace == CMYKColorspace)
        {
          quantum_type=CMYKAQuantum;
          if (!image->matte)
            quantum_type=CMYKQuantum;
        }
      else
        {
          quantum_type=RGBAQuantum;
          if (!image->matte)
            quantum_type=RGBQuantum;
        }
    status=True;
    (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                          "Using QuantumType %s, depth %u",
                          QuantumTypeToString(quantum_type),quantum_size);
    for (y=0; y < (long) image->rows; y++)
    {
      p=AcquireImagePixels(image,0,y,image->columns,1,&image->exception);
      if (p == (const PixelPacket *) NULL)
        break;
      indexes=AccessImmutableIndexes(image);
      q=pixels;
      switch (compression)
      {
#if defined(HasZLIB)
        case ZipCompression:
        {
          int
            code;

          if (y == 0)
            {
              zip_info.zalloc=ZLIBAllocFunc;
              zip_info.zfree=ZLIBFreeFunc;
              zip_info.opaque=(voidpf) NULL;
              code=deflateInit(&zip_info,(int) Min(image_info->quality/10,9));
              status|=code >= 0;
            }
          zip_info.next_in=pixels;
          zip_info.avail_in=(uInt) (packet_size*image->columns);
          (void) ExportImagePixelArea(image,quantum_type,quantum_size,pixels,0,0);
          do
          {
            zip_info.next_out=compress_pixels;
            zip_info.avail_out=(uInt) (1.01*packet_size*image->columns+12);
            code=deflate(&zip_info,Z_NO_FLUSH);
            status|=code >= 0;
            length=zip_info.next_out-compress_pixels;
            if (length != 0)
              {
                (void) WriteBlobMSBLong(image,(const magick_uint32_t) length);
                (void) WriteBlob(image,length,compress_pixels);
              }
          } while (zip_info.avail_in != 0);
          if (y == (long) (image->rows-1))
            {
              for ( ; ; )
              {
                zip_info.next_out=compress_pixels;
                zip_info.avail_out=(uInt) (1.01*packet_size*image->columns+12);
                code=deflate(&zip_info,Z_FINISH);
                status|=code >= 0;
                length=zip_info.next_out-compress_pixels;
                if (length == 0)
                  break;
                (void) WriteBlobMSBLong(image,(const magick_uint32_t) length);
                (void) WriteBlob(image,length,compress_pixels);
              }
              status=!deflateEnd(&zip_info);
            }
          break;
        }
#endif
#if defined(HasBZLIB)
        case BZipCompression:
        {
          int
            code;

          if (y == 0)
            {
              bzip_info.bzalloc=NULL;
              bzip_info.bzfree=NULL;
              bzip_info.opaque=NULL;
              code=BZ2_bzCompressInit(&bzip_info,
                (int) Min(image_info->quality/10,9),image_info->verbose,0);
              status|=code >= 0;
            }
          bzip_info.next_in=(char *) pixels;
          bzip_info.avail_in=(unsigned int) (packet_size*image->columns);
          (void) ExportImagePixelArea(image,quantum_type,quantum_size,pixels,0,0);
          do
          {
            bzip_info.next_out=(char *) compress_pixels;
            bzip_info.avail_out=(unsigned int)
              (1.01*packet_size*image->columns+600);
            code=BZ2_bzCompress(&bzip_info,BZ_FLUSH);
            status|=code >= 0;
            length=bzip_info.next_out-(char *) compress_pixels;
            if (length != 0)
              {
                (void) WriteBlobMSBLong(image,(const magick_uint32_t) length);
                (void) WriteBlob(image,length,compress_pixels);
              }
          } while (bzip_info.avail_in != 0);
          if (y == (long) (image->rows-1))
            {
              for ( ; ; )
              {
                bzip_info.next_out=(char *) compress_pixels;
                bzip_info.avail_out=(unsigned int)
                  (1.01*packet_size*image->columns+600);
                code=BZ2_bzCompress(&bzip_info,BZ_FINISH);
                status|=code >= 0;
                length=bzip_info.next_out-(char *) compress_pixels;
                if (length == 0)
                  break;
                (void) WriteBlobMSBLong(image,(const magick_uint32_t) length);
                (void) WriteBlob(image,length,compress_pixels);
              }
              status=!BZ2_bzCompressEnd(&bzip_info);
            }
          break;
        }
#endif
        case RLECompression:
        {
          pixel=(*p);
          index=0;
          if (image->storage_class == PseudoClass)
            index=(*indexes);
          length=255;
          for (x=0; x < (long) image->columns; x++)
          {
            if ((length < 255) && (x < (long) (image->columns-1)) &&
                ColorMatch(p,(&pixel)) &&
                ((image->matte == False) || (p->opacity == pixel.opacity)))
              length++;
            else
              {
                if (x > 0)
                  WriteRunlengthPacket(image,quantum_size,&pixel,length,&q,index);
                length=0;
              }
            if (image->storage_class == PseudoClass)
              index=indexes[x];
            pixel=(*p);
            p++;
          }
          WriteRunlengthPacket(image,quantum_size,&pixel,length,&q,index);
          (void) WriteBlob(image,q-pixels,pixels);
          break;
        }
        default:
        {
          (void) ExportImagePixelArea(image,quantum_type,quantum_size,pixels,0,0);
          (void) WriteBlob(image,packet_size*image->columns,pixels);
          break;
        }
      }
      if (image->previous == (Image *) NULL)
        if (QuantumTick(y,image->rows))
          if (!MagickMonitorFormatted(y,image->rows,&image->exception,
                                      SaveImageText,image->filename,
                                      image->columns,image->rows))
            break;
    }
    MagickFreeResourceLimitedMemory(pixels);
    MagickFreeResourceLimitedMemory(compress_pixels);
    if (image->next == (Image *) NULL)
      break;
    image=SyncNextImageInList(image);
    status=MagickMonitorFormatted(scene++,image_list_length,
                                  &image->exception,SaveImagesText,
                                  image->filename);
    if (status == False)
      break;
  } while (image_info->adjoin);
  if (image_info->adjoin)
    while (image->previous != (Image *) NULL)
      image=image->previous;
  CloseBlob(image);
  return(status);
}
