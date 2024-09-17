#ifndef TGL_BITMAP_CPP
    #define TGL_BITMAP_CPP



#include "ImageAttributes.cpp"



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
        CopyMemory(this->m_image,
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
    return Exists(this->m_directory);
}

bool TGL::tglBitmap::Stretch(largeuint_t xResize, largeuint_t yResize)
{
    return StretchX(xResize) && StretchY(yResize);
}

bool TGL::tglBitmap::StretchX(largeuint_t xResize)
{
    if (m_image)
    {
        if (current.width != xResize)
        {
            COLORREF
                *backup;

            largeuint_t
                priorWidth;

            backup = m_image;
            m_image = NULL;
            priorWidth = current.width;

            planned.width  = xResize;
            planned.height = current.height;

            if (Allocate())
            {
                for (largeuint_t column = 0; column < xResize; ++column)
                {
                    TGL::StepCopy<COLORREF>(m_image + column,
                                            backup  + column * priorWidth / xResize,
                                            current.height,
                                            current.width,
                                            priorWidth);
                }
            }

            delete []backup;
        }

        return true;
    }

    return false;
}

bool TGL::tglBitmap::StretchY(largeuint_t yResize)
{
    if (m_image)
    {
        if (current.height != yResize)
        {
            COLORREF
                *backup;

            largeuint_t
                priorHeight;

            backup = m_image;
            m_image = NULL;
            priorHeight = current.height;

            planned.width  = current.width;
            planned.height = yResize;

            if (Allocate())
            {
                for (largeuint_t line = 0; line < yResize; ++line)
                {
                    TGL::StepCopy<COLORREF>(m_image + current.width * line,
                                            backup  + current.width * (line * priorHeight / yResize),
                                            current.width);
                }
            }

            delete []backup;
        }

        return true;
    }

    return false;
}

bool TGL::tglBitmap::StretchDiv(largeuint_t xDivisor, largeuint_t yDivisor)
{
    return StretchDivX(xDivisor) && StretchDivY(yDivisor);
}

bool TGL::tglBitmap::StretchDivX(largeuint_t xDivisor)
{
    return (xDivisor > 0? StretchX(current.width / xDivisor) : false);
}

bool TGL::tglBitmap::StretchDivY(largeuint_t yDivisor)
{
    return (yDivisor > 0? StretchY(current.height / yDivisor) : false);
}

bool TGL::tglBitmap::StretchMul(largeuint_t xMultiplier, largeuint_t yMultiplier)
{
    return StretchMulX(xMultiplier) && StretchMulY(yMultiplier);
}

bool TGL::tglBitmap::StretchMulX(largeuint_t xMultiplier)
{
    return StretchX(current.width * xMultiplier);
}

bool TGL::tglBitmap::StretchMulY(largeuint_t yMultiplier)
{
    return StretchY(current.height * yMultiplier);
}

bool TGL::tglBitmap::Exists(const std::string &file)
{
    return Exists(file.c_str());
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

/*
bool TGL::tglBitmap::Crop(largeuint_t xSize, largeuint_t ySize)
{
    TGL::Message("Crop(" + TGL::String(xSize) + ", " + TGL::String(ySize) + ')', "");

    if (0 == this->m_size)
    {
        return false;
    }

    if (-1 == xSize)
    {
        xSize = this->m_current.width;
    }

    if (-1 == ySize)
    {
        ySize = this->m_current.height;
    }

    TGL::Message("Crop(" + TGL::String(xSize) + ", " + TGL::String(ySize) + ')', "");



    if (xSize != this->m_current.width)
    {
        if (ySize != this->m_current.height)
        {
            TGL::Message("Current Branch", "Different xSize\nDifferent ySize");
            // TODO: different height, different width
        }
        else
        {
            TGL::Message("Current Branch", "Different xSize");
            // TODO: same height, different width
        }
    }
    else
    {
        if (ySize != this->m_current.height)
        {
            TGL::Message("Current Branch", "Different ySize");

            //TODO: debug, it enters this branch but the crop doesn't take place

            COLORREF
                *backup;

            largeuint_t
                backupSize;

            backup = this->m_image;
            backupSize = this->m_size;
            this->m_image = NULL;

            this->m_planned.height = ySize;

            this->Allocate();
            ZeroMemory(this->m_image, this->m_size * this->m_current.bitCount / 8);
            CopyMemory(this->m_image,
                       backup,
                       TGL::Min(this->m_size, backupSize) * this->m_current.bitCount / 8);

            TGL::Message("yCrop values",
                         "size: " + TGL::String(this->m_size)
                       + "\nsize: " + TGL::String(backupSize)
                       + "\nwidth: " + TGL::String(this->m_current.width)
                       + "\nheight: " + TGL::String(this->m_current.height)
                       );

            delete []backup;
        }
    }



    return true;
}
*/

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
    return Fill(color, 0, 0);
}

largeuint_t TGL::tglBitmap::Fill(COLORREF color, largeuint_t x1, largeuint_t y1, largeuint_t x2, largeuint_t y2)
{
    if (this->m_image)
    {
        static
            largeuint_t
                x,
                y,
                filledPixels;

        filledPixels = 0;

        if (x1 > x2) std::swap(x1, x2);
        if (y1 > y2) std::swap(y1, y2);

        y1 = TGL::Max<decltype(y1)>(0, TGL::Min<decltype(y1)>(y1, m_current.height));
        x1 = TGL::Max<decltype(x1)>(0, TGL::Min<decltype(x1)>(x1, m_current.width));
        y2 = TGL::Max<decltype(y2)>(0, TGL::Min<decltype(y2)>(y2, m_current.height));
        x2 = TGL::Max<decltype(x2)>(0, TGL::Min<decltype(x2)>(x2, m_current.width));

        for (y = y1; y < y2; ++y)
        {
            operator ()(y);

            for (x = x1; x < x2; ++x)
            {
                operator [](x) = color;
            }
        }

        return filledPixels;
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
            // CopyMemory(((char*)(this->m_selectedLine)) + column * 4 + 1, buffer + column * 3, 3);

            // Consider making this a lambda instead, to choose how to copy red, green, and blue individually. That way, arrangements like 2 lines above can take place.
            CopyMemory(this->m_selectedLine + column, buffer + column * bytesPerPixel, bytesPerPixel);
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
        return -1;
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



#endif // TGL_BITMAP_CPP



































