#ifndef TGL_H
    #define TGL_H



#if _WIN32_WINNT<0x0500
    #define _WIN32_WINNT 0x0500
#endif // _WIN32_WINNT



#include <windows.h>
#include <iostream>
#include <fstream>
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

#define BLUE  1
#define GREEN 1 << 1
#define RED   1 << 2
#define ALPHA 1 << 3

#define BEGIN 0
#define MIDDLE -2
#define END -1

#define CLASS_ID(object) typeid(object).name()
#define CLASS_NAME(object) TGL::className[CLASS_ID(object)]
#define CLASS_IDENTITY \
std::string("\tTGL::")\
          + CLASS_NAME(*this)
#define OBJECT_ID "ID: " + TGL::String(this->m_ID)

#define LoopStart \
while (1)\
{\
static MSG message;\
if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))\
{\
    TranslateMessage(&message);\
    DispatchMessage (&message);\
}\
else

#define LoopEnd }

#define StartTGL() { TGL::Initialize()
#define EndTGL() } TGL::Clear()


#define Templated template<typename DataType>



namespace TGL
{
    // TGL classes

    class tglObject;
    class tglWindow;
    class tglVideo;
    class tglBitmap;
    class tglImageGenerator;



    struct WindowAttributes;
    struct ImageAttributes;
    struct HeaderTBM;



    uint16_t
        ALLOCATION = 16;

    std::vector<TGL::tglObject*>
        oArray;

    std::vector<bool>
        oActive;

    // TGL classes



    // TGL enums

    enum class VideoMode
    {
        Bits
       ,Bitmap
       ,Generator
    };

    enum class ImageCompression
    {
        None
       ,Count
    };

    // TGL enums



    // TGL variables

    extern std::map<const std::string, const std::string>
        className;

    std::map<const TGL::VideoMode, const std::string>
        modeName =
    {
        { TGL::VideoMode::Bits,      "Bits"      }
       ,{ TGL::VideoMode::Bitmap,    "Bitmap"    }
       ,{ TGL::VideoMode::Generator, "Generator" }
    };

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

    constexpr uint16_t
        bitCount = 32;

    constexpr uint8_t
        bitmap = 0,
        animation = 1;

    // TGL variables



    // TGL functions

    inline int8_t
        Sign(largeint_t value);

    inline char
        DigitUppercase(int8_t digit),
        DigitLowercase(int8_t digit);

    inline uint16_t
        Digits(largeint_t value);

    std::string
        String(largeint_t value)
       ,String(double value, uint8_t precision)
       ,StringBinary(largeuint_t value)
       ,StringHex(largeuint_t value)
       ,BitmapInfoValues(const BITMAPINFO &info)
       ,Colors(COLORREF pixel)
       ;

    inline COLORREF
        Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
       ,Red(COLORREF color)
       ,Green(COLORREF color)
       ,Blue(COLORREF color)
       ,Alpha(COLORREF color)
       ;

    Templated inline DataType Abs(DataType value);
    Templated inline DataType Min(DataType a, DataType b);
    Templated inline DataType Max(DataType a, DataType b);
    Templated inline DataType Mul(DataType a, DataType b);
    Templated inline DataType Div(DataType a, DataType b);
    Templated inline DataType Mod(DataType a, DataType b);
    Templated inline DataType Pow(DataType a, DataType b);

    inline int
        xScreen(),
        yScreen(),
        Message(const std::string &title, const std::string &description);

    Templated void *Copy(void *destination, void   *source, largeuint_t count);
    Templated void *Set (void *destination, DataType value, largeuint_t count);

    void
        StepCopyX(void *destination
                 ,void *source
                 ,largeuint_t size
                 ,largeuint_t repeat
                 ,largeint_t  skipDestination = 1
                 ,largeint_t  skipSource = 1
                 ,largeint_t  variationDestination = 0
                 ,largeint_t  variationSource = 0
                 )
       ,StepSetX(void *destination
                ,int value
                ,largeuint_t size
                ,largeuint_t repeat
                ,largeint_t  skip = 1
                ,largeint_t  variation = 0
                )
       ;

    Templated void StepCopy(void *destination
                           ,void *source
                           ,largeuint_t repeat
                           ,largeint_t  skipDestination = 1
                           ,largeint_t  skipSource = 1
                           ,largeint_t  variationDestination = 0
                           ,largeint_t  variationSource = 0
                           );
    Templated void StepSet(void *destination
                          ,int value
                          ,largeuint_t repeat
                          ,largeint_t  skip = 1
                          ,largeint_t  variation = 0
                          );

    // TGL functions
}



#include "tglObject.h"
#include "tglWindow.h"
#include "tglBitmap.h"
#include "tglImageGenerator.h"
#include "tglVideo.h"
#include "TGL Functions.h"



namespace TGL
{
    std::map<const std::string, const std::string>
        className =
    {
        { typeid(TGL::tglObject        ).name(), "tglObject"         }
       ,{ typeid(TGL::tglWindow        ).name(), "tglWindow"         }
       ,{ typeid(TGL::tglVideo         ).name(), "tglVideo"          }
       ,{ typeid(TGL::tglBitmap        ).name(), "tglBitmap"         }
       ,{ typeid(TGL::tglImageGenerator).name(), "tglImageGenerator" }
    };
}



#endif // TGL_H



































