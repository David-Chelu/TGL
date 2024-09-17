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



// TODO:
//    Flip / Swap(color1, color2)
//    Invert(colors) (using |)
//    Normalize(colors, low, high) // low and high are the lowest and highest points for the colors. They will be proportionally reduced to this interval.
//    Amplify(colors, pivot, power) // pivot is the starting point, power means the amount by which to turn up/down each color. Low power means not much amplifying, high power means colors reach the extremities
//    Contrast(colors) // calls Amplify(colors, 0x7F, 0x7F)
//    Compress(colors, pivot, power, threshold) // calls Amplify(colors, 0, 0xFF) and Normalize(colors, threshold)
//    Eliminate(colors, below, above) // below is a threshold below which all selected color values are removed, and above is a threshold above which all selected color values are removed. Has a case for x < below || x > above, as well as for x > below && x < above
//    ContrastImage(pivot, power) // each pixel's highest intensity is its intensity. Using that, each pixel is pushed with power away from pivot, creating more contrasted colors
//    Snap/Reduce(bits, colors) // simulates less bits per pixel (so if 8bit for red and has value 11, with a conversion to 4bit, the red value becomes 16. For 5bit, it becomes 8. For 7bit, it becomes either 10 or 12. bits is the value to simulate
//    Crop Variants:
//        -Crop = {xStart, yStart, xStop, yStop}
//            -CropStart = {xStart, yStart}
//            -CropStop = {xStop, yStop}
//            -CropX = {xStart, xStop}
//                -CropStartX = {xStart}
//                -CropStopX = {xStop}
//            -CropY = {yStart, yStop}
//                -CropStartY = {yStart}
//                -CropStopY = {yStop}
//            -CropDivide = {xPivot = BEGIN, yPivot = BEGIN, xDivisor, yDivisor}
//                -CropDivideX = {xPivot, xDivisor}
//                -CropDivideY = {yPivot, yDivisor}
//                -maybe add CropDivideBegin, CropDivideMiddle, CropDivideEnd and their x and y subvariants
//            -CropMultiply = {xPivot = BEGIN, yPivot = BEGIN, xDivisor, yDivisor}
//                -CropMultiplyX = {xPivot, xMultiplier}
//                -CropMultiplyY = {yPivot, yMultiplier}
//                -maybe add CropMultiplyBegin, CropMultiplyMiddle, CropMultiplyEnd and their x and y subvariants
//    DrawGradient // based on vertices, will create gradients between points
//    DrawCells // based on vertices, will create cells between points. Each cell is defined as the color

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
       ,Stretch(largeuint_t xResize, largeuint_t yResize)
       ,StretchX(largeuint_t xResize)
       ,StretchY(largeuint_t yResize)
       ,StretchDiv(largeuint_t xDivisor, largeuint_t yDivisor)
       ,StretchDivX(largeuint_t xDivisor)
       ,StretchDivY(largeuint_t yDivisor)
       ,StretchMul(largeuint_t xMultiplier, largeuint_t yMultiplier)
       ,StretchMulX(largeuint_t xMultiplier)
       ,StretchMulY(largeuint_t yMultiplier)
       ;

    static bool
        Exists(const std::string &file)
       ,Exists(const char *file)
       ;

    inline void
        DisplayValues() const
       ,Reset()
       ,Clear()
       ;

    inline std::string
        GetValues() const;

    largeuint_t
        Fill(COLORREF color)
       ,Fill(COLORREF color, largeuint_t x1, largeuint_t y1, largeuint_t x2 = -1, largeuint_t y2 = -1)
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



protected:

    TGL::ImageAttributes
        m_current,
        m_planned;



private:

    void
        Initialize();



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



#endif // TGL_BITMAP_H



































