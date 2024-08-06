#include <kulina.h>
static DIT *tbl;
static DIT *TB;
static DICH *CH;
static DIRA *RA;

int  tableboxtextbox1callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  tableboxbrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIRA *R;DIALOG *D; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  R = (DIRA *)kgGetWidget(Tmp,i);
  return ret;
}
void  tableboxbrowser1init(DIRA *R,void *pt) {
	void **apt=(void **)pt;
	tbl= (DIT *)apt[0];
	int Font =tbl->Font;
	RA = R;
	ThumbNail **th = (ThumbNail **)R->list;
	*(RA->df)=Font-16+1;
//	kgSetList(RA,(void**)th);
}
int  tableboxbrowser2callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DICH *C;DIALOG *D; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  C = (DICH *)kgGetWidget(Tmp,i);
  int type;
  th = (ThumbNail **) C->list;
  return ret;
}
void  tableboxbrowser2init(DICH *C,void *pt) {
	void **apt=(void **)pt;
	tbl= (DIT *)apt[0];
	int type=0;
	CH = C;
	ThumbNail **th = (ThumbNail **)C->list;
	th[1]->sw = tbl->hide;
	th[0]->sw = tbl->bordr;
	if(tbl->type != 0) type=1;
	th[2]->sw = type;
//	kgSetList(CH,(void **)th);
}

int  tableboxsplbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  ThumbNail **th;
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(butno) {
    case 1: 
      break;
    case 2: 
      th = (ThumbNail **) CH->list;
      tbl->bordr = th[0]->sw;
      tbl->hide = th[1]->sw;
      tbl->type = th[2]->sw;
      tbl->Font=16+(*RA->df)-1;
      tbl->nx= kgGetInt(TB,0);
      tbl->ny= kgGetInt(TB,1);
      tbl->width= kgGetInt(TB,2);
      tbl->FontSize= kgGetInt(TB,3);
      strcpy(tbl->Wid,kgGetString(TB,4));
      pt[1]=tbl;
      break;
  }
  return ret;
}
void  tableboxsplbutton1init(DIL *B,void *pt) {
}
int tableboxinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  tbl = (DIT *)pt[0];
  int hide,bordr,type=0;
  TB = (DIT *)kgGetNamedWidget(Tmp,(char *)"tableTbox");
  kgSetInt(TB,0,tbl->nx);
  kgSetInt(TB,1,tbl->ny);
  kgSetInt(TB,2,tbl->width);
  kgSetInt(TB,3,tbl->FontSize);
  kgSetString(TB,4,tbl->Wid);
  kgUpdateWidget(TB);

   if(tbl->type != 0) tbl->type=1;
 /* pt[0] is inputs, given by caller */
  return ret;
}
int tableboxcleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
 /* pt[1] is outputs, if any  to be given to caller */
 /* pt[0] is inputs, given by caller */
  return ret;
}
int Modifytablebox(void *Tmp,int GrpId) {
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
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

int tableboxCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
int tableboxResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
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
int tableboxWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  return ret;
}
