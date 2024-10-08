#ifndef WINDOW_ATTRIBUTES_CPP
    #define WINDOW_ATTRIBUTES_CPP



TGL::WindowAttributes::WindowAttributes()
{
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
                                        className (className )
                                       ,windowName(windowName)
                                       ,style     (style     )
                                       ,xPosition (xPosition )
                                       ,yPosition (yPosition )
                                       ,width     (width     )
                                       ,height    (height    )
                                       ,parent    (parent    )
                                       ,menu      (menu      )
                                       ,instance  (instance  )
                                       ,lpParam   (lpParam   )
                                       ,callback  (callback  )
                                       ,background(background)
{
}



TGL::WindowAttributes &TGL::WindowAttributes::operator =(const TGL::WindowAttributes &attributes)
{
    this->className  = attributes.className;
    this->windowName = attributes.windowName;

    this->style = attributes.style;

    this->xPosition = attributes.xPosition;
    this->yPosition = attributes.yPosition;

    this->width  = attributes.width;
    this->height = attributes.height;

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
         + "\n\tPosition: (" + TGL::String(this->xPosition) + ", " + TGL::String(this->yPosition) + ')'
         + "\n\tSize: (" + TGL::String(this->width) + ", " + TGL::String(this->height) + ')'
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

    this->xPosition =
    this->yPosition = 0;

    this->width  = TGL::xScreen();
    this->height = TGL::yScreen();

    this->parent = NULL;

    this->menu = NULL;

    this->instance = TGL::creationInstance;

    this->lpParam = NULL;

    this->callback = TGL::tglCallback;

    this->background = BLACK_BRUSH;
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
        width  = workRect.right  - workRect.left;
        height = workRect.bottom - workRect.top;
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
        xPosition = workRect.left;
        yPosition = workRect.top;
    }

    return result;
}

bool TGL::WindowAttributes::SetToWorkRect()
{
    return ResizeToWorkRect() && SnapToWorkRect();
}



#endif // WINDOW_ATTRIBUTES_CPP



































