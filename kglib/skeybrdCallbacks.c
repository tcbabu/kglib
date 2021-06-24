#include "kulina.h"
extern KEYBRD Kbrd;
static int ProcessLabel(void *D,int butno,char *Label) {
  int CurWid;
  char ch;
  CurWid = Kbrd.CurWid;
  if(CurWid< 0) return 0;
  kgSetCurrentWidget(D,CurWid);
  ch= Label[butno-1];
  kgSendKeyEvent(D,ch);
  if(Kbrd.ShiftPress) {
    Kbrd.ShiftPress=0;
    ProcessShift(D);
  }
  return 1;
}

int  skeybrdbutton1callback(int butno,int i,void *Tmp) {
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
  switch(butno) {
    case 1: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendEndKeyEvent(Tmp);
      break;
    case 2: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendBackspaceKeyEvent(Tmp);
      break;
    case 3: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendEnterKeyEvent(Tmp);
      break;
    case 4: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendSpaceKeyEvent(Tmp);
      break;
  }
  return ret;
}
void  skeybrdbutton1init(DIN *B,void *pt) {
}
int  skeybrdbutton2callback(int butno,int i,void *Tmp) {
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
  switch(butno) {
    case 1: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendHomeKeyEvent(Tmp);
      break;
    case 2: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendEscapeKeyEvent(Tmp);
      break;
    case 3: 
      kgSetGrpVisibility(D,Kbrd.GrpId,1);
      kgSetGrpVisibility(D,Kbrd.sgrp,0);
      kgSetGrpVisibility(D,Kbrd.symgrp,0);
      kgSetGrpVisibility(D,Kbrd.cgrp,1);
      kgUpdateGrp(D,Kbrd.cgrp);
      kgUpdateOn(D);
      break;
    case 4: 
      kgSetGrpVisibility(D,Kbrd.GrpId,1);
      kgSetGrpVisibility(D,Kbrd.sgrp,0);
      kgSetGrpVisibility(D,Kbrd.cgrp,0);
      kgSetGrpVisibility(D,Kbrd.symgrp,1);
      kgUpdateGrp(D,Kbrd.symgrp);
      kgUpdateOn(D);
      break;
  }
 
  return ret;
}
void  skeybrdbutton2init(DIN *B,void *pt) {
}
int  skeybrdbutton3callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  char Label[]="1234567890abcdefghijklmnopqrstuvwxyz,./?";
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  D = (DIALOG *)Tmp;
  ProcessLabel(D,butno,Label);
  return ret;
}
void  skeybrdbutton3init(DIN *B,void *pt) {
}
int  skeybrdbutton4callback(int butno,int i,void *Tmp) {
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
  switch(butno) {
    case 1: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendHomeKeyEvent(Tmp);
      break;
    case 2: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendEscapeKeyEvent(Tmp);
      break;
    case 3: 
      kgSetGrpVisibility(D,Kbrd.GrpId,1);
      kgSetGrpVisibility(D,Kbrd.cgrp,0);
      kgSetGrpVisibility(D,Kbrd.symgrp,0);
      kgSetGrpVisibility(D,Kbrd.sgrp,1);
      kgUpdateGrp(D,Kbrd.sgrp);
      kgUpdateOn(D);
      break;
    case 4: 
      kgSetGrpVisibility(D,Kbrd.GrpId,1);
      kgSetGrpVisibility(D,Kbrd.cgrp,0);
      kgSetGrpVisibility(D,Kbrd.sgrp,0);
      kgSetGrpVisibility(D,Kbrd.symgrp,1);
      kgUpdateGrp(D,Kbrd.symgrp);
      kgUpdateOn(D);
      break;
  }
  return ret;
}
void  skeybrdbutton4init(DIN *B,void *pt) {
}
int  skeybrdbutton5callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  char Label[]="1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ,./?";
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  ProcessLabel(D,butno,Label);
  return ret;
}
void  skeybrdbutton5init(DIN *B,void *pt) {
}
int  skeybrdbutton6callback(int butno,int i,void *Tmp) {
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
  switch(butno) {
    case 1: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendHomeKeyEvent(Tmp);
      break;
    case 2: 
      kgSetCurrentWidget(D,Kbrd.CurWid);
      kgSendEscapeKeyEvent(Tmp);
      break;
    case 3: 
      kgSetGrpVisibility(D,Kbrd.GrpId,1);
      kgSetGrpVisibility(D,Kbrd.sgrp,0);
      kgSetGrpVisibility(D,Kbrd.symgrp,0);
      kgSetGrpVisibility(D,Kbrd.cgrp,1);
      kgUpdateGrp(D,Kbrd.cgrp);
      kgUpdateOn(D);
      break;
    case 4: 
      kgSetGrpVisibility(D,Kbrd.GrpId,1);
      kgSetGrpVisibility(D,Kbrd.cgrp,0);
      kgSetGrpVisibility(D,Kbrd.symgrp,0);
      kgSetGrpVisibility(D,Kbrd.sgrp,1);
      kgUpdateGrp(D,Kbrd.sgrp);
      kgUpdateOn(D);
      break;
  }
  return ret;
}
void  skeybrdbutton6init(DIN *B,void *pt) {
}
int  skeybrdbutton7callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  char Label[]="1234567890~`!@#$%^&*()_+-={}|[]\\:\";',.<>?";
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  ProcessLabel(D,butno,Label);
  return ret;
}
void  skeybrdbutton7init(DIN *B,void *pt) {
}
int skeybrdinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int skeybrdcleanup(void *Tmp) {
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
int skeybrdCallBack(void *Tmp,void *tmp) {
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
int skeybrdResizeCallBack(void *Tmp) {
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
int skeybrdWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  return ret;
}
