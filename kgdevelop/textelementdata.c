#include <kulina.h>
#include "textelementdataCallbacks.h"
typedef struct _Estr {
	int index;
	int nx;
	int ny;
	int n;
	char **Prompt;
	int *sw;
	int *Field;
	int *Type;
	int *noecho;
}ESTR;
static int InitEstr(ESTR *e,int nx,int ny) {
	int i,j,k=0;
	e->index =0;
	e->nx = nx;
	e->ny = ny;
	e->n  = nx*ny;
	e->Prompt = (char **)malloc(sizeof(char *)*nx*ny);
	e->Field =  (int *)malloc(sizeof(int)*nx*ny);
	e->Type  =  (int *)malloc(sizeof(int)*nx*ny);
	e->sw    =  (int *)malloc(sizeof(int)*nx*ny);
	e->noecho    =  (int *)malloc(sizeof(int)*nx*ny);
	k = 0;
	for(j=0;j<ny;j++) {
		for(i=0;i<nx;i++){
			e->Prompt[k] = (char *)malloc(100);
			strcpy(e->Prompt[k],"");
			e->Field[k]=10;
			e->Type[k]= 2;
			e->sw[k]= 0;
			e->noecho[k]= 0;
			k++;
		}
	}
	return 1;
}
//#include "Gclrtextelementdata.c"

int textelementdataGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  DIM m0 = { 
    'B',
    10,11,  
    485,38,  
    0,0  
  };
  strncpy(m0.msg,(char *)"!w32!f21Text Box (1,1)",499);
  strcpy(m0.Wid,(char *)"elementMsg");
  m0.item = -1;
  T_ELMT *e1  ; 
  e1 =(T_ELMT *)malloc(sizeof(T_ELMT)*2);
  e1[0].fmt = (char *)malloc(19);
  strcpy(e1[0].fmt,(char *)"!w32!f21Prompt%30s");
  e1[0].v=(void *)v[0];
  e1[0].sw=1;
  e1[0].noecho=0;
  e1[0].img=NULL;
  e1[1].fmt = (char *)malloc(30);
  strcpy(e1[1].fmt,(char *)"!w32!f21Data Field Length%10d");
  e1[1].v=(void *)v[1];
  e1[1].sw=1;
  e1[1].noecho=0;
  e1[1].img=NULL;
  DIT t1 = { 
    't',
    8,51,  
    485,120,
    20, 
    1,2, 
    e1,
    1,1,
    NULL,textelementdatatextbox1callback,1,0,18,9 /* args,Call back */
  };
  strcpy(t1.Wid,(char *)"elementTbox");
  t1.pt=NULL;
  t1.type = 1;
  t1.item = -1;
  char *menu2[]  = { 
    (char *)"!w32!f21Integer",
    (char *)"!w32!f21Double",
    (char *)"!w32!f21String",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r2 = { 
    'r',
    130,136,  
    480,171,   
    8,0,  
    100, 
    25, 
    1,3, 
    0,1, 
    (int *)v[2], 
    NULL, 
    NULL ,
    NULL,textelementdatabrowser1callback, /* *args, callback */
    1,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu2);
  r2.list=(void **)th0;
  strcpy(r2.Wid,(char *)"elementRadio");
  r2.item = -1;
  DIM m3 = { 
    'm',
    30,141,  
    130,165,  
    1,0  
  };
  strncpy(m3.msg,(char *)"!w32!f21Data type",499);
  strcpy(m3.Wid,(char *)"textelementdataWidget5");
  m3.item = -1;
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"!w32!f21Finish");
  butn4[0].xpmn=NULL;
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-235255250;
  butn4[0].butncode='';
  DIL h4 = { 
    'h',
    196,259,  
    290,292,
    2,0,  
    84, 
    25, 
    1,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn4, 
    textelementdatasplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h4.Wid,(char *)"elementFinish");
  h4.item = -1;
  BUT_STR  *butn5=NULL; 
  butn5= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn5[0].sw=1;
  strcpy(butn5[0].title,(char *)"!w32!f21Previous");
  butn5[0].xpmn=NULL;
  butn5[0].xpmp=NULL;
  butn5[0].xpmh=NULL;
  butn5[0].bkgr=-240245255;
  butn5[0].butncode='';
  DIN b5 = { 
    'n',
    11,259,  
    105,293,
    2,2,  
    84, 
    24, 
    1,1, 
    7,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn5, 
    textelementdatabutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b5.Wid,(char *)"elementPrevious");
  b5.item = -1;
  BUT_STR  *butn6=NULL; 
  butn6= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn6[0].sw=1;
  strcpy(butn6[0].title,(char *)"!w32!f21Next");
  butn6[0].xpmn=NULL;
  butn6[0].xpmp=NULL;
  butn6[0].xpmh=NULL;
  butn6[0].bkgr=-240245255;
  butn6[0].butncode='';
  DIN b6 = { 
    'n',
    386,258,  
    480,292,
    2,2,  
    84, 
    24, 
    1,1, 
    7,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn6, 
    textelementdatabutton2callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b6.Wid,(char *)"elementNext");
  b6.item = -1;
  char *menu7[]  = { 
    (char *)"!w32Yes",
    (char *)"!w32No",
    NULL 
  };
  ThumbNail **th1 ;
  DIRA r7 = { 
    'r',
    132,192,  
    352,227,   
    8,0,  
    90, 
    25, 
    1,2, 
    0,1, 
    (int *)v[3], 
    NULL, 
    NULL ,
    NULL,textelementdatabrowser2callback, /* *args, callback */
    1,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu7);
  r7.list=(void **)th1;
  strcpy(r7.Wid,(char *)"elementRadio2");
  r7.item = -1;
  DIM m8 = { 
    'm',
    31,197,  
    131,221,  
    1,0  
  };
  strncpy(m8.msg,(char *)"!w32Echo",499);
  strcpy(m8.Wid,(char *)"textelementdataWidget9");
  m8.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+10));
  d =dtmp+i; 
  d[9].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIM));
  *d[0].m = m0;
  d[0].m->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIT));
  *d[1].t = t1;
  d[1].t->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIRA));
  *d[2].r = r2;
  d[2].r->item = -1;
  textelementdatabrowser1init(d[2].r,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIM));
  *d[3].m = m3;
  d[3].m->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIL));
  *d[4].h = h4;
  d[4].h->item = -1;
  textelementdatasplbutton1init(d[4].h,pt) ;
  d[5].t = (DIT *)malloc(sizeof(DIN));
  *d[5].N = b5;
  d[5].N->item = -1;
  textelementdatabutton1init(d[5].N,pt) ;
  d[6].t = (DIT *)malloc(sizeof(DIN));
  *d[6].N = b6;
  d[6].N->item = -1;
  textelementdatabutton2init(d[6].N,pt) ;
  d[7].t = (DIT *)malloc(sizeof(DIRA));
  *d[7].r = r7;
  d[7].r->item = -1;
  textelementdatabrowser2init(d[7].r,pt) ;
  d[8].t = (DIT *)malloc(sizeof(DIM));
  *d[8].m = m8;
  d[8].m->item = -1;
  d[9].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 
/* One can also use the following code to add Widgets to an existing Dialog */

int MaketextelementdataGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  2 data values
    RadioButtons1  1 data value

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
   GrpId = textelementdataGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int textelementdata( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = textelementdataGroup(&D,v,pt);
#else 
  GrpId = MaketextelementdataGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 6;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 667;   /* Position of Dialog */ 
  D.yo = 162;
  D.xl = 495;    /*  Length of Dialog */
  D.yl = 298;    /*  Width  of Dialog */
  D.Initfun = textelementdatainit;    /*   init fuction for Dialog */
  D.Cleanupfun = textelementdatacleanup;    /*   init fuction for Dialog */
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
  D.Callback = textelementdataCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = textelementdataResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = textelementdataWaitCallBack;  /*  Wait callback */
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
  Modifytextelementdata(&D,GrpId);    /*  add extras to  gui*/
//  ModifytextelementdataGc(&D);    /*  set colors for gui if don't like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
//void *Runtextelementdata(void *arg,int nx,int ny) {
void *kgGetTextElmts (void *arg,int nx,int ny) {
/*************************************************

    Text_Box1  2 data values
    RadioButtons1  1 data value

*************************************************/
   int i,j,k;
   char Code[3]={'d','F','s'};
   char  v0[500]="" ;
   int   v1 = 10;
   int   v2 = 2;
   int   v3 = 1;
   void* v[4];
   T_ELMT *elmt;
   ESTR e;
   InitEstr(&e,nx,ny);
   v[0]=(void *)(v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v[3]=(void *)(&v3);
   v2=3;
   void *pt=&e; /* pointer to send any extra information */
   textelementdata(arg,v,pt );
   elmt = (T_ELMT *)malloc(sizeof(T_ELMT)*nx*ny);
   for(k=0;k<(nx*ny);k++) {
	   sprintf(v0,"%-s%%%d%c",e.Prompt[k],e.Field[k],Code[e.Type[k]]);
           free(e.Prompt[k]);
	   e.Prompt[k] = (char *)malloc(strlen(v0)+1);
	   strcpy(e.Prompt[k],v0);
	   elmt[k].noecho=e.noecho[k];
           elmt[k].img=NULL;
           elmt[k].sw = (e.sw[k]+1)%2;
           elmt[k].fmt = e.Prompt[k];
   }
   free(e.Field);
   free(e.Type);
   free(e.sw);
   return elmt;
}
