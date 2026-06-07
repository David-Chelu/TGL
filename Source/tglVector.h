#ifndef TGL_VECTOR_H
    #define TGL_VECTOR_H



class TGL::tglVector : public TGL::tglObject
{
public:

    tglVector(size_t size = size_t(-1));
    tglVector(const std::vector<vType> &vector);
    tglVector(const std::initializer_list<vType> &ilVector);



    void
        Resize(uint32_t size = 0, vType value = 0),
        DisplayValues() const,
        LockSize(size_t size = 0),
        UnlockSize();

    largeuint_t
        Size() const;
    
    std::string
        GetValues() const;

    const std::vector<vType>
        &Dimensions() const;

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
        operator [](unsigned index) const,
        &operator [](TGL::Dimensions dimension),
        operator [](TGL::Dimensions dimension) const;


    
protected:

    std::vector<vType>
        _dimensions;

    bool
        _locked;
};



#endif // TGL_VECTOR_H