  int uiDraw_Dialog ( DIALOG *D ) {
      int n , i , controls = 0 , item , ch , oldi = -1;
      DIA *d;
      d = D->d;
      D->df = 0;
      if ( D->DrawBkgr == 1 ) _ui_Draw_Dialog_Area_Transparent ( D ) ;
      if ( D->Bkpixmap != NULL ) kgImage ( ( D ) , D->Bkpixmap , 0 , 0 , D->xl , D->yl , D->transparency , 1.0 ) ;
          
      i = 0;
      while ( d [ i ] .t != NULL ) {
          ch = ( d [ i ] .t->code ) ;
          switch ( ( int ) ch ) {
              case 'o': /* progress bar */
              _uiDrawO ( D , i ) ;
              break;
              case 'p': /* new for xpm display */
//         _uiDrawTransparentPicture(D,i);
              _uiDrawP ( D , i ) ;
              break;
              case 'i': /* info box */
//         _uiDrawInfo(D,i);
              _uiDrawI ( D , i ) ;
              break;
              case 'x': // new type browser
              _uiDrawX ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'v': // Vert scroll bar
              _uiDrawV ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'z': // Vert scroll bar
              _uiDrawZ ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'y': // new type browser
              _uiDrawY ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'r': // new type browser
              _uiDrawRadioButton ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'c': // new type browser
              _uiDrawCheckBox ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 't':
#if 1
              _uiDrawTextBox ( D , i ) ;
#endif
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
                  if ( D->InputWid < 0 ) D->InputWid = i;
              }
              break;
              case 'T':
              _uiDrawTableBox ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
                  if ( D->InputWid < 0 ) D->InputWid = i;
              }
              break;
              case 'h':
              _uiDrawN ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'H':
              _uiDrawHoriButtons ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'n':
              _uiDrawN ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'b':
              case 'N':
              _uiDrawB ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'f':
              _uiDrawSlideFloat ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'P':
              _uiDrawHbar ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'd':
              _uiDrawSlideInteger ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'w':
              _uiDrawBrowser ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'e':
              _uiDrawE ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 's':
              _uiDrawScrollMsgItem ( D , i ) ;
              if ( kgGetWidgetVisibility ( kgGetWidget ( D , i ) ) != 0 ) {
                  controls++;
                  D->df = i;
              }
              break;
              case 'g':
              _uiDrawGraphicsArea ( D , i ) ;
              break;
              case 'm':
              case 'M':
              case 'B':
              _uiDrawMessage ( D , i ) ;
              break;
              default:
              printf ( "Error: in dialog : wrong code |%c| \n" , ch ) ;
              exit ( 0 ) ;
          }
          i++;
      }
      D->controls = controls;
      D->TotWid = i;
      return controls;
  }
