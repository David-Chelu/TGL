#ifndef TGL_OBJECT_H
    #define TGL_OBJECT_H



class TGL::tglObject
{
public:

    tglObject();
    virtual ~tglObject();



    virtual void
        DisplayValues() const,
        Initialize() = 0;



    virtual TGL::Identity
        identity() const = 0;

private:
};



TGL::tglObject::tglObject()
{
}

TGL::tglObject::~tglObject()
{
}



void TGL::tglObject::DisplayValues() const
{
    std::cout << "    TGL::" << TGL::ClassName(this->identity()) << ':';
}



#include "tglObject Functions.h"



#endif // TGL_OBJECT_H



































