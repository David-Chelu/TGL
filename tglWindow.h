#ifndef TGL_WINDOW_H
    #define TGL_WINDOW_H



class TGL::tglWindow : public TGL::tglObject
{
public:

    tglWindow();
    ~tglWindow();



    void
        DisplayValues() const,
        Initialize(),
        Debug();



    TGL::Identity
        identity() const;

private:

    HMENU
        m_menuHandle;

    DWORD
        m_style,
        m_extendedStyle;

    const char
        *m_windowName,
        *m_className;

    WNDPROC
        m_windowProcedure;

    HWND
        m_parentWindow,
        m_windowHandle;

    WNDCLASS
        m_windowClass;

    HINSTANCE
        m_windowInstance;

    int32_t
        m_xPosition,
        m_yPosition;

    uint32_t
        m_backgroundColor,
        m_width,
        m_height;
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

    std::cout<< "\nHas menu: " << (this->m_menuHandle? "Yes" : "No")

             << "\nStyle: "          << TGL::StyleList        (this->m_style)
             << "\nExtended Style: " << TGL::ExtendedStyleList(this->m_extendedStyle)

             << "\nWindow name: " << this->m_windowName
             << "\nClass name: "  << this->m_className

             << "\nHas window procedure: " << (this->m_windowProcedure? "Yes" : "No")

             << "\nHas parent window: " << (this->m_parentWindow? "Yes" : "No")
             << "\nHas window handle: " << (this->m_windowHandle? "Yes" : "No")

             << "\nHas window instance: " << (this->m_windowInstance? "Yes" : "No")

             << "\nxPosition: " << this->m_xPosition
             << "\nyPosition: " << this->m_yPosition

             << "\nBackground color: " << TGL::ColorName(this->m_backgroundColor)
             << "\nWidth: "  << this->m_width
             << "\nHeight: " << this->m_height;
}

void TGL::tglWindow::Initialize()
{
    this->m_menuHandle = NULL;

    this->m_style = WS_VISIBLE;
    this->m_extendedStyle = 0;

    this->m_windowName = "TGL Window";
    this->m_className  = "Made Using TGL::tglWindow";

    this->m_windowProcedure = TGL::WindowProcedure;

    this->m_parentWindow =
    this->m_windowHandle = NULL;

    ZeroMemory(&this->m_windowClass, sizeof(this->m_windowClass));

    this->m_windowInstance = TGL::creationWindowInstance;

    this->m_xPosition =
    this->m_yPosition = 0;

    this->m_backgroundColor = GRAY_BRUSH;

    this->m_width  = TGL::screenWidth;
    this->m_height = TGL::screenHeight;
}



TGL::Identity TGL::tglWindow::identity() const
{
    return TGL::Identity::TGL_WINDOW;
}



#include "tglWindow Functions.h"



#endif // TGL_WINDOW_H



































