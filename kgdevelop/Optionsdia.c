#include <kulina.h>
int DiaCallBack(void *Tmp,void *tmp);
extern DIALOG *Dia;
static int BodrType=4,Sticky=0,FixPos=1,Deco=1,FullScreen=0,KbAttn=0,BtAttn=0,NewWin=0,DrBk=1,NoTaskBar=0;
static int Resize=0,MinWidth=100,MinHeight=100,StackPos=0;
static float Transparency=0.0;
extern DIALOG *Parent;
void InitOptions(DIALOG *D) {
  Sticky= D->Sticky;
  BodrType= D->bor_type;
  KbAttn= D->kbattn ;
  BtAttn= D->butattn ;
  Deco= D->Deco ;
  FullScreen= D->fullscreen ;
  Transparency= D->transparency ;
  NewWin= D->Newwin ;
  FixPos= D->Fixpos ;
  NoTaskBar= D->NoTaskBar ;
  DrBk = D->DrawBkgr;
  Resize = D->Resize;
  MinWidth = D->MinWidth;
  MinHeight= D->MinHeight;
  StackPos = D->StackPos;
  return;
}
void SetOptions(DIALOG *D) {
  D->Sticky=Sticky;
  D->bor_type=BodrType;
  D->kbattn = KbAttn;
  D->butattn = BtAttn;
  D->Deco = Deco;
  D->fullscreen = FullScreen;
  D->transparency = Transparency;
  D->Newwin = NewWin;
  D->Fixpos = FixPos;
  D->DrawBkgr= DrBk;
  D->NoTaskBar = NoTaskBar;
  D->Resize  =Resize;
  D->MinWidth = MinWidth;
  D->MinHeight = MinHeight;
  D->StackPos  = StackPos;
  D->Shapexpm=NULL;
  D->ResizeCallback=NULL;
  D->WaitCallback=NULL;
  return;
}
void *RunOptionsdia(void *arg) {
/*************************************************

    Browser1  1 data value
    Browser2  1 data value
    Browser3  1 data value
    Browser4  1 data value
    Browser5  1 data value
    Browser6  1 data value
    Browser7  1 data value
    Browser8  1 data value
    Browser9  1 data value
    Floatslidebar1  1 data value
    Browser10  1 data value

*************************************************/
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   int   v4 = 1;
   int   v5 = 1;
   int   v6 = 1;
   int   v7 = 1;
   int   v8 = 1;
   double v9 = 0.0;
   int   v10 = 1;
   v10=BodrType+1;
   v0=Sticky+1;v1=FixPos+1;v2=Deco+1;v3=FullScreen+1;v4=KbAttn+1;v5=BtAttn+1;v6=NewWin+1;v7=DrBk+1;v8=NoTaskBar+1;
   v9=Transparency;
//   Optionsdia(arg ,&v0 ,&v1 ,&v2 ,&v3 ,&v4 ,&v5 ,&v6 ,&v7 ,&v8 ,&v9 ,&v10 );
   BodrType=v10-1;
   Sticky=v0-1;FixPos=v1-1;Deco=v2-1;FullScreen=v3-1;KbAttn=v4-1;BtAttn=v5-1;NewWin=v6-1;DrBk=v7-1;NoTaskBar=v8-1;
   Transparency=v9;
   return NULL;
}
