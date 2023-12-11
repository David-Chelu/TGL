#ifndef IMAGE_ATTRIBUTES_H
    #define IMAGE_ATTRIBUTES_H



struct TGL::ImageAttributes
{
    ImageAttributes();
    ImageAttributes(largeuint_t width,
                    largeuint_t height,
                    uint16_t bitCount);



    TGL::ImageAttributes
        &operator =(const TGL::ImageAttributes &attributes);



    void
        DisplayValues() const;

    std::string
        GetValues() const;

    void
        Initialize();



    largeuint_t
        width,
        height;

    uint16_t
        bitCount;
};



TGL::ImageAttributes::ImageAttributes()
{
    this->Initialize();
}

TGL::ImageAttributes::ImageAttributes(largeuint_t width,
                                      largeuint_t height,
                                      uint16_t bitCount)
                                      :
                                       width(width)
                                      ,height(height)
                                      ,bitCount(bitCount)
{
}



TGL::ImageAttributes &TGL::ImageAttributes::operator =(const TGL::ImageAttributes &attributes)
{
    this->width    = attributes.width;
    this->height   = attributes.height;

    this->bitCount = attributes.bitCount;



    return *this;
}



void TGL::ImageAttributes::DisplayValues() const
{
    std::cout << this->GetValues() + "\n\n\n\n";
}

std::string TGL::ImageAttributes::GetValues() const
{
    return std::string("ImageAttributes:")
                     + "\n\twidth: "    + TGL::String(this->width)
                     + "\n\theight: "   + TGL::String(this->height)
                     + "\n\tbitCount: " + TGL::String(this->bitCount)
                     ;
}

void TGL::ImageAttributes::Initialize()
{
    this->width  = 0;
    this->height = 0;

    this->bitCount = TGL::bitCount;
}



#endif // IMAGE_ATTRIBUTES_H



































