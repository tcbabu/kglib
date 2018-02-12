#include <kulina.h>
extern DIALOG *Parent;
int  slideftextbox1callback(int key,int i,void *Tmp) {
  DIA *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = ((DIALOG *)Tmp)->d;
  T = D[i].t;
  e = T->elmt;
  return ret;
}
int  slidefhoribar1callback(int key,int i,void *Tmp) {
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
int slidefinit(void *Tmp) {
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  return ret;
}
void Runslidef(void) {
/*************************************************

    Text_Box1  5 data values

*************************************************/
   char  v0[100] ;
   int   v1 = 1;
   float v2 = 0.0;
   float v3 = 0.0;
   float v4 = 0.0;
//   slidef( v0, &v1, &v2, &v3, &v4 );
}
