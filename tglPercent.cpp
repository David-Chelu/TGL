#ifndef TGL_PERCENT_CPP
    #define TGL_PERCENT_CPP



TGL::Percent::Percent(long double value) : internalValue{value}
{
}

TGL::Percent &TGL::Percent::operator =(const TGL::Percent &other)
{
    internalValue = other.internalValue;
    
    return *this;
}

long double TGL::Percent::getValue()
{
    return internalValue / 100.F;
}

TGL::Percent operator ""_pc(long double value)
{
    return TGL::Percent(value);
}

TGL::Percent operator ""_pc(largeuint_t value)
{
    return TGL::Percent(value);
}



#endif // TGL_PERCENT_CPP