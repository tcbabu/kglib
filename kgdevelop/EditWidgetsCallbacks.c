#include <kulina.h>
Dlink *GetGuiList(void);
int ResetGuiList(Dlink *L);
void *RundefaultEdit(void *,char *,char *);
ThumbNail **GetGuiThumbNails(void);
DIN * Edit_Buttons(void *Dtmp,DIN *h);
void * Edit_t_box(void *Dtmp,void *ttmp);
void * Edit_T_box(void *Dtmp,void *ttmp);
int Runtextboxesdata(void *arg,void *t);
void *Runselectmenu(void *Dia,void *arg);
void *Runthumbnail(void *Dia,void *arg);
void *Runcheckbox(void *Dia,void *arg);
void *Runradiobuttons(void *Dia,void *arg);
void *RunEditThumbnails(void *arg,int items,void *Th);

static Dlink *Glist=NULL;
static void** Garry=NULL;
extern DIALOG *Parent;
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
      int k;
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
#if 0
		    Th[item]= Th[positem];
#else
		    if(positem < item) {
			    for(k=item-1;k>=positem; k--){
				    Th[k+1] = Th[k];
			    }
		    }
		    else {
			    for(k=item+1;k<=positem; k++){
				    Th[k-1] = Th[k];
			    }
		    }
#endif
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
#define UpdateList( str) { \
      Th = (ThumbNail **)kgGetList(Y); \
      free(Th[item -1]->name); \
      Th[item-1]->name = (char *)malloc(strlen(str)+1); \
      strcpy(Th[item-1]->name,str); \
      kgSetList(Y,(void **)Th); \
      ClearSelection ( Y ) ; \
      kgUpdateWidget(Y); \
      kgUpdateOn(Tmp); \
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
  int k;
  DIT *T;
  D = (DIALOG *)Tmp;
  Y = (DIY *)kgGetWidget(Tmp,i);
  if ((pos=kgDragRearrange(Tmp,Y,item-1))) {
	  ptmp = Garry[item-1];
#if 0
	  Garry[item-1]= Garry[pos-1];
	  Garry[pos-1]= ptmp;
#else
	  pos = pos -1;
	  item = item -1;

		    if(pos < item) {
			    for(k=item-1;k>=pos; k--){
				    Garry[k+1] = Garry[k];
			    }
		    }
		    else {
			    for(k=item+1;k<=pos; k++){
				    Garry[k-1] = Garry[k];
			    }
		    }
		    Garry[pos]= ptmp;;
#endif
	  return 1;
  }
  T = (DIT *)Garry[item-1];
  code = T->code;
  switch(code) {
    case 'n': 
      Edit_Buttons(Tmp,(DIN *)T);
      UpdateList((((DIN *)T)->Wid));
      break;
    case 'h': 
      Edit_Buttons(Tmp,(DIN *)T);
      UpdateList((((DIN *)T)->Wid));
      break;
    case 't': 
      Edit_t_box(Tmp,T);
      UpdateList((((DIT *)T)->Wid));
      break;
    case 'm':
      RundefaultEdit(Tmp,(char *)"Message Type1",((DIM *)T)->Wid);
#if 0
      Th = (ThumbNail **)kgGetList(Y);
      free(Th[item -1]->name);
      Th[item-1]->name = (char *)malloc(strlen(((DIM *)T)->Wid)+1);
      strcpy(Th[item-1]->name,((DIM *)T)->Wid);
      kgSetList(Y,(void **)Th);
      ClearSelection ( Y ) ;
      kgUpdateWidget(Y);
      kgUpdateOn(Tmp);d
#else
      UpdateList((((DIM *)T)->Wid));
#endif
      break;
    case 'T':
      Edit_T_box(Tmp,T);
      UpdateList((((DIT *)T)->Wid));
      break;
    case 'M':
      RundefaultEdit(Tmp,(char *)"Display Box",((DIM *)T)->Wid);
      UpdateList((((DIM *)T)->Wid));
      break;
    case 'B':
      RundefaultEdit(Tmp,(char *)"Message Type2",((DIM *)T)->Wid);
      UpdateList((((DIM *)T)->Wid));
      break;
    case 'x':
      RundefaultEdit(Tmp,(char *)"Selection Menu",((DIX *)T)->Wid);
      UpdateList((((DIX *)T)->Wid));
      break;
    case 'y':
      RundefaultEdit(Tmp,(char *)"ThumbNail Browser",((DIY *)T)->Wid);
      UpdateList((((DIY *)T)->Wid));
      break;
    case 'c':
      RundefaultEdit(Tmp,(char *)"Check Box",((DICH *)T)->Wid);
      UpdateList((((DICH *)T)->Wid));
      break;
    case 'r':
      RundefaultEdit(Tmp,(char *)"Radio Buttons",((DIRA *)T)->Wid);
      UpdateList((((DIRA *)T)->Wid));
      break;
    case 'w':
      RundefaultEdit(Tmp,(char *)"Pulldown Menu",((DIW *)T)->Wid);
      UpdateList((((DIW *)T)->Wid));
      break;
    case 'e':
      RundefaultEdit(Tmp,(char *)"Scroll Menu",((DIE *)T)->Wid);
      UpdateList((((DIE *)T)->Wid));
      break;
    case 's':
      RundefaultEdit(Tmp,(char *)"Scroll Message",((DIS *)T)->Wid);
      UpdateList((((DIS *)T)->Wid));
      break;
    case 'i':
      RundefaultEdit(Tmp,(char *)"Info Box",((DII *)T)->Wid);
      UpdateList((((DII *)T)->Wid));
      break;
    case 'o':
      RundefaultEdit(Tmp,(char *)"Progress Bar",((DIO *)T)->Wid);
      UpdateList((((DIO *)T)->Wid));
      break;
    case 'v':
      RundefaultEdit(Tmp,(char *)"Vertical Scroll Bar",((DIV *)T)->Wid);
      UpdateList((((DIV *)T)->Wid));
      break;
    case 'z':
      RundefaultEdit(Tmp,(char *)"Horizondal Scroll Bar",((DIZ *)T)->Wid);
      UpdateList((((DIZ *)T)->Wid));
      break;
    case 'p':
      RundefaultEdit(Tmp,(char *)"Display Box",((DIP *)T)->Wid);
      UpdateList((((DIP *)T)->Wid));
      break;
    case 'g':
      RundefaultEdit(Tmp,(char *)"Drawing Area",((DIG *)T)->Wid);
      UpdateList((((DIG *)T)->Wid));
      break;
    case 'd':
      RundefaultEdit(Tmp,(char *)"Integer Slide",((DID *)T)->Wid);
      UpdateList((((DID *)T)->Wid));
      break;
    case 'f':
      RundefaultEdit(Tmp,(char *)"Float Slide",((DIF *)T)->Wid);
      UpdateList((((DIF *)T)->Wid));
      break;
    case 'P':
      RundefaultEdit(Tmp,(char *)"Horizontal Slide",((DIF *)T)->Wid);
      UpdateList((((DIF *)T)->Wid));
      break;
    default:
      break;
  }
  return ret;
}
int  ModifyWidget(void *Tpt) {
  int ret=1,j; 
  ThumbNail **Th;
  char code;
  void **Thret=NULL;
  int k;
  DIX *X;
  DIY *Y;
  DICH *C;
  DIRA *R;
  DIS  *S;
  DIT *T= (DIT *)Tpt;
  DIALOG *Tmp = Parent;
  code = T->code;
  switch(code) {
    case 'n': 
      Edit_Buttons(Tmp,(DIN *)T);
      break;
    case 'h': 
      Edit_Buttons(Tmp,(DIN *)T);
      break;
    case 't': 
      Edit_t_box(Tmp,T);
      break;
    case 'm':
      RundefaultEdit(Tmp,(char *)"Message Type1",((DIM *)T)->Wid);
      break;
    case 'T':
      Edit_T_box(Tmp,T);
      break;
    case 'M':
      RundefaultEdit(Tmp,(char *)"Display Box",((DIM *)T)->Wid);
      break;
    case 'B':
      RundefaultEdit(Tmp,(char *)"Message Type2",((DIM *)T)->Wid);
      break;
    case 'x':
      X=(DIX *)T;
//      RundefaultEdit(Tmp,(char *)"Selection Menu",((DIX *)T)->Wid);
      Runselectmenu(Tmp,X);
      X->y2 = X->y1 - abs(X->y2 -X->y1);
      break;
    case 'y':
      Y=(DIY *)T;
//      RundefaultEdit(Tmp,(char *)"ThumbNail Browser",((DIY *)T)->Wid);
      Runthumbnail(Tmp,Y);
      Y->y2 = Y->y1 - abs(Y->y2 -Y->y1);
      break;
    case 'c':
      C = (DICH *)T;
//      RundefaultEdit(Tmp,(char *)"Check Box",((DICH *)T)->Wid);
      Runcheckbox(Tmp,C);
      C->y2 = C->y1 - abs(C->y2 -C->y1);
      Thret = (void **)RunEditThumbnails(Tmp,C->ny,(void*)kgGetList(C));
      j=0;while(Thret[j]!= NULL) j++;
      C->nx=1;
      C->ny = j;
      C->list = Thret;
      break;
    case 'r':
      R = (DIRA *) T;
//      RundefaultEdit(Tmp,(char *)"Radio Buttons",((DIRA *)T)->Wid);
      Runcheckbox(Tmp,R);
      R->y2 = R->y1 - abs(R->y2 -R->y1);
      Thret = (void **)RunEditThumbnails(Tmp,R->ny,(void*)kgGetList(R));
      j=0;while(Thret[j]!= NULL) j++;
      R->nx=1;
      R->ny = j;
      R->list = Thret;
      break;
    case 'w':
      RundefaultEdit(Tmp,(char *)"Pulldown Menu",((DIW *)T)->Wid);
      break;
    case 'e':
      RundefaultEdit(Tmp,(char *)"Scroll Menu",((DIE *)T)->Wid);
      break;
    case 's':
      RundefaultEdit(Tmp,(char *)"Scroll Message",((DIS *)T)->Wid);
      break;
    case 'i':
      RundefaultEdit(Tmp,(char *)"Info Box",((DII *)T)->Wid);
      break;
    case 'o':
      RundefaultEdit(Tmp,(char *)"Progress Bar",((DIO *)T)->Wid);
      break;
    case 'v':
      RundefaultEdit(Tmp,(char *)"Vertical Scroll Bar",((DIV *)T)->Wid);
      break;
    case 'z':
      RundefaultEdit(Tmp,(char *)"Horizondal Scroll Bar",((DIZ *)T)->Wid);
      break;
    case 'p':
      RundefaultEdit(Tmp,(char *)"Display Box",((DIP *)T)->Wid);
      break;
    case 'g':
      RundefaultEdit(Tmp,(char *)"Drawing Area",((DIG *)T)->Wid);
      break;
    case 'd':
      RundefaultEdit(Tmp,(char *)"Integer Slide",((DID *)T)->Wid);
      break;
    case 'f':
      RundefaultEdit(Tmp,(char *)"Float Slide",((DIF *)T)->Wid);
      break;
    case 'P':
      RundefaultEdit(Tmp,(char *)"Horizontal Slide",((DIF *)T)->Wid);
      break;
    default:
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
