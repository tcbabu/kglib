  int draw_image_cursor ( DIG *G ,void *img, int x0 , int y0 , int x1 , int y1 ) {
      int key;
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
      if ( dc->entry == 0 ) {x2 = -100; y2 = -100; }
      if ( dc->entry ) {
          kg_scr_recover ( wc ) ;
      };
      dc->entry = 1;
      xmin = x0 , xmax = x1;
      if(xmin>xmax ) {xmin = x1;xmax = x0;}
      ymin = y0; ymax = y1;
      if(ymin>ymax ) {ymin = y1;ymax = y0;}

      kg_scr_back ( wc , xmin , ymin , xmax , ymax ) ;
      kgImage(wc->D,img,xmin,ymin,xmax-xmin,ymax-ymin,0.,1.0);
      x2 = x1 , y2 = y1;
      uiUpdateOn ( wc->D ) ;
      dc->x2 = x2 , dc->y2 = y2;
      return ( key ) ;
  }
  char kgImageCursor ( DIG *G , void *image,float *xx , float *yy , \
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
      int temp;
      float dx , dy , xl , xu , yl , yu;
      D = ( DIALOG * ) G->D;
      kgWC *wc;
      kgDC *dc;
      void *img=NULL;
      wc = G->wc;
      dc = G->dc;
      xl = uiusr_x ( G->x1 ) ;
      xu = uiusr_x ( G->x2 ) ;
      yl = uiusr_y ( ( D->evgay-G->y2 ) ) ;
      yu = uiusr_y ( ( D->evgay-G->y1 ) ) ;
      if ( *xbgn < xl ) *xbgn = xl;
      if ( *xx > xu ) *xx = xu;
      if ( *ybgn > yu ) *ybgn = yu;
      if ( *yy < yl ) *yy = yl;
      if ( *xbgn > xu ) *xbgn = xl;
      if ( *ybgn < yl ) *ybgn = yu;
      dx = *xx - *xbgn;
      dy = *ybgn - *yy;
      if ( dx > ( xu - xl ) ) {
          dx = xu -xl;;
          *xbgn = xl;
          *xx = xl + dx;
      }
      if ( dy > ( yu - yl ) ) {
          dy = yu -yl;
          *ybgn = yu;
          *yy = *ybgn - dy;
      }
      if ( *xx > xu ) {
          *xx = xu;
          *xbgn = *xx -dx;
      }
      if ( *yy < yl ) {
          *yy = yl;
          *ybgn = *yy+dy;
      }
      img = kgChangeSizeImage(image,abs(*xx -*xbgn),abs(*yy - *ybgn));
      if ( G->D_ON == 0 ) {
          MAG = G->MAG;
          kgAntialiasingOff ( G ) ;
      }
      dc->entry = 0;
      temp = dc->c_bound;
      dc->c_bound = 14;
      uiset_clr ( D , 8 ) ;
      c_color = wc->c_color;
      xorg1 = uiscr_x ( *xx ) ;
      yorg1 = D->evgay-uiscr_y ( *yy ) ;
      xorg = uiscr_x ( *xbgn ) ;
      yorg = D->evgay-uiscr_y ( *ybgn ) ;
      dc->gcur_x = xorg;
      dc->gcur_y = yorg;
      xorg = ( xorg1- xorg ) ;
      yorg = - ( yorg1-yorg ) ;
      uiScrn_back ( wc , dc->msg_x , dc->msg_y , 40 ) ;
      xpo = dc->gcur_x , ypo = dc->gcur_y;
      draw_cursor ( G ) ;
      draw_image_cursor ( G , img ,dc->gcur_x , dc->gcur_y ,dc->gcur_x +xorg,dc->gcur_y+yorg) ;
      while ( ! OK ) {
          kbevent = kgSkipMouseMove ( D ) ;
          event = kbevent.event;
          button = kbevent.button;
          kb = kbevent.key;
          if ( ( event == 0 ) || ( event == 3 ) ) {
              if ( kbevent.x+xorg > G->x2 ) kbevent.x = G->x2 - xorg;
              if ( kbevent.y - yorg > G->y2 ) kbevent.y = G->y2 + yorg;
              if ( kbevent.x < G->x1 ) kbevent.x = G->x1;
              if ( kbevent.y < G->y1 ) kbevent.y = G->y1;
          }
          xpo = kbevent.x;
          ypo = kbevent.y;
          switch ( event ) {
              case 0: // pointer movement
//     case 2:  // button release
              case 3: // button press and movement
              if ( ( xpo != dc->gcur_x ) || ( ypo != dc->gcur_y ) ) {
                  dc->gcur_x = xpo , dc->gcur_y = ypo;
                  draw_image_cursor ( G , img,xorg , yorg , dc->gcur_x , dc->gcur_y ) ;
                  draw_po_cursor ( G ) ;
              }
              break;
              case 1: // button press
              if ( ( xpo != dc->gcur_x ) || ( ypo != dc->gcur_y ) ) {
                  dc->gcur_x = xpo , dc->gcur_y = ypo;
                  draw_image_cursor ( G ,img, xorg , yorg , dc->gcur_x , dc->gcur_y ) ;
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
              if ( ui_Uparrow ( kb ) ) { cursor_up ( dc ) ; draw_image_cursor \
               ( G ,img, xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Downarrow ( kb ) ) { cursor_down ( dc ) ; draw_image_cursor \
               ( G , img,xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Leftarrow ( kb ) ) { cursor_left ( dc ) ; draw_image_cursor \
               ( G , img,xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              if ( ui_Rightarrow ( kb ) ) { cursor_right ( dc ) ; draw_image_cursor \
               ( G , img,xorg , yorg , dc->gcur_x , dc->gcur_y ) ; break; }
              break;
              default:
              break;
          }
      }
      jump:
      dc->c_bound = temp;
      uiset_clr ( D , c_color ) ;
      if ( dc->entry ) {
          kg_scr_recover ( wc ) ;
      };
      uiScrn_recover ( wc ) ;
      *xx = uiusr_x ( dc->gcur_x ) ;
      *yy = uiusr_y ( ( D->evgay-dc->gcur_y ) ) ;
      if ( MAG ) {
          kgAntialiasingOn ( G , MAG-1 ) ;
      }
      kgFreeImage(img);
      return ( key ) ;
  }
