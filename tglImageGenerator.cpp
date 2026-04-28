#ifndef TGL_IMAGE_GENERATOR_CPP
    #define TGL_IMAGE_GENERATOR_CPP



void TGL::tglImageGenerator::CreateBuffer(largeuint_t xBuffer, largeuint_t yBuffer)
{
    m_image.planned.width  = xBuffer;
    m_image.planned.height = yBuffer;

    m_image.Allocate();
}

void TGL::tglImageGenerator::DrawPattern()
{
    DrawPattern(m_image);
}

void TGL::tglImageGenerator::GetRectangle(const TGL::tglBitmap &destination
                                         ,largeint_t &x1
                                         ,largeint_t &y1
                                         ,largeint_t &x2
                                         ,largeint_t &y2
                                         ,const TGL::tglBitmap &bitmap
                                         ,bool relative
                                         ) const
{
    if (bitmap.centered)
    {
        x2 = (x1 = (largeint_t(destination.current.width ) - largeint_t(bitmap.current.width )) / 2) + bitmap.current.width;
        y2 = (y1 = (largeint_t(destination.current.height) - largeint_t(bitmap.current.height)) / 2) + bitmap.current.height;
    }
    else
    {
        x2 = (x1 = bitmap.xPosition) + bitmap.current.width;
        y2 = (y1 = bitmap.yPosition) + bitmap.current.height;
    }

    if (x1 < destination.xPosition) x1 = destination.xPosition;
    if (y1 < destination.xPosition) y1 = destination.xPosition;
    if (x2 > largeint_t(destination.xPosition + destination.current.width )) x2 = destination.xPosition + destination.current.width;
    if (y2 > largeint_t(destination.yPosition + destination.current.height)) y2 = destination.yPosition + destination.current.height;
}

void TGL::tglImageGenerator::GetRectangle(largeint_t &x1
                                         ,largeint_t &y1
                                         ,largeint_t &x2
                                         ,largeint_t &y2
                                         ,const TGL::tglBitmap &bitmap
                                         ,bool relative
                                         ) const
{
    GetRectangle(m_image, x1, y1, x2, y2, bitmap, relative);
}

void TGL::tglImageGenerator::Wipe()
{
    for (largeuint_t index = 0; index < m_image.size; ++index)
    {
        m_image.image[index] = 0;
    }
}

bool TGL::tglImageGenerator::Combine(TGL::tglBitmap &destination)
{
    // TODO: implement case where external bitmap is rendered to

    return true;
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

    xStart = m_image.current.width;
    yStart = m_image.current.height;
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

    ParseRangeY()
    {
        m_image(yPixel);

        ParseRangeX()
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
                    m_image[xPixel] = bitmap(yPixel - y1)[xPixel - x1];

                    break;
                }
            }
        }
    }

    return true;
}

int32_t DrawVerticalSliceColor(TGL::tglBitmap *destination, uint32_t lineStart, uint32_t span, COLORREF color)
{
    // although the variable is called lineStart, it does not refer to the y coordinate in the image. Instead, it says where, horizontally, the current pixel is on the given line, in other words the column (0 -> width)

    int32_t
        line,
        pixelsDrawn{0};

    COLORREF
        *currentLine;

    while (span > 0)
    {
        ParseRange(line, 0, destination->current.height, ++line)
        {
            currentLine = destination->image + line * destination->current.width + lineStart;
            currentLine[0] = color;

            ++pixelsDrawn;
        }

        ++lineStart;
        --span;
    }

    return pixelsDrawn;
}

int32_t DrawVerticalSlices(TGL::tglBitmap *destination, const std::vector<Layer> *layers, uint32_t lineStart, uint32_t span, bool alpha)
{
    // although the variable is called lineStart, it does not refer to the y coordinate in the image. Instead, it says where, horizontally, the current pixel is on the given line, in other words the column (0 -> width)

    if (destination && layers)
    {
        int32_t
            line,
            width = int32_t(destination->current.width),
            pixelsDrawn{0};
        
        COLORREF
            *currentLine,
            color;
        
        while (span > 0)
        {
            ParseRange(line, 0, destination->current.height, ++line)
            {
                color = TGL::unrenderedColor;

                for (auto layer : *layers)
                {
                    largeint_t
                        xLeft = layer.bitmap->xPosition,
                        xRight = layer.bitmap->xPosition + layer.bitmap->current.width,
                        yUp = layer.bitmap->yPosition,
                        yDown = layer.bitmap->yPosition + layer.bitmap->current.height;
                    
                    if (xLeft <= destination->xPosition + lineStart && destination->xPosition + lineStart < xRight &&
                        yUp   <= destination->yPosition + line      && destination->yPosition + line      < yDown)
                    {
                        COLORREF
                            &pixelInBitmap =
                                layer.bitmap->image[(layer.bitmap->current.height - (destination->yPosition + line - yUp) - 1) * layer.bitmap->current.width + destination->xPosition + lineStart - xLeft];
                        
                        if (TGL::Alpha(pixelInBitmap))
                        {
                            color = pixelInBitmap;
                            
                            break;
                        }
                    }
                }

                currentLine = destination->image + (destination->current.height - line - 1) * destination->current.width + lineStart;
                currentLine[0] = color;

                ++pixelsDrawn;
            }

            ++lineStart;
            --span;
        }

        return pixelsDrawn;
    }

    return -1;
}

// TODO:DrawHorizontalSlices; this will make use of segmenting, and also parse Ox which avoids extra calculations

bool TGL::tglImageGenerator::CombineByPasting(TGL::tglBitmap &destination, bool alpha)
{
    static largeint_t
        xPixel, yPixel
       ,xStart, yStart
       ,xStop , yStop
       ;



    // if (erase)
    // {
    //     if (alpha)
    //     {
    //         for (auto &layer : layers_)
    //         {
    //             TGL::tglBitmap
    //                 &bitmap = (*layer.bitmap);

    //             GetRectangle(destination, xStart, yStart, xStop, yStop, bitmap);

    //             ParseRangeY()
    //             {
    //                 destination(yPixel - destination.yPosition);
    //                 bitmap(yPixel - yStart);

    //                 ParseRangeX()
    //                 {
    //                     if (0xFF == TGL::Alpha(bitmap[xPixel - xStart].color()))
    //                     {
    //                         destination[xPixel - destination.xPosition] = background;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //     else
    //     {
    //         for (auto &layer : layers_)
    //         {
    //             TGL::tglBitmap
    //                 &bitmap = (*layer.bitmap);

    //             GetRectangle(destination, xStart, yStart, xStop, yStop, bitmap);

    //             ParseRangeY()
    //             {
    //                 destination(yPixel - destination.yPosition);
    //                 bitmap(yPixel - yStart);

    //                 ParseRangeX()
    //                 {
    //                     destination[xPixel - destination.xPosition] = background;
    //                 }
    //             }
    //         }
    //     }
    // }
    // else

    switch (alpha)
    {
        case true:
        {
            for (auto &layer : layers_)
            {
                TGL::tglBitmap
                    &bitmap = (*layer.bitmap);

                GetRectangle(destination, xStart, yStart, xStop, yStop, bitmap);

                ParseRangeY()
                {
                    destination(yPixel - destination.yPosition);
                    bitmap(yPixel - yStart);

                    ParseRangeX()
                    {
                        if (0xFF == TGL::Alpha(bitmap[xPixel - xStart].color()))
                        {
                            destination[xPixel - destination.xPosition] = bitmap[xPixel - xStart];
                        }
                    }
                }
            }
        }
        break;



        case false:
            for (auto &layer : layers_)
            {
                TGL::tglBitmap
                    &bitmap = (*layer.bitmap);

                GetRectangle(destination, xStart, yStart, xStop, yStop, bitmap);

                ParseRangeY()
                {
                    destination(yPixel - destination.yPosition);
                    bitmap(yPixel - yStart);

                    ParseRangeX()
                    {
                        destination[xPixel - destination.xPosition] = bitmap[xPixel - xStart];
                    }
                }
            }
        break;
    }



//    int
//        x, y;
//
//    for (const Layer &layer : Draw::layers)
//    {
//        for (x = 0; x < layer.width; ++x)
//        {
//            for (y = 0; y < layer.height; ++y)
//            {
//                Draw::buffer[(y + layer.y) * Draw::width + x + layer.x] = 219;
//            }
//        }
//    }

    return true;
}

/**
 * TODO:
 * 1. stretch blt with distortion (quadrilateral but not necessarily parallel lines). This might make use of line algorithm as starting point for each line of pixels
 * 2. add a shadows array, which has the same ordering as Layers, or alternatively include shadow object inside Layer class
 * 3. isometric projection (dist = infinite) for global illumination source, using a predefined angle value
 * 4. perspective projection from a given point, using triangle equivalence. This has use in camera perspective (can be placed anywhere on the screen or off screen)
 */

bool TGL::tglImageGenerator::CombineByPasting(bool alpha)
{
    return CombineByPasting(m_image, alpha);
}

bool TGL::tglImageGenerator::CombineByPastingMT(TGL::tglBitmap &destination, bool alpha)
{
    if (destination.current.width)
    {
        long double
            performance;

        performance = TGL::performance.getValue();

        if (!TGL::IsFloatEqual(performance, 0.F))
        {
            uint32_t
                slices,
                cores,
                threads,
                slicesPerCore,
                remainderSlices;

            slices = destination.current.width;
            cores = TGL::GetNumberOfCores();
            threads = TGL::Approximate(performance * ((long double)cores) * ((long double)TGL::threadsPerCore));

            if (threads > 0)
            {
                slicesPerCore   = slices / threads;
                remainderSlices = slices % threads;

                std::vector<std::thread*>
                    threadArray;

                uint16_t
                    index;
                
                uint32_t
                    currentSlice = 0;

                threadArray.resize(threads);
                ParseRange(index, 0, threads, ++index)
                {
                    threadArray[index] =
                        new std::thread(DrawVerticalSlices,
                                        &destination,
                                        &layers_,
                                        currentSlice,
                                        slicesPerCore + (index < remainderSlices),
                                        true);
                    
                    currentSlice += slicesPerCore + (index < remainderSlices);
                }

                ParseRange(index, 0, threads, ++index)
                {
                    threadArray[index]->join();
                }

                ParseRange(index, 0, threads, ++index)
                {
                    delete threadArray[index];
                }

                return true;
            }
        }
    }

    return false;
}

bool TGL::tglImageGenerator::CombineByPastingMT(bool alpha)
{
    return CombineByPastingMT(m_image, alpha);
}

const TGL::tglBitmap &TGL::tglImageGenerator::GetBitmap() const
{
    return m_image;
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Add(TGL::tglBitmap *bitmap, uint16_t count)
{
    for (uint16_t index = 0; index < count; ++index)
    {
        (*this) += bitmap + index;
    }

    return (*this);
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Add(TGL::tglBitmap &bitmap)
{
    return Add(&bitmap);
}

TGL::tglImageGenerator &TGL::tglImageGenerator::Add(const std::vector<TGL::tglBitmap*> &bitmapList)
{
    return (*this) += bitmapList;
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

TGL::tglImageGenerator &TGL::tglImageGenerator::operator +=(const std::vector<TGL::tglBitmap*> &bitmapList)
{
    for (auto &bitmap : bitmapList)
    {
        operator +=(bitmap);
    }

    return *this;
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
