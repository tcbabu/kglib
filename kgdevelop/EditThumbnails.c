
#include <kulina.h>
#include "EditThumbnailsCallbacks.h"
//#include "GclrEditThumbnails.c"
void ModifyEditThumbnailsGc(void *Tmp) {
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
   gc->FontSize =9;
   gc->GuiFontSize =9;
   gc->InputFontSize =8;
   gc->MenuFont = 21;
   gc->PromptFont = 21;
   gc->ButtonFont = 21;
   gc->MsgFont = 21;
   gc->Font=23;
   kgMkgclr((char *)"EditThumbnails",Tmp);
*/
}
int EditThumbnailsGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  BUT_STR  *butn0=NULL; 
  butn0= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn0[0].sw=1;
  strcpy(butn0[0].title,(char *)"Delete");
  butn0[0].xpmn=NULL;
  butn0[0].xpmp=NULL;
  butn0[0].xpmh=NULL;
  butn0[0].bkgr=-240245255;
  butn0[0].butncode=127;
  butn0[1].sw=1;
  strcpy(butn0[1].title,(char *)"Add");
  butn0[1].xpmn=NULL;
  butn0[1].xpmp=NULL;
  butn0[1].xpmh=NULL;
  butn0[1].bkgr=-240245255;
  butn0[1].butncode=127;
  DIN b0 = { 
    'n',
    129,30,  
    307,60,
    2,2,  
    84, 
    24, 
    2,1, 
    7,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn0, 
    EditThumbnailsbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b0.Wid,(char *)"EditButtons");
  b0.item = -1;
  BUT_STR  *butn1=NULL; 
  butn1= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn1[0].sw=1;
  strcpy(butn1[0].title,(char *)"Okay");
  butn1[0].xpmn=NULL;
  butn1[0].xpmp=NULL;
  butn1[0].xpmh=NULL;
  butn1[0].bkgr=-235255250;
  butn1[0].butncode=127;
  DIL h1 = { 
    'h',
    130,330,  
    224,363,
    2,0,  
    84, 
    25, 
    1,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn1, 
    EditThumbnailssplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h1.Wid,(char *)"EditOkay");
  h1.item = -1;
  DIY y2 = { 
    'y',
    9,60,  
    333,324,   
    250,6,  
    20, 
    20, 
    1,25, 
    0,9, 
    (int *)v[0], 
    NULL, 
    NULL, 
    NULL,EditThumbnailsbrowser1callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     1,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(y2.Wid,(char *)"EditThumbnailsWidget1");
  y2.item = -1;
  DIM m3 = { 
    'm',
    9,7,  
    332,29,  
    -1,0  
  };
  strncpy(m3.msg,(char *)"",499);
  strcpy(m3.Wid,(char *)"ItemsMsg");
  m3.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+5));
  d =dtmp+i; 
  d[4].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIN));
  *d[0].N = b0;
  d[0].N->item = -1;
  EditThumbnailsbutton1init(d[0].N,pt) ;
  d[1].t = (DIT *)malloc(sizeof(DIL));
  *d[1].h = h1;
  d[1].h->item = -1;
  EditThumbnailssplbutton1init(d[1].h,pt) ;
  d[2].t = (DIT *)malloc(sizeof(DIY));
  *d[2].y = y2;
  d[2].y->item = -1;
  EditThumbnailsbrowser1init(d[2].y,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIM));
  *d[3].m = m3;
  d[3].m->item = -1;
  d[4].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeEditThumbnailsGroup(DIALOG *D,void *arg) {
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
   GrpId = EditThumbnailsGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int EditThumbnails( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = EditThumbnailsGroup(&D,v,pt);
#else 
  GrpId = MakeEditThumbnailsGroup(&D,pt); // can try this also
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
  D.xo = 786;   /* Position of Dialog */ 
  D.yo = 246;
  D.xl = 344;    /*  Length of Dialog */
  D.yl = 369;    /*  Width  of Dialog */
  D.Initfun = EditThumbnailsinit;    /*   init fuction for Dialog */
  D.Cleanupfun = EditThumbnailscleanup;    /*   init fuction for Dialog */
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
  D.Callback = EditThumbnailsCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = EditThumbnailsResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = EditThumbnailsWaitCallBack;  /*  Wait callback */
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
  ModifyEditThumbnails(&D,GrpId);    /*  add extras to  gui*/
  ModifyEditThumbnailsGc(&D);    /*  set colors for gui if don't like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *RunEditThumbnails(void *arg,int items,void *Th) {
/*************************************************

    Selectmenu1  1 data value

*************************************************/
#if 0
   int   v0 = 1;
   void* v[1];
   int Nitems = items;
   v[0]=(void *)(&v0);
   void *pt[2]; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   pt[0]=&Nitems;
   pt[1]= (void *)Th;

   EditThumbnails(arg,v,pt );
   return pt[1];
#else
   int i,j,k;
   int Nitems;
   char **Istrs, **Ostrs;
   ThumbNail **Ths=(ThumbNail **)Th;
   k=0;
   while(Ths[k] != NULL) k++;
   Istrs= (char **)malloc(sizeof(char *)*(k+1));
   k=0;
   while(Ths[k] != NULL) {Istrs[k]=Ths[k]->name;k++;}
   Istrs[k]=NULL;
   Ostrs= (char **)RunkgGetStrings(arg,Istrs);
   free(Istrs);
   if(Ostrs!= NULL) {
	   Ths =(ThumbNail **) kgStringToThumbNails(Ostrs);
	   free(Ostrs);
	   return Ths;
   }
   else return Th;
#endif
}
