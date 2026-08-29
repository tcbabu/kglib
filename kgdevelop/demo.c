#include <kulina.h>
#include "demoCallbacks.h"
#include "Gclrdemo.c"
int demoGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  BUT_STR  *butn0=NULL; 
  butn0= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn0[0].sw=1;
  strcpy(butn0[0].title,(char *)"!c15Spl butn(Done)");
  butn0[0].xpmn=NULL;
  butn0[0].xpmp=NULL;
  butn0[0].xpmh=NULL;
  butn0[0].bkgr=-118000;
  butn0[0].butncode=31;
  DIL h0 = { 
    'h',
    658,747,  
    787,774,
    2,0,  
    120, 
    25, 
    1,1, 
    2,0.500000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn0, 
    demodemoSplbuttoncallback ,  /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(h0.Wid,(char *)"demoSplbutton");
  h0.item = -1;
  BUT_STR  *butn1=NULL; 
  butn1= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn1[0].sw=1;
  strcpy(butn1[0].title,(char *)"but type0");
  butn1[0].xpmn=NULL;
  butn1[0].xpmp=NULL;
  butn1[0].xpmh=NULL;
  butn1[0].bkgr=-1;
  butn1[0].butncode=31;
  DIN b1 = { 
    'n',
    11,14,  
    89,87,
    2,20,  
    64, 
    44, 
    1,1, 
    0,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn1, 
    demodemoButton0callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b1.Wid,(char *)"demoButton0");
  b1.item = -1;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"but type2");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-1;
  butn2[0].butncode=-2302850;
  DIN b2 = { 
    'n',
    16,161,  
    90,235,
    2,2,  
    64, 
    64, 
    1,1, 
    2,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn2, 
    demodemoButton2callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b2.Wid,(char *)"demoButton2");
  b2.item = -1;
  BUT_STR  *butn3=NULL; 
  butn3= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn3[0].sw=1;
  strcpy(butn3[0].title,(char *)"but type1");
  butn3[0].xpmn=NULL;
  butn3[0].xpmp=NULL;
  butn3[0].xpmh=NULL;
  butn3[0].bkgr=-1;
  butn3[0].butncode=-1077952642;
  DIN b3 = { 
    'n',
    16,87,  
    90,161,
    2,2,  
    64, 
    64, 
    1,1, 
    1,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn3, 
    demodemoButton1callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b3.Wid,(char *)"demoButton1");
  b3.item = -1;
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"but type3");
  butn4[0].xpmn=NULL;
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-1;
  butn4[0].butncode=126;
  DIN b4 = { 
    'n',
    16,235,  
    90,309,
    2,2,  
    64, 
    64, 
    1,1, 
    3,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn4, 
    demodemoButton3callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b4.Wid,(char *)"demoButton3");
  b4.item = -1;
  BUT_STR  *butn5=NULL; 
  butn5= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn5[0].sw=1;
  strcpy(butn5[0].title,(char *)"but type4");
  butn5[0].xpmn=NULL;
  butn5[0].xpmp=NULL;
  butn5[0].xpmh=NULL;
  butn5[0].bkgr=-1;
  butn5[0].butncode=126;
  DIN b5 = { 
    'n',
    16,309,  
    90,383,
    2,2,  
    64, 
    64, 
    1,1, 
    4,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn5, 
    demodemoButton4callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b5.Wid,(char *)"demoButton4");
  b5.item = -1;
  BUT_STR  *butn6=NULL; 
  butn6= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn6[0].sw=1;
  strcpy(butn6[0].title,(char *)"Folder");
  butn6[0].xpmn=NULL;
  butn6[0].xpmp=NULL;
  butn6[0].xpmh=NULL;
  butn6[0].bkgr=-1;
  butn6[0].butncode=11046014;
  DIN b6 = { 
    'n',
    768,551,  
    990,580,
    2,2,  
    210, 
    20, 
    1,1, 
    7,0.500000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn6, 
    demodemoFoldercallback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b6.Wid,(char *)"demoFolder");
  b6.item = -1;
  BUT_STR  *butn7=NULL; 
  butn7= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn7[0].sw=1;
  strcpy(butn7[0].title,(char *)"but type6");
  butn7[0].xpmn=NULL;
  butn7[0].xpmp=NULL;
  butn7[0].xpmh=NULL;
  butn7[0].bkgr=-1;
  butn7[0].butncode=46838654;
  DIN b7 = { 
    'n',
    93,14,  
    167,88,
    2,2,  
    64, 
    64, 
    1,1, 
    6,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn7, 
    demodemoButton6callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b7.Wid,(char *)"demoButton6");
  b7.item = -1;
  BUT_STR  *butn8=NULL; 
  butn8= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn8[0].sw=1;
  strcpy(butn8[0].title,(char *)"but type7");
  butn8[0].xpmn=NULL;
  butn8[0].xpmp=NULL;
  butn8[0].xpmh=NULL;
  butn8[0].bkgr=-1;
  butn8[0].butncode=-2302850;
  DIN b8 = { 
    'n',
    94,90,  
    168,164,
    2,2,  
    64, 
    64, 
    1,1, 
    7,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn8, 
    demodemoButton7callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b8.Wid,(char *)"demoButton7");
  b8.item = -1;
  BUT_STR  *butn9=NULL; 
  butn9= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn9[0].sw=1;
  strcpy(butn9[0].title,(char *)"but type8");
  butn9[0].xpmn=NULL;
  butn9[0].xpmp=NULL;
  butn9[0].xpmh=NULL;
  butn9[0].bkgr=-1;
  butn9[0].butncode=-2302850;
  DIN b9 = { 
    'n',
    95,166,  
    169,240,
    2,2,  
    64, 
    64, 
    1,1, 
    8,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn9, 
    demodemoButton8callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b9.Wid,(char *)"demoButton8");
  b9.item = -1;
  BUT_STR  *butn10=NULL; 
  butn10= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn10[0].sw=1;
  strcpy(butn10[0].title,(char *)"but type9");
  butn10[0].xpmn=NULL;
  butn10[0].xpmp=NULL;
  butn10[0].xpmh=NULL;
  butn10[0].bkgr=-1;
  butn10[0].butncode=-2302850;
  DIN b10 = { 
    'n',
    96,243,  
    170,317,
    2,2,  
    64, 
    64, 
    1,1, 
    9,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn10, 
    demodemoButton9callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b10.Wid,(char *)"demoButton9");
  b10.item = -1;
  BUT_STR  *butn11=NULL; 
  butn11= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn11[0].sw=1;
  strcpy(butn11[0].title,(char *)"(tpe10 hidden)");
  butn11[0].xpmn=NULL;
  butn11[0].xpmp=NULL;
  butn11[0].xpmh=NULL;
  butn11[0].bkgr=-1;
  butn11[0].butncode=-2302850;
  DIN b11 = { 
    'n',
    91,322,  
    171,393,
    2,2,  
    64, 
    64, 
    1,1, 
    10,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn11, 
    demodemoButton10callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b11.Wid,(char *)"demoButton10");
  b11.item = -1;
  char **menu12 ; 
  menu12= (char **)malloc(sizeof(char *)*4);
  menu12[3]=NULL;
  menu12[0]=(char *)malloc(7);
  strcpy(menu12[0],(char *)"Resize");
  menu12[1]=(char *)malloc(9);
  strcpy(menu12[1],(char *)"Original");
  menu12[2]=(char *)malloc(10);
  strcpy(menu12[2],(char *)"Half Size");
  char *prompt12 ; 
  prompt12=(char *)malloc(1);
  strcpy(prompt12,(char *)"");
  DIW w12 = { 
    'w',
    45,503,  
    184,529,   
    3,  
    (int *)v[0],
    prompt12 ,
    menu12 ,
    NULL,demodemoPulldowncallback , /* *args, Callback  */
    0 
  };
  strcpy(w12.Wid,(char *)"demoPulldown");
  w12.item = -1;
  T_ELMT *e13  ; 
  e13 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e13[0].fmt = (char *)malloc(16);
  strcpy(e13[0].fmt,(char *)"Transparency%3d");
  e13[0].v=(void *)v[1];
  e13[0].sw=1;
  e13[0].noecho=0;
  e13[0].img=NULL;
  DIT t13 = { 
    't',
    6,472,  
    189,501,
    20, 
    1,1, 
    e13,
    1,1,
    NULL,demodemoTextboxcallback ,1 ,0,18,9 
  };
    /* *args,Callback,border,hide,font,fontsize */
  strcpy(t13.Wid,(char *)"demoTextbox");
  t13.pt=NULL;
  t13.type = 0;
  t13.item = -1;
  T_ELMT *e14  ; 
  e14 =(T_ELMT *)malloc(sizeof(T_ELMT)*6);
  e14[0].fmt = (char *)malloc(5);
  strcpy(e14[0].fmt,(char *)"%10F");
  e14[0].v=(void *)v[2];
  e14[0].sw=1;
  e14[0].noecho=0;
  e14[0].img=NULL;
  e14[1].fmt = (char *)malloc(5);
  strcpy(e14[1].fmt,(char *)"%10F");
  e14[1].v=(void *)v[3];
  e14[1].sw=1;
  e14[1].noecho=0;
  e14[1].img=NULL;
  e14[2].fmt = (char *)malloc(5);
  strcpy(e14[2].fmt,(char *)"%10F");
  e14[2].v=(void *)v[4];
  e14[2].sw=0;
  e14[2].noecho=0;
  e14[2].img=NULL;
   int Count14= 5;
   for(int j=1;j<2;j++) {
     for(int i=0;i<3;i++) {
       e14[j*3+i].fmt = (char *)malloc(strlen(e14[i].fmt)+1);
       strcpy(e14[(j)*3+i].fmt, e14[i].fmt);
       e14[(j)*3+i].v = (void *)v[Count14+(j-1)*3+i];
       e14[(j)*3+i].sw = e14[i].sw;
       e14[(j)*3+i].noecho = e14[i].noecho;
       e14[(j)*3+i].img = NULL;
     }
   }
  DIT T14 = { 
    'T',
    543,438,  
    915,495,
    26, 
    3,2, 
    e14,
    1,1,
    NULL,demodemoTablecallback , /* *args, Callback  */ 
    1,0,18,9
   };
  strcpy(T14.Wid,(char *)"demoTable");
  T14.pt=NULL;
  T14.type = 0;
  T14.item = -1;
  DID d15 = { 
    'd',
    747,500,  
    898,546,   
    0,100,  
    101,  
    (int *)v[8],
    NULL,
    NULL,demodemoDslidecallback /* *args, Callback  */
  };
  strcpy(d15.Wid,(char *)"demoDslide");
  d15.item = -1;
  DIF f16 = { 
    'f',
    584,500,  
    730,548,   
    1.000000,100.000000,  
    100,  
    (double *)v[9],
    NULL,
    NULL,demodemoFslidecallback /* *args, Callback  */
  };
  strcpy(f16.Wid,(char *)"demoFslide");
  f16.item = -1;
  char *xpm17=   NULL; /* pixmap info */ 
  DIP p17 = { 
    'p',
    29,532,  
    305,702,  
    (void *)xpm17,
    -1, /* bkgr colour */ 
      3,0,0.000000 /* border hide transparency*/ 
  };
  strcpy(p17.Wid,(char *)"demoImagebox");
  p17.item = -1;
  char *xpm18=   NULL; /* pixmap info */ 
  DIG g18 = { 
    'g',
    196,22,  
    944,428,  
    (void *)xpm18,
    0, /* bkgr colour */ 
    demodemoGboxinit, /* void *initgraph(int,void *)  */ 
    NULL,0,0 /* *data border hide*/
  };
  strcpy(g18.Wid,(char *)"demoGbox");
  g18.item = -1;
  DII i19 = { 
    'i',
    949,8,  
    1401,256,  
    49,11,0   
  };
  strcpy(i19.Wid,(char *)"demoIbox");
  i19.item = -1;
  DIM m20 = { 
    'm',
    347,501,  
    423,525,  
    1,0  
  };
  strncpy(m20.msg,(char *)"Message",499);
  strcpy(m20.Wid,(char *)"demoMessage");
  m20.item = -1;
  DIM m21 = { 
    'M',
    356,526,  
    527,567,  
    0,0  
  };
  strncpy(m21.msg,(char *)" Hellow",499);
  strcpy(m21.Wid,(char *)"demoSplash");
  m21.item = -1;
  char **menu22 ; 
  menu22= (char **)malloc(sizeof(char *)*7);
  menu22[6]=NULL;
  menu22[0]=(char *)malloc(4);
  strcpy(menu22[0],(char *)"one");
  menu22[1]=(char *)malloc(4);
  strcpy(menu22[1],(char *)"two");
  menu22[2]=(char *)malloc(6);
  strcpy(menu22[2],(char *)"three");
  menu22[3]=(char *)malloc(5);
  strcpy(menu22[3],(char *)"four");
  menu22[4]=(char *)malloc(5);
  strcpy(menu22[4],(char *)"five");
  menu22[5]=(char *)malloc(4);
  strcpy(menu22[5],(char *)"six");
  DIE e22 = { 
    'e',
    310,580,  
    465,731,   
    6,  
    (int *)v[10],
    NULL,
    menu22 ,
    NULL,demodemoEboxcallback , /* *args, Callback  */
    20,6,22,1,1,1,0 
  };
  strcpy(e22.Wid,(char *)"demoEbox");
  e22.item = -1;
  DIS s23 = { 
    's',
    951,259,  
    1400,464,   
    9,  
    NULL,
    NULL,
    NULL ,
    NULL,NULL, /* *args, Callback*/
    20,6,22,1,1,1,0
//     line width,offset (not used),scroll width,highlight item(not used)
//     border on/off,bkgr on/off,hide on/off
//     uses Gclr items: msg_fill,msg_char,msg_bodr,scroll_fill,scroll_dim,scroll_vbright)
  };
  strcpy(s23.Wid,(char *)"demoMsgscroll");
  s23.item = -1;
  DIHB d24 = { 
    'P',
    91,427,  
    262,454,   
    0,100,  
    133,  
    (int *)v[11],
    NULL,
    NULL,demodemoHBslidecallback , /* *args, Callback  */
    0,0,2,-1, /* bordr,hide,type,color */
  };
  strcpy(d24.Wid,(char *)"demoHBslide");
  d24.item = -1;
  DIX x25 = { 
    'x',
    611,581,  
    993,731,   
    10,2,  
    160, 
    25, 
    1,82395408, 
    0,5, 
    (int *)v[12], 
    NULL, 
    NULL, 
    NULL,demodemoXboxcallback , /* *args, Callback  */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /*=1 hide  */
   };
  strcpy(x25.Wid,(char *)"demoXbox");
  x25.item = -1;
  char *menu26[]  = { 
    (char *)"Zoom",
    (char *)"Review",
    (char *)"Antialias",
    (char *)"Save as Png",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r26 = { 
    'r',
    467,582,  
    610,730,   
    8,0,  
    90, 
    25, 
    1,4, 
    0,4, 
    (int *)v[13], 
    NULL, 
    NULL ,
    NULL,demodemoRadiocallback , /* *args, Callback  */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /*=1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu26);
  r26.list=(void **)th0;
  strcpy(r26.Wid,(char *)"demoRadio");
  r26.item = -1;
  char *menu27[]  = { 
    (char *)"Merge",
    (char *)"Appy Transparency",
    NULL 
  };
  ThumbNail **th1 ;
  DICH c27 = { 
    'c',
    189,456,  
    345,532,   
    8,0,  
    90, 
    25, 
    1,2, 
    0,2, 
    (int *)v[14], 
    NULL, 
    NULL, 
    NULL,demodempChboxcallback , /* *args, Callback  */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /*=1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu27);
  c27.list=(void **)th1;
  strcpy(c27.Wid,(char *)"dempChbox");
  c27.item = -1;
  DIY y28 = { 
    'y',
    991,476,  
    1400,732,   
    8,20,  
    64, 
    64, 
    1,82395408, 
    0,1, 
    (int *)v[15], 
    NULL, 
    NULL, 
    NULL,demodemoYboxcallback ,  /* *args, Callback  */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /*=1 hide  */
   };
  strcpy(y28.Wid,(char *)"demoYbox");
  y28.item = -1;
  DIO o29 = { 
    'o',
    263,432,  
    467,452,  
    0,50,0,0,-1,0  
       //hide,percent,border,type,color,direction 
  };
  strcpy(o29.Wid,(char *)"demoProgrss");
  o29.item = -1;
  DIV v30 = { 
    'v',
    10,527,  
    30,731,  
    0,  
    100.000000,0.000000,5.000000,  
    NULL,demodemoVbarcallback /* *args, Callback  */
  };
  strcpy(v30.Wid,(char *)"demoVbar");
  v30.item = -1;
  DIZ z31 = { 
    'z',
    30,710,  
    310,732,  
    0,  
    100.000000,0.000000,5.000000,  
    NULL,demodemoHbarcallback /* *args, Callback  */
  };
  strcpy(z31.Wid,(char *)"demoHbar");
  z31.item = -1;
  DIM m32 = { 
    'B',
    424,501,  
    524,525,  
    0,0  
  };
  strncpy(m32.msg,(char *)"Message Box(B)",499);
  strcpy(m32.Wid,(char *)"demoBmessage");
  m32.item = -1;
  BUT_STR  *butn33=NULL; 
  butn33= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn33[0].sw=1;
  strcpy(butn33[0].title,(char *)"but type5");
  butn33[0].xpmn=NULL;
  butn33[0].xpmp=NULL;
  butn33[0].xpmh=NULL;
  butn33[0].bkgr=-1;
  butn33[0].butncode=11645054;
  DIN b33 = { 
    'n',
    15,383,  
    89,457,
    2,2,  
    64, 
    64, 
    1,1, 
    5,0.150000,0,0,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn33, 
    demodemoButton5callback , /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(b33.Wid,(char *)"demoButton5");
  b33.item = -1;
  DIM m34 = { 
    'm',
    91,396,  
    191,420,  
    0,0  
  };
  strncpy(m34.msg,(char *)"(type10 hidden)",499);
  strcpy(m34.Wid,(char *)"demoMsg10");
  m34.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+36));
  d =dtmp+i; 
  d[35].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIL));
  *d[0].h = h0;
  d[0].h->item = -1;
  demodemoSplbuttoninit(d[0].h,pt) ;
  d[1].t = (DIT *)malloc(sizeof(DIN));
  *d[1].N = b1;
  d[1].N->item = -1;
  demodemoButton0init(d[1].N,pt) ;
  d[2].t = (DIT *)malloc(sizeof(DIN));
  *d[2].N = b2;
  d[2].N->item = -1;
  demodemoButton2init(d[2].N,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIN));
  *d[3].N = b3;
  d[3].N->item = -1;
  demodemoButton1init(d[3].N,pt) ;
  d[4].t = (DIT *)malloc(sizeof(DIN));
  *d[4].N = b4;
  d[4].N->item = -1;
  demodemoButton3init(d[4].N,pt) ;
  d[5].t = (DIT *)malloc(sizeof(DIN));
  *d[5].N = b5;
  d[5].N->item = -1;
  demodemoButton4init(d[5].N,pt) ;
  d[6].t = (DIT *)malloc(sizeof(DIN));
  *d[6].N = b6;
  d[6].N->item = -1;
  demodemoFolderinit(d[6].N,pt) ;
  d[7].t = (DIT *)malloc(sizeof(DIN));
  *d[7].N = b7;
  d[7].N->item = -1;
  demodemoButton6init(d[7].N,pt) ;
  d[8].t = (DIT *)malloc(sizeof(DIN));
  *d[8].N = b8;
  d[8].N->item = -1;
  demodemoButton7init(d[8].N,pt) ;
  d[9].t = (DIT *)malloc(sizeof(DIN));
  *d[9].N = b9;
  d[9].N->item = -1;
  demodemoButton8init(d[9].N,pt) ;
  d[10].t = (DIT *)malloc(sizeof(DIN));
  *d[10].N = b10;
  d[10].N->item = -1;
  demodemoButton9init(d[10].N,pt) ;
  d[11].t = (DIT *)malloc(sizeof(DIN));
  *d[11].N = b11;
  d[11].N->item = -1;
  demodemoButton10init(d[11].N,pt) ;
  d[12].t = (DIT *)malloc(sizeof(DIW));
  *d[12].w = w12;
  d[12].w->item = -1;
  d[13].t = (DIT *)malloc(sizeof(DIT));
  *d[13].t = t13;
  d[13].t->item = -1;
  d[14].t = (DIT *)malloc(sizeof(DIT));
  *d[14].t = T14;
  d[14].t->item = -1;
  d[15].t = (DIT *)malloc(sizeof(DID));
  *d[15].d = d15;
  d[15].d->item = -1;
  d[16].t = (DIT *)malloc(sizeof(DIF));
  *d[16].f = f16;
  d[16].f->item = -1;
  d[17].t = (DIT *)malloc(sizeof(DIP));
  *d[17].p = p17;
  d[17].p->item = -1;
  d[18].t = (DIT *)malloc(sizeof(DIG));
  *d[18].g = g18;
  d[18].g->item = -1;
  d[19].t = (DIT *)malloc(sizeof(DII));
  *d[19].i = i19;
  d[19].i->item = -1;
  d[20].t = (DIT *)malloc(sizeof(DIM));
  *d[20].m = m20;
  d[20].m->item = -1;
  d[21].t = (DIT *)malloc(sizeof(DIM));
  *d[21].m = m21;
  d[21].m->item = -1;
  d[22].t = (DIT *)malloc(sizeof(DIE));
  *d[22].e = e22;
  d[22].e->item = -1;
  demodemoEboxinit(d[22].e,pt) ;
  d[23].t = (DIT *)malloc(sizeof(DIS));
  *d[23].s = s23;
  d[23].s->item = -1;
  demodemoMsgscrollinit(d[23].s,pt) ;
  d[24].t = (DIT *)malloc(sizeof(DIHB));
  *d[24].B = d24;
  d[24].B->item = -1;
  d[25].t = (DIT *)malloc(sizeof(DIX));
  *d[25].x = x25;
  d[25].x->item = -1;
  demodemoXboxinit(d[25].x,pt) ;
  d[26].t = (DIT *)malloc(sizeof(DIRA));
  *d[26].r = r26;
  d[26].r->item = -1;
  demodemoRadioinit(d[26].r,pt) ;
  d[27].t = (DIT *)malloc(sizeof(DICH));
  *d[27].c = c27;
  d[27].c->item = -1;
  demodempChboxinit(d[27].c,pt) ;
  d[28].t = (DIT *)malloc(sizeof(DIY));
  *d[28].y = y28;
  d[28].y->item = -1;
  demodemoYboxinit(d[28].y,pt) ;
  d[29].t = (DIT *)malloc(sizeof(DIO));
  *d[29].o = o29;
  d[29].o->item = -1;
  d[30].t = (DIT *)malloc(sizeof(DIV));
  *d[30].v = v30;
  d[30].v->item = -1;
  d[31].t = (DIT *)malloc(sizeof(DIZ));
  *d[31].z = z31;
  d[31].z->item = -1;
  d[32].t = (DIT *)malloc(sizeof(DIM));
  *d[32].m = m32;
  d[32].m->item = -1;
  d[33].t = (DIT *)malloc(sizeof(DIN));
  *d[33].N = b33;
  d[33].N->item = -1;
  demodemoButton5init(d[33].N,pt) ;
  d[34].t = (DIT *)malloc(sizeof(DIM));
  *d[34].m = m34;
  d[34].m->item = -1;
  d[35].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakedemoGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Browser1  1 data value
    Text_Box1  1 data values
    TableBox1  6 data values
    Integerslidebar1  1 data value
    Floatslidebar1  1 data value
    Scrollmenu2  1 data value
    Integerslidebar2  1 data value
    Selectmenu3  1 data value
    RadioButtons4  1 data value
    CheckBox5  1 data value
    ThumbnailBrowser6  1 data value

*************************************************/
   int  *v0 ;
   v0 = (int *)malloc(sizeof(int));
   *v0 = 1;
   int  *v1 ;
   v1 = (int *)malloc(sizeof(int));
   *v1 = 1;
   double *v2 ;
   v2 = (double *)malloc(sizeof(double));
   *v2 = 0.0;
   double *v3 ;
   v3 = (double *)malloc(sizeof(double));
   *v3 = 0.0;
   double *v4 ;
   v4 = (double *)malloc(sizeof(double));
   *v4 = 0.0;
   double *v5 ;
   v5 = (double *)malloc(sizeof(double));
   *v5 = 0.0;
   double *v6 ;
   v6 = (double *)malloc(sizeof(double));
   *v6 = 0.0;
   double *v7 ;
   v7 = (double *)malloc(sizeof(double));
   *v7 = 0.0;
   int  *v8 ;
   v8 = (int *)malloc(sizeof(int));
   *v8 = 1;
   double *v9 ;
   v9 = (double *)malloc(sizeof(double));
   *v9 = 0.0;
   int  *v10 ;
   v10 = (int *)malloc(sizeof(int));
   *v10 = 1;
   int  *v11 ;
   v11 = (int *)malloc(sizeof(int));
   *v11 = 1;
   int  *v12 ;
   v12 = (int *)malloc(sizeof(int));
   *v12 = 1;
   int  *v13 ;
   v13 = (int *)malloc(sizeof(int));
   *v13 = 1;
   int  *v14 ;
   v14 = (int *)malloc(sizeof(int));
   *v14 = 1;
   int  *v15 ;
   v15 = (int *)malloc(sizeof(int));
   *v15 = 1;
   void** v=(void **)malloc(sizeof(void*)*17);
   v[16]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(v4);
   v[5]=(void *)(v5);
   v[6]=(void *)(v6);
   v[7]=(void *)(v7);
   v[8]=(void *)(v8);
   v[9]=(void *)(v9);
   v[10]=(void *)(v10);
   v[11]=(void *)(v11);
   v[12]=(void *)(v12);
   v[13]=(void *)(v13);
   v[14]=(void *)(v14);
   v[15]=(void *)(v15);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = demoGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   demoSetup(D,Gpt->arg);
   return GrpId;
}

int demo( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = demoGroup(&D,v,pt);
#else 
  GrpId = MakedemoGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 2;
  D.df = 33;
  D.tw = 4;
  D.bw = 46;
  D.lw = 4;
  D.rw = 4;
  D.xo = 403;   /* Position of Dialog */ 
  D.yo = 65;
  D.xl = 1412;    /*  Length of Dialog */
  D.yl = 786;    /*  Width  of Dialog */
  D.Initfun = demoinit;    /*   init fuction for Dialog */
  D.Cleanupfun = democleanup;    /*   cleanup fuction for Dialog */
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
  D.Callback = demoCallBack;    /*  default Callback  */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = demoResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = demoWaitCallBack;  /*  Wait callback */
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
  ModifydemoGc(&D);    /*  set colors for gui if do not like default*/
  Modifydemo(&D,GrpId);    /*  add extras to  gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Rundemo(void *parent ,void *args) {
/*************************************************

    Browser1  1 data value
    Text_Box1  1 data values
    TableBox1  6 data values
    Integerslidebar1  1 data value
    Floatslidebar1  1 data value
    Scrollmenu2  1 data value
    Integerslidebar2  1 data value
    Selectmenu3  1 data value
    RadioButtons4  1 data value
    CheckBox5  1 data value
    ThumbnailBrowser6  1 data value

*************************************************/
   int   v0 = 1;
   int   v1 = 1;
   double v2 = 0.0;
   double v3 = 0.0;
   double v4 = 0.0;
   double v5 = 0.0;
   double v6 = 0.0;
   double v7 = 0.0;
   int   v8 = 1;
   double v9 = 0.0;
   int   v10 = 1;
   int   v11 = 1;
   int   v12 = 1;
   int   v13 = 1;
   int   v14 = 1;
   int   v15 = 1;
   void* v[16];
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(&v3);
   v[4]=(void *)(&v4);
   v[5]=(void *)(&v5);
   v[6]=(void *)(&v6);
   v[7]=(void *)(&v7);
   v[8]=(void *)(&v8);
   v[9]=(void *)(&v9);
   v[10]=(void *)(&v10);
   v[11]=(void *)(&v11);
   v[12]=(void *)(&v12);
   v[13]=(void *)(&v13);
   v[14]=(void *)(&v14);
   v[15]=(void *)(&v15);
   void *pt[2]={NULL,NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   pt[0]=args;
   demo(parent,v,(void *)pt );
   return pt[1];
}
