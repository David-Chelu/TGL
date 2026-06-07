#ifndef WINDOW_ATTRIBUTES_CPP
    #define WINDOW_ATTRIBUTES_CPP



TGL::WindowAttributes::WindowAttributes()
{
    LockVectors();
    this->Initialize();
}

TGL::WindowAttributes::WindowAttributes(const std::string &className
                                       ,const std::string &windowName
                                       ,DWORD style
                                       ,largeint_t xPosition
                                       ,largeint_t yPosition
                                       ,largeuint_t width
                                       ,largeuint_t height
                                       ,HWND parent
                                       ,HMENU menu
                                       ,HINSTANCE instance
                                       ,const LPVOID lpParam
                                       ,WNDPROC callback
                                       ,COLORREF background)
                                       :
                                        className  (className )
                                       ,windowName (windowName)
                                       ,style      (style     )
                                       ,parent     (parent    )
                                       ,menu       (menu      )
                                       ,instance   (instance  )
                                       ,lpParam    (lpParam   )
                                       ,callback   (callback  )
                                       ,background (background)
{
    LockVectors();

    position[0] = xPosition;
    position[1] = yPosition;

    size[0] = width;
    size[1] = height;
}



TGL::WindowAttributes &TGL::WindowAttributes::operator =(const TGL::WindowAttributes &attributes)
{
    this->className  = attributes.className;
    this->windowName = attributes.windowName;

    this->style = attributes.style;

    this->position[0] = attributes.position[0];
    this->position[1] = attributes.position[1];

    this->size[0] = attributes.size[0];
    this->size[1] = attributes.size[1];

    this->background = attributes.background;



    return *this;
}



void TGL::WindowAttributes::DisplayValues() const
{
    std::cout << this->GetValues() + "\n\n\n\n";
}

std::string TGL::WindowAttributes::GetValues() const
{
    std::string
        text;

    text = std::string("WindowAttributes:")
         + "\n\tClass Name: " + this->className
         + "\n\tWindowName: " + this->windowName
         + "\n\tStyle: " + TGL::StringHex(this->style)
         + "\n\tPosition: (" + TGL::String(this->position[0]) + ", " + TGL::String(this->position[1]) + ')'
         + "\n\tSize: (" + TGL::String(this->size[0]) + ", " + TGL::String(this->size[1]) + ')'
         + "\n\tHas Parent: " + (this->parent? "Yes" : "No")
         + "\n\tHas Menu: " + (this->menu? "Yes" : "No")
         + "\n\tHas Instance: " + (this->instance? "Yes" : "No")
         + "\n\tLPParam: " + (this->lpParam? "Not NULL" : "NULL")
         + "\n\tHas Callback: " + (this->callback? "Yes; " + TGL::StringHex(largeint_t(this->callback)) : "No")
         + "\n\tBackground: " + TGL::String(this->background)
         ;

    return text;
}

void TGL::WindowAttributes::Initialize()
{
    this-> className = "TGL Window Class";
    this->windowName = "TGL Window";

    this->style = WS_POPUP;

    this->position[0] =
    this->position[1] = 0;

    this->size[0]  = TGL::xScreen();
    this->size[1] = TGL::yScreen();

    this->parent = NULL;

    this->menu = NULL;

    this->instance = TGL::creationInstance;

    this->lpParam = NULL;

    this->callback = TGL::tglCallback;

    this->background = BLACK_BRUSH;
}

void TGL::WindowAttributes::LockVectors()
{
    position.LockSize(2);
    size    .LockSize(2);
}

bool TGL::WindowAttributes::ResizeToWorkRect()
{
    bool
        result;

    result = SystemParametersInfo(SPI_GETWORKAREA,
                                  0,
                                  &workRect,
                                  0);
    {
        size[0]  = workRect.right  - workRect.left;
        size[1] = workRect.bottom - workRect.top;
    }

    return result;
}

bool TGL::WindowAttributes::SnapToWorkRect()
{
    bool
        result;

    result = SystemParametersInfo(SPI_GETWORKAREA,
                                  0,
                                  &workRect,
                                  0);
    {
        position[0] = workRect.left;
        position[1] = workRect.top;
    }

    return result;
}

bool TGL::WindowAttributes::SetToWorkRect()
{
    return ResizeToWorkRect() && SnapToWorkRect();
}



#endif // WINDOW_ATTRIBUTES_CPP



































