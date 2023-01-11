#include <iostream>
#include "TGL.h"

void TGL::tglWindow::Debug()
{
//    this->m_style = 0;
//    this->m_extendedStyle = 0;
//    this->DisplayValues();
//
//    std::cout << "\n\n\n";
//
//    this->m_style = WS_POPUP;
//    this->m_extendedStyle = WS_EX_ACCEPTFILES;
//    this->DisplayValues();
//
//    std::cout << "\n\n\n";
//
//    this->m_style = WS_POPUP | WS_BORDER;
//    this->m_extendedStyle = WS_EX_ACCEPTFILES | WS_EX_APPWINDOW;
//    this->DisplayValues();
//
//    std::cout << "\n\n\n";
//
//    this->Initialize();
}



int main()
{
    TGL::tglWindow
        *window = new TGL::tglWindow;

    window->DisplayValues();

    delete window;



    MessageBox(NULL,
               "Close message box to end the program.",
               "End of Process",
               MB_OK);



    return 0;
}
