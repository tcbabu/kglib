#include <kulina.h>
static DII *Bmsg=NULL;
static char Buf[50];
int  ButnTypebutton1callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 0;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton1init(DIN *B,void *pt) {
}
int  ButnTypebutton2callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 1;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton2init(DIN *B,void *pt) {
}
int  ButnTypebutton3callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 2;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton3init(DIN *B,void *pt) {
}
int  ButnTypebutton4callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 3;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton4init(DIN *B,void *pt) {
}
int  ButnTypebutton5callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 4;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton5init(DIN *B,void *pt) {
}
int  ButnTypebutton6callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 5;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton6init(DIN *B,void *pt) {
}
int  ButnTypebutton7callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 6;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton7init(DIN *B,void *pt) {
}
int  ButnTypebutton8callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 7;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton8init(DIN *B,void *pt) {
}
int  ButnTypebutton9callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 8;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton9init(DIN *B,void *pt) {
}
int  ButnTypebutton10callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 9;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton10init(DIN *B,void *pt) {
}
int  ButnTypebutton11callback(int butno,int i,void *Tmp) {
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
  int *type=(int *)(D->pt);
  *type = 10;
  sprintf(Buf,"!w32!f21Selected Type: %d",*type);
  kgWrite(Bmsg,Buf);
  kgUpdateOn(Tmp);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypebutton11init(DIN *B,void *pt) {
}
int  ButnTypesplbutton1callback(int butno,int i,void *Tmp) {
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
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  ButnTypesplbutton1init(DIL *B,void *pt) {
}
int ButnTypeinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1,*type;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  type = (int *)pt;
  Bmsg = (DII *)kgGetNamedWidget(Tmp,(char *)"ButnMsg");
  sprintf(Buf, "!w32!f21!c38Default Type: %d",*type);
  kgWrite(Bmsg,Buf);
  return ret;
}
int ButnTypecleanup(void *Tmp) {
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
int ModifyButnType(void *Tmp,int GrpId) {
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

int ButnTypeCallBack(void *Tmp,void *tmp) {
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
int ButnTypeResizeCallBack(void *Tmp) {
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
int ButnTypeWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  return ret;
}
