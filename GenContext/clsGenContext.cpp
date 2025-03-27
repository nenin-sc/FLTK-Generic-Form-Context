
#if defined(WIN32) || defined(_WIN32)
 #include <windows.h> // AllocConsole()
 #include <wincon.h> // AttachConsole()
#endif
#include <Fl/fl_ask.h>
#include "clsGenContext.h"
//const strErrorLocation VoidErrorLocation={nullptr, 0};
clsGenContext::strErrorLocation clsGenContext::voiderr={nullptr,0};
std::unordered_map<std::string, Fl_Double_Window*> clsGenContext::win_reg;
static const char *errcod[5]={"Request for invalid Widget key: \"%s\" from %s:%d.", //0
                              "Request for invalid Window key: \"%s\" from %s:%d.",  // 1
                              "Introduction of non-unique Widget key: \"%s\" from %s:%d.", //2
                              "Introduction of non-unique Window key: \"%s\" from %s:%d.", //3
                              "Attempt to re-assign Window for context: \"%s\" from %s:%d." //4
                              };
 bool clsGenContext::console_lock=false;
clsGenContext::clsGenContext()
{
    //ctor
  win=nullptr;
  parent_win=nullptr;
  leaf_win=nullptr;

}
//----------------------------------
clsGenContext::~clsGenContext()
{
    //dtor
}
//----------------------------------
void clsGenContext::TheEnd(){
 auto wnm=Win();
 for(auto &rwi:win_reg){
   if(rwi.second==wnm) continue;
   rwi.second->hide();
 }
 wnm->hide();

};
//----------------------------------
void * clsGenContext::fatal_error_trap(const size_t idx, const char *key, const strErrorLocation & place)  const{
 fl_alert(errcod[idx],key,(place.file!=nullptr)?place.file:"not defined",(place.file!=nullptr)?place.line:-1);
 exit(1);
 return nullptr;
};
//
void clsGenContext::Win( Fl_Double_Window  *w, const strErrorLocation & place){
            if( win!=nullptr) {
              std::string key="Unknown";
              for(auto const &mp:win_reg )
               if(mp.second==win){
                  key=mp.first;
                 break;
                }
              fatal_error_trap(4,key.c_str(),place);
              }
             else
           win=w;};
//----  --------------------------------------------------------------------------------------------------------
 void clsGenContext::RegisterWg(const std::string & key, Fl_Widget * v, const strErrorLocation & place) {
          auto tmp = widg_reg.find(key);
            if( tmp!=widg_reg.end()) {
                  fatal_error_trap(2,key.c_str(),place);
                   } else
            widg_reg[key]=v; };
 //----  -------------------------------------------------------------------------------------------------------
 void clsGenContext::RegisterWin(const std::string & key,  Fl_Double_Window *w, const strErrorLocation & place) {
           auto tmp = win_reg.find(key);
           if( tmp!=win_reg.end()) {
                  fatal_error_trap(3,key.c_str(),place);
                   } else
           win_reg[key]=w;};
//----  --------------------------------------------------------------------------------------------------------
 void clsGenContext::InitWinTermCon(){
 if(clsGenContext::console_lock) return;
 #if defined(WIN32) || defined(_WIN32) || defined(WIN64)

  clsGenContext::console_lock=true;
  HWND hwndFound;
 // FreeConsole(); not help against default debug console
  AllocConsole() ;
  AttachConsole(GetCurrentProcessId()) ;
  freopen("CON", "w", stdout) ;
  freopen("CON", "w", stderr) ;
  size_t MY_BUFSIZE= 1024;
  char pszNewWindowTitle[MY_BUFSIZE];
  char pszOldWindowTitle[MY_BUFSIZE];
  GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);
  wsprintf(pszNewWindowTitle,"%d/%d",
  GetTickCount(),
  GetCurrentProcessId());
  SetConsoleTitle(pszNewWindowTitle);
  Sleep(40);
  hwndFound=FindWindow(NULL, pszNewWindowTitle);
  SetConsoleTitle(pszOldWindowTitle);
  HMENU  menu=GetSystemMenu(hwndFound, FALSE);
  size_t rs=DeleteMenu(menu, 6, 1024);
  COORD ccc={80,120};
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);


 #endif
 };
//----------------

int clsGenContext::PutInPostBox(const int msg, size_t &nAddr){
  if(nAddr==0) return PBX_EMPTY_ADDR; // empty request
  for(auto wn:win_reg){
   auto cntx=reinterpret_cast<clsGenContext*>(wn.second->user_data());
   const int rs=cntx->CheckPostBox(msg);
   if(msg==0&&(--nAddr)==0) return PBX_OK;
  }
  return PBX_NOT_FOUND; // (somebody) not found
 };
//-----------------------------------------------------------------
 int clsGenContext::PutInPostBox(const int msg, const char* addr){
  auto rs=strnlen_s(addr,MaxIDLength);
  if(rs==0) return PBX_EMPTY_ADDR; // empty request
  if(rs==MaxIDLength) return PBX_INVALIDE_ADDR; // invalide addr string (must be shorter than 2077)
   auto wn = win_reg.find(addr);
   if( wn!=win_reg.end()) {
      auto cntx=reinterpret_cast<clsGenContext*>((*wn).second->user_data());
      const int rsc=cntx->CheckPostBox(msg);
      return rsc;
           };
  return PBX_NOT_FOUND; // not found --
 };
