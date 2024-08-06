#include <kulina.h>
static DIT *Tbox;
int  defaultEdittextbox1callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  Tbox = T;
  e = T->elmt;
  return ret;
}
int  defaultEditsplbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  char  **pt= (char **)kgGetArgPointer(Tmp); // Change as required
  DIT *T = (DIT *)kgGetNamedWidget(Tmp,(char *)"defaultEditTbox");
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  defaultEditsplbutton1init(DIL *B,void *pt) {
}
int defaultEditinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  char  **pt= (char **)kgGetArgPointer(Tmp); // Change as required
  DIM *M = (DIM *)kgGetNamedWidget(Tmp,(char *)"defaultEditMsg");
  DIT *T = (DIT *)kgGetNamedWidget(Tmp,(char *)"defaultEditTbox");
  kgWrite(M,pt[0]);
  kgSetString(T,0,pt[1]);
  kgUpdateWidget(T);
  Tbox = T;
 
  return ret;
}
int defaultEditcleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  return ret;
}
int ModifydefaultEdit(void *Tmp,int GrpId) {
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  DIA *d;
  int i,n;
  d = D->d;
  i=0;while(d[i].t!= NULL) {;
     i++;
  };
  n=1;
  return GrpId;
}

int defaultEditCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
int defaultEditResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
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
int defaultEditWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  return ret;
}
