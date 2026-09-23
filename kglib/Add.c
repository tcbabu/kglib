  void imgCopyImage ( DIG *G , int x0 , int y0 , GMIMG *img ) {
      GMIMG *Dimg , *Simg;
      kgDC *dc;
      kgWC *wc;
      PixelPacket *pixels , *spixels;
      int w , h , iw , ih , i , j , ii , jj , sloc , dloc , cx0 , cx1 , cy0 , cy1;
      int channels;
      float fs,fd;
      dc = G->dc;
      wc = G->wc;
      Simg = ( GMIMG * ) img;
      Dimg = G->img;
      iw = Dimg->image_width;
      ih = Dimg->image_height;
      w = Simg->image_width;
      h = Simg->image_height;
      channels = Simg->image_channels;
      cx0 = wc->c_v_x1;
      cx1 = wc->c_v_x2;
      cy0 = dc->EVGAY-1-wc->c_v_y2;
      cy1 = dc->EVGAY-1-wc->c_v_y1;
//  printf("%d %d %d %d\n",cx0,cy0,cx1,cy1);
      spixels = GetImagePixels ( ( Image * ) ( Simg->image ) , 0 , 0 , ( ( Image * )  \
          ( Simg->image ) )->columns , ( ( Image * ) ( Simg->image ) )->rows ) ;
      pixels = G->pixels;
//      printf("Channels = %d\n",channels);
      for ( j = 0;j < ( h ) ;j++ ) {
          jj = j+y0;
          if ( jj < cy0 ) continue;
          if ( jj >= cy1 ) break;
          if ( jj >= ih ) break;
          for ( i = 0;i < w;i++ ) {
              ii = i+x0;
              if ( ii < cx0 ) continue;
              if ( ii > cx1 ) continue;
              if ( ii >= iw ) continue;
              sloc = j*w+i;
              dloc = jj*iw+ii;
              if ( ( channels != 4 )  ) {
                  pixels [ dloc ] .blue = spixels [ sloc ] .blue;
                  pixels [ dloc ] .green = spixels [ sloc ] .green;
                  pixels [ dloc ] .red = spixels [ sloc ] .red;
                  pixels [ dloc ] .opacity = 255;
              }
              else {
                if( spixels [ sloc ] .opacity == 255 ) continue;
                if( spixels [ sloc ] .opacity == 0 ) {
                  pixels [ dloc ] .blue = spixels [ sloc ] .blue;
                  pixels [ dloc ] .green = spixels [ sloc ] .green;
                  pixels [ dloc ] .red = spixels [ sloc ] .red;
                  pixels [ dloc ] .opacity = spixels [ sloc ] .opacity;
                }
                else {
                  fd = 1-pixels [ dloc ] .opacity/255.0; ;
                  fs = 1. - spixels [ sloc ] .opacity/255.0;
                  fd = fd*(1- fs);
                  float aout = fs +fd;
                  fs = fs/(fs+fd);               
                  fd = fd/(fs+fs);
                  pixels [ dloc ] .blue = fd*pixels [ dloc ] .blue+fs* spixels [ sloc ] .blue;
//                  if ( pixels [ dloc ] .blue >255 ) pixels [ dloc ] .blue =255;
                  pixels [ dloc ] .green = fd*pixels [ dloc ] .green+fs* spixels [ sloc ] .green;
//                  if ( pixels [ dloc ] .green>255 ) pixels [ dloc ] .green=255;
                  pixels [ dloc ] .red = fd*pixels [ dloc ] .red+fs* spixels [ sloc ] .red;
//                  if ( pixels [ dloc ] .red>255 ) pixels [ dloc ] .red=255;
                  pixels [ dloc ] .opacity = (1.-aout)*255;;
                  if(pixels [ dloc ] .opacity > 255 ) pixels [ dloc ] .opacity =255;
                }
              }
//TCB
//      printf("%x %x %x %x\n",pixels[dloc].blue,pixels[dloc].green,pixels[dloc].red,pixels[dloc].opacity);
//      pixels[dloc].red=255;
          }
      }
      return;
  }
