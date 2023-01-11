#ifndef TGL_H
    #define TGL_H




#if _WIN32_WINNT<0x0500
    #define _WIN32_WINNT 0x0500
#endif // _WIN32_WINNT



#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <windows.h>



namespace TGL
{

    #if 1 // TGL classes

    class tglObject;
    class tglWindow;

    #endif // TGL classes



    #if 1 // enum types

    enum Identity
    {
        TGL_WINDOW
    };

    #endif // enum types



    #if 1 // TGL variables

        #if 1 // miscellaneous variables

        #endif // miscellaneous variables



        #if 1 // tglWindow variables

        HINSTANCE
            creationWindowInstance = (HINSTANCE)GetModuleHandle(0);

        HDC
            windowProcedureDC;

        PAINTSTRUCT
            windowProcedurePS;

        uint32_t
            screenWidth  = GetSystemMetrics(SM_CXSCREEN),
            screenHeight = GetSystemMetrics(SM_CYSCREEN);

        const std::vector <std::pair<uint32_t, std::string>>
            styles =
            {
                 { WS_OVERLAPPED, "WS_OVERLAPPED (WS_TILED)" }
                ,{ WS_POPUP, "WS_POPUP" }
                ,{ WS_CHILD, "WS_CHILD (WS_CHILDWINDOW)" }
                ,{ WS_MINIMIZE, "WS_MINIMIZE (WS_ICONIC)" }
                ,{ WS_VISIBLE, "WS_VISIBLE" }
                ,{ WS_DISABLED, "WS_DISABLED" }
                ,{ WS_CLIPSIBLINGS, "WS_CLIPSIBLINGS" }
                ,{ WS_CLIPCHILDREN, "WS_CLIPCHILDREN" }
                ,{ WS_MAXIMIZE, "WS_MAXIMIZE" }
                ,{ WS_CAPTION, "WS_CAPTION" }
                ,{ WS_BORDER, "WS_BORDER" }
                ,{ WS_DLGFRAME, "WS_DLGFRAME" }
                ,{ WS_VSCROLL, "WS_VSCROLL" }
                ,{ WS_HSCROLL, "WS_HSCROLL" }
                ,{ WS_SYSMENU, "WS_SYSMENU" }
                ,{ WS_THICKFRAME, "WS_THICKFRAME (WS_SIZEBOX)" }
                ,{ WS_MINIMIZEBOX, "WS_MINIMIZEBOX (WS_GROUP)" }
                ,{ WS_MAXIMIZEBOX, "WS_MAXIMIZEBOX (WS_TABSTOP)" }
                ,{ WS_POPUPWINDOW, "WS_POPUPWINDOW" }
                ,{ WS_OVERLAPPEDWINDOW, "WS_OVERLAPPEDWINDOW (WS_TILEDWINDOW)" }
            },

            extendedStyles =
            {
                 { WS_EX_DLGMODALFRAME, "WS_EX_DLGMODALFRAME" }
                ,{ WS_EX_NOPARENTNOTIFY, "WS_EX_NOPARENTNOTIFY" }
                ,{ WS_EX_TOPMOST, "WS_EX_TOPMOST" }
                ,{ WS_EX_ACCEPTFILES, "WS_EX_ACCEPTFILES" }
                ,{ WS_EX_TRANSPARENT, "WS_EX_TRANSPARENT" }
                ,{ WS_EX_MDICHILD, "WS_EX_MDICHILD" }
                ,{ WS_EX_TOOLWINDOW, "WS_EX_TOOLWINDOW" }
                ,{ WS_EX_WINDOWEDGE, "WS_EX_WINDOWEDGE" }
                ,{ WS_EX_CLIENTEDGE, "WS_EX_CLIENTEDGE" }
                ,{ WS_EX_CONTEXTHELP, "WS_EX_CONTEXTHELP" }
                ,{ WS_EX_RIGHT, "WS_EX_RIGHT" }
                ,{ WS_EX_RTLREADING, "WS_EX_RTLREADING" }
                ,{ WS_EX_LEFTSCROLLBAR, "WS_EX_LEFTSCROLLBAR" }
                ,{ WS_EX_CONTROLPARENT, "WS_EX_CONTROLPARENT" }
                ,{ WS_EX_STATICEDGE, "WS_EX_STATICEDGE" }
                ,{ WS_EX_APPWINDOW, "WS_EX_APPWINDOW" }
                ,{ WS_EX_LEFT, "WS_EX_LEFT (WS_EX_LTRREADING / WS_EX_RIGHTSCROLLBAR)" }
                ,{ WS_EX_OVERLAPPEDWINDOW, "WS_EX_OVERLAPPEDWINDOW" }
                ,{ WS_EX_LAYERED, "WS_EX_LAYERED" }
                ,{ WS_EX_NOINHERITLAYOUT, "WS_EX_NOINHERITLAYOUT" }
                ,{ WS_EX_LAYOUTRTL, "WS_EX_LAYOUTRTL" }
                ,{ WS_EX_COMPOSITED, "WS_EX_COMPOSITED" }
                ,{ WS_EX_NOACTIVATE, "WS_EX_NOACTIVATE" }
                #if WINVER >= 0x0602
                ,{ WS_EX_NOREDIRECTIONBITMAP, "WS_EX_NOREDIRECTIONBITMAP" }
                #endif
            };

        #endif // tglWindow variables



        #if 1 // object monitoring variables

        #endif // object monitoring variables

    #endif // TGL variables



    #if 1 // TGL functions

        #if 1 // miscellaneous functions

        const char
            *ClassName(TGL::Identity identity);

        #endif // miscellaneous functions



        #if 1 // tglWindow functions

        LRESULT CALLBACK
            WindowProcedure(HWND windowHandle,
                            UINT windowMessage,
                            WPARAM wordParameter,
                            LPARAM longParameter);

        const char
            *ColorName(uint32_t color);

        std::string
            StyleList(uint32_t style),
            ExtendedStyleList(uint32_t extendedStyle);

        #endif // tglWindow functions



        #if 1 // object monitoring functions

        #endif // object monitoring functions

    #endif // TGL functions

}



#include "tglObject.h"
#include "tglWindow.h"
#include "TGL Functions.h"



#endif // TGL_H



































