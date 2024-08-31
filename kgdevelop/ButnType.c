#include <kulina.h>
#include "ButnTypeCallbacks.h"
#include "dialog-password.c"
void ModifyButnTypeGc(void *Tmp) {
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
   gc->FontSize =8;
   gc->Font=23;
   kgMkgclr("ButnType",Tmp);
*/
}
int ButnTypeGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  char *xpm0=   NULL; /* pixmap info */ 
  DIP p0 = { 
    'p',
    10,8,  
    394,370,  
    (void *)xpm0,
    -1, /* bkgr colour */ 
      3,0,0.000000 /* border hide transparency*/ 
  };
  strcpy(p0.Wid,(char *)"ButnTypeWidget18");
  p0.item = -1;
  BUT_STR  *butn1=NULL; 
  butn1= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn1[0].sw=1;
  strcpy(butn1[0].title,(char *)"Type0");
  butn1[0].xpmn=(void *) (&dialog_password_str);
  butn1[0].xpmp=NULL;
  butn1[0].xpmh=NULL;
  butn1[0].bkgr=-1;
  butn1[0].butncode=127;
  DIN b1 = { 
    'n',
    26,31,  
    100,105,
    2,2,  
    64, 
    64, 
    1,1, 
    0,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn1, 
    ButnTypebutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b1.Wid,(char *)"ButnTypeWidget1");
  b1.item = -1;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"Type1");
  butn2[0].xpmn=(void *) (&dialog_password_str);
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-1;
  butn2[0].butncode=127;
  DIN b2 = { 
    'n',
    116,31,  
    190,105,
    2,2,  
    64, 
    64, 
    1,1, 
    1,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn2, 
    ButnTypebutton2callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b2.Wid,(char *)"ButnTypeWidget2");
  b2.item = -1;
  BUT_STR  *butn3=NULL; 
  butn3= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn3[0].sw=1;
  strcpy(butn3[0].title,(char *)"Type2");
  butn3[0].xpmn=(void *) (&dialog_password_str);
  butn3[0].xpmp=NULL;
  butn3[0].xpmh=NULL;
  butn3[0].bkgr=-1;
  butn3[0].butncode=127;
  DIN b3 = { 
    'n',
    206,31,  
    280,105,
    2,2,  
    64, 
    64, 
    1,1, 
    2,0.150000,0,0,1,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn3, 
    ButnTypebutton3callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b3.Wid,(char *)"ButnTypeWidget3");
  b3.item = -1;
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"Type3");
  butn4[0].xpmn=(void *) (&dialog_password_str);
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-1;
  butn4[0].butncode=127;
  DIN b4 = { 
    'n',
    301,31,  
    375,105,
    2,2,  
    64, 
    64, 
    1,1, 
    3,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn4, 
    ButnTypebutton4callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b4.Wid,(char *)"ButnTypeWidget4");
  b4.item = -1;
  BUT_STR  *butn5=NULL; 
  butn5= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn5[0].sw=1;
  strcpy(butn5[0].title,(char *)"Type4");
  butn5[0].xpmn=(void *) (&dialog_password_str);
  butn5[0].xpmp=NULL;
  butn5[0].xpmh=NULL;
  butn5[0].bkgr=-1;
  butn5[0].butncode=127;
  DIN b5 = { 
    'n',
    26,121,  
    100,195,
    2,2,  
    64, 
    64, 
    1,1, 
    4,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn5, 
    ButnTypebutton5callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b5.Wid,(char *)"ButnTypeWidget5");
  b5.item = -1;
  BUT_STR  *butn6=NULL; 
  butn6= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn6[0].sw=1;
  strcpy(butn6[0].title,(char *)"Type5");
  butn6[0].xpmn=(void *) (&dialog_password_str);
  butn6[0].xpmp=NULL;
  butn6[0].xpmh=NULL;
  butn6[0].bkgr=-1;
  butn6[0].butncode=127;
  DIN b6 = { 
    'n',
    116,121,  
    190,195,
    2,2,  
    64, 
    64, 
    1,1, 
    5,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn6, 
    ButnTypebutton6callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b6.Wid,(char *)"ButnTypeWidget6");
  b6.item = -1;
  BUT_STR  *butn7=NULL; 
  butn7= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn7[0].sw=1;
  strcpy(butn7[0].title,(char *)"Type6");
  butn7[0].xpmn=(void *) (&dialog_password_str);
  butn7[0].xpmp=NULL;
  butn7[0].xpmh=NULL;
  butn7[0].bkgr=-1;
  butn7[0].butncode=127;
  DIN b7 = { 
    'n',
    211,121,  
    285,195,
    2,2,  
    64, 
    64, 
    1,1, 
    6,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn7, 
    ButnTypebutton7callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b7.Wid,(char *)"ButnTypeWidget7");
  b7.item = -1;
  BUT_STR  *butn8=NULL; 
  butn8= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn8[0].sw=1;
  strcpy(butn8[0].title,(char *)"Type7");
  butn8[0].xpmn=(void *) (&dialog_password_str);
  butn8[0].xpmp=NULL;
  butn8[0].xpmh=NULL;
  butn8[0].bkgr=-1;
  butn8[0].butncode=127;
  DIN b8 = { 
    'n',
    301,121,  
    375,195,
    2,2,  
    64, 
    64, 
    1,1, 
    7,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn8, 
    ButnTypebutton8callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b8.Wid,(char *)"ButnTypeWidget9");
  b8.item = -1;
  BUT_STR  *butn9=NULL; 
  butn9= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn9[0].sw=1;
  strcpy(butn9[0].title,(char *)"Type8");
  butn9[0].xpmn=(void *) (&dialog_password_str);
  butn9[0].xpmp=NULL;
  butn9[0].xpmh=NULL;
  butn9[0].bkgr=-1;
  butn9[0].butncode=127;
  DIN b9 = { 
    'n',
    26,211,  
    100,285,
    2,2,  
    64, 
    64, 
    1,1, 
    8,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn9, 
    ButnTypebutton9callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b9.Wid,(char *)"ButnTypeWidget10");
  b9.item = -1;
  BUT_STR  *butn10=NULL; 
  butn10= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn10[0].sw=1;
  strcpy(butn10[0].title,(char *)"Type9");
  butn10[0].xpmn=(void *) (&dialog_password_str);
  butn10[0].xpmp=NULL;
  butn10[0].xpmh=NULL;
  butn10[0].bkgr=-1;
  butn10[0].butncode=127;
  DIN b10 = { 
    'n',
    116,211,  
    190,285,
    2,2,  
    64, 
    64, 
    1,1, 
    9,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn10, 
    ButnTypebutton10callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b10.Wid,(char *)"ButnTypeWidget11");
  b10.item = -1;
  BUT_STR  *butn11=NULL; 
  butn11= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn11[0].sw=1;
  strcpy(butn11[0].title,(char *)"Type10");
  butn11[0].xpmn=(void *) (&dialog_password_str);
  butn11[0].xpmp=NULL;
  butn11[0].xpmh=NULL;
  butn11[0].bkgr=-1;
  butn11[0].butncode=127;
  DIN b11 = { 
    'n',
    211,211,  
    285,285,
    2,2,  
    64, 
    64, 
    1,1, 
    10,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn11, 
    ButnTypebutton11callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b11.Wid,(char *)"ButnTypeWidget12");
  b11.item = -1;
  DIM m12 = { 
    'm',
    12,302,  
    391,328,  
    0,0  
  };
  strncpy(m12.msg,(char *)"!c16Note: Type0 only icon and Type10 nothing is drawn, hence invidsible button",499);
  strcpy(m12.Wid,(char *)"ButnTypeWidget13");
  m12.item = -1;
  DII i13 = { 
    'i',
    81,336,  
    296,364,  
    22,1,0   
  };
  strcpy(i13.Wid,(char *)"ButnMsg");
  i13.item = -1;
  BUT_STR  *butn14=NULL; 
  butn14= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn14[0].sw=1;
  strcpy(butn14[0].title,(char *)"Select");
  butn14[0].xpmn=NULL;
  butn14[0].xpmp=NULL;
  butn14[0].xpmh=NULL;
  butn14[0].bkgr=-235255250;
  butn14[0].butncode=127;
  DIL h14 = { 
    'h',
    155,374,  
    237,407,
    2,0,  
    72, 
    25, 
    1,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn14, 
    ButnTypesplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h14.Wid,(char *)"ButnOkay");
  h14.item = -1;
  DIM m15 = { 
    'm',
    18,13,  
    108,29,  
    0,0  
  };
  strncpy(m15.msg,(char *)"Type0",499);
  strcpy(m15.Wid,(char *)"Type0Msg");
  m15.item = -1;
  DIM m16 = { 
    'm',
    203,284,  
    304,300,  
    0,0  
  };
  strncpy(m16.msg,(char *)"Type10",499);
  strcpy(m16.Wid,(char *)"Type10Msg");
  m16.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+18));
  d =dtmp+i; 
  d[17].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIP));
  *d[0].p = p0;
  d[0].p->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIN));
  *d[1].N = b1;
  d[1].N->item = -1;
  ButnTypebutton1init(d[1].N,pt) ;
  d[2].t = (DIT *)malloc(sizeof(DIN));
  *d[2].N = b2;
  d[2].N->item = -1;
  ButnTypebutton2init(d[2].N,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIN));
  *d[3].N = b3;
  d[3].N->item = -1;
  ButnTypebutton3init(d[3].N,pt) ;
  d[4].t = (DIT *)malloc(sizeof(DIN));
  *d[4].N = b4;
  d[4].N->item = -1;
  ButnTypebutton4init(d[4].N,pt) ;
  d[5].t = (DIT *)malloc(sizeof(DIN));
  *d[5].N = b5;
  d[5].N->item = -1;
  ButnTypebutton5init(d[5].N,pt) ;
  d[6].t = (DIT *)malloc(sizeof(DIN));
  *d[6].N = b6;
  d[6].N->item = -1;
  ButnTypebutton6init(d[6].N,pt) ;
  d[7].t = (DIT *)malloc(sizeof(DIN));
  *d[7].N = b7;
  d[7].N->item = -1;
  ButnTypebutton7init(d[7].N,pt) ;
  d[8].t = (DIT *)malloc(sizeof(DIN));
  *d[8].N = b8;
  d[8].N->item = -1;
  ButnTypebutton8init(d[8].N,pt) ;
  d[9].t = (DIT *)malloc(sizeof(DIN));
  *d[9].N = b9;
  d[9].N->item = -1;
  ButnTypebutton9init(d[9].N,pt) ;
  d[10].t = (DIT *)malloc(sizeof(DIN));
  *d[10].N = b10;
  d[10].N->item = -1;
  ButnTypebutton10init(d[10].N,pt) ;
  d[11].t = (DIT *)malloc(sizeof(DIN));
  *d[11].N = b11;
  d[11].N->item = -1;
  ButnTypebutton11init(d[11].N,pt) ;
  d[12].t = (DIT *)malloc(sizeof(DIM));
  *d[12].m = m12;
  d[12].m->item = -1;
  d[13].t = (DIT *)malloc(sizeof(DII));
  *d[13].i = i13;
  d[13].i->item = -1;
  d[14].t = (DIT *)malloc(sizeof(DIL));
  *d[14].h = h14;
  d[14].h->item = -1;
  ButnTypesplbutton1init(d[14].h,pt) ;
  d[15].t = (DIT *)malloc(sizeof(DIM));
  *d[15].m = m15;
  d[15].m->item = -1;
  d[16].t = (DIT *)malloc(sizeof(DIM));
  *d[16].m = m16;
  d[16].m->item = -1;
  d[17].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeButnTypeGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = ButnTypeGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int ButnType( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = ButnTypeGroup(&D,v,pt);
#else 
  GrpId = MakeButnTypeGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 14;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 100;   /* Position of Dialog */ 
  D.yo = 200;
  D.xl = 404;    /*  Length of Dialog */
  D.yl = 417;    /*  Width  of Dialog */
  D.Initfun = ButnTypeinit;    /*   init fuction for Dialog */
  D.Cleanupfun = ButnTypecleanup;    /*   init fuction for Dialog */
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
  D.Callback = ButnTypeCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = ButnTypeResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = ButnTypeWaitCallBack;  /*  Wait callback */
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
//     if(parent != NULL) {D.xo=0;D.yo=0;}
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
  ModifyButnType(&D,GrpId);    /*  add extras to  gui*/
  ModifyButnTypeGc(&D);    /*  set colors for gui if don't like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
int kgGetButnType(void *arg,int *type) {
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
   int Btype=*type;
   pt = (void *)(&Btype);
   ButnType(arg,v,pt );
   *type = Btype;
   return Btype;
}
