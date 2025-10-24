#include <kulina.h>
static DIS *Info;
 /* Callback for  UpdatesCheckWidget3   */ 

int UpdatesCheckbrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DICH *C;DIALOG *D; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  ThumbNail **th; 
  int ret=1; 
  int *ipt= (int *)pt[0];
  D = (DIALOG *)Tmp;
  C = (DICH *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) C->list;
  ipt[0]= kgGetSwitch(C,0);   
  ipt[1]= kgGetSwitch(C,1);   
  return ret;
}
void  UpdatesCheckbrowser1init(DICH *C,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
 int *vals=(int *)pt[0];
 kgSetSwitch(C,0,vals[0]);
 kgSetSwitch(C,1,vals[1]);
}

 /* Callback for  UpdatesCheckWidget4   */ 

int UpdatesChecksplbutton1callback( int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(butno) {
    case 1: //  Okay 
      break;
  }
  return ret;
}
void  UpdatesChecksplbutton1init(DIL *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
void * UpdatesCheckbrowser2init(DIS *S,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
 return NULL;
}
int UpdatesCheckinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  Info = (DIS *)kgGetNamedWidget(Tmp,(char *)"InfoBox");
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs, given by caller */
  kgWrite(Info,(char *)"!c03!z43Please read this message");
  kgWrite(Info,(char *)" ");
  kgWrite(Info,(char *)"You are asked whether  to update the changes in the Callbacks or not.");
  kgWrite(Info,(char *)"Nothing from the Callbacks file is removed. Only new additions are included.");
  kgWrite(Info,(char *)"any unwanted lines need to be removed manually, though it won't create any problems.");
  kgWrite(Info,(char *)" ");
  kgWrite(Info,(char *)"The second option is whether to copy the new Dialog .src file to the .c file or not");
  kgWrite(Info, (char *)"This is important since codes can be changed by the developer, as there is");
  kgWrite(Info,(char *)" a way to send information and get back information through argument and ");
  kgWrite(Info,(char *)" through return pointer, however it is better to avoid that.");
  kgWrite(Info,(char *)" !c01 Original files will be backed up as .org files");
  kgWrite(Info,(char *)" !c02!z54 .src files will be  made anyway!!!");
  return ret;
}
int UpdatesCheckcleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[1] is outputs, if any  to be given to caller */
 /* pt[0] is inputs, given by caller */
  return ret;
}
int ModifyUpdatesCheck(void *Tmp,int GrpId) {
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs given by caller */
  DIA *d;
  int i,n;
  d = D->d;
  i=0;while(d[i].t!= NULL) {;
     i++;
  };
  n=1;
//  strcpy(D->name,"Kulina Designer ver 2.0");    /*  Dialog name you may change */
#if 0
  if(D->fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D->xo=D->yo=0; D->xl = xres-10; D->yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D->xo=D->yo=0; D->xl = xres; D->yl=yres;
//     D->StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
#endif
  return GrpId;
}

int UpdatesCheckCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
int UpdatesCheckResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
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
int UpdatesCheckWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  return ret;
}
