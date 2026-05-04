#ifndef TGL_VECTOR_CPP
    #define TGL_VECTOR_CPP



void TGL::tglVector::Resize(uint32_t size, vType value)
{
    _dimensions.resize(size, value);
}

void TGL::tglVector::DisplayValues() const
{
    std::cout << this->GetValues() + "\n\n\n\n";
}

largeuint_t TGL::tglVector::Size() const
{
    return _dimensions.size();
}

std::string TGL::tglVector::GetValues() const
{
    std::string
        dimensionsString = "\n";
    
    if (_dimensions.empty())
    {
        dimensionsString += "\t[]";
    }
    else
    {
        uint32_t
            index;

        ParseRange(index, 0, _dimensions.size(), ++index)
        {
            dimensionsString = dimensionsString +
                "\t[" + TGL::String(index) + "] " + TGL::String(_dimensions[index]) + '\n';
        }
    }

    return this->TGL::tglObject::GetValues()
           + "\nDimensions: " + TGL::String(_dimensions.size())
           + dimensionsString
           ;
}

TGL::tglVector::operator bool() const
{
    return 0 != Size();
}

bool TGL::tglVector::operator !() const
{
    return 0 == Size();
}



TGL::tglVector &TGL::tglVector::operator =(const std::initializer_list<vType> &ilVector)
{
    return *this = std::vector<vType>(ilVector);
}

TGL::tglVector &TGL::tglVector::operator -=(const std::initializer_list<vType> &ilVector)
{
    return *this -= std::vector<vType>(ilVector);
}

TGL::tglVector &TGL::tglVector::operator +=(const std::initializer_list<vType> &ilVector)
{
    return *this += std::vector<vType>(ilVector);
}

TGL::tglVector &TGL::tglVector::operator *=(const std::initializer_list<vType> &ilVector)
{
    return *this *= std::vector<vType>(ilVector);
}

TGL::tglVector &TGL::tglVector::operator /=(const std::initializer_list<vType> &ilVector)
{
    return *this /= std::vector<vType>(ilVector);
}

TGL::tglVector &TGL::tglVector::operator ^=(const std::initializer_list<vType> &ilVector)
{
    return *this ^= std::vector<vType>(ilVector);
}



TGL::tglVector &TGL::tglVector::operator =(const std::vector<vType> &vector)
{
    _dimensions = vector;

    return *this;
}

TGL::tglVector &TGL::tglVector::operator -=(const std::vector<vType> &vector)
{
    unsigned
        index,
        size = TGL::Min(_dimensions.size(), vector.size());
    
    ParseRange(index, 0, size, ++index)
    {
        _dimensions[index] -= vector[index];
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator +=(const std::vector<vType> &vector)
{
    unsigned
        index,
        size = TGL::Min(_dimensions.size(), vector.size());

    
    ParseRange(index, 0, size, ++index)
    {
        _dimensions[index] += vector[index];
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator *=(const std::vector<vType> &vector)
{
    unsigned
        index,
        size = TGL::Min(_dimensions.size(), vector.size());
    
    ParseRange(index, 0, size, ++index)
    {
        _dimensions[index] *= vector[index];
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator /=(const std::vector<vType> &vector)
{
    unsigned
        index,
        size = TGL::Min(_dimensions.size(), vector.size());
    
    ParseRange(index, 0, size, ++index)
    {
        if (0 != vector[index])
        {
            _dimensions[index] /= vector[index];
        }
        else
        {
            _dimensions[index] = 0;
        }
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator ^=(const std::vector<vType> &vector)
{
    unsigned
        index,
        size = TGL::Min(_dimensions.size(), vector.size());
    
    ParseRange(index, 0, size, ++index)
    {
        _dimensions[index] = pow(_dimensions[index], vector[index]);
    }

    return *this;
}



TGL::tglVector &TGL::tglVector::operator =(const TGL::tglVector &vector)
{
    return *this = vector._dimensions;
}

TGL::tglVector &TGL::tglVector::operator -=(const TGL::tglVector &vector)
{
    return *this -= vector._dimensions;
}

TGL::tglVector &TGL::tglVector::operator +=(const TGL::tglVector &vector)
{
    return *this += vector._dimensions;
}

TGL::tglVector &TGL::tglVector::operator *=(const TGL::tglVector &vector)
{
    return *this *= vector._dimensions;
}

TGL::tglVector &TGL::tglVector::operator /=(const TGL::tglVector &vector)
{
    return *this /= vector._dimensions;
}

TGL::tglVector &TGL::tglVector::operator ^=(const TGL::tglVector &vector)
{
    return *this ^= vector._dimensions;
}

TGL::tglVector &TGL::tglVector::operator =(vType value)
{
    unsigned
        index;
    
    ParseRange(index, 0, _dimensions.size(), ++index)
    {
        _dimensions[index] = value;
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator -=(vType value)
{
    unsigned
        index;
    
    ParseRange(index, 0, _dimensions.size(), ++index)
    {
        _dimensions[index] -= value;
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator +=(vType value)
{
    unsigned
        index;
    
    ParseRange(index, 0, _dimensions.size(), ++index)
    {
        _dimensions[index] += value;
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator *=(vType value)
{
    unsigned
        index;
    
    ParseRange(index, 0, _dimensions.size(), ++index)
    {
        _dimensions[index] *= value;
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator /=(vType value)
{
    unsigned
        index;

    if (0 != value)
    {
        ParseRange(index, 0, _dimensions.size(), ++index)
        {
            _dimensions[index] /= value;
        }
    }
    else
    {
        ParseRange(index, 0, _dimensions.size(), ++index)
        {
            _dimensions[index] = 0;
        }
    }

    return *this;
}

TGL::tglVector &TGL::tglVector::operator ^=(vType value)
{
    unsigned
        index;
    
    ParseRange(index, 0, _dimensions.size(), ++index)
    {
        _dimensions[index] = pow(_dimensions[index], value);
    }

    return *this;
}

vType &TGL::tglVector::operator [](unsigned index)
{
    return _dimensions[index];
}

vType TGL::tglVector::operator [](unsigned index) const
{
    return _dimensions[index];
}



#endif // TGL_VECTOR_CPP