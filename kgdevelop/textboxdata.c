
#include <kulina.h>
extern DIALOG *Parent;
int  textboxdatatextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  textboxdatabrowser1callback(int item,int i,void *Tmp) {
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
  return ret;
}
void  textboxdatabrowser1init(DIRA *R,void *pt) {
}
int  textboxdatahoribar1callback(int butno,int i,void *Tmp) {
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
  }
  return ret;
}
void  textboxdatahbutton1init(DILN *H,void *pt) {
}
int  textboxdatasplbutton1callback(int butno,int i,void *Tmp) {
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
void  textboxdatasplbutton1init(DIL *B,void *pt) {
}
int textboxdatainit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  DIM *M;
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  M = (DIM *) kgGetNamedWidget(Tmp,(char *)"textboxdataWidget5");
  strcpy(M->msg,(char *)pt);
  kgUpdateWidget(M);
  kgUpdateOn(Tmp);
  return ret;
}
int textboxdatacleanup(void *Tmp) {
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
int textboxdataCallBack(void *Tmp,void *tmp) {
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
int textboxdataResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
int textboxdataGroup_exp( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*2);
  for(j=0;j<2;j++) e0[j].noecho =0;
  for(j=0;j<2;j++) e0[j].img=NULL;
  e0[0].fmt = (char *)malloc(18);
  strcpy(e0[0].fmt,(char *)"Prompt String%20s");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(21);
  strcpy(e0[1].fmt,(char *)"Data Field Length%4d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  DIT t0 = { 
    't',
    9,43,  
    398,111,
    20, 
    1,2, 
    e0,
    1,1,
    NULL,textboxdatatextbox1callback,0,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"textboxdataWidget1");
  t0.pt=NULL;
  char *menu1[]  = { 
    (char *)"Integer",
    (char *)"Double",
    (char *)"String",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r1 = { 
    'r',
    83,123,  
    399,155,   
    63,0,  
    40, 
    25, 
    1,3, 
    -1077952577,1, 
    (int *)v[2], 
    NULL, 
    NULL ,
    NULL,textboxdatabrowser1callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  r1.list=(void **)th0;
  strcpy(r1.Wid,(char *)"textboxdataWidget3");
  DIM m2 = { 
    'm',
    11,125,  
    84,149,  
    1,0  
  };
  strncpy(m2.msg,(char *)"Data Type",499);
  strcpy(m2.Wid,(char *)"textboxdataWidget4");
  char **titles3=NULL; 
  titles3= (char **)malloc(sizeof(char *)*1);
  titles3[0]= (char *)malloc(5);
  strcpy(titles3[0],(char *)"Okay");
  int *sw3=NULL  ; 
  sw3 =(int *)malloc(sizeof(int)*1) ; 
  sw3[0]= 1; 
  char **xpms3  = NULL; 
  xpms3  = (char **)malloc(sizeof(char *)*3); 
  xpms3[0]=   NULL; /* pixmap info */ 
  xpms3[1]=   NULL; /* pixmap info */ 
  xpms3[2]=   NULL; /* pixmap info */ 
  int *bkgr3 =NULL; 
  bkgr3 =(int *)malloc(sizeof(int)*1) ; 
  bkgr3[0]=  -147000; 
  char *butncode3  = NULL;
  DILN H3 = { 
    'H',
    171,168,  
    259,201,
    0,0,
    80, 
    25, 
    1,1, 
    NULL, 
    sw3,
    titles3,
    butncode3,
    NULL,textboxdatahoribar1callback,/* arg, Callbak */
    (void **)xpms3,bkgr3, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H3.bval = 1; 
  strcpy(H3.Wid,(char *)"textboxdataWidget4");
  DIM m4 = { 
    'B',
    5,6,  
    408,29,  
    0,0  
  };
  strncpy(m4.msg,(char *)"",499);
  strcpy(m4.Wid,(char *)"textboxdataWidget5");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+6));
  d =dtmp+i; 
  d[5].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIRA));
  textboxdatabrowser1init(&r1,pt) ;
  *d[1].r = r1;
  d[1].r->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIM));
  *d[2].m = m2;
  d[2].m->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DILN));
  textboxdatahbutton1init(&H3,pt) ;
  *d[3].H = H3;
  d[3].H->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIM));
  *d[4].m = m4;
  d[4].m->item = -1;
  d[5].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

void ModifytextboxdataGc(void *Tmp) {
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
   gc->FontSize =8;
   gc->Font=23;
   kgMkgclr("textboxdata",Tmp);
*/
}
int textboxdataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*2);
  e0[0].fmt = (char *)malloc(26);
  strcpy(e0[0].fmt,(char *)"!w32!f21Prompt String%20s");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[0].noecho=0;
  e0[0].img=NULL;
  e0[1].fmt = (char *)malloc(29);
  strcpy(e0[1].fmt,(char *)"!w32!f21Data Field Length%4d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[1].noecho=0;
  e0[1].img=NULL;
  DIT t0 = { 
    't',
    31,41,  
    418,105,
    20, 
    1,2, 
    e0,
    1,1,
    NULL,textboxdatatextbox1callback,0,0,18,9 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"textboxdataWidget2");
  t0.pt=NULL;
  t0.type = 0;
  t0.item = -1;
  char *menu1[]  = { 
    (char *)"!w32!f21Integer",
    (char *)"!w32!f21Double",
    (char *)"!w32!f21String",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r1 = { 
    'r',
    112,114,  
    472,149,   
    8,0,  
    100, 
    25, 
    1,3, 
    1,1, 
    (int *)v[2], 
    NULL, 
    NULL ,
    NULL,textboxdatabrowser1callback, /* *args, callback */
    1,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  r1.list=(void **)th0;
  strcpy(r1.Wid,(char *)"textboxdataWidget3");
  r1.item = -1;
  DIM m2 = { 
    'm',
    9,119,  
    109,143,  
    1,0  
  };
  strncpy(m2.msg,(char *)"!w32!f21Data Type",499);
  strcpy(m2.Wid,(char *)"textboxdataWidget4");
  m2.item = -1;
  BUT_STR  *butn3=NULL; 
  butn3= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn3[0].sw=1;
  strcpy(butn3[0].title,(char *)"!w32!f23Okay");
  butn3[0].xpmn=NULL;
  butn3[0].xpmp=NULL;
  butn3[0].xpmh=NULL;
  butn3[0].bkgr=-235255250;
  butn3[0].butncode='';
  DIL h3 = { 
    'h',
    200,187,  
    282,220,
    2,0,  
    72, 
    25, 
    1,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn3, 
    textboxdatasplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h3.Wid,(char *)"textboxdataWidget5");
  h3.item = -1;
  DIM m4 = { 
    'm',
    81,160,  
    409,183,  
    0,0  
  };
  strncpy(m4.msg,(char *)"",499);
  strcpy(m4.Wid,(char *)"textboxdataWidget6");
  m4.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+6));
  d =dtmp+i; 
  d[5].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIRA));
  *d[1].r = r1;
  d[1].r->item = -1;
  textboxdatabrowser1init(d[1].r,pt) ;
  d[2].t = (DIT *)malloc(sizeof(DIM));
  *d[2].m = m2;
  d[2].m->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIL));
  *d[3].h = h3;
  d[3].h->item = -1;
  textboxdatasplbutton1init(d[3].h,pt) ;
  d[4].t = (DIT *)malloc(sizeof(DIM));
  *d[4].m = m4;
  d[4].m->item = -1;
  d[5].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

int textboxdata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = textboxdataGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 3;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 222;   /* Position of Dialog */ 
  D.yo = 120;
  D.xl = 414;    /*  Length of Dialog */
  D.yl = 208;    /*  Width  of Dialog */
  D.Initfun = textboxdatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = textboxdatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = textboxdataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = textboxdataResizeCallBack;  /*  Resize callback */
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
//  ModifytextboxdataGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
void *Runtextboxdata(void *arg) {
/*************************************************

    Text_Box1  2 data values
    RadioButtons1  1 data value

*************************************************/
   char *buf;
   char  v0[100]="" ;
   int   v1 = 10;
   int   v2 = 1;
   void* v[3];
   v[0]=(void *)(v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   void *pt=arg; /* pointer to send any extra information */
   textboxdata(NULL,v,pt );
   buf = (char *)malloc(200);
   switch(v2) {
     case 1:
       sprintf(buf,"%-s%%%-dd",v0,v1);
       break;
     case 2:
       sprintf(buf,"%-s%%%-dF",v0,v1);
       break;
     case 3:
       sprintf(buf,"%-s%%%-ds",v0,v1);
       break;
   }
   return buf;
}
int  textboxesdatatextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  textboxesdatabrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DICH *C;DIALOG *D;void *pt; 
  int **ptrs;
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  ptrs = (int **)D->pt;
  C = (DICH *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) C->list;
  *ptrs[0]=th[1]->sw;
  *ptrs[1]=th[0]->sw;
  return ret;
}
void  textboxesdatabrowser1init(DICH *C,void *pt) {
  int **ptrs;
  ThumbNail **th;
  ptrs = (int **)pt;
  th = (ThumbNail **)C->list;
  th[0]->sw = *ptrs[1];
  th[1]->sw = *ptrs[0];
}
int  textboxesdatahoribar1callback(int butno,int i,void *Tmp) {
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
void  textboxesdatahbutton1init(DILN *H,void *pt) {
}
int textboxesdatainit(void *Tmp) {
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
int textboxesdatacleanup(void *Tmp) {
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
int textboxesdataCallBack(void *Tmp,void *tmp) {
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
int textboxesdataResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
int textboxesdataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*3);
  for(j=0;j<3;j++) e0[j].noecho =0;
  for(j=0;j<3;j++) e0[j].img=NULL;
  e0[0].fmt = (char *)malloc(21);
  strcpy(e0[0].fmt,(char *)"Boxes X Dirextion%4d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(24);
  strcpy(e0[1].fmt,(char *)"Boxes in Y Direction%4d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[2].fmt = (char *)malloc(16);
  strcpy(e0[2].fmt,(char *)"Widget Name%25s");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  DIT t0 = { 
    't',
    9,20,  
    464,111,
    20, 
    1,3, 
    e0,
    1,1,
    NULL,textboxesdatatextbox1callback,1,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"textboxesdataWidget1");
  t0.pt=NULL;
  char *menu1[]  = { 
    (char *)"Draw Border",
    (char *)"Hide Widget",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c1 = { 
    'c',
    127,125,  
    344,163,   
    0,0,  
    100, 
    25, 
    1,2, 
    -16711159,1, 
    (int *)v[3], 
    NULL, 
    NULL, 
    NULL,textboxesdatabrowser1callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  c1.list=(void **)th0;
  strcpy(c1.Wid,(char *)"textboxesdataWidget2");
  char **titles2=NULL; 
  titles2= (char **)malloc(sizeof(char *)*2);
  titles2[0]= (char *)malloc(7);
  strcpy(titles2[0],(char *)"Cancel");
  titles2[1]= (char *)malloc(5);
  strcpy(titles2[1],(char *)"Okay");
  int *sw2=NULL  ; 
  sw2 =(int *)malloc(sizeof(int)*2) ; 
  sw2[0]= 1; 
  sw2[1]= 1; 
  char **xpms2  = NULL; 
  xpms2  = (char **)malloc(sizeof(char *)*6); 
  xpms2[0]=   NULL; /* pixmap info */ 
  xpms2[1]=   NULL; /* pixmap info */ 
  xpms2[2]=   NULL; /* pixmap info */ 
  xpms2[3]=   NULL; /* pixmap info */ 
  xpms2[4]=   NULL; /* pixmap info */ 
  xpms2[5]=   NULL; /* pixmap info */ 
  int *bkgr2 =NULL; 
  bkgr2 =(int *)malloc(sizeof(int)*2) ; 
  bkgr2[0]=  -147000000; 
  bkgr2[1]=  -118000; 
  char *butncode2  = NULL;
  DILN H2 = { 
    'H',
    149,181,  
    325,214,
    0,0,
    80, 
    25, 
    2,1, 
    NULL, 
    sw2,
    titles2,
    butncode2,
    NULL,textboxesdatahoribar1callback,/* arg, Callbak */
    (void **)xpms2,bkgr2, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H2.bval = 1; 
  strcpy(H2.Wid,(char *)"textboxesdataWidget4");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+4));
  d =dtmp+i; 
  d[3].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DICH));
  textboxesdatabrowser1init(&c1,pt) ;
  *d[1].c = c1;
  d[1].c->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DILN));
  textboxesdatahbutton1init(&H2,pt) ;
  *d[2].H = H2;
  d[2].H->item = -1;
  d[3].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 


int textboxesdata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = textboxesdataGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 2;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 289;   /* Position of Dialog */ 
  D.yo = 141;
  D.xl = 472;    /*  Length of Dialog */
  D.yl = 219;    /*  Width  of Dialog */
  D.Initfun = textboxesdatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = textboxesdatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = textboxesdataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = textboxesdataResizeCallBack;  /*  Resize callback */
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
//  ModifytextboxesdataGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
int Runtextboxesdata(void *arg) {
/*************************************************

    Text_Box1  3 data values
    CheckBox1  1 data value

*************************************************/
   int ret;
   int   v0 = 1;
   int   v1 = 1;
   char  v2[100]=" " ;
   int   v3 = 1;
   void* v[4];
   void *pt[2];
   DIT *t;
   int hide,bordr;
   t = (DIT *) arg;
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(&v3);
   hide = t->hide;
   bordr =t->bordr;
   v0 = t->nx;
   v1 = t->ny;
   strcpy(v2,t->Wid);
   pt[0]=&hide;
   pt[1]=&bordr;
   ret = textboxesdata(NULL,v,pt );
   if(ret) {
     t->nx = v0;
     t->ny = v1;
     strcpy(t->Wid,v2);
     t->hide = hide;
     t->bordr = bordr;
   }
   return ret;
}
int  tableboxesdatatextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  tableboxesdatabrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DICH *C;DIALOG *D;void *pt; 
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  pt = D->pt;
  C = (DICH *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) C->list;
  return ret;
}
void  tableboxesdatabrowser1init(DICH *C,void *pt) {
}
int  tableboxesdatahoribar1callback(int butno,int i,void *Tmp) {
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
void  tableboxesdatahbutton1init(DILN *H,void *pt) {
}
int tableboxesdatainit(void *Tmp) {
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
int tableboxesdatacleanup(void *Tmp) {
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
int tableboxesdataCallBack(void *Tmp,void *tmp) {
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
int tableboxesdataResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
int tableboxesdataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*3);
  for(j=0;j<3;j++) e0[j].noecho =0;
  for(j=0;j<3;j++) e0[j].img=NULL;
  e0[0].fmt = (char *)malloc(18);
  strcpy(e0[0].fmt,(char *)"No. of Columns%4d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(15);
  strcpy(e0[1].fmt,(char *)"No. of Rows%4d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[2].fmt = (char *)malloc(16);
  strcpy(e0[2].fmt,(char *)"Widget Name%25s");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  DIT t0 = { 
    't',
    9,20,  
    464,111,
    20, 
    1,3, 
    e0,
    1,1,
    NULL,tableboxesdatatextbox1callback,1,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"tableboxesdataWidget1");
  t0.pt=NULL;
  char *menu1[]  = { 
    (char *)"Draw Border",
    (char *)"Hide Widget",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c1 = { 
    'c',
    127,125,  
    344,163,   
    0,0,  
    100, 
    25, 
    1,2, 
    -1077952577,1, 
    (int *)v[3], 
    NULL, 
    NULL, 
    NULL,textboxesdatabrowser1callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  c1.list=(void **)th0;
  strcpy(c1.Wid,(char *)"tableboxesdataWidget2");
  char **titles2=NULL; 
  titles2= (char **)malloc(sizeof(char *)*2);
  titles2[0]= (char *)malloc(7);
  strcpy(titles2[0],(char *)"Cancel");
  titles2[1]= (char *)malloc(5);
  strcpy(titles2[1],(char *)"Okay");
  int *sw2=NULL  ; 
  sw2 =(int *)malloc(sizeof(int)*2) ; 
  sw2[0]= 1; 
  sw2[1]= 1; 
  char **xpms2  = NULL; 
  xpms2  = (char **)malloc(sizeof(char *)*6); 
  xpms2[0]=   NULL; /* pixmap info */ 
  xpms2[1]=   NULL; /* pixmap info */ 
  xpms2[2]=   NULL; /* pixmap info */ 
  xpms2[3]=   NULL; /* pixmap info */ 
  xpms2[4]=   NULL; /* pixmap info */ 
  xpms2[5]=   NULL; /* pixmap info */ 
  int *bkgr2 =NULL; 
  bkgr2 =(int *)malloc(sizeof(int)*2) ; 
  bkgr2[0]=  -147000000; 
  bkgr2[1]=  -118000; 
  char *butncode2  = NULL;
  DILN H2 = { 
    'H',
    149,181,  
    325,214,
    0,0,
    80, 
    25, 
    2,1, 
    NULL, 
    sw2,
    titles2,
    butncode2,
    NULL,tableboxesdatahoribar1callback,/* arg, Callbak */
    (void **)xpms2,bkgr2, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H2.bval = 1; 
  strcpy(H2.Wid,(char *)"tableboxesdataWidget4");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+4));
  d =dtmp+i; 
  d[3].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DICH));
  textboxesdatabrowser1init(&c1,pt) ;
  *d[1].c = c1;
  d[1].c->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DILN));
  tableboxesdatahbutton1init(&H2,pt) ;
  *d[2].H = H2;
  d[2].H->item = -1;
  d[3].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 


int tableboxesdata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = tableboxesdataGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 2;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 289;   /* Position of Dialog */ 
  D.yo = 141;
  D.xl = 472;    /*  Length of Dialog */
  D.yl = 219;    /*  Width  of Dialog */
  D.Initfun = tableboxesdatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = tableboxesdatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = tableboxesdataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = tableboxesdataResizeCallBack;  /*  Resize callback */
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
//  ModifytableboxesdataGc(&(D.gc));    /*  set colors for gui*/
  Print_gui_data(&D,(char *)"tableboxesdata.rc");
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
int Runtableboxesdata(void *arg) {
/*************************************************

    Text_Box1  3 data values
    CheckBox1  1 data value

*************************************************/
   int ret;
   int   v0 = 1;
   int   v1 = 1;
   char  v2[100]=" " ;
   int   v3 = 1;
   void* v[4];
   void *pt[2];
   DIT *t;
   int hide,bordr;
   t = (DIT *) arg;
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(&v3);
   hide = t->hide;
   bordr =t->bordr;
   v0 = t->nx;
   v1 = t->ny;
   strcpy(v2,t->Wid);
   pt[0]=&hide;
   pt[1]=&bordr;
   ret = tableboxesdata(NULL,v,pt );
   if(ret) {
     t->nx = v0;
     t->ny = v1;
     strcpy(t->Wid,v2);
     t->hide = hide;
     t->bordr = bordr;
   }
   return ret;
}
int  tableboxdatatextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  tableboxdatabrowser1callback(int item,int i,void *Tmp) {
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
  return ret;
}
void  tableboxdatabrowser1init(DIRA *R,void *pt) {
}
int  tableboxdatahoribar1callback(int butno,int i,void *Tmp) {
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
  }
  return ret;
}
void  tableboxdatahbutton1init(DILN *H,void *pt) {
}
int  tableboxdatabrowser2callback(int item,int i,void *Tmp) {
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
  return ret;
}
void  tableboxdatabrowser2init(DIRA *R,void *pt) {
}
int tableboxdatainit(void *Tmp) {
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
int tableboxdatacleanup(void *Tmp) {
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
int tableboxdataCallBack(void *Tmp,void *tmp) {
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
int tableboxdataResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
int tableboxdataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e0[0].fmt = (char *)malloc(21);
  strcpy(e0[0].fmt,(char *)"Data Field Length%4d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[0].noecho=0;
  e0[0].img=NULL;
  DIT t0 = { 
    't',
    4,39,  
    248,70,
    20, 
    1,1, 
    e0,
    1,1,
    NULL,tableboxdatatextbox1callback,0,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"textboxdataWidget1");
  t0.pt=NULL;
  char *menu1[]  = { 
    (char *)"Integer",
    (char *)"Double",
    (char *)"String",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r1 = { 
    'r',
    101,80,  
    406,112,   
    0,0,  
    100, 
    25, 
    1,3, 
    0,1, 
    (int *)v[1], 
    NULL, 
    NULL ,
    NULL,tableboxdatabrowser1callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  r1.list=(void **)th0;
  strcpy(r1.Wid,(char *)"textboxdataWidget3");
  DIM m2 = { 
    'm',
    25,84,  
    98,108,  
    1,0  
  };
  strncpy(m2.msg,(char *)"Data Type",499);
  strcpy(m2.Wid,(char *)"textboxdataWidget4");
  char **titles3=NULL; 
  titles3= (char **)malloc(sizeof(char *)*1);
  titles3[0]= (char *)malloc(5);
  strcpy(titles3[0],(char *)"Okay");
  int *sw3=NULL  ; 
  sw3 =(int *)malloc(sizeof(int)*1) ; 
  sw3[0]= 1; 
  char **xpms3  = NULL; 
  xpms3  = (char **)malloc(sizeof(char *)*3); 
  xpms3[0]=   NULL; /* pixmap info */ 
  xpms3[1]=   NULL; /* pixmap info */ 
  xpms3[2]=   NULL; /* pixmap info */ 
  int *bkgr3 =NULL; 
  bkgr3 =(int *)malloc(sizeof(int)*1) ; 
  bkgr3[0]=  -147000; 
  char *butncode3  = NULL;
  DILN H3 = { 
    'H',
    171,168,  
    259,201,
    0,0,
    80, 
    25, 
    1,1, 
    NULL, 
    sw3,
    titles3,
    butncode3,
    NULL,tableboxdatahoribar1callback,/* arg, Callbak */
    (void **)xpms3,bkgr3, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H3.bval = 1; 
  strcpy(H3.Wid,(char *)"textboxdataWidget4");
  DIM m4 = { 
    'B',
    5,6,  
    408,29,  
    0,0  
  };
  strncpy(m4.msg,(char *)"",499);
  strcpy(m4.Wid,(char *)"textboxdataWidget5");
  char *menu5[]  = { 
    (char *)"Input Column",
    (char *)"Output only column",
    NULL 
  };
  ThumbNail **th1 ;
  DIRA r5 = { 
    'r',
    104,118,  
    391,152,   
    0,0,  
    140, 
    25, 
    1,2, 
    -1077952577,1, 
    (int *)v[2], 
    NULL, 
    NULL ,
    NULL,tableboxdatabrowser2callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu5);
  r5.list=(void **)th1;
  strcpy(r5.Wid,(char *)"tableboxdataWidget6");
  DIM m6 = { 
    'm',
    3,122,  
    103,146,  
    1,0  
  };
  strncpy(m6.msg,(char *)"Column Switch",499);
  strcpy(m6.Wid,(char *)"tableboxdataWidget7");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+8));
  d =dtmp+i; 
  d[7].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIRA));
  tableboxdatabrowser1init(&r1,pt) ;
  *d[1].r = r1;
  d[1].r->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIM));
  *d[2].m = m2;
  d[2].m->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DILN));
  tableboxdatahbutton1init(&H3,pt) ;
  *d[3].H = H3;
  d[3].H->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIM));
  *d[4].m = m4;
  d[4].m->item = -1;
  d[5].t = (DIT *)malloc(sizeof(DIRA));
  tableboxdatabrowser2init(&r5,pt) ;
  *d[5].r = r5;
  d[5].r->item = -1;
  d[6].t = (DIT *)malloc(sizeof(DIM));
  *d[6].m = m6;
  d[6].m->item = -1;
  d[7].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

int tableboxdata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = tableboxdataGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 5;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 222;   /* Position of Dialog */ 
  D.yo = 120;
  D.xl = 414;    /*  Length of Dialog */
  D.yl = 208;    /*  Width  of Dialog */
//  D.Initfun = tableboxdatainit;    /*   init fuction for Dialog */
  D.Initfun = textboxdatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = tableboxdatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = tableboxdataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = tableboxdataResizeCallBack;  /*  Resize callback */
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
//  ModifytableboxdataGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
void *Runtableboxdata(void *arg,char *msg) {
/*************************************************

    Text_Box1  1 data values
    RadioButtons1  1 data value
    RadioButtons2  1 data value

*************************************************/
   T_ELMT *e;
   int   v0 = 10;
   int   v1 = 1;
   int   v2 = 1;
   void* v[3];
   e = (T_ELMT *)arg;
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   void *pt=NULL; /* pointer to send any extra information */
   tableboxdata(NULL,v,msg );
   switch(v1) {
     case 1:
     sprintf(e->fmt,"%%%-dd",v0);
     break;
     case 2:
     sprintf(e->fmt,"%%%-dF",v0);
     break;
     case 3:
     sprintf(e->fmt,"%%%-ds",v0);
     break;
   }
   e->sw = (v2)%2;
   e->noecho=0;
   e->img=NULL;
   return NULL;
}
