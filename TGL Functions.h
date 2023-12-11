#ifndef TGL_FUNCTIONS_H
    #define TGL_FUNCTIONS_H



int8_t TGL::Sign(largeint_t value)
{
    return (value < 0? -1 : 1);
}

char TGL::DigitUppercase(int8_t digit)
{
    return (digit < 10? 48 + digit : 55 + digit);
}

char TGL::DigitLowercase(int8_t digit)
{
    return (digit < 10? 48 + digit : 87 + digit);
}

uint16_t TGL::Digits(largeint_t value)
{
    static uint16_t
        digits;

    digits = 0;

    while (value)
    {
        value /= 10;

        ++digits;
    }

    return digits;
}

std::string TGL::String(largeint_t value)
{
    std::string
        result;

    if (!value)
    {
        result = '0';
    }
    else
    {
        int8_t
            sign = TGL::Sign(value);

        value = TGL::Abs(value);

        result.reserve(sizeof(value) * 3 + 1);



        while (value)
        {
            result.push_back(char(48 + value % 10));

            value /= 10;
        }

        if (NEGATIVE == sign)
        {
            result.push_back('-');
        }

        std::reverse(result.begin(), result.end());
    }

    return result;
}

std::string TGL::String(double value, uint8_t precision)
{
    int8_t
        sign;

    int64_t
        whole = value;

    sign = TGL::Sign(whole);
    value = TGL::Abs(value -= whole);

    for (; precision; --precision)
    {
        value *= 10;
    }

    return TGL::String(int64_t(whole)) + '.' + TGL::String(int64_t(value));
}

std::string TGL::StringBinary(largeuint_t value)
{
    std::string
        result;

    result.reserve(sizeof(value) * 8);

    do
    {
        result.push_back(char(48 + value % 2));

        value >>= 1;
    }
    while (value);

    std::reverse(result.begin(), result.end());

    return result;
}

std::string TGL::StringHex(largeuint_t value)
{
    std::string
        result;

    result.reserve(sizeof(value) * 2 + 2);

    do
    {
        result.push_back(TGL::DigitUppercase(value & 15));

        value >>= 4;
    }
    while (value);

    result += "x0";

    std::reverse(result.begin(), result.end());

    return result;
}

std::string TGL::BitmapInfoValues(const BITMAPINFO &info)
{
    return std::string("Bitmap Info:")
                     + "\n\tbiBitCount: " + TGL::String(info.bmiHeader.biBitCount)
                     + "\n\tbiPlanes: "   + TGL::String(info.bmiHeader.biPlanes)
                     + "\n\tbiSize: "     + TGL::String(info.bmiHeader.biSize)
                     + "\n\tbiWidth: "    + TGL::String(info.bmiHeader.biWidth)
                     + "\n\tbiHeight: "   + TGL::String(info.bmiHeader.biHeight);
}

std::string TGL::Colors(COLORREF pixel)
{
    return '(' + TGL::String(TGL::Red  (pixel))
        + ", " + TGL::String(TGL::Green(pixel))
        + ", " + TGL::String(TGL::Blue (pixel))
        + ", " + TGL::String(TGL::Alpha(pixel))
        +  ')';
}

COLORREF TGL::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    return uint32_t(blue) | uint32_t(green) << 8 | uint32_t(red) << 16 | uint32_t(alpha) << 24;
}

COLORREF TGL::Red(COLORREF color)
{
    return ((uint32_t(0xFF) << 16) & color) >> 16;
}

COLORREF TGL::Green(COLORREF color)
{
    return ((uint32_t(0xFF) << 8) & color) >> 8;
}

COLORREF TGL::Blue(COLORREF color)
{
    return uint32_t(0xFF) & color;
}

COLORREF TGL::Alpha(COLORREF color)
{
    return ((uint32_t(0xFF) << 24) & color) >> 24;
}

Templated DataType TGL::Abs(DataType value)
{
    return (value < 0? -value : value);
}

Templated DataType TGL::Min(DataType a, DataType b)
{
    return (a < b? a : b);
}

Templated DataType TGL::Max(DataType a, DataType b)
{
    return (a > b? a : b);
}

Templated DataType TGL::Mul(DataType a, DataType b)
{
    return a * b;
}

Templated DataType TGL::Div(DataType a, DataType b)
{
    return a / b;
}

Templated DataType TGL::Mod(DataType a, DataType b)
{
    return a - b * largeint_t(a / b);
}

Templated DataType TGL::Pow(DataType a, DataType b)
{
    return pow(a, b);
}

int TGL::xScreen()
{
    return GetSystemMetrics(SM_CXSCREEN);
}

int TGL::yScreen()
{
    return GetSystemMetrics(SM_CYSCREEN);
}

int TGL::Message(const std::string &title, const std::string &description)
{
    return MessageBox(NULL, description.c_str(), title.c_str(), MB_OK);
}



namespace TGL
{
    void
        Initialize(),
        Clear();
}

void TGL::Initialize()
{
}

void TGL::Clear()
{
    for (uint64_t index = 0; index < TGL::oArray.size(); ++index)
    {
        if (TGL::oActive[index])
        {
            delete TGL::oArray[index];
        }
    }

    TGL::oActive.clear();
    TGL::oArray.clear();
}



#endif // TGL_FUNCTIONS_H



































