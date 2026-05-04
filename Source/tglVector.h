#ifndef TGL_VECTOR_H
    #define TGL_VECTOR_H



class TGL::tglVector : public TGL::tglObject
{
public:

    tglVector() : dimensions{_dimensions} {}
    tglVector(const std::vector<vType> &vector) : tglVector() { _dimensions = vector; }
    tglVector(const std::initializer_list<vType> &vector) : tglVector() { _dimensions = std::vector<vType>(vector); }



    void
        Resize(uint32_t size, vType value = 0),
        DisplayValues() const;

    largeuint_t
        Size() const;
    
    std::string
        GetValues() const;

    operator bool() const;
    bool operator !() const;



    TGL::tglVector
        &operator  =(const std::initializer_list<vType> &ilVector),
        &operator -=(const std::initializer_list<vType> &ilVector),
        &operator +=(const std::initializer_list<vType> &ilVector),
        &operator *=(const std::initializer_list<vType> &ilVector),
        &operator /=(const std::initializer_list<vType> &ilVector),
        &operator ^=(const std::initializer_list<vType> &ilVector),
        &operator  =(const std::vector<vType> &vector),
        &operator -=(const std::vector<vType> &vector),
        &operator +=(const std::vector<vType> &vector),
        &operator *=(const std::vector<vType> &vector),
        &operator /=(const std::vector<vType> &vector),
        &operator ^=(const std::vector<vType> &vector),
        &operator  =(const TGL::tglVector &vector),
        &operator -=(const TGL::tglVector &vector),
        &operator +=(const TGL::tglVector &vector),
        &operator *=(const TGL::tglVector &vector),
        &operator /=(const TGL::tglVector &vector),
        &operator ^=(const TGL::tglVector &vector),
        &operator  =(vType value),
        &operator -=(vType value),
        &operator +=(vType value),
        &operator *=(vType value),
        &operator /=(vType value),
        &operator ^=(vType value);
    
    vType
        &operator [](unsigned index),
        operator [](unsigned index) const;



    std::vector<vType>
        &dimensions;
    
protected:

    std::vector<vType>
        _dimensions;
};



#endif // TGL_VECTOR_H