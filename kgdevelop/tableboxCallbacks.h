int  tableboxtextbox1callback(int cellno,int i,void *Tmp);
int  tableboxbrowser1callback(int item,int i,void *Tmp) ;
void  tableboxbrowser1init(DIRA *R,void *pt) ;
int  tableboxbrowser2callback(int item,int i,void *Tmp) ;
void  tableboxbrowser2init(DICH *C,void *pt) ;
int  tableboxsplbutton1callback(int butno,int i,void *Tmp) ;
void  tableboxsplbutton1init(DIL *B,void *pt) ;
int tableboxinit(void *Tmp) ;
int tableboxcleanup(void *Tmp) ;
int Modifytablebox(void *Tmp,int GrpId) ;
int tableboxCallBack(void *Tmp,void *tmp) ;
int tableboxResizeCallBack(void *Tmp) ;
int tableboxWaitCallBack(void *Tmp) ;
