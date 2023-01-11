#ifndef TGL_WINDOW_FUNCTIONS_H
    #define TGL_WINDOW_FUNCTIONS_H



#if 1 // tglWindow functions


LRESULT CALLBACK
    TGL::WindowProcedure(HWND windowHandle,
                         UINT windowMessage,
                         WPARAM wordParameter,
                         LPARAM longParameter)
{
    switch (windowMessage)
    {
        case WM_CREATE:
        {
            return 0;
        }
        case WM_PAINT:
        {
            TGL::windowProcedureDC =
            BeginPaint(windowHandle,
                       &TGL::windowProcedurePS);

            EndPaint(windowHandle,
                     &TGL::windowProcedurePS);

            return 0;
        }
        case WM_DESTROY:
        {
            return 0;
        }
    }
    return DefWindowProc(windowHandle, windowMessage, wordParameter, longParameter);
}

const char *TGL::ColorName(uint32_t color)
{
    switch (color)
    {
        case WHITE_BRUSH:  return "WHITE_BRUSH";
        case LTGRAY_BRUSH: return "LTGRAY_BRUSH";
        case GRAY_BRUSH:   return "GRAY_BRUSH";
        case DKGRAY_BRUSH: return "DKGRAY_BRUSH";
        case HOLLOW_BRUSH: return "NULL_BRUSH / HOLLOW_BRUSH"; // equivalent to case NULL_BRUSH:
        case BLACK_PEN:    return "BLACK_PEN";
        case NULL_PEN:     return "NULL_PEN";
        default:           return "Unknown color";
    }
}

std::string TGL::StyleList(uint32_t style)
{
    std::string
        styleString;

    bool
        comma = false;

    for (size_t index = 0; index < TGL::styles.size(); ++index)
    {
        if (style & TGL::styles[index].first)
        {
            styleString += TGL::styles[index].second;
            styleString += ", ";

            comma = true;
        }
    }

    return (comma? styleString.substr(0, styleString.length() - 2) : (styleString.empty()? std::string("No Styles") : styleString));
}

std::string TGL::ExtendedStyleList(uint32_t extendedStyle)
{
    std::string
        styleString;

    bool
        comma = false;

    for (size_t index = 0; index < TGL::extendedStyles.size(); ++index)
    {
        if (extendedStyle & TGL::extendedStyles[index].first)
        {
            styleString += TGL::extendedStyles[index].second;
            styleString += ", ";

            comma = true;
        }
    }

    return (comma? styleString.substr(0, styleString.length() - 2) : (styleString.empty()? std::string("No Styles") : styleString));
}

#endif // tglWindow functions



#endif // TGL_WINDOW_FUNCTIONS_H



































