#include <kulina.h>
extern DIALOG *Parent;
int  slidebaroptbrowser1callback(int item,int i,void *Tmp) {
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
void  slidebaroptbrowser1init(DIRA *R,void *pt) {
}
int  slidebaroptsplbutton1callback(int butno,int i,void *Tmp) {
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
    case 2: 
      break;
  }
  return ret;
}
void  slidebaroptsplbutton1init(DIL *B,void *pt) {
}
int  slidebaroptbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0,clr,r,g,b; 
  DIHB *W;
  BUT_STR * buts;
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  W = (DIHB *)D->pt;
  n = B->nx*B->ny;
  buts = (BUT_STR *)B->buts;
  clr = buts[butno-1].bkgr;
  if(clr == -1 ) {
   clr = D->gc.fill_clr;
  }
  if(clr < -1 ) {
    clr = -clr;
    b = ((clr)%1000)%256;
    g = ((clr/1000)%1000)%256;
    r = ((clr/1000000)%1000)%256;
  }
  else kgGetDefaultRGB(clr,&r,&g,&b);
//  kgGetColor(Tmp,100,100,&r,&g,&b);
  kgGetColor(Parent,100,100,&r,&g,&b);
  clr = r*1000000+g*1000+b;
  clr = -clr;
//  if(clr == D->gc.fill_clr) clr=-1;
  W->sldclr = clr;
  buts[butno-1].bkgr=clr;
  kgUpdateWidget(B);
  kgUpdateOn(D);

  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  slidebaroptbutton1init(DIN *B,void *pt) {
}
int  slidebaropttextbox1callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int slidebaroptinit(void *Tmp) {
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
int slidebaroptcleanup(void *Tmp) {
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
int slidebaroptCallBack(void *Tmp,void *tmp) {
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
int slidebaroptResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
void ModifyslidebaroptGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int slidebaroptGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  char *menu0[]  = { 
    (char *)"Type0",
    (char *)"Type1",
    (char *)"Type2",
    (char *)"Type3",
    (char *)"Type4",
    (char *)"Type5",
    (char *)"Type6",
    (char *)"Type7",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r0 = { 
    'r',
    303,27,  
    409,238,   
    8,0,  
    90, 
    25, 
    1,8, 
    1,8, 
    (int *)v[0], 
    NULL, 
    NULL ,
    NULL,slidebaroptbrowser1callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu0);
  r0.list=(void **)th0;
  strcpy(r0.Wid,(char *)"slidebaroptWidget4");
  DIM m1 = { 
    'm',
    302,3,  
    353,24,  
    -1,0  
  };
  strncpy(m1.msg,(char *)"Type:",499);
  strcpy(m1.Wid,(char *)"slidebaroptWidget7");
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"Cancel");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-1;
  butn2[0].butncode='c';
  butn2[1].sw=1;
  strcpy(butn2[1].title,(char *)"Okay");
  butn2[1].xpmn=NULL;
  butn2[1].xpmp=NULL;
  butn2[1].xpmh=NULL;
  butn2[1].bkgr=-1;
  butn2[1].butncode='o';
  DIL h2 = { 
    'h',
    130,247,  
    286,280,
    2,0,  
    72, 
    25, 
    2,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn2, 
    slidebaroptsplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h2.Wid,(char *)"slidebaroptWidget9");
  DIM m3 = { 
    'm',
    45,152,  
    201,175,  
    1,0  
  };
  strncpy(m3.msg,(char *)"Widget Color",499);
  strcpy(m3.Wid,(char *)"slidebaroptWidget12");
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"Color");
  butn4[0].xpmn=NULL;
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-1;
  butn4[0].butncode='';
  DIN b4 = { 
    'n',
    199,147,  
    279,182,
    2,2,  
    70, 
    25, 
    1,1, 
    4,0.200000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn4, 
    slidebaroptbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b4.Wid,(char *)"slidebaroptWidget13");
  T_ELMT *e5  ; 
  e5 =(T_ELMT *)malloc(sizeof(T_ELMT)*3);
  e5[0].fmt = (char *)malloc(14);
  strcpy(e5[0].fmt,(char *)"Min. Value%6d");
  e5[0].v=(void *)v[1];
  e5[0].sw=1;
  e5[1].fmt = (char *)malloc(14);
  strcpy(e5[1].fmt,(char *)"Max. value%6d");
  e5[1].v=(void *)v[2];
  e5[1].sw=1;
  e5[2].fmt = (char *)malloc(9);
  strcpy(e5[2].fmt,(char *)"Name%15s");
  e5[2].v=(void *)v[3];
  e5[2].sw=1;
  DIT t5 = { 
    't',
    4,24,  
    280,118,
    20, 
    1,3, 
    e5,
    1,1,
    NULL,slidebaropttextbox1callback,1,0,18,9 /* args,Call back */
  };
  strcpy(t5.Wid,(char *)"slidebaroptWidget15");
  t5.pt=NULL;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+7));
  d =dtmp+i; 
  d[6].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIRA));
  slidebaroptbrowser1init(&r0,pt) ;
  *d[0].r = r0;
  d[0].r->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIM));
  *d[1].m = m1;
  d[1].m->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIL));
  slidebaroptsplbutton1init(&h2,pt) ;
  *d[2].h = h2;
  d[2].h->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIM));
  *d[3].m = m3;
  d[3].m->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIN));
  slidebaroptbutton1init(&b4,pt) ;
  *d[4].N = b4;
  d[4].N->item = -1;
  d[5].t = (DIT *)malloc(sizeof(DIT));
  *d[5].t = t5;
  d[5].t->item = -1;
  d[6].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeslidebaroptGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    RadioButtons1  1 data value
    Text_Box1  3 data values

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
   char  *v3 ;
   v3 = (char *)malloc(sizeof(100));
   v3[0] = '\0';
   void** v=(void **)malloc(sizeof(void*)*4);
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = slidebaroptGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int slidebaropt( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = slidebaroptGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 5;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 100;   /* Position of Dialog */ 
  D.yo = 100;
  D.xl = 421;    /*  Length of Dialog */
  D.yl = 285;    /*  Width  of Dialog */
  D.Initfun = slidebaroptinit;    /*   init fuction for Dialog */
  D.Cleanupfun = slidebaroptcleanup;    /*   init fuction for Dialog */
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
  D.Callback = slidebaroptCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = slidebaroptResizeCallBack;  /*  Resize callback */
  D.WaitCallback = NULL;
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
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
//  ModifyslidebaroptGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
int Runslidebaropt(void *arg) {
/*************************************************

    RadioButtons1  1 data value
    Text_Box1  3 data values

*************************************************/
   int ret;
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   char  v3[100]=" " ;
   void* v[4];
   DIHB *W;
   W = (DIHB *)arg;
   v0 = W->type+1;
   v1 = W->min;
   v2 = W->max;
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(W->Wid);
   void *pt=arg; /* pointer to send any extra information */
   ret = slidebaropt(Parent,v,pt )-1;
   W->type = v0-1;
   W->min=v1;
   W->max = v2;
   return ret;
}
