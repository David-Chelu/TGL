#include <iostream>
#include "TGL.h"



int main()
{
    TGL::tglObject
        *window = new TGL::tglWindow;

    window->DisplayValues();

    delete window;



    MessageBox(NULL,
               "Close message box to end the program.",
               "End of Process",
               MB_OK);



    return 0;
}
