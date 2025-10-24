#include <stdio.h>
#include <kulina.h>
  static char *SearchStr ( char *str , char* ptn ) {
      char *ret = NULL;
      char *ptmp;
      ptmp = strstr ( str , ptn ) ;
      if ( ptmp != NULL ) {
          ret = ptmp;
          while ( ( ptmp = strstr ( ptmp+1 , ptn ) ) != NULL ) {
              ret = ptmp;
          }
      }
      return ret;
  }
  int GetFunName ( char *pt , char *Fun ) {
      int i = 0;
      strcpy ( Fun,pt ) ;
      while ( ( Fun [ i ] != ' ' ) && ( Fun [ i ] != '(' ) ) {
          if ( (Fun [ i ] < ' ') &&(Fun[i] !='\t') ) return 0;
          i++;
      }
      Fun [ i ] = '\0';
      return 1;
  }
  int CopyFunction ( Dlink *SrcLink , Dlink *TmpLink ) {
      int brackets = 1;
      char *line;
      while ( ( line = ( char * ) Dpick ( SrcLink ) ) != NULL ) {
          int i = 0;
          while ( line [ i ] >= ' ' ) {
              if ( line [ i ] == '{' ) brackets++;
              if ( line [ i ] == '}' ) brackets--;
              i++;
          }
          Dappend ( TmpLink , line ) ;
          if ( brackets == 0 ) break;
      }
      return 1;
  }
  int ProcCallbacks ( char *DiaName ) {
      char SrcFile [ 100 ] ;
      char CFile [ 100 ] ;
      char TmpFile [ 100 ] ;
      char *line , *pt , Fun [ 100 ] ;
      Dlink *SrcLink = NULL , *CLink = NULL , *TmpLink = NULL;
      sprintf ( SrcFile , "%-sCallbacks.src" , DiaName ) ;
      sprintf ( CFile , "%-sCallbacks.c" , DiaName ) ;
      sprintf ( TmpFile , "%-sCallbacks.c.org" , DiaName ) ;
      SrcLink = Dreadfile ( SrcFile ) ;
      if ( SrcLink == NULL ) {
          fprintf ( stderr , "SrcLink is empty; check .src file\n" ) ;
          return 0;
      }
      CLink = Dreadfile ( CFile ) ;
      if ( CLink == NULL ) {
          Resetlink ( CLink ) ;
          fprintf ( stderr , "CLink is NULL\n" ) ;
          Dwritefile ( SrcLink , CFile ) ;
          return 1;
      }
      Resetlink ( CLink ) ;
      Dwritefile ( CLink , TmpFile ) ;
      Resetlink ( CLink ) ;
      Resetlink ( SrcLink ) ;
      while ( 1 ) {
          while ( 1 ) {
              pt = NULL;
              line = ( char * ) Getrecord ( SrcLink ) ;
              if ( line == NULL ) break;
              pt = strstr ( line , DiaName ) ;
              if ( pt != NULL ) break;
          }
          if ( pt != NULL ) {
              if ( GetFunName ( pt , Fun ) == 0 ) continue;
              Resetlink ( CLink ) ;
              pt = NULL;
              while ( ( line = ( char * ) Getrecord ( CLink ) ) != NULL ) {
                  if ( ( pt = strstr ( line , Fun ) ) != NULL ) break;;
              }
              if ( pt == NULL ) {
                  if ( TmpLink == NULL ) TmpLink = Dopen ( ) ;
                  Dmove_back ( SrcLink , 1 ) ;
                  line = (char *)Dpick ( SrcLink ) ;
                  Dappend ( TmpLink , line ) ;
                  CopyFunction ( SrcLink , TmpLink ) ;
              }
          }
          else break;
      }
      if ( TmpLink == NULL ) {
          fprintf ( stderr , "No changes made\n" ) ;
          return 0;
      }
      sprintf ( Fun , "%-sinit" , DiaName ) ;
      Resetlink ( CLink ) ;
      while ( ( line = ( char * ) Getrecord ( CLink ) ) != NULL ) {
          if ( ( pt = strstr ( line , Fun ) ) != NULL ) break;
      }
      Dmove_back ( CLink , 2 ) ;
      Resetlink ( TmpLink ) ;
      while ( ( line = ( char * ) Getrecord ( TmpLink ) ) != NULL ) {
          Dadd ( CLink , line ) ;
      }
      Dwritefile ( CLink , CFile ) ;
      Dempty ( CLink ) ;
      Dempty ( SrcLink ) ;
      return 1;
  }
  int DeleteFunction ( Dlink *Link ) {
      int brackets = 1;
      char *line;
      while ( ( line = ( char * ) Dpick ( Link ) ) != NULL ) {
          int i = 0;
          while ( line [ i ] >= ' ' ) {
              if ( line [ i ] == '{' ) brackets++;
              if ( line [ i ] == '}' ) brackets--;
              i++;
          }
          if ( brackets == 0 ) break;
      }
      return 1;
  }
  int ProcDialog ( char *DiaName ) {
      char SrcFile [ 100 ] ;
      char CFile [ 100 ] ;
      char TmpFile [ 100 ] ;
      char *line , *pt , Fun [ 100 ] ;
      Dlink *SrcLink = NULL , *CLink = NULL , *TmpLink = NULL;
      sprintf ( SrcFile , "%-s.src" , DiaName ) ;
      sprintf ( CFile , "%-s.c" , DiaName ) ;
      sprintf ( TmpFile , "%-s.c.org" , DiaName ) ;
      sprintf(Fun,"%-sGroup",DiaName);
      SrcLink = Dreadfile ( SrcFile ) ;
      if ( SrcLink == NULL ) {
          fprintf ( stderr , "SrcLink is empty; check .src file\n" ) ;
          return 0;
      }
      CLink = Dreadfile ( CFile ) ;
      if ( CLink == NULL ) {
          Resetlink ( CLink ) ;
          fprintf ( stderr , "CLink is NULL\n" ) ;
          Dwritefile ( SrcLink , CFile ) ;
          return 1;
      }
      Resetlink ( CLink ) ;
      Dwritefile ( CLink , TmpFile ) ;
      Resetlink ( CLink ) ;
      Resetlink ( SrcLink ) ;
          while ( 1 ) {
              pt = NULL;
              line = ( char * ) Getrecord ( SrcLink ) ;
              if ( line == NULL ) break;
              pt = strstr ( line , Fun ) ;
              if ( pt != NULL ) break;
          }
          if ( pt != NULL ) {
              Resetlink ( CLink ) ;
              pt = NULL;
                  if ( TmpLink == NULL ) TmpLink = Dopen ( ) ;
                  Dmove_back ( SrcLink , 1 ) ;
                  line = (char *)Dpick ( SrcLink ) ;
                  Dappend ( TmpLink , line ) ;
                  CopyFunction ( SrcLink , TmpLink ) ;
          }
      Resetlink ( CLink ) ;
      while ( ( line = ( char * ) Getrecord ( CLink ) ) != NULL ) {
          if ( ( pt = strstr ( line , Fun ) ) != NULL ) break;
      }
      Dmove_back ( CLink , 1 ) ;
      Ddelete(CLink);
      DeleteFunction(CLink);
      Dmove_back ( CLink , 1 ) ;
      Resetlink ( TmpLink ) ;
      while ( ( line = ( char * ) Getrecord ( TmpLink ) ) != NULL ) {
          Dadd ( CLink , line ) ;
      }
      Dwritefile ( CLink , CFile ) ;
      Dempty ( CLink ) ;
      Dempty ( SrcLink ) ;
      return 1;
  }
#if 0
  int main ( int argc , char ** argv ) {
      ProcDialog ( argv [ 1 ] ) ;
      return 1;
  }
#endif     
#if 0
  int main ( int argc , char ** argv ) {
      ProcCallbacks ( argv [ 1 ] ) ;
      return 1;
  }
#endif     
