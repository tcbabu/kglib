#include <kulina.h>
extern DIALOG *Parent;
int  slidedtextbox1callback(int key,int i,void *Tmp) {
  DIA *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = ((DIALOG *)Tmp)->d;
  T = D[i].t;
  e = T->elmt;
  return ret;
}
int  slidedhoribar1callback(int key,int i,void *Tmp) {
  DIA *D;DILN *B; 
  int n,ret=1; 
  D = ((DIALOG *)Tmp)->d;
  B = D[i].H;
  n = B->nx;
  switch(key) {
    case 1: 
      break;
  }
  return ret;
}
int slidedinit(void *Tmp) {
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  return ret;
}
void Runslided(void) {
/*************************************************

    Text_Box1  5 data values

*************************************************/
   char  v0[100] ;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   int   v4 = 1;
//   slided( v0, &v1, &v2, &v3, &v4 );
}
