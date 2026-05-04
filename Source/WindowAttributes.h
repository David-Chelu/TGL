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

    bool
        ResizeToWorkRect(),
        SnapToWorkRect(),
        SetToWorkRect();



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

    static RECT
        workRect;
};



#endif // WINDOW_ATTRIBUTES_H



































