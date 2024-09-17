#ifndef TGL_WINDOW_H
    #define TGL_WINDOW_H



#include "WindowAttributes.h"



class TGL::tglWindow : public TGL::tglObject
{
public:

    tglWindow();
    tglWindow(const std::string &text);
    tglWindow(const TGL::tglWindow &window);
    ~tglWindow();



    inline TGL::tglWindow
        &Assign(const std::string &text)
       ,&Assign(const TGL::tglWindow &window)
       ;



    TGL::tglWindow
        &operator =(const std::string &text)
       ,&operator =(const TGL::tglWindow &window)
       ;

    operator bool() const;
    bool operator !() const;



    bool
        Show()
       ,Hide()
       ,Update(HWND insertAfter = NULL, UINT flags = SWP_SHOWWINDOW)
       ,FillScreen()
       ,Center()
       ,Decenter()
       ,ResizeToWorkRect()
       ,SnapToWorkRect()
       ,SetToWorkRect()
       ;

    HWND
        Create(),
        Create(const TGL::WindowAttributes &attributes);

    inline HWND
        RequestHWND();

    inline void
        DisplayValues() const;

    void
        Clear()
       ,Reset()
       ;

    inline std::string
        GetValues() const;



    const HWND
        handle() const;

    const bool
        &centered;

    const TGL::WindowAttributes
        &current;

    TGL::WindowAttributes
        &planned;

    largeuint_t
        xClient() const,
        yClient() const;

private:

    void
        Initialize();



    TGL::WindowAttributes
        m_current,
        m_planned;

    HWND
        m_handle;

    bool
        m_centered;

    RECT
        m_clientRect;

};



#endif // TGL_WINDOW_H
