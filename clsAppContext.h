#ifndef CLSAPPCONTEX_H
#define CLSAPPCONTEX_H
#include "GenContext/clsGenContext.h"
#include "main.h"



class clsAppContext:public clsGenContext
{
    public:
      void init_windows();
      clsAppContext();
      virtual ~clsAppContext();
      virtual int CheckPostBox(const int msg);
  //-- -----------------------
    void cbClose();
    void cbNew();
    void cbTest();
    protected:

    private:
};

#endif // CLSAPPCONTEX_H
