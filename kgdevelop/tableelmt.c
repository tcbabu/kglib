#include <kulina.h>
#include "tableelmtCallbacks.h"
//#include "Gclrtableelmt.c"
extern DIALOG *Parent;

typedef struct _Tbstr {
        int index;
        int nx;
        int ny;
        int n;
        int *sw;
        int *Field;
        int *Type;
}TBSTR;
static int SetTbstr(TBSTR *e,DIT *T) {
	int i,j,k=0,nx,ny,ln;
	T_ELMT *elmt=T->elmt;
	char Code[3]={'d','F','s'};
	char ch;
	char *pt;
	nx = T->nx;
	ny = T->ny;
        e->index =0;
        e->nx = nx;
        e->ny = ny;
        e->n  = nx;
        e->Field =  (int *)malloc(sizeof(int)*nx);
        e->Type  =  (int *)malloc(sizeof(int)*nx);
        e->sw    =  (int *)malloc(sizeof(int)*nx);
        k = 0;
        for(i=0;i<nx;i++){
			ln = strlen(elmt[k].fmt);
                        ch = elmt[k].fmt[ln-1];
			if(ch == 'd') e->Type[k]= 0;
			else if(ch == 'F') e->Type[k]= 1;
    			     else  e->Type[k]= 2;
			elmt[k].fmt[ln-1]='\0';
			pt = strstr(elmt[k].fmt,"\%");
			sscanf(pt+1,"%d",e->Field+k);
			*pt='\0';
			if(elmt[k].sw==1) e->sw[k]  = 0;
			else e->sw[k]=1;
                        k++;
        }
        return 1;
}
static int InitTbstr(TBSTR *e,int nx,int ny) {
        int i,j,k=0;
        e->index =0;
        e->nx = nx;
        e->ny = ny;
        e->n  = nx;
        e->Field =  (int *)malloc(sizeof(int)*nx);
        e->Type  =  (int *)malloc(sizeof(int)*nx);
        e->sw    =  (int *)malloc(sizeof(int)*nx);
        k = 0;
        for(i=0;i<nx;i++){
                        e->Field[k]=10;
                        e->Type[k]= 2;
			e->sw[k]  = 0;
                        k++;
        }
        return 1;
}

int tableelmtGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  DIM m0 = { 
    'B',
    12,21,  
    525,47,  
    0,0  
  };
  strncpy(m0.msg,(char *)"!w32For Column : 0",499);
  strcpy(m0.Wid,(char *)"tableelmtMsg");
  m0.item = -1;
  T_ELMT *e1  ; 
  e1 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e1[0].fmt = (char *)malloc(25);
  strcpy(e1[0].fmt,(char *)"!w32Data Field Length%5d");
  e1[0].v=(void *)v[0];
  e1[0].sw=1;
  e1[0].noecho=0;
  e1[0].img=NULL;
  DIT t1 = { 
    't',
    129,71,  
    380,105,
    20, 
    1,1, 
    e1,
    1,1,
    NULL,tableelmttextbox1callback,1,0,18,9 /* args,Call back */
  };
  strcpy(t1.Wid,(char *)"tableelmtTbox");
  t1.pt=NULL;
  t1.type = 1;
  t1.item = -1;
  char *menu2[]  = { 
    (char *)"!w32Integer",
    (char *)"!w32Double",
    (char *)"!w32String",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r2 = { 
    'r',
    142,121,  
    530,158,   
    8,0,  
    110, 
    25, 
    1,3, 
    0,1, 
    (int *)v[1], 
    NULL, 
    NULL ,
    NULL,tableelmtbrowser1callback, /* *args, callback */
    2,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu2);
  r2.list=(void **)th0;
  strcpy(r2.Wid,(char *)"tableelmtRadio1");
  r2.item = -1;
  DIM m3 = { 
    'm',
    42,127,  
    142,151,  
    1,0  
  };
  strncpy(m3.msg,(char *)"!w32Data Type",499);
  strcpy(m3.Wid,(char *)"tableelmtWidget6");
  m3.item = -1;
  char *menu4[]  = { 
    (char *)"!w32Input and Output",
    (char *)"!w32Output only",
    NULL 
  };
  ThumbNail **th1 ;
  DIRA r4 = { 
    'r',
    144,171,  
    530,206,   
    8,0,  
    170, 
    25, 
    1,2, 
    0,1, 
    (int *)v[2], 
    NULL, 
    NULL ,
    NULL,tableelmtbrowser2callback, /* *args, callback */
    2,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu4);
  r4.list=(void **)th1;
  strcpy(r4.Wid,(char *)"tableelmtRadio2");
  r4.item = -1;
  DIM m5 = { 
    'm',
    8,176,  
    145,200,  
    1,0  
  };
  strncpy(m5.msg,(char *)"!w32Column Type",499);
  strcpy(m5.Wid,(char *)"tableelmtWidget9");
  m5.item = -1;
  BUT_STR  *butn6=NULL; 
  butn6= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn6[0].sw=1;
  strcpy(butn6[0].title,(char *)"!w32Previous");
  butn6[0].xpmn=NULL;
  butn6[0].xpmp=NULL;
  butn6[0].xpmh=NULL;
  butn6[0].bkgr=-240245255;
  butn6[0].butncode='';
  DIN b6 = { 
    'n',
    26,226,  
    120,260,
    2,2,  
    84, 
    24, 
    1,1, 
    7,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn6, 
    tableelmtbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b6.Wid,(char *)"tableelmtPrevious");
  b6.item = -1;
  BUT_STR  *butn7=NULL; 
  butn7= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn7[0].sw=1;
  strcpy(butn7[0].title,(char *)"!w32Next");
  butn7[0].xpmn=NULL;
  butn7[0].xpmp=NULL;
  butn7[0].xpmh=NULL;
  butn7[0].bkgr=-240245255;
  butn7[0].butncode='';
  DIN b7 = { 
    'n',
    426,226,  
    520,260,
    2,2,  
    84, 
    24, 
    1,1, 
    7,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn7, 
    tableelmtbutton2callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b7.Wid,(char *)"tableelmtNext");
  b7.item = -1;
  BUT_STR  *butn8=NULL; 
  butn8= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn8[0].sw=1;
  strcpy(butn8[0].title,(char *)"!w32Done");
  butn8[0].xpmn=NULL;
  butn8[0].xpmp=NULL;
  butn8[0].xpmh=NULL;
  butn8[0].bkgr=-235255250;
  butn8[0].butncode='';
  DIL h8 = { 
    'h',
    233,226,  
    315,259,
    2,0,  
    72, 
    25, 
    1,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn8, 
    tableelmtsplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h8.Wid,(char *)"tableelmtSbutn");
  h8.item = -1;
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
  tableelmtbrowser1init(d[2].r,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIM));
  *d[3].m = m3;
  d[3].m->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIRA));
  *d[4].r = r4;
  d[4].r->item = -1;
  tableelmtbrowser2init(d[4].r,pt) ;
  d[5].t = (DIT *)malloc(sizeof(DIM));
  *d[5].m = m5;
  d[5].m->item = -1;
  d[6].t = (DIT *)malloc(sizeof(DIN));
  *d[6].N = b6;
  d[6].N->item = -1;
  tableelmtbutton1init(d[6].N,pt) ;
  d[7].t = (DIT *)malloc(sizeof(DIN));
  *d[7].N = b7;
  d[7].N->item = -1;
  tableelmtbutton2init(d[7].N,pt) ;
  d[8].t = (DIT *)malloc(sizeof(DIL));
  *d[8].h = h8;
  d[8].h->item = -1;
  tableelmtsplbutton1init(d[8].h,pt) ;
  d[9].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MaketableelmtGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  1 data values
    RadioButtons1  1 data value
    RadioButtons2  1 data value

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
   void** v=(void **)malloc(sizeof(void*)*4);
   v[3]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = tableelmtGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   return GrpId;
}

int tableelmt( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=2107030000;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = tableelmtGroup(&D,v,pt);
#else 
  GrpId = MaketableelmtGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 8;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 727;   /* Position of Dialog */ 
  D.yo = 301;
  if(parent != Parent) {
	  if(parent != NULL) {
		  D.xo = 0; D.yo=150;
	  }
  }
  D.xl = 542;    /*  Length of Dialog */
  D.yl = 279;    /*  Width  of Dialog */
  D.Initfun = tableelmtinit;    /*   init fuction for Dialog */
  D.Cleanupfun = tableelmtcleanup;    /*   init fuction for Dialog */
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
  D.Callback = tableelmtCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = tableelmtResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = tableelmtWaitCallBack;  /*  Wait callback */
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
  Modifytableelmt(&D,GrpId);    /*  add extras to  gui*/
//  ModifytableelmtGc(&D);    /*  set colors for gui if don't like default*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *kgGetTableElements(void *arg,int nx,int ny) {
/*************************************************

    Text_Box1  1 data values
    RadioButtons1  1 data value
    RadioButtons2  1 data value

*************************************************/
   int i,j,k;
   T_ELMT *elmt;
   char Code[3]={'d','F','s'};
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   void* v[3];
   TBSTR e;
   InitTbstr(&e,nx,ny);
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v0 = e.Field[0];
   v1 = e.Type[0]+1;
   v2 = e.sw[0]+1;
   elmt = (T_ELMT*)malloc(sizeof(T_ELMT)*nx*ny);
   void *pt=&e; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   tableelmt(arg,v,pt );
   k=0;
   for(j=0;j<ny;j++) {
	   for(i=0;i<nx;i++) {
		   elmt[k].noecho=0;
		   elmt[k].img=NULL;
		   elmt[k].sw = (e.sw[i]+1)%2;
		   elmt[k].fmt = (char *)malloc(5);
		   sprintf(elmt[k].fmt,"%%%d%c",e.Field[i],Code[e.Type[i]]);
//		   printf(" %s ",elmt[k].fmt);
		   k++;
	   }
//	   printf("\n");
   }
   free(e.Field);
   free(e.Type);
   free(e.sw);
   return elmt;
}
void *kgEditTableElements(void *arg,void *Tmp) {
/*************************************************

    Text_Box1  1 data values
    RadioButtons1  1 data value
    RadioButtons2  1 data value

*************************************************/
   int i,j,k;
   DIT *T=(DIT *)Tmp;
   T_ELMT *elmt;
   char Code[3]={'d','F','s'};
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   void* v[3];
   TBSTR e;
   SetTbstr(&e,T);
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(&v2);
   v0 = e.Field[0];
   v1 = e.Type[0]+1;
   v2 = (e.sw[0]+1);
   elmt = T->elmt;
   void *pt=&e; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   tableelmt(arg,v,pt );
   k=0;
   for(j=0;j<T->ny;j++) {
	   for(i=0;i<T->nx;i++) {
		   elmt[k].noecho=0;
		   elmt[k].img=NULL;
		   elmt[k].sw = (e.sw[i]+1)%2;
		   elmt[k].fmt = (char *)malloc(5);
		   sprintf(elmt[k].fmt,"%%%d%c",e.Field[i],Code[e.Type[i]]);
//		   printf(" %s ",elmt[k].fmt);
		   k++;
	   }
//	   printf("\n");
   }
   free(e.Field);
   free(e.Type);
   free(e.sw);
   return elmt;
}
