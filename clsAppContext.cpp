#include "clsAppContext.h"

#include <fmt/format.h>
#include <fmt/color.h>
extern Fl_Double_Window* winit_form1();


clsAppContext::clsAppContext()
{
    //ctor
  InitWinTermCon();
  fmt::print(fg(fmt::color::yellow_green), "FLTK ABI:{:d}\n",Fl::abi_version());
  fmt::print(fg(fmt::color::light_blue), "GenContext version: {}\n",libver);
//  fmt::print(fg(fmt::rgb(255, 120, 30)),"\t Test\n");
}

clsAppContext::~clsAppContext()
{
    //dtor

}

void clsAppContext::init_windows(){
  RegisterWin("Main",win);
  RegisterWin("Form1",winit_form1());

};
