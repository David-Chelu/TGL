#ifndef TGL_WINDOW_CPP
    #define TGL_WINDOW_CPP



#include "WindowAttributes.cpp"



TGL::tglWindow::tglWindow() : current(m_current), planned(m_planned), centered(m_centered)
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

TGL::tglWindow::operator bool() const
{
    return !!this->m_handle;
}

bool TGL::tglWindow::operator !() const
{
    return !this->m_handle;
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
                    ,this->m_centered? (TGL::xScreen() - planned.width)  / 2 : planned.xPosition
                    ,this->m_centered? (TGL::yScreen() - planned.height) / 2 : planned.yPosition
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

bool TGL::tglWindow::Center()
{
    if (!this->m_centered)
    {
        this->m_centered = true;

        this->Update();
    }

    return this->m_centered;
}

bool TGL::tglWindow::Decenter()
{
    if (this->m_centered)
    {
        this->m_centered = false;

        this->Update();
    }

    return !this->m_centered;
}

bool TGL::tglWindow::ResizeToWorkRect()
{
    return planned.ResizeToWorkRect();
}

bool TGL::tglWindow::SnapToWorkRect()
{
    return planned.SnapToWorkRect();
}

bool TGL::tglWindow::SetToWorkRect()
{
    return ResizeToWorkRect() && SnapToWorkRect();
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
                                       ,this->m_centered? (TGL::xScreen() - attributes.width)  / 2 : attributes.xPosition
                                       ,this->m_centered? (TGL::yScreen() - attributes.height) / 2 : attributes.yPosition
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

HWND TGL::tglWindow::RequestHWND()
{
    return m_handle;
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

largeuint_t TGL::tglWindow::xClient() const
{
    GetClientRect(m_handle, (LPRECT)&m_clientRect);

    return m_clientRect.right - m_clientRect.left;
}

largeuint_t TGL::tglWindow::yClient() const
{
    GetClientRect(m_handle, (LPRECT)&m_clientRect);

    return m_clientRect.bottom - m_clientRect.top;
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



#endif // TGL_WINDOW_CPP
