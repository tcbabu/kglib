#include <kulina.h>
extern DIALOG *Parent;
int  buttondatatextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  buttondatabrowser1callback(int item,int i,void *Tmp) {
  DICH *C;DIALOG *D;void *pt; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  pt = D->pt;
  C = (DICH *)kgGetWidget(Tmp,i);
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
void  buttondatabrowser1init(DICH *C,void *pt) {
}
int  buttondatabrowser2callback(int item,int i,void *Tmp) {
  DIN *B;
  DIALOG *D;DIX *X;void *pt; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  B = (DIN *)D->pt;
  B->type = item-1;
  X = (DIX *)kgGetWidget(Tmp,i);
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
int  hbuttondatabrowser2callback(int item,int i,void *Tmp) {
  DIL *B;
  DIALOG *D;DIX *X;void *pt; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  B = (DIL *)D->pt;
  B->type = item-1;
  X = (DIX *)kgGetWidget(Tmp,i);
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
void  buttondatabrowser2init(DIX *X,void *pt) {
  char *titles[]={(char *)"Type0",(char *)"Type1",(char *)"Type2",
                  (char *)"Type3",(char *)"Type4",(char *)"Type5",(char *)"Type6",
                  (char *)"Type7",(char *)"Type8",(char *)"Type9",(char *)"Type10",NULL};
  int df;
  DIN *B;
  ThumbNail **th;
  B = (DIN *)pt;
  th = kgStringToThumbNails(titles);
  X->list = (void **)th;
  X->pt= (void **)th;
  df = B->type;
  th[df]->sw =1;
}
void  hbuttondatabrowser2init(DIX *X,void *pt) {
  char *titles[]={(char *)"Type0",(char *)"Type1",(char *)"Type2",
                  (char *)"Type3",(char *)"Type4",(char *)"Type5",(char *)"Type6",
                  (char *)"Type7",(char *)"Type8",(char *)"Type9",(char *)"Type10",NULL};
  int df;
  DILN *B;
  ThumbNail **th;
  B = (DILN *)pt;
  th = kgStringToThumbNails(titles);
  X->list = (void **)th;
  X->pt= (void **)th;
  df = B->type;
  th[df]->sw =1;
}
int  buttondatahoribar1callback(int key,int i,void *Tmp) {
  DIALOG *D;DILN *B; 
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  B = (DILN *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(key) {
    case 1: 
      break;
    case 2: 
      break;
  }
  return ret;
}
void  buttondatahbutton1init(DILN *H,void *pt) {
}
int buttondatainit(void *Tmp) {
  /* you add any initialisation here */
  int ret = 1;
  ThumbNail **th;
  DICH *C;
  DIN *B;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  B = (DIN *)D->pt;
  C = (DICH *)kgGetNamedWidget(D,(char *)"buttondataWidget5");
  th = (ThumbNail **)C->list;
  th[0]->sw=B->hide;
  th[1]->sw=B->bordr;
  if(B->nodrawbkgr != 1) B->nodrawbkgr=0;
  th[2]->sw=(B->nodrawbkgr+1)%2;
  kgUpdateWidget(C);
  kgUpdateOn(D);
  return ret;
}
int hbuttondatainit(void *Tmp) {
  /* you add any initialisation here */
  int ret = 1;
  ThumbNail **th;
  DICH *C;
  DIL *B;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  B = (DIL *)D->pt;
  C = (DICH *)kgGetNamedWidget(D,(char *)"buttondataWidget5");
  th = (ThumbNail **)C->list;
  th[0]->sw=B->hide;
  th[1]->sw=B->bordr;
  return ret;
}
int buttondatacleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  int ret = 1;
  ThumbNail **th;
  DICH *C;
  DIN *B;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  B = (DIN *)D->pt;
  C = (DICH *)kgGetNamedWidget(D,(char *)"buttondataWidget5");
  th = (ThumbNail **)C->list;
  B->hide=th[0]->sw;
  B->bordr=th[1]->sw;
  B->nodrawbkgr= (th[2]->sw+1)%2;
  return ret;
}
int hbuttondatacleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  int ret = 1;
  ThumbNail **th;
  DICH *C;
  DIL *B;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  B = (DIL *)D->pt;
  C = (DICH *)kgGetNamedWidget(D,(char *)"buttondataWidget5");
  th = (ThumbNail **)C->list;
  B->hide=th[0]->sw;
  B->bordr=th[1]->sw;
  return ret;
}
int buttondataCallBack(void *Tmp,void *tmp) {
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
int buttondataResizeCallBack(void *Tmp) {
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
int buttondataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*8);
  for(j=0;j<8;j++) e0[j].noecho=0;
  e0[0].fmt = (char *)malloc(10);
  strcpy(e0[0].fmt,(char *)"Length%3d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(9);
  strcpy(e0[1].fmt,(char *)"Width%3d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[2].fmt = (char *)malloc(6);
  strcpy(e0[2].fmt,(char *)"Nx%3d");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  e0[3].fmt = (char *)malloc(6);
  strcpy(e0[3].fmt,(char *)"Ny%3d");
  e0[3].v=(void *)v[3];
  e0[3].sw=1;
  e0[4].fmt = (char *)malloc(8);
  strcpy(e0[4].fmt,(char *)"Xgap%3d");
  e0[4].v=(void *)v[4];
  e0[4].sw=1;
  e0[5].fmt = (char *)malloc(8);
  strcpy(e0[5].fmt,(char *)"Ygap%3d");
  e0[5].v=(void *)v[5];
  e0[5].sw=1;
  e0[6].fmt = (char *)malloc(18);
  strcpy(e0[6].fmt,(char *)"Rounding Fac.%10F");
  e0[6].v=(void *)v[6];
  e0[6].sw=1;
  e0[7].fmt = (char *)malloc(9);
  strcpy(e0[7].fmt,(char *)"Name%20s");
  e0[7].v=(void *)v[7];
  e0[7].sw=1;
  DIT t0 = { 
    't',
    9,20,  
    355,264,
    20, 
    1,8, 
    e0,
    1,1,
    NULL,buttondatatextbox1callback,0,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"buttondataWidget2");
  t0.pt=NULL;
  DIM m1 = { 
    'm',
    356,20,  
    460,44,  
    1,0  
  };
  strncpy(m1.msg,(char *)"Button Type",499);
  strcpy(m1.Wid,(char *)"buttondataWidget4");
  char *menu2[]  = { 
    (char *)"Hide",
    (char *)"Border",
    (char *)"Clean Background",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c2 = { 
    'c',
    370,167,  
    520,256,   
    0,0,  
    90, 
    25, 
    1,2, 
    -1052689,2, 
    (int *)v[8], 
    NULL, 
    NULL, 
    NULL,buttondatabrowser1callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu2);
  c2.list=(void **)th0;
  strcpy(c2.Wid,(char *)"buttondataWidget5");
  DIX x3 = { 
    'x',
    370,44,  
    520,164,   
    10,2,  
    108, 
    25, 
    1,2, 
    0,4, 
    (int *)v[9], 
    NULL, 
    NULL, 
    NULL,buttondatabrowser2callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     1,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(x3.Wid,(char *)"buttondataWidget6");
  char **titles4=NULL; 
  titles4= (char **)malloc(sizeof(char *)*2);
  titles4[0]= (char *)malloc(7);
  strcpy(titles4[0],(char *)"Cancel");
  titles4[1]= (char *)malloc(5);
  strcpy(titles4[1],(char *)"Okay");
  int *sw4=NULL  ; 
  sw4 =(int *)malloc(sizeof(int)*2) ; 
  sw4[0]= 1; 
  sw4[1]= 1; 
  char **xpms4  = NULL; 
  xpms4  = (char **)malloc(sizeof(char *)*6); 
  xpms4[0]=   NULL; /* pixmap info */ 
  xpms4[1]=   NULL; /* pixmap info */ 
  xpms4[2]=   NULL; /* pixmap info */ 
  xpms4[3]=   NULL; /* pixmap info */ 
  xpms4[4]=   NULL; /* pixmap info */ 
  xpms4[5]=   NULL; /* pixmap info */ 
  int *bkgr4 =NULL; 
  bkgr4 =(int *)malloc(sizeof(int)*2) ; 
  bkgr4[0]=  -177000000; 
  bkgr4[1]=  -147000; 
  char *butncode4  = NULL;
  DILN H4 = { 
    'H',
    172,275,  
    348,308,
    0,0,
    80, 
    25, 
    2,1, 
    NULL, 
    sw4,
    titles4,
    butncode4,
    NULL,buttondatahoribar1callback,/* arg, Callbak */
    (void **)xpms4,bkgr4, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H4.bval = 1; 
  strcpy(H4.Wid,(char *)"buttondataWidget7");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+6));
  d =dtmp+i; 
  d[5].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIM));
  *d[1].m = m1;
  d[1].m->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DICH));
  buttondatabrowser1init(&c2,pt) ;
  *d[2].c = c2;
  d[2].c->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIX));
  buttondatabrowser2init(&x3,pt) ;
  *d[3].x = x3;
  d[3].x->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DILN));
  buttondatahbutton1init(&H4,pt) ;
  *d[4].H = H4;
  d[4].H->item = -1;
  d[5].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */


int buttondata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = buttondataGroup(&D,v,pt);
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
  D.xl = 533;    /*  Length of Dialog */
  D.yl = 314;    /*  Width  of Dialog */
  D.Initfun = buttondatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = buttondatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = buttondataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = buttondataResizeCallBack;  /*  Resize callback */
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
//  ModifybuttondataGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
int hbuttondataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*6);
  for(j=0;j<6;j++) e0[j].noecho=0;
  e0[0].fmt = (char *)malloc(10);
  strcpy(e0[0].fmt,(char *)"Length%3d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(9);
  strcpy(e0[1].fmt,(char *)"Width%3d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[2].fmt = (char *)malloc(6);
  strcpy(e0[2].fmt,(char *)"Nx%3d");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  e0[3].fmt = (char *)malloc(8);
  strcpy(e0[3].fmt,(char *)"Xgap%3d");
  e0[3].v=(void *)v[3];
  e0[3].sw=1;
  e0[4].fmt = (char *)malloc(18);
  strcpy(e0[4].fmt,(char *)"Rounding Fac.%10F");
  e0[4].v=(void *)v[4];
  e0[4].sw=1;
  e0[5].fmt = (char *)malloc(9);
  strcpy(e0[5].fmt,(char *)"Name%20s");
  e0[5].v=(void *)v[5];
  e0[5].sw=1;
  DIT t0 = { 
    't',
    9,55,  
    353,240,
    20, 
    1,6, 
    e0,
    1,1,
    NULL,buttondatatextbox1callback,0,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"buttondataWidget2");
  t0.pt=NULL;
  DIM m1 = { 
    'm',
    356,20,  
    460,44,  
    1,0  
  };
  strncpy(m1.msg,(char *)"Button Type",499);
  strcpy(m1.Wid,(char *)"buttondataWidget4");
  char *menu2[]  = { 
    (char *)"Hide",
    (char *)"Border",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c2 = { 
    'c',
    373,187,  
    520,266,   
    0,0,  
    90, 
    25, 
    1,2, 
    -1,2, 
    (int *)v[6], 
    NULL, 
    NULL, 
    NULL,buttondatabrowser1callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu2);
  c2.list=(void **)th0;
  strcpy(c2.Wid,(char *)"buttondataWidget5");
  DIX x3 = { 
    'x',
    370,44,  
    520,164,   
    10,2,  
    108, 
    25, 
    1,2, 
    0,4, 
    (int *)v[7], 
    NULL, 
    NULL, 
    NULL,hbuttondatabrowser2callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     1,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(x3.Wid,(char *)"buttondataWidget6");
  char **titles4=NULL; 
  titles4= (char **)malloc(sizeof(char *)*2);
  titles4[0]= (char *)malloc(7);
  strcpy(titles4[0],(char *)"Cancel");
  titles4[1]= (char *)malloc(5);
  strcpy(titles4[1],(char *)"Okay");
  int *sw4=NULL  ; 
  sw4 =(int *)malloc(sizeof(int)*2) ; 
  sw4[0]= 1; 
  sw4[1]= 1; 
  char **xpms4  = NULL; 
  xpms4  = (char **)malloc(sizeof(char *)*6); 
  xpms4[0]=   NULL; /* pixmap info */ 
  xpms4[1]=   NULL; /* pixmap info */ 
  xpms4[2]=   NULL; /* pixmap info */ 
  xpms4[3]=   NULL; /* pixmap info */ 
  xpms4[4]=   NULL; /* pixmap info */ 
  xpms4[5]=   NULL; /* pixmap info */ 
  int *bkgr4 =NULL; 
  bkgr4 =(int *)malloc(sizeof(int)*2) ; 
  bkgr4[0]=  -177000000; 
  bkgr4[1]=  -147000; 
  char *butncode4  = NULL;
  DILN H4 = { 
    'H',
    172,275,  
    348,308,
    0,0,
    80, 
    25, 
    2,1, 
    NULL, 
    sw4,
    titles4,
    butncode4,
    NULL,buttondatahoribar1callback,/* arg, Callbak */
    (void **)xpms4,bkgr4, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H4.bval = 1; 
  strcpy(H4.Wid,(char *)"buttondataWidget7");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+6));
  d =dtmp+i; 
  d[5].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIM));
  *d[1].m = m1;
  d[1].m->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DICH));
  buttondatabrowser1init(&c2,pt) ;
  *d[2].c = c2;
  d[2].c->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIX));
  hbuttondatabrowser2init(&x3,pt) ;
  *d[3].x = x3;
  d[3].x->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DILN));
  buttondatahbutton1init(&H4,pt) ;
  *d[4].H = H4;
  d[4].H->item = -1;
  d[5].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakehbuttondataGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  6 data values
    CheckBox1  1 data value
    Selectmenu2  1 data value

*************************************************/
   int  *v0 ;
   v0 = (int *)malloc(sizeof(int));
   *v0 = 1;
   int  *v1 ;
   v1 = (int *)malloc(sizeof(int));
   *v1 = 1;
   int  *v2 ;
   v2 = (int *)malloc(sizeof(int));
   *v2 = 1;
   int  *v3 ;
   v3 = (int *)malloc(sizeof(int));
   *v3 = 1;
   double *v4 ;
   v4 = (double *)malloc(sizeof(double));
   *v4 = 0.0;
   char  *v5 ;
   v5 = (char *)malloc(sizeof(100));
   v5[0] = '\0';
   int  *v6 ;
   v6 = (int *)malloc(sizeof(int));
   *v6 = 1;
   int  *v7 ;
   v7 = (int *)malloc(sizeof(int));
   *v7 = 1;
   void** v=(void **)malloc(sizeof(void*)*8);
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(v4);
   v[5]=(void *)(v5);
   v[6]=(void *)(v6);
   v[7]=(void *)(v7);
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = hbuttondataGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int hbuttondata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = hbuttondataGroup(&D,v,pt);
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
  D.xl = 533;    /*  Length of Dialog */
  D.yl = 314;    /*  Width  of Dialog */
  D.Initfun = hbuttondatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = hbuttondatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = buttondataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = buttondataResizeCallBack;  /*  Resize callback */
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
//  ModifybuttondataGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
int Runbuttondata(void *arg) {
/*************************************************

    Text_Box1  8 data values
    CheckBox1  1 data value
    Selectmenu2  1 data value

*************************************************/
  DIN *B;
   int ret=1;
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   int   v4 = 1;
   int   v5 = 1;
   double v6 = 0.0;
   char  v7[100]=" " ;
   int   v8 = 1;
   int   v9 = 1;
   void* v[10];
   B = (DIN *)arg;
   v9= B->type+1;
   v[0]=(void *)(&B->lngth);
   v[1]=(void *)(&B->width);
   v[2]=(void *)(&B->nx);
   v[3]=(void *)(&B->ny);
   v[4]=(void *)(&B->xgap);
   v[5]=(void *)(&B->ygap);
   v[6]=(void *)(&v6);
   v6 = B->fac;
   v[7]=(void *)(B->Wid);
   v[8]=(void *)(&v8);
   v[9]=(void *)(&v9);
   void *pt=arg; /* pointer to send any extra information */
   ret=buttondata(NULL,v,pt );
   B->fac = v6;
   return ret;
}
int Runhbuttondata(void *arg) {
/*************************************************

    Text_Box1  8 data values
    CheckBox1  1 data value
    Selectmenu2  1 data value

*************************************************/
  DIL* B;
   int ret=1;
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   double v4 = 0.0;
   char  v5[100]=" " ;
   int   v6 = 1;
   int   v7 = 1;
   void* v[8];
   B = (DIL *)arg;
   v7 = B->type+1;
   v[0]=(void *)(&B->lngth);
   v[1]=(void *)(&B->width);
   v[2]=(void *)(&B->nx);
   v[3]=(void *)(&B->xgap);
   v[4]=(void *)(&v4);
   v4 = B->fac;
   v[5]=(void *)(B->Wid);
   v[6]=(void *)(&v6);
   v[7]=(void *)(&v7);
   void *pt=arg; /* pointer to send any extra information */
   ret=hbuttondata(NULL,v,pt );
   B->fac = v4;
   return ret;
}
int buttoneditGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*6);
  for(j=0;j<6;j++) e0[j].noecho=0;
  e0[0].fmt = (char *)malloc(10);
  strcpy(e0[0].fmt,(char *)"Length%3d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(9);
  strcpy(e0[1].fmt,(char *)"Width%3d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[2].fmt = (char *)malloc(8);
  strcpy(e0[2].fmt,(char *)"Xgap%3d");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  e0[3].fmt = (char *)malloc(8);
  strcpy(e0[3].fmt,(char *)"Ygap%3d");
  e0[3].v=(void *)v[3];
  e0[3].sw=1;
  e0[4].fmt = (char *)malloc(18);
  strcpy(e0[4].fmt,(char *)"Rounding Fac.%10F");
  e0[4].v=(void *)v[4];
  e0[4].sw=1;
  e0[5].fmt = (char *)malloc(9);
  strcpy(e0[5].fmt,(char *)"Name%20s");
  e0[5].v=(void *)v[5];
  e0[5].sw=1;
  DIT t0 = { 
    't',
    9,55,  
    353,240,
    20, 
    1,6, 
    e0,
    1,1,
    NULL,buttondatatextbox1callback,0,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"buttondataWidget2");
  t0.pt=NULL;
  DIM m1 = { 
    'm',
    356,20,  
    460,44,  
    1,0  
  };
  strncpy(m1.msg,(char *)"Button Type",499);
  strcpy(m1.Wid,(char *)"buttondataWidget4");
  char *menu2[]  = { 
    (char *)"Hide",
    (char *)"Border",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c2 = { 
    'c',
    373,187,  
    520,266,   
    0,0,  
    90, 
    25, 
    1,2, 
    0,2, 
    (int *)v[6], 
    NULL, 
    NULL, 
    NULL,buttondatabrowser1callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu2);
  c2.list=(void **)th0;
  strcpy(c2.Wid,(char *)"buttondataWidget5");
  DIX x3 = { 
    'x',
    370,44,  
    520,164,   
    10,2,  
    108, 
    25, 
    1,2, 
    0,4, 
    (int *)v[7], 
    NULL, 
    NULL, 
    NULL,buttondatabrowser2callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     1,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(x3.Wid,(char *)"buttondataWidget6");
  char **titles4=NULL; 
  titles4= (char **)malloc(sizeof(char *)*2);
  titles4[0]= (char *)malloc(7);
  strcpy(titles4[0],(char *)"Cancel");
  titles4[1]= (char *)malloc(5);
  strcpy(titles4[1],(char *)"Okay");
  int *sw4=NULL  ; 
  sw4 =(int *)malloc(sizeof(int)*2) ; 
  sw4[0]= 1; 
  sw4[1]= 1; 
  char **xpms4  = NULL; 
  xpms4  = (char **)malloc(sizeof(char *)*6); 
  xpms4[0]=   NULL; /* pixmap info */ 
  xpms4[1]=   NULL; /* pixmap info */ 
  xpms4[2]=   NULL; /* pixmap info */ 
  xpms4[3]=   NULL; /* pixmap info */ 
  xpms4[4]=   NULL; /* pixmap info */ 
  xpms4[5]=   NULL; /* pixmap info */ 
  int *bkgr4 =NULL; 
  bkgr4 =(int *)malloc(sizeof(int)*2) ; 
  bkgr4[0]=  -177000000; 
  bkgr4[1]=  -147000; 
  char *butncode4  = NULL;
  DILN H4 = { 
    'H',
    172,275,  
    348,308,
    0,0,
    80, 
    25, 
    2,1, 
    NULL, 
    sw4,
    titles4,
    butncode4,
    NULL,buttondatahoribar1callback,/* arg, Callbak */
    (void **)xpms4,bkgr4, /* pointers to xpms and colors */
     2,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H4.bval = 1; 
  strcpy(H4.Wid,(char *)"buttondataWidget7");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+6));
  d =dtmp+i; 
  d[5].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIM));
  *d[1].m = m1;
  d[1].m->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DICH));
  buttondatabrowser1init(&c2,pt) ;
  *d[2].c = c2;
  d[2].c->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIX));
  buttondatabrowser2init(&x3,pt) ;
  *d[3].x = x3;
  d[3].x->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DILN));
  buttondatahbutton1init(&H4,pt) ;
  *d[4].H = H4;
  d[4].H->item = -1;
  d[5].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */


int buttonedit( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = buttondataGroup(&D,v,pt);
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
  D.xl = 533;    /*  Length of Dialog */
  D.yl = 314;    /*  Width  of Dialog */
  D.Initfun = buttondatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = buttondatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = buttondataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = buttondataResizeCallBack;  /*  Resize callback */
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
//  ModifybuttondataGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
int Runbuttonedit(void *arg) {
/*************************************************

    Text_Box1  6 data values
    CheckBox1  1 data value
    Selectmenu2  1 data value

*************************************************/
   DIN* B;
   int ret=1;
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   double v4 = 0.0;
   char  v5[100]=" " ;
   int   v6 = 1;
   int   v7 = 1;
   int   hide,type,bordr;
   void* v[8];
   B = (DIN *)arg;
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(&v3);
   v[4]=(void *)(&v4);
   v[5]=(void *)(v5);
   v[6]=(void *)(&v6);
   v[7]=(void *)(&v7);
   v0= B->lngth;
   v1= B->width;
   v2= B->xgap;
   v3= B->ygap;
   v4 = B->fac;
   hide = B->hide;
   type = B->type;
   bordr = B->bordr;
   strcpy(v5,B->Wid);
   void *pt=arg; /* pointer to send any extra information */
   ret = buttonedit(NULL,v,pt );
   if(ret ) {
     B->lngth = v0;
     B->width = v1;
     B->xgap =  v2;
     B->ygap =  v3;
     B->fac = v4;
     strcpy(B->Wid,v5);
   }
   else { B->hide=hide;B->bordr=bordr; B->type=type;}
   return ret;
}
int Runhbuttonedit(void *arg) {
/*************************************************

    Text_Box1  6 data values
    CheckBox1  1 data value
    Selectmenu2  1 data value

*************************************************/
   DIL* B;
   int ret=1;
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   double v4 = 0.0;
   char  v5[100]=" " ;
   int   v6 = 1;
   int   v7 = 1;
   int   hide,type,bordr;
   void* v[8];
   B = (DIL *)arg;
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(&v3);
   v[4]=(void *)(&v4);
   v[5]=(void *)(v5);
   v[6]=(void *)(&v6);
   v[7]=(void *)(&v7);
   v0= B->lngth;
   v1= B->width;
   v2= B->xgap;
   v3= B->ygap;
   v4 = B->fac;
   hide = B->hide;
   type = B->type;
   bordr = B->bordr;
   strcpy(v5,B->Wid);
   void *pt=arg; /* pointer to send any extra information */
   ret = buttonedit(NULL,v,pt );
   if(ret ) {
     B->lngth = v0;
     B->width = v1;
     B->xgap =  v2;
     B->ygap =  v3;
     B->fac = v4;
     strcpy(B->Wid,v5);
   }
   else { B->hide=hide;B->bordr=bordr; B->type=type;}
   return ret;
}
