#include <kulina.h>
#include "UpdatesCheckCallbacks.h"
#include "GclrUpdatesCheck.c"
int UpdatesCheckGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  char *menu0[]  = { 
    (char *)"Update CallBacks (.c) file",
    (char *)"Copy Dialog file (to .c)",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c0 = { 
    'c',
    16,285,  
    475,322,   
    8,0,  
    200, 
    25, 
    1,2, 
    0,1, 
    (int *)v[0], 
    NULL, 
    NULL, 
    NULL,UpdatesCheckbrowser1callback , /* *args, Callback (null) */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    0, /* bordr */
    0, /* bkgr */
    0  /*=1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu0);
  c0.list=(void **)th0;
  strcpy(c0.Wid,(char *)"UpdatesCheckWidget3");
  c0.item = -1;
  BUT_STR  *butn1=NULL; 
  butn1= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn1[0].sw=1;
  strcpy(butn1[0].title,(char *)"Okay");
  butn1[0].xpmn=NULL;
  butn1[0].xpmp=NULL;
  butn1[0].xpmh=NULL;
  butn1[0].bkgr=-1;
  butn1[0].butncode=31;
  DIL h1 = { 
    'h',
    213,322,  
    295,355,
    2,0,  
    72, 
    25, 
    1,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn1, 
    UpdatesChecksplbutton1callback ,  /* *args, Callback (null) */
    NULL  /* any args */
  };
  strcpy(h1.Wid,(char *)"UpdatesCheckWidget4");
  h1.item = -1;
  DIS s2 = { 
    's',
    3,7,  
    472,276,   
    12,  
    NULL,
    NULL,
    NULL ,
    NULL,NULL, /* *args, Callback InfoBox */
    20,6,22,1,1,1,0
//     line width,offset (not used),scroll width,highlight item(not used)
//     border on/off,bkgr on/off,hide on/off
//     uses Gclr items: msg_fill,msg_char,msg_bodr,scroll_fill,scroll_dim,scroll_vbright)
  };
  strcpy(s2.Wid,(char *)"InfoBox");
  s2.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+4));
  d =dtmp+i; 
  d[3].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DICH));
  *d[0].c = c0;
  d[0].c->item = -1;
  UpdatesCheckbrowser1init(d[0].c,pt) ;
  d[1].t = (DIT *)malloc(sizeof(DIL));
  *d[1].h = h1;
  d[1].h->item = -1;
  UpdatesChecksplbutton1init(d[1].h,pt) ;
  d[2].t = (DIT *)malloc(sizeof(DIS));
  *d[2].s = s2;
  d[2].s->item = -1;
  UpdatesCheckbrowser2init(d[2].s,pt) ;
  d[3].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeUpdatesCheckGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    CheckBox1  1 data value

*************************************************/
   int  *v0 ;
   v0 = (int *)malloc(sizeof(int));
   *v0 = 1;
   void** v=(void **)malloc(sizeof(void*)*2);
   v[1]=NULL;
   v[0]=(void *)(v0);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = UpdatesCheckGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int UpdatesCheck( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = UpdatesCheckGroup(&D,v,pt);
#else 
  GrpId = MakeUpdatesCheckGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 2;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 895;   /* Position of Dialog */ 
  D.yo = 123;
  D.xl = 483;    /*  Length of Dialog */
  D.yl = 362;    /*  Width  of Dialog */
  D.Initfun = UpdatesCheckinit;    /*   init fuction for Dialog */
  D.Cleanupfun = UpdatesCheckcleanup;    /*   init fuction for Dialog */
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
  D.Callback = UpdatesCheckCallBack;    /*  default Callback  */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = UpdatesCheckResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = UpdatesCheckWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.NoWinMngr = 0;    /*  1 for no Window Manager*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 2.0");    /*  Dialog name you may change */
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
  ModifyUpdatesCheck(&D,GrpId);    /*  add extras to  gui*/
  ModifyUpdatesCheckGc(&D);    /*  set colors for gui if do not like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *RunUpdatesCheck(void *parent ,void *args) {
/*************************************************

    CheckBox1  1 data value

*************************************************/
   int   v0 = 1;
   void* v[1];
   v[0]=(void *)(&v0);
   void *pt[2]={NULL,NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   pt[0]=args;
   UpdatesCheck(parent,v,(void *)pt );
   return pt[1];
}
