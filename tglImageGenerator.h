#ifndef TGL_IMAGE_GENERATOR_H
    #define TGL_IMAGE_GENERATOR_H



struct Layer
{
    union
    {
        TGL::tglBitmap
            *bitmap;

        // TODO: add a pointer to tglAnimation when implemented
    };

    uint8_t
        type : 1;
};



class TGL::tglImageGenerator : public TGL::tglObject
{
public:

    void
        CreateBuffer(largeuint_t xBuffer, largeuint_t yBuffer)
       ,DrawPattern()
       ,GetRectangle(largeint_t &x1
                    ,largeint_t &y1
                    ,largeint_t &x2
                    ,largeint_t &y2
                    ,const TGL::tglBitmap &bitmap
                    ) const
       ,Wipe()
       ;

    bool
        Combine();

    const TGL::tglBitmap
        &GetBitmap() const;

    TGL::tglImageGenerator
        &Add(TGL::tglBitmap *bitmap)
       ,&Add(TGL::tglBitmap &bitmap)
       ,&Remove(TGL::tglBitmap *bitmap)
       ,&Remove(TGL::tglBitmap &bitmap)
       ,&Remove(size_t index)
       ;

    TGL::tglImageGenerator
        &operator +=(TGL::tglBitmap *bitmap)
       ,&operator +=(TGL::tglBitmap &bitmap)
       ,&operator -=(TGL::tglBitmap *bitmap)
       ,&operator -=(TGL::tglBitmap &bitmap)
       ,&operator -=(size_t index)
       ;



    static void
        DrawPattern(TGL::tglBitmap &bitmap)
       ,DrawPattern(TGL::tglBitmap *bitmap)
       ;

private:

    TGL::tglBitmap
        image_;

    std::vector<Layer>
        layers_;

};



#endif // TGL_IMAGE_GENERATOR_H
