#include <kulina.h>
#include "demoCallbacks.h"

static void *Args=NULL,*Rets=NULL;

static DIAINTR *It = NULL;


static MODINTERFACE ModFuns[] = { 
    (MODINTERFACE) NULL 
};
static Dlink *ModuleList=NULL;
  char myFolder [ 500 ] = "/usr/share/icons";
  static char *Picimg = NULL , *Curimg = NULL;
  static int angle = 0;
  static int Resize = 1;
  static float Transp = 0;
  static int Merge = 0;
  static int ApplyTransp = 0;
  static char buf [ 500 ] ;
#define ScrollWrite(txt) {\
  DIS *s;\
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;\
      kgWrite ( s , txt ) ;\
  }
#define InfoWrite(txt) {\
  DII *s;\
      int id;\
      s = ( DII * ) kgGetNamedWidget ( Tmp , "demoIbox" ) ;\
      kgWrite ( s , txt ) ; \
  }
#define MsgWrite(txt) {\
  DIM *s;\
      int id;\
      s = ( DIM * ) kgGetNamedWidget ( Tmp , "demoMessage" ) ;\
      kgWrite ( s , txt ) ;\
      kgUpdateOn ( Tmp ) ;\
  }
#define PutImage(img) {\
  int id;\
      DIP *s;\
      s = ( DIP * ) kgGetNamedWidget ( Tmp , "demoImagebox" ) ;\
      kgSetWidgetImage ( s , img ) ;\
      kgUpdateWidget ( s ) ;\
      kgUpdateOn ( Tmp ) ;\
  }
#define DrawBox(buf) {\
  void *img = NULL;\
      int id;\
      int wx , wy;\
      int vs , vp , hs , hp;\
      int ximg , yimg;\
      DIP *s;\
      DIT *T;\
      DIV *v;\
      DIZ *z;\
      s = ( DIP * ) kgGetNamedWidget ( Tmp , "demoImagebox" ) ;\
      T = ( DIT * ) kgGetNamedWidget ( Tmp , "demoTextbox" ) ;\
      v = ( DIV * ) kgGetNamedWidget ( Tmp , "demoVbar" ) ; \
      z = ( DIZ * ) kgGetNamedWidget ( Tmp , "demoHbar" ) ; \
      kgGetWidgetSize ( s , & wx , & wy ) ;\
      angle = 0.0;\
      Transp = ( kgGetInt ( T , 0 ) ) /100.0;\
      if ( Transp > 1.0 ) Transp = 1.0;\
      Picimg = kgGetImage ( buf ) ;\
      switch ( Resize ) {\
          case 0:\
          kgGetImageSize ( Picimg , & ximg , & yimg ) ;\
          vs = ( ( float ) wy/yimg ) *100;\
          hs = ( ( float ) wx/ximg ) *100;\
          if ( vs > 100 ) vs = 100;\
          vp = ( 100-vs ) /2;\
          if ( hs > 100 ) hs = 100;\
          hp = ( 100-hs ) /2;\
          kgSetScrollLength ( v , vs ) ;\
          kgSetScrollLength ( z , hs ) ;\
          kgSetScrollPos ( v , vp ) ;\
          kgSetScrollPos ( z , hp ) ;\
          kgUpdateWidget ( v ) ;\
          kgUpdateWidget ( z ) ;\
          break;\
          case 1:\
          kgSetScrollLength ( v , 100 ) ;\
          kgSetScrollLength ( z , 100 ) ;\
          kgSetScrollPos ( v , 0 ) ;\
          kgSetScrollPos ( z , 0 ) ;\
          kgUpdateWidget ( v ) ;\
          kgUpdateWidget ( z ) ;\
          Picimg = kgChangeSizeImage ( Picimg , wx , wy ) ;\
          break;\
          case 2:\
          Picimg = kgHalfSizeImage ( Picimg ) ;\
          kgGetImageSize ( Picimg , & ximg , & yimg ) ;\
          hs = ( ( float ) wx/ximg ) *100;\
          vs = ( ( float ) wy/yimg ) *100;\
          if ( vs > 100 ) vs = 100;\
          vp = ( 100-vs ) /2;\
          hs = ( ( float ) wy/yimg ) *100;\
          if ( hs > 100 ) hs = 100;\
          hp = ( 100-hs ) /2;\
          kgSetScrollLength ( v , vs ) ;\
          kgSetScrollLength ( z , hs ) ;\
          kgSetScrollPos ( v , vp ) ;\
          kgSetScrollPos ( z , hp ) ;\
          kgUpdateWidget ( v ) ;\
          kgUpdateWidget ( z ) ;\
          break;\
          default:\
          break;\
      }\
      if ( ApplyTransp && ( Transp > 0.001 ) ) {\
          kgAddTransparency ( Picimg , Transp ) ;\
      }\
      if ( Merge ) {\
          if ( Curimg != NULL ) {\
              if ( ApplyTransp ) kgMergeImages ( Curimg , Picimg , 0 , 0 ) ;\
              else kgMergeImages ( Curimg , Picimg , 0 , 0 ) ;\
          }\
          else Curimg = kgCopyImage ( Picimg ) ; \
      }\
      else {\
          if ( Curimg != NULL ) {\
              kgFreeImage ( Curimg ) ;\
          }\
          Curimg = kgCopyImage ( Picimg ) ; \
      }\
      kgSetWidgetImage ( s , Curimg ) ;\
      kgUpdateWidget ( s ) ;\
      kgUpdateOn ( Tmp ) ;\
  }
  static char buf [ 500 ] ;

 /* Callback for  demoSplbutton   */ 

int demodemoSplbuttoncallback( int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
      InfoWrite ( "You Pressed the special button" ) ;
      switch ( butno ) {
          case 1:
          ret = kgCheckMenu ( Tmp , 300 , 200 , "Really Quit" , 0 ) ;
          break;
      }
  return ret;
}
void  demodemoSplbuttoninit (DIL *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
  int demodemoButton0callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type0 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton0init ( DIN *B , void *pt ) {
  }
  int demodemoButton1callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type1 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton1init ( DIN *B , void *pt ) {
  }
  int demodemoButton2callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type2 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton2init ( DIN *B , void *pt ) {
  }
  int demodemoButton3callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type3 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton3init ( DIN *B , void *pt ) {
  }
  int demodemoButton4callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type4 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton4init ( DIN *B , void *pt ) {
  }
  int demodemoButton5callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type5 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton5init ( DIN *B , void *pt ) {
  }
  int demodemoButton6callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type6 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton6init ( DIN *B , void *pt ) {
  }
  int demodemoButton7callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      static char flname [ 300 ] = "##";
      static void *Img = NULL;
      float x1 , y1 , x2 , y2;
      int xsize , ysize;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIG *G;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      G = ( DIG * ) kgGetNamedWidget ( Tmp , "demoGbox" ) ;
      kgWrite ( s , "You pressed type7 Button\n" ) ;
      kgPickImage ( Tmp , 50 , 100 , flname+2 ) ;
      kgCrossCursor ( G , & x1 , & y1 ) ;
      kgDblCursor ( G , & x2 , & y2 , & x1 , & y1 ) ;
      Img = kgGetImage ( flname ) ;
      kgGetImageSize ( Img , & xsize , & ysize ) ;
      printf ( "Xsize: %d %d\n" , xsize , ysize ) ;
      kgDrawImage ( G , flname , x1 , y1 , x2 , y2 ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton7init ( DIN *B , void *pt ) {
  }
  int demodemoButton8callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type8 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton8init ( DIN *B , void *pt ) {
  }
  int demodemoButton9callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type9 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton9init ( DIN *B , void *pt ) {
  }
  int demodemoButton10callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      kgWrite ( s , "You pressed type10 Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoButton10init ( DIN *B , void *pt ) {
  }

int demodemoFoldercallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      char *pt , *ptmp;;
      int n , ret = 0;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B-> nx*B-> ny;
      DIS *s;
      DIX *X;DIY *Y;DICH *Ch;
      s = ( DIS * ) kgGetNamedWidget ( Tmp , "demoMsgscroll" ) ;
      X = ( DIX * ) kgGetNamedWidget ( Tmp , "demoXbox" ) ;
      Y = ( DIY * ) kgGetNamedWidget ( Tmp , "demoYbox" ) ;
      Ch = ( DICH * ) kgGetNamedWidget ( Tmp , "demoChbox" ) ;
      kgWrite ( s , "You pressed Folder Button\n" ) ;
      kgUpdateWidget ( s ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          if ( strlen ( myFolder ) == 1 ) break;
          pt = myFolder+1;
          while ( ( ptmp = strstr ( pt , "/" ) ) != NULL ) pt = ptmp+1;
          pt--;
          if ( pt != NULL ) pt [ 0 ] = '\0';
          if ( strlen ( myFolder ) <= 1 ) strcpy ( myFolder , "/" ) ;
          ScrollWrite ( myFolder ) ;
          kgFreeThumbNails ( ( ThumbNail ** ) ( kgGetList ( X ) ) ) ;
          kgFreeThumbNails ( ( ThumbNail ** ) ( kgGetList ( Y ) ) ) ;
          kgSetList ( X , ( void ** ) kgFolderThumbNails ( myFolder ) ) ;
          kgSetList ( Y , ( void ** ) kgMakeThumbNails ( myFolder , 64 ) ) ;
          kgUpdateWidget ( X ) ;
          kgUpdateWidget ( Y ) ;
          kgUpdateOn ( Tmp ) ;
          break;
      }
      return ret;
  }
void  demodemoFolderinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
 /* Callback for  demoPulldown   */ 

int demodemoPulldowncallback(int item ,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIW *B;
      int ret = 1;
      D = ( DIALOG * ) Tmp;
      B = ( DIW * ) kgGetWidget ( Tmp , i ) ;
      InfoWrite ( "You selected DIW(pulldown menu)  item" ) ;
      switch ( item ) {
          case 1:
          Resize = 1;
          break;
          case 2:
          Resize = 0;
          break;
          default:
          Resize = 2;
          break;
      }
      return ret;
}

 /* Callback for  demoTextbox   */ 

int demodemoTextboxcallback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
      DIALOG *D;DIT *T;T_ELMT *e;
      int ret = 1;
      D = ( DIALOG * ) Tmp;
      T = ( DIT * ) kgGetWidget ( Tmp , i ) ;
      e = T-> elmt;
      InfoWrite ( "you typed text box" ) ;
      Transp = ( kgGetInt ( T , 0 ) ) /100.0;
      if ( Transp > 1.0 ) Transp = 1.0;
      return ret;
}

 /* Callback for  dempTable   */ 

int demodemoTablecallback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
           However cellno got 2 special values
             1. SCROLL_DOWN a scrolldown action
             2. SCROLL_UP a scrolldown action
             3. LINE_CHANGE for line change  action
             4. TAB_PRESS for tab action
             5. BUTTON2_PRESS for button2 action
             6. BUTTON3_PRESS for button3 action
             which may be ignored or peocessed
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
      DIALOG *D;DIT *T;T_ELMT *e;
      int ret = 1;
      float val0 , val1 , val2 , val3 , val4 , val5;
      D = ( DIALOG * ) Tmp;
      T = ( DIT * ) kgGetWidget ( Tmp , i ) ;
      e = T-> elmt;
      val0 = kgGetDouble ( T , 0 ) ;
      val1 = kgGetDouble ( T , 1 ) ;
      val2 = val0*val1;
      val3 = kgGetDouble ( T , 3 ) ;
      val4 = kgGetDouble ( T , 4 ) ;
      val5 = val3*val4;
      kgSetDouble ( T , 2 , val2 ) ;
      kgSetDouble ( T , 5 , val5 ) ;
      kgUpdateWidget ( T ) ;
      kgUpdateOn ( Tmp ) ;
      InfoWrite ( "you typed a table box" ) ;
      return ret;
}

 /* Callback for  demoDslide   */ 

int demodemoDslidecallback(int  val,int i,void *Tmp) {
  /*********************************** 
    val : current value 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DID *SD;DIF *SF; DIT *TB;
      int ret = 1;
      float fval;
      D = ( DIALOG * ) Tmp;
      SD = ( DID * ) kgGetWidget ( Tmp , i ) ;
      SF = ( DIF * ) kgGetNamedWidget ( Tmp , "demoFslide" ) ;
      TB = ( DIT * ) kgGetNamedWidget ( Tmp , "demoTable" ) ;
      fval = kgGetDouble ( TB , 1 ) ;
      kgSetDouble ( TB , 0 , ( float ) val ) ;
//  kgSetFloat(TB,1,(float)fval);
      kgSetDouble ( TB , 2 , ( float ) fval*val ) ;
      kgUpdateWidget ( TB ) ;
      kgUpdateOn ( Tmp ) ;
      InfoWrite ( "you moved int slide" ) ;
      return ret;
}

 /* Callback for  demoFslide   */ 

int demodemoFslidecallback(double val,int i,void *Tmp) {
  /*********************************** 
    val : current value 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIF *F; DIT *TB;
      int ret = 1;
      float fval;
      D = ( DIALOG * ) Tmp;
      F = ( DIF * ) kgGetWidget ( Tmp , i ) ;
      TB = ( DIT * ) kgGetNamedWidget ( Tmp , "demoTable" ) ;
      fval = kgGetDouble ( TB , 0 ) ;
      kgSetDouble ( TB , 1 , ( float ) val ) ;
      kgSetDouble ( TB , 2 , ( float ) fval*val ) ;
      kgUpdateWidget ( TB ) ;
      kgUpdateOn ( Tmp ) ;
      InfoWrite ( "you moved float slide" ) ;
      return ret;
}

 /* InitFunction for  demoGbox   */ 

void demodemoGboxinit (int i,void *Tmp) {
  /*********************************** 
    int routine for grahics area 
   ***********************************/ 
  DIALOG *D;
  DIG *G;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  G = D->d[i].g;
  G->D = (void *)(Tmp);
      kgUserFrame ( G , 0.0 , 0.0 , 100.0 , 100.0 ) ;
  return ;
}

 /* Callback for  demoEbox   */ 

int demodemoEboxcallback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIE *E;void *pt;
      int ret = 1;
      void *img;
      static float Hue = 1.0;
      D = ( DIALOG * ) Tmp;
      pt = D-> pt;
      E = ( DIE * ) kgGetWidget ( Tmp , i ) ;
      InfoWrite ( "Pressed DIE" ) ;
#if 0
      ScrollWrite ( " " ) ;
      ScrollWrite ( "You made a selection in DIE " ) ;
      ScrollWrite ( "(menu of character Strings)" ) ;
      ScrollWrite ( "You can customise DIE " ) ;
#endif
      if ( Picimg == NULL ) return ret;
      switch ( item ) {
          case 1:
          angle += 30;
          angle = angle%360;
          img = kgRotateImage ( Picimg , ( float ) angle ) ;
          if ( Curimg != NULL ) kgFreeImage ( Curimg ) ;
          Curimg = img;
          PutImage ( Curimg ) ;
          break;
          case 2:
          img = kgEmbossImage ( Curimg ) ;
          if ( Curimg != NULL ) kgFreeImage ( Curimg ) ;
          Curimg = img;
          PutImage ( Curimg ) ;
          break;
          case 3:
          kgImagetoGray ( Curimg ) ;
          PutImage ( Curimg ) ;
          break;
          case 4:
          Curimg = kgImageModifyColor ( Curimg , .5 , .2 , .5 ) ;
          PutImage ( Curimg ) ;
          break;
          case 5:
          kgModifyImageHSV ( Curimg , 1.0 , 1.0 , 1.1 ) ;
          PutImage ( Curimg ) ;
          break;
          case 6:
          kgModifyImageHSV ( Curimg , 1.0 , 1.0 , 0.909 ) ;
          PutImage ( Curimg ) ;
          break;
          case 7:
          kgModifyImageHSV ( Curimg , 1.0 , 1.1 , 1.0 ) ;
          PutImage ( Curimg ) ;
          break;
          case 8:
          kgModifyImageHSV ( Curimg , 1.0 , 0.909 , 1.0 ) ;
          PutImage ( Curimg ) ;
          break;
          case 9:
          Hue = 1.028;
          kgModifyImageHSV ( Curimg , Hue , 1.0 , 1.0 ) ;
          PutImage ( Curimg ) ;
          break;
          case 10:
          kgImageModifyColor ( Curimg , 1.1 , 1.0 , 1.0 ) ;
          PutImage ( Curimg ) ;
          break;
          case 11:
          kgImageModifyColor ( Curimg , 0.909 , 1.0 , 1.0 ) ;
          PutImage ( Curimg ) ;
          break;
          case 12:
          kgImageModifyColor ( Curimg , 1.0 , 1.1 , 1.0 ) ;
          PutImage ( Curimg ) ;
          break;
          case 13:
          kgImageModifyColor ( Curimg , 1.0 , 0.909 , 1.0 ) ;
          PutImage ( Curimg ) ;
          break;
          case 14:
          kgImageModifyColor ( Curimg , 1.0 , 1.0 , 1.1 ) ;
          PutImage ( Curimg ) ;
          break;
          case 15:
          kgImageModifyColor ( Curimg , 1.0 , 1.0 , 0.909 ) ;
          PutImage ( Curimg ) ;
          break;
          case 16:
          kgFlipImage ( Curimg ) ;
          PutImage ( Curimg ) ;
          break;
          case 17:
          kgFlopImage ( Curimg ) ;
          PutImage ( Curimg ) ;
          break;
          case 18:
          if ( Curimg != NULL ) kgFreeImage ( Curimg ) ;
          Curimg = NULL;
          angle = 0;
          Curimg = kgCopyImage ( Picimg ) ;
          PutImage ( Curimg ) ;
          break;
          default:
          break;
      }
      return ret;
}
void * demodemoEboxinit (DIE *E,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
#if 0
  char **menu22 ;
  menu22= (char **)malloc(sizeof(char *)*19);
  menu22[18]=NULL;
  menu22[0]=(char *)malloc(7);
  strcpy(menu22[0],(char *)"Rotate");
  menu22[1]=(char *)malloc(7);
  strcpy(menu22[1],(char *)"Emboss");
  menu22[2]=(char *)malloc(13);
  strcpy(menu22[2],(char *)"ToGrayScale");
  menu22[3]=(char *)malloc(7);
  strcpy(menu22[3],(char *)"ToColor");
  menu22[4]=(char *)malloc(14);
  strcpy(menu22[4],(char *)"Brightness +");
  menu22[5]=(char *)malloc(14);
  strcpy(menu22[5],(char *)"Brightness -");
  menu22[6]=(char *)malloc(14);
  strcpy(menu22[6],(char *)"Saturation +");
  menu22[7]=(char *)malloc(14);
  strcpy(menu22[7],(char *)"Saturation -");
  menu22[8]=(char *)malloc(9);
  strcpy(menu22[8],(char *)"Hue +");
  menu22[9]=(char *)malloc(9);
  strcpy(menu22[9],(char *)"Red +");
  menu22[10]=(char *)malloc(9);
  strcpy(menu22[10],(char *)"Red -");
  menu22[11]=(char *)malloc(9);
  strcpy(menu22[11],(char *)"Green +");
  menu22[12]=(char *)malloc(9);
  strcpy(menu22[12],(char *)"Green -");
  menu22[13]=(char *)malloc(9);
  strcpy(menu22[13],(char *)"Blue +");
  menu22[14]=(char *)malloc(9);
  strcpy(menu22[14],(char *)"Blue -");
  menu22[15]=(char *)malloc(5);
  strcpy(menu22[15],(char *)"Flip");
  menu22[16]=(char *)malloc(5);
  strcpy(menu22[16],(char *)"Flop");
  menu22[17]=(char *)malloc(9);
  strcpy(menu22[17],(char *)"Original");
  E->menu = menu22;
#endif
  char *menu22[]={
  (char *)"Rotate",
  (char *)"Emboss",
  (char *)"ToGrayScale",
  (char *)"ToColor",
  (char *)"Brightness +",
  (char *)"Brightness -",
  (char *)"Saturation +",
  (char *)"Saturation -",
  (char *)"Hue +",
  (char *)"Red +",
  (char *)"Red -",
  (char *)"Green +",
  (char *)"Green -",
  (char *)"Blue +",
  (char *)"Blue -",
  (char *)"Flip",
  (char *)"Flop",
  (char *)"Original",
    NULL
  };
  kgFreeDouble(kgGetList(E));
  kgSetList(E,(void **)kgAllocStrings(menu22));
}

 /* Callback for  dempMsgscroll   */ 

void * demodempMsgscrollinit (DIS *S,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
}

 /* Callback for  demoWidget27dempSlide   */ 

int demodemoHBslidecallback(int  val,int i,void *Tmp) {
  /*********************************** 
    val : current value 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIHB *SD;
      int ret = 1;
      DIO *O;
      DIT *T;
      D = ( DIALOG * ) Tmp;
      SD = ( DIHB * ) kgGetWidget ( Tmp , i ) ;
      O = ( DIO * ) kgGetNamedWidget ( Tmp , "demoProgrss" ) ;
      T = ( DIT * ) kgGetNamedWidget ( Tmp , "demoTextbox" ) ;
      kgSetProgressBar ( O , val ) ;
      kgSetInt ( T , 0 , val ) ;
      kgUpdateWidget ( T ) ;
      kgUpdateOn ( Tmp ) ;
      InfoWrite ( "You a moved DIHB (a tyoe of slide}" ) ;
      ScrollWrite ( " " ) ;
      ScrollWrite ( "DIHB slide" ) ;
      ScrollWrite ( "You have to set its range" ) ;
      ScrollWrite ( "in a way it is way to input a value" ) ;
      ScrollWrite ( "The look of DIHB can be changed" ) ;
      return ret;
  }

 /* Callback for  demoXbox   */ 

int demodemoXboxcallback(int item,int i,void *Tmp) {
      DIALOG *D;DIX *X;void *pt; DIY *Y;DICH *Ch;
      char buff [ 300 ] ;
      int ret = 1;
      ThumbNail **list;
      ThumbNail *th;
      D = ( DIALOG * ) Tmp;
      pt = D-> pt;
      X = ( DIX * ) kgGetWidget ( Tmp , i ) ;
      InfoWrite ( "You picked item in DIX (check box)" ) ;
      ScrollWrite ( " " ) ;
      ScrollWrite ( " DIX (check box)" ) ;
      ScrollWrite ( "Check Box used ThumNails as its items" ) ;
      ScrollWrite ( "ThumbNails got an image and a name also a switch" ) ;
      ScrollWrite ( "But image/name can be set as NULL" ) ;
      ScrollWrite ( "there are few helper routines to make ThimbNails" ) ;
      ScrollWrite ( "Now it lists Folders in the current folder" ) ;
      list = ( ThumbNail ** ) kgGetList ( X ) ;
      if ( list == NULL ) return ret;
      th = list [ item-1 ] ;
      strcpy ( buff , myFolder ) ;
      strcat ( buff , "/" ) ;
      strcat ( buff , th-> name ) ;
      strcpy ( myFolder , buff ) ;
      Y = ( DIY * ) kgGetNamedWidget ( Tmp , "demoYbox" ) ;
      Ch = ( DICH * ) kgGetNamedWidget ( Tmp , "demoChbox" ) ;
      kgFreeThumbNails ( ( ThumbNail ** ) ( kgGetList ( X ) ) ) ;
      kgSetList ( X , ( void ** ) kgFolderThumbNails ( myFolder ) ) ;
      kgFreeThumbNails ( ( ThumbNail ** ) ( kgGetList ( Y ) ) ) ;
      kgSetList ( Y , ( void ** ) kgMakeThumbNails ( myFolder , 64 ) ) ;
      kgUpdateWidget ( X ) ;
      kgUpdateWidget ( Y ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( item ) {
          case 1:
          break;
      }
      return ret;
  }
  void demodemoXboxinit ( DIX *X , void *pt ) {
 // One may setup browser list here by setting X->list
 // if it need to be freed set it as X->pt also
//     strcpy(myFolder,"/usr/share/icons/CratOS_lion-icons/apps/scalable");
//     strcpy(myFolder,"/usr/share");
//     X->list = (void **) kgFolderThumbNails(myFolder);
      kgSetList ( X , ( void ** ) kgFolderThumbNails ( myFolder ) ) ;
  }

 /* Callback for  demoRadio   */ 

int demodemoRadiocallback(int item,int i,void *Tmp) {
      DIRA *R;DIALOG *D;void *pt;
      ThumbNail **th;
      char hcopyfile [ 200 ] ;
      int ret = 1;
      static float x1 , y1 , x2 , y2;
      static int entry = 1;
      D = ( DIALOG * ) Tmp;
      DIG *g;
      pt = D-> pt;
      R = ( DIRA * ) kgGetWidget ( Tmp , i ) ;
      th = ( ThumbNail ** ) kgGetList ( R ) ;;
      g = ( DIG * ) kgGetNamedWidget ( Tmp , "demoGbox" ) ;
      if ( entry ) kgGetWindow ( g , & x1 , & y1 , & x2 , & y2 ) ;
      entry = 0;
      InfoWrite ( "This is DIRA (radio button)" ) ;
      ScrollWrite ( " " ) ;
      ScrollWrite ( "Radio buttons (DIRA) to select one" ) ;
      ScrollWrite ( "It also uses ThimbNails , but ignores images" ) ;
      ScrollWrite ( "Now you have selected an item" ) ;
      switch ( item ) {
          case 1:
          kgPointerZoom ( g ) ;
          break;
          case 2:
          kgUserFrame ( g , x1 , y1 , x2 , y2 ) ;
          kgReview ( g ) ;
          break;
          case 3:
          kgAntialiasedReview ( g ) ;
          break;
          case 4:
          kgFileBrowser ( Tmp , 50 , 200 , hcopyfile , "*.png" ) ;
//	  kgHardCopy(g,hcopyfile);
          kgSaveAsPng ( g , hcopyfile ) ;
          break;
          default:
          break;
      }
      return ret;
}
void  demodemoRadioinit (DIRA *R,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
}

 /* Callback for  dempChbox   */ 

int demodempChboxcallback(int item,int i,void *Tmp) {
      DICH *C;DIALOG *D;void *pt;
      ThumbNail **th;
      int ret = 1;
      D = ( DIALOG * ) Tmp;
      pt = D-> pt;
      C = ( DICH * ) kgGetWidget ( Tmp , i ) ;
      th = ( ThumbNail ** ) kgGetList ( C ) ;
      InfoWrite ( " Check menui(DICH) using ThumbNails" ) ;
      ScrollWrite ( " " ) ;
      ScrollWrite ( " Check Menu (DICH) " ) ;
      ScrollWrite ( "This Check menu is using ThumbNails" ) ;
      ScrollWrite ( " it can be set for single or multiple items" ) ;
      ScrollWrite ( " Now it is set for Files" ) ;
      Merge = kgGetSwitch ( C , 0 ) ;
      ApplyTransp = kgGetSwitch ( C , 1 ) ;
      return ret;
}
void  demodempChboxinit (DICH *C,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
}

 /* Callback for  demoYbox   */ 

int demodemoYboxcallback(int item,int i,void *Tmp) {
      DIALOG *D;DIY *Y;void *pt;
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      int ret = 1 , x , y;
      D = ( DIALOG * ) Tmp;
      ThumbNail **TH , *th;
      pt = D-> pt;
      Y = ( DIY * ) kgGetWidget ( Tmp , i ) ;
      DIT *wid;
      InfoWrite ( "ThumbNail browser (DIY)" ) ;
      ScrollWrite ( "  " ) ;
      ScrollWrite ( "ThumbNail browser (DIY" ) ;
      ScrollWrite ( "DIY is another brower for ThumbNails" ) ;
      ScrollWrite ( "can select multiple items" ) ;
      ScrollWrite ( "One can program it to drag items" ) ;
#if 0
      TH = ( ThumbNail ** ) kgGetList ( Y ) ;
      th = kgCopyThumbNail ( TH [ item-1 ] ) ;
      kgDeleteThumbNail ( Y , item-1 ) ;
      kgInsertThumbNail ( Y , th , 0 ) ;
      kgUpdateWidget ( Y ) ;
      kgUpdateOn ( Tmp ) ;
#endif
#if 1
      if ( kgDragThumbNail ( Y , item-1 , & x , & y ) ) {
          wid = ( DIT * ) kgGetLocationWidget ( Tmp , x , y ) ;
          if ( wid != NULL ) {
//	     if(wid->code=='p') {
              if ( kgCheckWidgetName ( wid , "demoImagebox" ) ) {
                  ThumbNail *thtmp;
                  thtmp = ( ( ThumbNail ** ) kgGetList ( Y ) ) [ item-1 ] ;
                  sprintf ( buf , "%-s/%s" , myFolder , thtmp-> name ) ;
                  DrawBox ( buf ) ;
              }
              else {
                  if ( kgCheckWidgetName ( wid , "demoYbox" ) ) {
                      int pos = -1;
                      pos = kgGetThumbNailItem ( Y , x , y ) ;
                      if ( pos != item-1 ) {
                          kgMoveThumbNail ( Y , item-1 , pos ) ;
                          kgUpdateWidget ( Y ) ;
                          kgUpdateOn ( Tmp ) ;
                      }
                  }
              }
          }
      }
#endif
      switch ( item ) {
          case 1:
          break;
      }
      return ret;
  }
void  demodemoYboxinit (DIY *Y,void *ptmp) {
 // One may setup browser list here by setting Y->list
 // if it need to be freed set it as Y->pt also
//     Y->list = (void **) kgFileThumbNails(myFolder,"*");
      kgFreeThumbNails ( ( ThumbNail ** ) kgGetList ( Y ) ) ;
      kgSetList ( Y , ( void ** ) kgMakeThumbNails ( myFolder , 64 ) ) ;
#if 0
      kgInsertThumbNail ( Y , kgPickThumbNail ( Y , 1 ) , 0 ) ;
      kgSortList ( Y ) ;
      kgDeleteThumbNail ( Y , 2 ) ;
#endif
  }

 /* Callback for  demoVbar   */ 

int demodemoVbarcallback(double val,int i,void *Tmp) {
  /*********************************** 
    val : current value 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIV *V; 
  int ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  V = (DIV *) kgGetWidget(Tmp,i);
  return ret;
}

 /* Callback for  demoHbar   */ 

int demodemoHbarcallback(double val,int i,void *Tmp) {
  /*********************************** 
    val : current value 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIZ *Z; 
  int ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  Z = (DIZ *) kgGetWidget(Tmp,i);
  return ret;
}

 /* Callback for  demoButton5   */ 

 
void * demodemoMsgscrollinit (DIS *S,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
}
 /* Callback for  demoWidget27demoHBlide   */ 



int demoCallBack(void *Tmp,void *tmp) {
  /***********************************
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
      int ret = 0;
      DIALOG *D;
      KBEVENT *kbe;
      D = ( DIALOG * ) Tmp;
      DIT *T;
      kbe = ( KBEVENT * ) tmp;
      T = ( DIT * ) kgGetClickedWidget ( Tmp ) ;
      if ( kbe-> event == 1 ) {
          if ( kbe-> button == 1 ) {
              if ( T != NULL ) {
                  InfoWrite(" ");
                  sprintf ( buf , "!c38code= %c\n" , T-> code ) ;
                  InfoWrite ( buf ) ;
                  switch ( T-> code ) {
                      case 's':
                      InfoWrite ( "You have Pressed Message Scroll(DIS)" ) ;
                      break;
                      case 'p':
                      strcpy ( buf , "" ) ;
                      InfoWrite ( "You have Pressed Message Scroll(DIS)" ) ;
                      ScrollWrite ( "!c01PICK AN IMAGE FILE" ) ;
//			  kgFolderBrowser(Tmp,20,20,buf, "*");
                      kgPickImage ( Tmp , 100 , 100 , buf ) ;
                      if ( buf [ 0 ] != '\0' ) DrawBox ( buf ) ;
                      break;
                      case 'g':
                      InfoWrite ( "You clicked drawing area(DIG)" ) ;
                      ScrollWrite("!c03Drawing tool in action; finish that");
                      kgDrawingTool ( kgGetNamedWidget ( Tmp , "demoGbox" ) ) ;
                      break;
                      default:
                      InfoWrite ( "You have clicked a Widget" ) ;
                      InfoWrite ( "May be an output Widget" ) ;
                      break;
                  }
              }
              else {
                  ScrollWrite ( "  " ) ;
                  InfoWrite ( "You have clicked outside widgets" ) ;
                  ScrollWrite ( "This is the  default callback " ) ;
                  ScrollWrite ( "used if no other call back is  proper or NULL" ) ;
                  ScrollWrite ( "You can use it to  program click on arbitary position" ) ;
              }
          }
      }
      return ret;
}

void * demoCleanDia(void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  
/* you add any cleaning  here */

  return NULL;
}
void *  demoAction(void *Tmp,void *Args) {
  return NULL;
} 
int   demoOn(void *itmp) {
  DIAINTR * Dt = (DIAINTR *) itmp;
  if(Dt == NULL ) Dt = (DIAINTR *)It;
  if(Dt != NULL) {
    if(Dt->Dtmp != NULL)kgSetGrpVisibility(Dt->Dtmp,Dt->GrpId,1);
    else return 0;
    return 1;
  } 
  return 0;
} 
int   demoOff(void *itmp) {
  DIAINTR * Dt = (DIAINTR *) itmp;
  if(Dt == NULL ) Dt = (DIAINTR *)It;
  if(Dt != NULL) {
    if(Dt->Dtmp != NULL)kgSetGrpVisibility(Dt->Dtmp,Dt->GrpId,0);
    else return 0;
    return 1;
  } 
  return 0;
} 

static char *GetPointer(char *str) { 
  char *pt; 
  pt = (char *)malloc(strlen(str)+1); 
  strcpy(pt,str); 
  return pt; 
} 
void * demoInterface(void *args,void *rets) {
  /*********************************** 
   ***********************************/ 
  DIAINTR *it= (DIAINTR *)malloc(sizeof(DIAINTR));
  it->GrpId=0;
  // filled by MakeGroup  it->xsh=0;
  it->ysh=0;
  it->RunDia = Rundemo;
  it->MakeGroup = MakedemoGroup;
  it->Title = GetPointer((char *)"demo");
  it->Help = GetPointer( (char *)"No help yet, request");
  it->Action = demoAction;
  it->Settings = demoSetup;
  it->Cleanup  = demoCleanDia;
  if(args != NULL) Args=args;
  if(rets != NULL) Rets=rets;
  it->args = Args;
  it->rets = Rets;
  it->SwitchOn = demoOn;
  it->SwitchOff = demoOff;
  it->Dtmp = NULL; // fiiled by MakeGroup 
  It = it;
  return it;
}
int demoinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs, given by caller */
  return ret;
}

int demoSetup(void *Tmp,void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  /* you add any initialisation here */
  /* useful for setting is used as MakeGroup */
  return 1;
}
int democleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[1] is outputs, if any  to be given to caller */
 /* pt[0] is inputs, given by caller */
  return ret;
}
int Modifydemo(void *Tmp,int GrpId) {
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs given by caller */
  DIA *d;
  int i,n;
  kgCheckParentPosition(Tmp);
  d = D->d;

  if( ModuleList == NULL) ModuleList = kgGetModuleList((void **)ModFuns);
  i=0;
  void *args=NULL;
  DIAINTR *Dt;
  Resetlink(ModuleList);
  while ( (Dt=(DIAINTR *)Getrecord(ModuleList)) != NULL) {
    Dt->GrpId = Dt->MakeGroup(Tmp,NULL);
    kgShiftGrp(Tmp,Dt->GrpId,Dt->xsh,Dt->ysh);
    Dt->Settings(Tmp,args);
    i++;
  };

  i=0;while(d[i].t!= NULL) {;
     i++;
  };
  n=1;
//  strcpy(D->name,"Kulina Designer ver 3.0");    /*  Dialog name you may change */
#if 0
  if(D->fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D->xo=D->yo=0; D->xl = xres-10; D->yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D->xo=D->yo=0; D->xl = xres; D->yl=yres;
//     D->StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
#endif
  return GrpId;
}
int demoResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  kgGetWindowSize(D,&xres,&yres);
  dx = xres - D->xl;
  dy = yres - D->yl;
  /* extra code */
  D->xl= xres;
  D->yl= yres;
  kgRedrawDialog(D);
  return ret;
}
int demoWaitCallBack(void *Tmp) {
      int ret = 0;
      static int entry = 0;
      static DIM *sp = NULL;
      static DIM *msg = NULL;
      static DIM *msgb = NULL;
      static int Minute = -1;
      char buff [ 100 ] ;
      static char *days [ 7 ] = {"Sun" , "Mon" , "Tue" , "Wed" , "Thu" , "Fri" , "Sat"};
          
      static char *months [ 12 ] = {"Jan" , "Feb" , "Mar" , "Apr" , "May" , "Jun" , "Jul" , "Aug" , "Sep" , "Oct" , "Nov" , "Dec"};
          
      time_t tp , t;
      struct tm *dt;
      int odate = -1 , ndate;
      usleep ( 10000 ) ;
      t = time ( & tp ) ;
      dt = localtime ( & t ) ;
      entry = ( ++entry ) %100;
      if ( ( entry != 0 ) && ( entry != 50 ) ) return ret;
#if 0
      if ( dt-> tm_min != Minute ) {
      }
#endif
      if ( entry ) {
          if ( sp == NULL ) {
              sp = kgGetNamedWidget ( Tmp , "demoSplash" ) ;
              msg = kgGetNamedWidget ( Tmp , "demoMessage" ) ;
              msgb = kgGetNamedWidget ( Tmp , "demoBmessage" ) ;
          }
          ndate = dt-> tm_year*10000+dt-> tm_mon*100+dt-> tm_mday;
          if ( ndate != odate ) {
              odate = ndate;
              sprintf ( buff , "%d %-s" , dt-> tm_year+1900 , months [ dt-> tm_mon ] ) ;
              kgWrite ( msg , buff ) ;
              sprintf ( buff , "%d %-s" , dt-> tm_mday , days [ dt-> tm_wday ] ) ;
              kgWrite ( msgb , buff ) ;
          }
          Minute = dt-> tm_min;
          sprintf ( buff , "%2.2d" , dt-> tm_hour ) ;
          strcat ( buff , "!%:!%" ) ;
          sprintf ( buff+strlen ( buff ) , "%2.2d" , dt-> tm_min ) ;
          kgWrite ( sp , buff ) ;
      }
      else {
          if ( sp == NULL ) sp = kgGetNamedWidget ( Tmp , "demoSplash" ) ;
          Minute = dt-> tm_min;
          sprintf ( buff , "%2.2d" , dt-> tm_hour ) ;
          strcat ( buff , "!% !%" ) ;
          sprintf ( buff+strlen ( buff ) , "%2.2d" , dt-> tm_min ) ;
          kgWrite ( sp , buff ) ;
      }
      return ret;
}
