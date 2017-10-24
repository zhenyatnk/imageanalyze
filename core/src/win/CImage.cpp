#include <imageanalyzer/core/IImage.hpp>
#include <imageanalyzer/core/RAII.hpp>
#include <imageanalyzer/core/Unicode.hpp>

#include <objidl.h>
#include <gdiplus.h>
#include <mutex>

using namespace Gdiplus;

namespace imageanalyzer {
namespace core {

namespace {

class GDI_initializer
    :public IRAII
{
public:
    GDI_initializer()
    {
        CHECK_THROW_OTHER_ERR(GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL), 
                             Status::Ok, exceptions::image_error, "Can't initializing GDI Plus");
    }

    ~GDI_initializer()
    {
        GdiplusShutdown(m_GdiplusToken);
    }

private:
    GdiplusStartupInput m_GdiplusStartupInput;
    ULONG_PTR m_GdiplusToken;
};

std::wstring s2ws(const std::string& aString)
{
    int lSizeNeeded = MultiByteToWideChar(CP_UTF8, 0, &aString[0], (int)aString.size(), NULL, 0);
    std::wstring wstrTo(lSizeNeeded, 0);
    MultiByteToWideChar(CP_UTF8, 0, &aString[0], (int)aString.size(), &wstrTo[0], lSizeNeeded);
    return wstrTo;
}

}
//------------------------------------------------------------------------------------------------
class CImage
    :public IImage
{
public:
    CImage(const CFileName& aFileName);

    virtual TColor GetColor(const TPoint &aPixel) override;
    virtual ILinearStream::Ptr GetColors(const TRectangle& aPixels) override;
    virtual TSize GetSize() override;

protected:
    std::shared_ptr<Bitmap> GetImage();

private:
    GDI_initializer m_GDI;
    CFileName m_FileName;
    std::shared_ptr<Bitmap> m_FileImage;
    std::mutex m_GetColor;
};

CImage::CImage(const CFileName& aFileName)
    :m_FileName(aFileName)
{}

TColor CImage::GetColor(const TPoint &aPixel)
{
    Color lPixel;
    {
        std::lock_guard<std::mutex> l(m_GetColor);
        CHECK_THROW_OTHER_ERR(GetImage()->GetPixel(aPixel.m_X, aPixel.m_Y, &lPixel),
            Status::Ok, exceptions::image_error, "Can't get color for pixel for file=" + convert(m_FileName.GetFullFileName()));
    }
    return TColor(lPixel.GetAlpha(), lPixel.GetRed(), lPixel.GetGreen(), lPixel.GetBlue());
}

ILinearStream::Ptr CImage::GetColors(const TRectangle& aPixels)
{
    ILinearWriteStream::Ptr lResult;
    {
        std::lock_guard<std::mutex> l(m_GetColor);
        auto lBlockBitmap = std::make_shared<BitmapData>();
        Rect rect(aPixels.m_Left.m_X, aPixels.m_Left.m_Y, aPixels.m_Size.m_Width, aPixels.m_Size.m_Height);
        CHECK_THROW_OTHER_ERR(GetImage()->LockBits(&rect, ImageLockModeRead, PixelFormat32bppARGB, lBlockBitmap.get()),
            Status::Ok, exceptions::image_error, "Can't lock block color pixel for file=" + convert(m_FileName.GetFullFileName()));

        lResult = CreateLinearWriteBuffer(aPixels.m_Size.m_Width * aPixels.m_Size.m_Height * sizeof(uint32_t));
        for (uint32_t iY = 0; iY < aPixels.m_Size.m_Height; ++iY)
            memcpy(lResult->GetBuff<uint32_t*>() + iY*aPixels.m_Size.m_Width, (uint8_t*)lBlockBitmap->Scan0 + iY*lBlockBitmap->Stride, aPixels.m_Size.m_Width*sizeof(uint32_t));

        CHECK_THROW_OTHER_ERR(GetImage()->UnlockBits(lBlockBitmap.get()),
            Status::Ok, exceptions::image_error, "Can't unlock block color pixel for file=" + convert(m_FileName.GetFullFileName()));
    }
    return lResult;
}

TSize CImage::GetSize()
{
    return TSize(GetImage()->GetWidth(), GetImage()->GetHeight());
}

std::shared_ptr<Bitmap> CImage::GetImage()
{
    if (!m_FileImage)
    {
        m_FileImage = std::shared_ptr<Bitmap>(Bitmap::FromFile(m_FileName.GetFullFileName().c_str()));
        CHECK_THROW_OTHER_ERR(m_FileImage->GetLastStatus(),
            Status::Ok, exceptions::image_error, "Can't open image file=" + convert(m_FileName.GetFullFileName()));
    }
    
    return m_FileImage;
}

IImage::Ptr CreateImage(const CFileName& aFileName)
{
    return std::make_shared<CImage>(aFileName);
}

}
}
