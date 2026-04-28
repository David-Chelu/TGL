#ifndef TGL_PERCENT_H
    #define TGL_PERCENT_H



struct TGL::Percent
{
    Percent(long double value = 0.F);

    TGL::Percent
        &operator =(const TGL::Percent &other);

    long double
        getValue();

private:

    long double
        internalValue;
};



#endif // TGL_PERCENT_H