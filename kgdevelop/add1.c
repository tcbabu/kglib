  int  CheckWidgetName ( void *Tmp , char *id ) {
      DIALOG *D;
      DIA *d;
      DIX *x;
      int i = 0;
      D = ( DIALOG * ) Tmp;
      d = D->d;
      while ( d [ i ] .x != NULL ) {
          x = ( DIX * ) d [ i ] .x;
          i++;
          switch ( x->code ) {
              case 'x':
              case 'r':
              case 'c':
              case 'y':
              if ( strcmp ( x->Wid , id ) == 0 ) return 1;
              break;
              case 'v':
              if ( strcmp ( ( ( DIV * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'z':
              if ( strcmp ( ( ( DIZ * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'o':
              if ( strcmp ( ( ( DIO * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'p': /* new for xpm display */
              if ( strcmp ( ( ( DIP * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'i': /* info box */
              if ( strcmp ( ( ( DII * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 't':
              case 'T':
              if ( strcmp ( ( ( DIT * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'h':
              if ( strcmp ( ( ( DIL * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'H':
              if ( strcmp ( ( ( DILN * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'n':
              if ( strcmp ( ( ( DIN * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'b':
              case 'N':
              if ( strcmp ( ( ( DIB * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'f':
              if ( strcmp ( ( ( DIF * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'P':
              if ( strcmp ( ( ( DIHB * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'd':
              if ( strcmp ( ( ( DID * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'w':
              if ( strcmp ( ( ( DIW * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'e':
              if ( strcmp ( ( ( DIE * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 's':
              if ( strcmp ( ( ( DIS * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'g':
              if ( strcmp ( ( ( DIG * ) x )->Wid , id ) == 0 ) return 1;
              break;
              case 'm':
              case 'M':
              case 'B':
              if ( strcmp ( ( ( DIM * ) x )->Wid , id ) == 0 ) return 1;
              break;
              default:
              break;
          }
      }
      return 0;
  }
