#include <unistd.h>
#include <ctype.h>
#include <kulina.h>
extern char CWD[500];
char icondir[500];
static void SetButton(DIALOG *D,DIN *B,int index) {
  char buff[200];
  ThumbNail **th;
  char *xpm;
  DIN *db;
  DICH *C;
  DIRA *R;
  BUT_STR *buts;
  buts = (BUT_STR *)(B->buts);
  sprintf(buff,"For Button: %-d",index+1);
  kgSplash(D,0,buff);
  kgSetstring(D,1,0,buts[index].title);
  db = (DIN *)kgGetWidget(D,2);
  C = (DICH *)kgGetWidget(D,3);
  R = (DIRA *)kgGetWidget(D,11);
  th = (ThumbNail **) C->list;
  th[0]->sw = buts[index].sw;
  ((BUT_STR *)(db->buts))[0].bkgr = buts[index].bkgr;
  kgUpdateWidget(C);
  kgUpdateWidget(db);
  kgUpdateWidget(kgGetWidget(D,1));
  xpm = (char *)buts[index].xpmn;
  if(xpm != NULL) { kgSetstring(D,4,0,(xpm+2)); }
  else kgSetstring(D,4,0,(char *)"");
  xpm = (char *)buts[index].xpmp;
  if(xpm != NULL) { kgSetstring(D,4,1,(xpm+2)); }
  else kgSetstring(D,4,1,(char *)"");
  xpm = (char *)buts[index].xpmh;
  if(xpm != NULL) { kgSetstring(D,4,2,(xpm+2)); }
  else kgSetstring(D,4,2,(char *)"");
  kgUpdateWidget(kgGetWidget(D,4));
  *(R->df) = (buts[index].butncode) -' '+1;
  kgUpdateWidget(R);
  kgUpdateOn(D);
}
static void GetButton(DIALOG *D,DIN *B,int index) {
  int i;
  char buff[200];
  ThumbNail **th;
  char *xpm;
  DIN *db;
  DICH *C;
  DIRA *R;
  BUT_STR *buts;
  buts = (BUT_STR *)(B->buts);
  strcpy(buff,kgGetstring(D,1,0));
  strcpy(buts[index].title,buff);
  db = (DIN *)kgGetWidget(D,2);
  C = (DICH *)kgGetWidget(D,3);
  R = (DIRA *)kgGetWidget(D,11);
  th = (ThumbNail **) C->list;
  buts[index].sw = th[0]->sw;
  buts[index].bkgr=((BUT_STR *)(db->buts))[0].bkgr;
  strcpy(buff,kgGetstring(D,4,0));
  i = 0;
  while(buff[i]==' ')i++;
  if(buff[i] != '\0') {
   xpm = (char *)malloc(strlen(buff+i)+3);
   strcpy(xpm,"##");
   strcat(xpm,buff+i);
   buts[index].xpmn=(void *)xpm;
  }
  strcpy(buff,kgGetstring(D,4,1));
  i = 0;
  while(buff[i]==' ')i++;
  if(buff[i] != '\0') {
   xpm = (char *)malloc(strlen(buff+i)+3);
   strcpy(xpm,"##");
   strcat(xpm,buff+i);
   buts[index].xpmp=(void *)xpm;
  }
  strcpy(buff,kgGetstring(D,4,2));
  i = 0;
  while(buff[i]==' ')i++;
  if(buff[i] != '\0') {
    xpm = (char *)malloc(strlen(buff+i)+3);
    strcpy(xpm,"##");
    strcat(xpm,buff+i);
    buts[index].xpmh=(void *)xpm;
  }
  buts[index].butncode= (*(R->df))+31-1;
}
int  butnopttextbox1callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  butnoptbutnbox1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B;
  BUT_STR *buts;
  int n,ret =0,r,g,b,clr,*bkgr;
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  buts = (BUT_STR *)B->buts;
  clr = buts[butno-1].bkgr;
  if(clr == -1 ) {
   clr = D->gc.fill_clr;
  }
  if(clr < -1 ) {
    clr = -clr;
    b = ((clr)%1000)%256;
    g = ((clr/1000)%1000)%256;
    r = ((clr/1000000)%1000)%256;
  }
  else kgGetDefaultRGB(clr,&r,&g,&b);
  kgGetColor(Tmp,100,100,&r,&g,&b);
  clr = r*1000000+g*1000+b;
  clr = -clr;
//  if(clr == D->gc.fill_clr) clr=-1;
  buts[butno-1].bkgr=clr;
  kgUpdateWidget(B);
  kgUpdateOn(D);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  butnoptbutton1init(DIN *B,void *pt) {
}
int  butnoptbrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DICH *C;DIALOG *D;void *pt; 
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  pt = D->pt;
  C = (DICH *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) C->list;
  return ret;
}
void  butnoptbrowser1init(DICH *C,void *pt) {
}
int  butnopttextbox2callback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  return ret;
}
int  butnoptbutnbox2callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  char flname[500];
  char cwd[500];
  DIT *T;
  DIALOG *D;DIN *B;
  int n,ret =0;
  static int Entry=0;
  if(Entry==0) {
   strcpy(icondir,"/usr/share/icons");
   Entry=1;
  }
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  T=(DIT *)kgGetWidget(Tmp,4);
  flname[0]='\0';
  getcwd(cwd,499);
  chdir(icondir);
  switch(butno) {
    case 1:
      kgPickImage(NULL,100,100,flname);
      chdir(CWD);
      chdir("Images");
      kgImagetoC(flname);
      chdir(CWD);
      kgSetstring(Tmp,4,0,flname);
      break;
    case 2:
      kgPickImage(NULL,100,100,flname);
      chdir(CWD);
      chdir("Images");
      kgImagetoC(flname);
      chdir(CWD);
      kgSetstring(Tmp,4,1,flname);
      break;
    case 3:
      kgPickImage(NULL,100,100,flname);
      chdir(CWD);
      chdir("Images");
      kgImagetoC(flname);
      chdir(CWD);
      kgSetstring(Tmp,4,2,flname);
      break;
  }
  chdir(cwd);
  kgUpdateWidget(T);
  kgUpdateOn(D);
  return ret;
}
void  butnoptbutton2init(DIN *B,void *pt) {
}
int  butnopthoribar1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIN *B;
  int *index;
  void **ptrs;
  DIALOG *D;DILN *H; 
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  H = (DILN *) kgGetWidget(Tmp,i);
  n = H->nx;
  ptrs = (void **)(D->pt);
  B = (DIN *)ptrs[0];
  index = (int *)ptrs[1];
  GetButton(D,B,*index);
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  butnopthbutton1init(DILN *H,void *pt) {
}
int  butnoptvertscroll1callback(double val,int i,void *Tmp) {
  /*********************************** 
    val : current value 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIN *B;
  int *index;
  void **ptrs;
  DIALOG *D;DIV *V; 
  int ret=1,n; 
  D = (DIALOG *)Tmp;
  ptrs = (void **)(D->pt);
  B = (DIN *)ptrs[0];
  n = B->nx*B->ny;
  index = (int *)ptrs[1];
  GetButton(D,B,*index);
  V = (DIV *) kgGetWidget(Tmp,i);
  *index = (int)(n*val/100.0+0.5);
  SetButton(D,B,*index);
  return ret;
}
int  butnoptbrowser2callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item)  not any specific relevence
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIRA *R;DIALOG *D;void *pt; 
  ThumbNail **th; 
  int ret=1; 
  D = (DIALOG *)Tmp;
  pt = D->pt;
  R = (DIRA *)kgGetWidget(Tmp,i);
  th = (ThumbNail **) R->list;
  return ret;
}
void  butnoptbrowser2init(DIRA *R,void *pt) {
}
int butnoptinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1,*index,n;
  DIALOG *D;void *pt;
  DIV *V;
  void **ptrs;
  DIN *B;
  D = (DIALOG *)Tmp;
  ptrs = (void **)(D->pt);
  B = (DIN *)ptrs[0];
  index = (int *)ptrs[1];
  n = B->nx*B->ny;
  SetButton(D,B,*index);
  if(n>1) {
    V = (DIV *)kgGetNamedWidget(D,(char *)"butnoptWidget11");
    V->ds = 1.0*100.0/(double)n;
    if(V->ds > 100.) V->ds=100.;
    V->df =0.0;
    V->mvmt = 1.0*100.0/n;
    kgSetWidgetVisibility(V,1);
  }
  kgUpdateOn(D);
  return ret;
}
int butnoptcleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1,*index;
  return ret;
}
int butnoptCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
  int ret = 0;
  KBEVENT *kbe;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
int butnoptResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgRedrawDialog(D);
  return ret;
}
void ModifybutnoptGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int butnoptGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j,n;
  DIA *d=NULL,*dtmp;
  DIM m0 = { 
    'M',
    11,10,  
    430,33,  
    0,0  
  };
  strncpy(m0.msg,(char *)"Button 1",499);
  strcpy(m0.Wid,(char *)"");
  T_ELMT *e1  ; 
  e1 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e1[0].fmt = (char *)malloc(10);
  strcpy(e1[0].fmt,(char *)"Title%20s");
  e1[0].v=(void *)v[0];
  e1[0].sw=1;
  e1[0].noecho=0;
  DIT t1 = { 
    't',
    57,47,  
    335,81,
    20, 
    1,1, 
    e1,
    1,1,
    NULL,butnopttextbox1callback,0,0,0,0, /* args,Call back */
  };
  strcpy(t1.Wid,(char *)"");
  t1.pt=NULL;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"!c01C!c10o!c02l!c03o!c04r");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-1;
  butn2[0].butncode='x';
  DIN b2 = { 
    'n',
    334,47,  
    410,78,
    0,0,  
    70, 
    25, 
    1,1, 
    2,0.500000,0,0 ,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide */
    NULL,
    butnoptbutnbox1callback, /* args, Callbak */
    NULL
  };
  b2.bval = 1; 
  b2.buts = butn2; 
  strcpy(b2.Wid,(char *)"");
  char *menu3[]  = { 
    (char *)"Button Active",
    NULL 
  };
  ThumbNail **th0 ;
  DICH c3 = { 
    'c',
    170,90,  
    320,120,   
    117,0,  
    90, 
    25, 
    1,1, 
    0,1, 
    (int *)v[1], 
    NULL, 
    NULL, 
    NULL,butnoptbrowser1callback, /* *args, callback */
    0,  /* Border Offset  */
     2,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu3);
  c3.list=(void **)th0;
  strcpy(c3.Wid,(char *)"");
  T_ELMT *e4  ; 
  e4 =(T_ELMT *)malloc(sizeof(T_ELMT)*3);
  e4[0].fmt = (char *)malloc(5);
  strcpy(e4[0].fmt,(char *)"%15s");
  e4[0].v=(void *)v[2];
  e4[0].sw=1;
  e4[1].fmt = (char *)malloc(5);
  strcpy(e4[1].fmt,(char *)"%15s");
  e4[1].v=(void *)v[3];
  e4[1].sw=1;
  e4[2].fmt = (char *)malloc(5);
  strcpy(e4[2].fmt,(char *)"%15s");
  e4[2].v=(void *)v[4];
  e4[2].sw=1;
  DIT t4 = { 
    't',
    155,127,  
    335,221,
    20, 
    1,3, 
    e4,
    1,1,
    NULL,butnopttextbox2callback,0,0,0,0 /* args,Call back */
  };
  strcpy(t4.Wid,(char *)"");
  t4.pt=NULL;
  BUT_STR  *butn5=NULL; 
  butn5= (BUT_STR *)malloc(sizeof(BUT_STR)*3);
  butn5[0].sw=1;
  strcpy(butn5[0].title,(char *)"Pick");
  butn5[0].xpmn=NULL;
  butn5[0].xpmp=NULL;
  butn5[0].xpmh=NULL;
  butn5[0].bkgr=-1;
  butn5[0].butncode=31;
  butn5[1].sw=1;
  strcpy(butn5[1].title,(char *)"Pick");
  butn5[1].xpmn=NULL;
  butn5[1].xpmp=NULL;
  butn5[1].xpmh=NULL;
  butn5[1].bkgr=-1;
  butn5[1].butncode=31;
  butn5[2].sw=1;
  strcpy(butn5[2].title,(char *)"Pick");
  butn5[2].xpmn=NULL;
  butn5[2].xpmp=NULL;
  butn5[2].xpmh=NULL;
  butn5[2].bkgr=-1;
  butn5[2].butncode=31;
  DIN b5 = { 
    'n',
    333,124,  
    392,217,
    0,5,  
    54, 
    25, 
    1,3, 
    4,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide */
    NULL,
    butnoptbutnbox2callback, /* args, Callbak */
    NULL
  };
  b5.bval = 1; 
  b5.buts = butn5; 
  strcpy(b5.Wid,(char *)"");
  DIM m6 = { 
    'm',
    33,132,  
    155,156,  
    1,0  
  };
  strncpy(m6.msg,(char *)"Primary Image",499);
  strcpy(m6.Wid,(char *)"");
  DIM m7 = { 
    'm',
    33,160,  
    155,184,  
    1,0  
  };
  strncpy(m7.msg,(char *)"Pressed Image",499);
  strcpy(m7.Wid,(char *)"");
  DIM m8 = { 
    'm',
    27,193,  
    155,217,  
    1,0  
  };
  strncpy(m8.msg,(char *)"Hight light Image",499);
  strcpy(m8.Wid,(char *)"");
  char **titles9=NULL; 
  titles9= (char **)malloc(sizeof(char *)*1);
  titles9[0]= (char *)malloc(5);
  strcpy(titles9[0],(char *)"Okay");
  int *sw9=NULL  ; 
  sw9 =(int *)malloc(sizeof(int)*1) ; 
  sw9[0]= 1; 
  char **xpms9  = NULL; 
  xpms9  = (char **)malloc(sizeof(char *)*3); 
  xpms9[0]=   NULL; /* pixmap info */ 
  xpms9[1]=   NULL; /* pixmap info */ 
  xpms9[2]=   NULL; /* pixmap info */ 
  int *bkgr9 =NULL; 
  bkgr9 =(int *)malloc(sizeof(int)*1) ; 
  bkgr9[0]=  -1; 
  char *butncode9  = NULL;
  DILN H9 = { 
    'H',
    197,338,  
    283,369,
    4,0,
    80, 
    25, 
    1,1, 
    NULL, 
    sw9,
    titles9,
    butncode9,
    NULL,butnopthoribar1callback,/* arg, Callbak */
    (void **)xpms9,bkgr9, /* pointers to xpms and colors */
     3,0.500000, /* button type and roundinfg factor(0-0.5) */
     0,0 /* button border,hide */
  };
  H9.bval = 1; 
  strcpy(H9.Wid,(char *)"");
  DIV v10 = { 
    'v',
    431,8,  
    451,329,  
    1,  
    100.000000,0.000000,5.000000,  
    NULL,butnoptvertscroll1callback /* *args, callback */
  };
  strcpy(v10.Wid,(char *)"butnoptWidget11");
  char **menu11;
  menu11 = (char **) malloc(sizeof(char *)*98);
  menu11[97]=NULL;
  menu11[0]=(char *)malloc(7);
  strcpy(menu11[0],(char *)"(null)");
  menu11[1]=(char *)malloc(9);
  strcpy(menu11[1],(char *)"(space)");
  menu11[2]=(char *)malloc(9);
  strcpy(menu11[2],(char *)"(33)");
  for(i=3;i<97;i++) {
     menu11[i]=(char *)malloc(2);
     menu11[i][0]=31+i;
     menu11[i][1]=0;
  }
/*
  char *menu11[]  = { 
    (char *)"A",
    (char *)"Q",
    (char *)"C",
    (char *)"D",
    (char *)"E",
    (char *)"F",
    (char *)"G",
    (char *)"H",
    (char *)"I",
    (char *)"J",
    (char *)"K",
    (char *)"L",
    (char *)"M",
    (char *)"N",
    (char *)"O",
    (char *)"P",
    (char *)"Q",
    (char *)"R",
    (char *)"S",
    (char *)"T",
    (char *)"U",
    (char *)"V",
    (char *)"W",
    (char *)"X",
    (char *)"Y",
    (char *)"Z",
    NULL 
  };
*/
  ThumbNail **th1 ;
  DIRA r11 = { 
    'r',
    90,231,  
    422,327,   
    4,0,  
    52, 
    25, 
    1,26, 
    -1077952577,3, 
    (int *)v[5], 
    NULL, 
    NULL ,
    NULL,butnoptbrowser2callback, /* *args, callback */
    4,  /* Border Offset  */
     18,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu11);
  kgFreeDouble((void **)menu11);
  r11.list=(void **)th1;
  strcpy(r11.Wid,(char *)"butnoptWidget13");
  DIM m12 = { 
    'm',
    10,241,  
    89,265,  
    1,0  
  };
  strncpy(m12.msg,(char *)"Button Code",499);
  strcpy(m12.Wid,(char *)"butnoptWidget14");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+14));
  d =dtmp+i; 
  d[13].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIM));
  *d[0].m = m0;
  d[0].m->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIT));
  *d[1].t = t1;
  d[1].t->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIN));
  butnoptbutton1init(&b2,pt) ;
  *d[2].N = b2;
  d[2].N->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DICH));
  butnoptbrowser1init(&c3,pt) ;
  *d[3].c = c3;
  d[3].c->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIT));
  *d[4].t = t4;
  d[4].t->item = -1;
  d[5].t = (DIT *)malloc(sizeof(DIN));
  butnoptbutton2init(&b5,pt) ;
  *d[5].N = b5;
  d[5].N->item = -1;
  d[6].t = (DIT *)malloc(sizeof(DIM));
  *d[6].m = m6;
  d[6].m->item = -1;
  d[7].t = (DIT *)malloc(sizeof(DIM));
  *d[7].m = m7;
  d[7].m->item = -1;
  d[8].t = (DIT *)malloc(sizeof(DIM));
  *d[8].m = m8;
  d[8].m->item = -1;
  d[9].t = (DIT *)malloc(sizeof(DILN));
  butnopthbutton1init(&H9,pt) ;
  *d[9].H = H9;
  d[9].H->item = -1;
  d[10].t = (DIT *)malloc(sizeof(DIV));
  *d[10].v = v10;
  d[10].v->item = -1;
  d[11].t = (DIT *)malloc(sizeof(DIRA));
  butnoptbrowser2init(&r11,pt) ;
  *d[11].r = r11;
  d[11].r->item = -1;
  d[12].t = (DIT *)malloc(sizeof(DIM));
  *d[12].m = m12;
  d[12].m->item = -1;
  d[13].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakebutnoptGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  1 data values
    CheckBox1  1 data value
    Text_Box2  3 data values
    RadioButtons2  1 data value

*************************************************/
   char  *v0 ;
   v0 = (char *)malloc(sizeof(100));
   v0[0] = '\0';
   int  *v1 ;
   v1 = (int *)malloc(sizeof(int));
   *v1 = 1;
   char  *v2 ;
   v2 = (char *)malloc(sizeof(100));
   v2[0] = '\0';
   char  *v3 ;
   v3 = (char *)malloc(sizeof(100));
   v3[0] = '\0';
   char  *v4 ;
   v4 = (char *)malloc(sizeof(100));
   v4[0] = '\0';
   int  *v5 ;
   v5 = (int *)malloc(sizeof(int));
   *v5 = 1;
   void** v=(void **)malloc(sizeof(void*)*6);
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(v4);
   v[5]=(void *)(v5);
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = butnoptGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int butnopt( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = butnoptGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 2;
  D.df = 11;
  D.tw = 4;
  D.bw = 44;
  D.lw = 4;
  D.rw = 4;
  D.xo = 275;   /* Position of Dialog */ 
  D.yo = 109;
  D.xl = 461;    /*  Length of Dialog */
  D.yl = 378;    /*  Width  of Dialog */
  D.Initfun = butnoptinit;    /*   init fuction for Dialog */
  D.Cleanupfun = butnoptcleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.000000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = butnoptCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = butnoptResizeCallBack;  /*  Resize callback */
  D.WaitCallback = NULL;
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 1.0");    /*  Dialog name you may change */
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
//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/
//  ModifybutnoptGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runbutnopt(void *Parent,void *arg) {
/*************************************************

    Text_Box1  1 data values
    CheckBox1  1 data value
    Text_Box2  3 data values
    RadioButtons2  1 data value

*************************************************/
   int index=0;
   void *ptrs[2];
   char  v0[100]=" " ;
   int   v1 = 1;
   char  v2[100]=" " ;
   char  v3[100]=" " ;
   char  v4[100]=" " ;
   int   v5 = 1;
   void* v[6];
   v[0]=(void *)(v0);
   v[1]=(void *)(&v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(v4);
   v[5]=(void *)(&v5);
   ptrs[0]=arg;
   ptrs[1]=&index;
   butnopt(Parent,v,ptrs );
   return NULL;
}
