#include <imageanalyzer/core/IImage.hpp>
#include <imageanalyzer/core/RAII.hpp>

#include <objidl.h>
#include <gdiplus.h>

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
    virtual TSize GetSize() override;

protected:
    std::shared_ptr<Bitmap> GetImage();

private:
    GDI_initializer m_GDI;
    CFileName m_FileName;
    std::shared_ptr<Bitmap> m_FileImage;
};

CImage::CImage(const CFileName& aFileName)
    :m_FileName(aFileName)
{}

TColor CImage::GetColor(const TPoint &aPixel)
{
    Color lPixel;
    CHECK_THROW_OTHER_ERR(GetImage()->GetPixel(aPixel.m_X, aPixel.m_Y, &lPixel),
        Status::Ok, exceptions::image_error, "Can't get color for pixel for file=" + m_FileName.GetFullFileName());
    return TColor(lPixel.GetAlpha(), lPixel.GetRed(), lPixel.GetGreen(), lPixel.GetBlue());
}

TSize CImage::GetSize()
{
    return TSize(GetImage()->GetWidth(), GetImage()->GetHeight());
}

std::shared_ptr<Bitmap> CImage::GetImage()
{
    if (!m_FileImage)
    {
        m_FileImage = std::shared_ptr<Bitmap>(Bitmap::FromFile(s2ws(m_FileName.GetFullFileName()).c_str()));
        CHECK_THROW_OTHER_ERR(m_FileImage->GetLastStatus(),
            Status::Ok, exceptions::image_error, "Can't open image file=" + m_FileName.GetFullFileName());
    }
    
    return m_FileImage;
}

IImage::Ptr CreateImage(const CFileName& aFileName)
{
    return std::make_shared<CImage>(aFileName);
}

}
}
