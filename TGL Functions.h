#ifndef TGL_FUNCTIONS_H
    #define TGL_FUNCTIONS_H



int8_t TGL::Sign(largeint_t value)
{
    return (value < 0? -1 : 1);
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



#endif // TGL_FUNCTIONS_H



































