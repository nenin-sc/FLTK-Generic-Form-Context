#include "../clsAppContext.h"
#include "clsForm1Context.h"


void clsForm1Context::cbClose(){
 Fl_Double_Window * parent_win=ParentWin();
 auto parent_cntxt=reinterpret_cast< clsAppContext *>(parent_win->user_data());
 parent_cntxt->GetWg<Fl_Input>("intx_test",ERR_PLACE)->value(GetWg<Fl_Input>("intx_test",ERR_PLACE)->value());
 parent_win->activate();
 Win()->hide();
};
