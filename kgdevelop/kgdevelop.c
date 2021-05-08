#include <unistd.h>
#include <kulina.h>
#include <malloc.h>
#include <string.h>
#include <malloc.h>
#include <signal.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "image.c"
#define VER 1401010200
char kulinahome[500];
char CWD[500];
int FullScreen=0;
void *T;
int gindex;
void *Tmp;
static FILE *fp,*fp1,*Inc;
static int Vcount=0,Tbox=0,Listitem=0,Vertbox=0,Horizbox=0,
           Textbox=0,Tblbox=0,Gbox=0,Hbox=0,Butbox=0,Pixbox=0,Mbox=0,
           Brwbox=0,Ibox=0,Sfbox=0,Sibox=0,Filebox=0,Foldbox=0,WidCount=0;
static char buff[500];
static int Vx1,Vy1,Vx2,Vy2;
/*static Dlink *Dialink=NULL;*/
DIALOG *Parent=NULL;
DIG *GBOX;
DIALOG *Dia=NULL;
int Get_data_line();
int Pid =-1;
static int Xoff=7,Yoff=46,Evgay;
int Runslidebaropt(void *arg);
int RunOptions(void *Tmp);
int RunBorderoptdia(void *Tmp);
int RunItemoptdia(void *Tmp);
int RunFileoptdia(void *);
int actcntl=0,totcntl=0,horicntl=0,vertscroll=0,horizscroll=0;
int SetControlCounters(DIALOG *D);
void *Runbutnopt(void *parent,void *arg);
char **RungetStrings(void *parent,int n);
char **RuneditStrings(void *parent,char **v);
ThumbNail **RuneditThumbNails(void *parent,ThumbNail **th);
void *Runselectmenu(void *arg);
void *Runcheckbox(void *arg);
void *Runthumbnail(void *arg);
void *Runradiobuttons(void *arg);
void ChangeControlSize(DIALOG *D);
void ChangeControlPos(DIALOG *D);
void ChangeControlVisibility(DIALOG *D);
void ChangeDialogSize(DIALOG *D);
void ChangeDialogTopWidth(DIALOG *D);
void ChangeDialogBottomWidth(DIALOG *D);
void ChangeDialogLeftWidth(DIALOG *D);
void ChangeDialogRightWidth(DIALOG *D);
void DRAW_DIALOG(DIALOG *);
void ShowDialog(DIALOG *D);
void DeleteControl(DIALOG *D);
void AddControl(DIALOG *D,void * T);
void SetOptions(DIALOG *D);
void InitOptions(DIALOG *D);
void Align_items(DIALOG *D);
DIALOG * Make_dialog_structure_from_file(char *flname);
void Convert_gui_data(void);
int buttoninfo(void *parent,char *msg,  void *v0, void *v1, void *v2 );

void Make_gui_code(DIALOG *D,char *flname,char *dianame);
int Runbuttondata(void *arg);
int Runhbuttondata(void *arg);
int Runmessagedata(void *arg);
void *Runtextboxdata(void *arg);
int Runtextboxesdata(void *arg);
int Runtableboxesdata(void *arg);
void *Runtableboxdata(void *arg,char *msg);

static char flname[100],Sourcecode[100],DiaName[200],Callbackcode[100],
           Includecode[100],Maincode[100];
ThumbNail ** MakeSampleThumbNails(int size,int n) {
  int i;
  void *img,*thimg;
  ThumbNail **th;
  char **Str;
  n++;
  Str = (char **)malloc(sizeof(char *)*n-1);
  Str[n-1]=NULL;
  for(i=0;i<(n-1);i++) {
    Str[i]=(char *)malloc(15);
    sprintf(Str[i],"Test item%-d",i);
  }
  th = kgStringToThumbNails(Str);
  free(Str);
  img = kgFMGtogmImage(&sample_str);
  if(img != NULL) {
    thimg = kgChangeSizeImage(img,size,size);
    kgFreeImage(img);
    for(i=0;i<(n-1);i++) {
     th[i]->img= thimg;
    }
  }
  return th;
}
int Box_gincur(float *x1,float *y1,float *x2,float *y2) {
   float yl,yu;
   yl = *y1;
   yu = *y2;
   yl = Evgay-yl;
   yu = Evgay -yu;
   kgBoxCursor((DIG *)kgGetWidget(Parent,1),x1,&yl,x2,&yu);
   yl = Evgay-yl;
   yu = Evgay -yu;
   *y1 = yl;
   *y2 = yu;
   return 1;
}
int Rect_gincur(float *x1,float *y1,float *x2,float *y2) {
   float yl,yu;
   yl = *y1;
   yu = *y2;
   yl = Evgay-yl;
   yu = Evgay -yu;
   kgRectCursor((DIG *)kgGetWidget(Parent,1),x1,&yl,x2,&yu);
   yl = Evgay-yl;
   yu = Evgay -yu;
   *y1 = yl;
   *y2 = yu;
   return 1;
}
int Cross_gincur(float *x1,float *y1) {
   float yl,yu;
   yl = *y1;
   yl = Evgay-yl;
   kgCrossCursor((DIG *)kgGetWidget(Parent,1),x1,&yl);
   yl = Evgay-yl;
   *y1 = yl;
   return 1;
}
int InitCounters(void) {
  Vcount=0,Tbox=0,Tblbox=0,Gbox=0,Hbox=0,Butbox=0;
  Brwbox=0,Ibox=0,Sfbox=0,Sibox=0,Filebox=0,Foldbox=0;
  Pixbox =0, Mbox=0;
  Textbox=0;
  Listitem=0;
  Vertbox=0;
  Horizbox=0;
  return 1;
}
int DiaCallBack(void *Tmp,void *tmp) {
  int ret = 0;
  int x1,y1,x2,y2;
  DIALOG *D;
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
//       x1 = D->xo; y1= D->yo;x2= x1+D->xl;y2= y1+D->yl;
       x1 = 7;y1=3; x2=774;y2=40;
       if(( (kbe->x -x1)*(x2-kbe->x) > 0) &&
         ( (kbe->y-y1)*(y2-kbe->y) > 0)) ret=1;
//       printf("%d %d %d %d: %d\n",x1,y1,x2,y2,ret);
    }
  }
  if(ret)kgPushBackEvent(D);
  return ret;
}
int DiaHoribarCallback(int key,int i,void *Tmp) {
   return 1;
}
void Convert_gui_data(void) {
  DIALOG *D;int Yshift;int yfac;
  FILE *fp1;
  DIT *t;
  Dlink *L;
  DIA *d;
  D = Dia;
  int i,n,no;
  int x1,y1,x2,y2,xl,yl;
//TCB
  Yshift =Evgay;
  yfac = -1;
  L = Dopen();
  d = D->d;
  i=0;while(d[i].t != NULL) {Dadd(L,d[i].t);i++;};
  D->yo = D->yo*yfac+Yshift;
  Resetlink(L);
  while ((t=(DIT *)Getrecord(L)) != NULL) {
    switch(t->code) {
     case 't':
      t->y1 *=yfac;
      t->y2 *=yfac;
      t->y1 +=Yshift;
      t->y2 +=Yshift;
      break;
     case 'x':
      {
      DIX *x;
      x = (DIX *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'y':
      {
      DIY *x;
      x = (DIY *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'r':
      {
      DIRA *x;
      x = (DIRA *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'c':
      {
      DICH *x;
      x = (DICH *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'w':
     case 'e':
     case 's':
      {
      DIW *x;
      x = (DIW *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'n':
      {
      DIN *x;
      x = (DIN *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'b':
      {
      DIB *x;
      x = (DIB *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'N':
      {
      DIBN *x;
      x = (DIBN *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'h':
      {
      DIL *x;
      x = (DIL *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'H':
      {
      DILN *x;
      x = (DILN *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'p':
      {
      DIP *x;
      x = (DIP *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'i':
      {
      DII *x;
      x = (DII *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'g':
      {
      DIG *x;
      x = (DIG *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'm':
     case 'B':
     case 'M':
      {
      DIM *x;
      x = (DIM *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'o':
      {
      DIO *x;
      x = (DIO *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'v':
      {
      DIV *x;
      x = (DIV *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'z':
      {
      DIZ *x;
      x = (DIZ *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'T':
      {
      DIT *x;
      x = (DIT *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'f':
      {
      DIF *x;
      x = (DIF *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'd':
      {
      DID *x;
      x = (DID *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     case 'P':
      {
      DIHB *x;
      x = (DIHB *) t;
      x->y1 *=yfac;
      x->y2 *=yfac;
      x->y1 +=Yshift;
      x->y2 +=Yshift;
      }
      break;
     deafault:
      t->y1 *=yfac;
      t->y2 *=yfac;
      t->y1 +=Yshift;
      t->y2 +=Yshift;
      break;
    }
  }
  Dfree(L);
}
void Draw_gui_box(void) {
  DIALOG *D;int Yshift;int yfac;
  FILE *fp1;
  DIT *t;
  Dlink *L;
  DIA *d;
  D = Dia;
  int i,n,no;
  int x1,y1,x2,y2,xl,yl;
  float xoff,yoff;
  L = Dopen();
  d = D->d;
  i=0;while(d[i].t != NULL) {Dadd(L,d[i].t);i++;};
  Resetlink(L);
  xoff = D->xo;
  yoff = Evgay-D->yo;
  yoff = -yoff;
  while ((t=(DIT *)Getrecord(L)) != NULL) {
    switch(t->code) {
     case 't':
      kgMove2f(GBOX,t->x1+xoff,t->y1+yoff);
      kgDraw2f(GBOX,t->x2+xoff,t->y1+yoff);
      kgDraw2f(GBOX,t->x2+xoff,t->y2+yoff);
      kgDraw2f(GBOX,t->x1+xoff,t->y2+yoff);
      kgDraw2f(GBOX,t->x1+xoff,t->y1+yoff);
      break;
     case 'x':
      {
      DIX *x;
      x = (DIX *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'y':
     case 'r':
     case 'c':
      {
      DIY *x;
      x = (DIY *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'w':
     case 'e':
     case 's':
      {
      DIW *x;
      x = (DIW *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'b':
      {
      DIB *x;
      x = (DIB *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'n':
      {
      DIN *x;
      x = (DIN *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'N':
      {
      DIBN *x;
      x = (DIBN *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'h':
      {
      DIL *x;
      x = (DIL *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'H':
      {
      DILN *x;
      x = (DILN *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'p':
      {
      DIP *x;
      x = (DIP *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'i':
      {
      DII *x;
      x = (DII *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'g':
      {
      DIG *x;
      x = (DIG *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'm':
     case 'B':
     case 'M':
      {
      DIM *x;
      x = (DIM *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'o':
      {
      DIO *x;
      x = (DIO *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'v':
      {
      DIV *x;
      x = (DIV *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'z':
      {
      DIZ *x;
      x = (DIZ *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'T':
      {
      DIT *x;
      x = (DIT *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'f':
      {
      DIF *x;
      x = (DIF *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'd':
      {
      DID *x;
      x = (DID *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     case 'P':
      {
      DIHB *x;
      x = (DIHB *) t;
      kgMove2f(GBOX,x->x1+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y1+yoff);
      kgDraw2f(GBOX,x->x2+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y2+yoff);
      kgDraw2f(GBOX,x->x1+xoff,x->y1+yoff);
      }
      break;
     deafault:
      break;
    }
  }
  Dfree(L);
//TCB
//  clr_buf();
  kgClearBuffer(GBOX);
}
void InitDialog(void) {
  Dia = Make_dialog_structure_from_file(flname);
  Dia->tmpdir=(char *)malloc(200);
  Dia->Shapexpm=NULL;
  Dia->Callback=DiaCallBack;
  strcpy(Dia->tmpdir,"/tmp");
  SetControlCounters(Dia);
  Dia->ThInfo = OpenThreads(0);
  return;
}
void makeguidiagbox1init(int i,void *tmp) {
  DIALOG *D;
  DIG *g;
  int x1,y1,x2,y2,xres,yres;
  D = (DIALOG *)tmp;
  g = D->d[i].g;
  GBOX=D->d[i].g;
//  get_resolution(&xres,&yres);
  xres = D->evgax;
  yres = D->evgay;
  Vx1 = g->vx1;
  Vy1 = g->vy1;
  Vx2 = g->vx2;
  Vy2 = g->vy2;
//  get_viewport(&x1,&y1,&x2,&y2);
#if 1
  kgViewport(g,0.0,.0,1.0,1.0);
  Tmp=tmp;
  gindex =i;
  x1 = g->x1;
  y1 = g->y1;
  x2 = g->x2;
  y2 = g->y2;
  Evgay = (int)(y2-y1-1);
  InitDialog();
//  Dia->gc = D->gc;
  Dia->evgax = D->evgax;
  Dia->evgay = D->evgay;
  Dia->Hsize=1;
  
#if 0
  Convert_gui_data(Dia,Evgay,-1); /* rewriting */
  Convert_gui_data(Dia,Evgay,-1); /* rewriting */
  Print_gui_data(Dia,"JUNK.rc"); /* rewriting */
#endif
  Convert_gui_data();
//  set_window(0.,0.,(float)(x2-x1),(float)(y2-y1));
  kgUserFrame(GBOX,0.,0.,(float)(x2-x1-1),(float)(y2-y1-1));
//  change_cur_format("5.0f","5.0f");
//  clr_viewport();
  kgClearView(GBOX);
  DRAW_DIALOG(Dia);
#endif
  return;
}
int BorderActions(int but) {
   switch(but) {
     case 1:
      ChangeDialogSize(Dia);
      DRAW_DIALOG(Dia);
      return 1;
     case 2:
      ChangeDialogTopWidth(Dia);
      DRAW_DIALOG(Dia);
      return 1;
     case 3:
      ChangeDialogBottomWidth(Dia);
      DRAW_DIALOG(Dia);
      return 1;
     case 4:
      ChangeDialogLeftWidth(Dia);
      DRAW_DIALOG(Dia);
      return 1;
     case 5:
      ChangeDialogRightWidth(Dia);
      DRAW_DIALOG(Dia);
      return 1;
     default:
      return 1;

   }
}
int  makeguidiabutton1callback(int key,int i,void *Tmp) {
  DIA *D;DIB *B; 
  int n,ret =1,but; 
  float xx,yy;
  D = ((DIALOG *)Tmp)->d;
  B = D[i].b;
  n = B->nx*B->ny;
  xx = Dia->xo;
  yy = Dia->yo;
  kgPrintf(Parent,2,(char *)"!c02!s!f22!z53DESIGN MODE");
  switch(key) {
    case 1: 
      ret = 1;
      switch(RunFileoptdia(Tmp)) {
        case 1:
         ret=0;
        case 2:
         SetOptions(Dia);
         Convert_gui_data();
         Make_gui_code(Dia,Sourcecode,DiaName);
         Print_gui_data(Dia,flname); /* rewriting */
         Convert_gui_data();
         break;
        case 3:
         if(!kgCheckMenu(Parent,100,200,(char *)"Quit without SAVING...",0) ) {
               ret=0;
         }
         break;
        default:
         ret =0;
         break;
      }
      break;
    case 2: 
      kgPrintf(Parent,2,(char *)"!s!f22!z53WIDGET ACTIONS");
      RunItemoptdia(Tmp);
      ret = 0;
      break;
    case 3: 
      but = RunBorderoptdia(Tmp);
      /*BorderActions(but);*/
      ret = 0;
      break;
    case 5: 
//      cross_gincur((DIG *)kgGetWidget(Parent,1),&xx,&yy);
      kgCrossCursor(GBOX,&xx,&yy);
      Dia->xo = xx;
      Dia->yo = yy;
      DRAW_DIALOG(Dia);
      ret = 0;
      break;
    case 6: 
//      RunOptionsdia(Tmp);
//      SetOptions(Dia);
      RunOptions(Tmp);
      InitOptions(Dia);
      DRAW_DIALOG(Dia);
      ret = 0;
      break;
    case 4: 
      ChangeDialogSize(Dia);
      DRAW_DIALOG(Dia);
      ret = 0;
      break;
    case 7: 
      kgPrintf(Parent,2,(char *)"!c01!s!f03!z53TESTING DESIGN");
      ShowDialog(Dia);
      kgPrintf(Parent,2,(char *)"!c02!s!f03!z53DESIGN MODE    ");
      DRAW_DIALOG(Dia);
      ret = 0;
      break;
  }
  return ret;
}

void  makeguidiabutton1init(DIB *B,void *pt) {
}
int makeguidiacleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int makeguidiaCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
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
int makeguidiaResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgGetWindowSize(D,&xres,&yres);
  dx = xres - D->xl;
  dy = yres - D->yl;
  /* extra code */
  D->xl= xres;
  D->yl= yres;
  kgRedrawDialog(D);
  return ret;
}
int makeguidiaWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  return ret;
}
int makeguidiainit(void *Tmp) {
//  DRAW_DIALOG(Dia);
  Parent= (DIALOG *)Tmp;
  T = ((DIALOG *)Tmp)->d[2].i->twin;  
  return 1;
}
#if 0
int makeguidia( void *parent, void *v0 ){
  int xres,yres,xl,yl;
  int ret=1;
  DIALOG D;
  DIA d[4];
  char *titles0[]  = { 
    (char *)"File", 
    (char *)"Widget", 
    (char *)"Border", 
    (char *)"Resize", 
    (char *)"Repos", 
    (char *)"Options", 
    (char *)"Test", 
    NULL
  };
  char *butncode0  = NULL;
  int sw[7]={1,1,1,1,1,1,1};
  DIB n0 = { 
    'b',
    7,3,  
    774,40,
    9,0,  
    88, 
    30, 
    7,1, 
    (int *)v0, 
    sw,
    titles0,
    butncode0,
    NULL,makeguidiabutnbox1callback, /* args, Callbak */
    NULL,NULL
    ,1,0.5,0,0
  };
  DIG g1 = { 
    'g',
    6,45,  
    888,664,  
    NULL, /* pixmap info */ 
    0, /* bkgr colour */ 
    makeguidiagbox1init,/* void *initgraph(int,void *)  */ 
    NULL,0,0 /* *data */
  };
  DII i3 = {
    'i',
    716,5,
    1002,38,
    22,0,
    30,1
  };

  kgDisplaySize(&xres,&yres);
  D.fullscreen = FullScreen;
  if( D.fullscreen) {
    yl = ((yres));
    xl = (xres );
  }
  else {
    yl = ((yres-50));
    xl = (xres -30);
  }

  d[0].b = &n0;
  d[1].g = &g1;
  d[2].i = &i3;
  d[3].t = NULL;
  i3.hide=0;
  D.d = d;
  D.bkup = 0; /* set to 1 for backup */
  D.bor_type = 3;
  D.df = -1;
  D.tw = 43;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 0;   /* Position of Dialog */ 
  D.yo = 0;
  D.xl = 900;    /*  Length of Dialog */
  D.yl = 675;    /*  Width  of Dialog */
  D.xl = xl;
  D.yl = yl;
  g1.x2 = g1.x1+xl-12;
  g1.y2 = g1.y1+yl-52;
  D.Initfun = makeguidiainit;  
  D.Cleanupfun = NULL;
  strcpy(D.name,"Kulina Designer Ver 1.0");
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
       D.xo= xres - D.xl-10;D.yo=10;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
  }    /*  end of fullscreen mode */
  D.kbattn=1;
  D.butattn=1;
  D.Deco=1;
  D.DrawBkgr=1;
  D.Bkpixmap=NULL;
  D.Callback=NULL;
  D.transparency = 0;
  D.Newwin=1;
  D.Sticky=0;
  D.Resize=0;
  D.ResizeCallback=NULL;
  D.WaitCallback = NULL;
  D.MinWidth=D.MinHeight=200;
  D.Fixpos=1;
  D.NoTaskBar=0;
  D.parent = parent;
  D.Shapexpm=NULL;
  D.StackPos=0;
//  D.Initfun = NULL;
//  ret= sDialog(&D);
  Parent = &D;
  kgDefaultGuiTheme(&(D.gc));
//  kgColorTheme(&(D),210,210,210);
//  D.gc.GuiFontSize=9;
  D.SearchList=NULL;
//  Print_gui_data(&D,"/root/makeguidia.rc");
  ret = kgUi(&D);
  return ret;
}
#else
void ModifymakeguidiaGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int makeguidiaGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  char **titles0=NULL; 
  titles0= (char **)malloc(sizeof(char *)*7);
  titles0[0]= (char *)malloc(5);
  strcpy(titles0[0],(char *)"File");
  titles0[1]= (char *)malloc(7);
  strcpy(titles0[1],(char *)"Widget");
  titles0[2]= (char *)malloc(7);
  strcpy(titles0[2],(char *)"Border");
  titles0[3]= (char *)malloc(7);
  strcpy(titles0[3],(char *)"Resize");
  titles0[4]= (char *)malloc(6);
  strcpy(titles0[4],(char *)"Repos");
  titles0[5]= (char *)malloc(8);
  strcpy(titles0[5],(char *)"Options");
  titles0[6]= (char *)malloc(5);
  strcpy(titles0[6],(char *)"Test");
  int *sw0=NULL  ; 
  sw0 =(int *)malloc(sizeof(int)*7) ; 
  sw0[0]= 1; 
  sw0[1]= 1; 
  sw0[2]= 1; 
  sw0[3]= 1; 
  sw0[4]= 1; 
  sw0[5]= 1; 
  sw0[6]= 1; 
  char **xpms0  = NULL; 
  xpms0  = (char **)malloc(sizeof(char *)*21); 
  xpms0[0]=   NULL; /* pixmap info */ 
  xpms0[1]=   NULL; /* pixmap info */ 
  xpms0[2]=   NULL; /* pixmap info */ 
  xpms0[3]=   NULL; /* pixmap info */ 
  xpms0[4]=   NULL; /* pixmap info */ 
  xpms0[5]=   NULL; /* pixmap info */ 
  xpms0[6]=   NULL; /* pixmap info */ 
  xpms0[7]=   NULL; /* pixmap info */ 
  xpms0[8]=   NULL; /* pixmap info */ 
  xpms0[9]=   NULL; /* pixmap info */ 
  xpms0[10]=   NULL; /* pixmap info */ 
  xpms0[11]=   NULL; /* pixmap info */ 
  xpms0[12]=   NULL; /* pixmap info */ 
  xpms0[13]=   NULL; /* pixmap info */ 
  xpms0[14]=   NULL; /* pixmap info */ 
  xpms0[15]=   NULL; /* pixmap info */ 
  xpms0[16]=   NULL; /* pixmap info */ 
  xpms0[17]=   NULL; /* pixmap info */ 
  xpms0[18]=   NULL; /* pixmap info */ 
  xpms0[19]=   NULL; /* pixmap info */ 
  xpms0[20]=   NULL; /* pixmap info */ 
  int *bkgr0 =NULL; 
  bkgr0 =(int *)malloc(sizeof(int)*7) ; 
  bkgr0[0]=  -1; 
  bkgr0[1]=  -1; 
  bkgr0[2]=  -1; 
  bkgr0[3]=  -1; 
  bkgr0[4]=  -1; 
  bkgr0[5]=  -1; 
  bkgr0[6]=  -1; 
  char *butncode0  = NULL;
  DIB b0 = { 
    'b',
    7,3,  
    774,40,
    9,0,  
    88, 
    30, 
    7,1, 
    NULL, 
    sw0,
    titles0,
    butncode0,
    NULL,makeguidiabutton1callback, /* args, Callbak */
      (void **)xpms0,bkgr0, /* pointers to xpms and colors */
      1,0.500000,0,0 /* button type and roundinfg factor(0-0.5),bordr,hide */
  };
  b0.bval = 1; 
  strcpy(b0.Wid,(char *)"");
  char *xpm1=   NULL; /* pixmap info */ 
  DIG g1 = { 
    'g',
    6,45,  
    1330,711,  
    (void *)xpm1,
    0, /* bkgr colour */ 
    makeguidiagbox1init,/* void *initgraph(int,void *)  */ 
    NULL,0,0 /* *data border hide*/
  };
  strcpy(g1.Wid,(char *)"");
  DII i2 = { 
    'i',
    716,5,  
    1002,38,  
    1,0,0   
  };
  strcpy(i2.Wid,(char *)"");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+4));
  d =dtmp+i; 
  d[3].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIB));
  makeguidiabutton1init(&b0,pt) ;
  *d[0].b = b0;
  d[0].b->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIG));
  *d[1].g = g1;
  d[1].g->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DII));
  *d[2].i = i2;
  d[2].i->item = -1;
  d[3].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakemakeguidiaGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = makeguidiaGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int makeguidia( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = makeguidiaGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 0; /* set to 1 for backup */
  D.bor_type = 3;
  D.df = 0;
  D.tw = 43;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 20;   /* Position of Dialog */ 
  D.yo = 10;
  D.xl = 1336;    /*  Length of Dialog */
  D.yl = 718;    /*  Width  of Dialog */
  D.Initfun = makeguidiainit;    /*   init fuction for Dialog */
  D.Cleanupfun = makeguidiacleanup;    /*   init fuction for Dialog */
  D.kbattn = 1;    /*  1 for drawing keyborad attention */
  D.butattn = 1;    /*  1 for drawing button attention */
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
  D.Callback = makeguidiaCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = makeguidiaResizeCallBack;  /*  Resize callback */
#if 1 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = makeguidiaWaitCallBack;  /*  Wait callback */
#endif
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
       D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-60;
//       D.xo= xres - D.xl-10;D.yo=10;
       d[1].g->x2 =D.xl-8;
       d[1].g->y2 =D.yl-8;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/
//  ModifymakeguidiaGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
#endif
#define GETDATALINE  if(Get_data_line() < 0 ) {\
    printf("Error : In reading.... %s\n",buff);\
    exit(0); \
  }
int NULLDATA(void) {
 if((buff[0]=='N')&&(buff[1]=='U')&&(buff[2]=='L')
                            &&(buff[3]=='L')) return 1;
 else return 0;
}
void Print_message(FILE *fp,DIM *t,int control,char *dianame) {
  fprintf(fp,"  DIM m%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d  \n",t->justification,t->hide);
  fprintf(fp,"  };\n");
  fprintf(fp,"  strncpy(m%-d.msg,(char *)\"%-s\",499);\n",Tbox,t->msg);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(m%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  m%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_displaybox(FILE *fp,DIM *t,int control,char *dianame) {
  fprintf(fp,"  DIM m%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d  \n",t->justification,t->hide);
  fprintf(fp,"  };\n");
  fprintf(fp,"  strncpy(m%-d.msg,(char *)\"%-s\",499);\n",Tbox,t->msg);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(m%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  m%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_progressbar(FILE *fp,DIO *t,int control,char *dianame) {
  fprintf(fp,"  DIO o%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,%d,%d,%d,%d  \n",t->hide,t->percent,t->bordr,t->type,t->clr,t->direction);
  fprintf(fp,"       //hide,percent,border,type,color,direction \n");
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(o%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  o%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_vertscroll(FILE *fp,DIV *t,int control,char *dianame) {
  fprintf(fp,"  DIV v%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    %d,  \n",t->hide);
  fprintf(fp,"    %lf,%lf,%lf,  \n",t->ds,t->df,t->mvmt);
  fprintf(fp,"    NULL,%-svertscroll%-dcallback /* *args, callback */\n",
                   dianame,control);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(v%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  v%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_horizscroll(FILE *fp,DIZ *t,int control,char *dianame) {
  fprintf(fp,"  DIZ z%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    %d,  \n",t->hide);
  fprintf(fp,"    %lf,%lf,%lf,  \n",t->ds,t->df,t->mvmt);
  fprintf(fp,"    NULL,%-shorizscroll%-dcallback /* *args, callback */\n",
                   dianame,control);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(z%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  z%-d.item = -1;\n",Tbox);
  Tbox++;
}
void StringCopy(char *d,char *s) {
  int i=0,l,j;
  while((s[i]>=' ')&&(s[i]!= '"')) { i++; }
  if(s[i] < ' ') {
    d[0] ='\0';
    return;
  }
  else {
    i++;
    j= i;
    while((s[i]>=' ')&&(s[i]!= '"')) { i++; }
    if(s[i] < ' ') {
      d[0] ='\0';
      return;
    }
    else {
      s[i]='\0';
      l = strlen(s+j);
      strcpy(d,s+j);
    }
  }
}
DIM * Read_message(void) {
  int i, n,l;
  DIM *t;
  t = (DIM *) malloc(sizeof(DIM));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  StringCopy(t->msg,buff);
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->justification),&(t->hide));
  return t;
}
DIO * Read_progressbar(void) {
  int i, n,l;
  DIO *t;
  t = (DIO *) malloc(sizeof(DIO));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  t->y2 = t->y2;
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  t->percent=50;
  t->bordr=0;
  t->type=0;
  t->clr =-1;
  t->direction =0;
  return t;
}
DIV * Read_vertscroll(void) {
  int i, n,l;
  DIV *t;
  t = (DIV *) malloc(sizeof(DIV));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  t->y2 = t->y2;
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  t->ds=100.;
  t->df=0.;
  t->mvmt=5.;
  return t;
}
DIZ * Read_horizscroll(void) {
  int i, n,l;
  DIZ *t;
  t = (DIZ *) malloc(sizeof(DIZ));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  t->y2 = t->y2;
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  t->ds=100.;
  t->df=0.;
  t->mvmt=5.;
  return t;
}
void Print_floatslide(FILE *fp,DIF *t,int control,char *dianame) {
  fprintf(fp,"  DIF f%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %lf,%lf,  \n",t->min,t->max);
  fprintf(fp,"    %d,  \n",t->lngth);
  fprintf(fp,"    (double *)v[%-d],\n",Vcount++);
  fprintf(fp,"    NULL,\n");
  fprintf(fp,"    NULL,%-sfslide%-dcallback /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(f%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  f%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_intslide(FILE *fp,DID *t,int control,char *dianame) {

  fprintf(fp,"  DID d%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->min,t->max);
  fprintf(fp,"    %d,  \n",t->lngth);
  fprintf(fp,"    (int *)v[%-d],\n",Vcount++);
  fprintf(fp,"    NULL,\n");
  fprintf(fp,"    NULL,%-sdslide%-dcallback /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(d%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  d%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_horislide(FILE *fp,DIHB *t,int control,char *dianame) {

  fprintf(fp,"  DIHB d%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->min,t->max);
  fprintf(fp,"    %d,  \n",t->lngth);
  fprintf(fp,"    (int *)v[%-d],\n",Vcount++);
  fprintf(fp,"    NULL,\n");
  fprintf(fp,"    NULL,%-sdslide%-dcallback, /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"    %d,%d,%d,%d, /* bordr,hide,type,color */\n",
                  t->bordr,t->hide,t->type,t->sldclr);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(d%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  d%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_browser(FILE *fp,DIW *t,int control,char *dianame) {
  char **pt,*prompt;
  int nitem=0;
  pt = t->menu;
  if(pt!= NULL) {
  fprintf(fp,"  char **menu%-d ; \n",Tbox);
  while( *pt != NULL) {
     nitem++;
     pt++;
  }
  fprintf(fp,"  menu%-d= (char **)malloc(sizeof(char *)*%-d);\n",Tbox,nitem+1);
  fprintf(fp,"  menu%-d[%-d]=NULL;\n",Tbox,nitem);
  pt = t->menu;
  nitem=0;
  while( *pt != NULL) {
    fprintf(fp,"  menu%-d[%-d]=(char *)malloc(%d);\n",Tbox,nitem,strlen(*pt)+1);
    fprintf(fp,"  strcpy(menu%-d[%-d],(char *)\"%-s\");\n",Tbox,nitem,*pt);
    (pt++);
    nitem++;
  }
  }
  if(t->prompt != NULL) {
    fprintf(fp,"  char *prompt%-d ; \n",Tbox);
    fprintf(fp,"  prompt%-d=(char *)malloc(%d);\n",Tbox,strlen(t->prompt)+1);
    fprintf(fp,"  strcpy(prompt%-d,(char *)\"%-s\");\n",Tbox,t->prompt);
  }
  fprintf(fp,"  DIW w%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,  \n",t->size);
  fprintf(fp,"    (int *)v[%-d],\n",Vcount++);
  if(t->prompt != NULL) {
    fprintf(fp,"    prompt%-d ,\n",Tbox);
  }
  else fprintf(fp,"    NULL,\n");
  if(pt!= NULL) fprintf(fp,"    menu%-d ,\n",Tbox);
  else   fprintf(fp,"     NULL,\n");
  fprintf(fp,"    NULL,%-sbrowser%-dcallback, /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"    %-d \n",t->hide);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(w%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  w%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_scrollmenu(FILE *fp,DIE *t,int control,char *dianame) {
  char **pt;
  int nitem=0;
  pt = t->menu;
  if(pt!= NULL) {
  fprintf(fp,"  char **menu%-d ; \n",Tbox);
  while( *pt != NULL) {
     nitem++;
     pt++;
  }
  fprintf(fp,"  menu%-d= (char **)malloc(sizeof(char *)*%-d);\n",Tbox,nitem+1);
  fprintf(fp,"  menu%-d[%-d]=NULL;\n",Tbox,nitem);
  pt = t->menu;
  nitem=0;
  while( *pt != NULL) {
    fprintf(fp,"  menu%-d[%-d]=(char *)malloc(%d);\n",Tbox,nitem,strlen(*pt)+1);
    fprintf(fp,"  strcpy(menu%-d[%-d],(char *)\"%-s\");\n",Tbox,nitem,*pt);
    (pt++);
    nitem++;
  }
  }
  fprintf(fp,"  DIE e%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,  \n",t->size);
  fprintf(fp,"    (int *)v[%-d],\n",Vcount++);
  fprintf(fp,"    NULL,\n");
  fprintf(fp,"    menu%-d ,\n",Tbox);
  fprintf(fp,"    NULL,%-sbrowser%-dcallback, /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"    %d,%d,%d,%d,%d,%d,%-d \n",t->width,t->offset,t->w,t->itemhi,
                  t->bordr,t->bkgr,t->hide);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(e%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  e%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_Msgscroll(FILE *fp,DIS *t,int control,char *dianame) {
  char **pt;
#if 0
  pt = t->menu;
  fprintf(fp,"  char *menu%-d[]  = { \n",Tbox);
  while( *pt != NULL) 
    fprintf(fp,"    (char *)\"%s\",\n",*(pt++));
  fprintf(fp,"    NULL \n  };\n");
#endif
  fprintf(fp,"  DIS s%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,  \n",t->size);
  fprintf(fp,"    NULL,\n");
  fprintf(fp,"    NULL,\n");
//  fprintf(fp,"    menu%-d ,\n",Tbox);
  fprintf(fp,"    NULL ,\n");
  fprintf(fp,"    NULL,NULL, /* *args, callback */\n");
  fprintf(fp,"    %d,%d,%d,%d,%d,%d,%d\n",
                  t->width,t->offset,t->w,t->itemhi,t->bordr,t->bkgr,t->hide);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(s%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  s%-d.item = -1;\n",Tbox);
  Tbox++;
}
DIW * Read_browser(void) {
  int i, n,l,selmt;
  char **pt,*tmp;
  DIW *t;
  Dlink *L;
  t = (DIW *) malloc(sizeof(DIW));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  t->y2 = t->y2;
  GETDATALINE;
  sscanf(buff,"%d",&(t->size));
  GETDATALINE;
  if(!NULLDATA()){
    t->prompt = (char *)malloc(200);
    StringCopy(t->prompt,buff);
  }
  else t->prompt = NULL;
  L = Dopen();
  i =0;
  GETDATALINE;
  while(!NULLDATA()) {
    tmp = (char *)malloc(200);
    StringCopy(tmp,buff);
    Dadd(L,tmp);
    i++;
    GETDATALINE;
  }
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  pt = (char **) malloc(sizeof(char *)*(i +1));
  t->menu=pt;
  i=0;
  Resetlink(L);
  while((tmp = (char *)Getrecord(L))!= NULL) {
    pt[i++] = tmp;
  }
  pt[i]= NULL;
  Dfree(L);
  t->df = (int *)malloc(sizeof(int));
  *((int *)(t->df)) = 1;
  t->arg = NULL;
  t->Update = NULL;
  return t;
}
DIE * Read_scrollmenu(void) {
  int i, n,l,selmt;
  char **pt,*tmp;
  DIE *t;
  Dlink *L;
  t = (DIE *) malloc(sizeof(DIE));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d",&(t->size));
  GETDATALINE;
  if(!NULLDATA()){
    t->prompt = (char *)malloc(200);
    StringCopy(t->prompt,buff);
  }
  else t->prompt = NULL;
  L = Dopen();
  i =0;
  GETDATALINE;
  while(!NULLDATA()) {
    tmp = (char *)malloc(200);
    StringCopy(tmp,buff);
    Dadd(L,tmp);
    i++;
    GETDATALINE;
  }
  pt = (char **) malloc(sizeof(char *)*(i +1));
  t->menu=pt;
  i=0;
  Resetlink(L);
  while((tmp = (char *)Getrecord(L))!= NULL) {
    pt[i++] = tmp;
  }
  pt[i]= NULL;
  Dfree(L);
  t->df = (int *)malloc(sizeof(int));
  *((int *)(t->df)) = 1;
  t->arg = NULL;
  t->Update = NULL;
  GETDATALINE;
  sscanf(buff,"%d%d%d%d%d%d%d",&(t->width),&(t->offset),&(t->w),&(t->itemhi),&(t->bordr),&(t->bkgr),&(t->hide));
  return t;
}
DIS * Read_msgscroll(void) {
  int i, n,l,selmt;
  char **pt,*tmp;
  DIS *t;
  Dlink *L;
  t = (DIS *) malloc(sizeof(DIS));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d",&(t->size));
  GETDATALINE;
  if(!NULLDATA()){
    t->prompt = (char *)malloc(200);
    StringCopy(t->prompt,buff);
  }
  else t->prompt = NULL;
  L = Dopen();
  i =0;
  GETDATALINE;
  while(!NULLDATA()) {
    tmp = (char *)malloc(200);
    StringCopy(tmp,buff);
    Dadd(L,tmp);
    i++;
    GETDATALINE;
  }
  pt = (char **) malloc(sizeof(char *)*(i +1));
  t->menu=pt;
  i=0;
  Resetlink(L);
  while((tmp = (char *)Getrecord(L))!= NULL) {
    pt[i++] = tmp;
  }
  pt[i]= NULL;
  Dfree(L);
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->arg = NULL;
  t->Update = NULL;
  t->width=20,t->offset=6,t->w=22,t->itemhi=1,t->bordr=1,t->bkgr=1;
  return t;
}
DIHB * Read_horislide(void) {
  DIHB *t;
  t = (DIHB *) malloc(sizeof(DIHB));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->min),&(t->max));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d",&(t->lngth));
  GETDATALINE;
  if(!NULLDATA()){
    t->prompt = (char *)malloc(200);
    StringCopy(t->prompt,buff);
  }
  else t->prompt = NULL;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->y2 = t->y2;
  t->df = (int *)malloc(sizeof(int));
  *((int *)(t->df)) = 1;
  t->arg = NULL;
  t->Update = NULL;
  return t;
}
DID * Read_intslide(void) {
  DID *t;
  t = (DID *) malloc(sizeof(DID));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->min),&(t->max));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d",&(t->lngth));
  GETDATALINE;
  if(!NULLDATA()){
    t->prompt = (char *)malloc(200);
    StringCopy(t->prompt,buff);
  }
  else t->prompt = NULL;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->y2 = t->y2;
  t->df = (int *)malloc(sizeof(int));
  *((int *)(t->df)) = 1;
  t->arg = NULL;
  t->Update = NULL;
  return t;
}
DIF * Read_floatslide(void) {
  DIF *t;
  t = (DIF *) malloc(sizeof(DIF));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%lf%lf",&(t->min),&(t->max));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d",&(t->lngth));
  GETDATALINE;
  if(!NULLDATA()){
    t->prompt = (char *)malloc(200);
    StringCopy(t->prompt,buff);
  }
  else t->prompt = NULL;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->y2 = t->y2;
  t->df = (double *)malloc(sizeof(double));
  *((double *)(t->df)) = 1;
  t->arg = NULL;
  t->Update = NULL;
  return t;
}
char *basename(void *pt) {
  int i=0;
  char *tmp;
  tmp = (char *)pt;
  tmp = (char *)malloc(strlen(tmp+2)+1);
  strcpy(tmp,(char *)pt+2);
  while( (tmp[i] != '.')&&(tmp[i]> ' ') ) i++;
  tmp[i]='\0';
  return tmp;
}
void PrintImage(FILE *fp,void *img) {
  JPGIMG *jpg;
  char *pt;
  int ch;
  if(img== NULL) {
    fprintf(fp,"    NULL, /* pixmap info */ \n");
  }
  else {
    jpg = (JPGIMG *)img;
    ch = jpg->Sign[3];
    jpg->Sign[3]='\0';
    if((strcmp("JPG",jpg->Sign)==0) ||(strcmp("PNG",jpg->Sign)==0)) {
      fprintf(fp,"    (char *)\"##%-s\" , // Pixmap info\n",jpg->flname);
    }
    else {
      jpg->Sign[3]=ch;
      pt = (char *)img;
      fprintf(fp,"    (char *)\"%-s\" , // Pixmap info\n",pt);
    }
  }
}
void PrintXpm(FILE *fp,void *img,int id) {
  JPGIMG *jpg;
  char *pt;
  int ch;
  if(img== NULL) {
    fprintf(fp,"  char *xpm%-d=   NULL; /* pixmap info */ \n",id);
  }
  else {
    pt = (char *)img;
    if((pt[0]=='#')&&(pt[1]=='#')&&(pt[3]>' ')) {
      fprintf(fp,"  char *xpm%-d;// Pixmap info\n",id);
      fprintf(fp,"  xpm%-d = (char *)malloc(%-d);\n",id,strlen(pt)+1);
      fprintf(fp,"  strcpy(xpm%-d, (char *)\"%-s\");\n",id,(pt));
    }
    else {
      fprintf(fp,"  char *xpm%-d=   NULL; /* pixmap info */ \n",id);
    }
  }
}
void PrintXpms(FILE *fp,void *img,int id,int index) {
  JPGIMG *jpg;
  char *pt;
  int ch;
  if(img== NULL) {
    fprintf(fp,"  xpms%-d[%-d]=   NULL; /* pixmap info */ \n",id,index);
  }
  else {
    pt = (char *)img;
    if((pt[0]=='#')&&(pt[1]=='#')&&(pt[3]>' ')) {
      fprintf(fp,"  xpms%-d[%-d] = (char *)malloc(%-d);\n",id,index,strlen(pt)+1);
      fprintf(fp,"  strcpy(xpms%-d[%-d], (char *)\"%-s\");\n",id,index,(pt));
    }
    else {
      fprintf(fp,"  xpms%-d[%-d]=   NULL; /* pixmap info */ \n",id,index);
    }
  }
}
void Print_pixmapbox(FILE *fp,DIP *t,int control,char *dianame) {
  char *pt=NULL;
//TCB dated 2Aug12
  printf("Tra : %f\n",t->transparency);
  if( (t->xpm != NULL) && (*((char *)(t->xpm)) > ' ')){
#if 0
    fprintf(fp,"#ifndef D%-s \n",basename((char *)(t->xpm)));
    fprintf(fp,"#define D%-s \n",basename((char *)(t->xpm)));
    fprintf(fp,"#include \"%-s\" \n",(char *)(t->xpm)+2);
    fprintf(fp,"#endif \n");
#endif
//    pt = basename((char *)(t->xpm));
    pt = (char *)(t->xpm);
  }
  PrintXpm(fp,t->xpm,Tbox);
  t->transparency =0.0;
  fprintf(fp,"  DIP p%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    (void *)xpm%-d,\n",Tbox);
//  PrintImage(fp,t->xpm);
  fprintf(fp,"    %d, /* bkgr colour */ \n  ",t->bkgr_clr);
  fprintf(fp,"    %d,%d,%f /* border hide transparency*/ \n  };\n",t->bordr,t->hide,t->transparency);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(p%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  p%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_infobox(FILE *fp,DII *t,int control,char *dianame) {
  fprintf(fp,"  DII i%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,%d   \n",t->nchrs,t->nlines,t->hide);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(i%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  i%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_graphbox(FILE *fp,DIG *t,int control,char *dianame) {
  PrintXpm(fp,t->xpm,Tbox);
  fprintf(fp,"  DIG g%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,  \n",t->x2,t->y2);
  fprintf(fp,"    (void *)xpm%-d,\n",Tbox);
//  PrintImage(fp,t->xpm);
  fprintf(fp,"    %d, /* bkgr colour */ \n",t->bkgr_clr);
  fprintf(fp,"    %-sgbox%-dinit,/* void *initgraph(int,void *)  */ \n",
          dianame,control);
  fprintf(fp,"    NULL,%d,%d /* *data border hide*/\n  };\n",t->bordr,t->hide);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(g%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  g%-d.item = -1;\n",Tbox);
  Tbox++;
}
DIP *Read_pixmap(void) {
  int i, n,l;
  DIP *t;
  t = (DIP *) malloc(sizeof(DIP));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  t->y1 = t->y1;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  t->y2 = t->y2;
  GETDATALINE;
  if(!NULLDATA()) {
    t->xpm = (void *)malloc(100);
    strcpy((char *)(t->xpm),"##");
    sscanf(buff,"%s",(char *)(t->xpm)+2);
  }
  else t->xpm = NULL;
  GETDATALINE;
  sscanf(buff,"%d",&(t->bkgr_clr));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->bordr),&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->transparency = 0.0;
  return t;
}
DII *Read_infobox(void) {
  int i, n,l;
  DII *t;
  t = (DII *) malloc(sizeof(DII));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  t->y1 = t->y1;
  t->y2 = t->y2;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->nchrs),&(t->nlines));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  return t;
}
DIG *Read_graphbox(void) {
  int i, n,l;
  DIG *t;
  t = (DIG *) malloc(sizeof(DIG));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  t->y1 = t->y1;
  t->y2 = t->y2;
  GETDATALINE;
  if(!NULLDATA()) {
    t->xpm = (void *)malloc(100);
    StringCopy((char *)t->xpm,buff);
  }
  else t->xpm = NULL;
  GETDATALINE;
  sscanf(buff,"%d",&(t->bkgr_clr));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->bordr),&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->initgraph = NULL;
  t->data = NULL;
  return t;
}
void Print_ThumbnailBrowser(FILE *fp,DIY *t,int control,char *dianame) {
  int i=0,n;
  char **pt;
#if 0
  pt = t->menu;
  if(pt!= NULL) {
    fprintf(fp,"  char *menu%-d[]  = { \n",Tbox);
    while( *pt != NULL) 
      {fprintf(fp,"    (char *)\"%s\",\n",*(pt++));i++;}
    fprintf(fp,"    NULL \n  };\n");
    n =i;
    fprintf(fp,"  int sw%-d[%-d]  = { \n",Tbox,n);
    for(i=0;i<n-1;i++) {
      fprintf(fp,"    %d, \n",t->sw[i]);
    }
    fprintf(fp,"    %d  \n  };\n",t->sw[n-1]);
    fprintf(fp,"  void *xpm%-d[]  = { \n",Tbox);
    if(t->xpm == NULL) {
      for(i=0;i<n;i++) {
        fprintf(fp,"    NULL, \n");
      }
    }
    else {
      for(i=0;i<n;i++) {
        PrintImage(fp,t->xpm[i]);
      }
    }
    fprintf(fp,"    NULL\n  };\n");
  }
  else {
    fprintf(fp,"  char **menu%-d  = NULL; \n",Tbox);
    fprintf(fp,"  int *sw%-d  = NULL; \n",Tbox);
    fprintf(fp,"  void **xpm%-d  = NULL; \n",Tbox);
  }
#endif
  t->nx=1;
  t->ny = n;
  fprintf(fp,"  DIY y%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    %d,%d, \n",t->nxsize,t->size);
  fprintf(fp,"    (int *)v[%-d], \n",Vcount++);
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    NULL,%-sbrowser%-dcallback, /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"    %d,  /* Border Offset  */\n ",t->offset);
  fprintf(fp,"    %d,  /* Scroll width  */\n ",t->w);
  fprintf(fp,"    %d,  /* Type  */\n ",t->type);
  fprintf(fp,"    %d, /* item highlight */\n",t->itemhi);
  fprintf(fp,"    %d, /* bordr */\n",t->bordr);
  fprintf(fp,"    %d, /* bkgr */\n",t->bkgr);
  fprintf(fp,"    %d  /* =1 hide  */\n ",t->hide);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(y%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  y%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_RadioButtons(FILE *fp,DIRA *t,int control,char *dianame) {
  int i=0,n;
  ThumbNail **pt;
  pt = (ThumbNail  **)t->list;
  fprintf(fp,"  char *menu%-d[]  = { \n",Tbox);
  while( *pt != NULL) 
    {fprintf(fp,"    (char *)\"%s\",\n",(*(pt++))->name);i++;}
  fprintf(fp,"    NULL \n  };\n");
  n =i;

#if 0
  fprintf(fp,"  int sw%-d[%-d]  = { \n",Tbox,n);
  for(i=0;i<n-1;i++) {
    fprintf(fp,"    %d, \n",t->sw[i]);
  }
  fprintf(fp,"    %d  \n  };\n",t->sw[n-1]);
  fprintf(fp,"  void *xpm%-d[]  = { \n",Tbox);
  if(t->xpm == NULL) {
    for(i=0;i<n;i++) {
      fprintf(fp,"    NULL, \n");
    }
  }
  else {
    for(i=0;i<n;i++) {
      PrintImage(fp,t->xpm[i]);
    }
  }
  fprintf(fp,"    NULL\n  };\n");
#endif
  t->nx=1;
  t->ny = n;
  fprintf(fp,"  ThumbNail **th%-d ;\n",Listitem);
  fprintf(fp,"  DIRA r%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    %d,%d, \n",t->nxsize,t->size);
  fprintf(fp,"    (int *)v[%-d], \n",Vcount++);
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    NULL ,\n",Tbox);
  fprintf(fp,"    NULL,%-sbrowser%-dcallback, /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"    %d,  /* Border Offset  */\n ",t->offset);
  fprintf(fp,"    %d,  /* Scroll width  */\n ",t->w);
  fprintf(fp,"    %d,  /* Type  */\n ",t->type);
  fprintf(fp,"    %d, /* item highlight */\n",t->itemhi);
  fprintf(fp,"    %d, /* bordr */\n",t->bordr);
  fprintf(fp,"    %d, /* bkgr */\n",t->bkgr);
  fprintf(fp,"    %d  /* =1 hide  */\n ",t->hide);
  fprintf(fp,"  };\n");
  fprintf(fp,"  th%-d = (ThumbNail **)kgStringToThumbNails((char **)menu%-d);\n",Listitem,Tbox);
  fprintf(fp,"  r%-d.list=(void **)th%-d;\n",Tbox,Listitem);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(r%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  r%-d.item = -1;\n",Tbox);
  Tbox++;
  Listitem++;
}
void Print_CheckBox(FILE *fp,DICH *t,int control,char *dianame) {
  int i=0,n;
  ThumbNail **pt;
  pt = (ThumbNail  **)t->list;
  fprintf(fp,"  char *menu%-d[]  = { \n",Tbox);
  while( *pt != NULL) 
    {fprintf(fp,"    (char *)\"%s\",\n",(*(pt++))->name);i++;}
  fprintf(fp,"    NULL \n  };\n");
  n =i;
#if 0
  fprintf(fp,"  int sw%-d[%-d]  = { \n",Tbox,n);
  for(i=0;i<n-1;i++) {
    fprintf(fp,"    %d, \n",t->sw[i]);
  }
  fprintf(fp,"    %d  \n  };\n",t->sw[n-1]);
  fprintf(fp,"  void *xpm%-d[]  = { \n",Tbox);
  if(t->xpm == NULL) {
    for(i=0;i<n;i++) {
      fprintf(fp,"    NULL, \n");
    }
  }
  else {
    for(i=0;i<n;i++) {
      PrintImage(fp,t->xpm[i]);
    }
  }
  fprintf(fp,"    NULL\n  };\n");
#endif
  t->nx=1;
  t->ny = n;
  fprintf(fp,"  ThumbNail **th%-d ;\n",Listitem);
  fprintf(fp,"  DICH c%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    %d,%d, \n",t->nxsize,t->size);
  fprintf(fp,"    (int *)v[%-d], \n",Vcount++);
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    NULL,%-sbrowser%-dcallback, /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"    %d,  /* Border Offset  */\n ",t->offset);
  fprintf(fp,"    %d,  /* Scroll width  */\n ",t->w);
  fprintf(fp,"    %d,  /* Type  */\n ",t->type);
  fprintf(fp,"    %d, /* item highlight */\n",t->itemhi);
  fprintf(fp,"    %d, /* bordr */\n",t->bordr);
  fprintf(fp,"    %d, /* bkgr */\n",t->bkgr);
  fprintf(fp,"    %d  /* =1 hide  */\n ",t->hide);
  fprintf(fp,"  };\n");
  fprintf(fp,"  th%-d = (ThumbNail **)kgStringToThumbNails((char **)menu%-d);\n",Listitem,Tbox);
  fprintf(fp,"  c%-d.list=(void **)th%-d;\n",Tbox,Listitem);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(c%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  c%-d.item = -1;\n",Tbox);
  Tbox++;
  Listitem++;
}
void Print_selectmenu(FILE *fp,DIX *t,int control,char *dianame) {
  int i=0,n;
  char **pt;
#if 0
  pt = t->menu;
  fprintf(fp,"  char *menu%-d[]  = { \n",Tbox);
  while( *pt != NULL) 
    {fprintf(fp,"    (char *)\"%s\",\n",*(pt++));i++;}
  fprintf(fp,"    NULL \n  };\n");
  n =i;
  fprintf(fp,"  int sw%-d[%-d]  = { \n",Tbox,n);
  for(i=0;i<n-1;i++) {
    fprintf(fp,"    %d, \n",t->sw[i]);
  }
  fprintf(fp,"    %d  \n  };\n",t->sw[n-1]);
  fprintf(fp,"  void *xpm%-d[]  = { \n",Tbox);
  if(t->xpm == NULL) {
    for(i=0;i<n;i++) {
      fprintf(fp,"    NULL, \n");
    }
  }
  else {
    for(i=0;i<n;i++) {
      PrintImage(fp,t->xpm[i]);
    }
  }
  fprintf(fp,"    NULL\n  };\n");
#endif
  t->nx=1;
  t->ny = n;
  fprintf(fp,"  DIX x%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,   \n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    %d,%d, \n",t->nxsize,t->size);
  fprintf(fp,"    (int *)v[%-d], \n",Vcount++);
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    NULL,%-sbrowser%-dcallback, /* *args, callback */\n",
                  dianame,control);
  fprintf(fp,"    %d,  /* Border Offset  */\n ",t->offset);
  fprintf(fp,"    %d,  /* Scroll width  */\n ",t->w);
  fprintf(fp,"    %d,  /* Type  */\n ",t->type);
  fprintf(fp,"    %d, /* item highlight */\n",t->itemhi);
  fprintf(fp,"    %d, /* bordr */\n",t->bordr);
  fprintf(fp,"    %d, /* bkgr */\n",t->bkgr);
  fprintf(fp,"    %d  /* =1 hide  */\n ",t->hide);
  fprintf(fp,"  };\n");
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(x%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  x%-d.item = -1;\n",Tbox);
  Tbox++;
}
DIX *Read_selectmenu(void) {
#if 1
  int i, n,l,*tmpv;
  DIX *t;
  char *tmp,**pt,*xpm;
  Dlink *L;
  t = (DIX *) malloc(sizeof(DIX));
  tmpv = (int *) malloc(sizeof(int));
  *tmpv =1;
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->xgap),&(t->ygap));
  t->xgap=10;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->lngth),&(t->width));
  GETDATALINE;
  sscanf(buff,"%d",&(t->ny));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->offset),&(t->w));
  GETDATALINE;
  sscanf(buff,"%d%d%d%d%d",&(t->type),&(t->itemhi),&(t->bordr),&(t->bkgr),&(t->hide));
  t->nx =1;
  t->ny =1;
  t->list=(void **)MakeSampleThumbNails((int)(t->width*0.8),12);
#if 0
  L = Dopen();
  i =0;
  GETDATALINE;
  while(!NULLDATA()) {
    tmp = (char *)malloc(200);
    StringCopy(tmp,buff);
    Dadd(L,tmp);
    i++;
    if(i==t->ny) break;
    GETDATALINE;
  }
  t->ny=i;
  pt = (char **) malloc(sizeof(char *)*(i +1));
  t->menu=pt;
  i=0;
  Resetlink(L);
  while((tmp = (char *)Getrecord(L))!= NULL) {
    pt[i++] = tmp;
  }
  pt[i]= NULL;
  n = Dcount(L);
  t->ny = (n+t->nx)/t->nx;
  Dfree(L);
  t->sw = (int *) malloc(sizeof(int)*n);
  for(i=0;i<n;i++) {t->sw[i]=0;}
  GETDATALINE;
  if(!NULLDATA()) {
    sscanf(buff,"%d",&(t->sw[0]));
    for(i=1;i<n;i++) {
      GETDATALINE;
      sscanf(buff,"%d",&(t->sw[i]));
    }
  }
  t->xpm = (void **)malloc(sizeof(char *)*n);
  for(i=0;i<n;i++) {
    GETDATALINE;
    if(!NULLDATA()) {
      t->xpm[i]= (void *)malloc(100);
      xpm =(char *) t->xpm[i];
      strcpy(xpm,"##");
      sscanf(buff,"%s",xpm+2);
    }
    else t->xpm[i]=NULL;
  }
#endif
  t->df = (int *)tmpv;
  t->arg = NULL;
  t->Update = NULL;
  return t;
#endif
}
DIY *Read_thumbnailbrowser(void) {
#if 1
  int i, n,l,*tmpv;
  DIY *t;
  char *tmp,**pt,*xpm;
  Dlink *L;
  t = (DIY *) malloc(sizeof(DIY));
  tmpv = (int *) malloc(sizeof(int));
  *tmpv =1;
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->xgap),&(t->ygap));
  GETDATALINE;
  sscanf(buff,"%d",&(t->width));
  t->lngth=t->width;
  t->nx=t->ny=t->size=t->nxsize=0;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->offset),&(t->w));
  GETDATALINE;
  sscanf(buff,"%d%d%d%d%d",&(t->type),&(t->itemhi),&(t->bordr),&(t->bkgr),&(t->hide));
  t->df = (int *)tmpv;
  t->prompt=NULL;
  t->arg = NULL;
  t->list=(void **)MakeSampleThumbNails((int)(t->width),20);
  t->Update = NULL;
  return t;
#endif
}
DIRA *Read_radiobutton(void) {
#if 1
  int i, n,l,*tmpv;
  DIRA *t;
  char *tmp,**pt,*xpm;
  Dlink *L;
  t = (DIRA *) malloc(sizeof(DIRA));
  tmpv = (int *) malloc(sizeof(int));
  *tmpv =1;
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->xgap),&(t->ygap));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->lngth),&(t->width));
  GETDATALINE;
  sscanf(buff,"%d",&(t->ny));
  t->nx=1;
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->offset),&(t->w));
  GETDATALINE;
  sscanf(buff,"%d%d%d%d%d",&(t->type),&(t->itemhi),&(t->bordr),&(t->bkgr),&(t->hide));
  n = t->ny;
  L = Dopen();
  i =0;
  GETDATALINE;
  while(!NULLDATA()) {
    tmp = (char *)malloc(200);
    StringCopy(tmp,buff);
    Dadd(L,tmp);
    i++;
    if(i==t->ny) break;
    GETDATALINE;
  }
  t->ny=i;
  pt = (char **) malloc(sizeof(char *)*(i +1));
  i=0;
  Resetlink(L);
  while((tmp = (char *)Getrecord(L))!= NULL) {
    pt[i++] = tmp;
  }
  pt[i]= NULL;
  t->list=(void **)kgStringToThumbNails(pt);
  free(pt);
  Dfree(L);
  i=0;
  t->df = (int *)tmpv;
  t->arg = NULL;
  t->Update = NULL;
  return t;
#endif
}
DICH *Read_checkbox(void) {
#if 1
  int i, n,l,*tmpv;
  DICH *t;
  char *tmp,**pt,*xpm;
  Dlink *L;
  t = (DICH *) malloc(sizeof(DICH));
  tmpv = (int *) malloc(sizeof(int));
  *tmpv =1;
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->xgap),&(t->ygap));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->lngth),&(t->width));
  GETDATALINE;
  sscanf(buff,"%d",&(t->ny));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->offset),&(t->w));
  GETDATALINE;
  sscanf(buff,"%d%d%d%d%d",&(t->type),&(t->itemhi),&(t->bordr),&(t->bkgr),&(t->hide));
  n = t->ny;
  t->nx=1;
  L = Dopen();
  i =0;
  GETDATALINE;
  while(!NULLDATA()) {
    tmp = (char *)malloc(200);
    StringCopy(tmp,buff);
    Dadd(L,tmp);
    i++;
    if(i==t->ny) break;
    GETDATALINE;
  }
  t->ny=i;
  pt = (char **) malloc(sizeof(char *)*(i +1));
  i=0;
  Resetlink(L);
  while((tmp = (char *)Getrecord(L))!= NULL) {
    pt[i++] = tmp;
  }
  pt[i]= NULL;
  t->list=(void **)kgStringToThumbNails(pt);
  free(pt);
  Dfree(L);
  t->df = (int *)tmpv;
  t->arg = NULL;
  t->Update = NULL;
  return t;
#endif
}
void Print_textbox(FILE *fp,DIT *t,int control,char *dianame) {
  int i, n;
  T_ELMT *e;
  n = t->nx*t->ny;
  e = t->elmt;
  fprintf(fp,"  T_ELMT *e%-d  ; \n",Tbox);
  fprintf(fp,"  e%-d =(T_ELMT *)malloc(sizeof(T_ELMT)*%-d);\n",Tbox,n);
  for(i=0;i<n;i++) {
    fprintf(fp,"  e%-d[%-d].fmt = (char *)malloc(%d);\n",Tbox,i,strlen(e[i].fmt)+1);
    fprintf(fp,"  strcpy(e%-d[%-d].fmt,(char *)\"%-s\");\n",Tbox,i,e[i].fmt);
    fprintf(fp,"  e%-d[%-d].v=(void *)v[%-d];\n",Tbox,i,Vcount++);
    fprintf(fp,"  e%-d[%-d].sw=1;\n",Tbox,i);
    fprintf(fp,"  e%-d[%-d].noecho=0;\n",Tbox,i);
  }
  fprintf(fp,"  DIT t%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,\n",t->x2,t->y2);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    e%-d,\n",Tbox);
  fprintf(fp,"    %d,%d,\n",t->row,t->col);
  fprintf(fp,"    NULL,%-stextbox%-dcallback,%d,%d,%d,%d /* args,Call back */\n  };\n",
                  dianame,control,t->bordr,t->hide,t->Font,t->FontSize);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(t%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  t%-d.pt=NULL;\n",Tbox);
  fprintf(fp,"  t%-d.type = 0;\n",Tbox);
  fprintf(fp,"  t%-d.item = -1;\n",Tbox);
  Tbox++;
  t->y1 = t->y1;
  t->y2 = t->y2;
}
DIT * Read_textbox(void) {
  int i, n,l,selmt;
  DIT *t;
  T_ELMT *e;
  char *ctmp;
  double *ftmp;
  int *itmp;
  char ch;
  selmt = sizeof(T_ELMT);
  t = (DIT *) malloc(sizeof(DIT));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d",&(t->width));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->nx),&(t->ny));
  n = (t->nx)*(t->ny);
  t->elmt = (T_ELMT *) malloc(selmt*n);
  e = t->elmt;
  for(i=0;i<n;i++) {
    GETDATALINE;
    e[i].fmt = (char *)malloc(100);
    StringCopy(e[i].fmt,buff);
    e[i].sw =1;
    l = strlen(e[i].fmt) - 1;
    while( e[i].fmt[l] <= ' ') l--;
    ch = e[i].fmt[l];
    switch(ch) {
      case 'f':
        e[i].fmt[l]='F';
      case 'F':
        ftmp = (double *)malloc(sizeof(double));
        *ftmp =0.;
        e[i].v = (void *)ftmp;
        break;
      case 'd':
        itmp = (int *)malloc(sizeof(int));
        *itmp = 1;
        e[i].v = (void *)itmp;
        break;
      case 's':
        ctmp = (char *)malloc(100);
        ctmp[0]='\0';
        e[i].v = (void *) ctmp;
        break;
    }
  }
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d%d%d",&(t->row),&(t->col),&(t->bordr));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->arg = NULL;
  t->Update = NULL;
  t->y1 = t->y1;
  t->y2 = t->y2;
  return t;
}
void Print_tablebox(FILE *fp,DIT *t,int control,char *dianame) {
  int i, n;
  T_ELMT *e;
  n = t->nx*t->ny;
  e = t->elmt;
  fprintf(fp,"  T_ELMT *e%-d  ; \n",Tbox);
  fprintf(fp,"  e%-d =(T_ELMT *)malloc(sizeof(T_ELMT)*%-d);\n",Tbox,n);
  for(i=0;i<n;i++) {
    fprintf(fp,"  e%-d[%-d].fmt = (char *)malloc(%d);\n",Tbox,i,strlen(e[i].fmt)+1);
    fprintf(fp,"  strcpy(e%-d[%-d].fmt,(char *)\"%-s\");\n",Tbox,i,e[i].fmt);
    fprintf(fp,"  e%-d[%-d].v=(void *)v[%-d];\n",Tbox,i,Vcount++);
    fprintf(fp,"  e%-d[%-d].sw=%d;\n",Tbox,i,e[i].sw);
    fprintf(fp,"  e%-d[%-d].noecho=0;\n",Tbox,i);
  }
  fprintf(fp,"  DIT T%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,\n",t->x2,t->y2);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    e%-d,\n",Tbox);
  fprintf(fp,"    %d,%d,\n",t->row,t->col);
  fprintf(fp,"    NULL,%-stablebox%-dcallback,%d,%d,%d,%d /* args,Call back */\n  };\n",
                  dianame,control,t->bordr,t->hide,t->Font,t->FontSize);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(T%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  T%-d.pt=NULL;\n",Tbox);
  fprintf(fp,"  T%-d.type = 0;\n",Tbox);
  fprintf(fp,"  T%-d.item = -1;\n",Tbox);
  Tbox++;
}
DIT * Read_tablebox(void) {
  char temp[200];
  int i, n,l,selmt,nx,ny,j,k,sw;
  DIT *t;
  T_ELMT *e;
  char *ctmp;
  double *ftmp;
  int *itmp;
  char ch;
  selmt = sizeof(T_ELMT);
  t = (DIT *) malloc(sizeof(DIT));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d",&(t->width));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->nx),&(t->ny));
  n = (t->nx)*(t->ny);
  nx = t->nx;
  ny = t->ny;
  t->elmt = (T_ELMT *) malloc(selmt*n);
  e = t->elmt;
  for(j=0;j<nx;j++) {
    GETDATALINE;
    sscanf(buff,"%d",&sw);
    GETDATALINE;
    strcpy(temp,buff);
    for(k=0;k<ny;k++) {
      strcpy(buff,temp);
      i = k*nx+j;
      e[i].fmt = (char *)malloc(100);
      StringCopy(e[i].fmt,buff);
      e[i].sw =sw;
      l = strlen(e[i].fmt) - 1;
      while( e[i].fmt[l] <= ' ') l--;
      ch = e[i].fmt[l];
      switch(ch) {
        case 'F':
          ftmp = (double *)malloc(sizeof(double));
          *ftmp =0.;
          e[i].v = (void *)ftmp;
          break;
        case 'd':
          itmp = (int *)malloc(sizeof(int));
          *itmp = 1;
          e[i].v = (void *)itmp;
          break;
        case 's':
          ctmp = (char *)malloc(100);
          ctmp[0]='\0';
          e[i].v = (void *) ctmp;
          break;
      }
    }
  }
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  sscanf(buff,"%d%d%d",&(t->row),&(t->col),&(t->bordr));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->arg = NULL;
  t->Update = NULL;
  t->y1 = t->y1;
  t->y2 = t->y2;
  return t;
}
void Read_dialog_dimensions(DIALOG *D) {
  char extra[30]=" 0 1 1 0 1 1 1 1 0 0.0"; // junk info to make old rc file compatible
//  kgDefaultGuiTheme(&(D->gc));
  GETDATALINE;
  sscanf(buff,"%d%d%d%d",&(D->xo),&(D->yo),&(D->xl),&(D->yl));
  GETDATALINE;
  sscanf(buff,"%d%d%d%d",&(D->lw),&(D->rw),&(D->tw),&(D->bw));
  GETDATALINE;
  strcat(buff,extra);
  sscanf(buff,"%d%d%d%d%d%d%d%d%d%d%d%d%f%d%d%d%d",&(D->df),&(D->bor_type),&(D->bkup),
     &(D->Sticky),&(D->Fixpos),&(D->Deco),&(D->fullscreen),&(D->kbattn),&(D->butattn),&(D->Newwin),
     &(D->DrawBkgr),&(D->NoTaskBar),&(D->transparency),&(D->Resize),&(D->MinWidth),
     &(D->MinHeight),&(D->StackPos));
  InitOptions(D);
}
void Print_buttonbox(FILE *fp,DIB *t,int control,char *dianame) {
  int i, n;
  n = t->nx*t->ny;
  fprintf(fp,"  char **titles%-d=NULL; \n",Tbox);
  if(t->titles != NULL) {
  fprintf(fp,"  titles%-d= (char **)malloc(sizeof(char *)*%-d);\n",Tbox,n);
  for(i=0;i<n;i++) {
    if(t->titles[i]==NULL)  {
      fprintf(fp,"  titles%-d[%-d]=NULL;\n",Tbox,i);
    }
    else  {
      fprintf(fp,"  titles%-d[%-d]= (char *)malloc(%-d);\n",Tbox,i,strlen(t->titles[i])+1);
      fprintf(fp,"  strcpy(titles%-d[%-d],(char *)\"%-s\");\n",Tbox,i,t->titles[i]);
    }
  }
  }
  fprintf(fp,"  int *sw%-d=NULL  ; \n",Tbox);
  fprintf(fp,"  sw%-d =(int *)malloc(sizeof(int)*%-d) ; \n",Tbox,n);
  for(i=0;i<n;i++) {
    fprintf(fp,"  sw%-d[%-d]= %d; \n",Tbox,i,t->sw[i]);
  }
  fprintf(fp,"  char **xpms%-d  = NULL; \n",Tbox);
  if(t->xpm != NULL) {
    fprintf(fp,"  xpms%-d  = (char **)malloc(sizeof(char *)*%d); \n",Tbox,3*n);
    for(i=0;i<3*n;i++) {
      PrintXpms(fp,t->xpm[i],Tbox,i);
    }
  }
  fprintf(fp,"  int *bkgr%-d =NULL; \n",Tbox);
  fprintf(fp,"  bkgr%-d =(int *)malloc(sizeof(int)*%-d) ; \n",Tbox,n);
  for(i=0;i<n;i++) {
    fprintf(fp,"  bkgr%-d[%-d]=  %d; \n",Tbox,i,t->bkgr[i]);
  }
  fprintf(fp,"  char *butncode%-d  = NULL;\n",Tbox);
  if(t->butncode != NULL) {
    fprintf(fp,"  butncode%-d  = (char *)malloc(%-d);\n",Tbox,strlen(t->butncode)+1);
    fprintf(fp,"  strcpy(butncode%-d  ,(char *)\"%-s\");\n",Tbox,t->butncode);
  }
  fprintf(fp,"  DIB b%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,\n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
//  fprintf(fp,"    (int *)v[%-d], \n",Vcount++);
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    sw%-d,\n",Tbox);
  fprintf(fp,"    titles%-d,\n",Tbox);
  fprintf(fp,"    butncode%-d,\n",Tbox);
  fprintf(fp,"    NULL,%-sbutton%-dcallback, /* args, Callbak */\n  ",
                  dianame,control);
  fprintf(fp,"    (void **)xpms%d,bkgr%-d, /* pointers to xpms and colors */\n  ",Tbox,Tbox);
  fprintf(fp,"    %d,%f,%d,%d /* button type and roundinfg factor(0-0.5),bordr,hide */\n  };\n"
                 ,t->type,t->fac,t->bordr,t->hide);
  fprintf(fp,"  b%-d.bval = 1; \n",Tbox);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(b%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  b%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_buttonboxn(FILE *fp,DIN *t,int control,char *dianame) {
  int i, n,ln;
  BUT_STR *butn;
  n = t->nx*t->ny;
  ln = t->lngth;
  if(t->width <ln) ln = t->width;
  fprintf(fp,"  BUT_STR  *butn%-d=NULL; \n",Tbox);
  fprintf(fp,"  butn%-d= (BUT_STR *)malloc(sizeof(BUT_STR)*%-d);\n",Tbox,n);
  butn = (BUT_STR *)t->buts;
  for(i=0;i<n;i++) {
    fprintf(fp,"  butn%-d[%-d].sw=%d;\n",Tbox,i,butn[i].sw);
    if(butn[i].title==NULL)  {
      fprintf(fp,"  butn%-d[%-d].title[0]='\0';\n",Tbox,i);
    }
    else  {
      fprintf(fp,"  strcpy(butn%-d[%-d].title,(char *)\"%-s\");\n",Tbox,i,butn[i].title);
    }
    fprintf(fp,"  butn%-d[%-d].xpmn=NULL;\n",Tbox,i);
    fprintf(fp,"  butn%-d[%-d].xpmp=NULL;\n",Tbox,i);
    fprintf(fp,"  butn%-d[%-d].xpmh=NULL;\n",Tbox,i);
    if(butn[i].xpmn != NULL) {
      fprintf(fp,"#if 1\n");
      fprintf(fp,"  butn%-d[%-d].xpmn= (char *)malloc(100); \n",Tbox,i);
      fprintf(fp,"  strcpy(butn%-d[%-d].xpmn,(char *)\"%-s\");\n",Tbox,i,butn[i].xpmn);
      fprintf(fp,"#else\n");
      fprintf(fp,"  butn%-d[%-d].xpmn= "
       "kgGetProcessedImage(\"%-s\",%-d,0.8,0,0,0);\n",Tbox,i,butn[i].xpmn,ln);
      fprintf(fp,"#endif\n");
    }
    if(butn[i].xpmp != NULL) {
      fprintf(fp,"#if 1\n");
      fprintf(fp,"  butn%-d[%-d].xpmp= (char *)malloc(100); \n",Tbox,i);
      fprintf(fp,"  strcpy(butn%-d[%-d].xpmp,(char *)\"%-s\");\n",Tbox,i,butn[i].xpmp);
      fprintf(fp,"#else\n");
      fprintf(fp,"  butn%-d[%-d].xpmp= "
       "kgGetProcessedImage(\"%-s\",%-d,0.8,0,0,0);\n",Tbox,i,butn[i].xpmp,ln);
      fprintf(fp,"#endif\n");
    }
    if(butn[i].xpmh != NULL) {
      fprintf(fp,"#if 1\n");
      fprintf(fp,"  butn%-d[%-d].xpmh= (char *)malloc(100); \n",Tbox,i);
      fprintf(fp,"  strcpy(butn%-d[%-d].xpmh,(char *)\"%-s\");\n",Tbox,i,butn[i].xpmh);
      fprintf(fp,"#else\n");
      fprintf(fp,"  butn%-d[%-d].xpmh= "
       "kgGetProcessedImage(\"%-s\",%-d,0.8,0,0,0);\n",Tbox,i,butn[i].xpmh,ln);
      fprintf(fp,"#endif\n");
    }
    fprintf(fp,"  butn%-d[%-d].bkgr=%d;\n",Tbox,i,butn[i].bkgr);
    fprintf(fp,"  butn%-d[%-d].butncode=\'%c\';\n",Tbox,i,butn[i].butncode);
  }
  fprintf(fp,"  DIN b%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,\n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    %d,%f,%d,%d,%d,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/\n \n"
                 ,t->type,t->fac,t->bordr,t->hide,t->nodrawbkgr);
//  fprintf(fp,"    NULL,\n");
  fprintf(fp,"    butn%-d, \n",Tbox);
  fprintf(fp,"    %-sbutton%-dcallback, /*  Callbak */\n  ",
                  dianame,control);
  fprintf(fp,"    NULL  /* any args */\n");
  fprintf(fp,"  };\n");
//  fprintf(fp,"  b%-d.bval = 1; \n",Tbox);
//  fprintf(fp,"  b%-d.buts = butn%-d; \n",Tbox,Tbox);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(b%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  b%-d.item = -1;\n",Tbox);
  Tbox++;
}
void Print_splbuttonbox(FILE *fp,DIL *t,int control,char *dianame) {
  int i, n,ln;
  BUT_STR *butn;
  n = t->nx*t->ny;
  ln = t->lngth;
  if(t->width <ln) ln = t->width;
  fprintf(fp,"  BUT_STR  *butn%-d=NULL; \n",Tbox);
  fprintf(fp,"  butn%-d= (BUT_STR *)malloc(sizeof(BUT_STR)*%-d);\n",Tbox,n);
  butn = (BUT_STR *)t->buts;
  if( butn==NULL) printf("butn==NULL: %s,%d\n",__FILE__,__LINE__);
  for(i=0;i<n;i++) {
    fprintf(fp,"  butn%-d[%-d].sw=%d;\n",Tbox,i,butn[i].sw);
    if(butn[i].title==NULL)  {
      fprintf(fp,"  butn%-d[%-d].title[0]='\0';\n",Tbox,i);
    }
    else  {
      fprintf(fp,"  strcpy(butn%-d[%-d].title,(char *)\"%-s\");\n",Tbox,i,butn[i].title);
    }
    fprintf(fp,"  butn%-d[%-d].xpmn=NULL;\n",Tbox,i);
    fprintf(fp,"  butn%-d[%-d].xpmp=NULL;\n",Tbox,i);
    fprintf(fp,"  butn%-d[%-d].xpmh=NULL;\n",Tbox,i);
    if(butn[i].xpmn != NULL) {
      fprintf(fp,"#if 1\n");
      fprintf(fp,"  butn%-d[%-d].xpmn= (char *)malloc(100); \n",Tbox,i);
      fprintf(fp,"  strcpy(butn%-d[%-d].xpmn,(char *)\"%-s\");\n",Tbox,i,butn[i].xpmn);
      fprintf(fp,"#else\n");
      fprintf(fp,"  butn%-d[%-d].xpmn= "
       "kgGetProcessedImage(\"%-s\",%-d,0.8,0,0,0);\n",Tbox,i,butn[i].xpmn,ln);
      fprintf(fp,"#endif\n");
    }
    if(butn[i].xpmp != NULL) {
      fprintf(fp,"#if 1\n");
      fprintf(fp,"  butn%-d[%-d].xpmp= (char *)malloc(100); \n",Tbox,i);
      fprintf(fp,"  strcpy(butn%-d[%-d].xpmp,(char *)\"%-s\");\n",Tbox,i,butn[i].xpmp);
      fprintf(fp,"#else\n");
      fprintf(fp,"  butn%-d[%-d].xpmp= "
       "kgGetProcessedImage(\"%-s\",%-d,0.8,0,0,0);\n",Tbox,i,butn[i].xpmp,ln);
      fprintf(fp,"#endif\n");
    }
    if(butn[i].xpmh != NULL) {
      fprintf(fp,"#if 1\n");
      fprintf(fp,"  butn%-d[%-d].xpmh= (char *)malloc(100); \n",Tbox,i);
      fprintf(fp,"  strcpy(butn%-d[%-d].xpmh,(char *)\"%-s\");\n",Tbox,i,butn[i].xpmh);
      fprintf(fp,"#else\n");
      fprintf(fp,"  butn%-d[%-d].xpmh= "
       "kgGetProcessedImage(\"%-s\",%-d,0.8,0,0,0);\n",Tbox,i,butn[i].xpmh,ln);
      fprintf(fp,"#endif\n");
    }
    fprintf(fp,"  butn%-d[%-d].bkgr=%d;\n",Tbox,i,butn[i].bkgr);
    fprintf(fp,"  butn%-d[%-d].butncode=\'%c\';\n",Tbox,i,butn[i].butncode);
  }
  fprintf(fp,"  DIL h%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,\n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    %d,%f,%d,%d,%d,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/\n \n"
                 ,t->type,t->fac,t->bordr,t->hide,t->nodrawbkgr);
  fprintf(fp,"    butn%-d, \n",Tbox);
  fprintf(fp,"    %-ssplbutton%-dcallback, /*  Callbak */\n  ",
                  dianame,control);
  fprintf(fp,"    NULL  /* any args */\n");
  fprintf(fp,"  };\n");
//  fprintf(fp,"  h%-d.bval = 1; \n",Tbox);
//  fprintf(fp,"  h%-d.buts = butn%-d; \n",Tbox,Tbox);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(h%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  h%-d.item = -1;\n",Tbox);
  Tbox++;
}
DIB * Read_buttonbox(void){
  DIB *t;
  char temp;
  int i, n,l;
  int *tmp;
  char *pt;
  tmp = (int *) malloc(sizeof(int));
  *tmp =1;
  t = (DIB *) malloc(sizeof(DIB));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->xgap),&(t->ygap));
  GETDATALINE;
  sscanf(buff,"%d",&(t->lngth));
  GETDATALINE;
  sscanf(buff,"%d",&(t->width));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->nx),&(t->ny));
  n = t->nx*t->ny;
  t->xpm = (void **)malloc(sizeof(char *)*3*n);
  t->bkgr = (int *)malloc(sizeof(int)*n);
  for(i=0;i<n;i++) { t->bkgr[i]=-1;}
  GETDATALINE;
  t->sw = (int *) malloc(sizeof(int)*n);
  if(NULLDATA()) {
    for(i=0;i<n;i++) {
      t->sw[i]=1;
    }
  }
  else {
    sscanf(buff,"%d",&(t->sw[0]));
    for(i=1;i<n;i++) {
      GETDATALINE;
      sscanf(buff,"%d",&(t->sw[i]));
    }
  }
  t->titles = (char **) malloc(sizeof(char *)*(n+1));
  for(i=0;i<n;i++) {
    GETDATALINE;
    t->titles[i] = (char *)malloc(100);
    StringCopy(t->titles[i],buff);
  }
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  if(NULLDATA()) {
    t->butncode = NULL;
  }
  else {
   t->butncode = (char *)malloc(100);
   StringCopy(t->butncode,buff);
  }
  for(i=0;i<3*n;i++) {
    GETDATALINE;
    if(!NULLDATA()) {
      t->xpm[i]= (void *)malloc(100);
      pt =(char *) t->xpm[i];
      strcpy(pt,"##");
      sscanf(buff,"%s",pt+2);
    }
    else t->xpm[i]=NULL;
  }
  for(i=0;i<n;i++) {
    GETDATALINE;
    if(!NULLDATA()) {
      sscanf(buff,"%d",(t->bkgr)+i);
    }
    else break;
  }
  GETDATALINE;
  sscanf(buff,"%d%f%d",&(t->type),&(t->fac),&(t->bordr));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->df = (int *)tmp;
  t->arg = NULL;
  t->Update = NULL;
  return t;
}
void Print_buttonboxnew(FILE *fp,DIBN *t,int control,char *dianame) {
  int i, n;
  char *pt=NULL;

  n = t->nx*t->ny;
  fprintf(fp,"  char *titles%-d[]  = { \n",Tbox);
  for(i=0;i<n;i++) {
    fprintf(fp,"    (char *)\"%s\", \n",t->titles[i]);
  }
  fprintf(fp,"    NULL\n  };\n");
#if 0
  for(i=0;i<n;i++) {
    if( (t->xpm[i] != NULL) && (*((char *)(t->xpm[i])+2) > ' ')){
     /*  fprintf(fp,"#include \"%-s\" \n",t->xpm[i]+2);*/
      fprintf(fp,"#ifndef D%-s \n",basename((char *)(t->xpm[i])));
      fprintf(fp,"#define D%-s \n",basename((char *)(t->xpm[i])));
      fprintf(fp,"#include \"%-s\" \n",(char *)(t->xpm[i])+2);
      fprintf(fp,"#endif \n");
    }
  }
#endif
  fprintf(fp,"  void *xpm%-d[]  = { \n",Tbox);
  if(t->xpm == NULL) {
    for(i=0;i<3*n;i++) {
      fprintf(fp,"    NULL, \n");
    }
  }
  else {
    for(i=0;i<n;i++) {
      PrintImage(fp,t->xpm[i]);
    }
    for(i=0;i<2*n;i++) {
      fprintf(fp,"    NULL, \n");
    }
  }
  fprintf(fp,"    NULL\n  };\n");
  
  fprintf(fp,"  int bkgr%-d[]  = { \n",Tbox);
  for(i=0;i<n;i++) {
    fprintf(fp,"    %d, \n",t->bkgr[i]);
  }
  fprintf(fp,"    -1\n  };\n");
  if(t->butncode == NULL) {
    fprintf(fp,"  char *butncode%-d  = NULL;\n",Tbox);
  }
  else {
    fprintf(fp,"  char *butncode%-d  = (char *)\"%-s\"; \n",Tbox,t->butncode);
  }
  fprintf(fp,"  DIBN n%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,\n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,  \n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
  fprintf(fp,"    (int *)v[%-d], \n",Vcount++);
  if( t->prompt != NULL )
    fprintf(fp,"    (char *)\"%-s\",\n",t->prompt);
  else  fprintf(fp,"    NULL,\n");
  fprintf(fp,"    titles%-d,\n",Tbox);
  fprintf(fp,"    butncode%-d,\n",Tbox);
  fprintf(fp,"    NULL,%-sbutton%-dcallback, /* args, Callbak */\n",
                  dianame,control);
  fprintf(fp,"    xpm%d,bkgr%d, /* pointers to xpms and colors */\n  ",Tbox,Tbox);
  fprintf(fp,"    %d,%f,%d,%d /* button type and roundinfg factor(0-0.5),bordr,hide */\n  };\n"
                 ,t->type,t->fac,t->bordr,t->hide);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(n%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  n%-d.item = -1;\n",Tbox);
  Tbox++;
}
DIBN * Read_buttonboxnew(void){
  DIBN *t;
  char extra[20]=" 2 0.0";
  char temp,*pt;
  int i, n,l;
  int *tmp;
  tmp = (int *) malloc(sizeof(int));
  *tmp =1;
  t = (DIBN *) malloc(sizeof(DIBN));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  if(t->code=='n') t->code='N';
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->xgap),&(t->ygap));
  GETDATALINE;
  sscanf(buff,"%d",&(t->lngth));
  GETDATALINE;
  sscanf(buff,"%d",&(t->width));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->nx),&(t->ny));
  n = t->nx*t->ny;
  t->xpm = (void **)malloc(sizeof(char *)*3*n);
  t->bkgr = (int *)malloc(sizeof(int)*n);
  for(i=0;i<n;i++) { t->bkgr[i]=-1;}
  GETDATALINE;
  if(NULLDATA()) t->prompt =NULL;
  else {
   t->prompt = (char *)malloc(100);
   StringCopy(t->prompt,buff);
  }
  n = t->nx*t->ny;
  t->titles = (char **) malloc(sizeof(char *)*(n+1));
  for(i=0;i<n;i++) {
    GETDATALINE;
    t->titles[i] = (char *)malloc(100);
    StringCopy(t->titles[i],buff);
  }
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  if(NULLDATA()) {
    t->butncode = NULL;
  }
  else {
   t->butncode = (char *)malloc(100);
   StringCopy(t->butncode,buff);
  }
  for(i=0;i<n;i++) {
    GETDATALINE;
    if(!NULLDATA()) {
      t->xpm[i]= (void *)malloc(100);
      pt =(char *) t->xpm[i];
      strcpy(pt,"##");
      sscanf(buff,"%s",pt+2);
    }
    else t->xpm[i]=NULL;
  }
  for(i=n;i<3*n;i++) {
     t->xpm[i]=NULL;
  }
  for(i=0;i<n;i++) {
    GETDATALINE;
    if(!NULLDATA()) {
      sscanf(buff,"%d",(t->bkgr)+i);
    }
    else break;
  }
  GETDATALINE;
  sscanf(buff,"%d%f%d",&(t->type),&(t->fac),&(t->bordr));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->df = (int *)tmp;
  t->arg = NULL;
  t->Update = NULL;
  t->bordr =0;
  return t;
}
void Print_horibarnew(FILE *fp,DILN *t,int control,char *dianame) {
  static int entry=0;
  int i, n;
  char *pt=NULL;

  entry++;
  n = t->nx*t->ny;
  fprintf(fp,"  char **titles%-d=NULL; \n",Tbox);
  if(t->titles != NULL) {
  fprintf(fp,"  titles%-d= (char **)malloc(sizeof(char *)*%-d);\n",Tbox,n);
  for(i=0;i<n;i++) {
    if(t->titles[i]==NULL)  {
      fprintf(fp,"  titles%-d[%-d]=NULL;\n",Tbox,i);
    }
    else  {
      fprintf(fp,"  titles%-d[%-d]= (char *)malloc(%-d);\n",Tbox,i,strlen(t->titles[i])+1);
      fprintf(fp,"  strcpy(titles%-d[%-d],(char *)\"%-s\");\n",Tbox,i,t->titles[i]);
    }
  }
  }
  fprintf(fp,"  int *sw%-d=NULL  ; \n",Tbox);
  fprintf(fp,"  sw%-d =(int *)malloc(sizeof(int)*%-d) ; \n",Tbox,n);
  for(i=0;i<n;i++) {
    fprintf(fp,"  sw%-d[%-d]= %d; \n",Tbox,i,t->sw[i]);
  }
  fprintf(fp,"  char **xpms%-d  = NULL; \n",Tbox);
  if(t->xpm != NULL) {
    fprintf(fp,"  xpms%-d  = (char **)malloc(sizeof(char *)*%d); \n",Tbox,3*n);
    for(i=0;i<3*n;i++) {
      PrintXpms(fp,t->xpm[i],Tbox,i);
    }
  }
  fprintf(fp,"  int *bkgr%-d =NULL; \n",Tbox);
  fprintf(fp,"  bkgr%-d =(int *)malloc(sizeof(int)*%-d) ; \n",Tbox,n);
  for(i=0;i<n;i++) {
    fprintf(fp,"  bkgr%-d[%-d]=  %d; \n",Tbox,i,t->bkgr[i]);
  }
  fprintf(fp,"  char *butncode%-d  = NULL;\n",Tbox);
  if(t->butncode != NULL) {
    fprintf(fp,"  butncode%-d  = (char *)malloc(%-d);\n",Tbox,strlen(t->butncode)+1);
    fprintf(fp,"  strcpy(butncode%-d  ,(char *)\"%-s\");\n",Tbox,t->butncode);
  }
  fprintf(fp,"  DILN H%-d = { \n",Tbox);
  fprintf(fp,"    \'%c\',\n",t->code);
  fprintf(fp,"    %d,%d,  \n",t->x1,t->y1);
  fprintf(fp,"    %d,%d,\n",t->x2,t->y2);
  fprintf(fp,"    %d,%d,\n",t->xgap,t->ygap);
  fprintf(fp,"    %d, \n",t->lngth);
  fprintf(fp,"    %d, \n",t->width);
  fprintf(fp,"    %d,%d, \n",t->nx,t->ny);
//  fprintf(fp,"    butn%-d, \n",entry);
  fprintf(fp,"    NULL, \n");
  fprintf(fp,"    sw%-d,\n",Tbox);
  fprintf(fp,"    titles%-d,\n",Tbox);
  fprintf(fp,"    butncode%-d,\n",Tbox);
  fprintf(fp,"    NULL,%-shoribar%-dcallback,/* arg, Callbak */\n",
                  dianame,control);
  fprintf(fp,"    (void **)xpms%d,bkgr%d, /* pointers to xpms and colors */\n ",Tbox,Tbox);
  fprintf(fp,"    %d,%f, /* button type and roundinfg factor(0-0.5) */\n ",t->type,t->fac);
  fprintf(fp,"    %d,%d /* button border,hide */\n  };\n",t->bordr,t->hide);
  fprintf(fp,"  H%-d.bval = 1; \n",Tbox);
  t->Wid[49]='\0';
  fprintf(fp,"  strcpy(H%-d.Wid,(char *)\"%-s\");\n",Tbox,t->Wid);
  fprintf(fp,"  H%-d.item = -1;\n",Tbox);
  Tbox++;
}
DILN * Read_horibarnew(void){
  DILN *t;
  char temp,*pt;
  int i, n,l;
  int *tmp;
  tmp = (int *) malloc(sizeof(int));
  *tmp =1;
  t = (DILN *) malloc(sizeof(DILN));
  GETDATALINE;
  sscanf(buff,"%c",&(t->code));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x1),&(t->y1));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->xgap),&(t->ygap));
  GETDATALINE;
  sscanf(buff,"%d",&(t->lngth));
  GETDATALINE;
  sscanf(buff,"%d",&(t->width));
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->nx),&(t->ny));
  n = t->nx*t->ny;
  t->xpm = (void **)malloc(sizeof(char *)*3*n);
  t->bkgr = (int *)malloc(sizeof(int)*n);
  for(i=0;i<n;i++) { t->bkgr[i]=-1;}
  GETDATALINE;
  if(NULLDATA()) {
    t->sw = NULL;
  }
  else {
    t->sw = (int *) malloc(sizeof(int)*n);
    sscanf(buff,"%d",&(t->sw[0]));
    for(i=1;i<n;i++) {
      GETDATALINE;
      sscanf(buff,"%d",&(t->sw[i]));
    }
  }
  t->titles = (char **) malloc(sizeof(char *)*(n+1));
  for(i=0;i<n;i++) {
    GETDATALINE;
    t->titles[i] = (char *)malloc(100);
    StringCopy(t->titles[i],buff);
  }
  GETDATALINE;
  sscanf(buff,"%d%d",&(t->x2),&(t->y2));
  GETDATALINE;
  if(NULLDATA()) {
    t->butncode = NULL;
  }
  else {
   t->butncode = (char *)malloc(100);
   StringCopy(t->butncode,buff);
  }
  for(i=0;i<3*n;i++) {
    GETDATALINE;
    if(!NULLDATA()) {
      t->xpm[i]= (void *)malloc(100);
      pt =(char *) t->xpm[i];
      strcpy(pt,"##");
      sscanf(buff,"%s",pt+2);
    }
    else t->xpm[i]=NULL;
  }
  for(i=0;i<n;i++) {
    GETDATALINE;
    if(!NULLDATA()) {
      sscanf(buff,"%d",(t->bkgr)+i);
    }
    else break;
  }
  GETDATALINE;
  sscanf(buff,"%d%f%d",&(t->type),&(t->fac),&(t->bordr));
  GETDATALINE;
  sscanf(buff,"%d",&(t->hide));
  if((t->hide != 0) &&(t->hide!=1)) t->hide=0;
  t->df = (int *)tmp;
  t->arg = NULL;
  t->Update = NULL;
  t->bordr=0;
  return t;
}
int Get_data_line() {
 int l,i,OK=0;
 if(fgets(buff,199,fp)==NULL) return -1;
 l = strlen(buff);
 while(l>1) {
  if((buff[0]=='/')&&(buff[1]=='/')) {
    if(fgets(buff,199,fp)==NULL) return -1;
    l = strlen(buff);
  }
  else break;
 }
 i=l-1;
 while( (i>=1)){
  if( (buff[i]=='/')&&(buff[i-1]=='/')) {OK=1;break;}
  else i--;
 }
 if(OK) buff[i-1]='\0';
 return strlen(buff);
}
Dlink *Read_gui_data(DIALOG *D,char *flname){
 Dlink *Dialink; 
 DIA *tmp;
 DIX *X; DIY *Y;DILN *H;
 DIL *h;
 int l,i;
 Dialink = Dopen();
 fp = fopen(flname,"r");
 if(fp==NULL) return Dialink;
 while( (l=Get_data_line()) >=0 ){
   if(l==0) continue;
   switch (buff[0]) {
     case 'D':  /* Dialog information */
      Read_dialog_dimensions(D);
      continue;
     case 't':
      tmp = (DIA *)Read_data_textbox(fp);
      break;
     case 'x':
      tmp = (DIA *)Read_data_selectmenu(fp);
      X = (DIX *)tmp;
      X->list = (void **)MakeSampleThumbNails((int)(X->width*0.8),12);
      break;
     case 'y':
      tmp = (DIA *)Read_data_thumbnailbrowser(fp);
      Y = (DIY *)tmp;
      Y->list =(void **)MakeSampleThumbNails((int)(Y->width),20);
      break;
     case 'r':
      tmp = (DIA *)Read_data_radiobutton(fp);
      break;
     case 'c':
      tmp = (DIA *)Read_data_checkbox(fp);
      break;
     case 's':
      tmp = (DIA *)Read_data_msgscroll(fp);
      break;
     case 'w':
      tmp = (DIA *)Read_data_browser(fp);
      break;
     case 'e':
      tmp = (DIA *)Read_data_scrollmenu(fp);
      break;
     case 'b':
      tmp = (DIA *)Read_data_buttonbox(fp);
      break;
     case 'n':
      tmp = (DIA *)Read_data_buttonboxn(fp);
      break;
     case 'N':
      tmp = (DIA *)Read_data_buttonboxnew(fp);
      break;
     case 'h':
      tmp = (DIA *)Read_data_splbuttonbox(fp);
      h = (DIL *)tmp;
      h->Update=DiaHoribarCallback;
      actcntl++,totcntl++;horicntl++;
      break;
     case 'H':
      tmp = (DIA *)Read_data_horibarnew(fp);
//      tmp = (DIA *)Read_horibarnew();
      H = (DILN *)tmp;
      H->Update=DiaHoribarCallback;
      actcntl++,totcntl++;horicntl++;
      break;
     case 'p':
      tmp = (DIA *)Read_data_pixmapbox(fp);
      break;
     case 'i':
      tmp = (DIA *)Read_data_infobox(fp);
      break;
     case 'g':
      tmp = (DIA *)Read_data_graphbox(fp);
      break;
     case 'm':
     case 'B':
     case 'M':
      tmp = (DIA *)Read_data_message(fp);
      break;
     case 'o':
      tmp = (DIA *)Read_data_progressbar(fp);
      break;
     case 'v':
      tmp = (DIA *)Read_data_vertscroll(fp);
      break;
     case 'z':
      tmp = (DIA *)Read_data_horizscroll(fp);
      break;
     case 'T':
      tmp = (DIA *)Read_data_tablebox(fp);
      break;
     case 'f':
      tmp = (DIA *)Read_data_floatslide(fp);
      break;
     case 'd':
      tmp = (DIA *)Read_data_intslide(fp);
      break;
     case 'P':
      tmp = (DIA *)Read_data_horislide(fp);
      break;
     default:
      break;
      printf("Error: Wrong code %c\n",buff[0]);
      exit(0);
   }
   Dadd(Dialink,tmp);
 }
 fclose(fp);
// printf("Read Data\n");
 return Dialink;
}
void Print_gui_structures(Dlink *Dialink,FILE *fp1,char *dianame) {
  DIT *t;
  int control =0;
  InitCounters();
  Resetlink(Dialink);
  while ((t=(DIT *)Getrecord(Dialink)) != NULL) {
    control++;
    switch(t->code) {
     case 't':
      Textbox++;
      Print_textbox(fp1,(DIT *)t,Textbox,dianame);
      break;
     case 'x':
      Brwbox++;
      Print_selectmenu(fp1,(DIX *)t,Brwbox,dianame);
      break;
     case 'y':
      Brwbox++;
      Print_ThumbnailBrowser(fp1,(DIY *)t,Brwbox,dianame);
      break;
     case 'r':
      Brwbox++;
      Print_RadioButtons(fp1,(DIRA *)t,Brwbox,dianame);
      break;
     case 'c':
      Brwbox++;
      Print_CheckBox(fp1,(DICH *)t,Brwbox,dianame);
      break;
     case 'w':
      Brwbox++;
      Print_browser(fp1,(DIW *)t,Brwbox,dianame);
      break;
     case 'e':
      Brwbox++;
      Print_scrollmenu(fp1,(DIE *)t,Brwbox,dianame);
      break;
     case 's':
      Brwbox++;
      Print_Msgscroll(fp1,(DIS *)t,Brwbox,dianame);
      break;
     case 'b':
      Butbox++;
      Print_buttonbox(fp1,(DIB *)t,Butbox,dianame);
      break;
     case 'n':
      Butbox++;
      Print_buttonboxn(fp1,(DIN *)t,Butbox,dianame);
      break;
     case 'N':
      Butbox++;
      Print_buttonboxnew(fp1,(DIBN *)t,Butbox,dianame);
      break;
     case 'h':
      Hbox++;
      Print_splbuttonbox(fp1,(DIL *)t,Hbox,dianame);
      break;
     case 'H':
      Hbox++;
      Print_horibarnew(fp1,(DILN *)t,Hbox,dianame);
      break;
     case 'p':
      Pixbox++;
      Print_pixmapbox(fp1,(DIP *)t,Pixbox,dianame);
      break;
     case 'i':
      Ibox++;
      Print_infobox(fp1,(DII *)t,Ibox,dianame);
      break;
     case 'g':
      Gbox++;
      Print_graphbox(fp1,(DIG *)t,Gbox,dianame);
      break;
     case 'm':
     case 'B':
      Mbox++;
      Print_message(fp1,(DIM *)t,Mbox,dianame);
      break;
     case 'M':
      Mbox++;
      Print_displaybox(fp1,(DIM *)t,Mbox,dianame);
      break;
     case 'o':
      Mbox++;
      Print_progressbar(fp1,(DIO *)t,Mbox,dianame);
      break;
     case 'v':
      Vertbox++;
      Print_vertscroll(fp1,(DIV *)t,Vertbox,dianame);
      break;
     case 'z':
      Horizbox++;
      Print_horizscroll(fp1,(DIZ *)t,Horizbox,dianame);
      break;
     case 'T':
      Tblbox++;
      Print_tablebox(fp1,(DIT *)t,Tblbox,dianame);
      break;
     case 'f':
      Sfbox++;
      Print_floatslide(fp1,(DIF *)t,Sfbox,dianame);
      break;
     case 'd':
      Sibox++;
      Print_intslide(fp1,(DID *)t,Sibox,dianame);
      break;
     case 'P':
      Sibox++;
      Print_horislide(fp1,(DIHB *)t,Sibox,dianame);
      break;
     default:
      break;
    }
  }
}
void Print_gui_freememory(Dlink *Dialink,FILE *fp1,char *dianame) {
  DIT *t;
  DIRA *r;
  DICH *c;
  int control =0;
  InitCounters();
  Resetlink(Dialink);
  while ((t=(DIT *)Getrecord(Dialink)) != NULL) {
    control++;
    switch(t->code) {
     case 't':
      break;
     case 'x':
      Brwbox++;
      break;
     case 'y':
      Brwbox++;
      break;
     case 'r':
      Brwbox++;
//      Print_RadioButtons(fp1,(DIRA *)t,Brwbox,dianame);
//      fprintf(fp1,"  kgFreeDouble((void **)th%-d);\n",Listitem++);
      fprintf(fp1,"  kgFreeDouble((void **)(d[%-d].r->list));\n",control-1);
      Listitem++;
      break;
     case 'c':
      Brwbox++;
//      Print_CheckBox(fp1,(DICH *)t,Brwbox,dianame);
//      fprintf(fp1,"  kgFreeDouble((void **)th%-d);\n",Listitem++);
      fprintf(fp1,"  kgFreeDouble((void **)(d[%-d].c->list));\n",control-1);
      Listitem++;
      break;
     case 'w':
      Brwbox++;
      break;
     case 'e':
      Brwbox++;
      break;
     case 's':
      Brwbox++;
      break;
     case 'n':
     case 'b':
      Butbox++;
      break;
     case 'N':
      Butbox++;
      break;
     case 'h':
      Hbox++;
      break;
     case 'H':
      Hbox++;
      break;
     case 'p':
      Pixbox++;
      break;
     case 'i':
      Ibox++;
      break;
     case 'g':
      Gbox++;
      break;
     case 'm':
     case 'B':
     case 'M':
      Mbox++;
      break;
     case 'T':
      Tblbox++;
      break;
     case 'f':
      Sfbox++;
      break;
     case 'd':
      Sibox++;
      break;
     case 'P':
      Sibox++;
      break;
     default:
      break;
    }
  }
}
void get_char_codes(char *loc,T_ELMT *e,int n) {
  int i,l;
  char *tmp;
  for(i=0;i<n;i++) {
    tmp = e[i].fmt;
    l = strlen(tmp);
    while( tmp[l] <=' ')l--;
    loc[i]=tmp[l];
  }
}
void Write_gui_data_info(Dlink *Dialink, FILE *fp){
  DIT *t;
  int nvar=0, control=0;;
  InitCounters();
  Resetlink(Dialink);
  fprintf(fp,"/*************************************************\n\n");
  while ((t=(DIT *)Getrecord(Dialink)) != NULL) {
    control++;
    switch(t->code) {
     case 't':
      Textbox++;
      nvar = (t->nx*t->ny);
      fprintf(fp,"    Text_Box%-d  %d data values\n",Textbox,nvar);
      break;
     case 'x':
      Brwbox++;
      fprintf(fp,"    Selectmenu%-d  1 data value\n",Brwbox);
      break;
     case 'y':
      Brwbox++;
      fprintf(fp,"    ThumbnailBrowser%-d  1 data value\n",Brwbox);
      break;
     case 'r':
      Brwbox++;
      fprintf(fp,"    RadioButtons%-d  1 data value\n",Brwbox);
      break;
     case 'c':
      Brwbox++;
      fprintf(fp,"    CheckBox%-d  1 data value\n",Brwbox);
      break;
     case 'w':
      Brwbox++;
      fprintf(fp,"    Browser%-d  1 data value\n",Brwbox);
      break;
     case 'e':
      Brwbox++;
      fprintf(fp,"    Scrollmenu%-d  1 data value\n",Brwbox);
      break;
     case 'b':
      Butbox++;
      break;
     case 'n':
      Butbox++;
      break;
     case 'N':
      Butbox++;
      fprintf(fp,"    Buttonbox%-d (new) 1 data value\n",Butbox);
      break;
     case 'T':
      Tblbox++;
      nvar = (t->nx*t->ny);
      fprintf(fp,"    TableBox%-d  %d data values\n",Tblbox,nvar);
      break;
     case 'f':
      Sfbox++;
      fprintf(fp,"    Floatslidebar%-d  1 data value\n",Sfbox);
      break;
     case 'd':
      Sibox++;
      fprintf(fp,"    Integerslidebar%-d  1 data value\n",Sibox);
      break;
     case 'P':
      Sibox++;
      fprintf(fp,"    Integerslidebar%-d  1 data value\n",Sibox);
      break;
     default:
      break;
    }
  }
  fprintf(fp,"\n*************************************************/\n");
}
void Align_items(DIALOG *D) {
  int i=0,V=5;
  DIA *d;
  DIT *t;
  d= D->d;
  int x2,y1,xl,yl;
  int f;
  while ((t=d[i].t) != NULL) {
    i++;
      xl = t->x2 - t->x1;
      yl = t->y2 - t->y1;
      x2 = t->x2;
      y1 = t->y1;
      f = (int)((float)y1/(float)V+0.5001);
      y1 = f*V;
      f = (int)((float)x2/(float)V+0.5001);
      x2 = f*V;
      t->x1 = x2-xl;
      t->x2 = x2;
      t->y1= y1;
      t->y2= y1+yl;
  }
}
void Hori_Align_items(DIALOG *D) {
  int i=0,V=5;
  DIA *d;
  DIT *t;
  d= D->d;
  int x2,y1,xl,yl;
  int f;
  while ((t=d[i].t) != NULL) {
    i++;
      xl = t->x2 - t->x1;
      yl = t->y2 - t->y1;
      x2 = t->x2;
      y1 = t->y1;
      f = (int)((float)x2/(float)V+0.5001);
      x2 = f*V;
      t->x1 = x2-xl;
      t->x2 = x2;
      t->y1= y1;
      t->y2= y1+yl;
  }
}
void Vert_Align_items(DIALOG *D) {
  int i=0,V=5;
  DIA *d;
  DIT *t;
  d= D->d;
  int x2,y1,xl,yl;
  int f;
  while ((t=d[i].t) != NULL) {
    i++;
      xl = t->x2 - t->x1;
      yl = t->y2 - t->y1;
      x2 = t->x2;
      y1 = t->y1;
      f = (int)((float)y1/(float)V+0.5001);
      y1 = f*V;
      t->x1 = x2-xl;
      t->x2 = x2;
      t->y1= y1;
      t->y2= y1+yl;
  }
}
void WriteTextBoxCallback(int count,FILE *fp,char *dianame) {
 fprintf(Inc,"int  %-stextbox%-dcallback(int cellno,int i,void *Tmp);\n",
             dianame,count);
 fprintf(fp,"int  %-stextbox%-dcallback(int cellno,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /************************************************* \n");
 fprintf(fp,"   cellno: current cell counted along column strting with 0 \n");
 fprintf(fp,"           ie 0 to (nx*ny-1) \n");
 fprintf(fp,"   i     : widget id starting from 0 \n");
 fprintf(fp,"   Tmp   : Pointer to DIALOG \n");
 fprintf(fp,"   *************************************************/ \n");
 fprintf(fp,"  DIALOG *D;DIT *T;T_ELMT *e; \n");
 fprintf(fp,"  int ret=1;\n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  T = (DIT *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  e = T->elmt;\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
void WriteTableBoxCallback(int count,FILE *fp,char *dianame) {
 fprintf(Inc,"int  %-stablebox%-dcallback(int cellno,int i,void *Tmp);\n",
             dianame,count);
 fprintf(fp,"int  %-stablebox%-dcallback(int cellno,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /************************************************* \n");
 fprintf(fp,"   cellno: current cell counted along column strting with 0 \n");
 fprintf(fp,"           ie 0 to (nx*ny-1) \n");
 fprintf(fp,"           However cellno got 2 special values\n");
 fprintf(fp,"             1. SCROLL_DOWN a scrolldown action\n");
 fprintf(fp,"             2. SCROLL_UP a scrolldown action\n");
 fprintf(fp,"             which may be ignored or peocessed\n");
 fprintf(fp,"   i     : widget id starting from 0 \n");
 fprintf(fp,"   Tmp   : Pointer to DIALOG \n");
 fprintf(fp,"   *************************************************/ \n");
 fprintf(fp,"  DIALOG *D;DIT *T;T_ELMT *e; \n");
 fprintf(fp,"  int ret=1;\n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  T = (DIT *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  e = T->elmt;\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
void WriteSelectmenuCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    item : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIX *X;void *pt; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  pt = D->pt;\n");
 fprintf(fp,"  X = (DIX *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  switch(item) {\n");
 fprintf(fp,"    case 1: \n      break;\n");
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbrowser%-dinit(DIX *X,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbrowser%-dinit(DIX *X,void *pt) {\n", dianame,count);
 fprintf(fp," // One may setup browser list here by setting X->list\n", dianame,count);
 fprintf(fp," // if it need to be freed set it as X->pt also\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteThumbnailBrowserCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  DIALOG *D;DIY *Y;void *pt; \n");
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    item : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  pt = D->pt;\n");
 fprintf(fp,"  Y = (DIY *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  switch(item) {\n");
 fprintf(fp,"    case 1: \n      break;\n");
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbrowser%-dinit(DIY *Y,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbrowser%-dinit(DIY *Y,void *pt) {\n", dianame,count);
 fprintf(fp," // One may setup browser list here by setting Y->list\n", dianame,count);
 fprintf(fp," // if it need to be freed set it as Y->pt also\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteRadioButtonsCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    item : selected item (1 to max_item)  not any specific relevence\n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIRA *R;DIALOG *D;void *pt; \n");
 fprintf(fp,"  ThumbNail **th; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  pt = D->pt;\n");
 fprintf(fp,"  R = (DIRA *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  th = (ThumbNail **) R->list;\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbrowser%-dinit(DIRA *R,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbrowser%-dinit(DIRA *R,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteCheckBoxCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    item : selected item (1 to max_item)  not any specific relevence\n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DICH *C;DIALOG *D;void *pt; \n");
 fprintf(fp,"  ThumbNail **th; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  pt = D->pt;\n");
 fprintf(fp,"  C = (DICH *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  th = (ThumbNail **) C->list;\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbrowser%-dinit(DICH *C,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbrowser%-dinit(DICH *C,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteButnBoxNewCallback(int count,int nb,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbutton%-dcallback(int key,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbutton%-dcallback(int key,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  DIALOG *D;DIBN *B; \n");
 fprintf(fp,"  int n,ret =0; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  B = (DIBN *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  n = B->nx*B->ny;\n");
 fprintf(fp,"  switch(key) {\n");
 for(i=0;i<nb;i++) {
   fprintf(fp,"    case %-d: \n      break;\n",i+1);
 }
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbutton%-dinit(DIBN *B,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbutton%-dinit(DIBN *B,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteButnBoxCallback(int count,int nb,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbutton%-dcallback(int butno,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbutton%-dcallback(int butno,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    butno : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIB *B; \n");
 fprintf(fp,"  int n,ret =0; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  B = (DIB *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  n = B->nx*B->ny;\n");
 fprintf(fp,"  switch(butno) {\n");
 for(i=0;i<nb;i++) {
   fprintf(fp,"    case %-d: \n      break;\n",i+1);
 }
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbutton%-dinit(DIB *B,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbutton%-dinit(DIB *B,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteButnBoxnCallback(int count,int nb,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbutton%-dcallback(int butno,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbutton%-dcallback(int butno,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    butno : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIN *B; \n");
 fprintf(fp,"  int n,ret =0; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  B = (DIN *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  n = B->nx*B->ny;\n");
 fprintf(fp,"  switch(butno) {\n");
 for(i=0;i<nb;i++) {
   fprintf(fp,"    case %-d: \n      break;\n",i+1);
 }
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbutton%-dinit(DIN *B,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbutton%-dinit(DIN *B,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteHoriBarCallback(int count,int nb,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-ssplbutton%-dcallback(int butno,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-ssplbutton%-dcallback(int butno,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    butno : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIL *B; \n");
 fprintf(fp,"  int n,ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  B = (DIL *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  n = B->nx;\n");
 fprintf(fp,"  switch(butno) {\n");
 for(i=0;i<nb;i++) {
   fprintf(fp,"    case %-d: \n      break;\n",i+1);
 }
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-ssplbutton%-dinit(DIL *B,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-ssplbutton%-dinit(DIL *B,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteHoriBarNewCallback(int count,int nb,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-shoribar%-dcallback(int butno,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-shoribar%-dcallback(int butno,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    butno : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DILN *B; \n");
 fprintf(fp,"  int n,ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  B = (DILN *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  n = B->nx;\n");
 fprintf(fp,"  switch(butno) {\n");
 for(i=0;i<nb;i++) {
   fprintf(fp,"    case %-d: \n      break;\n",i+1);
 }
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-shbutton%-dinit(DILN *H,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-shbutton%-dinit(DILN *H,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteBrowserCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    item : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIW *B; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  B = (DIW *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  switch(item) {\n");
 fprintf(fp,"    case 1: \n      break;\n");
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
void WriteScrollmenuCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sbrowser%-dcallback(int item,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    item : selected item (1 to max_item) \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIE *E;void *pt; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  pt = D->pt;\n");
 fprintf(fp,"  E = (DIE *)kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  switch(item) {\n");
 fprintf(fp,"    case 1: \n      break;\n");
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"void  %-sbrowser%-dinit(DIE *E,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbrowser%-dinit(DIE *E,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteMsgScrollinit(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"void  %-sbrowser%-dinit(DIS *S,void *pt) ;\n", dianame,count);
 fprintf(fp,"void  %-sbrowser%-dinit(DIS *S,void *pt) {\n", dianame,count);
 fprintf(fp,"}\n");
}
void WriteSlideDCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sdslide%-dcallback(int val,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sdslide%-dcallback(int val,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    val : current value \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DID *SD; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  SD = (DID *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
void WriteSlideHCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sdslide%-dcallback(int val,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sdslide%-dcallback(int val,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    val : current value \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIHB *SD; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  SD = (DIHB *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
void WriteSlideFCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-sfslide%-dcallback(double val,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-sfslide%-dcallback(double val,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    val : current value \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIF *F; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  F = (DIF *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
void WriteVertScrollCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-svertscroll%-dcallback(double val,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-svertscroll%-dcallback(double val,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    val : current value \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIV *V; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  V = (DIV *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
void WriteHorizScrollCallback(int count,FILE *fp,char *dianame) {
 int i;
 fprintf(Inc,"int  %-shorizscroll%-dcallback(double val,int i,void *Tmp) ;\n",
             dianame,count);
 fprintf(fp,"int  %-shorizscroll%-dcallback(double val,int i,void *Tmp) {\n",
             dianame,count);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    val : current value \n");
 fprintf(fp,"    i :  Index of Widget  (0 to max_widgets-1) \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  DIALOG *D;DIZ *Z; \n");
 fprintf(fp,"  int ret=1; \n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  Z = (DIZ *) kgGetWidget(Tmp,i);\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
int Writeinitroutine(FILE *fp,char *dianame) {
 fprintf(Inc,"int %-sinit(void *Tmp) ;\n",dianame);
 fprintf(Inc,"int %-scleanup(void *Tmp) ;\n",dianame);
 fprintf(fp,"int %-sinit(void *Tmp) {\n",dianame);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  /* you add any initialisation here */\n");
 fprintf(fp,"  int ret = 1;\n");
 fprintf(fp,"  DIALOG *D;void *pt;\n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  pt = D->pt;\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(fp,"int %-scleanup(void *Tmp) {\n",dianame);
 fprintf(fp,"  /* you add any cleanup/mem free here */\n");
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  int ret = 1;\n");
 fprintf(fp,"  DIALOG *D;void *pt;\n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  pt = D->pt;\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
int WriteDefaultCallback(FILE *fp,char *dianame) {
 fprintf(Inc,"int %-sCallBack(void *Tmp,void *tmp) ;\n",dianame);
 fprintf(fp,"int %-sCallBack(void *Tmp,void *tmp) {\n",dianame);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"    tmp :  Pointer to KBEVENT  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  int ret = 0;\n");
 fprintf(fp,"  DIALOG *D;\n");
 fprintf(fp,"  KBEVENT *kbe;\n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  kbe = (KBEVENT *)tmp;\n");
 fprintf(fp,"  if(kbe->event ==1) {\n");
 fprintf(fp,"    if(kbe->button ==1) {\n");
 fprintf(fp,"    }\n");
 fprintf(fp,"  }\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(Inc,"int %-sResizeCallBack(void *Tmp) ;\n",dianame);
 fprintf(Inc,"int %-sWaitCallBack(void *Tmp) ;\n",dianame);
 fprintf(fp,"int %-sResizeCallBack(void *Tmp) {\n",dianame);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  int ret = 0;\n");
 fprintf(fp,"  int xres,yres,dx,dy;\n");
 fprintf(fp,"  DIALOG *D;\n");
 fprintf(fp,"  D = (DIALOG *)Tmp;\n");
 fprintf(fp,"  kgGetWindowSize(D,&xres,&yres);\n");
 fprintf(fp,"  dx = xres - D->xl;\n");
 fprintf(fp,"  dy = yres - D->yl;\n");
 fprintf(fp,"  /* extra code */\n");
 fprintf(fp,"  D->xl= xres;\n");
 fprintf(fp,"  D->yl= yres;\n");
 fprintf(fp,"  kgRedrawDialog(D);\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
 fprintf(fp,"int %-sWaitCallBack(void *Tmp) {\n",dianame);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    Tmp :  Pointer to DIALOG  \n");
 fprintf(fp,"    Called while waiting for event  \n");
 fprintf(fp,"    return value 1 will close the the UI  \n");
 fprintf(fp,"   ***********************************/ \n");
 fprintf(fp,"  int ret = 0;\n");
 fprintf(fp,"  return ret;\n");
 fprintf(fp,"}\n");
}
int WriteGboxinit(int control,FILE *fp,char *dianame){
  fprintf(Inc,"void %-sgbox%-dinit(int i,void *Tmp) ;\n",dianame,control);
  fprintf(fp,"void %-sgbox%-dinit(int i,void *Tmp) {\n",dianame,control);
 fprintf(fp,"  /*********************************** \n");
 fprintf(fp,"    int routine for grahics area \n");
 fprintf(fp,"   ***********************************/ \n");
  fprintf(fp,"  DIALOG *D;void *pt;\n");
  fprintf(fp,"  DIG *G;\n");
  fprintf(fp,"  D = (DIALOG *)Tmp;\n");
  fprintf(fp,"  pt = D->pt;\n");
  fprintf(fp,"  G = D->d[i].g;\n");
  fprintf(fp,"  G->D = (void *)(Tmp);\n");
  fprintf(fp,"  return ;\n");
  fprintf(fp,"}\n");
}
void WriteCallBacks(Dlink *Dialink, FILE *fp,char *dianame){
  int nvar=0, control=0;
  DIT *t;
  DIL *h;
  DILN *H;
  DIBN *n;
  DIB *b;
  DIN *N;
  InitCounters();
  Resetlink(Dialink);
  while ((t=(DIT *)Getrecord(Dialink)) != NULL) {
    control++;
    switch(t->code) {
     case 't':
      Textbox++;
      WriteTextBoxCallback(Textbox,fp,dianame);
      break;
     case 'x':
      Brwbox++;
      WriteSelectmenuCallback(Brwbox,fp,dianame);
      break;
     case 'y':
      Brwbox++;
      WriteThumbnailBrowserCallback(Brwbox,fp,dianame);
      break;
     case 'r':
      Brwbox++;
      WriteRadioButtonsCallback(Brwbox,fp,dianame);
      break;
     case 'c':
      Brwbox++;
      WriteCheckBoxCallback(Brwbox,fp,dianame);
      break;
     case 'w':
      Brwbox++;
      WriteBrowserCallback(Brwbox,fp,dianame);
      break;
     case 's':
      Brwbox++;
      WriteMsgScrollinit(Brwbox,fp,dianame);
      break;
     case 'e':
      Brwbox++;
      WriteScrollmenuCallback(Brwbox,fp,dianame);
      break;
     case 'b':
      b = (DIB *)t;
      Butbox++;
      WriteButnBoxCallback(Butbox,b->nx*b->ny,fp,dianame);
      break;
     case 'n':
      N = (DIN *)t;
      Butbox++;
      WriteButnBoxnCallback(Butbox,N->nx*N->ny,fp,dianame);
      break;
     case 'N':
      n = (DIBN *)t;
      Butbox++;
      WriteButnBoxNewCallback(Butbox,n->nx*n->ny,fp,dianame);
      break;
     case 'h':
      Hbox++;
      h = (DIL *)t;
      WriteHoriBarCallback(Hbox,h->nx,fp,dianame);
      break;
     case 'H':
      Hbox++;
      H = (DILN *)t;
      WriteHoriBarNewCallback(Hbox,H->nx,fp,dianame);
      break;
     case 'T':
      Tblbox++;
      WriteTableBoxCallback(Tblbox,fp,dianame);
      break;
     case 'f':
      Sfbox++;
      WriteSlideFCallback(Sfbox,fp,dianame);
      break;
     case 'd':
      Sibox++;
      WriteSlideDCallback(Sibox,fp,dianame);
      break;
     case 'v':
      Vertbox++;
      WriteVertScrollCallback(Vertbox,fp,dianame);
      break;
     case 'z':
      Horizbox++;
      WriteHorizScrollCallback(Horizbox,fp,dianame);
      break;
     case 'P':
      Sibox++;
      WriteSlideHCallback(Sibox,fp,dianame);
      break;
     case 'g':
      Gbox++;
      WriteGboxinit(Gbox,fp,dianame);
      break;
     default:
      break;
    }
  }
  Writeinitroutine(fp,dianame);
  WriteDefaultCallback(fp,dianame);
  
}
char * Get_gui_args(Dlink *Dialink) {
  DIT *t;
  char *tmp=NULL;
  int nvar=0;
  Resetlink(Dialink);
  while ((t=(DIT *)Getrecord(Dialink)) != NULL) {
    switch(t->code) {
     case 't':
     case 'T':
      nvar += (t->nx*t->ny);
      break;
     case 'y':
     case 'c':
     case 'r':
      nvar++;
      break;
     case 'x':
     case 'w':
     case 'e':
     case 'N':
      nvar++;
      break;
     case 'n':
      break;
     case 'f':
      nvar++;
      break;
     case 'd':
     case 'P':
      nvar++;
      break;
     default:
      break;
    }
  }
  tmp= (char *)malloc(nvar+2);
  Resetlink(Dialink);
  nvar=0;
  while ((t=(DIT *)Getrecord(Dialink)) != NULL) {
    switch(t->code) {
     case 't':
     case 'T':
      get_char_codes(tmp+nvar,t->elmt,t->nx*t->ny);
      nvar +=(t->nx*t->ny);
      break;
     case 'y':
     case 'r':
     case 'c':
     case 'x':
     case 'w':
     case 'e':
     case 'N':
      tmp[nvar]='d';
      nvar++;
      break;
     case 'f':
      tmp[nvar]='f';
      nvar++;
      break;
     case 'd':
      tmp[nvar]='d';
      nvar++;
      break;
     case 'P':
      tmp[nvar]='d';
      nvar++;
      break;
     default:
      break;
    }
  }
  tmp[nvar]='\0';
  return tmp;
}
#define MaxMin(z) {\
  if(xmin > (z)->x1 ) xmin = (z)->x1;\
  if(ymin > (z)->y1 ) ymin = (z)->y1;\
  if(xmax < (z)->x1 ) xmax = (z)->x2;\
  if(ymax < (z)->y1 ) ymax = (z)->y2;\
}
void Get_gui_limits(Dlink *Dialink,int *x1,int *y1,
           int *x2,int *y2) {
  DIT *t;DIX *x; DIY *y; DIW *w; DIB *b; DIN *N;
  DIBN *n;DIL *h; DILN *H; DIP *p; DIG *g;
  DIM *m;
  int xmin=0,ymin,xmax,ymax;
  ymin = xmin;
  xmax = 10, ymax = xmax;
  Resetlink(Dialink);
  while ((t=(DIT *)Getrecord(Dialink)) != NULL) {
    switch(t->code) {
     case 't':
     case 'T':
      MaxMin((DIT *)t);
      break;
     case 'x':
      MaxMin((DIX *)t);
      break;
     case 'y':
     case 'r':
     case 'c':
      MaxMin((DIY *)t);
      break;
     case 'w':
     case 'e':
     case 's':
      MaxMin((DIW *)t);
      break;
     case 'b':
      MaxMin((DIB *)t);
      break;
     case 'n':
      MaxMin((DIN *)t);
      break;
     case 'N':
      MaxMin((DIBN *)t);
      break;
     case 'h':
      MaxMin((DIL *)t);
      break;
     case 'H':
      MaxMin((DILN *)t);
      break;
     case 'p':
      MaxMin((DIP *)t);
      break;
     case 'i':
      MaxMin((DII *)t);
      break;
     case 'g':
      MaxMin((DIG *)t);
      break;
     case 'm':
     case 'B':
     case 'M':
     case 'o':
      MaxMin((DIM *)t);
      break;
     case 'v':
      MaxMin((DIV *)t);
      break;
     case 'z':
      MaxMin((DIZ *)t);
      break;
     case 'f':
      MaxMin((DIF *)t);
      break;
     case 'd':
      MaxMin((DID *)t);
      break;
     case 'P':
      MaxMin((DID *)t);
      break;
     default:
      break;
    }
  }
  *x1 = xmin; *y1=ymax;
  *x2 = xmax; *y2=-ymin;
}
void assign_dia_names(Dlink *L,FILE *fp1,char *dianame) {
  int n=-1,brwsr=0,butn=0,hbutn=0;
  DIT *t;
  Resetlink(L);
  while ((t=(DIT *)Getrecord(L)) != NULL) {
    n++;
    switch(t->code) {
#if 0
     case 't':
      fprintf(fp1,"  d[%-d].t = &t%-d;\n",n,n);
      break;
     case 'o':
      fprintf(fp1,"  d[%-d].o = &o%-d;\n",n,n);
      break;
     case 'v':
      fprintf(fp1,"  d[%-d].v = &v%-d;\n",n,n);
      break;
     case 'z':
      fprintf(fp1,"  d[%-d].z = &z%-d;\n",n,n);
      break;
     case 'x':
      fprintf(fp1,"  d[%-d].x = &x%-d;\n",n,n);
      fprintf(fp1,"  %-sbrowser%-dinit(&x%-d,pt) ;\n", dianame,brwsr+1,n);
      brwsr++;
      break;
     case 'y':
      fprintf(fp1,"  d[%-d].y = &y%-d;\n",n,n);
      fprintf(fp1,"  %-sbrowser%-dinit(&y%-d,pt) ;\n", dianame,brwsr+1,n);
      brwsr++;
      break;
     case 'r':
      fprintf(fp1,"  d[%-d].r = &r%-d;\n",n,n);
      fprintf(fp1,"  %-sbrowser%-dinit(&r%-d,pt) ;\n", dianame,brwsr+1,n);
      brwsr++;
      break;
     case 'c':
      fprintf(fp1,"  d[%-d].c = &c%-d;\n",n,n);
      fprintf(fp1,"  %-sbrowser%-dinit(&c%-d,pt) ;\n", dianame,brwsr+1,n);
      brwsr++;
      break;
     case 'w':
      fprintf(fp1,"  d[%-d].w = &w%-d;\n",n,n);
      brwsr++;
      break;
     case 'e':
      fprintf(fp1,"  d[%-d].e = &e%-d;\n",n,n);
      brwsr++;
      break;
     case 's':
      fprintf(fp1,"  d[%-d].s = &s%-d;\n",n,n);
      fprintf(fp1,"  %-sbrowser%-dinit(&s%-d,pt) ;\n", dianame,brwsr+1,n);
      brwsr++;
      break;
     case 'b':
      fprintf(fp1,"  d[%-d].b = &b%-d;\n",n,n);
      fprintf(fp1,"  %-sbutton%-dinit(&b%-d,pt) ;\n", dianame,butn+1,n);
      butn++;
      break;
     case 'n':
     case 'N':
      fprintf(fp1,"  d[%-d].n = &n%-d;\n",n,n);
      fprintf(fp1,"  %-sbutton%-dinit(&n%-d,pt) ;\n", dianame,butn+1,n);
      butn++;
      break;
     case 'h':
      fprintf(fp1,"  d[%-d].h = &h%-d;\n",n,n);
      break;
     case 'H':
      fprintf(fp1,"  d[%-d].H = &H%-d;\n",n,n);
      fprintf(fp1,"  %-shbutton%-dinit(&H%-d,pt) ;\n", dianame,hbutn+1,n);
      hbutn++;
      break;
     case 'p':
      fprintf(fp1,"  d[%-d].p = &p%-d;\n",n,n);
      break;
     case 'i':
      fprintf(fp1,"  d[%-d].i = &i%-d;\n",n,n);
      break;
     case 'g':
      fprintf(fp1,"  d[%-d].g = &g%-d;\n",n,n);
      break;
     case 'm':
     case 'B':
     case 'M':
      fprintf(fp1,"  d[%-d].m = &m%-d;\n",n,n);
      break;
     case 'T':
      fprintf(fp1,"  d[%-d].t = &T%-d;\n",n,n);
      break;
     case 'f':
      fprintf(fp1,"  d[%-d].f = &f%-d;\n",n,n);
      break;
     case 'd':
      fprintf(fp1,"  d[%-d].d = &d%-d;\n",n,n);
      break;
     case 'P':
      fprintf(fp1,"  d[%-d].B = &d%-d;\n",n,n);
      break;
#else
     case 't':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIT));\n",n);
      fprintf(fp1,"  *d[%-d].t = t%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].t->item = -1;\n",n);
      break;
     case 'o':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIO));\n",n);
      fprintf(fp1,"  *d[%-d].o = o%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].o->item = -1;\n",n);
      break;
     case 'v':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIV));\n",n);
      fprintf(fp1,"  *d[%-d].v = v%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].v->item = -1;\n",n);
      break;
     case 'z':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIZ));\n",n);
      fprintf(fp1,"  *d[%-d].z = z%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].z->item = -1;\n",n);
      break;
     case 'x':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIX));\n",n);
      fprintf(fp1,"  %-sbrowser%-dinit(&x%-d,pt) ;\n", dianame,brwsr+1,n);
      fprintf(fp1,"  *d[%-d].x = x%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].x->item = -1;\n",n);
      brwsr++;
      break;
     case 'y':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIY));\n",n);
      fprintf(fp1,"  %-sbrowser%-dinit(&y%-d,pt) ;\n", dianame,brwsr+1,n);
      fprintf(fp1,"  *d[%-d].y = y%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].y->item = -1;\n",n);
      brwsr++;
      break;
     case 'r':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIRA));\n",n);
      fprintf(fp1,"  %-sbrowser%-dinit(&r%-d,pt) ;\n", dianame,brwsr+1,n);
      fprintf(fp1,"  *d[%-d].r = r%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].r->item = -1;\n",n);
      brwsr++;
      break;
     case 'c':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DICH));\n",n);
      fprintf(fp1,"  %-sbrowser%-dinit(&c%-d,pt) ;\n", dianame,brwsr+1,n);
      fprintf(fp1,"  *d[%-d].c = c%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].c->item = -1;\n",n);
      brwsr++;
      break;
     case 'w':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIW));\n",n);
      fprintf(fp1,"  *d[%-d].w = w%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].w->item = -1;\n",n);
      brwsr++;
      break;
     case 'e':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIE));\n",n);
      fprintf(fp1,"  *d[%-d].e = e%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].e->item = -1;\n",n);
      brwsr++;
      break;
     case 's':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIS));\n",n);
      fprintf(fp1,"  %-sbrowser%-dinit(&s%-d,pt) ;\n", dianame,brwsr+1,n);
      fprintf(fp1,"  *d[%-d].s = s%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].s->item = -1;\n",n);
      brwsr++;
      break;
     case 'b':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIB));\n",n);
      fprintf(fp1,"  %-sbutton%-dinit(&b%-d,pt) ;\n", dianame,butn+1,n);
      fprintf(fp1,"  *d[%-d].b = b%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].b->item = -1;\n",n);
      butn++;
      break;
     case 'n':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIN));\n",n);
      fprintf(fp1,"  %-sbutton%-dinit(&b%-d,pt) ;\n", dianame,butn+1,n);
      fprintf(fp1,"  *d[%-d].N = b%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].N->item = -1;\n",n);
      butn++;
      break;
     case 'N':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIBN));\n",n);
      fprintf(fp1,"  %-sbutton%-dinit(&n%-d,pt) ;\n", dianame,butn+1,n);
      fprintf(fp1,"  *d[%-d].n = n%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].n->item = -1;\n",n);
      butn++;
      break;
     case 'h':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIL));\n",n);
      fprintf(fp1,"  %-ssplbutton%-dinit(&h%-d,pt) ;\n", dianame,hbutn+1,n);
      fprintf(fp1,"  *d[%-d].h = h%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].h->item = -1;\n",n);
      hbutn++;
      break;
     case 'H':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DILN));\n",n);
      fprintf(fp1,"  %-shbutton%-dinit(&H%-d,pt) ;\n", dianame,hbutn+1,n);
      fprintf(fp1,"  *d[%-d].H = H%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].H->item = -1;\n",n);
      hbutn++;
      break;
     case 'p':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIP));\n",n);
      fprintf(fp1,"  *d[%-d].p = p%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].p->item = -1;\n",n);
      break;
     case 'i':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DII));\n",n);
      fprintf(fp1,"  *d[%-d].i = i%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].i->item = -1;\n",n);
      break;
     case 'g':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIG));\n",n);
      fprintf(fp1,"  *d[%-d].g = g%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].g->item = -1;\n",n);
      break;
     case 'm':
     case 'B':
     case 'M':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIM));\n",n);
      fprintf(fp1,"  *d[%-d].m = m%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].m->item = -1;\n",n);
      break;
     case 'T':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIT));\n",n);
      fprintf(fp1,"  *d[%-d].t = T%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].t->item = -1;\n",n);
      break;
     case 'f':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIF));\n",n);
      fprintf(fp1,"  *d[%-d].f = f%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].f->item = -1;\n",n);
      break;
     case 'd':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DID));\n",n);
      fprintf(fp1,"  *d[%-d].d = d%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].d->item = -1;\n",n);
      break;
     case 'P':
      fprintf(fp1,"  d[%d].t = (DIT *)malloc(sizeof(DIHB));\n",n);
      fprintf(fp1,"  *d[%-d].B = d%-d;\n",n,n);
      fprintf(fp1,"  d[%-d].B->item = -1;\n",n);
      break;
#endif
     default:
      break;
    }
  }
  fprintf(fp1,"  d[%-d].t = NULL;\n",n+1);
  
}
void init_dia_array(Dlink *L,DIA *d) {
  int n=-1;
  DIT *t;
  Resetlink(L);
  while ((t=(DIT *)Getrecord(L)) != NULL) {
    n++;
    switch(t->code) {
     case 't':
      d[n].t = (DIT *)t;
      break;
     case 'x':
      d[n].x = (DIX *)t;
      break;
     case 'y':
      d[n].y = (DIY *)t;
      break;
     case 'r':
      d[n].r = (DIRA *)t;
      break;
     case 'c':
      d[n].c = (DICH *)t;
      break;

     case 'w':
      d[n].w = (DIW *)t;
      break;
     case 'e':
      d[n].e = (DIE *)t;
      break;
     case 's':
      d[n].s = (DIS *)t;
      break;
     case 'b':
      d[n].b = (DIB *)t;
      break;
     case 'n':
      d[n].N = (DIN *)t;
      break;
     case 'N':
      d[n].n = (DIBN *)t;
      break;
     case 'h':
      d[n].h = (DIL *)t;
      break;
     case 'H':
      d[n].H = (DILN *)t;
      break;
     case 'p':
      d[n].p = (DIP *)t;
      break;
     case 'i':
      d[n].i = (DII *)t;
      break;
     case 'g':
      d[n].g = (DIG *)t;
      break;
     case 'm':
     case 'B':
     case 'M':
      d[n].m = (DIM *)t;
      break;
     case 'o':
      d[n].o = (DIO *)t;
      break;
     case 'v':
      d[n].v = (DIV *)t;
      break;
     case 'z':
      d[n].z = (DIZ *)t;
      break;
     case 'T':
      d[n].t = (DIT *)t;
      break;
     case 'f':
      d[n].f = (DIF *)t;
      break;
     case 'd':
      d[n].d = (DID *)t;
      break;
     case 'P':
      d[n].B = (DIHB *)t;
      break;
     default:
      break;
    }
  }
  d[n+1].t = NULL;
  
}
void Write_gui_variables(char *codes,FILE *fp1){
  int i,n;
  char ch;
  i=0;
  while(codes[i] != '\0') {
    switch(codes[i]) {
      case 'f':
      case 'F':
        fprintf(fp1,"   double v%-d = 0.0;\n",i);
        break;
      case 'd':
        fprintf(fp1,"   int   v%-d = 1;\n",i);
        break;
      case 's':
        fprintf(fp1,"   char  v%-d[500]=\"\" ;\n",i);
        break;
      default:
        break;
    }
    i++;
  }
  if(i>0) fprintf(fp1,"   void* v[%-d];\n",i);
  else    fprintf(fp1,"   void **v=NULL;\n");
  n=i;
  for(i=0;i<n;i++) {
    if(codes[i] =='s')fprintf(fp1,"   v[%d]=(void *)(v%-d);\n",i,i);
    else              fprintf(fp1,"   v[%d]=(void *)(&v%-d);\n",i,i);
  }
  fprintf(fp1,"   void *pt=NULL; /* pointer to send any extra information */\n");
}
void Write_group_variables(char *codes,FILE *fp1){
  int i,n;
  char ch;
  i=0;
  while(codes[i] != '\0') {
    switch(codes[i]) {
      case 'f':
      case 'F':
        fprintf(fp1,"   double *v%-d ;\n",i);
        fprintf(fp1,"   v%-d = (double *)malloc(sizeof(double));\n",i);
        fprintf(fp1,"   *v%-d = 0.0;\n",i);
        break;
      case 'd':
        fprintf(fp1,"   int  *v%-d ;\n",i);
        fprintf(fp1,"   v%-d = (int *)malloc(sizeof(int));\n",i);
        fprintf(fp1,"   *v%-d = 1;\n",i);
        break;
      case 's':
        fprintf(fp1,"   char  *v%-d ;\n",i);
        fprintf(fp1,"   v%-d = (char *)malloc(sizeof(char)*500);\n",i);
        fprintf(fp1,"   v%-d[0] = '\\0';\n",i);
        break;
      default:
        break;
    }
    i++;
  }
  if(i>0) {
    fprintf(fp1,"   void** v=(void **)malloc(sizeof(void*)*%-d);\n",i+1);
    fprintf(fp1,"   v[%-d]=NULL;\n",i);
  }
  else    fprintf(fp1,"   void **v=NULL;\n");
  n=i;
  for(i=0;i<n;i++) {
    if(codes[i] =='s')fprintf(fp1,"   v[%d]=(void *)(v%-d);\n",i,i);
    else              fprintf(fp1,"   v[%d]=(void *)(v%-d);\n",i,i);
  }
  fprintf(fp1,"   void *pt=NULL; /* pointer to send any extra information */\n");
}
void Write_gui_args(char *codes,FILE *fp1) {
  int i,n;
  n = strlen(codes);
   fprintf(fp1,"NULL");
#if 0
  for(i=0;i<n;i++) {
    if( (i+1)%5 ==0) fprintf(fp1," \n    ");
    if(codes[i] == 's') fprintf(fp1," ,v%-d",i);
    else fprintf(fp1," ,&v%-d",i);
  }
#else
   fprintf(fp1,",v,pt");
#endif
}
Dlink *Make_controls_link(DIALOG *D){
  Dlink *L;
  DIA *d;
  int i,n,no;
  L = Dopen();
  d = D->d;
  i=0;while(d[i].t != NULL) {Dadd(L,d[i].t);i++;};
  return L;
}
void Make_gui_code(DIALOG *D,char *flname,char *dianame){
  FILE *fpc;
  Dlink *L;
  DIA *d;
  int i,n,no;
  char *codes;
  InitCounters();
  SetOptions(D);
  L = Dopen();
  d = D->d;
  i=0;while(d[i].t != NULL) {Dadd(L,d[i].t);i++;};
  fp1 = fopen(flname,"w");
  fpc = fopen(Callbackcode,"w");
  Inc = fopen(Includecode,"w");
  fprintf(fp1,"#include <kulina.h>\n");
  fprintf(fp1,"#include \"%-s\"\n",Includecode);
  fprintf(fpc,"#include <kulina.h>\n");
  WriteCallBacks(L,fpc,dianame);
  fclose(fpc);
  fclose(Inc);
  codes = Get_gui_args(L);
  fprintf(fp1,"void Modify%-sGc(Gclr *gc) {\n",dianame);
  fprintf(fp1,"/*\n");
  fprintf(fp1,"//  You may change default settings here \n");
  fprintf(fp1,"//  probably you can allow the user to create a config in $HOME\n");
  fprintf(fp1,"//  and try to read that file (if exits); so dynamic configuration is possible\n");
  fprintf(fp1,"   gc->FontSize =8;\n");
  fprintf(fp1,"   gc->Font=23;\n");
  fprintf(fp1,"*/\n");
  fprintf(fp1,"}\n");
  n = strlen(codes);

#if 1 
// Group Code
  fprintf(fp1,"int %-sGroup( DIALOG *D,void **v,void *pt) {\n",dianame);
  fprintf(fp1,"  int GrpId=0,oitems=0,i,j;\n");
  no = Dcount(L);
  fprintf(fp1,"  DIA *d=NULL,*dtmp;\n");
  Print_gui_structures(L,fp1,dianame);
  fprintf(fp1,"  dtmp = D->d;\n");
  fprintf(fp1,"  i=0;\n");
  fprintf(fp1,"  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;\n");
  fprintf(fp1,"  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+%-d));\n",(no+1));
  fprintf(fp1,"  d =dtmp+i; \n");
  fprintf(fp1,"  d[%-d].t=NULL;\n",no);
  assign_dia_names(L,fp1,dianame);
  fprintf(fp1,"  GrpId=kgOpenGrp(D);\n");
  fprintf(fp1,"  D->d = dtmp;\n");
  fprintf(fp1,"  j=0;\n");
  fprintf(fp1,"  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}\n");
  fprintf(fp1,"  return GrpId;\n");
  fprintf(fp1,"} \n");
  fprintf(fp1,"\n");
  fprintf(fp1,"/* One can also use the following code to add Widgets to an existing Dialog */\n");
  fprintf(fp1,"\n");
  fprintf(fp1,"int Make%-sGroup(DIALOG *D,void *arg) {\n",dianame);
  fprintf(fp1,"   int GrpId;\n");
  fprintf(fp1,"   WIDGETGRP *Gpt;\n");
  Write_gui_data_info(L,fp1);
  Write_group_variables(codes,fp1);
  fprintf(fp1,"   GrpId = %-sGroup(D,v,pt);\n",dianame);
  fprintf(fp1,"   Gpt = kgGetWidgetGrp(D,GrpId);\n");
  fprintf(fp1,"   Gpt->arg= v; "
                 "// kulina will double free this; you may modify\n");
  fprintf(fp1,"   return GrpId;\n");
  fprintf(fp1,"}\n");
  fprintf(fp1,"\n");
#endif
  fprintf(fp1,"int %-s( void *parent,void **v,void *pt) {\n",dianame);
  fprintf(fp1,"  int ret=1,GrpId,k;\n");
  fprintf(fp1,"  DIALOG D;\n");
  no = Dcount(L);
//  fprintf(fp1,"  DIA d[%-d];\n",(no+1));
  fprintf(fp1,"  DIA *d=NULL;\n");
  fprintf(fp1,"  D.VerId=%d;\n",VER);
  fprintf(fp1,"  kgInitUi(&D);\n");
  fprintf(fp1,"  D.d=NULL;\n");
  fprintf(fp1,"  GrpId = %-sGroup(&D,v,pt);\n",dianame);
  fprintf(fp1,"  d = D.d;\n");
  fprintf(fp1,"  D.d = d;\n");
  fprintf(fp1,"  D.bkup = %-d; /* set to 1 for backup */\n",D->bkup);
  fprintf(fp1,"  D.bor_type = %-d;\n",D->bor_type);
  fprintf(fp1,"  D.df = %d;\n",D->df);
  fprintf(fp1,"  D.tw = %d;\n",D->tw);
  fprintf(fp1,"  D.bw = %d;\n",D->bw);
  fprintf(fp1,"  D.lw = %d;\n",D->lw);
  fprintf(fp1,"  D.rw = %d;\n",D->rw);
  fprintf(fp1,"  D.xo = %d;   /* Position of Dialog */ \n",D->xo);
  fprintf(fp1,"  D.yo = %d;\n", D->yo);
  fprintf(fp1,"  D.xl = %d;    /*  Length of Dialog */\n",D->xl);
  fprintf(fp1,"  D.yl = %d;    /*  Width  of Dialog */\n",D->yl);
  fprintf(fp1,"  D.Initfun = %-sinit;    /*   init fuction for Dialog */\n",dianame);
  fprintf(fp1,"  D.Cleanupfun = %-scleanup;    /*   init fuction for Dialog */\n",dianame);
  fprintf(fp1,"  D.kbattn = %-d;    /*  1 for drawing keyborad attention */\n",D->kbattn);
  fprintf(fp1,"  D.butattn = %-d;    /*  1 for drawing button attention */\n",D->butattn);
  fprintf(fp1,"  D.fullscreen = %-d;    /*  1 for for fullscreen mode */\n",D->fullscreen);
  fprintf(fp1,"  D.Deco = %-d;    /*  1 for Window Decorration */\n",D->Deco);
  fprintf(fp1,"  D.transparency = %-f;    /*  float 1.0 for full transparency */\n",D->transparency);
  fprintf(fp1,"  D.Newwin = %-d;    /*  1 for new window not yet implemented */\n",D->Newwin);
  fprintf(fp1,"  D.DrawBkgr = %-d;    /*  1 for drawing background */\n",D->DrawBkgr);
  fprintf(fp1,"  D.Bkpixmap = NULL;    /*  background image */\n");
  fprintf(fp1,"  D.Sticky = %-d;    /*  1 for stickyness */\n",D->Sticky);
  fprintf(fp1,"  D.Resize = %-d;    /*  1 for Resize option */\n",D->Resize);
  fprintf(fp1,"  D.MinWidth = %-d;    /*   for Resize option */\n",D->MinWidth);
  fprintf(fp1,"  D.MinHeight = %-d;    /*   for Resize option */\n",D->MinHeight);
  fprintf(fp1,"#if 1 \n");
  fprintf(fp1,"  D.Callback = %-sCallBack;    /*  default callback */\n",dianame);
  fprintf(fp1,"#else \n");
  fprintf(fp1,"  D.Callback = NULL;    \n");
  fprintf(fp1,"#endif\n");
  fprintf(fp1,"  D.ResizeCallback = %-sResizeCallBack;  /*  Resize callback */\n",dianame);
  fprintf(fp1,"#if 0 \n");
  fprintf(fp1,"  D.WaitCallback = NULL;  /*  Wait callback */\n");
  fprintf(fp1,"#else \n");
  fprintf(fp1,"  D.WaitCallback = %-sWaitCallBack;  /*  Wait callback */\n",dianame);
  fprintf(fp1,"#endif\n");
  fprintf(fp1,"  D.Fixpos = %-d;    /*  1 for Fixing Position */\n",D->Fixpos);
  fprintf(fp1,"  D.NoTaskBar = %-d;    /*  1 for not showing in task bar*/\n",D->NoTaskBar);
  fprintf(fp1,"  D.NoWinMngr = 0;    /*  1 for no Window Manager*/\n");
  fprintf(fp1,"  D.StackPos = %-d;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/\n",
                                D->StackPos);
  fprintf(fp1,"  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */\n");
  fprintf(fp1,"  D.parent = parent;    /*  1 for not showing in task bar*/\n");
  fprintf(fp1,"  D.pt = pt;    /*  any data to be passed by user*/\n");

  fprintf(fp1,"//  strcpy(D.name,\"Kulina Designer ver 1.0\");    /*  Dialog name you may change */\n");
  fprintf(fp1,"  if(D.fullscreen!=1) {    /*  if not fullscreen mode */\n");
  fprintf(fp1,"     int xres,yres; \n");
  fprintf(fp1,"     kgDisplaySize(&xres,&yres); \n");
  fprintf(fp1,"      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;\n");
  fprintf(fp1,"  }\n");
  fprintf(fp1,"  else {    // for fullscreen\n");
  fprintf(fp1,"     int xres,yres; \n");
  fprintf(fp1,"     kgDisplaySize(&xres,&yres); \n");
  fprintf(fp1,"     D.xo=D.yo=0; D.xl = xres; D.yl=yres;\n");
  fprintf(fp1,"//     D.StackPos = 1; // you may need it\n");
  fprintf(fp1,"  }    /*  end of fullscreen mode */\n");
//  fprintf(fp1,"  D.SearchList=(void *)Dopen();    /*  list of directories picture search */\n");
//  fprintf(fp1,"  kgDefaultGuiTheme(&(D.gc));    /*  set colors for gui*/\n");
  fprintf(fp1,"//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/\n");
  fprintf(fp1,"//  Modify%-sGc(&(D.gc));    /*  set colors for gui*/\n",dianame);
  fprintf(fp1,"  ret= kgUi(&D);\n");
  fprintf(fp1,"  kgCleanUi(&D);\n");
  fprintf(fp1,"  return ret;\n");
  fprintf(fp1,"}\n");
  fprintf(fp1,"void *Run%-s(void *arg) {\n",dianame);
  Write_gui_data_info(L,fp1);
  Write_gui_variables(codes,fp1);
  fprintf(fp1,"   %-s(",dianame);
  Write_gui_args(codes,fp1);
  fprintf(fp1," );\n");
  fprintf(fp1,"   return NULL;\n");
  fprintf(fp1,"}\n");
  fclose(fp1);
  fpc = fopen(Maincode,"w");
  fprintf(fpc,"#include <stdio.h>\n");
  fprintf(fpc,"void *Run%-s(void *);\n",dianame);
  fprintf(fpc,"int main(void) { Run%-s(NULL);return 1;}\n",dianame);
  fclose(fpc);
  Dfree(L);
}
DIALOG * Make_dialog_structure(DIALOG *D,Dlink *L){
  DIA *d;
  int i,n,no,l;
  char *codes;
  int x1,y1,x2,y2,xl,yl;
  l = Dcount(L);
  free(D->d);
  d = (DIA *)malloc(sizeof(DIA)*(l+1));
  d[l].t = NULL;
  D->d = d;
  init_dia_array(L,d);
  D->Initfun = NULL;
  D->Cleanupfun = NULL;
  SetOptions(D);
  return D;
}
DIALOG * Make_dialog_structure_from_file(char *flname) {
  Dlink *L;
  int i,n,no,l;
  char *codes;
  DIALOG *D;
  DIA *d;
  int x1,y1,x2,y2,xl,yl;
  D = (DIALOG *)malloc(sizeof(DIALOG));
  D->xo=10,D->yo= 10,D->xl=400,D->yl=400,D->tw=4,D->rw=4;
  D->lw=4;D->bw=4; D->df=1; D->bor_type=4; D->bkup=1;
  kgDefaultGuiTheme(&(D->gc));
  L = Read_gui_data(D,flname);
  l = Dcount(L);
  d = (DIA *)malloc(sizeof(DIA)*(l+1));
  d[l].t = NULL;
  D->d = d;
  init_dia_array(L,d);
  if( (D->xl <=0) ||(D->yl <=0)) {
    Get_gui_limits(L,&x1,&y1,&x2,&y2);
    xl = x2; yl = y2;
    D->xo = 200; D->yo = 200;
    D->xl = x2+25; D->yl = y2 +12;
  }
  Dfree(L);
  SetOptions(D);
  return D;
}
void reinitialise_graphics(void) {
  DIALOG *D;
  DIG *g;
  int x1,y1,x2,y2,xres,yres;
  D = (DIALOG *)Tmp;
  g = D->d[gindex].g;
  x1 = g->x1;
  y1 = g->y1;
  x2 = g->x2;
  y2 = g->y2;
  kgViewport(g,0.0,.0,1.0,1.0);
//  set_viewport(Vx1,Vy1,Vx2,Vy2);
//  Get_resolution(&xres,&yres);
//  get_viewport(&x1,&y1,&x2,&y2);
//  set_window(0.,(float)(y2-y1),(float)(x2-x1),0.);
  kgUserFrame(g,0.,0.,(float)(x2-x1),(float)(y2-y1));
//  change_cur_format("5.0f","5.0f");
}
#define CheckPos_Resize(z) {\
  float x1,y1,x2,y2,tmp;\
  x1 = (z)->x1+D->xo; y1 = (z)->y1+D->yo;\
  x2 = (z)->x2+D->xo; y2 = (z)->y2+D->yo;\
  if( ((x1 -ixpos)*(x2-ixpos) < 0) \
      && ((y1 -iypos)*(y2-iypos) < 0)) OK = 1;\
  else OK =0 ;\
  if(OK) {\
    Rect_gincur(&x2,&y2,&x1,&y1);\
    if(x1>x2) {tmp =x2;x2=x1;x1=tmp;}\
    if(y1>y2) {tmp =y2;y2=y1;y1=tmp;}\
    (z)->x1 = (int)(x1+0.5)-D->xo;\
    (z)->y1 = (int)(y1+0.5)-D->yo;\
    (z)->x2 = (int)(x2+0.5)-D->xo;\
    (z)->y2 = (int)(y2+0.5)-D->yo;\
  }\
}
#define CheckPos_Repos(z) {\
  float x1,y1,x2,y2;\
  int dx,dy;\
  x1 = (z)->x1+D->xo; y1 = (z)->y1+D->yo;\
  x2 = (z)->x2+D->xo; y2 = (z)->y2+D->yo;\
  dx = x2 -x1; dy = y2 -y1;\
  if( ((x1 -ixpos)*(x2-ixpos) < 0) \
      && ((y1 -iypos)*(y2-iypos) < 0)) OK = 1;\
  else OK =0 ;\
  if(OK) {\
    Box_gincur(&x1,&y1,&x2,&y2);\
    (z)->x1 = (int)(x1+0.5)-D->xo;\
    (z)->y1 = (int)(y1+0.5)-D->yo;\
    (z)->x2 = (z)->x1 +dx;\
    (z)->y2 = (z)->y1 +dy;\
  }\
}
#define CheckPos_Visibility(z) {\
  float x1,y1,x2,y2;\
  int dx,dy;\
  x1 = (z)->x1+D->xo; y1 = (z)->y1+D->yo;\
  x2 = (z)->x2+D->xo; y2 = (z)->y2+D->yo;\
  dx = x2 -x1; dy = y2 -y1;\
  if( ((x1 -ixpos)*(x2-ixpos) < 0) \
      && ((y1 -iypos)*(y2-iypos) < 0)) OK = 1;\
  else OK =0 ;\
  if(!OK) {\
    break;\
  }\
}
void ChangeControlSize(DIALOG *D){
  Dlink *L;
  DIA *d;
  DIT *t;
  DII *tmp;
  static float xpos=50,ypos=50;
  int ixpos=50,iypos=50,OK=0,i;
  if(totcntl==0) {
    gprintf(Parent,(char *)"NO CONTROLS DEFINED... RETURNING");
    return;
  }
  Convert_gui_data();
  d = D->d;
  L = Dopen();
  i=0; while (d[i].t != NULL) {Dadd(L,d[i].t);i++;}
  Cross_gincur(&xpos,&ypos);
  ixpos = (int)(xpos + 0.5);
  iypos = (int)(ypos + 0.5);
//  iypos = Evgay -iypos;
  Resetlink(L);
  while ( (!OK) && ( (t=(DIT *)Getrecord(L)) != NULL)) {
    switch(t->code) {
     case 't':
     case 'T':
      CheckPos_Resize((DIT *)t);
      break;
     case 'x':
      CheckPos_Resize((DIX *)t);
      break;
     case 'y':
      CheckPos_Resize((DIY *)t);
      break;
     case 'r':
      CheckPos_Resize((DIRA *)t);
      break;
     case 'c':
      CheckPos_Resize((DICH *)t);
      break;
     case 'e':
      CheckPos_Resize((DIE *)t);
      break;
     case 'w':
     case 's':
      CheckPos_Resize((DIW *)t);
      break;
     case 'b':
      CheckPos_Resize((DIB *)t);
      break;
     case 'n':
      CheckPos_Resize((DIN *)t);
      break;
     case 'N':
      CheckPos_Resize((DIBN *)t);
      break;
     case 'h':
      CheckPos_Resize((DIL *)t);
      break;
     case 'H':
      CheckPos_Resize((DILN *)t);
      break;
     case 'p':
      CheckPos_Resize((DIP *)t);
      break;
     case 'i':
      CheckPos_Resize((DII *)t);
      tmp = (DII *)t;
      tmp->nchrs = (tmp->x2 -tmp->x1 -10)/9;
      tmp->nlines = (tmp->y2 -tmp->y1 -5)/22;
      break;
     case 'g':
      CheckPos_Resize((DIG *)t);
      break;
     case 'm':
     case 'B':
     case 'M':
     case 'o':
      CheckPos_Resize((DIM *)t);
      break;
     case 'v':
      CheckPos_Resize((DIV *)t);
      break;
     case 'z':
      CheckPos_Resize((DIZ *)t);
      break;
     case 'f':
      CheckPos_Resize((DIF *)t);
      break;
     case 'd':
      CheckPos_Resize((DID *)t);
      break;
     case 'P':
      CheckPos_Resize((DIHB *)t);
      break;
     default:
      break;
    }
  }
  Dfree(L);
  Convert_gui_data();
}
void ChangeControlPos(DIALOG *D){
  Dlink *L;
  DIA *d;
  DIT *t;
  static float xpos=50,ypos=50;
  int ixpos=50,iypos=50,OK=0,i;
  if(totcntl==0) {
    gprintf(Parent,(char *)"NO CONTROLS DEFINED... RETURNING");
    return;
  }
  Convert_gui_data();
  d = D->d;
  L = Dopen();
  i=0; while (d[i].t != NULL) {Dadd(L,d[i].t);i++;}
  Cross_gincur(&xpos,&ypos);
  ixpos = (int)(xpos + 0.5);
  iypos = (int)(ypos + 0.5);
//  iypos = Evgay -iypos;
  Resetlink(L);
  while ( (!OK) && ( (t=(DIT *)Getrecord(L)) != NULL)) {
    switch(t->code) {
     case 't':
     case 'T':
      CheckPos_Repos((DIT *)t);
      break;
     case 'x':
      CheckPos_Repos((DIX *)t);
      break;
     case 'y':
      CheckPos_Repos((DIY *)t);
      break;
     case 'c':
      CheckPos_Repos((DICH *)t);
      break;
     case 'r':
      CheckPos_Repos((DIRA *)t);
      break;
     case 'w':
     case 'e':
     case 's':
      CheckPos_Repos((DIW *)t);
      break;
     case 'b':
      CheckPos_Repos((DIB *)t);
      break;
     case 'n':
      CheckPos_Repos((DIN *)t);
      break;
     case 'N':
      CheckPos_Repos((DIBN *)t);
      break;
     case 'h':
      CheckPos_Repos((DIL *)t);
      break;
     case 'H':
      CheckPos_Repos((DILN *)t);
      break;
     case 'p':
      CheckPos_Repos((DIP *)t);
      break;
     case 'i':
      CheckPos_Repos((DII *)t);
      break;
     case 'g':
      CheckPos_Repos((DIG *)t);
      break;
     case 'm':
     case 'B':
     case 'M':
     case 'o':
      CheckPos_Repos((DIM *)t);
      break;
     case 'v':
      CheckPos_Repos((DIV *)t);
      break;
     case 'z':
      CheckPos_Repos((DIZ *)t);
      break;
     case 'f':
      CheckPos_Repos((DIF *)t);
      break;
     case 'd':
      CheckPos_Repos((DID *)t);
      break;
     case 'P':
      CheckPos_Repos((DIHB *)t);
      break;
     default:
      break;
    }
  }
  Dfree(L);
  Convert_gui_data();
}
void ChangeControlVisibility(DIALOG *D){
  Dlink *L;
  DIA *d;
  DIT *t;
  static float xpos=50,ypos=50;
  int ixpos=50,iypos=50,OK=0,i,hide;
  if(totcntl==0) {
    gprintf(Parent,(char *)"NO CONTROLS DEFINED... RETURNING");
    return;
  }
  Convert_gui_data();
  d = D->d;
  L = Dopen();
  i=0; while (d[i].t != NULL) {Dadd(L,d[i].t);i++;}
  Cross_gincur(&xpos,&ypos);
  ixpos = (int)(xpos + 0.5);
  iypos = (int)(ypos + 0.5);
  Resetlink(L);
  while ( (!OK) && ( (t=(DIT *)Getrecord(L)) != NULL)) {
    switch(t->code) {
     case 't':
     case 'T':
      CheckPos_Visibility((DIT *)t);
      hide = ((DIT *)t)->hide;
      hide = (hide+1)%2;
      ((DIT *)t)->hide = hide;
      break;
     case 'x':
      CheckPos_Visibility((DIX *)t);
      hide = ((DIX *)t)->hide;
      hide = (hide+1)%2;
      ((DIX *)t)->hide = hide;
      break;
     case 'y':
      CheckPos_Visibility((DIY *)t);
      hide = ((DIY *)t)->hide;
      hide = (hide+1)%2;
      ((DIY *)t)->hide = hide;
      break;
     case 'c':
      CheckPos_Visibility((DICH *)t);
      hide = ((DICH *)t)->hide;
      hide = (hide+1)%2;
      ((DICH *)t)->hide = hide;
      break;
     case 'r':
      CheckPos_Visibility((DIRA *)t);
      hide = ((DIRA *)t)->hide;
      hide = (hide+1)%2;
      ((DIRA *)t)->hide = hide;
      break;
     case 'w':
      CheckPos_Visibility((DIW *)t);
      hide = ((DIW *)t)->hide;
      hide = (hide+1)%2;
      ((DIW *)t)->hide = hide;
      break;
     case 'e':
      CheckPos_Visibility((DIE *)t);
      hide = ((DIE *)t)->hide;
      hide = (hide+1)%2;
      ((DIE *)t)->hide = hide;
      break;
     case 's':
      CheckPos_Visibility((DIS *)t);
      hide = ((DIS *)t)->hide;
      hide = (hide+1)%2;
      ((DIS *)t)->hide = hide;
      break;
     case 'b':
      CheckPos_Visibility((DIB *)t);
      hide = ((DIB *)t)->hide;
      hide = (hide+1)%2;
      ((DIB *)t)->hide = hide;
      break;
     case 'n':
      CheckPos_Visibility((DIN *)t);
      hide = ((DIN *)t)->hide;
      hide = (hide+1)%2;
      ((DIN *)t)->hide = hide;
      break;
     case 'N':
      CheckPos_Visibility((DIBN *)t);
      hide = ((DIBN *)t)->hide;
      hide = (hide+1)%2;
      ((DIBN *)t)->hide = hide;
      break;
     case 'h':
      CheckPos_Visibility((DIL *)t);
      hide = ((DIL *)t)->hide;
      hide = (hide+1)%2;
      ((DIL *)t)->hide = hide;
      break;
     case 'H':
      CheckPos_Visibility((DILN *)t);
      hide = ((DILN *)t)->hide;
      hide = (hide+1)%2;
      ((DILN *)t)->hide = hide;
      break;
     case 'p':
      CheckPos_Visibility((DIP *)t);
      hide = ((DIP *)t)->hide;
      hide = (hide+1)%2;
      ((DIP *)t)->hide = hide;
      break;
     case 'i':
      CheckPos_Visibility((DII *)t);
      hide = ((DII *)t)->hide;
      hide = (hide+1)%2;
      ((DII *)t)->hide = hide;
      break;
     case 'g':
      CheckPos_Visibility((DIG *)t);
      hide = ((DIG *)t)->hide;
      hide = (hide+1)%2;
      ((DIG *)t)->hide = hide;
      break;
     case 'm':
     case 'B':
     case 'M':
     case 'o':
      CheckPos_Visibility((DIM *)t);
      hide = ((DIM *)t)->hide;
      hide = (hide+1)%2;
      ((DIM *)t)->hide = hide;
      break;
     case 'v':
      CheckPos_Visibility((DIV *)t);
      hide = ((DIV *)t)->hide;
      hide = (hide+1)%2;
      ((DIV *)t)->hide = hide;
      break;
     case 'z':
      CheckPos_Visibility((DIZ *)t);
      hide = ((DIZ *)t)->hide;
      hide = (hide+1)%2;
      ((DIZ *)t)->hide = hide;
      break;
     case 'f':
      CheckPos_Visibility((DIF *)t);
      hide = ((DIF *)t)->hide;
      hide = (hide+1)%2;
      ((DIF *)t)->hide = hide;
      break;
     case 'd':
      CheckPos_Visibility((DID *)t);
      hide = ((DID *)t)->hide;
      hide = (hide+1)%2;
      ((DID *)t)->hide = hide;
      break;
     case 'P':
      CheckPos_Visibility((DIHB *)t);
      hide = ((DIHB *)t)->hide;
      hide = (hide+1)%2;
      ((DIHB *)t)->hide = hide;
      break;
     default:
      break;
    }
  }
  Dfree(L);
  Convert_gui_data();
}
void ChangeDialogSize(DIALOG *D) {
  float xo,yo,x2,y2,xl,yl,tmp;
  xo = D->xo;
  yo = D->yo;
  x2 = xo+D->xl;
  y2 = yo- D->yl;
  kgRectCursor((DIG *)kgGetWidget(Parent,1),&x2,&y2,&xo,&yo);
  if(xo >x2) {tmp =xo; xo=x2;x2=xo;};
  if(yo <y2) {tmp =yo; yo=y2;y2=yo;};
  D->xl =  (x2-xo+0.5);
  D->yl =  fabsf(y2-yo+0.5);
  D->xo = xo;
  D->yo = yo;
  return;
}
void ChangeDialogTopWidth(DIALOG *D) {
  float xo,yo,x2,y2,xl,yl;
  xo = D->xo;
  yo = D->yo;
  x2 = xo+D->xl;
  y2 = yo-D->tw;
  kgRectCursor((DIG *)kgGetWidget(Parent,1),&x2,&y2,&xo,&yo);
  D->tw =  fabsf(yo-y2+0.5);
  return;
}
void ChangeDialogBottomWidth(DIALOG *D) {
  float xo,yo,x2,y2,xl,yl;
  xo = D->xo;
  yo = D->yo-D->yl-1;
  x2 = xo+D->xl;
  y2 = yo+D->bw;
  kgRectCursor((DIG *)kgGetWidget(Parent,1),&x2,&y2,&xo,&yo);
  D->bw =  fabsf(y2-yo+0.5);
  return;
}
void ChangeDialogLeftWidth(DIALOG *D) {
  float xo,yo,x2,y2,xl,yl;
  xo = D->xo;
  yo = D->yo;
  x2 = xo+D->lw;
  y2 = yo-D->yl;
  kgRectCursor((DIG *)kgGetWidget(Parent,1),&x2,&y2,&xo,&yo);
  D->lw =  fabsf(x2-xo+0.5);
  return;
}
void ChangeDialogRightWidth(DIALOG *D) {
  float xo,yo,x2,y2,xl,yl;
  xo = D->xo+D->xl;
  yo = D->yo-D->yl;
  x2 = xo-D->rw;
  y2 = D->yo;
  kgRectCursor((DIG *)kgGetWidget(Parent,1),&x2,&y2,&xo,&yo);
  D->rw =  fabsf(xo-x2+0.5);
  return;
}

void ShowDialog_o(DIALOG *D,char *name){
  int status;
  char cwd[200];
  Make_gui_code(D,(char *)"Junk.c",name);
  system("xccg Junk");
  Pid = fork();
  if(Pid == 0) {
     getcwd(cwd,100);
     strcat(cwd,"/Junk");
     execl(cwd,"Junk",NULL);
  }
  else wait(&status);
}
void DRAW_DIALOG(DIALOG *D) {
  int bkup;
#if 1
  Xoff = GBOX->x1;
  Yoff = GBOX->y1;
  kgClearView(GBOX);
  Convert_gui_data();
  bkup = D->bkup;
  D->bkup=0;
#if 0
  D->Deco=1;
  D->DrawBkgr=1;
  D->Bkpixmap=NULL;
  D->Callback=NULL;
  D->transparency = 0.0;
  D->Newwin=0;
  D->Sticky=0;
  D->Fixpos=0;
  D->NoTaskBar=0;
#endif
//  D->ThInfo = OpenThreads(2);
  D->xo +=Xoff;
  D->yo +=Yoff;
  D->parent=Parent;
  D->wc = Parent->wc;
  D->evgax = Parent->evgax;
  D->evgay = Parent->evgay;
//  D->gc = Parent->gc;
  D->Bkpixmap=NULL;
//TCB
  D->SearchList=(void *)Dopen();
  kgAddSearchDir(D,(char *)"/usr/share/icons");
  kgAddSearchDir(D,(char *)"/usr/share/icons/kulina");
  kgAddSearchDir(D,(char *)"/usr/share/local/icons");
  kgAddSearchDir(D,(char *)"/usr/share/local/icons/kulina");
  kgAddSearchDir(D,(char *)"/usr/share/kulina/Pictures");
  kgAddSearchDir(D,(char *)"/usr/share/local/kulina/Pictures");
  kgDrawDialog(D);
  
  Dempty((Dlink *)(D->SearchList));
  D->SearchList=NULL;
  D->bkup =bkup;
  D->xo -=Xoff;
  D->yo -=Yoff;
//  swapbuffers();
//  singlebuffer();
//  reinitialise_graphics();
  Convert_gui_data();
  kgLineColor(GBOX,3);
  Draw_gui_box();
  kgUpdateOn(Parent);
#endif
  
 }
void ShowDialog(DIALOG *D){
  DIA *tmp;
  int i;
  int bkup,Newwin;
  int xo,yo,xl,yl;
#if 0
  if ((horicntl == 0)&& (actcntl > 1)) {
    gprintf(Parent, (char *)" NO WAY TO COME BACK.. DEFINE HORI. BAR");
    return;
  }
#endif
  Convert_gui_data();
  kgClearView(GBOX);
  kgClearBuffer(GBOX);
  xo = D->xo;
  yo = D->yo;
  xl = D->xl;
  yl = D->yl;
  bkup = D->bkup;
  Newwin=D->Newwin;
  D->xo=xo; D->yo=yo;D->xl=xl;D->yl=yl;
  D->xo +=Xoff;
  D->yo +=Yoff;
  D->bkup=1;
  D->Bkpixmap=NULL;
  D->Callback=DiaCallBack;
  D->Newwin=0;
  D->StackPos=0;
  D->Shapexpm=NULL;
  D->Initfun=NULL;
  D->Cleanupfun=NULL;
  D->parent=Parent;
  D->ResizeCallback=NULL;
  D->WaitCallback=NULL;
#if 0
  D->bkup=0;
  D->Deco=1;
  D->DrawBkgr=1;
  D->transparency = 0;
  D->Newwin=1;
  D->Sticky=0;
  D->Fixpos=1;
  D->NoTaskBar=0;
  D->parent=NULL;
#endif
  D->SearchList=(void *)Dopen();
  kgAddSearchDir(D,(char *)"/usr/share/icons");
  kgAddSearchDir(D,(char *)"/usr/share/icons/kulina");
  kgAddSearchDir(D,(char *)"/usr/share/local/icons");
  kgAddSearchDir(D,(char *)"/usr/share/local/icons/kulina");
  kgAddSearchDir(D,(char *)"/usr/share/kulina/Pictures");
  kgAddSearchDir(D,(char *)"/usr/share/local/kulina/Pictures");
  kgUi(D);
  Dempty((Dlink *)(D->SearchList));
  D->SearchList=NULL;
  D->bkup =bkup;
  D->Newwin=Newwin;
  D->xo -=Xoff;
  D->yo -=Yoff;
  D->ThInfo = OpenThreads(0);
  Convert_gui_data();
  reinitialise_graphics();
}
void initgraph(void *g) {
 DIG *G;
 float v[4];
 int xres,yres;
 G = (DIG *)g;
 kgUserFrame(G,(float)(G->x1),(float)(G->y2),(float)(G->x2),(float)(G->y1));
// change_cur_format("5.0f","5.0f");
 DRAW_DIALOG(Dia);
 return ;
}
#define CheckPos(z) {\
  float x1,y1,x2,y2;\
  int dx,dy;\
  x1 = (z)->x1+D->xo; y1 = (z)->y1+D->yo;\
  x2 = (z)->x2+D->xo; y2 = (z)->y2+D->yo;\
  dx = x2 -x1; dy = y2 -y1;\
  if( ((x1 -ixpos)*(x2-ixpos) < 0) \
      && ((y1 -iypos)*(y2-iypos) < 0)) OK = 1;\
  else OK =0 ;\
}
int SetControlCounters(DIALOG *D) {
  int i=0;
  Dlink *L;
  DIA *d;
  DIT *t;
  d = D->d;
  L = Dopen();
  i=0; while (d[i].t != NULL) {Dadd(L,d[i].t);i++;}
  Resetlink(L);
  actcntl=0;totcntl=0;horicntl=0,vertscroll=0,horizscroll=0;
  while (  ( (t=(DIT *)Getrecord(L)) != NULL)) {
    switch(t->code) {
     case 't':
     case 'T':
      actcntl++,totcntl++;
      break;
     case 'x':
      actcntl++,totcntl++;
      break;
     case 'y':
     case 'r':
     case 'c':
      actcntl++,totcntl++;
      break;
     case 'w':
     case 'e':
      actcntl++,totcntl++;
      break;
     case 'b':
     case 'n':
      actcntl++,totcntl++;
      break;
     case 'N':
      actcntl++,totcntl++;
      horicntl++;
      break;
     case 'h':
      actcntl++,totcntl++;
      horicntl++;
      break;
     case 'H':
      actcntl++,totcntl++;
      horicntl++;
      break;
     case 'p':
      totcntl++;
      break;
     case 's':
     case 'i':
      totcntl++;
      break;
     case 'g':
      totcntl++;
      break;
     case 'm':
     case 'B':
     case 'M':
      totcntl++;
      break;
     case 'o':
      totcntl++;
      break;
     case 'v':
      totcntl++;
      vertscroll++;
      break;
     case 'z':
      horizscroll++;
      totcntl++;
      break;
     case 'f':
      totcntl++;
      break;
     case 'd':
      totcntl++;
      break;
     case 'P':
      totcntl++;
      break;
     default:
      break;
    }
  }
  Dfree(L);
  return 1;
}
void DeleteControl(DIALOG *D) {
  Dlink *L;
  DIA *d;
  DIT *t;
  static float xpos=50,ypos=50;
  int ixpos=50,iypos=50,OK=0,i;
  if(totcntl==0) {
    gprintf(Parent,(char *)"NO CONTROLS TO DELETE... RETURNING");
    return;
  }
  Convert_gui_data();
  d = D->d;
  L = Dopen();
  i=0; while (d[i].t != NULL) {Dadd(L,d[i].t);i++;}
//  gincur(&xpos,&ypos);
  Cross_gincur(&xpos,&ypos);
  ixpos = (int)(xpos + 0.5);
  iypos = (int)(ypos + 0.5);
//  iypos = Evgay -iypos;
  Resetlink(L);
  i=0;
  while ( (!OK) && ( (t=(DIT *)Getrecord(L)) != NULL)) {
    i++;
    switch(t->code) {
     case 't':
     case 'T':
      CheckPos((DIT *)t);
      break;
     case 'x':
      CheckPos((DIX *)t);
      break;
     case 'y':
     case 'r':
     case 'c':
      CheckPos((DIY *)t);
      break;
     case 'w':
     case 'e':
     case 's':
      CheckPos((DIW *)t);
      break;
     case 'b':
      CheckPos((DIB *)t);
      break;
     case 'n':
      CheckPos((DIN *)t);
      break;
     case 'N':
      CheckPos((DIBN *)t);
      break;
     case 'h':
      CheckPos((DIL *)t);
      break;
     case 'H':
      CheckPos((DILN *)t);
      break;
     case 'p':
      CheckPos((DIP *)t);
      break;
     case 'i':
      CheckPos((DII *)t);
      break;
     case 'g':
      CheckPos((DIG *)t);
      break;
     case 'm':
     case 'B':
     case 'M':
     case 'o':
      CheckPos((DIM *)t);
      break;
     case 'v':
      CheckPos((DIV *)t);
      break;
     case 'z':
      CheckPos((DIZ *)t);
      break;
     case 'f':
      CheckPos((DIF *)t);
      break;
     case 'd':
      CheckPos((DID *)t);
      break;
     case 'P':
      CheckPos((DIHB *)t);
      break;
     default:
      break;
    }
  }
  if(OK){
    Dposition(L,i); Ddelete(L);
    Make_dialog_structure(D,L);
    SetControlCounters(D);
  }
  else printf("Nothing Selected\n");
  Convert_gui_data();
  Dfree(L);
}
int get_t_length(char *c,int sz)
 {
  int i=0,no=0,j=0;
  int lng;
  while(*(c+j)== ' ') j++;
  c = c+j;
  while((*(c+i) !='%')&&(*(c+i) != '\0'))i++;
  if(*(c+i)=='\0') { lng = i*9+8+158;}
  else {
   if(i!=0) lng= i*9+8;
   else lng =0;
   i++; if(isdigit(*(c+i))) no =no*10+(*(c+i)-'0');
   i++; if(isdigit(*(c+i))){ no =no*10+(*(c+i)-'0');i++;}
//   if( *(c+i) != 's') no++;
   no +=2;
   lng +=(no*sz+sz+4);
  }
  return(lng);
 }
int Check_format(char *buf,int *size){
 int code;
 *size =0;
 while( *buf <= ' ') buf++;
 if( *buf != '%') return -1;
 buf++;
 if( isdigit( *buf) ){
  *size = *buf-'0';
  while( isdigit( *(++buf)) ) *size = *size*10 + (*buf-'0');
  if( (*buf == 'f') ) *buf='F';
  if( (*buf == 'D') ) *buf='d';
  if( (*buf != 's') && (*buf != 'F') && (*buf != 'd') ) return -1;
  else {
   switch (*buf) {
    case 's' : code=0;break;
    case 'F' : code=1;break;
    case 'f' : code=1;break;
    case 'd' : code=2;break;
   }
   return code;
  }
 }
 else{ return -1; }
}
DILN * Making_hori_bar_o(DIALOG *D) { /* NEW TYPE */
   DILN *h;
   int i,n=0,sw,offset=4;
   char buf[100],buf1[100]="";
   int  lng=100;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   double fac=0.5;
   int type=2;
   char **xpm,name[60];
   int *bkgr;
   int clr=-1;
   int xgap=0,ygap=0,lngth=80,width=25,nxb=1,nyb=1,dx,dy;
   static int Entry=0;
   DILN htmp = {'H',10L,10L,0,0,5,5,50,25,1,1,NULL,NULL,NULL,
           NULL,NULL,NULL,NULL,NULL,2,0.2,0,0};
   htmp.Wid[0]='\0';
   htmp.xgap=xgap;
   htmp.ygap=0;
   htmp.lngth=lngth;
   htmp.width=width;
   htmp.nx=1;
   htmp.ny=1;
   htmp.type=type;
   htmp.fac=fac;
   Entry =1;

   nyb=1;
   sprintf(htmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"xgap%4dlngth%4dwidth%4dnxb%4dType%4dRound Fac%10FName%20s",&(htmp.xgap),&(htmp.lngth),
                   &(htmp.width),&(htmp.nx),&(htmp.type),&(fac),htmp.Wid);
   h = kgCreateHButtons(htmp.x1,htmp.y1,htmp.nx,htmp.lngth,htmp.width,NULL,htmp.Wid);
   h->type=htmp.type;
   h->fac = fac;
   h->xgap= htmp.xgap;
   max= h->nx*h->ny;
   nxb = h->nx;
   nyb = h->ny;
   xgap = h->xgap;
   ygap = h->ygap;
   for(i=0;i<(h->nx*h->ny);i++){
    Runbutnopt(Parent,h);
   }
   dx = h->x2 - h->x1;
   dy = h->y2 - h->y1;
   x1=h->x1+D->xo;y1=h->y1+D->yo;
   x2=h->x2+D->xo;
   y2=h->y2+D->yo;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   h->x1 = x1;
   h->y1 = y1;
   h->x2 = x1+dx;
   h->y2 = y1+dy;
   return h;
 }
DILN * Making_hori_bar(DIALOG *D) { /* NEW TYPE */
   DILN *h;
   int i,n=0,sw,offset=4;
   char buf[100],buf1[100]="";
   int  lng=100;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   double fac=0.5;
   int type=2;
   char **xpm,name[60];
   int *bkgr;
   int clr=-1;
   int xgap=0,ygap=0,lngth=80,width=25,nxb=1,nyb=1,dx,dy;
   static int Entry=0;
   DILN htmp = {'H',10L,10L,0,0,5,5,50,25,1,1,NULL,NULL,NULL,
           NULL,NULL,NULL,NULL,NULL,2,0.2,0,0};
   htmp.Wid[0]='\0';
   htmp.xgap=xgap;
   htmp.ygap=0;
   htmp.lngth=lngth;
   htmp.width=width;
   htmp.nx=1;
   htmp.ny=1;
   htmp.type=type;
   htmp.fac=fac;
   nyb=1;
   sprintf(htmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   htmp.type= type;
   htmp.fac =fac;
   if( !Runhbuttondata(&htmp)) {
     return NULL;
   }
   h = kgCreateHButtons(10,10,htmp.nx,htmp.lngth,htmp.width,NULL,htmp.Wid);
   h->xgap =htmp.xgap;
   h->ygap =htmp.ygap;
   h->hide = htmp.hide;
   h->bordr = htmp.bordr;
   h->type =htmp.type;
   h->fac =  htmp.fac;
   nxb = h->nx;
   nyb = h->ny;
   xgap= h->xgap;
   ygap= h->ygap;
   lngth = h->lngth;
   width = h->width;
   lng=0;
   min=0;
   max = nxb*nyb;
   for(i=0;i<(h->nx*h->ny);i++){
    Runbutnopt(Parent,h);
   }
   dx = h->x2 - h->x1;
   dy = h->y2 - h->y1;
   x1=h->x1+D->xo;y1=h->y1+D->yo;
   x2=h->x2+D->xo;
   y2=h->y2+D->yo;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   h->x1 = x1;
   h->y1 = y1;
   h->x2 = x1+dx;
   h->y2 = y1+dy;
   return h;
 }
DIN * Making_Buttons(DIALOG *D) { /* NEW TYPE */
   DIN *h;
   int i,n=0,sw,offset=4;
   char buf[100],buf1[100]="";
   int  lng=100;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   double fac=0.15;
   int type=5;
   char **xpm,name[60];
   int *bkgr;
   int clr=-1;
   int xgap=0,ygap=0,lngth=64,width=64,nxb=1,nyb=1;
   DIN htmp = {'n',10L,10L,60,20,2,2,64,64,1,1,
           7,0.2,0,0,0,1,NULL,NULL,NULL};
   htmp.Wid[0]='\0';
   nyb=1;
   sprintf(htmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   htmp.type= type;
   htmp.fac =fac;
   htmp.nodrawbkgr=0;
   if( !Runbuttondata(&htmp)) {
     return NULL;
   }
   h = kgCreateButtons(10,10,htmp.nx,htmp.ny,htmp.lngth,htmp.width,NULL,htmp.Wid);
   h->xgap =htmp.xgap;
   h->ygap =htmp.ygap;
   h->hide = htmp.hide;
   h->bordr = htmp.bordr;
   h->nodrawbkgr = htmp.nodrawbkgr;
   h->type =htmp.type;
   h->fac =  htmp.fac;
   nxb = h->nx;
   nyb = h->ny;
   xgap= h->xgap;
   ygap= h->ygap;
   lngth = h->lngth;
   width = h->width;
   lng=0;
   min=0;
   max = nxb*nyb;
   Runbutnopt(Parent,h);
   x1=D->xo;y1=D->yo;
   x2=x1+nxb*lngth+(nxb)*xgap+2*offset;
   y2=y1+nyb*(width+ygap)+2*offset;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+nxb*lngth+(nxb)*xgap+2*offset;
   y2=y1+nyb*(width+ygap)+2*offset;
   h->x1 = x1;
   h->y1 = y1;
   h->x2 = x2;
   h->y2 = y2;
   return h;
 }
DIL * Making_SplButtons(DIALOG *D) { /* NEW TYPE */
   DIL *h;
   int i,n=0,sw,offset=4;
   char buf[100],buf1[100]="";
   int  lng=100;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   double fac=0.5;
   int type=2;
   char **xpm,name[60];
   int *bkgr;
   int clr=-1;
   int xgap=0,ygap=0,lngth=72,width=25,nxb=1,nyb=1;
   DIL htmp = {'h',10L,10L,60,20,2,0,72,25,1,1,
           7,0.2,0,0,0,1,NULL,NULL,NULL};
   htmp.Wid[0]='\0';
   nyb=1;
   sprintf(htmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   htmp.type= type;
   htmp.fac =fac;
   htmp.nodrawbkgr=0;
   if( !Runbuttondata(&htmp)) {
     return NULL;
   }
   h = kgCreateSplButtons(10,10,htmp.nx,htmp.ny,htmp.lngth,htmp.width,NULL,htmp.Wid);
   h->xgap =htmp.xgap;
   h->ygap =htmp.ygap;
   h->hide = htmp.hide;
   h->bordr = htmp.bordr;
   h->type =htmp.type;
   h->fac =  htmp.fac;
   nxb = h->nx;
   nyb = h->ny;
   xgap= h->xgap;
   ygap= h->ygap;
   lngth = h->lngth;
   width = h->width;
   lng=0;
   min=0;
   max = nxb*nyb;
   Runbutnopt(Parent,h);
   x1=D->xo;y1=D->yo;
   x2=x1+nxb*lngth+(nxb)*xgap+2*offset;
   y2=y1+nyb*(width+ygap)+2*offset;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+nxb*lngth+(nxb)*xgap+2*offset;
   y2=y1+nyb*(width+ygap)+2*offset;
   h->x1 = x1;
   h->y1 = y1;
   h->x2 = x2;
   h->y2 = y2;
   return h;
 }
DIB * Making_Buttonsn(DIALOG *D) { /* NEW TYPE */
   DIB *h;
   int i,n=0,sw,offset=4;
   char buf[100],buf1[100]="";
   int  lng=100;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   double fac=0.15;
   int type=4;
   char **xpm,name[60];
   int *bkgr;
   int clr=-1;
   int xgap=0,ygap=0,lngth=48,width=48,nxb=1,nyb=1;
   DIB htmp = {'n',10L,10L,60,20,5,5,48,48,1,1,NULL,NULL,NULL,
           NULL,NULL,NULL,NULL,NULL,2,0.2,0,0,-1};
   htmp.Wid[0]='\0';
   nyb=1;
   sprintf(htmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   htmp.type= type;
   htmp.fac =fac;
   if( !Runbuttondata(&htmp)) {
     return NULL;
   }
   h = kgCreateButtonsb(10,10,htmp.nx,htmp.ny,htmp.lngth,htmp.width,NULL,htmp.Wid);
   h->xgap =htmp.xgap;
   h->ygap =htmp.ygap;
   h->hide = htmp.hide;
   h->bordr = htmp.bordr;
   h->type =htmp.type;
   h->fac =  htmp.fac;
   nxb = h->nx;
   nyb = h->ny;
   xgap= h->xgap;
   ygap= h->ygap;
   lngth = h->lngth;
   width = h->width;
   lng=0;
   min=0;
   max = nxb*nyb;
   Runbutnopt(Parent,h);
   x1=D->xo;y1=D->yo;
   x2=x1+nxb*lngth+(nxb)*xgap+2*offset;
   y2=y1+nyb*(width+ygap)+2*offset;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+nxb*lngth+(nxb)*xgap+2*offset;
   y2=y1+nyb*(width+ygap)+2*offset;
   h->x1 = x1;
   h->y1 = y1;
   h->x2 = x2;
   h->y2 = y2;
   return h;
 }
DII * Making_Infobox(DIALOG *D){
   DII  *g; 
   int i,n;
   char buf[60],buf1[60]=" ";
   int  nchrs=60,nlines=10,l,w;
   float x1,y1,x2,y2;
   DII gtmp = {'i',10,10,20,20,22,0,0,0,0,0};
   gtmp.Wid[0]='\0';
   sprintf(gtmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"No of chars :%3dNo of Lines :%3dName%20s",&nchrs,&nlines,gtmp.Wid);
   g = kgCreateInfoBox(gtmp.x1,gtmp.y1,nchrs,nlines,gtmp.Wid);
   x1=g->x1+D->xo;y1=g->y1+D->yo;
   x2=g->x2+D->xo;
   y2=g->y2+D->yo;
   l = g->x2-g->x1;
   w = g->y2 - g->y1;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   g->x1 =x1;
   g->y1 =y1;
   g->x2 =x1 + l;
   g->y2 =y1 + w;
   return g;
}
DIG * Making_Graphbox(DIALOG *D){
   DIG  *g; 
   int i,n;
   char buf[60],buf1[60]=" ";
   int  lng=640,wdth=480;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   DIG gtmp = {'g',10,10,20,20,NULL,0,NULL,NULL,0,0};
   gtmp.Wid[0]='\0';
   sprintf(gtmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"X dir size (in pixels):%4dY dir size (in pixels):%4dHide:%2dName%20s",&lng,&wdth,&(gtmp.hide),gtmp.Wid);
   g = kgCreateDrawingBox(gtmp.x1,gtmp.y1,lng,wdth,gtmp.Wid);
   x1=g->x1+D->xo;y1=g->y1+D->yo;
   lng = g->x2-g->x1;
   wdth = g->y2 - g->y1;
   x2=x1+lng;
   y2=y1+wdth;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   g->x1 =x1;
   g->y1 =y1;
   g->x2 =x1 + lng;
   g->y2 =y1 + wdth;
   g->bkgr_clr = 0;
   g->hide=gtmp.hide;
   return g;
 }
DIP * Making_Pixmap(DIALOG *D){
   DIP  *p; 
   int i,n,col=-1;
   char buf[60],buf1[60]=" ",*xpm;
   int  lng=128,wdth=128;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   DIP ptmp = {'p',10,10,20,20,NULL,-1};
   ptmp.Wid[0]='\0';
   sprintf(ptmp.Wid,"%-sWidget%-d",DiaName,++WidCount);
   ptmp.bordr=3;
   ptmp.hide=0;
   gscanf(Parent,(char *)"Xpm file : %20sBackground Color: %3d border type: %2dhide: %2dName%20s",buf1,&col,&(ptmp.bordr),&(ptmp.hide),ptmp.Wid);
   p = kgCreateImageBox(ptmp.x1,ptmp.y1,200,200,buf1,ptmp.bordr,ptmp.Wid);
   x1=p->x1+D->xo;y1=p->y1+D->yo;
   Cross_gincur(&x1,&y1);
   x2=p->x2+D->xo;
   y2=p->y2+D->yo;
   Rect_gincur(&x2,&y2,&x1,&y1);
   x1 -=D->xo;
   y1 -=D->yo;
   x2 -=D->xo;
   y2 -=D->yo;
   p->x1 =x1+0.5;
   p->y1 =y1+0.5;
   p->x2 =x2+0.5;
   p->y2 =y2+0.5;
   p->bkgr_clr = col;
   p->hide = ptmp.hide;
   p->transparency=0.0;
   return p;
 }
DIM * Making_DisplayBox(DIALOG *D){
   DIM  *m; 
   int i,n;
   char buf[500],buf1[500]=" ";
   int  lng=100;
   int  min=0,max=100,df=0,ln=200,wd=40,hide=0;
   float x1,y1,x2,y2;
   DIM mtmp = {'M',10L,10L,0,0,1,0};
   m = (DIM *)malloc(sizeof(DIM));
   mtmp.Wid[0]='\0';
   *m = mtmp;
   sprintf(m->Wid,"%-sWidget%-d",DiaName,++WidCount);
   m->msg[0]='\0';
   m->x2 = m->x1+ln;
   m->y2 = m->x1+wd;
   m->justification=1;
   m->hide=0;
   if(!Runmessagedata(m)) {
     free(m);
     return NULL;
   }
   lng = m->x2 -m->x1;
   wd =  m->y2 - m->y1;
   x1=10+D->xo;y1=10+D->yo;
   x2=x1+lng;
   y2=y1+wd;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+lng;
   y2=y1+wd;
   m->x1 =x1;
   m->y1 =y1;
   m->x2 =x2;
   m->y2 =y2;
   return m;
 }
DIO * Making_Progressbar(DIALOG *D){
   DIO  *m; 
   int i,n;
   char buf[500],buf1[500]=" ";
   int  lng=100;
   int  min=0,max=100,df=0,ln=204,wd=20,hide=0;
   float x1,y1,x2,y2;
   DIO mtmp = {'o',10L,10L,0,0,0,50,0,2,-1,0};
   m = (DIO *)malloc(sizeof(DIO));
   mtmp.Wid[0]='\0';
   *m = mtmp;
   sprintf(m->Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"Length:%4dWidth:%4dHide:%2dName%20s",&ln,&wd,&hide,m->Wid);
   x1=10+D->xo;y1=10+D->yo;
   x2=x1+ln;
   y2=y1+wd;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+ln;
   y2=y1+wd;
   m->x1 =x1;
   m->y1 =y1;
   m->x2 =x2;
   m->y2 =y2;
   m->hide = hide;
   return m;
}
DIV * Making_Vertscroll(DIALOG *D){
   DIV  *m; 
   int i,n;
   char buf[500],buf1[500]=" ";
   int  lng=100;
   int  min=0,max=100,ln=204,wd=20,hide=0;
   float x1,y1,x2,y2;
   double ds=100.,df=0.0;
   DIV mtmp = {'v',10L,10L,30,210,0,100.,0.,5.,NULL,NULL};
   m = (DIV *)malloc(sizeof(DIV));
   mtmp.Wid[0]='\0';
   *m = mtmp;
   sprintf(m->Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"Length:%4dWidth:%4dHide:%2dName%20s",&ln,&wd,&hide,m->Wid);
   x1=10+D->xo;y1=10+D->yo;
   x2=x1+wd;
   y2=y1+ln;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+wd;
   y2=y1+ln;
   m->x1 =x1;
   m->y1 =y1;
   m->x2 =x2;
   m->y2 =y2;
   m->hide = hide;
   return m;
}
DIZ * Making_Horizscroll(DIALOG *D){
   DIZ  *m; 
   int i,n;
   char buf[500],buf1[500]=" ";
   int  lng=100;
   int  min=0,max=100,ln=204,wd=20,hide=0;
   float x1,y1,x2,y2;
   double ds=100.,df=0.0;
   DIZ mtmp = {'z',10L,10L,30,210,0,100.,0.,5.,NULL,NULL};
   m = (DIZ *)malloc(sizeof(DIZ));
   mtmp.Wid[0]='\0';
   *m = mtmp;
   sprintf(m->Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"Length:%4dWidth:%4dHide:%2dName%20s",&ln,&wd,&hide,m->Wid);
   x1=10+D->xo;y1=10+D->yo;
   x2=x1+ln;
   y2=y1+wd;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+ln;
   y2=y1+wd;
   m->x1 =x1;
   m->y1 =y1;
   m->x2 =x2;
   m->y2 =y2;
   m->hide = hide;
   return m;
}
DIM * Making_Message(DIALOG *D){
   DIM  *m; 
   int i,n;
   char buf[500],buf1[500]=" ";
   int  lng=100,ln=100,wd=24,hide=0;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   DIM mtmp = {'m',10L,10L,0,0,1,0};
   m = (DIM *)malloc(sizeof(DIM));
   mtmp.Wid[0]='\0';
   *m = mtmp;
   sprintf(m->Wid,"%-sWidget%-d",DiaName,++WidCount);
   m->msg[0]='\0';
   m->x2 = m->x1+ln;
   m->y2 = m->x1+wd;
   m->justification=1;
   m->hide=0;
//   gscanf(Parent,(char *)"Length:%4dWidth:%4dInitail Text:%40sName:%20sHide:%2d",&ln,&wd,buf1,m->Wid,&hide);
   if(!Runmessagedata(m)) {
     free(m);
     return NULL;
   }
   n=0;while(buf1[n]!='\0')n++;
//   lng = n*9+5;
   lng = m->x2 -m->x1;
   wd =  m->y2 - m->y1;
   x1=10+D->xo;y1=10+D->yo;
   x2=x1+lng;
   y2=y1+wd;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+lng;
   y2=y1+wd;
   m->x1 =x1;
   m->y1 =y1;
   m->x2 =x2;
   m->y2 =y2;
//   strncpy(m->msg,buf1,499);
   return m;
 }
DIM * Making_Messageb(DIALOG *D){
   DIM  *m; 
   int i,n;
   char buf[60],buf1[60]=" ";
//   int  lng=100;
   int  lng=100,ln=100,wd=24,hide=0;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   DIM mtmp = {'B',10L,10L,0,0,0,0};
   m = (DIM *)malloc(sizeof(DIM));
   mtmp.Wid[0]='\0';
   *m = mtmp;
   sprintf(m->Wid,"%-sWidget%-d",DiaName,++WidCount);
   m->msg[0]='\0';
   m->x2 = m->x1+ln;
   m->y2 = m->x1+wd;
   m->justification=0;
   m->hide=0;
   if(!Runmessagedata(m)) {
     free(m);
     return NULL;
   }
   lng = m->x2 -m->x1;
   wd =  m->y2 - m->y1;
   x1=10+D->xo;y1=10+D->yo;
   x2=x1+lng;
   y2=y1+wd;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+lng;
   y2=y1+wd;
   m->x1 =x1;
   m->y1 =y1;
   m->x2 =x2;
   m->y2 =y2;
   return m;
 }
DIT * Making_t_box_o(DIALOG *D)
 {
   DIT *T=NULL;
   T_ELMT *E=NULL;
   int i,n,k,j,code=0,size=0,l;
   char buf[60],buf1[30]=" ",buf2[6]=" ",ch;
   int  nx=1,ny=1,lngth=0,ln,width,lnx[1000];
   float x1=10,y1=10,x2,y2;
   double *ftmp;
   int   *itmp;
   char  *ctmp;
   DIT Tmp = {'t',10L,10L,0,0,20L,1L,1L,NULL,0,0,NULL,NULL};
   T = (DIT *)malloc(sizeof(DIT));
   Tmp.Wid[0]='\0';
   *T = Tmp;
   sprintf(T->Wid,"%-sWidget%-d",DiaName,++WidCount);
   T->bordr=1;
   T->hide=0;
   gscanf(Parent,(char *)"No. of boxes in X dir%2dNo of boxes in Y dir%2dName%20s",&nx,&ny,T->Wid);
   T->nx = nx; T->ny = ny;
   E = (T_ELMT *)malloc(sizeof(T_ELMT)*nx*ny);
   for(i=0;i<(nx*ny) ;i++) {
     E[i].fmt = (char *)malloc(150);
   }
   T->elmt = E;
   width = (ny)*T->width+(ny-1)*10;
   for(j=0;j<nx;j++) lnx[j]=0;
   i=0;
   for(k=0;k<ny;k++){
     ln=0;
     for(j=0;j<nx;j++) {
       buf1[0]='\0';
       buf2[0]='\0';
       sprintf(buf,"Prompt for ITEM %-d %%20sFormat for ITEM %-d %%4s",i+1,i+1);
       gscanf(Parent,buf,buf1,buf2);
       while((code=Check_format(buf2,&size))< 0) {
          opntwin(Parent,0L,350L,30L,1L);
          gprintf(Parent,(char *)" ERROR: Wrong Format.....");
          gscanf(Parent,buf,buf1,buf2);
          clstwin(Parent);
       }
       strcat(buf1,buf2);
       ln =get_t_length(buf1,9);
       if(ln >lnx[j])lnx[j]=ln;
       strcpy(E[i].fmt,buf1);
       l = strlen(E[i].fmt) - 1;
       while( E[i].fmt[l] <= ' ') l--;
       ch = E[i].fmt[l];
       switch(ch) {
         case 'F':
           ftmp = (double *)malloc(sizeof(double));
           *ftmp =0.;
           E[i].v = (void *)ftmp;
           break;
         case 'd':
           itmp = (int *)malloc(sizeof(int));
           *itmp = 1;
           E[i].v = (void *)itmp;
           break;
         case 's':
           ctmp = (char *)malloc(500);
           ctmp[0]='\0';
           E[i].v = (void *) ctmp;
           break;
       }
       E[i].sw = 1;
       i++;
     }
     if( ln>lngth) lngth = ln;
   }
   lngth=0;
   for(j=0;j<nx;j++) lngth+=lnx[j];
   lngth = (nx-1)*10+lngth;
   lngth += (10+4);
   width += (10+4);
   x1 +=D->xo;
   y1 +=D->yo;
   x2 = x1+lngth;
   y2 = y1+width;
   Box_gincur(&x1,&y1,&x2,&y2);
   x2 = x1+lngth;
   y2 = y1+width;
   T->x1 = x1-D->xo;
   T->y1 = y1-D->yo;
   T->x2 = x2-D->xo;
   T->y2 = y2-D->yo;
   T->col = 1;
   T->row = 1;
   return T;
 }
DIT * Making_t_box(DIALOG *D)
 {
   DIT *T=NULL;
   T_ELMT *E=NULL;
   int i,n,k,j,code=0,size=0,l;
   char buf[60],buf1[30]=" ",buf2[6]=" ",ch;
   int  nx=1,ny=1,lngth=0,ln,width,lnx[1000];
   float x1=10,y1=10,x2,y2;
   double *ftmp;
   int   *itmp;
   char  *ctmp;
   DIT Tmp = {'t',10L,10L,0,0,20L,1L,1L,NULL,0,0,NULL,NULL};
   T = (DIT *)malloc(sizeof(DIT));
   Tmp.Wid[0]='\0';
   *T = Tmp;
   sprintf(T->Wid,"%-sWidget%-d",DiaName,++WidCount);
   T->bordr=1;
   T->hide=0;
   T->nx = nx; T->ny = ny;
   T->Font=18;
   T->FontSize=9;
   sprintf(T->Wid,"%-sWidget%-d",DiaName,++WidCount);
   if( !Runtextboxesdata(T) ) {
     free(T);
     return NULL;
   }
   nx = T->nx;
   ny = T->ny;
   E = (T_ELMT *)malloc(sizeof(T_ELMT)*nx*ny);
   i=0;
   for(j=0;j<ny;j++) {
     for(k=0;k<(nx) ;k++) {
       sprintf(buf,"For Textbox: (%d,%d)",k+1,j+1);
       E[i].fmt = (char *)Runtextboxdata(buf);
       i++;
     }
   }
   T->elmt = E;
   width = (ny)*T->width+(ny-1)*10;
   for(j=0;j<nx;j++) lnx[j]=0;
   i=0;
   for(k=0;k<ny;k++){
     ln=0;
     for(j=0;j<nx;j++) {
       ln =get_t_length(E[i].fmt,9);
       if(ln >lnx[j])lnx[j]=ln;
       l = strlen(E[i].fmt) - 1;
       while( E[i].fmt[l] <= ' ') l--;
       ch = E[i].fmt[l];
       switch(ch) {
         case 'F':
           ftmp = (double *)malloc(sizeof(double));
           *ftmp =0.;
           E[i].v = (void *)ftmp;
           break;
         case 'd':
           itmp = (int *)malloc(sizeof(int));
           *itmp = 1;
           E[i].v = (void *)itmp;
           break;
         case 's':
           ctmp = (char *)malloc(500);
           ctmp[0]='\0';
           E[i].v = (void *) ctmp;
           break;
       }
       E[i].sw = 1;
       i++;
     }
     if( ln>lngth) lngth = ln;
   }
   lngth=0;
   for(j=0;j<nx;j++) lngth+=lnx[j];
   lngth = (nx-1)*10+lngth;
   lngth += (10+4);
   width += (10+4);
   x1 +=D->xo;
   y1 +=D->yo;
   x2 = x1+lngth;
   y2 = y1+width;
   Box_gincur(&x1,&y1,&x2,&y2);
   x2 = x1+lngth;
   y2 = y1+width;
   T->x1 = x1-D->xo;
   T->y1 = y1-D->yo;
   T->x2 = x2-D->xo;
   T->y2 = y2-D->yo;
   T->col = 1;
   T->row = 1;
   return T;
 }
DIT * Making_T_box(DIALOG *D)
 {
   DIT *T=NULL;
   T_ELMT *E=NULL;
   int i,n,k,j,code=0,size=0,l,sw=1;
   char buf[100],buf1[100]=" ",buf2[10]=" ",ch;
   int  nx=1,ny=1,lngth=0,ln,width;
   float x1=10,y1=10,x2,y2;
   double *ftmp;
   int   *itmp;
   char  *ctmp;
   DIT Tmp = {'T',10L,10L,0,0,24L,1L,1L,NULL,0,0,NULL,NULL};
   T = (DIT *)malloc(sizeof(DIT));
   Tmp.Wid[0]='\0';
   *T = Tmp;
   T->bordr=1;
   T->hide =0;
   T->Font=18;
   T->FontSize=9;
   sprintf(T->Wid,"%-sWidget%-d",DiaName,++WidCount);
//   gscanf(Parent,(char *)"No. of Columns%2dNo of Rows%2dName%20s",&nx,&ny,T->Wid);
   T->nx = nx; T->ny = ny;
   if( !Runtableboxesdata(T) ) {
     free(T);
     return NULL;
   }
   nx = T->nx;
   ny = T->ny;
   E = (T_ELMT *)malloc(sizeof(T_ELMT)*nx*ny);
   for(i=0;i<(nx*ny) ;i++) {
     E[i].fmt = (char *)malloc(150);
   }
   T->elmt = E;
   for(i=0;i<(nx) ;i++) {
       sprintf(buf,"For Column: %d",i);
       Runtableboxdata(E+i,buf);
       for(j=1;j<ny;j++) {
          strcpy(E[i+j*nx].fmt,E[i].fmt);
          E[i+j*nx].sw = E[i].sw;
       }
   }
   width = (ny)*T->width;
   i=0;
   ln=0;
   for(j=0;j<nx;j++) {
     ln +=(get_t_length(E[j].fmt,T->FontSize));
     for(k=0;k<ny;k++){
       i = k*nx + j;
       l = strlen(E[i].fmt) - 1;
       while( E[i].fmt[l] <= ' ') l--;
       ch = E[i].fmt[l];
       switch(ch) {
         case 'F':
           ftmp = (double *)malloc(sizeof(double));
           *ftmp =0.;
           E[i].v = (void *)ftmp;
           break;
         case 'd':
           itmp = (int *)malloc(sizeof(int));
           *itmp = 1;
           E[i].v = (void *)itmp;
           break;
         case 's':
           ctmp = (char *)malloc(300);
           ctmp[0]='\0';
           E[i].v = (void *) ctmp;
           break;
       }
     }
     if( ln>lngth) lngth = ln;
   }
   /* lngth = nx+1+lngth;*/
//   lngth += 10;
   lngth += 2*4+1;
//TCB
   width += 2*4+1;
   x1 +=D->xo;
   y1 +=D->yo;
   x2 = x1+lngth;
   y2 = y1+width;
   Box_gincur(&x1,&y1,&x2,&y2);
   x2 = x1+lngth;
   y2 = y1+width;
   T->x1 = x1-D->xo;
   T->y1 = y1-D->yo;
   T->x2 = x2-D->xo;
   T->y2 = y2-D->yo;
   T->col = 1;
   T->row = 1;
   return T;
 }
DIBN * Making_Buttonsnew(DIALOG *D) {
   DIBN *N;
   int i,n;
   char buf[100],buf1[100]=" ";
   char **xpm,name[60];
   int *bkgr;
   int clr;
   int  lng=100;
   int  min=0,max=100,df=0;
   float x1,y1,x2,y2;
   double fac=0.2;
   int xgap=0,ygap=0,lngth=54,width= 54,nxb=1,nyb=1,type=2,bordr=0;
   DIBN Ntmp = {'N',10,10,0,0,9,9,54,54,1,1,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,6,0.25,1,0};
   N = (DIBN *)malloc(sizeof(DIBN));
   Ntmp.type=type;
   Ntmp.fac = fac;
   Ntmp.Wid[0]='\0';
   *N = Ntmp;
   sprintf(N->Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"prompt%20sxgap%3dygap%3dlength%3dwidth%3dnxb%3dnyb%3dType%3dRounding Fac%FName%20s",
            buf1,&xgap,&ygap,&lngth,&width,&nxb,&nyb,&type,&fac,N->Wid);
   i=0;while(buf1[i]== ' ')i++;
   n=0;while(buf1[i+n]!='\0')n++;
   N->prompt = (char *)malloc(strlen(buf1+i)+2);
   if(n!=0) strcpy(N->prompt,buf1+i);
   else N->prompt[0]='\0';
   xpm = (char **) malloc(sizeof(char *)*(nxb*nyb)*3);
   bkgr= (int *) malloc(sizeof(int)*(nxb*nyb));
   N->xgap= xgap;
   N->ygap= ygap;
   N->width= width;
   N->lngth = lngth;
   N->nx= nxb;
   N->ny= nyb;
   N->df = (int *)malloc(sizeof(int));
   *((int *)(N->df)) =1;
   N->type=type;
   N->fac=fac;
   N->xpm = NULL;
   max= nxb*nyb;
   N->titles = (char **)malloc(sizeof(char *)*(max+1));
   lng=0;
   min=0;
   for(i=0;i<max;i++){
    strcpy(buf1,"");
    strcpy(name,"              ");
    sprintf(buf,"Give title button %-d %%35sXpm File %%20sBack ground color %%3d",(i+1));
    clr = -1;
//    gscanf(Parent,buf,buf1,name,&clr);
    sprintf(buf,"For Button %-d ",(i+1));
#if 0
    buttoninfo(Parent,buf, buf1,name,&clr);
    if ( name[0] > ' ') {
       xpm[i]= (char *) malloc(strlen(name)+3);
       strcpy(xpm[i],"##");
       strcat(xpm[i],name);
    }
    else xpm[i]= NULL;
    bkgr[i] = clr;
    min =strlen(buf1);
    N->titles[i] = (char *)malloc(min+1);
    if(min>lng) lng=min;
    strcpy(N->titles[i],buf1);
#endif
   }
#if 0
   if( lng == 0 ){ lngth=15; }
   else {
     lng = lng*9+26;
     if(lng>lngth) lngth=lng;
   }
   N->lngth = lngth;
#endif
   if(n!=0) n++;
   x1=10+D->xo;y1=10+D->yo;
   x2=x1+nxb*lngth+(nxb-1)*xgap+n*9+6;
   y2=y1+(nyb*width+(nyb-1)*ygap)+6;
   Box_gincur(&x1,&y1,&x2,&y2);
//   move2f(x1,y1); draw2f(x1,y2); draw2f(x2,y2);
//   draw2f(x2,y1); draw2f(x1,y1);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+nxb*lngth+(nxb-1)*xgap+n*9+6;
   y2=y1+(nyb*width+(nyb-1)*ygap)+6;
   N->x1 = x1; N->y1 = y1;
   N->x2 = x2; N->y2 = y2;
   N->xpm = (void **)xpm;
   for(i=max;i<3*max;i++) N->xpm[i]=NULL;
   N->bkgr = bkgr;
   N->bordr=bordr;
   N->hide=0;
   return N;
 }
DIW * Making_Browser(DIALOG *D) {
   DIW *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int  min=4,max=6,df=0,ln=0;
   int msize=0;
   float x1,y1,x2,y2;
   char **menu;
   DIW Wtmp ={'w',10L,10L,0,0,5,NULL,NULL,NULL,NULL,NULL,0};
   W = (DIW *)malloc(sizeof(DIW));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"prompt%20sportion size%4dNo. of menu items%4dName%20s",
            buf1,&min,&max,W->Wid);
   i=0;while(buf1[i]==' ')i++;
   n=0;while(buf1[i+n]!='\0')n++;
   W->prompt = (char *)malloc(n+1);
   if(n!=0) strcpy(W->prompt,buf1+i);
   else W->prompt[0] = '\0';
   W->size = min;
   W->df = (int *)malloc(sizeof(int));
   *((int *)(W->df)) = 1;
#if 0
   W->menu = (char **)malloc(sizeof(char *)*(max+1));
   W->menu[max]= NULL;
   for(i=0;i<max;i++){
    strcpy(buf1,"              ");
    sprintf(buf,"Give menu item %-d :%%15s",(i+1));
    gscanf(Parent,buf,buf1);
    min=0;while (*(buf1+min) != '\0') min++;
    if(msize<min) msize=min;
    W->menu[i]= (char *)malloc(min+1);
    strcpy(W->menu[i],buf1);
   }
#else
   W->menu = RungetStrings(D,max);
   menu = W->menu;
   i=0;
   msize=5;
   while(menu[i]!= NULL) {
     ln = strlen(menu[i]);
     if(ln> msize) msize=ln;
     i++;
   }
#endif
   if(n!=0) {n++;ln=8;}
   x1=10+D->xo;y1=10+D->yo;x2=x1+(n*9+ln)+msize*9+32;y2=y1+29;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   x2=x1+(n*9+ln)+msize*9+32;y2=y1+29;
   W->x1 = x1;
   W->y1 = y1;
   W->x2 = x2;
   W->y2 = y2;
   W->item=-1;
   return W;
 }

DIE * Making_Menu(DIALOG *D) {
   DIE *W;
   int i,n;
   char **menu;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int  min=4,max=6,df=0,ln=0,w=200,h=200,maxchar=15;
   int msize=0;
   float x1,y1,x2,y2;
   DIE Wtmp ={'e',10L,10L,0,0,5,NULL,NULL,NULL,NULL,NULL,20,6,22,1,1,1,0};
   W = (DIE *)malloc(sizeof(DIE));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"portion size%4dNo. of menu items%4dName%20s", &min,&max,W->Wid);
   h = (min)*20+16;
   W->prompt=(char *)" ";
   W->size = min;
   W->df = (int *)malloc(sizeof(int));
   *((int *)(W->df)) = 1;
   W->menu = RungetStrings(D,max);
   menu = W->menu;
   i=0;
   maxchar=5;
   while(menu[i]!= NULL) {
     ln = strlen(menu[i]);
     if(ln> maxchar) maxchar=ln;
     i++;
   }
   w = (maxchar*9+30);
#if 0
   W->menu = (char **)malloc(sizeof(char *)*(max+1));
   W->menu[max]= NULL;
   for(i=0;i<max;i++){
    strcpy(buf1,"              ");
    sprintf(buf,"Give menu item %-d :%%15s",(i+1));
    gscanf(Parent,buf,buf1);
    min=0;while (*(buf1+min) != '\0') min++;
    if(msize<min) msize=min;
    W->menu[i]= (char *)malloc(min+1);
    strcpy(W->menu[i],buf1);
   }
   if(n!=0) {n++;ln=8;}
#endif
   x1=10+D->xo;y1=10+D->yo;x2=x1+w;y2=y1+h;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   W->x1 = x1;
   W->y1 = y1;
   W->x2 = x1+w;
   W->y2 = y1+h;
   return W;
 }
DIS * Making_MsgScroll(DIALOG *D) {
   DIS *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int  min=4,max=6,df=0,ln=0,w=200,h=200,maxchar=15;
   int msize=0;
   float x1,y1,x2,y2;
   DIS Wtmp ={'s',10L,10L,0,0,5,NULL,NULL,NULL,NULL,NULL,20,6,22,0,1,1,0};
   W = (DIS *)malloc(sizeof(DIS));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
   gscanf(Parent,(char *)"Visible portion size%3dNo. of lines%3dMax. line length%3dName%20s",
            &min,&max,&maxchar,W->Wid);
   h = (min+1)*20+20;
   w = (maxchar*9+44);
   W->prompt=(char *)" ";
   W->size = min;
   W->menu = (char **)malloc(sizeof(char *)*(max+1));
   W->menu[max]= NULL;
   for(i=0;i<max;i++){
    strcpy(buf1," ");
    W->menu[i]= (char *)malloc(maxchar+1);
    strcpy(W->menu[i],buf1);
   }
   if(n!=0) {n++;ln=8;}
   x1=10+D->xo;y1=10+D->yo;x2=x1+w;y2=y1+h;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
//   x2=x1+(n*9+ln)+msize*9+42;y2=y1+29;
   W->x1 = x1;
   W->y1 = y1;
   W->x2 = x1+w;
   W->y2 = y1+h;
   return W;
 }


int    GetSlidebarSizeH(DIHB *W, int *ln,int *wd) {
 int Sldwd =20,l,w;
 int ret,n=0,lngth=0,i=0;
 
 l = W->lngth+10;
 w = 25;
 *ln= l; *wd = w;
 return 0;
}
int    GetSlidebarSizeD(DID *W, int *ln,int *wd) {
 int Sldwd =20,l,w;
 int ret,n=0,lngth=0,i=0;
 
 l = W->lngth+2*Sldwd+6;
 w = 2*Sldwd;
 while((W->prompt[i])==' ') i++;
 while((W->prompt[n+i])>=' ') n++;
 if(n != 0) {
     lngth = n*9+4;
 }
 l += (lngth+4);
 w += 6;
 *ln= l; *wd = w;
 return 0;
}
int    GetSlidebarSizeF(DIF *W, int *ln,int *wd) {
 int Sldwd =20,l,w;
 int ret,n=0,lngth=0,i=0;
 
 l = W->lngth+2*Sldwd+6;
 w = 2*Sldwd;
 while((W->prompt[i])==' ') i++;
 while((W->prompt[n+i])>=' ') n++;
 if(n != 0) {
     lngth = n*9+4;
 }
 l += (lngth+4);
 w += 6;
 *ln= l; *wd = w;
 return 0;
}

DIHB * Making_SlideH(DIALOG *D) {
   DIHB *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int  min=4,max=6,df=5,ln=0,wd=0;
   int msize=0;
   float x1,y1,x2,y2;
   DIHB Wtmp ={'P',0,100,0,0,0,100,101,NULL,NULL,NULL,NULL,0,0,2,-1};
   W = (DIHB *)malloc(sizeof(DIHB));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
//   slided(buf,&(W->lngth),&(W->min),&(W->max),&df);
//   gscanf(Parent,(char *)"Length:%4dMin Val:%4dMax Val:%4dDef Val:%4dName%20s",&(W->lngth),&(W->min),&(W->max),&df,W->Wid);
   if(!Runslidebaropt((void *)W)) {
         free(W);
         return NULL;
   }
   else {
    n =0;
    W->prompt = (char *)malloc(n+1);
    if(n!=0) strcpy(W->prompt,buf+i);
    else W->prompt[0] = '\0';
    W->df = (int *)malloc(sizeof(int));
    *((int *)(W->df)) = df;
    GetSlidebarSizeH(W,&ln,&wd);
    x1=D->xo+10;y1=D->yo+10;
    x2=D->xo+10+ln;y2=D->yo+10+wd;
    Box_gincur(&x1,&y1,&x2,&y2);
    x1 -=D->xo;
    y1 -=D->yo;
   
    W->x1 = x1+0.5;
    W->y1 = y1+0.5;
    W->x2 = x1+0.5+ln;
    W->y2 = y1+0.5+wd;
    return W;
   }
 }
DID * Making_SlideD(DIALOG *D) {
   DID *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int  min=4,max=6,df=5,ln=0,wd=0;
   int msize=0;
   float x1,y1,x2,y2;
   DID Wtmp ={'d',0,100,0,0,0,100,101,NULL,NULL,NULL,NULL};

   W = (DID *)malloc(sizeof(DID));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
//   slided(buf,&(W->lngth),&(W->min),&(W->max),&df);
   gscanf(Parent,(char *)"Length:%4dMin Val:%4dMax Val:%4dDef Val:%4dName%20s",&(W->lngth),&(W->min),&(W->max),&df,W->Wid);
#if 0
   i=0;while(buf[i]==' ')i++;
   n=0;while(buf[i+n]>=' ')n++;
   buf[n] ='\0';
#else
   n=0;
#endif
   W->prompt = (char *)malloc(n+1);
   if(n!=0) strcpy(W->prompt,buf+i);
   else W->prompt[0] = '\0';
   W->df = (int *)malloc(sizeof(int));
   *((int *)(W->df)) = df;
   GetSlidebarSizeD(W,&ln,&wd);
   x1=D->xo+10;y1=D->yo+10;
   x2=D->xo+10+ln;y2=D->yo+10+wd;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   
   W->x1 = x1+0.5;
   W->y1 = y1+0.5;
   W->x2 = x1+0.5+ln;
   W->y2 = y1+0.5+wd;
   return W;
 }
DIF * Making_SlideF(DIALOG *D) {
   DIF *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   double  min=4,max=6,df=1;
   int ln=0,wd=0;
   int msize=0;
   float x1,y1,x2,y2;
   DIF Wtmp ={'f',0,100,0,0,1,100,100,NULL,NULL,NULL,NULL};

   W = (DIF *)malloc(sizeof(DIF));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   min = W->min;
   max = W->max;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
//   slidef(buf,&(W->lngth),&(min),&(max),&df);
   gscanf(Parent,(char *)"Length:%4dMin Val:%12FMax Val:%12FDef Val:%12FName%20s",&(W->lngth),&(min),&(max),&df,W->Wid);
   W->min = min;
   W->max = max;
#if 0
   i=0;while(buf[i]==' ')i++;
   n=0;while(buf[i+n]>=' ')n++;
   buf[n] ='\0';
#else
   n=0;
#endif
   W->prompt = (char *)malloc(n+1);
   if(n!=0) strcpy(W->prompt,buf+i);
   else W->prompt[0] = '\0';
   W->df = (double *)malloc(sizeof(double));
   *((double *)(W->df)) = df;
   GetSlidebarSizeF(W,&ln,&wd);
   x1=D->xo+10;y1=D->yo+10;
   x2=D->xo+10+ln;y2=D->yo+10+wd;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   
   W->x1 = x1+0.5;
   W->y1 = y1+0.5;
   W->x2 = x1+0.5+ln;
   W->y2 = y1+0.5+wd;
   return W;
 }
DIX * Making_Selectmenu(DIALOG *D) {
   DIX *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int  min=4,max=6,df=0,ln=0,w=25,h=200,maxchar=15;
   int msize=0;
   float x1,y1,x2,y2;
   DIX Wtmp = {'x',0L,0L,150,120,8,2,90,25,1,4,1,1,NULL,NULL,NULL,
           NULL,NULL,6,22,0,1,1,1,0};
   int type=2;
   char **xpm,name[60];
   int *sw;
   int xgap=0,ygap=0,lngth=200,width=160,nxb=1,nyb=2;
   static int Entry=0;
   W = (DIX *)malloc(sizeof(DIX));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
//   gscanf(Parent,(char *)"Length %4dHeight %4dNo of Items%4dItem Height%4dItem Gap%4d",&lngth,&width,&max,&w,&ygap);
   Runselectmenu(W);
   W->df = (int *)malloc(sizeof(int));
   max = W->ny;
   *((int *)(W->df)) = 1;
   W->list=(void **)MakeSampleThumbNails((int)(W->width*0.8),12);
   W->nx=1;
   W->ny= max;
   lngth= W->x2-W->x1;
   width = W->y2 - W->y1;
   W->lngth = lngth -2*W->offset-W->w-W->xgap;
   x1=10+D->xo;y1=10+D->yo;x2=x1+lngth;y2=y1+width;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   W->x1 = x1;
   W->y1 = y1;
   W->x2 = x1+lngth;
   W->y2 = y1+width;
   return W;
}
DIRA * Making_RadioButtons(DIALOG *D) {
   DIRA *W;
   char **menu;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int offset=10,w=22;
   int  min=4,max=6,df=0,ln=0,itemw=25,h=200,maxchar=15;
   int msize=0;
   float x1,y1,x2,y2;
   DIRA Wtmp = {'r',0L,0L,150,120,0,0,90,25,1,4,1,1,NULL,NULL,NULL,
           NULL,NULL,6,22,0,0,1,0,0};
   int type=2;
   char **xpm,name[60];
   int *sw;
   int xgap=0,ygap=0,lngth=200,width=160,nxb=1,nyb=2;
   static int Entry=0;
   W = (DIRA *)malloc(sizeof(DIRA));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   W->xgap=8;
   W->ygap=0;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
   Runcheckbox(W);
   W->prompt=(char *)" ";
   W->size = 2;
   W->df = (int *)malloc(sizeof(int));
   max = W->ny;
   *((int *)(W->df)) = 1;
   W->list= NULL;
   W->nx=1;
#if 0
   menu = (char **)malloc(sizeof(char *)*(max+1));
   menu[max]= NULL;
   for(i=0;i<max;i++){
    strcpy(buf1,"              ");
    sprintf(buf,"Give menu item %-d :%%15s",(i+1));
    gscanf(Parent,buf,buf1);
    min=0;while (*(buf1+min) != '\0') min++;
    if(msize<min) msize=min;
    menu[i]= (char *)malloc(min+1);
    strcpy(menu[i],buf1);
   }
#else
   menu = RungetStrings(D,max);
   i=0;
   msize=5;
   while(menu[i]!= NULL) {
     ln = strlen(menu[i]);
     if(ln> msize) msize=ln;
     i++;
   }
//   if(W->xgap<=0 ) W->xgap =msize*9;
#endif
   W->list = (void **)kgStringToThumbNails(menu);
   free(menu);
   lngth= W->x2-W->x1;
   width = W->y2 - W->y1;
   x1=10+D->xo;y1=10+D->yo;x2=x1+lngth;y2=y1+width;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   W->x1 = x1;
   W->y1 = y1;
   W->x2 = x1+lngth;
   W->y2 = y1+width;
   return W;
}
DICH * Making_CheckBox(DIALOG *D) {
   char **menu;
   DICH *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int offset=10,w=22;
   int  min=4,max=6,df=0,ln=0,itemw=25,h=200,maxchar=15;
   int msize=0;
   float x1,y1,x2,y2;
   DICH Wtmp = {'c',0L,0L,150,120,0,0,90,25,1,4,1,1,NULL,NULL,NULL,
           NULL,NULL,6,22,0,0,1,0,0};
   int type=2;
   char **xpm,name[60];
   int *sw;
   int xgap=0,ygap=0,lngth=200,width=160,nxb=1,nyb=2;
   static int Entry=0;
   W = (DICH *)malloc(sizeof(DICH));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
   W->xgap=8;
   W->ygap=0;
   Runcheckbox(W);
   W->prompt=(char *)" ";
   W->size = 2;
   W->df = (int *)malloc(sizeof(int));
   max = W->ny;
   *((int *)(W->df)) = 1;
   W->list=NULL;
   W->nx=1;
#if 0
   menu = (char **)malloc(sizeof(char *)*(max+1));
   menu[max]= NULL;
   for(i=0;i<max;i++){
    strcpy(buf1,"              ");
    sprintf(buf,"Give menu item %-d :%%15s",(i+1));
    gscanf(Parent,buf,buf1);
    min=0;while (*(buf1+min) != '\0') min++;
    if(msize<min) msize=min;
    menu[i]= (char *)malloc(min+1);
    strcpy(menu[i],buf1);
   }
#else
   menu=RungetStrings(D,max);
   i=0;
   msize=5;
   while(menu[i]!= NULL) {
     ln = strlen(menu[i]);
     if(ln> msize) msize=ln;
     i++;
   }
//   if(W->xgap<=0 ) W->xgap =msize*9;
#endif
   W->list = (void **)kgStringToThumbNails(menu);
   free(menu);
   lngth= W->x2-W->x1;
   width = W->y2 - W->y1;
   x1=10+D->xo;y1=10+D->yo;x2=x1+lngth;y2=y1+width;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   W->x1 = x1;
   W->y1 = y1;
   W->x2 = x1+lngth;
   W->y2 = y1+width;
   return W;
}
DIY * Making_ThumbnailBrowser(DIALOG *D) {
   DIY *W;
   int i,n;
   char buf[60],buf1[30]=" ";
   int  lng=100;
   int offset=10,w=22;
   int  min=4,max=6,df=0,ln=0,itemw=84,h=200,maxchar=15;
   int msize=0;
   float x1,y1,x2,y2;
   DIY Wtmp = {'y',0L,0L,324,264,8,20,64,64,3,4,3,1,NULL,NULL,NULL,
           NULL,NULL,6,22,0,1,1,1,0};
   int type=2;
   char **xpm,name[60];
   int *sw;
   int xgap=12,ygap=12,lngth=350,width=320,nxb=1,nyb=2;
   static int Entry=0;
   W = (DIY *)malloc(sizeof(DIY));
   Wtmp.Wid[0]='\0';
   *W = Wtmp;
   sprintf(W->Wid,"%-sWidget%-d",DiaName,++WidCount);
   Runthumbnail(W);
   W->prompt=(char *)" ";
   W->size = 2;
   W->df = (int *)malloc(sizeof(int));
   max = W->ny;
   *((int *)(W->df)) = 1;
   W->list=(void **)MakeSampleThumbNails((int)(W->width),20);
   W->nx=1;
   W->ny= max;
   lngth= W->x2-W->x1;
   width = W->y2 - W->y1;
   x1=10+D->xo;y1=10+D->yo;x2=x1+lngth;y2=y1+width;
   Box_gincur(&x1,&y1,&x2,&y2);
   x1 -=D->xo;
   y1 -=D->yo;
   W->x1 = x1;
   W->y1 = y1;
   W->x2 = x1+lngth;
   W->y2 = y1+width;
   return W;
}
int addoptdia(int *v0) {
 int ret,i;
 DIA d[2];
 DIALOG D;
 DIBN b1 ={'N',10L,10L,0,0,9,9,15,15,1,1,NULL,NULL,NULL,NULL,NULL,NULL};
 void **xpm0     = NULL;
 int  *bkgr0     = NULL;
 char *titles0[] = {
        (char *)"Text box",
        (char *)"Browser",
        (char *)"Buttons",
        (char *)"Hori.bar",
        (char *)"Message",
        (char *)"Pixmap",
        (char *)"Graph box",
        (char *)"Info box",
        (char *)"Slide(d)",
        (char *)"Quit",
        NULL
  };
 b1.prompt =(char *)malloc(sizeof(char)*1);
 b1.prompt[0]='\0';
 b1.xgap=9;
 b1.ygap=9;
 b1.width=25;
 b1.nx=1;
 b1.ny=10;
 b1.df=(int *)v0;
 b1.titles=titles0;
 b1.xpm=xpm0;
 b1.bkgr=bkgr0;
 b1.lngth=107;
 b1.x1=678;
 b1.y1=17;
 b1.x2=806;
 b1.y2=261;
 b1.type=3;
 b1.fac=0.2;
 d[0].n = &b1;
 d[0].b->x1 =24;
 d[0].b->y1 =24;
 d[0].b->x2 =152;
 d[0].b->y2 =359;
 d[1].t=NULL;
 D.d =d; D.xo =625; D.yo =6; D.xl = 167; D.yl =374;
 D.bkup =1;
 D.bor_type=4;D.tw=4;D.lw=4;D.rw=4;D.bw=4;
 D.df = -1;
 D.Initfun = NULL;
 D.Cleanupfun = NULL;
// ret = Dialog(&D);
  D.Deco=1;
  D.DrawBkgr=1;
  D.Bkpixmap=NULL;
  D.Callback=NULL;
  D.transparency = 0;
  D.Newwin=0;
  D.Sticky=0;
  D.Fixpos=1;
  D.NoTaskBar=0;
  D.Shapexpm=NULL;
  D.StackPos=0;
  kgDefaultGuiTheme(&(D.gc));
//  D.gc.GuiFontSize=9;
  D.SearchList=NULL;
  ret =kgUi(&D);
 free(b1.prompt);
 return ret;
}
int Dummy(int item,void *arg) {
  printf("Reached Dummy: item=%d\n",item);
  return 1;
}
void AddControl(DIALOG *D,void *T) {
  Dlink *L;
  DIA *d;
  DIT *t;
  int  but = 1    ;
  static float xpos=50,ypos=50;
  int ixpos=50,iypos=50,OK=0,i;
  char *addmenu[]={(char *)"Spl. Buttons",(char *)"Buttons",(char *)"Pulldown Browser",(char *)"Textbox",(char *)"Tablebox",(char *)"Slidebar(I)",
                  (char *)"Slidebar(F)",(char *)"Imagebox",(char *)"Drawing area",(char *)"Info box",(char *)"Message",(char *)"Display Box",(char *)"Message(B)",
                   (char *)"Scroll Menu",(char *)"Msg Scroll",(char *)"Hori Slide Bar",(char *)"Selection Menu",(char *)"Radio Buttons",
                   (char *)"Check Box",(char *)"ThumbnailBrowser",(char *)"ProgressBar",(char *)"Vert. Scroll",(char *)"Horiz. Scroll",NULL};
  Convert_gui_data();
  d = D->d;
  L = Dopen();
  i=0; while (d[i].t != NULL) {Dadd(L,d[i].t);i++;}
  if(WidCount==0) WidCount=Dcount(L);
  /*while(but !=15) {*/
//   but = kgMenu(Parent,100,45,1,0,addmenu,20);
//   but = kgMenu1(Parent,120,45,0,addmenu,21,Dummy,NULL);
   but = kgMenu1(Parent,120,45,0,addmenu,23,NULL,NULL);
   switch(but) {
     case 4:
      kgPrintf(Parent,2,(char *)"!s!f31!z53TEXT BOX.....");
      t = Making_t_box(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 5:
      kgPrintf(Parent,2,(char *)"!s!f31!z53TABLE BOX.....");
      t = Making_T_box(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 2:
      kgPrintf(Parent,2,(char *)"!s!f31!z53BUTTONS.....");
      t = (DIT *)Making_Buttons(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 3:
      kgPrintf(Parent,2,(char *)"!s!f31!z53BROWSER.....");
      t = (DIT *)Making_Browser(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 14:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Scroll Menu.....");
      t = (DIT *)Making_Menu(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 15:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Msg Scroll.....");
      t = (DIT *)Making_MsgScroll(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 17:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Selection Menu.....");
      t = (DIT *)Making_Selectmenu(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 18:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Radio Buttons.....");
      t = (DIT *)Making_RadioButtons(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 19:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Check Box.....");
      t = (DIT *)Making_CheckBox(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 20:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Thumbnail Browser.....");
      t = (DIT *)Making_ThumbnailBrowser(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 21:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Progrss Bar.....");
      t = (DIT *)Making_Progressbar(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 22:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Vert. Scroll.....");
      t = (DIT *)Making_Vertscroll(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 23:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Horiz. Scroll.....");
      t = (DIT *)Making_Horizscroll(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 1:
      /*
      if( horicntl < 1) {
        twin_wprintf(T,"HORI. BAR");
        t = (DIT *)Making_hori_bar(D);
        Dappend(L,t);
      }
      else gprintf(Parent,(char *)"HORI BAR IS DEFINED.. MORE THAN 1 NOT ALLOWED");
      */
      kgPrintf(Parent,2,(char *)"!s!f31!z53HORI. BAR.....");
//      t = (DIT *)Making_hori_bar(D);
      t = (DIT *)Making_SplButtons(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 16:
      kgPrintf(Parent,2,(char *)"!s!f31!z53Hori Slide Bar...");
      t = (DIT *)Making_SlideH(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 6:
      kgPrintf(Parent,2,(char *)"!s!f31!z53SLIDE(D) BAR...");
      t = (DIT *)Making_SlideD(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 7:
      kgPrintf(Parent,2,(char *)"!s!f31!z53SLIDE(F) BAR...");
      t = (DIT *)Making_SlideF(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 11:
      kgPrintf(Parent,2,(char *)"!s!f31!z53MESSAGE BOX...");
      t = (DIT *)Making_Message(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 12:
      kgPrintf(Parent,2,(char *)"!s!f31!z53DISPLAY BOX...");
      t = (DIT *)Making_DisplayBox(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 13:
      kgPrintf(Parent,2,(char *)"!s!f31!z53MESSAGE BOX...");
      t = (DIT *)Making_Messageb(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 8: /* pixmap */
      kgPrintf(Parent,2,(char *)"!s!f31!z53PIXMAP BOX...");
      t = (DIT *)Making_Pixmap(D);
      if(t!= NULL) Dappend(L,t);
      kgPrintf(Parent,2,(char *)"!s!f31!z53MADE PIXMAP BOX...");
      break;
     case 9: /* graph box */
      kgPrintf(Parent,2,(char *)"!s!f31!z53GRAPHICS BOX...");
      t = (DIT *)Making_Graphbox(D);
      if(t!= NULL) Dappend(L,t);
      break;
     case 10: /* info box */
      kgPrintf(Parent,2,(char *)"!s!f31!z53INFO.  BOX...");
      t = (DIT *)Making_Infobox(D);
      if(t!= NULL) Dappend(L,t);
      break;
     default:
      break;
   }
  Make_dialog_structure(D,L);
  Convert_gui_data();
  SetControlCounters(D);
  Dfree(L);
}
void Runmakeguidia(void *parent) {
/*************************************************

    Buttonbox1 (new) 1 data value

*************************************************/
   void **v=NULL;
   void **pt=NULL;
   makeguidia( parent,v,pt);
}
int main(int narg,char **args) {
  FILE *fp,*tp;
  char buff[500];
  if(getenv("KULINA")==NULL) {
    fprintf(stderr,"KULINA is not set, setting as /usr\n");
//    exit(0);
    setenv ("KULINA","/usr",0);
  }
  strcpy(kulinahome,getenv("KULINA"));
  if( narg < 2) {
    printf("Usage: kgdesigner  <dianame> \n");
    exit(0);
  }
  if(narg> 2) {
    if(strcmp(args[1],"-f")==0 ) FullScreen=1;
  }
  strcpy(DiaName,args[1]);
  sprintf(flname,"%-s.rc",args[1]);
  sprintf(Sourcecode,"%-s.src",args[1]);
  sprintf(Callbackcode,"%-sCallbacks.src",args[1]);
  sprintf(Includecode,"%-sCallbacks.h",args[1]);
  sprintf(Maincode,"main.src");
#if 0
  Dia = Make_dialog_structure_from_file(flname);
  SetControlCounters(Dia);
#endif
  getcwd(CWD,499);
  mkdir((char *)"Images",0700);
  Runmakeguidia(NULL);
  if( (fp= fopen("Makefile","r"))== NULL) {
    fp= fopen("Makefile","w");
    fprintf(fp,"KULINA=/usr\n");
    fprintf(fp,"#CC\t=g++ -pthread\n");
    fprintf(fp,"CC\t=cc -pthread\n");
    fprintf(fp,"%-s\t: %-s.o %-sCallbacks.o main.o\n",args[1],args[1],args[1]);
    /* fprintf(fp,"\t cc -o %-s %-s.o %-sCallbacks.o main.o $(PARAS)/lib/glib.a -lX11 -lm\n",args[1],args[1],args[1]);*/
    fprintf(fp,"\t $(CC) -o %-s %-s.o %-sCallbacks.o main.o -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread -lz -lbz2 -lGL\n",args[1],args[1],args[1]);
    fprintf(fp,"%-s.o\t: %-s.c \n",args[1],args[1]);
    fprintf(fp,"\t $(CC) -c %-s.c\n",args[1]);
    fprintf(fp,"%-sCallbacks.o\t: %-sCallbacks.c \n",args[1],args[1]);
    fprintf(fp,"\t $(CC) -c %-sCallbacks.c\n",args[1]);
    fprintf(fp,"main.o\t: main.c \n");
    fprintf(fp,"\t $(CC) -c main.c\n");
    fprintf(fp,"clean\t:  \n");
    fprintf(fp,"\t   rm -f *.o %-s\n",args[1]);
    fclose(fp);
    tp = fopen("/usr/include/kulina.h","r");
    if(tp != NULL) {
      fclose(tp);
      system("cp /usr/include/kulina.h kulina.h");
    }
    else {
      tp = fopen("/usr/local/include/kulina.h","r");
      if(tp != NULL) {
        fclose(tp);
        system("cp /usr/local/include/kulina.h kulina.h");
      }
      else system("cp $KULINA/include/kulina.h kulina.h");
    }
  }
  else fclose(fp);
  if( (fp= fopen("main.c","r"))== NULL) {
    sprintf(buff,"cp main.src main.c");
    system(buff);
  }
  else fclose(fp);
  sprintf(buff,"%-sCallbacks.c",args[1]);
  if( (fp= fopen(buff,"r"))== NULL) {
    sprintf(buff,"cp %-sCallbacks.src %-sCallbacks.c",args[1],args[1]);
    system(buff);
  }
  else fclose(fp);
  sprintf(buff,"%-s.c",args[1]);
  if( (fp= fopen(buff,"r"))== NULL) {
    sprintf(buff,"cp %-s.src %-s.c",args[1],args[1]);
    system(buff);
  }
  else fclose(fp);
  return 1;
}
