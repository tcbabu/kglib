#include <kulina.h>
extern DIALOG *Dia;
int  Optionsbrowser1callback(int item,int i,void *Tmp) {
  DIRA *R;DIALOG *D;void *pt; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  pt = D->pt;
  R = (DIRA *)kgGetWidget(Tmp,i);
  return ret;
}
void  Optionshbutton1init(DILN *H,void *pt) {
}

void  Optionsbrowser1init(DIRA *R,void *pt) {
  char **menu=NULL;int *sw=NULL;void **xpm; 
}
int  Optionsbrowser2callback(int item,int i,void *Tmp) {
  DICH *C;DIALOG *D;void *pt; 
  DIT *T;
  DIM *M;
  ThumbNail **th1;
  int ret=1,Resize; 
  D = (DIALOG *)Tmp;
  pt = D->pt;
  C = (DICH *)kgGetWidget(Tmp,i);
  th1 = (ThumbNail**)C->list;
  Resize = Dia->Resize;
  Dia->Sticky = th1[0]->sw;
  Dia->Fixpos = th1[1]->sw;
  Dia->Deco = th1[2]->sw;
  Dia->fullscreen = th1[3]->sw;
  Dia->kbattn = th1[4]->sw;
  Dia->butattn = th1[5]->sw;
  Dia->Newwin = th1[6]->sw;
  Dia->DrawBkgr = th1[7]->sw;
  Dia->NoTaskBar = (th1[8]->sw+1)%2;
  Dia->Resize = (th1[9]->sw);
  if(Resize != Dia->Resize) {
     T = (DIT *)kgGetWidget(D,6);
     M = (DIM *)kgGetWidget(D,7);
     if(Dia->Resize==1) {
       T->hide=0;
       M->hide=0;
     }
     else {
       T->hide=1;
       M->hide=1;
     }
     kgUpdateWidget(T);
     kgUpdateWidget(M);
     kgUpdateOn(D);
  }
  return ret;
}
void  Optionsbrowser2init(DICH *C,void *pt) {
  ThumbNail **th1;
  th1 = (ThumbNail **)C->list;
  th1[0]->sw=Dia->Sticky;
  th1[1]->sw=Dia->Fixpos;
  th1[2]->sw=Dia->Deco;
  th1[3]->sw=Dia->fullscreen;
  th1[4]->sw=Dia->kbattn;
  th1[5]->sw=Dia->butattn;
  th1[6]->sw=Dia->Newwin;
  th1[7]->sw=Dia->DrawBkgr;
  th1[8]->sw=(Dia->NoTaskBar+1)%2;
  th1[9]->sw=(Dia->Resize);
}
int  Optionshoribar1callback(int key,int i,void *Tmp) {
  DIALOG *D;DILN *B; 
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  B = (DILN *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(key) {
    case 1: 
      break;
  }
  return ret;
}
int  Optionsfslide1callback(double val,int i,void *Tmp) {
  DIALOG *D;DIF *F; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  F = (DIF *) kgGetWidget(Tmp,i);
  return ret;
}
int  Optionstextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e;
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int OptionsResizeCallBack(void *Tmp) {
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}

int Optionsinit(void *Tmp) {
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int OptionsCallBack(void *Tmp,void *tmp) {
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
void ModifyOptionsGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
void  Optionsbrowser3init(DIRA *R,void *pt) {
  ThumbNail **th1;
  int df;
  th1 = (ThumbNail **)R->list;
  th1[0]->sw=0;
  th1[1]->sw=0;
  th1[2]->sw=0;
  df = *(R->df)-1;
  if(df< 0) df=0;
  if(df > 2) df =2;
  *(R->df) = (df+1);
  th1[df]->sw=1;
  
}

int  Optionsbrowser3callback(int item,int i,void *Tmp) {
  DIRA *R;DIALOG *D;void *pt;
  int ret=1;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  R = (DIRA *)kgGetWidget(Tmp,i);
  switch(item) {
    case 1:
      break;
  }
  return ret;
}



int Options( void *parent,void **v,void *pt) {
  int ret=1;
  DIALOG D;
  DIA *d=NULL;
  char *menu0[]  = { 
    (char *)"(null)",
    (char *)"Type1",
    (char *)"Type2",
    (char *)"Type3",
    (char *)"Type4",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r0 = { 
    'r',
    15,56,  
    405,96,   
    5,0,  
    70, 
    25, 
    1,5, 
    0,1, 
    (int *)v[0], 
    NULL, 
    NULL ,
    NULL,Optionsbrowser1callback, /* *args, callback */
    4,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    0, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu0);
  r0.list=(void **)th0;
  char *menu1[]  = { 
    (char *)"Sticky",
    (char *)"Fixed Position",
    (char *)"Decoration",
    (char *)"Full Screen",
    (char *)"Draw Keyboard Attention",
    (char *)"Draw Button Attention",
    (char *)"New Window",
    (char *)"Draw Background",
    (char *)"Taskbar Entry",
    (char *)"Allow Resize",
    NULL 
  };
  ThumbNail **th1 ;
  DICH c1 = { 
    'c',
    16,154,  
    405,301,   
    10,0,  
    170, 
    25, 
    1,10, 
    0,5, 
    (int *)v[1], 
    NULL, 
    NULL, 
    NULL,Optionsbrowser2callback, /* *args, callback */
    4,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  c1.list=(void **)th1;
  int butn1 =1;
  int sw2[1]  = { 
    1  
  };
  char *titles2[]  = { 
    (char *)"Okay", 
    NULL
  };
  void *xpm2[]  = { 
    NULL, /* pixmap info */ 
    NULL, /* pixmap info */ 
    NULL, /* pixmap info */ 
    NULL
  };
  int bkgr2[]  = { 
    -1, 
    -1
  };
  char *butncode2  = NULL;
  DILN H2 = { 
    'H',
    189,429,  
    275,460,
    4,0,
    80, 
    25, 
    1,1, 
    &butn1, 
    sw2,
    titles2,
    butncode2,
    NULL,Optionshoribar1callback,/* arg, Callbak */
    xpm2,bkgr2, /* pointers to xpms and colors */
     3,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  DIF f3 = { 
    'f',
    210,361,  
    360,407,   
    0.000000,1.000000,  
    100,  
    (double *)v[2],
    (char *)"" ,
    NULL,Optionsfslide1callback /* *args, callback */
  };
  DIM m4 = { 
    'm',
    138,382,  
    210,402,  
    1,0  
  };
  strcpy(m4.msg,(char *)"Trnsparency");
  DIM m5 = { 
    'm',
    184,33,  
    255,55,  
    1,0  
  };
  strcpy(m5.msg,(char *)"Border type:");
  T_ELMT e6[2]  = { 
    {(char *)"Width%3d", v[3], 1},
    {(char *)"Height%3d", v[4], 1}
  };
  DIT t6 = { 
    't',
    151,322,  
    405,353,
    20, 
    2,1, 
    e6,
    1,1,
    NULL,Optionstextbox1callback /* args,Call back */
  };
  DIM m7 = { 
    'm',
    6,327,  
    150,348,  
    1,1  
  };
  strcpy(m7.msg,(char *)"Minimum Size for Resize");
  char *menu8[]  = { 
    (char *)"Below",
    (char *)"Normal",
    (char *)"Above",
    NULL 
  };
  ThumbNail **th2 ;
  DIRA r8 = { 
    'r',
    114,106,  
    405,143,   
    54,0,  
    35, 
    25, 
    1,3, 
    0,1, 
    (int *)v[5], 
    NULL, 
    NULL ,
    NULL,Optionsbrowser3callback, /* *args, callback */
    6,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    0, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th2 = (ThumbNail **)kgStringToThumbNails((char **)menu8);
  r8.list=(void **)th2;
  DIM m9 = { 
    'm',
    15,112,  
    115,137,  
    1,0  
  };
  strcpy(m9.msg,(char *)"Stack Position");
  kgInitUi(&D);
  d = (DIA *)malloc(sizeof(DIA )*(11));
  d[10].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIRA));
  Optionsbrowser1init(&r0,pt) ;
  *d[0].r = r0;
  d[1].t = (DIT *)malloc(sizeof(DICH));
  Optionsbrowser2init(&c1,pt) ;
  *d[1].c = c1;
  d[2].t = (DIT *)malloc(sizeof(DILN));
  Optionshbutton1init(&H2,pt) ;
  *d[2].H = H2;
  d[3].t = (DIT *)malloc(sizeof(DIF));
  *d[3].f = f3;
  d[4].t = (DIT *)malloc(sizeof(DIM));
  *d[4].m = m4;
  d[5].t = (DIT *)malloc(sizeof(DIM));
  *d[5].m = m5;
  if(Dia->Resize != 1) { t6.hide=1; m7.hide=1; }
  else {t6.hide=0;m7.hide=0;}
  d[6].t = (DIT *)malloc(sizeof(DIT));
  *d[6].t = t6;
  d[7].t = (DIT *)malloc(sizeof(DIM));
  *d[7].m = m7;
  d[8].t = (DIT *)malloc(sizeof(DIRA));
  Optionsbrowser3init(&r8,pt) ;
  *d[8].r = r8;
  d[9].t = (DIT *)malloc(sizeof(DIM));
  *d[9].m = m9;
  d[10].t = NULL;
  kgInitUi(&D);
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 8;
  D.tw = 4;
  D.bw = 18;
  D.lw = 4;
  D.rw = 4;
  D.xo = 310;   /* Position of Dialog */ 
  D.yo = 40;
  D.xl = 425;    /*  Length of Dialog */
  D.yl = 468;    /*  Width  of Dialog */
  D.Initfun = Optionsinit;    /*   init fuction for Dialog */
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
  D.MinWidth = 1336;    /*   for Resize option */
  D.MinHeight = 0;    /*   for Resize option */
#if 1 
  D.Callback = OptionsCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = OptionsResizeCallBack;  /*  Resize callback */
  D.WaitCallback = NULL;
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    
  D.pt = pt;    /*  any data to be passed by user*/
  strcpy(D.name,"Kulina Designer ver 1.0");    /*  Dialog name you may change */
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
//  ModifyOptionsGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  kgFreeDouble((void **)th0);
  kgFreeDouble((void **)th1);
  kgFreeDouble((void **)th2);
//  insert any memory frees here to avoid leak  
  return ret;
}
void *RunOptions(void *arg) {
/*************************************************

    RadioButtons1  1 data value
    CheckBox2  1 data value
    Floatslidebar1  1 data value
    Text_Box1  2 data values

*************************************************/
   int   v0 = 1;
   int   v1 = 1;
   double v2 = 0.0;
   int   v3 = 1;
   int   v4 = 1;
   int   v5 = 1;
   void* v[6];
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v2 = Dia->transparency;
   v0= Dia->bor_type+1;
   v3= Dia->MinWidth;
   v4= Dia->MinHeight;
   v5= Dia->StackPos+2;
   void *pt=NULL; /* pointer to send any extra information */
   v[3]=(void *)(&v3);
   v[4]=(void *)(&v4);
   v[5]=(void *)(&v5);
   Options(arg,v,pt );
   Dia->transparency=v2;
   Dia->bor_type=v0-1;
   Dia->MinWidth=v3;
   Dia->MinHeight=v4;
   Dia->StackPos=v5-2;
   return NULL;
}
