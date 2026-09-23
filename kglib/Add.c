  void *uiMergegmImages ( GMIMG *png1 , GMIMG *png2 , int Xshft , int Yshft ) {
/*
  Second Picture is put on the first and the
  pointer to the first picture is returned
*/
      int w , h , bkgrclr , xsize , ysize;
      float rzfac;
      int i , j , sloc = 0 , dloc;
      unsigned int opacity , alpha , alphas;
      int xoff , yoff;
      float f , f1,fs,fd,aout;
      GMIMG *dpng = NULL;
      Image *image , *tmpimg , *simage , *oimage;
      PixelPacket *spixels , *pixels , *opixels;
      unsigned char r , g , b , bg_r , bg_g , bg_b;
      unsigned int red , green , blue;
      if ( png1 == NULL ) return NULL;
      if ( png2 == NULL ) return NULL;
      image = ( Image * ) ( png1->image ) ;
      simage = ( Image * ) ( png2->image ) ;
      uiInitGm ( ) ;
      spixels = GetImagePixels ( simage , 0 , 0 , simage->columns , simage->rows ) ;
      pixels = GetImagePixels ( image , 0 , 0 , image->columns , image->rows ) ;
      w = image->columns;
      h = image->rows;
      xsize = image->columns;
      ysize = image->rows;
      xoff = ( xsize - simage->columns ) *0.5+Xshft;
      yoff = ( ysize - simage->rows ) *0.5+Yshft;
      sloc = 0;
      for ( j = yoff;j < ( yoff+simage->rows ) ;j++ ) {
          for ( i = xoff;i < ( xoff+simage->columns ) ;i++ ) {
              opacity = spixels [ sloc ] .opacity;
              alpha = 255- opacity;
              if ( ( alpha == 0 ) ) {sloc++;continue;}
              dloc = ( j*xsize+i ) ;
              opacity = pixels [ dloc ] .opacity;
              alphas = 255 -opacity;
              if ( alpha == 0xff ) {
                  pixels[dloc].blue = spixels [ sloc ] .blue;
                  pixels[dloc].green = spixels [ sloc ] .green;
                  pixels[dloc].red = spixels [ sloc ] .red;
                  pixels[dloc].opacity = spixels [ sloc ] .opacity ;
              }
              else {
                  fd = 1-pixels [ dloc ] .opacity/255.0; ;
                  fs = 1. - spixels [ sloc ] .opacity/255.0;
                  fd = fd*(1- fs);
                  float aout = fs +fd;
                  fs = fs/(aout);               
                  fd = fd/(aout);
                  pixels [ dloc ] .blue = fd*pixels [ dloc ] .blue+fs* spixels [ sloc ] .blue;
//                  if ( pixels [ dloc ] .blue >255 ) pixels [ dloc ] .blue =255;
                  pixels [ dloc ] .green = fd*pixels [ dloc ] .green+fs* spixels [ sloc ] .green;
//                  if ( pixels [ dloc ] .green>255 ) pixels [ dloc ] .green=255;
                  pixels [ dloc ] .red = fd*pixels [ dloc ] .red+fs* spixels [ sloc ] .red;
//                  if ( pixels [ dloc ] .red>255 ) pixels [ dloc ] .red=255;
                  pixels [ dloc ] .opacity = (1.-aout)*255;;
                  if(pixels [ dloc ] .opacity > 255 ) pixels [ dloc ] .opacity =255;
              }
              sloc++;
          }
      }
      SyncImagePixels ( image ) ;
      return png1;
  }
