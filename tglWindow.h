#ifndef TGL_WINDOW_H
    #define TGL_WINDOW_H



class TGL::tglWindow : public TGL::tglObject
{
public:

    tglWindow();
    ~tglWindow();



    void
        DisplayValues() const,
        Initialize();



    TGL::Identity
        identity() const;

private:

};



TGL::tglWindow::tglWindow()
{
    this->Initialize();
}

TGL::tglWindow::~tglWindow()
{
}



void TGL::tglWindow::DisplayValues() const
{
    TGL::tglObject::DisplayValues();
}

void TGL::tglWindow::Initialize()
{
}



TGL::Identity TGL::tglWindow::identity() const
{
    return TGL::Identity::TGL_WINDOW;
}



#include "tglWindow Functions.h"



#endif // TGL_WINDOW_H



































