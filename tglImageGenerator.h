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

    tglImageGenerator() : image{image_} {}



    void
        CreateBuffer(largeuint_t xBuffer, largeuint_t yBuffer)
       ,DrawPattern()
       ,GetRectangle(largeint_t &x1
                    ,largeint_t &y1
                    ,largeint_t &x2
                    ,largeint_t &y2
                    ,const TGL::tglBitmap &bitmap
                    ,bool relative = true
                    ) const
       ,GetRectangle(const TGL::tglBitmap &destination
                    ,largeint_t &x1
                    ,largeint_t &y1
                    ,largeint_t &x2
                    ,largeint_t &y2
                    ,const TGL::tglBitmap &bitmap
                    ,bool relative = true
                    ) const
       ,Wipe()
       ;

    bool
        Combine(TGL::tglBitmap &destination)
       ,Combine()
       ,CombineByPasting(TGL::tglBitmap &destination, bool alpha = true)
       ,CombineByPasting(bool alpha = true)
       ;

    const TGL::tglBitmap
        &GetBitmap() const; // TODO: remove this

    TGL::tglImageGenerator
        &Add(TGL::tglBitmap *bitmap, uint16_t count = 1)
       ,&Add(TGL::tglBitmap &bitmap)
       ,&Add(const std::vector<TGL::tglBitmap*> &bitmapList)
       ,&Remove(TGL::tglBitmap *bitmap)
       ,&Remove(TGL::tglBitmap &bitmap)
       ,&Remove(size_t index)
       ;

    TGL::tglImageGenerator
        &operator +=(TGL::tglBitmap *bitmap)
       ,&operator +=(TGL::tglBitmap &bitmap)
       ,&operator +=(const std::vector<TGL::tglBitmap*> &bitmapList)
       ,&operator -=(TGL::tglBitmap *bitmap)
       ,&operator -=(TGL::tglBitmap &bitmap)
       ,&operator -=(size_t index)
       ;



    static void
        DrawPattern(TGL::tglBitmap &bitmap)
       ,DrawPattern(TGL::tglBitmap *bitmap)
       ;



    TGL::tglBitmap
        &image;

private:

    TGL::tglBitmap
        image_;

    std::vector<Layer>
        layers_;

    // TODO: add a variable for universal frame count. This will help determine an animation's frame selection for combining (done via modulo). Each animation will also have a speed, so these 2 combined will determine an individual animation layer's speed.

};



#endif // TGL_IMAGE_GENERATOR_H
