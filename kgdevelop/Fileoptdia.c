#include <kulina.h>
extern DIALOG *Parent;
int  Fileoptdiabutnbox1callback(int key,int i,void *Tmp) {
  DIA *D;DIBN *B; 
  int n,ret =1; 
  D = ((DIALOG *)Tmp)->d;
  B = D[i].n;
  n = B->nx*B->ny;
  switch(key) {
    case 1: 
      break;
    case 2: 
      break;
    case 3: 
      break;
  }
  return ret;
}
int Fileoptdia(  void *v0 ){
  int ret=1;
  DIALOG D;
  DIA d[2];
  char *titles0[]  = { 
    (char *)"Save", 
    (char *)"Save&quit", 
    (char *)"Quit", 
    NULL
  };
  char *butncode0  = NULL;
  DIBN n0 = { 
    'N',
    5,10,  
    126,115,
    9,9,  
    107, 
    25, 
    1,3, 
    (int *)v0, 
    (char *)"",
    titles0,
    butncode0,
    NULL,Fileoptdiabutnbox1callback, /* args, Callbak */
    NULL,NULL
    ,3,0.2
  };
  d[0].n = &n0;
  d[1].t = NULL;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = -1;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 10;   /* Position of Dialog */ 
  D.yo = 40;
  D.xl = 132;    /*  Length of Dialog */
  D.yl = 124;    /*  Width  of Dialog */
  D.Initfun = NULL;    /*  Width  of Dialog */
  D.Deco=1;
  D.DrawBkgr=1;
  D.Bkpixmap=NULL;
  D.Callback=NULL;
  D.transparency = 0;
  D.Newwin=0;
  D.Sticky=0;
  D.Fixpos=1;
  D.NoTaskBar=0;
  D.StackPos=0;
  D.Shapexpm=NULL;
//  ret= Dialog(&D);
  kgDefaultGuiTheme(&(D.gc));
//  D.gc.GuiFontSize=9;
  D.SearchList=NULL;
  ret= kgUi(&D);
  return ret;
}
int RunFileoptdia(void *parent) {
/*************************************************

    Buttonbox1 (new) 1 data value

*************************************************/
   int   v0 = 1;
   char *fmenu[]={(char *)"Save",(char *)"Save&Quit",(char *)"Quit",NULL};
//   Fileoptdia( &v0 );
//   v0 = kgMenu(Parent,0,45,1,0,fmenu,3);
   v0 = kgMenu1(Parent,20,45,0,fmenu,3,NULL,NULL);
   return v0;
}
