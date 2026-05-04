#ifndef TGL_VIDEO_H
    #define TGL_VIDEO_H



union source_t
{
    struct
    {
        largeint_t xPosition, yPosition;
        largeuint_t width, height;
        const void *image;
        uint16_t bitCount;
        bool centered;
    };

    const TGL::tglBitmap
        *bitmap;

    const TGL::tglImageGenerator
        *generator;
};

struct destination_t
{
    largeuint_t
        width,
        height;
};



class TGL::tglVideo : public tglObject
{
public:

    tglVideo();
    tglVideo(HWND newHandle);
    tglVideo(const TGL::tglWindow &window);
    ~tglVideo();



    inline TGL::tglVideo
        &Assign(HWND newHandle)
       ,&Assign(const TGL::tglWindow &window)
       ,&Assign(const void *image)
       ,&Assign(const TGL::tglBitmap *bitmap)
       ,&Assign(const TGL::tglBitmap &bitmap)
       ,&Assign(const TGL::tglImageGenerator *generator)
       ,&Assign(const TGL::tglImageGenerator &generator)
       ;



    inline TGL::tglVideo
        &operator =(HWND newHandle)
       ,&operator =(const TGL::tglWindow &window)
       ,&operator =(const void *image)
       ,&operator =(const TGL::tglBitmap *bitmap)
       ,&operator =(const TGL::tglBitmap &bitmap)
       ,&operator =(const TGL::tglImageGenerator *generator)
       ,&operator =(const TGL::tglImageGenerator &generator)
       ;



    inline void
        DisplayValues() const;

    void
        Clear(),
        Reset(),
        SetMode(const TGL::VideoMode newMode),
        SetBitsModeXPosition(largeint_t xPosition),
        SetBitsModeYPosition(largeint_t yPosition),
        SetBitsModeWidth(largeuint_t width),
        SetBitsModeHeight(largeuint_t height),
        SetBitsModeCentered(bool centered),
        SetBitsModeBitCount(uint16_t bitCount),
        SetBitsModeValues(largeint_t xPosition,
                          largeint_t yPosition,
                          largeuint_t width,
                          largeuint_t height,
                          bool centered = false,
                          uint16_t bitCount = TGL::bitCount);

    inline std::string
        GetValues() const;

    inline bool
        Lock(),
        Unlock();

    bool
        Display(const void *image,
                largeint_t xPosition,
                largeint_t yPosition,
                largeint_t width,
                largeint_t height,
                bool centered = false,
                uint16_t bitCount = TGL::bitCount)
       ,Display(const TGL::tglBitmap *bitmap)
       ,Display(const TGL::tglBitmap &bitmap)
       ,Display(const TGL::tglImageGenerator *generator)
       ,Display(const TGL::tglImageGenerator &generator)
       ,Display()
       ;

    inline HDC
        RequestHDC();



    const HWND
        handle() const;

    const HDC
        hdc() const;

    bool
        locked() const;

    const BITMAPINFO
        &infoExtern() const,
        &info() const;

    TGL::VideoMode
        mode() const;

    const source_t
        &source;

    const destination_t
        &destination;

private:

    void
        Initialize();

    bool
        DisplayBits()
       ,DisplayBitmap()
       ,DisplayGenerator()
       ;

    inline std::string
        GetSourceValues() const;



    HWND
        m_handle;

    HDC
        m_hdc;

    bool
        m_locked;
        // add m_absolute, m_relative, or m_coordinates (mode to switch between relative and absolute). This will determine whether the coordinates are bound to the window, or the monitor (the world, the camera). If relative, it works standard. If absolute, you can move around the window while the camera and character stay in the same place.

    BITMAPINFO
        m_infoExtern,
        m_info;

    TGL::VideoMode
        m_mode;

    source_t
        m_source;

    destination_t
        m_destination;
};



#endif // TGL_VIDEO_H



































