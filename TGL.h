#ifndef TGL_H
    #define TGL_H



#if _WIN32_WINNT<0x0500
    #define _WIN32_WINNT 0x0500
#endif // _WIN32_WINNT



#include <windows.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <typeinfo>



typedef int64_t largeint_t;
typedef uint64_t largeuint_t;

#define NEGATIVE -1
#define POSITIVE  1

#define Templated template<typename DataType>



namespace TGL
{
    // TGL classes

    class tglObject;



    uint16_t
        ALLOCATION = 16;

    std::vector<TGL::tglObject*>
        oArray;

    std::vector<bool>
        oActive;

    // TGL classes



    // TGL variables

    extern std::map<const std::string, const std::string>
        className;

    HINSTANCE
        creationInstance = (HINSTANCE)GetModuleHandle(0);

    HDC
        callbackDC;

    PAINTSTRUCT
        callbackPS;

    LRESULT CALLBACK
        tglCallback(HWND handle
                   ,UINT message
                   ,WPARAM wParam
                   ,LPARAM lParam);

    // TGL variables



    // TGL functions

    inline int8_t
        Sign(largeint_t value);

    inline uint16_t
        Digits(largeint_t value);

    std::string
        String(largeint_t value),
        String(double value, uint8_t precision);

    Templated inline DataType Abs(DataType value);
    Templated inline DataType Min(DataType a, DataType b);
    Templated inline DataType Max(DataType a, DataType b);
    Templated inline DataType Mul(DataType a, DataType b);
    Templated inline DataType Div(DataType a, DataType b);
    Templated inline DataType Mod(DataType a, DataType b);
    Templated inline DataType Pow(DataType a, DataType b);

    // TGL functions
}



#include "tglObject.h"
#include "TGL Functions.h"



namespace TGL
{
    std::map<const std::string, const std::string>
        className =
    {
        { typeid(TGL::tglObject).name(), "tglObject" }
    };
}



#endif // TGL_H



































