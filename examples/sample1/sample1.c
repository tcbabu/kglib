#include <kulina.h>
#include "sample1Callbacks.h"
void Modifysample1Gc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int sample1Group( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  char *xpm0=   NULL; /* pixmap info */ 
  DIG g0 = { 
    'g',
    154,5,  
    794,485,  
    (void *)xpm0,
    0, /* bkgr colour */ 
    sample1gbox1init,/* void *initgraph(int,void *)  */ 
    NULL,0,0 /* *data border hide*/
  };
  strcpy(g0.Wid,(char *)"sample1Widget1");
  g0.item = -1;
  BUT_STR  *butn1=NULL; 
  butn1= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn1[0].sw=1;
  strcpy(butn1[0].title,(char *)"Quit");
  butn1[0].xpmn=NULL;
  butn1[0].xpmp=NULL;
  butn1[0].xpmh=NULL;
  butn1[0].bkgr=-1;
  butn1[0].butncode='';
  DIL h1 = { 
    'h',
    34,399,  
    116,432,
    2,0,  
    72, 
    25, 
    1,1, 
    2,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn1, 
    sample1splbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h1.Wid,(char *)"sample1Widget2");
  h1.item = -1;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*6);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"Drawing Tool");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-1;
  butn2[0].butncode='';
  butn2[1].sw=1;
  strcpy(butn2[1].title,(char *)"Zoom");
  butn2[1].xpmn=NULL;
  butn2[1].xpmp=NULL;
  butn2[1].xpmh=NULL;
  butn2[1].bkgr=-1;
  butn2[1].butncode='';
  butn2[2].sw=1;
  strcpy(butn2[2].title,(char *)"Redraw");
  butn2[2].xpmn=NULL;
  butn2[2].xpmp=NULL;
  butn2[2].xpmh=NULL;
  butn2[2].bkgr=-1;
  butn2[2].butncode='';
  butn2[3].sw=1;
  strcpy(butn2[3].title,(char *)"Antialiasing On");
  butn2[3].xpmn=NULL;
  butn2[3].xpmp=NULL;
  butn2[3].xpmh=NULL;
  butn2[3].bkgr=-1;
  butn2[3].butncode='';
  butn2[4].sw=1;
  strcpy(butn2[4].title,(char *)"Antialising Off");
  butn2[4].xpmn=NULL;
  butn2[4].xpmp=NULL;
  butn2[4].xpmh=NULL;
  butn2[4].bkgr=-1;
  butn2[4].butncode='';
  butn2[5].sw=1;
  strcpy(butn2[5].title,(char *)"Make Png");
  butn2[5].xpmn=NULL;
  butn2[5].xpmp=NULL;
  butn2[5].xpmh=NULL;
  butn2[5].bkgr=-1;
  butn2[5].butncode='';
  DIN b2 = { 
    'n',
    8,126,  
    138,290,
    2,2,  
    120, 
    24, 
    1,6, 
    5,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn2, 
    sample1button1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b2.Wid,(char *)"sample1Widget3");
  b2.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+4));
  d =dtmp+i; 
  d[3].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIG));
  *d[0].g = g0;
  d[0].g->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIL));
  sample1splbutton1init(&h1,pt) ;
  *d[1].h = h1;
  d[1].h->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIN));
  sample1button1init(&b2,pt) ;
  *d[2].N = b2;
  d[2].N->item = -1;
  d[3].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int Makesample1Group(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = sample1Group(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int sample1( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = sample1Group(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 2;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 10;   /* Position of Dialog */ 
  D.yo = 10;
  D.xl = 800;    /*  Length of Dialog */
  D.yl = 491;    /*  Width  of Dialog */
  D.Initfun = sample1init;    /*   init fuction for Dialog */
  D.Cleanupfun = sample1cleanup;    /*   init fuction for Dialog */
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
  D.Callback = sample1CallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = sample1ResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = sample1WaitCallBack;  /*  Wait callback */
#endif
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
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/
//  Modifysample1Gc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runsample1(void *arg) {
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
   sample1(NULL,v,pt );
   return NULL;
}
