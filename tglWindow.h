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



    bool
        Show()
       ,Hide()
       ,Update(HWND insertAfter = NULL, UINT flags = SWP_SHOWWINDOW)
       ,FillScreen()
       ;

    HWND
        Create(),
        Create(const TGL::WindowAttributes &attributes);

    inline void
        DisplayValues() const;

    void
        Clear()
       ,Reset()
       ,Center()
       ,Decenter()
       ;

    inline std::string
        GetValues() const;



    const HWND
        handle() const;

    bool
        centered() const;

    const TGL::WindowAttributes
        &current;

    TGL::WindowAttributes
        &planned;

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

};



TGL::tglWindow::tglWindow() : current(m_current), planned(m_planned)
{
    this->Initialize();
}

TGL::tglWindow::tglWindow(const std::string &text) : tglWindow()
{
    this->Assign(text);
}

TGL::tglWindow::tglWindow(const TGL::tglWindow &window) : tglWindow()
{
    this->Assign(window);
}

TGL::tglWindow::~tglWindow()
{
    this->Clear();
}



TGL::tglWindow &TGL::tglWindow::Assign(const std::string &text)
{
    return (*this) = text;
}

TGL::tglWindow &TGL::tglWindow::Assign(const TGL::tglWindow &window)
{
    return (*this) = window;
}



TGL::tglWindow &TGL::tglWindow::operator =(const std::string &text)
{
    this->planned.className
  = this->planned.windowName
  = text
  ;

    return *this;
}

TGL::tglWindow &TGL::tglWindow::operator =(const TGL::tglWindow &window)
{
    this->planned    = window.planned;
    this->m_centered = window.m_centered;

    return *this;
}



bool TGL::tglWindow::Show()
{
    if (this->m_handle)
    {
        return ShowWindow(this->m_handle, SW_RESTORE);
    }

    return false;
}

bool TGL::tglWindow::Hide()
{
    if (this->m_handle)
    {
        return ShowWindow(this->m_handle, SW_HIDE);
    }

    return false;
}

bool TGL::tglWindow::Update(HWND insertAfter, UINT flags)
{
    if (SetWindowPos(this->m_handle
                    ,insertAfter
                    ,planned.xPosition - this->m_centered * planned.width  / 2
                    ,planned.yPosition - this->m_centered * planned.height / 2
                    ,planned.width
                    ,planned.height
                    ,flags
                    ))
    {
        this->m_current.xPosition = this->m_planned.xPosition;
        this->m_current.yPosition = this->m_planned.yPosition;

        this->m_current.width     = this->m_planned.width;
        this->m_current.height    = this->m_planned.height;

        return true;
    }

    return false;
}

bool TGL::tglWindow::FillScreen()
{
    this->planned.xPosition = 0;
    this->planned.yPosition = 0;

    this->planned.width  = TGL::xScreen();
    this->planned.height = TGL::yScreen();

    return this->Update();
}

HWND TGL::tglWindow::Create()
{
    return this->Create(this->planned);
}

HWND TGL::tglWindow::Create(const TGL::WindowAttributes &attributes)
{
    static WNDCLASS
        wClass;



    ZeroMemory(&wClass, sizeof(wClass));
    wClass.hbrBackground = (HBRUSH)GetStockObject(attributes.background);
    wClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wClass.lpfnWndProc   = attributes.callback;
    wClass.lpszClassName = attributes.className.c_str();

    if (!RegisterClass(&wClass))
    {
        TGL::Message("RegisterClass(WNDCLASS)", "Window class could not be registered " + attributes.className + '.');

        return NULL;
    }

    if (!(this->m_handle = CreateWindow(attributes. className.c_str()
                                       ,attributes.windowName.c_str()
                                       ,attributes.style
                                       ,attributes.xPosition - this->m_centered * attributes.width  / 2
                                       ,attributes.yPosition - this->m_centered * attributes.height / 2
                                       ,attributes.width
                                       ,attributes.height
                                       ,attributes.parent
                                       ,attributes.menu
                                       ,attributes.instance
                                       ,attributes.lpParam
                                       )))
    {
        TGL::Message("CreateWindow(WindowAttributes)", "Window could not be created " + attributes.windowName + '.');

        return NULL;
    }

    this->m_current = attributes;



    return this->m_handle;
}

void TGL::tglWindow::DisplayValues() const
{
    std::cout << this->GetValues() + "\n\n\n\n";
}

void TGL::tglWindow::Clear()
{
    if (this->m_handle)
    {
        DestroyWindow(this->m_handle);
    }
}

void TGL::tglWindow::Reset()
{
    this->Clear();
    this->Initialize();

    this->m_current.Initialize();
    this->m_planned.Initialize();
}

void TGL::tglWindow::Center()
{
    if (!this->m_centered)
    {
        this->m_centered = true;

        this->Update();
    }
}

void TGL::tglWindow::Decenter()
{
    if (this->m_centered)
    {
        this->m_centered = false;

        this->Update();
    }
}

std::string TGL::tglWindow::GetValues() const
{
    return this->TGL::tglObject::GetValues()
           + "\nHas Handle: " + (this->m_handle? ("Yes; " + TGL::StringHex(largeint_t(this->m_handle))) : "No")
           + "\nCurrent " + this->current.GetValues()
           + "\n\nPlanned " + this->planned.GetValues()
           ;
}



const HWND TGL::tglWindow::handle() const
{
    return this->m_handle;
}

bool TGL::tglWindow::centered() const
{
    return this->m_centered;
}



void TGL::tglWindow::Initialize()
{
    this->m_centered = false;
    this->m_handle = NULL;
}



#ifndef CUSTOM_CALLBACK
LRESULT CALLBACK TGL::tglCallback(HWND handle
                                 ,UINT message
                                 ,WPARAM wParam
                                 ,LPARAM lParam)
{
    switch (message)
    {
        case WM_CREATE:
        {
            return 0;
        }
        case WM_PAINT:
        {
            TGL::callbackDC =
            BeginPaint(handle, &TGL::callbackPS);
            EndPaint(handle, &TGL::callbackPS);

            return 0;
        }
        case WM_DESTROY:
        {
            return 0;
        }
    }
    return DefWindowProc(handle, message, wParam, lParam);
}
#endif // CUSTOM_CALLBACK



#endif // TGL_WINDOW_H
