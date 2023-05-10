#include <kulina.h>
extern DIALOG *Parent;
int  messagedatatextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  messagedatahoribar1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DILN *B; 
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  B = (DILN *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(butno) {
    case 1: 
      break;
    case 2: 
      break;
  }
  return ret;
}
void  messagedatahbutton1init(DILN *H,void *pt) {
}
int  messagedatabrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret=1; 
#if 0
  DIRA *R;DIALOG *D;void **pt; 
  ThumbNail **th; 
  int *justification;
  D = (DIALOG *)Tmp;
  pt = (void **)D->pt;
  justification = (int *)pt[0];
  R = (DIRA *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) R->list;
  if(th[0]->sw==1) *justification=-1;
  if(th[1]->sw==1) *justification=0;
  if(th[2]->sw==1) *justification=1;
#endif
  return ret;
}
void  messagedatabrowser1init(DIRA *R,void *pt) {
#if 0
  ThumbNail **th; 
  int *justification;
  void **ptrs;
  ptrs = (void **)pt;
  th = (ThumbNail **) R->list;
  justification = (int *)ptrs[0];
  th[0]->sw=0;
  th[1]->sw=0;
  th[2]->sw=0;
  th[*justification+1]->sw=1;
#endif
}
int  messagedatabrowser2callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DICH *C;DIALOG *D;void **pt; 
  int *hide;
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  pt = (void **)D->pt;
  hide = (int *) pt[1];
  C = (DICH *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) C->list;
  *hide=th[0]->sw;
  return ret;
}
void  messagedatabrowser2init(DICH *C,void *pt) {
  int *hide;
  ThumbNail **th; 
  void **ptrs;
  ptrs = (void **)pt;
  hide = (int *) ptrs[1];
  th = (ThumbNail **) C->list;
  th[0]->sw=*hide;
}
int messagedatainit(void *Tmp) {
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
int messagedatacleanup(void *Tmp) {
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
int messagedataCallBack(void *Tmp,void *tmp) {
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
int messagedataResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
int messagedataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*4);
  for(j=0;j<4;j++) e0[j].noecho =0;
  e0[0].fmt = (char *)malloc(10);
  strcpy(e0[0].fmt,(char *)"Length%4d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(9);
  strcpy(e0[1].fmt,(char *)"Width%4d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[2].fmt = (char *)malloc(17);
  strcpy(e0[2].fmt,(char *)"Initail Text%30s");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  e0[3].fmt = (char *)malloc(16);
  strcpy(e0[3].fmt,(char *)"Widget Name%25s");
  e0[3].v=(void *)v[3];
  e0[3].sw=1;
  DIT t0 = { 
    't',
    21,33,  
    452,157,
    20, 
    1,4, 
    e0,
    1,1,
    NULL,messagedatatextbox1callback,0,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"messagedataWidget1");
  t0.pt=NULL;
  char **titles1=NULL; 
  titles1= (char **)malloc(sizeof(char *)*2);
  titles1[0]= (char *)malloc(7);
  strcpy(titles1[0],(char *)"Cancel");
  titles1[1]= (char *)malloc(5);
  strcpy(titles1[1],(char *)"Okay");
  int *sw1=NULL  ; 
  sw1 =(int *)malloc(sizeof(int)*2) ; 
  sw1[0]= 1; 
  sw1[1]= 1; 
  char **xpms1  = NULL; 
  xpms1  = (char **)malloc(sizeof(char *)*6); 
  xpms1[0]=   NULL; /* pixmap info */ 
  xpms1[1]=   NULL; /* pixmap info */ 
  xpms1[2]=   NULL; /* pixmap info */ 
  xpms1[3]=   NULL; /* pixmap info */ 
  xpms1[4]=   NULL; /* pixmap info */ 
  xpms1[5]=   NULL; /* pixmap info */ 
  int *bkgr1 =NULL; 
  bkgr1 =(int *)malloc(sizeof(int)*2) ; 
  bkgr1[0]=  -147000000; 
  bkgr1[1]=  -147000; 
  char *butncode1  = NULL;
  DILN H1 = { 
    'H',
    148,277,  
    324,310,
    0,0,
    80, 
    25, 
    2,1, 
    NULL, 
    sw1,
    titles1,
    butncode1,
    NULL,messagedatahoribar1callback,/* arg, Callbak */
    (void **)xpms1,bkgr1, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H1.bval = 1; 
  strcpy(H1.Wid,(char *)"messagedataWidget2");
  DIM m2 = { 
    'm',
    39,173,  
    139,197,  
    1,0  
  };
  strncpy(m2.msg,(char *)"Text Justification",499);
  strcpy(m2.Wid,(char *)"messagedataWidget4");
  char *menu3[]  = { 
    (char *)"left",
    (char *)"centre",
    (char *)"right",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r3 = { 
    'r',
    144,169,  
    440,200,   
    54,0,  
    40, 
    25, 
    1,3, 
    -1118482,1, 
    (int *)v[4], 
    NULL, 
    NULL ,
    NULL,messagedatabrowser1callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu3);
  r3.list=(void **)th0;
  strcpy(r3.Wid,(char *)"messagedataWidget5");
  char *menu4[]  = { 
    (char *)"Hide Widget",
    NULL 
  };
  ThumbNail **th1 ;
  DICH c4 = { 
    'c',
    137,213,  
    288,250,   
    0,0,  
    90, 
    25, 
    1,1, 
    0,1, 
    (int *)v[5], 
    NULL, 
    NULL, 
    NULL,messagedatabrowser2callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu4);
  c4.list=(void **)th1;
  strcpy(c4.Wid,(char *)"messagedataWidget8");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+6));
  d =dtmp+i; 
  d[5].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DILN));
  messagedatahbutton1init(&H1,pt) ;
  *d[1].H = H1;
  d[1].H->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIM));
  *d[2].m = m2;
  d[2].m->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIRA));
  messagedatabrowser1init(&r3,pt) ;
  *d[3].r = r3;
  d[3].r->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DICH));
  messagedatabrowser2init(&c4,pt) ;
  *d[4].c = c4;
  d[4].c->item = -1;
  d[5].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 


int messagedata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = messagedataGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 4;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 200;   /* Position of Dialog */ 
  D.yo = 100;
  D.xl = 469;    /*  Length of Dialog */
  D.yl = 321;    /*  Width  of Dialog */
  D.Initfun = messagedatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = messagedatacleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.000000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = messagedataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = messagedataResizeCallBack;  /*  Resize callback */
  D.WaitCallback = NULL;
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = Parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 1.0");    /*  Dialog name you may change */
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
  }    /*  end of fullscreen mode */
//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/
//  ModifymessagedataGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
int Runmessagedata(void *arg) {
/*************************************************

    Text_Box1  4 data values
    RadioButtons1  1 data value
    CheckBox2  1 data value

*************************************************/
   DIM *M;
   int ret;
   void *pt[2];
   int   v0 = 1;
   int   v1 = 1;
   char  v2[100]=" " ;
   char  v3[100]=" " ;
   int   v4 = 1;
   int   v5 = 1;
   int justification,hide;
   void* v[6];
   M = (DIM *)arg;
   justification =M->justification;
   hide = M->hide;
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(&v4);
   v[5]=(void *)(&v5);
   v0 = M->x2-M->x1;
   v1 = M->y2-M->y1;
   strcpy(v2,M->msg);
   strcpy(v3,M->Wid);
   pt[0]=&justification;
   pt[1]=&hide;
   v4 = justification+2;
   ret = messagedata(NULL,v,pt );
   if(ret ) {
//     M->justification=justification;
     M->justification=v4-2;
     M->hide = hide;
     strcpy(M->Wid,v3);
     strcpy(M->msg,v2);
     M->x2 = M->x1+v0;
     M->y2 = M->y1+v1;
   }
   return ret;
}
