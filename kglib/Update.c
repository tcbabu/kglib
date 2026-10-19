
static void *Args=NULL,*Rets=NULL;

static DIAINTR *It = NULL;


static MODINTERFACE ModFuns[] = { 
    (MODINTERFACE) NULL 
};
static Dlink *ModuleList=NULL;
void *RunkgFB(void *,void *);
char * kgGetFolderName ( char *flname );

static int ResetFBxboxes(void *Tmp) {
  char filter[200],folder[300];
  int ln;
  DIT *T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox2");
  strcpy(folder,kgGetString(T,0));
  ln = strlen(folder);
  if(ln > 1){if (folder[ln-1]=='/')  folder[ln-1]='\0';};  
//  printf("Folder= %s\n",folder);
  T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox1");
  strcpy(filter,kgGetString(T,1));
  DIX *X = (DIX *)kgGetNamedWidget(Tmp,(char *)"Xbox1");
  kgFreeThumbNails((ThumbNail **)kgGetList(X));
  char **menu = kgFolderMenu(folder);
  if(menu != NULL) {
     kgSetList(X,(void **)kgStringToThumbNails(menu));
     kgFreeDouble((void **)menu);
  }
  else kgSetList(X,NULL);
  kgUpdateWidget(X);   
  X = (DIX *)kgGetNamedWidget(Tmp,(char *)"Xbox2");
  kgFreeThumbNails((ThumbNail **)kgGetList(X));
  menu = kgFileMenu(folder,filter);
  if(menu != NULL) {
     kgSetList(X,(void **)kgStringToThumbNails(menu));
     kgFreeDouble((void **)menu);
  }
  else kgSetList(X,NULL);
  kgUpdateWidget(X);   
  kgUpdateOn(Tmp);
}
 /* Callback for  Txbox1   */ 

int kgFBTxbox1callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  ResetFBxboxes(Tmp);
  return ret;
}

 /* Callback for  Xbox1   */ 

int kgFBXbox1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIX *X; 
  int ret=1,ln; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  X = (DIX *)kgGetWidget(Tmp,i);
  char folder[300];
  DIT *T= (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox2");
  strcpy(folder,kgGetString(T,0));
  ln = strlen(folder);
  if(folder[ln-1] != '/') strcat(folder,(char *)"/");
  strcat(folder,(char *) kgGetSelectedString(X));
  strcat(folder,(char *) "/");
//  printf("Selection: %s\n",folder);
  kgSetString(T,0,folder);
  kgUpdateWidget(T);
  ResetFBxboxes(Tmp);
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
void  kgFBXbox1init (DIX *X,void *ptmp) {
 // One may setup browser list here by setting X->list
 // if it need to be freed set it as X->pt also
 void **pt=(void **)ptmp; //pt[0] is arg 
}

 /* Callback for  Xbox2   */ 

int kgFBXbox2callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIX *X; 
  int ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  X = (DIX *)kgGetWidget(Tmp,i);
  DIT *T= (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox1");
  char flname[300];
  strcat(flname,(char *) kgGetSelectedString(X));
  kgSetString(T,0,flname);
  kgUpdateWidget(T);
  kgUpdateOn(Tmp);
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
void  kgFBXbox2init (DIX *X,void *ptmp) {
 // One may setup browser list here by setting X->list
 // if it need to be freed set it as X->pt also
 void **pt=(void **)ptmp; //pt[0] is arg 
}

 /* Callback for  Button1   */ 

int kgFBButton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  switch(butno) {
    case 1: //  Update 
      break;
  }
  return ret;
}
void  kgFBButton1init (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}

 /* Callback for  Splbutn1   */ 

int kgFBSplbutn1callback( int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  void **args= (void **)(pt[0]);
  char *fl = (char *)args[2];
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  char flname[300];
  switch(butno) {
    case 1: //  !c15Cancel 
     pt[1]= NULL;
      break;
    case 2: //  !c15Okay 
      DIT *T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox2");
      strcpy(flname,kgGetString(T,0));
      int ln = strlen(flname);
      if(flname[ln-1]!= '/') strcat(flname,(char *)"/");
      T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox1");
      strcat(flname,kgGetString(T,0));
      strcpy(fl,flname);
      pt[1]=fl;
      break;
  }
  return ret;
}
void  kgFBSplbutn1init (DIL *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}

 /* Callback for  Button2   */ 

int kgFBButton2callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0,k; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  char folder[300];
  DIT *T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox2");
  strcpy(folder,kgGetString(T,0));
          k = strlen ( folder ) ;
          if( (k>1)&& (folder[k-1]=='/')) {
             k--;
             folder[k]='\0';
          }
          k--;
          while ( ( folder[ k ] != '/' ) && ( k > 0 ) ) \
              {folder [ k ] = '\0';k--;}
          kgSetString(T,0,folder);
          kgUpdateWidget(T);
          ResetFBxboxes(Tmp);
  switch(butno) {
    case 1: //   
      break;
  }
  return ret;
}
void  kgFBButton2init (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
 kgChangeButtonNormalImage(B,0,kgUpdirImage(30,130,140,130));
}

 /* Callback for  Button3   */ 

int kgFBButton3callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  DIT *T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox2");
  kgSetString(T,0,getenv("PWD"));
  kgUpdateWidget(T);
  ResetFBxboxes(Tmp);
  switch(butno) {
    case 1: //   
      break;
  }
  return ret;
}
void  kgFBButton3init (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
 kgChangeButtonNormalImage(B,0,kgHomeImage(30,130,140,130));
}
int kgFBSetup(void *Tmp,void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  /* you add any initialisation here */
  /* useful for setting is used as MakeGroup */
  return 1;
}
 
void * kgFBCleanDia(void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  
/* you add any cleaning  here */

  return NULL;
}
 
 
void *  kgFBAction(void *Tmp,void *Args) {
  return NULL;
} 
 
 
int   kgFBOn(void *itmp) {
  DIAINTR * Dt = (DIAINTR *) itmp;
  if(Dt == NULL ) Dt = (DIAINTR *)It;
  if(Dt != NULL) {
    if(Dt->Dtmp != NULL)kgSetGrpVisibility(Dt->Dtmp,Dt->GrpId,1);
    else return 0;
    return 1;
  } 
  return 0;
} 
 
int   kgFBOff(void *itmp) {
  DIAINTR * Dt = (DIAINTR *) itmp;
  if(Dt == NULL ) Dt = (DIAINTR *)It;
  if(Dt != NULL) {
    if(Dt->Dtmp != NULL)kgSetGrpVisibility(Dt->Dtmp,Dt->GrpId,0);
    else return 0;
    return 1;
  } 
  return 0;
} 
 
static char *GetPointer(char *str) { 
  char *pt; 
  pt = (char *)malloc(strlen(str)+1); 
  strcpy(pt,str); 
  return pt; 
} 
 
 
void * kgFBInterface(void *args,void *rets) {
  /*********************************** 
   ***********************************/ 
  DIAINTR *it= (DIAINTR *)malloc(sizeof(DIAINTR));
  it->GrpId=0;
  // filled by MakeGroup  it->xsh=0;
  it->ysh=0;
  it->RunDia = RunkgFB;
  it->MakeGroup = MakekgFBGroup;
  it->Title = GetPointer((char *)"kgFB");
  it->Help = GetPointer( (char *)"No help yet, request");
  it->Action = kgFBAction;
  it->Settings = kgFBSetup;
  it->Cleanup  = kgFBCleanDia;
  if(args != NULL) Args=args;
  if(rets != NULL) Rets=rets;
  it->args = Args;
  it->rets = Rets;
  it->SwitchOn = kgFBOn;
  it->SwitchOff = kgFBOff;
  it->Dtmp = NULL; // fiiled by MakeGroup 
  It = it;
  return it;
}
 
 
int kgFBTxbox2callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  ResetFBxboxes(Tmp);
  return ret;
}
int kgFBButton4callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  switch(butno) {
    case 1: //  Go 
      break;
  }
  return ret;
}
void  kgFBButton4init (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgFBGocallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  ResetFBxboxes(Tmp);
  switch(butno) {
    case 1: //  Go 
      break;
  }
  return ret;
}
void  kgFBGoinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgFBRefreshcallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  ResetFBxboxes(Tmp);
  switch(butno) {
    case 1: //  Refresh 
      break;
  }
  return ret;
}
void  kgFBRefreshinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgFBinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs, given by caller */
  void **iargs=(void **)pt[0];
  int index=0;
  char flname[300];
  char filter[200];
  char folder[300];
  strcpy(flname,(char *)iargs[2]);
  strcpy(filter,(char *)iargs[3]);
  char *fpt = kgGetFolderName(flname);
  if(fpt == NULL) strcpy(folder,getenv("PWD"));
  else {
    index=strlen(fpt);
    strcpy(folder,fpt);
    free(fpt);
  }
  DIT *T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox2");
  kgSetString(T,0,folder);
  kgUpdateWidget(T);
  T = (DIT *)kgGetNamedWidget(Tmp,(char *)"Txbox1");
  DII *I = (DII *)kgGetNamedWidget(Tmp,(char *)"Info");
  kgSetString(T,0,flname+index);
  kgSetString(T,1,filter);
  kgUpdateWidget(T);
  kgWrite(I,folder);
  ResetFBxboxes(Tmp);
  kgUpdateOn(Tmp);
  return ret;
}
int kgFBcleanup(void *Tmp) {
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
int ModifykgFB(void *Tmp,int GrpId) {
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs given by caller */
  int *ipt;
  void **iargs;
  iargs = (void **)(pt[0]);
  DIA *d;
  int i,n;
  kgCheckParentPosition(Tmp);
  d = D->d;

  if( ModuleList == NULL) ModuleList = kgGetModuleList((void **)ModFuns);
  i=0;
  void *args=NULL;
  DIAINTR *Dt;
  Resetlink(ModuleList);
  while ( (Dt=(DIAINTR *)Getrecord(ModuleList)) != NULL) {
    Dt->GrpId = Dt->MakeGroup(Tmp,NULL);
    kgShiftGrp(Tmp,Dt->GrpId,Dt->xsh,Dt->ysh);
    Dt->Settings(Tmp,args);
    i++;
  };

  i=0;while(d[i].t!= NULL) {;
     i++;
  };
  n=1;
//  strcpy(D->name,"Kulina Designer ver 3.0");    /*  Dialog name you may change */
  ipt = (int *)iargs[0];
  D->xo = *ipt;
  ipt = (int *)iargs[1];
  D->yo = *ipt;
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

int kgFBCallBack(void *Tmp,void *tmp) {
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
int kgFBResizeCallBack(void *Tmp) {
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
int kgFBWaitCallBack(void *Tmp) {
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
void ModifykgFBGc(void *Tmp) {
   DIALOG *D;
   Gclr *gc;
   D = (DIALOG *)Tmp;
   gc = &(D->gc);
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   kgColorTheme(D,220,220,200);
   kgColorTheme1(D,220,220,200);
   kgColorTheme2(D,220,220,200);
   kgDefaultGuiTheme(gc);
   kgGrayGuiTheme(gc);
   gc->FontSize =9;
   gc->GuiFontSize =9;
   gc->InputFontSize =8;
   gc->MenuFont = 21;
   gc->PromptFont = 21;
   gc->ButtonFont = 21;
   gc->MsgFont = 21;
   gc->Font=23;
   kgMkgclr((char *)"kgFB",Tmp);
*/
}
int kgFBGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*2);
  e0[0].fmt = (char *)malloc(15);
  strcpy(e0[0].fmt,(char *)"File Name:%30s");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[0].noecho=0;
  e0[0].img=NULL;
  e0[1].fmt = (char *)malloc(15);
  strcpy(e0[1].fmt,(char *)"Filter   :%30s");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[1].noecho=0;
  e0[1].img=NULL;
  DIT t0 = { 
    't',
    20,18,  
    426,84,
    24, 
    1,2, 
    e0,
    1,1,
    NULL,kgFBTxbox1callback ,0 ,0,5,9 
  };
    /* *args,Callback,border,hide,font,fontsize */
  strcpy(t0.Wid,(char *)"Txbox1");
  t0.pt=NULL;
  t0.type = 1;
  t0.Font = -1;
  t0.FontSize = 9;
  t0.item = -1;
  DII i1 = { 
    'i',
    91,94,  
    472,121,  
    41,1,1   
  };
  strcpy(i1.Wid,(char *)"Info");
  i1.item = -1;
  DIX x2 = { 
    'x',
    17,124,  
    267,366,   
    10,2,  
    208, 
    18, 
    1,103396080, 
    0,11, 
    (int *)v[2], 
    NULL, 
    NULL, 
    NULL,kgFBXbox1callback , /* *args, Callback  */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     2,  /* Type  */
     1, /* item highlight */
    0, /* bordr */
    1, /* bkgr */
    0  /*=1 hide  */
   };
  strcpy(x2.Wid,(char *)"Xbox1");
  x2.item = -1;
  DIX x3 = { 
    'x',
    268,124,  
    518,366,   
    10,2,  
    208, 
    18, 
    1,103396080, 
    0,11, 
    (int *)v[3], 
    NULL, 
    NULL, 
    NULL,kgFBXbox2callback , /* *args, Callback  */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     2,  /* Type  */
     1, /* item highlight */
    0, /* bordr */
    1, /* bkgr */
    0  /*=1 hide  */
   };
  strcpy(x3.Wid,(char *)"Xbox2");
  x3.item = -1;
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"Refresh");
  butn4[0].xpmn=NULL;
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-216226216;
  butn4[0].butncode=31;
  DIN b4 = { 
    'n',
    426,55,  
    500,89,
    2,2,  
    64, 
    24, 
    1,1, 
    2,0.500000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn4, 
    kgFBRefreshcallback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b4.Wid,(char *)"Refresh");
  b4.item = -1;
  BUT_STR  *butn5=NULL; 
  butn5= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn5[0].sw=1;
  strcpy(butn5[0].title,(char *)"!c03Cancel");
  butn5[0].xpmn=NULL;
  butn5[0].xpmp=NULL;
  butn5[0].xpmh=NULL;
  butn5[0].bkgr=-216226216;
  butn5[0].butncode=34942;
  butn5[1].sw=1;
  strcpy(butn5[1].title,(char *)"!c38Okay");
  butn5[1].xpmn=NULL;
  butn5[1].xpmp=NULL;
  butn5[1].xpmh=NULL;
  butn5[1].bkgr=-216226216;
  butn5[1].butncode=30991486;
  DIL h5 = { 
    'h',
    181,368,  
    350,397,
    10,0,  
    72, 
    24, 
    2,1, 
    7,0.500000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn5, 
    kgFBSplbutn1callback ,  /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(h5.Wid,(char *)"Splbutn1");
  h5.item = -1;
  BUT_STR  *butn6=NULL; 
  butn6= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn6[0].sw=1;
  strcpy(butn6[0].title,(char *)"");
  butn6[0].xpmn=NULL;
  butn6[0].xpmp=NULL;
  butn6[0].xpmh=NULL;
  butn6[0].bkgr=-1;
  butn6[0].butncode=31;
  DIN b6 = { 
    'n',
    57,88,  
    92,123,
    2,2,  
    30, 
    30, 
    1,1, 
    8,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn6, 
    kgFBButton2callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b6.Wid,(char *)"Button2");
  b6.item = -1;
  BUT_STR  *butn7=NULL; 
  butn7= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn7[0].sw=1;
  strcpy(butn7[0].title,(char *)"");
  butn7[0].xpmn=NULL;
  butn7[0].xpmp=NULL;
  butn7[0].xpmh=NULL;
  butn7[0].bkgr=-1;
  butn7[0].butncode=126;
  DIN b7 = { 
    'n',
    20,88,  
    57,123,
    2,2,  
    30, 
    30, 
    1,1, 
    8,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn7, 
    kgFBButton3callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b7.Wid,(char *)"Button3");
  b7.item = -1;
  T_ELMT *e8  ; 
  e8 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e8[0].fmt = (char *)malloc(11);
  strcpy(e8[0].fmt,(char *)"Folder%26s");
  e8[0].v=(void *)v[4];
  e8[0].sw=1;
  e8[0].noecho=0;
  e8[0].img=NULL;
  DIT t8 = { 
    't',
    90,89,  
    431,119,
    24, 
    1,1, 
    e8,
    1,1,
    NULL,kgFBTxbox2callback ,0 ,0,5,9 
  };
    /* *args,Callback,border,hide,font,fontsize */
  strcpy(t8.Wid,(char *)"Txbox2");
  t8.pt=NULL;
  t8.type = 1;
  t8.Font = -1;
  t8.FontSize = 9;
  t8.item = -1;
  BUT_STR  *butn9=NULL; 
  butn9= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn9[0].sw=1;
  strcpy(butn9[0].title,(char *)"Go");
  butn9[0].xpmn=NULL;
  butn9[0].xpmp=NULL;
  butn9[0].xpmh=NULL;
  butn9[0].bkgr=-216226216;
  butn9[0].butncode=12688766;
  DIN b9 = { 
    'n',
    425,88,  
    463,123,
    0,0,  
    30, 
    30, 
    1,1, 
    7,0.500000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn9, 
    kgFBGocallback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b9.Wid,(char *)"Go");
  b9.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+11));
  d =dtmp+i; 
  d[10].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DII));
  *d[1].i = i1;
  d[1].i->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIX));
  *d[2].x = x2;
  d[2].x->item = -1;
  kgFBXbox1init(d[2].x,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIX));
  *d[3].x = x3;
  d[3].x->item = -1;
  kgFBXbox2init(d[3].x,pt) ;
  d[4].t = (DIT *)malloc(sizeof(DIN));
  *d[4].N = b4;
  d[4].N->item = -1;
  kgFBRefreshinit(d[4].N,pt) ;
  d[5].t = (DIT *)malloc(sizeof(DIL));
  *d[5].h = h5;
  d[5].h->item = -1;
  kgFBSplbutn1init(d[5].h,pt) ;
  d[6].t = (DIT *)malloc(sizeof(DIN));
  *d[6].N = b6;
  d[6].N->item = -1;
  kgFBButton2init(d[6].N,pt) ;
  d[7].t = (DIT *)malloc(sizeof(DIN));
  *d[7].N = b7;
  d[7].N->item = -1;
  kgFBButton3init(d[7].N,pt) ;
  d[8].t = (DIT *)malloc(sizeof(DIT));
  *d[8].t = t8;
  d[8].t->item = -1;
  d[9].t = (DIT *)malloc(sizeof(DIN));
  *d[9].N = b9;
  d[9].N->item = -1;
  kgFBGoinit(d[9].N,pt) ;
  d[10].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakekgFBGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  2 data values
    Selectmenu1  1 data value
    Selectmenu2  1 data value
    Text_Box2  1 data values

*************************************************/
   char  *v0 ;
   v0 = (char *)malloc(sizeof(char)*500);
   v0[0] = '\0';
   char  *v1 ;
   v1 = (char *)malloc(sizeof(char)*500);
   v1[0] = '\0';
   int  *v2 ;
   v2 = (int *)malloc(sizeof(int));
   *v2 = 1;
   int  *v3 ;
   v3 = (int *)malloc(sizeof(int));
   *v3 = 1;
   char  *v4 ;
   v4 = (char *)malloc(sizeof(char)*500);
   v4[0] = '\0';
   void** v=(void **)malloc(sizeof(void*)*6);
   v[5]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(v4);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = kgFBGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   kgFBSetup(D,Gpt->arg);
   return GrpId;
}

int kgFB( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=-1685927296;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = kgFBGroup(&D,v,pt);
#else 
  GrpId = MakekgFBGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 9;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 200;   /* Position of Dialog */ 
  D.yo = 200;
  D.xl = 530;    /*  Length of Dialog */
  D.yl = 402;    /*  Width  of Dialog */
  D.Initfun = kgFBinit;    /*   init fuction for Dialog */
  D.Cleanupfun = kgFBcleanup;    /*   cleanup fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.NoTabProcess = 0;    /*  1 for disabling Tab use */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.000000;    /*  float 1.0 for full transparency */
  D.Newwin = 1;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = kgFBCallBack;    /*  default Callback  */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = kgFBResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = kgFBWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 0;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.NoWinMngr = 0;    /*  1 for no Window Manager*/
  D.StackPos = 1;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 3.0");    /*  Dialog name you may change */
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
  ModifykgFBGc(&D);    /*  set colors for gui if do not like default*/
  ModifykgFB(&D,GrpId);    /*  add extras to  gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *RunkgFB(void *parent ,void *args) {
/*************************************************

    Text_Box1  2 data values
    Selectmenu1  1 data value
    Selectmenu2  1 data value
    Text_Box2  1 data values

*************************************************/
   char  v0[500]="" ;
   char  v1[500]="" ;
   int   v2 = 1;
   int   v3 = 1;
   char  v4[500]="" ;
   void* v[5];
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(&v3);
   v[4]=(void *)(v4);
   void *pt[2]={NULL,NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   pt[0]=args;
   kgFB(parent,v,(void *)pt );
   return pt[1];
}
int kgFolderBrowser(void *Tmp,int xo,int yo,char *flname,char *filter) {
    char *pt[5];
    void *res;
    pt[4]=NULL;
    pt[0]= (void *)malloc(sizeof(int));
    *((int *)pt[0])=xo;
    pt[1]= (void *)malloc(sizeof(int));
    *((int *)pt[1])=yo;
    pt[2]=flname;
    pt[3]= filter;
    res =RunkgFB(Tmp,pt);
    if(res == NULL) return 0;
    strcpy(flname,res);
    free(pt[0]);
    free(pt[1]);
    return 1;
}
