#include <kulina.h>
extern void *Parent;
int  checkboxtextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  checkboxbrowser1callback(int item,int i,void *Tmp) {
  ThumbNail **th;
  DICH *C;DIALOG *D;void *pt; 
  DIX *X;
  int ret=1; 
  int k,*sw;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  X = (DIX *)pt;
  C = (DICH *)kgGetWidget(Tmp,i);
  th = (ThumbNail **)C->list;
#if 1
  X->itemhi = th[0]->sw;
  X->bkgr = th[1]->sw;
  X->bordr = th[2]->sw;
  X->hide = th[3]->sw;
#endif
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
void  checkboxbrowser1init(DICH *C,void *pt) {
  ThumbNail **th;
  char **menu=NULL;int *sw=NULL;void **xpm; 
  DIX *X;
  int type,i;
  X = (DIX *)pt;
  th = (ThumbNail **)C->list;
#if 1
  for(i=0;i<4;i++) th[i]->sw=0;
  if(X->itemhi != 0) th[0]->sw=1;
  if(X->bkgr != 0) th[1]->sw=1;
  if(X->bordr != 0) th[2]->sw=1;
  if(X->hide != 0) th[3]->sw=1;
#endif
}
int  checkboxhoribar1callback(int key,int i,void *Tmp) {
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
int checkboxinit(void *Tmp) {
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int checkboxCallBack(void *Tmp,void *tmp) {
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


int checkboxGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*7);
  for(j=0;j<7;j++) e0[j].noecho=0;
  for(j=0;j<7;j++) e0[j].img=NULL;
  e0[0].fmt = (char *)malloc(10);
  strcpy(e0[0].fmt,(char *)"Length%4d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[1].fmt = (char *)malloc(9);
  strcpy(e0[1].fmt,(char *)"Width%4d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[2].fmt = (char *)malloc(15);
  strcpy(e0[2].fmt,(char *)"Item Length%4d");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  e0[3].fmt = (char *)malloc(14);
  strcpy(e0[3].fmt,(char *)"Item Width%4d");
  e0[3].v=(void *)v[3];
  e0[3].sw=1;
  e0[4].fmt = (char *)malloc(12);
  strcpy(e0[4].fmt,(char *)"No Items%4d");
  e0[4].v=(void *)v[4];
  e0[4].sw=1;
  e0[5].fmt = (char *)malloc(17);
  strcpy(e0[5].fmt,(char *)"Border Offset%4d");
  e0[5].v=(void *)v[5];
  e0[5].sw=1;
  e0[6].fmt = (char *)malloc(16);
  strcpy(e0[6].fmt,(char *)"Scroll Width%4d");
  e0[6].v=(void *)v[6];
  e0[6].sw=1;
  DIT t0 = { 
    't',
    16,21,  
    221,236,
    20, 
    1,7, 
    e0,
    1,1,
    NULL,NULL,0,0 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"");
  char *menu1[]  = { 
    (char *)"Draw item highlight",
    (char *)"Draw background",
    (char *)"Draw Border",
    (char *)"Hide",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c1 = { 
    'c',
    241,70,  
    431,182,   
    0,0,  
    153, 
    25, 
    1,4, 
    0,4, 
    (int *)v[7], 
    NULL, 
    NULL, 
    NULL,NULL, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  c1.list=(void **)th0;
  strcpy(c1.Wid,(char *)"");
  char **titles2=NULL; 
  titles2= (char **)malloc(sizeof(char *)*1);
  titles2[0]= (char *)malloc(5);
  strcpy(titles2[0],(char *)"Okay");
  int *sw2=NULL  ; 
  sw2 =(int *)malloc(sizeof(int)*1) ; 
  sw2[0]= 1; 
  char **xpms2  = NULL; 
  xpms2  = (char **)malloc(sizeof(char *)*3); 
  xpms2[0]=   NULL; /* pixmap info */ 
  xpms2[1]=   NULL; /* pixmap info */ 
  xpms2[2]=   NULL; /* pixmap info */ 
  int *bkgr2 =NULL; 
  bkgr2 =(int *)malloc(sizeof(int)*1) ; 
  bkgr2[0]=  -1; 
  char *butncode2  = NULL;
  DILN H2 = { 
    'H',
    198,294,  
    284,325,
    4,0,
    80, 
    25, 
    1,1, 
    NULL, 
    sw2,
    titles2,
    butncode2,
    NULL,checkboxhoribar1callback,/* arg, Callbak */
    (void **)xpms2,bkgr2, /* pointers to xpms and colors */
     3,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H2.bval = 1; 
  strcpy(H2.Wid,(char *)"");
  T_ELMT *e3  ; 
  e3 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e3[0].fmt = (char *)malloc(16);
  strcpy(e3[0].fmt,(char *)"Widget Name%20s");
  e3[0].v=(void *)v[8];
  e3[0].sw=1;
  DIT t3 = { 
    't',
    55,243,  
    387,277,
    20, 
    1,1, 
    e3,
    1,1,
    NULL,NULL,0,0 /* args,Call back */
  };
  strcpy(t3.Wid,(char *)"checkboxWidget4");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+5));
  d =dtmp+i; 
  d[4].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DICH));
  *d[1].c = c1;
  d[1].c->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DILN));
  *d[2].H = H2;
  d[2].H->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIT));
  *d[3].t = t3;
  d[3].t->item = -1;
  d[4].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

int checkbox( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010100;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = checkboxGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 3;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 443;   /* Position of Dialog */ 
  D.yo = 137;
  D.xl = 441;    /*  Length of Dialog */
  D.yl = 332;    /*  Width  of Dialog */
  D.Initfun = NULL;
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
  D.Callback = checkboxCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = NULL;
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
//  ModifychecboxGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  k=0; 
  while(d[k].t != NULL) {
    switch(d[k].t->code){
      case 'r':
       kgFreeDouble((void **)(d[k].r->list));
       d[k].r->list=NULL;
      break;
      case 'c':
       kgFreeDouble((void **)(d[k].c->list));
       d[k].c->list=NULL;
      break;
      deafult:
      break;
    }
    k++;
  }
//  insert any memory frees here to avoid leak  
  kgCleanUi(&D);
  return ret;
}
void *Runcheckbox(void *arg) {
/*************************************************

    Text_Box1  7 data values
    CheckBox1  1 data value
    Text_Box2  1 data values

*************************************************/
   DIX *X;
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   int   v4 = 1;
   int   v5 = 1;
   int   v6 = 1;
   int   v7 = 1;
   char  v8[100]=" " ;
   void* v[9];
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(&v3);
   v[4]=(void *)(&v4);
   v[5]=(void *)(&v5);
   v[6]=(void *)(&v6);
   v[7]=(void *)(&v7);
   v[8]=(void *)(v8);
   void *pt=arg; /* pointer to send any extra information */
   X = (DIX *)arg;
   v0 = X->x2-X->x1;
   v1 = X->y2-X->y1;
   v2 = X->lngth;
   v3 = X->width;
   v4 = X->ny;
   v5 = X->offset;
   v6 = X->w;
   strcpy(v8,X->Wid);
   checkbox(Parent,v,pt );
   X->x2=X->x1+v0;
   X->y2=X->y1+v1;
   X->lngth = v2;
   X->width = v3;
   X->ny = v4;
   X->offset=v5;
   if(v5==0) v5=2;
   X->w = v6;
   strcpy(X->Wid,v8);
   return NULL;
}
