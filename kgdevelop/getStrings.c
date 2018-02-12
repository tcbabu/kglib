#include <kulina.h>
int  getStringstextbox1callback(int key,int i,void *Tmp) {
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  getStringshoribar1callback(int key,int i,void *Tmp) {
  DIALOG *D;DILN *B; 
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  B = (DILN *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(key) {
    case 1: 
      break;
  }
  return ret;
}
int getStringsinit(void *Tmp) {
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int getStringsCallBack(void *Tmp,void *tmp) {
  int ret = 0;
  DIALOG *D;
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
void ModifygetStringsGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int getStrings( void *parent,void **v,int id) {
  int n=0,k=0,yextra=0;
  int ret=1;
  DIALOG D;
  DIA d[3];
  T_ELMT *e0;
  DIT t0 = { 
    't',
    11,10,  
    451,44,
    20, 
    1,1, 
    NULL,
    1,1,
    NULL,getStringstextbox1callback /* args,Call back */
  };
  int butn1 =1;
  int sw1[1]  = { 
    1  
  };
  char *titles1[]  = { 
    (char *)"Okay", 
    NULL
  };
  void *xpm1[]  = { 
    NULL, /* pixmap info */ 
    NULL, 
    NULL, 
    NULL
  };
  int bkgr1[]  = { 
    -1, 
    -1
  };
  char *butncode1  = NULL;
  DILN H1 = { 
    'H',
    202,124,  
    288,155,
    4,0,
    80, 
    25, 
    1,1, 
    &butn1, 
    sw1,
    titles1,
    butncode1,
    NULL,getStringshoribar1callback,/* arg, Callbak */
    xpm1,bkgr1, /* pointers to xpms and colors */
     3,0.500000 /* button type and roundinfg factor(0-0.5) */
  };
  n=0;
  while(v[n++]!= NULL);
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*n);
  e0[n-1].fmt=NULL;
  for(k=0;k<(n-1);k++) {
    e0[k].fmt= (char *)malloc(sizeof(char)*20);
    sprintf(e0[k].fmt,"Item%-d String%%30s",k+id);
    e0[k].v = v[k];
    e0[k].sw =1;
  }
  t0.ny=n-1;
  t0.elmt = e0;
  yextra = (n-2)*30;
  t0.y2 +=yextra;
  yextra = (n-4)*30;
  H1.y1+=yextra;
  H1.y2+=yextra;
  d[0].t = &t0;
  d[1].H = &H1;
  d[2].t = NULL;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 1;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 323;   /* Position of Dialog */ 
  D.yo = 69;
  D.xl = 457;    /*  Length of Dialog */
  D.yl = 157+yextra;    /*  Width  of Dialog */
  D.Initfun = getStringsinit;    /*   init fuction for Dialog */
  D.kbattn = 1;    /*  1 for drawing keyborad attention */
  D.butattn = 1;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.000000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
#if 0 
  D.Callback = getStringsCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.WaitCallback = NULL;    
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = NULL;    /*  any data to be passed by user*/
  strcpy(D.name,"Kulina Designer ver 1.0");    /*  Dialog name you may change */
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
  }    /*  end of fullscreen mode */
  kgDefaultGuiTheme(&(D.gc));    /*  set colors for gui*/
//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/
//  ModifygetStringsGc(&(D.gc));    /*  set colors for gui*/
  D.SearchList=NULL;
  ret= kgUi(&D);
//  insert any memory frees here to avoid leak  
  k=0;
  while(e0[k].fmt != NULL) {free(e0[k].fmt);k++;}
  free(e0);
  return ret;
}
char **RungetStrings(void *parent,int n) {
/*************************************************

    Text_Box1  1 data values

*************************************************/
   int i=0,id=1,k,iq,ir,ip=16;
   char  **v,*dummy;
   void *pt=NULL; /* pointer to send any extra information */
   v=(char **)malloc(sizeof(char*)*(n+1));
   v[n]=NULL;
   iq=n/ip;
   ir=n%ip;
   for(i=0;i<n;i++) {
    v[i]=(char *)malloc(60);
    v[i][0]=' ';
    v[i][1]='\0';
   }
   id = 1;
   for(i=0;i<iq;i++) {
     dummy=v[id];
     v[(i+1)*ip]=NULL;
     getStrings(parent,(void **)(v+i*ip),id );
     v[(i+1)*ip]=dummy;
     id+=ip;
   }
   if(ir!= 0) getStrings(parent,(void **)(v+iq*ip),id);
   return v;
}
char **RuneditStrings(void *parent,char **v) {
/*************************************************

    Text_Box1  1 data values

*************************************************/
   int i=0,id=1,k,iq,ir,ip=16,n=0;
   char *dummy;
   void *pt=NULL; /* pointer to send any extra information */
   if(v==NULL) return v;
   n=0;while(v[n++]!=NULL);
   n--;
   if(n > 0) {
     iq=n/ip;
     ir=n%ip;
     id = 1;
     for(i=0;i<iq;i++) {
       dummy=v[id];
       v[(i+1)*ip]=NULL;
       getStrings(parent,(void **)(v+i*ip),id );
       v[(i+1)*ip]=dummy;
       id+=ip;
     }
     if(ir!= 0) getStrings(parent,(void **)(v+iq*ip),id);
   }
   return v;
}
ThumbNail **RuneditThumbNails(void *parent,ThumbNail **th) {
/*************************************************

    Text_Box1  1 data values

*************************************************/
   int i=0,id=1,k,iq,ir,ip=16,n=0;
   char  **v,*dummy;
   void *pt=NULL; /* pointer to send any extra information */
   if(th==NULL) return th;
   n=0;while(th[n++]!=NULL);
   if(n==1) return th;
   v= (char **)malloc(sizeof(char*)*n);
   v[n]=NULL;
   n--;
   if(n > 0) {
     for(i=0;i<n;i++) {
      v[i]=th[i]->name;
     }
     iq=n/ip;
     ir=n%ip;
     id = 1;
     for(i=0;i<iq;i++) {
       dummy=v[id];
       v[(i+1)*ip]=NULL;
       getStrings(parent,(void **)(v+i*ip),id );
       v[(i+1)*ip]=dummy;
       id+=ip;
     }
     if(ir!= 0) getStrings(parent,(void **)(v+iq*ip),id);
     free(v);
   }
   return th;
}
