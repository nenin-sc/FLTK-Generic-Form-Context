#ifndef CLSGENCONTEXT_H
#define CLSGENCONTEXT_H
#include <unordered_map>
#include <string>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
/*
Generic context class for Fl_Window
*/
#if defined(WIN32) || defined(_WIN32)
  // source:  https://stackoverflow.com/questions/31050113/how-to-extract-the-source-filename-without-path-and-suffix-at-compile-time
  constexpr const char* source_file_name_str_end(const char *str) {
    return *str ? source_file_name_str_end(str + 1) : str;
   }
  constexpr bool source_file_name_str_slant(const char *str) {
    return *str == '\\' ? true : (*str ? source_file_name_str_slant(str + 1) : false);
   }
  constexpr const char* source_file_name_r_slant(const char* str) {
    return *str == '\\' ? (str + 1) : source_file_name_r_slant(str - 1);
   }
  constexpr const char* source_file_name_4_assert(const char* str) {
    return source_file_name_str_slant(str) ? source_file_name_r_slant(source_file_name_str_end(str)) : str;
}

#elif
    constexpr const char* source_file_name_str_end(const char *str) {
    return *str ? source_file_name_str_end(str + 1) : str;
   }
   constexpr bool source_file_name_str_slant(const char *str) {
    return *str == '/' ? true : (*str ? source_file_name_str_slant(str + 1) : false);
   }
   constexpr const char* source_file_name_r_slant(const char* str) {
    return *str == '/' ? (str + 1) : source_file_name_r_slant(str - 1);
   }
   constexpr const char* source_file_name_4_assert(const char* str) {
    return source_file_name_str_slant(str) ? source_file_name_r_slant(source_file_name_str_end(str)) : str;
}

#endif
  #define ERR_PLACE {source_file_name_4_assert(__FILE__),__LINE__}
class clsGenContext
{
    public:
        constexpr static const char * libver="20241206.00";

        enum {PBX_OK=0, PBX_NOT_MINE=-1, PBX_EMPTY_ADDR=-2,PBX_INVALIDE_ADDR=-3,PBX_NOT_FOUND=-4,};
        const static size_t MaxIDLength=2077;// maximum length of the ID/keys for Widgets and Windows, used for protection from some char*  features inside
        struct strErrorLocation{const char * file; const int line;};
        static bool console_lock;
        template<class T>
        inline T * GetWg(const std::string & key,  const strErrorLocation & place=voiderr) const {
               std::unordered_map<std::string,Fl_Widget *>::const_iterator tmp = widg_reg.find(key);
               if( tmp==widg_reg.end())
                  return (T*) fatal_error_trap(0u,key.c_str(),place);
               return (T*) tmp->second; };
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~
       inline Fl_Double_Window * GetWin(const std::string & key, const strErrorLocation & place=voiderr) const {
           auto tmp = win_reg.find(key);
           if( tmp==win_reg.end())
              return (Fl_Double_Window *) fatal_error_trap(1,key.c_str(),place);
           return tmp->second;
           };
   //~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void RegisterWg(const std::string & key, Fl_Widget * v, const strErrorLocation & place=voiderr);
        inline Fl_Double_Window * Win() const {return win;};
        void Win( Fl_Double_Window  *w, const strErrorLocation & place=voiderr);
        virtual inline Fl_Double_Window * ParentWin() const {return parent_win;};
        virtual inline Fl_Double_Window * LeafWin() const {return parent_win;};
        virtual inline void ParentWin(  Fl_Double_Window *w)  {parent_win=w;};
        virtual inline void LeafWin(  Fl_Double_Window *w)  {leaf_win=w;};
        void RegisterWin(const std::string & key,  Fl_Double_Window *w, const strErrorLocation & place=voiderr );
        clsGenContext();
        virtual ~clsGenContext();
        void InitWinTermCon();
        virtual void TheEnd(); // close all windows;
    // Post Office: ability to send messages for different forms, mainly to enable/disable/clear/refresh widgets
        virtual int CheckPostBox(const int msg) { return PBX_NOT_MINE;}; // "0" received and treated; "-1" - "not mine"; other values - error codes (?);
        static int PutInPostBox(const int msg,size_t & nAddr); // "0"- OK, other -error codes; nAddr - Number of addressee, return number of unserved recipients;
        static int PutInPostBox(const int msg,const char* Addr); //  "0"- OK, other -error codes; Addr - ID of Window to search

    protected:
        Fl_Double_Window        * win,  // window of this context            -- const
                          *parent_win,  // window, which called this context -- const
                            *leaf_win;  // window, which returned to context -- last called window, temporary
        static std::unordered_map<std::string, Fl_Double_Window*> win_reg;
        std::unordered_map<std::string, Fl_Widget *> widg_reg;
        void * fatal_error_trap(const size_t idx, const char *key, const strErrorLocation & place=voiderr) const;
    private:

        static strErrorLocation voiderr;
};

#endif // CLSGENCONTEXT_H
