  int draw_box_cursor ( DIG *G , int x0 , int y0 , int x1 , int y1 ) {
      int key;
#if 1
      int x2 , y2;
      int xmin , ymin , xmax , ymax;
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
 //     if ( dc->entry == 0 ) {x2 = -100; y2 = -100; }
      if ( dc->entry ) {
          kg_scr_recover ( wc ) ;
          kg_scr_recover ( wc ) ;
          kg_scr_recover ( wc ) ;
          kg_scr_recover ( wc ) ;
      };
      dc->entry = 1;
      xmin = x1 , xmax = x1+x0;
      ymin = y1; ymax = y1+y0;
      kg_scr_back ( wc , xmin , ymin , xmax , ymin+1 ) ;
      kg_scr_back ( wc , xmin , ymax-1 , xmax , ymax ) ;
      kg_scr_back ( wc , xmin , ymin , xmin+1 , ymax ) ;
      kg_scr_back ( wc , xmax-1 , ymin , xmax , ymax ) ;
      _uiDraw_Bound ( wc , xmin , ymin , xmax , ymax ) ;
      x2 = x1 , y2 = y1;
      uiUpdateOn ( wc->D ) ;
#endif
      dc->x2 = x2 , dc->y2 = y2;
      return ( key ) ;
  }
  char kgBoxCursor ( DIG *G ,float *xx , float *yy , \
  float *xbgn , float *ybgn ) \
  /*   (xbgn,ybgn) initial upper left corner
       (xx,yy) is lower right corner
       (xbgn,ybgn) not updated
       New position to lower left corner is send 
       through (xx,yy)
  ***************************************************/
  {
      KBEVENT kbevent;
      DIALOG *D;
      int kb , button , event , OK = 0 , c_color; ;
      int ch , key , MAG = 0;
      int xpo , ypo , but , pointer , xorg , yorg , xorg1 , yorg1;
      int temp,xchg=0,ychg=0;;
      float dx , dy , xl , xu , yl , yu;
      float wx1,wy1,wx2,wy2;
      int Dxl,Dyl,Dxu,Dyu;
      int Dwxl,Dwyl,Dwxu,Dwyu;
      D = ( DIALOG * ) G->D;
      kgWC *wc;
      kgDC *dc;
      void *img=NULL;
      wc = G->wc;
      dc = G->dc;
      kgGetWindow(G,&wx1,&wy1,&wx2,&wy2);
      if(*xbgn > *xx ){xl = *xx;*xx=*xbgn;*xbgn=xl;xchg=1;}
      if(*ybgn < *yy ){yl = *yy;*yy=*ybgn;*ybgn=yl;ychg=1;}
      dx = *xx - *xbgn;
      dy = *ybgn - *yy;
      if(dx > (wx2-wx1)) return 0;
      if(dy > (wy2-wy1)) return 0;
      xl = wx1;
      xu = wx2;
      yl = wy1;
      yu = wy2;
      if ( G->D_ON == 0 ) {
          MAG = G->MAG;
          kgAntialiasingOff ( G ) ;
      }
      kgGetDeviceCord(G,*xbgn,*ybgn,&Dxl,&Dyl);
      kgGetDeviceCord(G,*xx,*yy,&Dxu,&Dyu);
      kgGetDeviceCord(G,wx1,wy1,&Dwxl,&Dwyu);
      kgGetDeviceCord(G,wx2,wy2,&Dwxu,&Dwyl);
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
      draw_box_cursor ( G , xorg , yorg , dc->gcur_x , dc->gcur_y ) ;
      while ( ! OK ) {
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
                  draw_box_cursor ( G , xorg , yorg , dc->gcur_x , dc->gcur_y ) ;
                  draw_po_cursor ( G ) ;
              }
              break;
              case 1: // button press
              if ( ( xpo != dc->gcur_x ) || ( ypo != dc->gcur_y ) ) {
                  dc->gcur_x = xpo , dc->gcur_y = ypo;
                  draw_box_cursor ( G , xorg , yorg , dc->gcur_x , dc->gcur_y ) ;
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
              if ( ui_Uparrow ( kb ) ) { cursor_up ( dc ) ; draw_box_cursor \
               ( G , xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Downarrow ( kb ) ) { cursor_down ( dc ) ; draw_box_cursor \
               ( G , xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Leftarrow ( kb ) ) { cursor_left ( dc ) ; draw_box_cursor \
               ( G , xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Rightarrow ( kb ) ) { cursor_right ( dc ) ; draw_box_cursor \
               ( G ,xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              break;
              default:
              break;
          }
      }
      jump:
      dc->c_bound = temp;
      uiset_clr ( D , c_color ) ;
      if ( dc->entry ) {
//          kg_scr_recover ( wc ) ;
//          kg_scr_recover ( wc ) ;
//          kg_scr_recover ( wc ) ;
          kg_scr_recover ( wc ) ;
      };
      uiScrn_recover ( wc ) ;
      if ( kbevent.x+xorg > Dwxu ) kbevent.x = Dwxu - xorg;
      if ( kbevent.y + yorg > Dwyu ) kbevent.y = Dwyu - yorg;
      if ( kbevent.x < Dwxl ) kbevent.x = Dwxl;
      if ( kbevent.y < Dwyl ) kbevent.y = Dwyl;
      dc->gcur_x = kbevent.x;
      dc->gcur_y = kbevent.y;
      *xx = uiusr_x ( dc->gcur_x ) ;
      *yy = uiusr_y ( ( D->evgay-dc->gcur_y ) ) ;
      *xbgn = *xx+dx;
      *ybgn = *yy-dy;
      if(xchg ){xl = *xx;*xx=*xbgn;*xbgn=xl;}
      if(ychg ){yl = *yy;*yy=*ybgn;*ybgn=yl;}
      if ( MAG ) {
          kgAntialiasingOn ( G , MAG-1 ) ;
      }
      if(img!=NULL)kgFreeImage(img);
      return ( key ) ;
  }
