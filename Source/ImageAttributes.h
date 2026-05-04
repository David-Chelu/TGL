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



#endif // IMAGE_ATTRIBUTES_H



































