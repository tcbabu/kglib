#include <kulina.h>
typedef struct _Estr {
        int index;
        int nx;
        int ny;
        int n;
        char **Prompt;
        int *sw;
        int *Field;
        int *Type;
        int *noecho;
}ESTR;

static ESTR *e;
static DIN *P,*N;
static DIT *T;
static DIRA *R,*R2;
static DIM *Msg;
static char Buf[200];
int  textelementdatatextbox1callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  textelementdatabrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIRA *R;DIALOG *D;void *pt; 
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  pt = D->pt;
  R = (DIRA *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) R->list;
  int index=e->index;
  e->Type[index] = item -1;
  return ret;
}
void  textelementdatabrowser1init(DIRA *R,void *pt) {
}
int  textelementdatasplbutton1callback(int butno,int i,void *Tmp) {
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
  int index=e->index;
  strcpy(e->Prompt[index],kgGetString(T,0));
  e->Field[index] = kgGetInt(T,1);
  e->Type[index]=kgGetSelection(R)-1;
  e->noecho[index]=kgGetSelection(R2)-1;
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  textelementdatasplbutton1init(DIL *B,void *pt) {
}
int  textelementdatabutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  int index = e->index;
  if(index== 0) return 1;
  strcpy(e->Prompt[index],kgGetString(T,0));
  e->Field[index] = kgGetInt(T,1);
  e->Type[index]=kgGetSelection(R) -1;
  e->noecho[index]=kgGetSelection(R2) -1;
  if(index== (e->n-1)) kgSetWidgetVisibility(N,1);
  index -= 1;
  e->index = index;
  if(index== 0) kgSetWidgetVisibility(P,0);
  kgSetString(T,0,e->Prompt[index]);
  kgSetInt(T,1,e->Field[index]);
  kgSetSelection(R,e->Type[index]+1);
  kgSetSelection(R2,e->noecho[index]+1);
  kgUpdateWidget(R);
  kgUpdateWidget(R2);
  kgUpdateWidget(T);
  sprintf(Buf,"Text Box: (%d,%d)",(index%e->nx),(index/e->nx));
  kgWrite(Msg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  textelementdatabutton1init(DIN *B,void *pt) {
}
int  textelementdatabutton2callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  int index = e->index;
  if(index== (e->n-1)) return 1;
  strcpy(e->Prompt[index],kgGetString(T,0));
  e->Field[index] = kgGetInt(T,1);
  e->Type[index]=kgGetSelection(R) -1;
  e->noecho[index]=kgGetSelection(R2)-1;
  if(index== 0) kgSetWidgetVisibility(P,1);
  index += 1;
  e->index = index;
  if(index== (e->n-1)) kgSetWidgetVisibility(N,0);
  kgSetString(T,0,e->Prompt[index]);
  kgSetInt(T,1,e->Field[index]);
  kgSetSelection(R,e->Type[index]+1);
  kgSetSelection(R2,e->noecho[index]+1);
  kgUpdateWidget(R);
  kgUpdateWidget(R2);
  kgUpdateWidget(T);
  sprintf(Buf,"Text Box: (%d,%d)",(index%e->nx),(index/e->nx));
  kgWrite(Msg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  textelementdatabutton2init(DIN *B,void *pt) {
}
int  textelementdatabrowser2callback(int item,int i,void *Tmp) {
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
  return ret;
}
void  textelementdatabrowser2init(DIRA *R,void *pt) {
}
int textelementdatainit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  int index;
  e = (ESTR *)pt;
  index = e->index;
  P = (DIN *)kgGetNamedWidget(Tmp,(char *)"elementPrevious");
  N = (DIN *)kgGetNamedWidget(Tmp,(char *)"elementNext");
  Msg = (DIM *)kgGetNamedWidget(Tmp,(char *)"elementMsg");
  T   = (DIT *)kgGetNamedWidget(Tmp,(char *)"elementTbox");
  R   = (DIRA *)kgGetNamedWidget(Tmp,(char *)"elementRadio");
  R2  = (DIRA *)kgGetNamedWidget(Tmp,(char *)"elementRadio2");
  kgSetInt(T,1,e->Field[index]);
  kgSetString(T,0,e->Prompt[index]);
  kgSetWidgetVisibility(P,0);
  sprintf(Buf,"Text Box: (%d,%d)",(index%e->nx),(index/e->nx));
  kgWrite(Msg,Buf);
  if(e->n == 1) {
    kgSetWidgetVisibility(N,0);
  }
  return ret;
}
int textelementdatacleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int Modifytextelementdata(void *Tmp,int GrpId) {
  DIALOG *D;
  D = (DIALOG *)Tmp;
  DIA *d;
  int i,n;
  d = D->d;
  i=0;while(d[i].t!= NULL) {;
     i++;
  };
  n=1;
  return GrpId;
}

int textelementdataCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
int textelementdataResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
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
int textelementdataWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  return ret;
}
