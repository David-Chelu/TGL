#ifndef TGL_IMAGE_GENERATOR_CPP
    #define TGL_IMAGE_GENERATOR_CPP



void TGL::tglImageGenerator::CreateBuffer(largeuint_t xBuffer, largeuint_t yBuffer)
{
    image_.planned.width  = xBuffer;
    image_.planned.height = yBuffer;

    image_.Allocate();
}

void TGL::tglImageGenerator::DrawPattern()
{
    DrawPattern(image_);
}

void TGL::tglImageGenerator::GetRectangle(largeint_t &x1
                                         ,largeint_t &y1
                                         ,largeint_t &x2
                                         ,largeint_t &y2
                                         ,const TGL::tglBitmap &bitmap
                                         ) const
{
    if (bitmap.centered)
    {
        x2 = (x1 = (image_.current.width  - bitmap.current.width)  / 2) + bitmap.current.width;
        y2 = (y1 = (image_.current.height - bitmap.current.height) / 2) + bitmap.current.height;
    }
    else
    {
        x2 = (x1 = bitmap.xPosition) + bitmap.current.width;
        y2 = (y1 = bitmap.yPosition) + bitmap.current.height;
    }
}

void TGL::tglImageGenerator::Wipe()
{
    for (largeuint_t index = 0; index < image_.size; ++index)
    {
        image_.image[index] = 0;
    }
}

bool TGL::tglImageGenerator::Combine()
{
    // TODO: implement segmentation algorithm
    /*
    Option 1: upon internal bitmap allocation, also allocate equal segments of the whole image.
    For instance, 10x10 segments (if xScreen and yScreen % 10 == 0).
    Each segment has an overall bool that tells if it is filled or not, as well as a bool matrix that marks individual pixels.
    Consider segmenting lines with overall bools, to further skip checks.
    Each time a layer is brought into focus, it's checked to see what segments it touches on, and only those segments will be looped through while checking their overall availability bool.

    Option 2: upon first layer coming into focus, segment the rest into outlying sections.
    Either the rest are checked linearly, or a few more sections are created (otherwise it can become too fragmented).
    */

    static COLORREF
        color;

    static largeint_t
        xStart
       ,yStart
       ,xStop
       ,yStop
       ,x1
       ,y1
       ,x2
       ,y2
       ,xPixel
       ,yPixel
       ;

    xStart = image_.current.width;
    yStart = image_.current.height;
    xStop  = 0;
    yStop  = 0;

    for (auto &layer : layers_)
    {
        if (TGL::bitmap == layer.type &&
            layer.bitmap->image)
        {
            GetRectangle(x1, y1, x2, y2, *layer.bitmap);

            xStart = TGL::Min(xStart, x1);
            yStart = TGL::Min(yStart, y1);

            xStop = TGL::Max(xStop, x2);
            yStop = TGL::Max(yStop, y2);
        }

        if (TGL::animation == layer.type)
        {
        }
    }

    for (yPixel = yStart; yPixel < yStop; ++yPixel)
    {
        image_(yPixel);

        for (xPixel = xStart; xPixel < xStop; ++xPixel)
        {
            for (auto &layer : layers_)
            {
                TGL::tglBitmap
                    &bitmap = *layer.bitmap;

                GetRectangle(x1, y1, x2, y2, bitmap);

                if (x1 <= xPixel && xPixel < x2 &&
                    y1 <= yPixel && yPixel < y2)
                    // && 255 == TGL::Alpha(color = layer.bitmap(yPixel)[xPixel]
                {
                    image_[xPixel] = bitmap(yPixel - y1)[xPixel - x1];

                    break;
                }
            }
        }
    }

    return true;
}

const TGL::tglBitmap &TGL::tglImageGenerator::GetBitmap() const
{
    return image_;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Add(TGL::tglBitmap *bitmap)
{
    return (*this) += bitmap;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Add(TGL::tglBitmap &bitmap)
{
    return Add(&bitmap);
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Remove(TGL::tglBitmap *bitmap)
{
    return (*this) -= bitmap;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Remove(TGL::tglBitmap &bitmap)
{
    return Remove(&bitmap);
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Remove(size_t index)
{
    return (*this) -= index;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::operator +=(TGL::tglBitmap *bitmap)
{
    layers_.push_back({bitmap, TGL::bitmap});

    return *this;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::operator +=(TGL::tglBitmap &bitmap)
{
    return (*this) += &bitmap;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::operator -=(TGL::tglBitmap *bitmap)
{
    for (size_t layer = 0; layer < layers_.size(); ++layer)
    {
        if (TGL::bitmap == layers_[layer].type &&
                 bitmap == layers_[layer].bitmap)
        {
            layers_.erase(layers_.begin() + layer);

            break;
        }
    }

    return *this;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::operator -=(TGL::tglBitmap &bitmap)
{
    return (*this) -= &bitmap;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::operator -=(size_t index)
{
    return *this;
}



void TGL::tglImageGenerator::DrawPattern(TGL::tglBitmap &bitmap)
{
    if (!bitmap.image)
    {
        bitmap.planned.width =
        bitmap.planned.height =
        256;

        bitmap.Allocate();
    }

    largeuint_t
        width,
        height;

    bitmap.Fill(0);

    width  = TGL::Min(static_cast<largeuint_t>(256U), bitmap.current.width);
    height = TGL::Min(static_cast<largeuint_t>(256U), bitmap.current.height);

    for (uint16_t y = 0, x; y < height; ++y)
    {
        bitmap(y);

        for (x = 0; x < width; ++x)
        {
            bitmap[x] = TGL::Pixel(x
                                  ,y
                                  ,x * y
                                  );
        }
    }
}

void TGL::tglImageGenerator::DrawPattern(TGL::tglBitmap *bitmap)
{
    DrawPattern(*bitmap);
}



#endif // TGL_IMAGE_GENERATOR_CPP
