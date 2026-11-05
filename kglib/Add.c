  int draw_path_cursor ( DIG *G ,void *img, int x1 , int y1 ) {
      int key;
      int x2 , y2;
      int xmin , ymin , xmax , ymax,dx=0,dy=0;
      DIALOG *D;
      int EVGAY;
      kgWC *wc;
      kgDC *dc;
      D = G->D;
      wc = G->wc;
      dc = G->dc;
      EVGAY = D->evgay;
      x2 = dc->x2;
      y2 = dc->y2;
      if ( dc->entry ) {
          kg_scr_recover ( wc ) ;
      };
      if(img != NULL) kgGetImageSize(img,&dx,&dy);
      dc->entry = 1;
      xmin = x1-dx/2 , xmax = xmin+dx;;
      ymin = y1-dy/2; ymax = ymin + dy;;
      kg_scr_back ( wc , xmin , ymin , xmax , ymax ) ;
      kgImage(wc->D,img, xmin , ymin , abs(xmax-xmin) , abs(ymax-ymin),0.0,0.9 ) ;
//      _uiDraw_Bound ( wc , xmin , ymin , xmax , ymax ) ;
      x2 = x1 , y2 = y1;
      uiUpdateOn ( wc->D ) ;
      dc->x2 = x2 , dc->y2 = y2;
      return ( key ) ;
  }
  char kgPathPoints ( DIG *G , void *image,int *n,float *xx , float *yy ) {
  /*   (xo,yo) is start point;
       (xx,yy) retuns pints selected
       n  no of points setcted;
       image , image to be drawn at each of the points
  ***************************************************/
      KBEVENT kbevent;
      DIALOG *D;
      int kb , button , event , OK = 0 , c_color; ;
      int ch , key , MAG = 0;
      int xpo , ypo , but , pointer , xorg , yorg , xorg1 , yorg1;
      int temp,xchg=0,ychg=0;;
      float dx=4 , dy=4 , xl , xu , yl , yu;
      float wx1,wy1,wx2,wy2;
      int Dxl,Dyl,Dxu,Dyu;
      int Dwxl,Dwyl,Dwxu,Dwyu;
      Dlink *Plist=Dopen();      
      typedef struct _Pnt { int x;int y;} PNT;
      PNT *ptmp=NULL;;
      float xbgn=0.,ybgn=0;
      D = ( DIALOG * ) G->D;
      kgWC *wc;
      kgDC *dc;
      void *img=NULL,*bimg =NULL;;
      wc = G->wc;
      dc = G->dc;
      kgGetWindow(G,&wx1,&wy1,&wx2,&wy2);
      xbgn = wx1+(wx2-wx1)/2;
      ybgn = wy1+(wy2-wy1)/2;
      kgCrorssCursor(G,&xbgn,&ybgn);
      xl = wx1;
      xu = wx2;
      yl = wy1;
      yu = wy2;
      if ( G->D_ON == 0 ) {
          MAG = G->MAG;
          kgAntialiasingOff ( G ) ;
      }
      kgGetDeviceCord(G,xbgn,ybgn,&Dxl,&Dyl);
      kgGetDeviceCord(G,wx1,wy1,&Dwxl,&Dwyu);
      kgGetDeviceCord(G,wx2,wy2,&Dwxu,&Dwyl);
      if(image != NULL) kgGetImageSize(img,&dx,&dy);
      else {
        bimg = kgCreateImage(dx,dy);
        kgSetImageColor(bimg,0,100,120);
        image = bimg;
      }
      Dyu = Dyl+dy;
      Dxu = Dxl+dx;
      img = kgChangeSizeImage(image,abs(Dxu-Dxl),abs(Dyu - Dyl));
      kgAddTransparency(img,0.3);
      dc->entry = 0;
      temp = dc->c_bound;
      dc->c_bound = 14;
      uiset_clr ( D , 8 ) ;
      c_color = wc->c_color;
      xorg1 = Dxu;
      yorg1 = Dyu;
      xorg = Dxl;
      yorg = Dyl;
      dc->gcur_x = xorg;
      dc->gcur_y = yorg;
      xorg = ( Dxu -Dxl ) ;
      yorg = (Dyu - Dyl) ;
      uiScrn_back ( wc , dc->msg_x , dc->msg_y , 40 ) ;
      xpo = dc->gcur_x , ypo = dc->gcur_y;
      draw_cursor ( G ) ;
      draw_path_cursor ( G ,img, dc->gcur_x , dc->gcur_y ) ;
      while ( ! OK ) {
          ptmp = (PNT *)malloc(sizeof(PNT));
          ptmp->x = dc->gcur_x;
          ptmp->y = dc->gcur_y ;
          Dadd(Plist,ptmp);
          kbevent = kgSkipMouseMove ( D ) ;
          event = kbevent.event;
          button = kbevent.button;
          kb = kbevent.key;
          if ( ( event == 0 ) || ( event == 3 ) ) {
              if ( kbevent.x+xorg > Dwxu ) kbevent.x = Dwxu - xorg;
              if ( kbevent.y + yorg > Dwyu ) kbevent.y = Dwyu - yorg;
              if ( kbevent.x < Dwxl ) kbevent.x = Dwxl;
              if ( kbevent.y < Dwyl ) kbevent.y = Dwyl;
          }
          xpo = kbevent.x;
          ypo = kbevent.y;
          switch ( event ) {
              case 0: // pointer movement
              case 3: // button press and movement
              if ( ( xpo != dc->gcur_x ) || ( ypo != dc->gcur_y ) ) {
                  dc->gcur_x = xpo , dc->gcur_y = ypo;
                  draw_path_cursor ( G ,img, dc->gcur_x , dc->gcur_y ) ;
                  draw_po_cursor ( G ) ;
              }
              break;
              case 1: // button press
              if ( ( xpo != dc->gcur_x ) || ( ypo != dc->gcur_y ) ) {
                  dc->gcur_x = xpo , dc->gcur_y = ypo;
                  draw_path_cursor ( G ,img, dc->gcur_x , dc->gcur_y ) ;
                  draw_po_cursor ( G ) ;
              }
              if ( button == 1 ) key = '\r';
              if ( button == 3 ) key = '.';
              OK = 1;
              continue;
              case 5: // key release
              key = kb;
              if ( ui_Linefeed ( kb ) ) { key = '\r'; OK = 1; continue; }
              if ( ui_Return ( kb ) ) {key = '\r'; OK = 1; continue; }
              if ( ( kb >= '0' ) && ( kb <= '9' ) ) {dc->jmp = kb-'0'; continue; }
              if ( ( kb == '.' ) || ( kb == 'u' ) || ( kb == 'U' ) ) {
                  OK = 1; continue;
              }
              if ( ui_Uparrow ( kb ) ) { cursor_up ( dc ) ; draw_path_cursor \
               ( G , img, dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Downarrow ( kb ) ) { cursor_down ( dc ) ; draw_path_cursor \
               ( G ,img,  dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Leftarrow ( kb ) ) { cursor_left ( dc ) ; draw_path_cursor \
               ( G , img, dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Rightarrow ( kb ) ) { cursor_right ( dc ) ; draw_path_cursor \
               ( G , img,dc->gcur_x , dc->gcur_y ) ; break; }
              break;
              default:
              break;
          }
      }
      jump:
          ptmp = (PNT *)malloc(sizeof(PNT));
          ptmp->x = dc->gcur_x;
          ptmp->y = dc->gcur_y ;
          Dadd(Plist,ptmp);
      dc->c_bound = temp;
      uiset_clr ( D , c_color ) ;
      if ( dc->entry ) {
          kg_scr_recover ( wc ) ;
      };
      uiScrn_recover ( wc ) ;
      if ( kbevent.x+xorg > Dwxu ) kbevent.x = Dwxu - xorg;
      if ( kbevent.y + yorg > Dwyu ) kbevent.y = Dwyu - yorg;
      if ( kbevent.x < Dwxl ) kbevent.x = Dwxl;
      if ( kbevent.y < Dwyl ) kbevent.y = Dwyl;
      dc->gcur_x = kbevent.x;
      dc->gcur_y = kbevent.y;
#if 0
      *xx = uiusr_x ( dc->gcur_x ) ;
      *yy = uiusr_y ( ( D->evgay-dc->gcur_y ) ) ;
      xbgn = *xx+dx;
      ybgn = *yy-dy;
      if(xchg ){xl = *xx;*xx=xbgn;xbgn=xl;}
      if(ychg ){yl = *yy;*yy=*ybgn;*ybgn=yl;}
#endif
      if ( MAG ) {
          kgAntialiasingOn ( G , MAG-1 ) ;
      }
      if(img!=NULL)kgFreeImage(img);
      if(bimg!=NULL)kgFreeImage(img);
      return ( key ) ;
  }
