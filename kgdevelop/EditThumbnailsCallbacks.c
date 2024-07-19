#include <kulina.h>

static Dlink *Glist=NULL;
static void** Garry=NULL;
static int Nitems=0;
static DIY *Y=NULL;
static DIM *M=NULL;
static char Buf[200];
extern DIALOG *Parent;
static DIALOG *Dtmp;
void *RunAddItem(void *arg,char *Prompt);

ThumbNail **MakeStringThumbNails(char **Str,int l,int w);
//extern DIALOG *Parent;
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
  static int DeleteSelection ( void *Wid ) {
      int i;
      ThumbNail **Th = ( ThumbNail ** ) kgGetList ( Wid ) ;
      void *pt;
      i = 0;
      Glist = Dopen();
      while ( Th [ i ] != NULL ) {
          if(Th [ i ] -> sw != 1) Dadd(Glist,Th[i]);
	  else kgFreeThumbNail(Th[i]);
          i++;
      }
      Resetlink(Glist);
      i=0;
      while( (pt= Getrecord(Glist)) != NULL) {
	      Th[i++]= (ThumbNail *)pt;
      }
      Th[i]=NULL;
      kgSetList(Wid,(void **)Th);
      kgUpdateWidget(Wid);
      Dfree(Glist);
      return 1;
  }
  static int AddItem ( void *Wid ) {
      int i;
      ThumbNail **Th = ( ThumbNail ** ) kgGetList ( Wid ) ;
      ThumbNail **Tadd=NULL;
      DIY *Y = (DIY *)Wid;
      void *pt;
      char *Str[2];
      char *cpt;
      i = 0;
      Buf[0]='\0';
//      gscanf(Parent,(char *)"String To Add:%30s",Buf);
      cpt = (char *)RunAddItem((void *)Dtmp,(char *)"New Brwoser Item");
      strcpy(Buf,cpt);
      free(cpt);
      Str[0]=Buf;
      Str[1]=NULL;
      Tadd = (ThumbNail **) MakeStringThumbNails(Str,Y->lngth+Y->xgap,Y->width);
      Glist = Dopen();
      while ( Th [ i ] != NULL ) {
	  Dadd(Glist,Th[i]);
          i++;
      }
      i=0;
      while( Tadd[i] != NULL) {
	  Dadd(Glist,Tadd[i]);
          i++;
      }
      if(Tadd!=NULL) free(Tadd);
      Resetlink(Glist);
      if(Th != NULL) free(Th);
      Th = (ThumbNail **)malloc(sizeof(ThumbNail *)*(Dcount(Glist)+1));
      i=0;
      Resetlink(Glist);
      while( (pt= Getrecord(Glist)) != NULL) {
	      Th[i++]= (ThumbNail *)pt;
      }
      Th[i]=NULL;
      kgSetList(Wid,(void **)Th);
      kgUpdateWidget(Wid);
      Dfree(Glist);
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
int  EditThumbnailsbrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIY *X; 
  int ret=0; 
  void *ptmp;
  char code;
  int pos,k;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  X = (DIY *)kgGetWidget(Tmp,i);
  
  if ((pos=kgDragRearrange(Tmp,X,item-1))) {
	  ptmp = Garry[item-1];
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
	  return 1;
  }
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
ThumbNail **MakeStringThumbNails(char **Str,int lngth,int width) {
	 int i;
	 ThumbNail **Th =NULL;
	 if(Str != NULL) {
		 Th = (ThumbNail **)kgStringToThumbNails(Str);
		 i=0;
		 while(Str[i]!= NULL) {
		   Th[i]->img = kgStringToImage(Th[i]->name,NULL,
			 lngth,width,21,1,-1,width-2,-1);
		   i++;
		 }

	 }
	 return Th;
}
void  EditThumbnailsbrowser1init(DIY *X,void *pt) {
 // One may setup browser list here by setting X->list
 // if it need to be freed set it as X->pt also
   int n,i=0;
   void **ptmp = (void **)pt;
   int *pint= (int *)ptmp[0];
   void **List = (void **)ptmp[1];
   void *tpt;
   ThumbNail *Th;
   Nitems = *pint;
   Y = X;
   kgSetList(X,List);
   Glist = Dopen();
   i=0;
   while (List[i] != NULL){
	   Th = (ThumbNail *) List[i];
	   Th->img = kgStringToImage(Th->name,NULL,X->xgap+X->lngth,X->width,21,1,-1,X->width-2,-1);
	   Dadd(Glist,List[i++]);
   }
   n = Dcount(Glist);
   Garry = (void **)malloc(sizeof(void *)*(n+1));
   Resetlink(Glist);
   i=0;
   while((tpt=Getrecord(Glist))!= NULL) Garry[i++]=tpt;
   Garry[i]=NULL;
   Dfree(Glist);
}
int  EditThumbnailsbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  D = (DIALOG *)Tmp;
  Dtmp = D;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  switch(butno) {
    case 1: 
      DeleteSelection(Y);
      kgUpdateOn(Tmp);
      break;
    case 2: 
      AddItem(Y);
      break;
    case 3: 
      break;
  }
  return ret;
}
void  EditThumbnailsbutton1init(DIN *B,void *pt) {
}
int  EditThumbnailssplbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1,j; 
  ThumbNail **Th= (ThumbNail **)kgGetList(Y);
  ThumbNail **Thret=NULL;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  void **ptmp= (void **)pt;
  int *nitems = (int *)ptmp[0];
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  j=0;
  while(Th[j]!=NULL) j++;
  if(j!= *nitems) {
    ret = kgWarnMenu(Parent,100,100,(char *)"Items Not Matching !!!!!! (But you may..)",0);
  }
  if(ret) {
    Thret = (ThumbNail **)malloc(sizeof(ThumbNail *)*(j+1));
    j=0;
    while(Th[j]!=NULL) {Thret[j]=Th[j];j++;}
    Thret[j]=NULL;
    Th[0]=NULL;
    kgSetList(Y,(void **)Th);
    ptmp[1]=(void *)Thret;
  }
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  EditThumbnailssplbutton1init(DIL *B,void *pt) {
}
int EditThumbnailsinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  void **ptmp = (void **)pt;
  int *nitems= (int *)ptmp[0];
  M = (DIM *)kgGetNamedWidget(Tmp,(char *)"ItemsMsg");
  sprintf(Buf,"Expectiong !w43%d!w34 items",*nitems);
  kgWrite(M,Buf);
  Buf[0]='\0';
  return ret;
}
int EditThumbnailscleanup(void *Tmp) {
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
int ModifyEditThumbnails(void *Tmp,int GrpId) {
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

int EditThumbnailsCallBack(void *Tmp,void *tmp) {
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
int EditThumbnailsResizeCallBack(void *Tmp) {
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
int EditThumbnailsWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  void *pt= (void *)kgGetArgPointer(Tmp); // Change as required
  return ret;
}
