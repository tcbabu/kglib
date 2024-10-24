#include <kulina.h>
float Ox1,Oy1,Ox2,Oy2;
void sample1gbox1init(int i,void *Tmp) {
  /*********************************** 
    int routine for grahics area 
   ***********************************/ 
  DIALOG *D;void *pt;
  DIG *G;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  G = D->d[i].g;
  G->D = (void *)(Tmp);
  kgViewport(G,0.,0.,1.,1.);
  kgUserFrame(G,0.0,0.,100.,75.);
  kgMove2f(G,5.0,5.0);
  kgDraw2f(G,5.,70.);
  kgDraw2f(G,95.,70.);
  kgDraw2f(G,95.,5.);
  kgDraw2f(G,5.,5.);
  kgGetWindow(G,&Ox1,&Oy1,&Ox2,&Oy2);
  return ;
}
int  sample1splbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(butno) {
    case 1: 
      break;
  }
  return ret;
}
void  sample1splbutton1init(DIL *B,void *pt) {
}
int  sample1button1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  DIG *G;
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  G = (DIG *)kgGetNamedWidget(D,"sample1Widget1");
  switch(butno) {
    case 1: 
      kgDrawingTool(G);
      break;
    case 2: 
      kgPointerZoom(G);
      break;
    case 3: 
      kgUserFrame(G,Ox1,Oy1,Ox2,Oy2);
      kgReview(G);
      break;
    case 4: 
      kgAntialiasingOn(G,1);
      kgReview(G);
      break;
    case 5: 
      kgAntialiasingOff(G);
      kgReview(G);
      break;
    case 6: 
      if(kgQstMenu(Tmp,20,200,"Create |image.png| ?",1) ) {
        kgImageCopy(G,"image");
      }
      break;
  }
  return ret;
}
void  sample1button1init(DIN *B,void *pt) {
}
int sample1init(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int sample1cleanup(void *Tmp) {
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
int sample1CallBack(void *Tmp,void *tmp) {
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
int sample1ResizeCallBack(void *Tmp) {
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
int sample1WaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  return ret;
}
