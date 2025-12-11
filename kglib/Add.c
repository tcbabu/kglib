  void *ui_MakeStringImage ( void *str , int font , float width ) {
      int ret = 0 , i , j , OK , xl , yl , count = 0 , \
      k , color , r , g , b , fcolor;
      float ln , length = 0 ;
      float w_x1 = 0.0 , w_y1 = 0.0 , w_x2 = 686 , w_y2 = 226 , dyl , dxl , yy;
      float h , s , v , Vb , rf , gf , bf;
      void *fid , *Img;
      float rfac = xo , yo , l , w;
      char *pt , buf [ 5000 ] ;
      Dlink *S = NULL;
      if ( str == NULL ) return NULL;
      S = Dopen;
      strcpy ( buf , ( char * ) str ) ;
      pt = buf;
      j = 1;
      k = 0;
      while ( 1 ) {
          i = 0;
          if ( pt [ i ] == '\0' ) break;
          Dadd ( S , pt ) ;
          j++;
          OK = 1;
          while ( pt [ i ] != '\0' ) {
              OK = 0;
              if ( ( pt [ i ] == '\n' ) ) { pt [ i ] = '\0';break;}
              if ( ( ( pt [ i ] == '\\' ) && ( pt [ i+1 ] == 'n' ) ) ) \
              { pt [ i ] = '\0';i++;break;}
              i++;
              OK = 1;
          }
          str [ k++ ] = pt;
          ln = ftStringLength ( font , pt , width ) ;
          if ( length < ln ) length = ln;
          if ( OK ) break;
          pt = pt+i+1;
      }
      count = Dcount ( S ) ;
      xl = 1.1*length;
      yl = 2*width*count;
      w_x2 = xl;
      w_y2 = yl;
      l = xl;
      w = yl;
      fid = kgInitImage ( ( int ) ( w_x2-w_x1 ) , ( int ) ( w_y2-w_y1 ) , 2 ) ;
      kgUserFrame ( fid , w_x1-3 , w_y1-3 , w_x2+3 , w_y2+3 ) ;
      fcolor = 901;
      r = 240;
      g = 240;
      b = 220;
      kgChangeColor ( fid , 901 , r , g , b ) ;
      color = 902;
      kgChangeColor ( fid , 902 , 20 , 20 , 20 ) ;
      kgGetRGB ( ( DIG * ) fid , fcolor , & r , & g , & b ) ;
      rf = r;gf = g;bf = b;
      RGBtoHSV ( rf , gf , bf , & h , & s , & v ) ;
      Vb = 1.5*v;
      if ( Vb > 1. ) Vb = 1.;
      HSVtoRGB ( & rf , & gf , & bf , h , s , Vb ) ;
      kgChangeColor ( fid , 152 , ( int ) rf , ( int ) gf , ( int ) bf ) ;
      HSVtoRGB ( & rf , & gf , & bf , h , s , 0.5*v ) ;
      kgChangeColor ( fid , 153 , ( int ) rf , ( int ) gf , ( int ) bf ) ;
      kgChangeColor ( fid , 151 , ( int ) r , ( int ) g , ( int ) b ) ;
      kgTextColor ( fid , color ) ;
      kgTextFont ( fid , font ) ;
      kgTextSize ( fid , 1.2*width , width , 0. ) ;
      xo = ( w_x1+w_x2 ) *.5;
      yo = ( w_y1+w_y2 ) *.5;
      kgRoundedRectangleFill ( fid , xo , yo , ( float ) l+2 , \
       ( float ) w+2 , 0 , 153 , rfac ) ;
      kgRoundedRectangleFill ( fid , xo , yo , ( float ) l+1 , \
       ( float ) w+1 , 0 , 152 , rfac ) ;
      kgRoundedRectangleFill ( fid , xo , yo , ( float ) l-4 , \
       ( float ) w-4 , 0 , 151 , rfac ) ;
      k = count;
      Resetlink ( S ) ;
      yy = yl-1.7*width;
      dyl = 2*width;
      while ( ( pt = ( char * ) Getrecord ( S ) ) != NULL ) {
          lng = ftStringLength ( font , pt , width ) ;
          kgMove2f ( fid , ( xl-ln ) *0.5 , yy ) ;
          kgWriteText ( fid , pt ) ;
          yy -= dyl;
      }
      Img = kgGetSharpImage ( fid ) ;
      kgCloseImage ( fid ) ;
      Dfree ( S ) ;
      return Img;
  }
