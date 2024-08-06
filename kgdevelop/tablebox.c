#include <kulina.h>
#include "tableboxCallbacks.h"
#include "Gclrtablebox.c"
int tableboxGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*5);
  e0[0].fmt = (char *)malloc(18);
  strcpy(e0[0].fmt,(char *)"No. of Columns%4d");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  e0[0].noecho=0;
  e0[0].img=NULL;
  e0[1].fmt = (char *)malloc(15);
  strcpy(e0[1].fmt,(char *)"No. of Rows%4d");
  e0[1].v=(void *)v[1];
  e0[1].sw=1;
  e0[1].noecho=0;
  e0[1].img=NULL;
  e0[2].fmt = (char *)malloc(13);
  strcpy(e0[2].fmt,(char *)"Row Width%2d");
  e0[2].v=(void *)v[2];
  e0[2].sw=1;
  e0[2].noecho=0;
  e0[2].img=NULL;
  e0[3].fmt = (char *)malloc(12);
  strcpy(e0[3].fmt,(char *)"FontSize%2d");
  e0[3].v=(void *)v[3];
  e0[3].sw=1;
  e0[3].noecho=0;
  e0[3].img=NULL;
  e0[4].fmt = (char *)malloc(16);
  strcpy(e0[4].fmt,(char *)"Widget Name%25s");
  e0[4].v=(void *)v[4];
  e0[4].sw=1;
  e0[4].noecho=0;
  e0[4].img=NULL;
  DIT t0 = { 
    't',
    9,20,  
    433,173,
    20, 
    1,5, 
    e0,
    1,1,
    NULL,tableboxtextbox1callback,0,0,8,16 /* args,Call back */
  };
  strcpy(t0.Wid,(char *)"tableTbox");
  t0.pt=NULL;
  t0.type = 1;
  t0.item = -1;
  char *menu1[]  = { 
    (char *)"!f16Courier",
    (char *)"!f17CourierOblique",
    (char *)"!f18CourierBold",
    (char *)"!f19CourierBoldOblique",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r1 = { 
    'r',
    69,176,  
    458,236,   
    8,0,  
    170, 
    24, 
    1,4, 
    0,2, 
    (int *)v[5], 
    NULL, 
    NULL ,
    NULL,tableboxbrowser1callback, /* *args, callback */
    2,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    0, /* bordr */
    0, /* bkgr */
    0  /*=1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu1);
  r1.list=(void **)th0;
  strcpy(r1.Wid,(char *)"TableFont");
  r1.item = -1;
  char *menu2[]  = { 
    (char *)"Draw Border",
    (char *)"Hide Widget",
    (char *)"Type1",
    NULL 
  };
  ThumbNail **th1 ;
  DICH c2 = { 
    'c',
    77,241,  
    459,269,   
    0,0,  
    120, 
    25, 
    1,3, 
    0,1, 
    (int *)v[6], 
    NULL, 
    NULL, 
    NULL,tableboxbrowser2callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    0, /* bordr */
    0, /* bkgr */
    0  /*=1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu2);
  c2.list=(void **)th1;
  strcpy(c2.Wid,(char *)"tableCheckBox");
  c2.item = -1;
  DIM m3 = { 
    'm',
    14,193,  
    64,217,  
    1,0  
  };
  strncpy(m3.msg,(char *)"!w32Font",499);
  strcpy(m3.Wid,(char *)"tableelemtWidget5");
  m3.item = -1;
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"Cancel");
  butn4[0].xpmn=NULL;
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-235255250;
  butn4[0].butncode='';
  butn4[1].sw=1;
  strcpy(butn4[1].title,(char *)"!c38Okay");
  butn4[1].xpmn=NULL;
  butn4[1].xpmp=NULL;
  butn4[1].xpmh=NULL;
  butn4[1].bkgr=-235255250;
  butn4[1].butncode='';
  DIL h4 = { 
    'h',
    149,270,  
    324,300,
    2,0,  
    84, 
    25, 
    2,1, 
    7,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn4, 
    tableboxsplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h4.Wid,(char *)"tableboxsbutn");
  h4.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+6));
  d =dtmp+i; 
  d[5].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIRA));
  *d[1].r = r1;
  d[1].r->item = -1;
  tableboxbrowser1init(d[1].r,pt) ;
  d[2].t = (DIT *)malloc(sizeof(DICH));
  *d[2].c = c2;
  d[2].c->item = -1;
  tableboxbrowser2init(d[2].c,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIM));
  *d[3].m = m3;
  d[3].m->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIL));
  *d[4].h = h4;
  d[4].h->item = -1;
  tableboxsplbutton1init(d[4].h,pt) ;
  d[5].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MaketableboxGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  5 data values
    RadioButtons1  1 data value
    CheckBox2  1 data value

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
   char  *v4 ;
   v4 = (char *)malloc(sizeof(char)*500);
   v4[0] = '\0';
   int  *v5 ;
   v5 = (int *)malloc(sizeof(int));
   *v5 = 1;
   int  *v6 ;
   v6 = (int *)malloc(sizeof(int));
   *v6 = 1;
   void** v=(void **)malloc(sizeof(void*)*8);
   v[7]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(v4);
   v[5]=(void *)(v5);
   v[6]=(void *)(v6);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = tableboxGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int tablebox( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = tableboxGroup(&D,v,pt);
#else 
  GrpId = MaketableboxGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 4;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 289;   /* Position of Dialog */ 
  D.yo = 141;
  D.xl = 483;    /*  Length of Dialog */
  D.yl = 310;    /*  Width  of Dialog */
  D.Initfun = tableboxinit;    /*   init fuction for Dialog */
  D.Cleanupfun = tableboxcleanup;    /*   init fuction for Dialog */
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
  D.Callback = tableboxCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = tableboxResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = tableboxWaitCallBack;  /*  Wait callback */
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
  Modifytablebox(&D,GrpId);    /*  add extras to  gui*/
  ModifytableboxGc(&D);    /*  set colors for gui if don't like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runtablebox(void *parent ,void *args) {
/*************************************************

    Text_Box1  5 data values
    RadioButtons1  1 data value
    CheckBox2  1 data value

*************************************************/
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   char  v4[500]="" ;
   int   v5 = 1;
   int   v6 = 1;
   void* v[7];
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(&v3);
   v[4]=(void *)(v4);
   v[5]=(void *)(&v5);
   v[6]=(void *)(&v6);
   void *pt[2]={NULL,NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   pt[0]=args;
   tablebox(parent,v,(void *)pt );
   return pt[1];
}
