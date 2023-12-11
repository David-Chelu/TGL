#ifndef WINDOW_ATTRIBUTES_H
    #define WINDOW_ATTRIBUTES_H



struct TGL::WindowAttributes
{
    WindowAttributes();
    WindowAttributes(const std::string &className
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
                    ,COLORREF background
                    );



    TGL::WindowAttributes
        &operator =(const TGL::WindowAttributes &attributes);



    void
        DisplayValues() const;

    std::string
        GetValues() const;

    void
        Initialize();



    std::string
        className,
        windowName;

    DWORD
        style;

//    TGL::tglVector2D
//        position,
//        size;

    largeint_t
        xPosition,
        yPosition;

    largeuint_t
        width,
        height;

    HWND
        parent;

    HMENU
        menu;

    HINSTANCE
        instance;

    LPVOID
        lpParam;

    WNDPROC
        callback;

    COLORREF
        background;
};



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



#endif // WINDOW_ATTRIBUTES_H



































