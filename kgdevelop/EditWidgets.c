#include <kulina.h>
#include "EditWidgetsCallbacks.h"
//#include "GclrEditWidgets.c"
extern DIALOG *Parent;
void ModifyEditWidgetsGc(void *Tmp) { 
  DIALOG *D;
  Gclr *gc;
  D = (DIALOG *)Tmp;
  gc = &(D->gc);
#if 0
  kgColorTheme(D,220,220,200);
  kgColorTheme1(D,220,220,200);
  kgColorTheme2(D,220,220,200);
#endif
  kgDefineColor(49,50,55,50);
  gc->char_clr = 49;
  kgDefineColor(44,220,220,220);
  gc->fill_clr = 44;
  kgDefineColor(44,220,220,220);
  gc->bodr_clr = 44;
  kgDefineColor(6,0,255,255);
  gc->cur_clr = 6;
  kgDefineColor(45,240,255,254);
  gc->high_clr = 45;
  kgDefineColor(47,244,247,255);
  gc->char_hclr = 47;
  kgDefineColor(49,50,55,50);
  gc->msg_char = 49;
  kgDefineColor(45,240,255,254);
  gc->msg_fill = 45;
  kgDefineColor(47,244,247,255);
  gc->msg_bodr = 47;
  kgDefineColor(43,187,187,187);
  gc->txt_fill = 43;
  kgDefineColor(48,40,45,40);
  gc->txt_char = 48;
  kgDefineColor(49,50,55,50);
  gc->txt_pchar = 49;
  kgDefineColor(43,187,187,187);
  gc->tabl_fill = 43;
  kgDefineColor(41,99,99,99);
  gc->tabl_line = 41;
  kgDefineColor(49,50,55,50);
  gc->tabl_char = 49;
  kgDefineColor(47,244,247,255);
  gc->tabl_hchar = 47;
  kgDefineColor(40,66,66,66);
  gc->v_dim = 40;
  kgDefineColor(42,143,143,143);
  gc->dim = 42;
  kgDefineColor(46,242,246,255);
  gc->bright = 46;
  kgDefineColor(47,244,247,255);
  gc->vbright = 47;
  kgDefineColor(85,39,44,39);
  gc->twin_fill = 85;
  kgDefineColor(86,235,255,250);
  gc->twin_char = 86;
  kgDefineColor(42,143,143,143);
  gc->twin_bodr = 42;
  kgDefineColor(46,242,246,255);
  gc->info_fill = 46;
  kgDefineColor(49,50,55,50);
  gc->info_char = 49;
  kgDefineColor(49,50,55,50);
  gc->but_char = 49;
  kgDefineColor(49,50,55,50);
  gc->menu_char = 49;
  kgDefineColor(40,66,66,66);
  gc->SplashFillColor = 40;
  kgDefineColor(46,242,246,255);
  gc->SplashBodrColor = 46;
  kgDefineColor(26,174,239,239);
  gc->SplashCharColor = 26;
  kgDefineColor(46,242,246,255);
  gc->ProgFillColor = 46;
  kgDefineColor(6,0,255,255);
  gc->ProgBodrColor = 6;
  kgDefineColor(8,0,190,255);
  gc->ProgColor = 8;
  kgDefineColor(44,220,220,220);
  gc->scroll_fill = 44;
  kgDefineColor(46,242,246,255);
  gc->scroll_bright = 46;
  kgDefineColor(47,244,247,255);
  gc->scroll_vbright = 47;
  kgDefineColor(42,143,143,143);
  gc->scroll_dim = 42;
  kgDefineColor(6,0,255,255);
  gc->ItemHighColor = 6;
//  kgMkgclr("EditWidgets",Tmp);
}
int EditWidgetsGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  DIY y0 = { 
    'y',
    5,49,  
    540,388,   
    110,30,  
    55, 
    64, 
    1,9879771, 
    0,3, 
    (int *)v[0], 
    NULL, 
    NULL, 
    NULL,EditWidgetsbrowser1callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     1,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(y0.Wid,(char *)"EditYbox");
  y0.item = -1;
  DII i1 = { 
    'i',
    11,14,  
    387,44,  
    40,0,1   
  };
  strcpy(i1.Wid,(char *)"EditInfo");
  i1.item = -1;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"Done");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-235255250;
  butn2[0].butncode=127;
  DIL h2 = { 
    'h',
    213,407,  
    295,440,
    2,0,  
    72, 
    25, 
    1,1, 
    2,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn2, 
    EditWidgetssplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h2.Wid,(char *)"EditWidgetsWidget3");
  h2.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+4));
  d =dtmp+i; 
  d[3].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIY));
  *d[0].y = y0;
  d[0].y->item = -1;
  EditWidgetsbrowser1init(d[0].y,pt) ;
  d[1].t = (DIT *)malloc(sizeof(DII));
  *d[1].i = i1;
  d[1].i->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIL));
  *d[2].h = h2;
  d[2].h->item = -1;
  EditWidgetssplbutton1init(d[2].h,pt) ;
  d[3].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeEditWidgetsGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    ThumbnailBrowser1  1 data value

*************************************************/
   int  *v0 ;
   v0 = (int *)malloc(sizeof(int));
   *v0 = 1;
   void** v=(void **)malloc(sizeof(void*)*2);
   v[1]=NULL;
   v[0]=(void *)(v0);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = EditWidgetsGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int EditWidgets( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = EditWidgetsGroup(&D,v,pt);
#else 
  GrpId = MakeEditWidgetsGroup(&D,pt); // can try this also
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
  D.xo = 638;   /* Position of Dialog */ 
  D.yo = 179;
#if 0
  if(parent != Parent) {
	  D.xo =0; D.yo = 0;
  }
#endif
  D.xl = 550;    /*  Length of Dialog */
  D.yl = 452;    /*  Width  of Dialog */
  D.Initfun = EditWidgetsinit;    /*   init fuction for Dialog */
  D.Cleanupfun = EditWidgetscleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
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
  D.Callback = EditWidgetsCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = EditWidgetsResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = EditWidgetsWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.NoWinMngr = 0;    /*  1 for no Window Manager*/
  D.StackPos = 1;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
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
  ModifyEditWidgets(&D,GrpId);    /*  add extras to  gui*/
  ModifyEditWidgetsGc(&D);    /*  set colors for gui if don't like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *RunEditWidgets(void *arg) {
/*************************************************

    ThumbnailBrowser1  1 data value

*************************************************/
   int   v0 = 1;
   void* v[1];
   v[0]=(void *)(&v0);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   EditWidgets(arg,v,pt );
   return NULL;
}
