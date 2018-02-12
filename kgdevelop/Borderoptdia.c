#include <kulina.h>
extern DIALOG *Dia;
extern DIALOG *Parent;
void ChangeDialogSize(DIALOG *D);
void ChangeDialogTopWidth(DIALOG *D);
void ChangeDialogBottomWidth(DIALOG *D);
void ChangeDialogLeftWidth(DIALOG *D);
void ChangeDialogRightWidth(DIALOG *D);
void DRAW_DIALOG(DIALOG *D);

int  Borderoptdiabutnbox1callback(int key,int i,void *Tmp) {
  DIA *D;DIBN *B; 
  int n,ret =0; 
  D = ((DIALOG *)Tmp)->d;
  B = D[i].n;
  n = B->nx*B->ny;
  switch(key) {
     case 1:
      ChangeDialogTopWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     case 2:
      ChangeDialogBottomWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     case 3:
      ChangeDialogLeftWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     case 4:
      ChangeDialogRightWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     default:
      ret = 1;
      break;
  }
  return ret;
}
int Borderoptdia(  void *v0 ){
  int ret=1;
  DIALOG D;
  DIA d[2];
  char *titles0[]  = { 
    (char *)"Topwidth", 
    (char *)"Bottomwidth", 
    (char *)"Left width", 
    (char *)"Right width", 
    (char *)"Go back", 
    NULL
  };
  char *butncode0  = NULL;
  DIBN n0 = { 
    'N',
    6,9,  
    761,30,
    9,9,  
    134, 
    25, 
    5,1, 
    (int *)v0, 
    (char *)"",
    titles0,
    butncode0,
    NULL,Borderoptdiabutnbox1callback, /* args, Callbak */
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
  D.xo = 0;   /* Position of Dialog */ 
  D.yo = 0;
  D.xl = 763;    /*  Length of Dialog */
  D.yl = 43;    /*  Width  of Dialog */
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
  kgDefaultGuiTheme(&(D.gc));
//  D.gc.GuiFontSize=9;
  D.SearchList=NULL;
  ret= kgUi(&D);
  return ret;
}
int RunBorderoptdia(void *parent) {
/*************************************************

    Buttonbox1 (new) 1 data value

*************************************************/
   int   v0 = 1;
//   Borderoptdia( &v0 );
   char *bdrmenu[]={(char *)"Top width",(char *)"Bottom width",(char *)"Left width",(char *)"Right width",NULL};
   switch(kgMenu1(Parent,220,45,0,bdrmenu,4,NULL,NULL)) {
     case 1:
      ChangeDialogTopWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     case 2:
      ChangeDialogBottomWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     case 3:
      ChangeDialogLeftWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     case 4:
      ChangeDialogRightWidth(Dia);
      DRAW_DIALOG(Dia);
      break;
     default:
      break;
   }
   return v0;
}
