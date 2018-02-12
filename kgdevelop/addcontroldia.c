#include <kulina.h>
extern DIALOG * Parent;
int  addcontroldiabutnbox1callback(int key,int i,void *Tmp) {
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
    case 4: 
      break;
    case 5: 
      break;
    case 6: 
      break;
    case 7: 
      break;
    case 8: 
      break;
    case 9: 
      break;
    case 10: 
      break;
    case 11: 
      break;
    case 12: 
      break;
    case 13: 
      break;
    case 14: 
      break;
    case 15: 
      break;
  }
  return ret;
}
int Runaddcontroldia(void *parent) {
/*************************************************

    Buttonbox1 (new) 1 data value

*************************************************/
   int   v0 = 1;
//   addcontroldia(parent, &v0 );
   return  v0;
}
