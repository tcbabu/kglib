              if ( ui_Linefeed ( kb ) ) {
                 kbevent.x = dc->gcur_x ; kbevent.y = dc->gcur_y;   
                 key = '\r'; OK = 1; continue; }
              if ( ui_Return ( kb ) ) {
                 kbevent.x = dc->gcur_x ; kbevent.y = dc->gcur_y;   
                 key = '\r'; OK = 1; continue; }
              if ( ( kb >= '0' ) && ( kb <= '9' ) ) {dc->jmp = kb-'0'; continue; }
              if ( ( kb == '.' ) || ( kb == 'u' ) || ( kb == 'U' ) ) {
                 kbevent.x = dc->gcur_x ; kbevent.y = dc->gcur_y;   
                  OK = 1; continue;
              }
              if ( ui_Uparrow ( kb ) ) { cursor_up ( dc ) ;}
              if ( ui_Downarrow ( kb ) ) { cursor_down ( dc ) ;}
              if ( ui_Leftarrow ( kb ) ) { cursor_left ( dc ) ;}
              if ( ui_Rightarrow ( kb ) ) { cursor_right ( dc ) ; }
              kbevent.x = dc->gcur_x ; kbevent.y = dc->gcur_y;   
              if ( kbevent.x+xorg > Dwxu ) kbevent.x = Dwxu - xorg;
              if ( kbevent.y + yorg > Dwyu ) kbevent.y = Dwyu - yorg;
              if ( kbevent.x < Dwxl ) kbevent.x = Dwxl;
              if ( kbevent.y < Dwyl ) kbevent.y = Dwyl;
              dc->gcur_x = kbevent.x;
              dc->gcur_y = kbevent.y;
              draw_box_cursor( G , xorg , yorg , dc->gcur_x , dc->gcur_y ) ;  
