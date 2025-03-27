#include "clsAppContext.h"

void clsAppContext::cbClose(){
 Win()->hide();
};

void clsAppContext::cbTest(){
 GetWg<Fl_Input>("intx_test",ERR_PLACE)->value("Main");
};

void clsAppContext::cbNew(){
 Win()->deactivate();
 auto tdw=GetWin("Form1",ERR_PLACE);
 auto new_cntxt=reinterpret_cast<clsGenContext *>(tdw->user_data());
 new_cntxt->ParentWin(Win());
 new_cntxt->Win()->show();
}

int clsAppContext::CheckPostBox(const int msg){
 auto inp=GetWg<Fl_Input>("intx_test",ERR_PLACE);
 inp->value("Msg");
 return 0;
};
