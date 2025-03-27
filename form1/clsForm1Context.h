#ifndef CLSFORM1CONTEXT_H
#define CLSFORM1CONTEXT_H
#include "../GenContext/clsGenContext.h"
#include "form1.h"

class clsForm1Context:public clsGenContext
{
    public:
        clsForm1Context();
        virtual ~clsForm1Context();
        void InitWinCon();
  //-- ---------------------
    void cbClose();
    protected:

    private:
};

#endif // CLSFORM1CONTEXT_H
