#include <kulina.h>
#include "kgdevelopCallbacks.h"
#include "Gclrkgdevelop.c"
int kgdevelopGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  BUT_STR  *butn0=NULL; 
  butn0= (BUT_STR *)malloc(sizeof(BUT_STR)*7);
  butn0[0].sw=1;
  strcpy(butn0[0].title,(char *)"File");
  butn0[0].xpmn=NULL;
  butn0[0].xpmp=NULL;
  butn0[0].xpmh=NULL;
  butn0[0].bkgr=-1;
  butn0[0].butncode=125;
  butn0[1].sw=1;
  strcpy(butn0[1].title,(char *)"Widget");
  butn0[1].xpmn=NULL;
  butn0[1].xpmp=NULL;
  butn0[1].xpmh=NULL;
  butn0[1].bkgr=-1;
  butn0[1].butncode=125;
  butn0[2].sw=1;
  strcpy(butn0[2].title,(char *)"Border");
  butn0[2].xpmn=NULL;
  butn0[2].xpmp=NULL;
  butn0[2].xpmh=NULL;
  butn0[2].bkgr=-1;
  butn0[2].butncode=125;
  butn0[3].sw=1;
  strcpy(butn0[3].title,(char *)"Resize");
  butn0[3].xpmn=NULL;
  butn0[3].xpmp=NULL;
  butn0[3].xpmh=NULL;
  butn0[3].bkgr=-1;
  butn0[3].butncode=125;
  butn0[4].sw=1;
  strcpy(butn0[4].title,(char *)"Repos");
  butn0[4].xpmn=NULL;
  butn0[4].xpmp=NULL;
  butn0[4].xpmh=NULL;
  butn0[4].bkgr=-1;
  butn0[4].butncode=125;
  butn0[5].sw=1;
  strcpy(butn0[5].title,(char *)"Options");
  butn0[5].xpmn=NULL;
  butn0[5].xpmp=NULL;
  butn0[5].xpmh=NULL;
  butn0[5].bkgr=-1;
  butn0[5].butncode=125;
  butn0[6].sw=1;
  strcpy(butn0[6].title,(char *)"Test");
  butn0[6].xpmn=NULL;
  butn0[6].xpmp=NULL;
  butn0[6].xpmh=NULL;
  butn0[6].bkgr=-1;
  butn0[6].butncode=125;
  DIN b0 = { 
    'n',
    7,3,  
    700,38,
    12,5,  
    84, 
    25, 
    7,1, 
    1,0.500000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn0, 
    kgdevelopKDbarcallback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b0.Wid,(char *)"KDbar");
  b0.item = -1;
  char *xpm1=   NULL; /* pixmap info */ 
  DIG g1 = { 
    'g',
    9,43,  
    2505,956,  
    (void *)xpm1,
    0, /* bkgr colour */ 
    kgdevelopKDgboxinit, /* void *initgraph(int,void *)  */ 
    NULL,0,0 /* *data border hide*/
  };
  strcpy(g1.Wid,(char *)"KDgbox");
  g1.item = -1;
  DII i2 = { 
    'i',
    716,5,  
    1002,38,  
    30,1,0   
  };
  strcpy(i2.Wid,(char *)"KDinfo");
  i2.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+4));
  d =dtmp+i; 
  d[3].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIN));
  *d[0].N = b0;
  d[0].N->item = -1;
  kgdevelopKDbarinit(d[0].N,pt) ;
  d[1].t = (DIT *)malloc(sizeof(DIG));
  *d[1].g = g1;
  d[1].g->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DII));
  *d[2].i = i2;
  d[2].i->item = -1;
  d[3].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakekgdevelopGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = kgdevelopGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   kgdevelopSetup(D,Gpt->arg);
   return GrpId;
}

int kgdevelop( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = kgdevelopGroup(&D,v,pt);
#else 
  GrpId = MakekgdevelopGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 0; /* set to 1 for backup */
  D.bor_type = 3;
  D.df = 0;
  D.tw = 43;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 0;   /* Position of Dialog */ 
  D.yo = 0;
  D.xl = 2514;    /*  Length of Dialog */
  D.yl = 963;    /*  Width  of Dialog */
  D.Initfun = kgdevelopinit;    /*   init fuction for Dialog */
  D.Cleanupfun = kgdevelopcleanup;    /*   cleanup fuction for Dialog */
  D.kbattn = 1;    /*  1 for drawing keyborad attention */
  D.butattn = 1;    /*  1 for drawing button attention */
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
  D.Callback = kgdevelopCallBack;    /*  default Callback  */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = kgdevelopResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = kgdevelopWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.NoWinMngr = 0;    /*  1 for no Window Manager*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
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
  ModifykgdevelopGc(&D);    /*  set colors for gui if do not like default*/
  Modifykgdevelop(&D,GrpId);    /*  add extras to  gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runkgdevelop(void *parent ,void *args) {
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt[2]={NULL,NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   pt[0]=args;
   kgdevelop(parent,v,(void *)pt );
   return pt[1];
}
