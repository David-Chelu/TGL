#ifndef TGL_BITMAP_H
    #define TGL_BITMAP_H



#include "ImageAttributes.h"



struct TGL::HeaderTBM
{
    largeuint_t
        width,
        height;

    TGL::ImageCompression
        compression;

    uint8_t
        bitCount;
};

struct ImageWithSize_t
{
    COLORREF *image;
    largeuint_t width, height;
};

struct ColorWithSize_t
{
    COLORREF color;
    largeuint_t width, height;
};



//    Stretch?
//    Crop
//    Flip / Swap(color1, color2)
//    Invert(colors) (using |)
//    Normalize(colors, low, high) // low and high are the lowest and highest points for the colors. They will be proportionally reduced to this interval.
//    Amplify(colors, pivot, power) // pivot is the starting point, power means the amount by which to turn up/down each color. Low power means not much amplifying, high power means colors reach the extremities
//    Contrast(colors) // calls Amplify(colors, 0x7F, 0x7F)
//    Compress(colors, pivot, power, threshold) // calls Amplify(colors, 0, 0xFF) and Normalize(colors, threshold)
//    Eliminate(colors, below, above) // below is a threshold below which all selected color values are removed, and above is a threshold above which all selected color values are removed. Has a case for x < below || x > above, as well as for x > below && x < above
//    ContrastImage(pivot, power) // each pixel's highest intensity is its intensity. Using that, each pixel is pushed with power away from pivot, creating more contrasted colors
//    Snap/Reduce(bits, colors) // simulates less bits per pixel (so if 8bit for red and has value 11, with a conversion to 4bit, the red value becomes 16. For 5bit, it becomes 8. For 7bit, it becomes either 10 or 12. bits is the value to simulate

class TGL::tglBitmap : public TGL::tglObject
{
public:

    tglBitmap();
    tglBitmap(const ImageWithSize_t &imageSize);
    tglBitmap(const ColorWithSize_t &colorSize);
    tglBitmap(const std::string &newDirectory);
    ~tglBitmap();



    inline TGL::tglBitmap
        &Assign(const ImageWithSize_t &imageSize)
       ,&Assign(const ColorWithSize_t &colorSize)
       ,&Assign(COLORREF pixel)
       ,&Assign(const TGL::tglBitmap &source)
       ,&Assign(const std::string &newDirectory)
       ;

    TGL::tglBitmap
        &Copy(const TGL::tglBitmap &source);

    bool
        Allocate()
       ,Deallocate()
       ,Center()
       ,Decenter()
       ,Exists()
       ,Exists(const std::string &file)
       ,Exists(const char *file)
       ;

    inline void
        DisplayValues() const,
        Reset(),
        Clear();


    inline std::string
        GetValues() const;

    largeuint_t
        Fill(COLORREF color)
       ,Replace(COLORREF target, COLORREF color)
       ,Filter(uint8_t colors)
       ,Keep(uint8_t colors)
       ,Load()
       ,Load(const std::string &file)
       ,Load(const char *file)
       ,Save()
       ,Save(const std::string &file)
       ,Save(const char *file)
       ,LoadTBM()
       ,LoadTBM(const std::string &file)
       ,LoadTBM(const char *file)
       ,SaveTBM(const TGL::ImageCompression compression = TGL::ImageCompression::None)
       ,SaveTBM(const std::string &file, const TGL::ImageCompression compression = TGL::ImageCompression::None)
       ,SaveTBM(const char *file, const TGL::ImageCompression compression = TGL::ImageCompression::None)
       ;



    TGL::tglBitmap
        &operator  =(const ImageWithSize_t &imageSize)
       ,&operator  =(const ColorWithSize_t &colorSize)
       ,&operator  =(COLORREF pixel)
       ,&operator  =(const TGL::tglBitmap &source)
       ,&operator  =(const std::string &newDirectory)
       ,&operator ()(largeuint_t line)
       ,&operator [](largeuint_t column)
       ;

    operator bool() const;
    bool operator !() const;



    const TGL::ImageAttributes
        &current;

    TGL::ImageAttributes
        &planned;

    COLORREF
        *const &image,
        *const &selectedLine;

    const uint64_t
        &selectedColumn,
        &size;

    const bool
        &centered;

    int64_t
        &xPosition,
        &yPosition;

    uint8_t
        &alpha;

    std::string
        &directory;

private:

    void
        Initialize();



    TGL::ImageAttributes
        m_current,
        m_planned;

    COLORREF
        *m_image,
        *m_selectedLine;

    uint64_t
        m_selectedColumn,
        m_size;

    bool
        m_centered;
        // add m_absolute, m_relative, or m_coordinates (mode to switch between relative and absolute). This will determine whether the coordinates are bound to the window, or the monitor (the world, the camera). If relative, it works standard. If absolute, you can move around the window while the camera and character stay in the same place.

    int64_t
        m_xPosition,
        m_yPosition;

    uint8_t
        m_alpha;

    std::string
        m_directory;
};



TGL::tglBitmap::tglBitmap() : current(m_current), planned(m_planned), image(m_image), selectedLine(m_selectedLine), selectedColumn(m_selectedColumn), size(m_size), centered(m_centered), xPosition(m_xPosition), yPosition(m_yPosition), alpha(m_alpha), directory(m_directory)
{
    this->Initialize();
}

TGL::tglBitmap::tglBitmap(const ImageWithSize_t &imageSize) : tglBitmap()
{
    this->Assign(imageSize);
}

TGL::tglBitmap::tglBitmap(const ColorWithSize_t &colorSize) : tglBitmap()
{
    this->Assign(colorSize);
}

TGL::tglBitmap::tglBitmap(const std::string &newDirectory) : tglBitmap()
{
    this->Assign(newDirectory);
}

TGL::tglBitmap::~tglBitmap()
{
    this->Clear();
}



TGL::tglBitmap &TGL::tglBitmap::Assign(const ImageWithSize_t &imageSize)
{
    return (*this) = imageSize;
}

TGL::tglBitmap &TGL::tglBitmap::Assign(const ColorWithSize_t &colorSize)
{
    return (*this) = colorSize;
}

TGL::tglBitmap &TGL::tglBitmap::Assign(COLORREF pixel)
{
    return (*this) = pixel;
}

TGL::tglBitmap &TGL::tglBitmap::Assign(const TGL::tglBitmap &source)
{
    return (*this) = source;
}

TGL::tglBitmap &TGL::tglBitmap::Assign(const std::string &newDirectory)
{
    return (*this) = newDirectory;
}

TGL::tglBitmap &TGL::tglBitmap::Copy(const TGL::tglBitmap &source)
{
    this->Reset();

    this->m_planned = source.m_current;

    this->m_centered = source.m_centered;

    this->m_xPosition = source.m_xPosition;
    this->m_yPosition = source.m_yPosition;

    this->m_alpha = source.m_alpha;

    if (source.image && this->Allocate())
    {
        memcpy(this->m_image,
               source.image,
               this->m_size * this->m_current.bitCount / 8);
    }



    return *this;
}

bool TGL::tglBitmap::Allocate()
{
    if (this->m_planned.width && this->m_planned.height)
    {
        this->Deallocate();

        if (this->m_selectedLine = this->m_image = new COLORREF[this->m_planned.width * this->m_planned.height])
        {
            this->m_size =
            (this->m_current.width  = this->m_planned.width) *
            (this->m_current.height = this->m_planned.height);

            this->m_current.bitCount = this->m_planned.bitCount;

            this->m_selectedColumn = 0;

            return true;
        }
    }

    return false;
}

bool TGL::tglBitmap::Deallocate()
{
    if (this->m_image)
    {
        delete []this->m_image;

        this->m_size =
        this->m_current.width =
        this->m_current.height = 0;

        this->m_current.bitCount = 0;

        this->m_image = this->m_selectedLine = NULL;
        this->m_selectedColumn = 0;

        return true;
    }

    return false;
}

bool TGL::tglBitmap::Center()
{
    if (!this->m_centered)
    {
        this->m_centered = true;
    }

    return this->m_centered;
}

bool TGL::tglBitmap::Decenter()
{
    if (this->m_centered)
    {
        this->m_centered = false;
    }

    return !this->m_centered;
}

bool TGL::tglBitmap::Exists()
{
    return this->Exists(this->m_directory);
}

bool TGL::tglBitmap::Exists(const std::string &file)
{
    return this->Exists(file.c_str());
}

bool TGL::tglBitmap::Exists(const char *file)
{
    FILE
        *opener;

    opener = fopen(file, "r");

    if (opener)
    {
        fclose(opener);

        return true;
    }

    return false;
}

void TGL::tglBitmap::DisplayValues() const
{
    std::cout << this->GetValues() + "\n\n\n\n";
}

void TGL::tglBitmap::Reset()
{
    this->Clear();
    this->Initialize();

    this->m_current.Initialize();
    this->m_planned.Initialize();
}

void TGL::tglBitmap::Clear()
{
    this->Deallocate();
}

std::string TGL::tglBitmap::GetValues() const
{
    return this->TGL::tglObject::GetValues()
           + "\nCurrent "          + this->m_current.GetValues()
           + "\n\nPlanned "        + this->m_planned.GetValues()
           + "\n\nImage: "         + (this->m_image? "Yes; " + TGL::StringHex(largeuint_t(this->m_image)) : "No")
           + "\nSelected Line: "   + (this->m_image? TGL::String(this->m_current.height - 1 - (this->m_selectedLine - this->m_image) / this->m_current.width) : "0")
           + "\nSelected Column: " + TGL::String(this->m_selectedColumn)
           + "\nSize: "            + TGL::String(this->m_size)
           + "\nCentered: "        + (this->m_centered? "Yes" : "No")
           + "\nPosition: ("       + TGL::String(this->m_xPosition) + ", " + TGL::String(this->m_yPosition) + ')'
           + "\nAlpha: "           + TGL::String(this->m_alpha)
           ;
}

largeuint_t TGL::tglBitmap::Fill(COLORREF color)
{
    if (this->m_image)
    {
        for (largeuint_t pixel = 0; pixel < this->m_size; ++pixel)
        {
            this->m_image[pixel] = color;
        }

        return this->m_size;
    }

    return 0;
}

largeuint_t TGL::tglBitmap::Replace(COLORREF target, COLORREF color)
{
    static largeuint_t
        count;

    count = 0;

    if (this->m_image)
    {
        for (largeuint_t pixel = 0; pixel < this->m_size; ++pixel)
        {
            if (target == this->m_image[pixel])
            {
                this->m_image[pixel] = color;

                ++count;
            }
        }
    }

    return count;
}

largeuint_t TGL::tglBitmap::Filter(uint8_t colors)
{
    return this->Keep(~colors);
}

largeuint_t TGL::tglBitmap::Keep(uint8_t colors)
{
    if (this->m_image)
    {
        COLORREF
            mask;

        mask = TGL::Pixel((colors & RED)   * 0xFF
                         ,(colors & GREEN) * 0xFF
                         ,(colors & BLUE)  * 0xFF
                         ,(colors & ALPHA) * 0xFF
                          );

        for (largeuint_t pixel = 0; pixel < this->m_size; ++pixel)
        {
            this->m_image[pixel] &= mask;
        }

        return this->m_size;
    }

    return 0;
}

largeuint_t TGL::tglBitmap::Load()
{
    return this->Load(this->m_directory);
}

largeuint_t TGL::tglBitmap::Load(const std::string &file)
{
    return this->Load(file.c_str());
}

largeuint_t TGL::tglBitmap::Load(const char *file)
{
    std::fstream
        opener;

    opener.open(file, std::ios::in | std::ios::binary);

    if (!opener.is_open())
    {
        return 0;
    }

    BITMAPFILEHEADER
        header;

    BITMAPINFOHEADER
        info;

    largeuint_t
        bytesPerLine;

    char
        *buffer;

    uint8_t
        bytesPerPixel;



    opener.read((char*)&header, sizeof(header));
    opener.read((char*)&info,   sizeof(info));

    if (!info.biWidth || !info.biHeight)
    {
        TGL::Message("Error in TGL::tglBitmap::Load(const char *file)", std::string("File ") + file + "'s image size is 0.");

        return 0;
    }

    this->Deallocate();

    this->m_planned.width    = info.biWidth;
    this->m_planned.height   = info.biHeight;

    this->Allocate();

    if (!info.biWidth || !info.biHeight)
    {
        TGL::Message("Error in TGL::tglBitmap::Load(const char *file)", "Allocation failed.");

        return 0;
    }

    bytesPerPixel = info.biBitCount / 8;
    bytesPerLine = info.biSizeImage / this->m_current.height;
    buffer = new char[bytesPerLine];

    ZeroMemory(this->m_image, this->m_size * bytesPerPixel);

    for (largeuint_t line = 0; line < this->m_current.height; ++line)
    {
        opener.read(buffer, bytesPerLine);
        (*this)(this->m_current.height - line - 1);

        for (largeuint_t column = 0; column < this->m_current.width; ++column)
        {
            // Use this for interesting color changes
            // memcpy(((char*)(this->m_selectedLine)) + column * 4 + 1, buffer + column * 3, 3);

            // Consider making this a lambda instead, to choose how to copy red, green, and blue individually. That way, arrangements like 2 lines above can take place.
            memcpy(this->m_selectedLine + column, buffer + column * bytesPerPixel, bytesPerPixel);
        }
    }

    delete []buffer;
    opener.close();

    return this->m_size;
}

largeuint_t TGL::tglBitmap::Save()
{
    return this->Save(this->m_directory);
}

largeuint_t TGL::tglBitmap::Save(const std::string &file)
{
    return this->Save(file.c_str());
}

largeuint_t TGL::tglBitmap::Save(const char *file)
{
    std::fstream
        opener;

    opener.open(file, std::ios::out | std::ios::binary);

    if (!opener.is_open())
    {
        return 0;
    }

    static char
        nothing[3] = {0};

    BITMAPFILEHEADER
        header;

    BITMAPINFOHEADER
        info;

    largeuint_t
        bytesPerLine;

    uint8_t
        padding;



    info.biSize = sizeof(info);
    padding = (4 - (info.biWidth = this->m_current.width) % 4) & 3;
    info.biHeight = this->m_current.height;
    info.biPlanes = 1;
    info.biBitCount = (TGL::bitCount == this->m_current.bitCount? 24 : this->m_current.bitCount);
    info.biCompression = BI_RGB;
    info.biSizeImage = ((bytesPerLine = info.biWidth * info.biBitCount / 8) + padding) * info.biHeight;
    info.biXPelsPerMeter =
    info.biYPelsPerMeter =
    info.biClrUsed       =
    info.biClrImportant  = 0;

    header.bfType = (uint16_t('M') << 8) | 'B';
    header.bfOffBits = sizeof(header) + info.biSize;
    header.bfSize = header.bfOffBits + info.biSizeImage;
    header.bfReserved1 =
    header.bfReserved2 = 0;

    opener.write((char*)&header, sizeof(header));
    opener.write((char*)&info,   sizeof(info));

    for (largeint_t line = this->m_current.height - 1; line >= 0; --line)
    {
        (*this)(line);

        for (largeuint_t column = 0; column < this->m_current.width; ++column)
        {
            opener.write((char*)(this->m_selectedLine + column), info.biBitCount / 8);
        }

        opener.write(nothing, padding);
    }

    opener.close();

    return info.biSizeImage;
}


largeuint_t TGL::tglBitmap::LoadTBM()
{
    return this->LoadTBM(this->m_directory);
}

largeuint_t TGL::tglBitmap::LoadTBM(const std::string &file)
{
    return this->LoadTBM(file.c_str());
}

largeuint_t TGL::tglBitmap::LoadTBM(const char *file)
{
    std::fstream
        opener;

    opener.open(file, std::ios::in | std::ios::binary);

    if (!opener.is_open())
    {
        return 0;
    }

    TGL::HeaderTBM
        header;



    opener.read((char*)&header, sizeof(header));

    this->Deallocate();
    this->m_planned.bitCount = header.bitCount;
    this->m_planned.width    = header.width;
    this->m_planned.height   = header.height;
    this->Allocate();

    switch (header.compression)
    {
        case TGL::ImageCompression::None:
        {
            opener.read((char*)this->m_image, this->m_size * this->m_current.bitCount / 8);

            break;
        }

        case TGL::ImageCompression::Count:
        {
            largeuint_t
                cursor;

            uint32_t
                count;

            COLORREF
                pixel;

            // TODO: load whole file first, then unpack image

            count = 0;

            for (cursor = 0; cursor < this->m_size; )
            {
                if (!count)
                {
                    opener.read((char*)&count, sizeof(count));
                    opener.read((char*)&pixel, sizeof(pixel));
                }
                else
                {
                    this->m_image[cursor++] = pixel;
                    --count;
                }
            }

            break;
        }
    }



    opener.close();

    return header.width * header.height * header.bitCount / 8;
}

largeuint_t TGL::tglBitmap::SaveTBM(const TGL::ImageCompression compression)
{
    return this->SaveTBM(this->m_directory);
}

largeuint_t TGL::tglBitmap::SaveTBM(const std::string &file, const TGL::ImageCompression compression)
{
    return this->SaveTBM(file.c_str());
}

largeuint_t TGL::tglBitmap::SaveTBM(const char *file, const TGL::ImageCompression compression)
{
    std::fstream
        opener;

    opener.open(file, std::ios::out | std::ios::binary);

    if (!opener.is_open())
    {
        return 0;
    }

    TGL::HeaderTBM
        header;



    header.width  = this->m_current.width;
    header.height = this->m_current.height;
    header.compression = compression;
    header.bitCount = this->m_current.bitCount;



    opener.write((char*)&header, sizeof(header));

    switch (compression)
    {
        case TGL::ImageCompression::None:
        {
            opener.write((char*)this->m_image, header.width * header.height * this->m_current.bitCount / 8);

            break;
        }

        case TGL::ImageCompression::Count:
        {
            uint32_t
                count;

            COLORREF
                pixel;

            // TODO: optimize

            if (1 == this->m_size)
            {
                count = 1;
                pixel = this->m_image[0];

                opener.write((char*)&count, sizeof(count));
                opener.write((char*)&pixel, sizeof(pixel));
            }
            else
            {
                count = 1;

                for (largeuint_t index = 1; index < this->m_size; ++index)
                {
                    if (this->m_image[index] != this->m_image[index - 1])
                    {
                        pixel = this->m_image[index - 1];

                        opener.write((char*)&count, sizeof(count));
                        opener.write((char*)&pixel, sizeof(pixel));

                        count = 1;
                    }
                    else
                    {
                        ++count;
                    }
                }

                if (this->m_image[this->m_size - 1] != this->m_image[this->m_size - 2])
                {
                    count = 1;
                }
                else
                {
                    ++count;
                }

                pixel = this->m_image[this->m_size - 1];

                opener.write((char*)&count, sizeof(count));
                opener.write((char*)&pixel, sizeof(pixel));
            }

            break;
        }

        default:
        {
            break;
        }
    }



    opener.close();

    return header.width * header.height;
}



TGL::tglBitmap &TGL::tglBitmap::operator =(const ColorWithSize_t &colorSize)
{
    this->m_planned.width  = colorSize.width;
    this->m_planned.height = colorSize.height;

    this->Allocate();
    this->Fill(colorSize.color);

    return *this;
}

TGL::tglBitmap &TGL::tglBitmap::operator =(const ImageWithSize_t &imageSize)
{
    this->m_size =
    (this->m_current.width  = imageSize.width) *
    (this->m_current.height = imageSize.height);

    this->m_selectedLine = this->m_image = imageSize.image;

    return *this;
}

TGL::tglBitmap &TGL::tglBitmap::operator =(COLORREF pixel)
{
    if (this->m_image && this->m_selectedColumn < this->m_current.width)
    {
        this->m_selectedLine[this->m_selectedColumn] = pixel;
    }

    return *this;
}

TGL::tglBitmap &TGL::tglBitmap::operator =(const TGL::tglBitmap &source)
{
    if (this->m_image && this->m_selectedColumn < this->m_current.width
     &&  source.image &&  source.selectedColumn <  source.current.width)
    {
        this->m_selectedLine[this->m_selectedColumn] =
         source.selectedLine[ source.selectedColumn];
    }

    return *this;
}

TGL::tglBitmap &TGL::tglBitmap::operator =(const std::string &newDirectory)
{
    this->m_directory = newDirectory;

    return *this;
}

TGL::tglBitmap &TGL::tglBitmap::operator ()(largeuint_t line)
{
    if (this->m_image && line < this->m_current.height)
    {
        this->m_selectedLine = this->m_image + (this->m_current.height - line - 1) * this->m_current.width;
    }

    return *this;
}

TGL::tglBitmap &TGL::tglBitmap::operator [](largeuint_t column)
{
    if (this->m_image && column < this->m_current.width)
    {
        this->m_selectedColumn = column;
    }

    return *this;
}

TGL::tglBitmap::operator bool() const
{
    return !!this->m_image;
}

bool TGL::tglBitmap::operator !() const
{
    return !this->m_image;
}



void TGL::tglBitmap::Initialize()
{
    this->m_image        = NULL;
    this->m_selectedLine = NULL;

    this->m_selectedColumn = 0;
    this->m_size = 0;

    this->m_centered = false;

    this->m_xPosition
  = this->m_yPosition
  = 0;

    this->m_alpha = 0xFF;
}



#endif // TGL_BITMAP_H



































