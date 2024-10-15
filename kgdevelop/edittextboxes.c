#include <kulina.h>
#include "edittextboxesCallbacks.h"
//#include "Gclredittextboxes.c"
extern DIALOG *Parent;
void ModifyedittextboxesGc(void *Tmp) {
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
   gc->GuiGuiSize =9;
   gc->InputFontSize =8;
   gc->MenuFont = 21;
   gc->PromptFont = 21;
   gc->ButtonFont = 21;
   gc->MsgFont = 21;
   gc->Font=23;
   kgMkgclr((char *)"edittextboxes",Tmp);
*/
}
int edittextboxesGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e0[0].fmt = (char *)malloc(24);
  strcpy(e0[0].fmt,(char *)"Widget Name%20s");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[0].noecho=0;
  e0[0].img=NULL;
  DIT t0 = { 
    't',
    65,71,  
    395,104,
    20, 
    1,1, 
    e0,
    1,1,
    NULL,edittextboxestextbox1callback,0,0,18,9 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"edittextTbox1");
  t0.pt=NULL;
  t0.type = 0;
  t0.item = -1;
  char *menu1[]  = { 
    (char *)"Draw Border",
    (char *)"Hide Widget",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c1 = { 
    'c',
    46,156,  
    350,191,   
    8,0,  
    140, 
    25, 
    1,2, 
    0,1, 
    (int *)v[1], 
    NULL, 
    NULL, 
    NULL,edittextboxesbrowser1callback, /* *args, callback */
    1,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  c1.list=(void **)th0;
  strcpy(c1.Wid,(char *)"edittextCbox1");
  c1.item = -1;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"!c03Cancel");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-235255250;
  butn2[0].butncode=127;
  butn2[1].sw=1;
  strcpy(butn2[1].title,(char *)"!c37Continue");
  butn2[1].xpmn=NULL;
  butn2[1].xpmp=NULL;
  butn2[1].xpmh=NULL;
  butn2[1].bkgr=-235255250;
  butn2[1].butncode=127;
  DIL h2 = { 
    'h',
    162,201,  
    342,234,
    2,0,  
    84, 
    25, 
    2,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn2, 
    edittextboxessplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h2.Wid,(char *)"edittextSbun1");
  h2.item = -1;
  char *menu3[]  = { 
    (char *)"Default",
    (char *)"Type1",
    NULL 
  };
  ThumbNail **th1 ;
  DIRA r3 = { 
    'r',
    181,115,  
    422,149,   
    8,0,  
    90, 
    25, 
    1,2, 
    0,1, 
    (int *)v[2], 
    NULL, 
    NULL ,
    NULL,edittextboxesbrowser2callback, /* *args, callback */
    1,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    10, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu3);
  r3.list=(void **)th1;
  strcpy(r3.Wid,(char *)"edittextRadio1");
  r3.item = -1;
  DIM m4 = { 
    'm',
    42,119,  
    182,143,  
    1,0  
  };
  strncpy(m4.msg,(char *)"Text Box/Table  Type",499);
  strcpy(m4.Wid,(char *)"edittextMsg1");
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
  d[1].t = (DIT *)malloc(sizeof(DICH));
  *d[1].c = c1;
  d[1].c->item = -1;
  edittextboxesbrowser1init(d[1].c,pt) ;
  d[2].t = (DIT *)malloc(sizeof(DIL));
  *d[2].h = h2;
  d[2].h->item = -1;
  edittextboxessplbutton1init(d[2].h,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIRA));
  *d[3].r = r3;
  d[3].r->item = -1;
  edittextboxesbrowser2init(d[3].r,pt) ;
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

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeedittextboxesGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  1 data values
    CheckBox1  1 data value
    RadioButtons2  1 data value

*************************************************/
   char  *v0 ;
   v0 = (char *)malloc(sizeof(char)*500);
   v0[0] = '\0';
   int  *v1 ;
   v1 = (int *)malloc(sizeof(int));
   *v1 = 1;
   int  *v2 ;
   v2 = (int *)malloc(sizeof(int));
   *v2 = 1;
   void** v=(void **)malloc(sizeof(void*)*4);
   v[3]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = edittextboxesGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int edittextboxes( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = edittextboxesGroup(&D,v,pt);
#else 
  GrpId = MakeedittextboxesGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 3;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 585;   /* Position of Dialog */ 
  D.yo = 322;
  D.xl = 478;    /*  Length of Dialog */
  D.yl = 246;    /*  Width  of Dialog */
  if(parent != Parent) {
	  D.xo=0;D.yo=200;
  }
  else {
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo = (xres - D.xl)*0.5;
     D.yo = (yres - D.yl)*0.25;
  }
  D.Initfun = edittextboxesinit;    /*   init fuction for Dialog */
  D.Cleanupfun = edittextboxescleanup;    /*   init fuction for Dialog */
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
  D.Callback = edittextboxesCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = edittextboxesResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = edittextboxesWaitCallBack;  /*  Wait callback */
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
  Modifyedittextboxes(&D,GrpId);    /*  add extras to  gui*/
  ModifyedittextboxesGc(&D);    /*  set colors for gui if don't like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret-1;
}
int Runedittextboxes(void *Dia,void *arg) {
/*************************************************

    Text_Box1  1 data values
    CheckBox1  1 data value
    RadioButtons2  1 data value

*************************************************/
   int ret;
   char  v0[500]="" ;
   int   v1 = 1;
   int   v2 = 1;
   void* v[3];
   v[0]=(void *)(v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   void *pt[3];
   DIT *t = (DIT *)arg;
   int hide,bordr,type;
   hide = t->hide;
   bordr =t->bordr;
   type =t->type;
   strcpy(v0,t->Wid);
   pt[0]=&hide;
   pt[1]=&bordr;
   pt[2]=&type;
   ret = edittextboxes(Dia,v,pt );
   if(ret) {
     strcpy(t->Wid,v0);
     t->hide = hide;
     t->bordr = bordr;
     t->type = type;
   }

   return ret;
}
