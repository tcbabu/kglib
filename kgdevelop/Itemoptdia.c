#include <kulina.h>
extern DIALOG *Parent;
extern int Evgay;
extern DIALOG *Dia;
extern void *T;
void uitwin_wprintf(DIALOG *D,void *Tmp,char *s);
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
void Convert_gui_data(void);
void Align_items(DIALOG *D);
void Vert_Align_items(DIALOG *D);
void Hori_Align_items(DIALOG *D);

int RunItemoptdia(void *arg) {
/*************************************************

    Buttonbox1 (new) 1 data value

*************************************************/
   char *menu[]={(char *)"Add",(char *)"Delete",(char *)"Resize",(char *)"Repos",(char *)"Toggle Visibility",(char *)"Vert. Align",(char *)"Hoz. Align",NULL};
   int   v0 = 1;
   switch(kgMenu1(Parent,120,45,0,menu,7,NULL,NULL)) {
      case 1:
        AddControl(Dia,T);
        DRAW_DIALOG(Dia);
        break;
      case 2:
        DeleteControl(Dia);
        DRAW_DIALOG(Dia);
        break;
      case 3:
        ChangeControlSize(Dia);
        DRAW_DIALOG(Dia);
        break;
      case 4:
        ChangeControlPos(Dia);
        DRAW_DIALOG(Dia);
        break;
      case 5:
        ChangeControlVisibility(Dia);
        DRAW_DIALOG(Dia);
        break;
      case 6:
        Hori_Align_items(Dia);
        DRAW_DIALOG(Dia);
        break;
      case 7:
        Vert_Align_items(Dia);
        DRAW_DIALOG(Dia);
        break;
       default:
        break;
   }
   return v0;
}
