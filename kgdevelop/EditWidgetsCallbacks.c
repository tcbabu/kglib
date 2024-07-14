#include <kulina.h>
Dlink *GetGuiList(void);
int ResetGuiList(Dlink *L);
ThumbNail **GetGuiThumbNails(void);
DIN * Edit_Buttons(DIN *h);
static Dlink *Glist=NULL;
static void** Garry=NULL;
  static int ClearSelection ( void *Wid ) {
      int i;
      ThumbNail **Th = ( ThumbNail ** ) kgGetList ( Wid ) ;
      i = 0;
      while ( Th [ i ] != NULL ) {
          Th [ i ] -> sw = 0;
          i++;
      }
      return 1;
  }
  static int SelectAll ( void *Wid ) {
      int i;
      ThumbNail **Th = ( ThumbNail ** ) kgGetList ( Wid ) ;
      i = 0;
      while ( Th [ i ] != NULL ) {
          Th [ i ] -> sw = 1;
          i++;
      }
      return 1;
  }
  static int kgDragRearrange( void *Tmp , void *fw , int item ) {
	  /* returns 0 if no rearrange
	   * pos number (from 1 to max) if rearrange
	  */
      DIY *FY , *TY;
      FY = ( DIY * ) fw;
      int x = -1 , y = -1;
      void *tw = NULL;
      int sid , did;
      char *des = NULL;
      int same = 0;
      if ( kgDragThumbNail ( FY , item , & x , & y ) ) {
          tw = ( DIT * ) kgGetLocationWidget ( Tmp , x , y ) ;
          if ( tw == fw ) {
                  ThumbNail **Th = NULL,*tth;
                  char *name;
		  int positem = 1000000;
		  positem = kgGetThumbNailItem((DIY *)tw,x,y);
		  if(positem != item){
	            Th = (ThumbNail **)kgGetList(FY);
		    tth = Th[item];
		    Th[item]= Th[positem];
		    Th[positem]= tth;
		    kgSetList(FY,(void **)Th);
                    ClearSelection ( FY ) ;
                    kgUpdateWidget ( FY ) ;
                    kgUpdateOn ( Tmp ) ;
		    return positem+1;
		  }
                  return 0;
          }
          else return 0;
      }
      return 0;
  }
int  EditWidgetsbrowser1callback(int item,int i,void *Tmp) {
  DIALOG *D;DIY *Y; 
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret=1; 
  int pos=0;
  void *ptmp;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  ThumbNail **Th;
  char code;
  DIT *T;
  D = (DIALOG *)Tmp;
  Y = (DIY *)kgGetWidget(Tmp,i);
  if ((pos=kgDragRearrange(Tmp,Y,item-1))) {
	  ptmp = Garry[item-1];
	  Garry[item-1]= Garry[pos-1];
	  Garry[pos-1]= ptmp;
	  return 1;
  }
  T = (DIT *)Garry[item-1];
  code = T->code;
  switch(code) {
    case 'n': 
      Edit_Buttons((DIN *)T);
      break;
    case 'h': 
      Edit_Buttons((DIN *)T);
      break;
  }
  return ret;
}
void  EditWidgetsbrowser1init(DIY *Y,void *pt) {
 // One may setup browser list here by setting Y->list
 // if it need to be freed set it as Y->pt also
   int n,i=0;;
   void *ptmp;
   void **List = (void **)GetGuiThumbNails();
   kgSetList(Y,List);
   Glist = GetGuiList();
   n = Dcount(Glist);
   Garry = (void **)malloc(sizeof(void *)*(n+1));
   Resetlink(Glist);
   i=0;
   while((ptmp=Getrecord(Glist))!= NULL) Garry[i++]=ptmp;
   Garry[i]=NULL;

}
int  EditWidgetssplbutton1callback(int butno,int i,void *Tmp) {
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
  Dfree(Glist);
  Glist = Dopen();
  int k=0;
  while(Garry[k] != NULL) Dadd(Glist,Garry[k++]);
  Resetlink(Glist);
  ResetGuiList(Glist);
  Dfree(Glist);
  free(Garry);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  EditWidgetssplbutton1init(DIL *B,void *pt) {
}
int EditWidgetsinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  return ret;
}
int EditWidgetscleanup(void *Tmp) {
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
int ModifyEditWidgets(void *Tmp,int GrpId) {
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

int EditWidgetsCallBack(void *Tmp,void *tmp) {
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
int EditWidgetsResizeCallBack(void *Tmp) {
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
int EditWidgetsWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  return ret;
}
