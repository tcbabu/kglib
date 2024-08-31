#include <kulina.h>
typedef struct _Tbstr {
        int index;
        int nx;
        int ny;
        int n;
        int *sw;
        int *Field;
        int *Type;
}TBSTR;
static TBSTR *e;
static DIN *P,*N;
static DIT *T;
static DIRA *R1,*R2;
static DIM *Msg;
static char Buf[200];

int  tableelmttextbox1callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;
  int ret=1;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  int index=e->index;
  e->Field[index] = kgGetInt(T,0);

  return ret;
}
int  tableelmtbrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIRA *R;DIALOG *D; 
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  R = (DIRA *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) R->list;
  int index=e->index;
  e->Type[index] = item -1;
  return ret;
}
void  tableelmtbrowser1init(DIRA *R,void *pt) {
}
int  tableelmtbrowser2callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIRA *R;DIALOG *D; 
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  R = (DIRA *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) R->list;
  int index=e->index;
  e->sw[index] = item -1;
  return ret;
}
void  tableelmtbrowser2init(DIRA *R,void *pt) {
}
int  tableelmtbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  int index = e->index;
  if(index== 0) return 1;
  e->Field[index] = kgGetInt(T,0);
  e->Type[index]=kgGetSelection(R1) -1;
  e->sw[index]=kgGetSelection(R2) -1;
  if(index== (e->n-1)) kgSetWidgetVisibility(N,1);
  index -= 1;
  e->index = index;
  if(index== 0) kgSetWidgetVisibility(P,0);
  kgSetInt(T,0,e->Field[index]);
  kgSetSelection(R1,e->Type[index]+1);
  kgSetSelection(R2,e->sw[index]+1);
  kgUpdateWidget(R1);
  kgUpdateWidget(R2);
  kgUpdateWidget(T);
  sprintf(Buf,"Table Column: %d",(index));
  kgWrite(Msg,Buf);
  kgUpdateOn(Tmp);

  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  tableelmtbutton1init(DIN *B,void *pt) {
}
int  tableelmtbutton2callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  int index = e->index;
  if(index== (e->n-1)) return 1;
  e->Field[index] = kgGetInt(T,0);
  e->Type[index]=kgGetSelection(R1) -1;
  e->sw[index]=kgGetSelection(R2) -1;
  if(index== 0) kgSetWidgetVisibility(P,1);
  index += 1;
  e->index = index;
  if(index== (e->n-1)) kgSetWidgetVisibility(N,0);
  kgSetInt(T,0,e->Field[index]);
  kgSetSelection(R1,e->Type[index]+1);
  kgSetSelection(R2,e->sw[index]+1);
  kgUpdateWidget(R1);
  kgUpdateWidget(R2);
  kgUpdateWidget(T);
  sprintf(Buf,"Table Column: %d",(index));
  kgWrite(Msg,Buf);
  kgUpdateOn(Tmp);

  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  tableelmtbutton2init(DIN *B,void *pt) {
}
int  tableelmtsplbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  int index=e->index;
  e->Field[index] = kgGetInt(T,0);
  e->Type[index]=kgGetSelection(R1)-1;
  e->sw[index]=kgGetSelection(R2)-1;

  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  tableelmtsplbutton1init(DIL *B,void *pt) {
}
int tableelmtinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  int index;
  e = (TBSTR *)pt;
  index = e->index;
  P = (DIN *)kgGetNamedWidget(Tmp,(char *)"tableelmtPrevious");
  N = (DIN *)kgGetNamedWidget(Tmp,(char *)"tableelmtNext");
  Msg = (DIM *)kgGetNamedWidget(Tmp,(char *)"tableelmtMsg");
  T   = (DIT *)kgGetNamedWidget(Tmp,(char *)"tableelmtTbox");
  R1  = (DIRA *)kgGetNamedWidget(Tmp,(char *)"tableelmtRadio1");
  R2  = (DIRA *)kgGetNamedWidget(Tmp,(char *)"tableelmtRadio2");
  kgSetInt(T,0,e->Field[index]);
  kgSetSelection(R1,e->Type[index]+1);
  kgSetSelection(R2,e->sw[index]+1);
  kgUpdateWidget(T);
  kgSetWidgetVisibility(P,0);
  sprintf(Buf,"Table Column: %d",(index));
  kgWrite(Msg,Buf);
  if(e->n == 1) {
    kgSetWidgetVisibility(N,0);
  }

  return ret;
}
int tableelmtcleanup(void *Tmp) {
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
int Modifytableelmt(void *Tmp,int GrpId) {
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

int tableelmtCallBack(void *Tmp,void *tmp) {
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
int tableelmtResizeCallBack(void *Tmp) {
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
int tableelmtWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  return ret;
}
