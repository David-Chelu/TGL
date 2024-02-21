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



TGL::tglVideo::tglVideo() : source(m_source), destination(m_destination)
{
    this->Initialize();
}

TGL::tglVideo::tglVideo(HWND newHandle) : tglVideo()
{
    this->Assign(newHandle);
}

TGL::tglVideo::tglVideo(const TGL::tglWindow &window) : tglVideo()
{
    this->Assign(window);
}

TGL::tglVideo::~tglVideo()
{
    this->Clear();
}



TGL::tglVideo &TGL::tglVideo::Assign(HWND newHandle)
{
    return (*this) = newHandle;
}

TGL::tglVideo &TGL::tglVideo::Assign(const TGL::tglWindow &window)
{
    return (*this) = window;
}

TGL::tglVideo &TGL::tglVideo::Assign(const void *image)
{
    return (*this) = image;
}

TGL::tglVideo &TGL::tglVideo::Assign(const TGL::tglBitmap *bitmap)
{
    return (*this) = bitmap;
}

TGL::tglVideo &TGL::tglVideo::Assign(const TGL::tglBitmap &bitmap)
{
    return (*this) = bitmap;
}

TGL::tglVideo &TGL::tglVideo::Assign(const TGL::tglImageGenerator *generator)
{
    return (*this) = generator;
}

TGL::tglVideo &TGL::tglVideo::Assign(const TGL::tglImageGenerator &generator)
{
    return (*this) = generator;
}



TGL::tglVideo &TGL::tglVideo::operator =(HWND newHandle)
{
    if (!this->m_locked)
    {
        this->m_handle = newHandle;

        if (!this->m_destination.width ||
            !this->m_destination.height)
        {
            static RECT
                window;

            GetWindowRect(this->m_handle, &window);

            this->m_destination.width  = window.right  - window.left;
            this->m_destination.height = window.bottom - window.top;
        }
    }

    return *this;
}

TGL::tglVideo &TGL::tglVideo::operator =(const TGL::tglWindow &window)
{
    this->m_destination.width  = window.current.width;
    this->m_destination.height = window.current.height;

    return (*this) = window.handle();
}

TGL::tglVideo &TGL::tglVideo::operator =(const void *image)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.image = image;
    }

    return *this;
}

TGL::tglVideo &TGL::tglVideo::operator =(const TGL::tglBitmap *bitmap)
{
    if (TGL::VideoMode::Bitmap == this->m_mode)
    {
        this->m_source.bitmap = bitmap;
    }

    return *this;
}

TGL::tglVideo &TGL::tglVideo::operator =(const TGL::tglBitmap &bitmap)
{
    return (*this) = &bitmap;
}

TGL::tglVideo &TGL::tglVideo::operator =(const TGL::tglImageGenerator *generator)
{
    if (TGL::VideoMode::Generator == this->m_mode)
    {
        this->m_source.generator = generator;
    }

    return *this;
}

TGL::tglVideo &TGL::tglVideo::operator =(const TGL::tglImageGenerator &generator)
{
    return (*this) = &generator;
}



void TGL::tglVideo::DisplayValues() const
{
    std::cout << this->GetValues() + "\n\n\n\n";
}

std::string TGL::tglVideo::GetValues() const
{
    return this->TGL::tglObject::GetValues()
           + "\nHas Window: "   + (this->m_handle? ("Yes; " + TGL::StringHex(largeint_t(this->m_handle))) : "No")
           + "\nHas HDC: "      + (this->m_hdc   ? ("Yes; " + TGL::StringHex(largeint_t(this->m_hdc)))    : "No")
           + "\nIs Locked: "    + (this->m_locked?  "Yes"                                                 : "No")
           + "\nMode: "         + TGL::modeName[this->m_mode]
           + '\n'               + TGL::BitmapInfoValues(this->m_info)
           + "\n\nExtern "        + TGL::BitmapInfoValues(this->m_infoExtern)
           + "\n\nDestination: (" + TGL::String(this->m_destination.width) + ", " + TGL::String(this->m_destination.height) + ')'
           + "\n\nSource " + this->GetSourceValues()
           ;
}

void TGL::tglVideo::Clear()
{
    if (this->m_locked)
    {
        if (this->Unlock())
        {
            this->m_handle = NULL;
        }
        else
        {
            TGL::Message("Error: tglVideo::Clear()", "Could not unlock video DC.");
        }
    }

    this->m_mode = TGL::VideoMode::Bits;

    this->m_source.image = NULL;
}

void TGL::tglVideo::Reset()
{
    this->Clear();
    this->Initialize();
}

void TGL::tglVideo::SetMode(const TGL::VideoMode newMode)
{
    if (newMode != this->m_mode)
    {
        switch (this->m_mode = newMode)
        {
            case TGL::VideoMode::Bits:
            {
                this->m_source.height    = 0;
                this->m_source.width     = 0;
                this->m_source.xPosition = 0;
                this->m_source.yPosition = 0;
                this->m_source.image     = NULL;
                this->m_source.bitCount  = 32;

                break;
            }

            case TGL::VideoMode::Bitmap:
            {
                this->m_source.bitmap = NULL;
            }
        }
    }
}

void TGL::tglVideo::SetBitsModeXPosition(largeint_t xPosition)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.xPosition = xPosition;
    }
}

void TGL::tglVideo::SetBitsModeYPosition(largeint_t yPosition)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.yPosition = yPosition;
    }
}

void TGL::tglVideo::SetBitsModeWidth(largeuint_t width)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.width = width;
    }
}

void TGL::tglVideo::SetBitsModeHeight(largeuint_t height)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.height = height;
    }
}

void TGL::tglVideo::SetBitsModeCentered(bool centered)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.centered = centered;
    }
}

void TGL::tglVideo::SetBitsModeBitCount(uint16_t bitCount)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.bitCount = bitCount;
    }
}

void TGL::tglVideo::SetBitsModeValues(largeint_t xPosition,
                                      largeint_t yPosition,
                                      largeuint_t width,
                                      largeuint_t height,
                                      bool centered,
                                      uint16_t bitCount)
{
    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.height    = height;
        this->m_source.width     = width;
        this->m_source.xPosition = xPosition;
        this->m_source.yPosition = yPosition;
        this->m_source.centered  = centered;
        this->m_source.bitCount  = bitCount;
    }
}

bool TGL::tglVideo::Lock()
{
    if (!this->m_locked && !this->m_hdc && (this->m_hdc = GetDC(this->m_handle)))
    {
        return (this->m_locked = true);
    }

    return (this->m_locked = false);
}

bool TGL::tglVideo::Unlock()
{
    if (this->m_locked && this->m_hdc && ReleaseDC(this->m_handle, this->m_hdc))
    {
        this->m_hdc = NULL;

        return (this->m_locked = false);
    }

    return (this->m_locked = true);
}

bool TGL::tglVideo::Display(const void *image,
                            largeint_t xPosition,
                            largeint_t yPosition,
                            largeint_t width,
                            largeint_t height,
                            bool centered,
                            uint16_t bitCount)
{
    this->m_infoExtern.bmiHeader.biWidth    = width;
    this->m_infoExtern.bmiHeader.biHeight   = height;
    this->m_infoExtern.bmiHeader.biBitCount = bitCount;

    return !!
    SetDIBitsToDevice(this->m_hdc
                     ,centered? (this->m_destination.width  - width)  / 2 : xPosition
                     ,centered? (this->m_destination.height - height) / 2 : yPosition
                     ,width
                     ,height
                     ,0, 0
                     ,0, height
                     ,image
                     ,&this->m_infoExtern
                     ,DIB_RGB_COLORS)
                     ;
}

bool TGL::tglVideo::Display(const TGL::tglBitmap *bitmap)
{
    return this->Display(bitmap->image,
                         bitmap->xPosition,
                         bitmap->yPosition,
                         bitmap->current.width,
                         bitmap->current.height,
                         bitmap->centered,
                         bitmap->current.bitCount);
}

bool TGL::tglVideo::Display(const TGL::tglBitmap &bitmap)
{
    return this->Display(&bitmap);
}

bool TGL::tglVideo::Display(const TGL::tglImageGenerator *generator)
{
    return this->Display(generator->GetBitmap());
}

bool TGL::tglVideo::Display(const TGL::tglImageGenerator &generator)
{
    return this->Display(&generator);
}

bool TGL::tglVideo::Display()
{
    switch (this->m_mode)
    {
        case TGL::VideoMode::Bits:
        {
            return this->DisplayBits();
        }

        case TGL::VideoMode::Bitmap:
        {
            return this->DisplayBitmap();
        }

        case TGL::VideoMode::Generator:
        {
            return this->DisplayGenerator();
        }

        default:
        {
            return false;
        }
    }
}

HDC TGL::tglVideo::RequestHDC()
{
    return m_hdc;
}



const HWND TGL::tglVideo::handle() const
{
    return this->m_handle;
}

const HDC TGL::tglVideo::hdc() const
{
    return this->m_hdc;
}

bool TGL::tglVideo::locked() const
{
    return this->m_locked;
}

const BITMAPINFO &TGL::tglVideo::infoExtern() const
{
    return this->m_infoExtern;
}

const BITMAPINFO &TGL::tglVideo::info() const
{
    return this->m_info;
}



void TGL::tglVideo::Initialize()
{
    this->m_handle = NULL;
    this->m_hdc = NULL;
    this->m_locked = false;

    ZeroMemory(&this->m_infoExtern, sizeof(this->m_infoExtern));

    this->m_infoExtern.bmiHeader.biSize        = sizeof(this->m_infoExtern.bmiHeader);
    this->m_infoExtern.bmiHeader.biPlanes      = 1;
    this->m_infoExtern.bmiHeader.biBitCount    = TGL::bitCount;
    this->m_infoExtern.bmiHeader.biCompression = BI_RGB;

    ZeroMemory(&this->m_info, sizeof(this->m_info));

    this->m_info.bmiHeader.biSize        = sizeof(this->m_info.bmiHeader);
    this->m_info.bmiHeader.biPlanes      = 1;
    this->m_info.bmiHeader.biBitCount    = TGL::bitCount;
    this->m_info.bmiHeader.biCompression = BI_RGB;



    this->m_mode = TGL::VideoMode::Bits;

    if (TGL::VideoMode::Bits == this->m_mode)
    {
        this->m_source.width     = 0;
        this->m_source.height    = 0;
        this->m_source.xPosition = 0;
        this->m_source.yPosition = 0;
        this->m_source.image     = NULL;
        this->m_source.bitCount  = 32;
    }

    this->m_destination.width
  = this->m_destination.height
  = 0;
}

bool TGL::tglVideo::DisplayBits()
{
    this->m_info.bmiHeader.biWidth    = this->m_source.width;
    this->m_info.bmiHeader.biHeight   = this->m_source.height;
    this->m_info.bmiHeader.biBitCount = this->m_source.bitCount;

    return !!
    SetDIBitsToDevice(this->m_hdc
                     ,this->m_source.centered? (this->m_destination.width  - this->m_source.width)  / 2 : this->m_source.xPosition
                     ,this->m_source.centered? (this->m_destination.height - this->m_source.height) / 2 : this->m_source.yPosition
                     ,this->m_source.width
                     ,this->m_source.height
                     ,0, 0
                     ,0, this->m_source.height
                     ,this->m_source.image
                     ,&this->m_info
                     ,DIB_RGB_COLORS)
                     ;
}

bool TGL::tglVideo::DisplayBitmap()
{
    this->m_info.bmiHeader.biWidth    = this->m_source.bitmap->current.width;
    this->m_info.bmiHeader.biHeight   = this->m_source.bitmap->current.height;
    this->m_info.bmiHeader.biBitCount = this->m_source.bitmap->current.bitCount;

    return !!
    SetDIBitsToDevice(this->m_hdc
                     ,this->m_source.bitmap->centered? (this->m_destination.width  - this->m_source.bitmap->current.width)  / 2 : this->m_source.bitmap->xPosition
                     ,this->m_source.bitmap->centered? (this->m_destination.height - this->m_source.bitmap->current.height) / 2 : this->m_source.bitmap->yPosition
                     ,this->m_source.bitmap->current.width
                     ,this->m_source.bitmap->current.height
                     ,0, 0
                     ,0, this->m_source.bitmap->current.height
                     ,this->m_source.bitmap->image
                     ,&this->m_info
                     ,DIB_RGB_COLORS)
                     ;
}

bool TGL::tglVideo::DisplayGenerator()
{
    return this->Display(this->m_source.generator);
}

std::string TGL::tglVideo::GetSourceValues() const
{
    switch (this->m_mode)
    {
        case TGL::VideoMode::Bits:
        {
            return std::string("Source:\n\tbitCount: ") + TGL::String(this->m_source.bitCount)
                             + "\n\tcentered: "  + (this->m_source.centered? "Yes" : "No")
                             + "\n\twidth: "     + TGL::String(this->m_source.width)
                             + "\n\theight: "    + TGL::String(this->m_source.height)
                             + "\n\timage: "     + (this->m_source.image? "Yes; " + TGL::StringHex(largeuint_t(this->m_source.image)) : "No")
                             + "\n\txPosition: " + TGL::String(this->m_source.xPosition)
                             + "\n\tyPosition: " + TGL::String(this->m_source.yPosition)
                             ;
        }

        case TGL::VideoMode::Bitmap:
        {
            return (this->m_source.bitmap? this->m_source.bitmap->GetValues() : "Bitmap is NULL");
        }

        default:
        {
            return "None of the video modes";
        }
    }

    return "No case detected";
}



#endif // TGL_VIDEO_H



































