#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/TaskAnalyzeExceptions.hpp>
#include <imageanalyzer/core/TRectangle.hpp>
#include <imageanalyzer/core/TMetaImage.hpp>
#include <imageanalyzer/core/TMetaImageJson.hpp>

#include <threadpoolex/core/TaskWaiting.hpp>
#include <threadpoolex/core/RAII.hpp>

#include <mutex>
#include <fstream>
#include <future>
#include <vector>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace core {

class CTaskAnalyzeBlockImage
    :public ITask, virtual CBaseObservableTask
{
public:
    CTaskAnalyzeBlockImage(IImage::Ptr aImage, const TRectangle &aRectangle, THistogram& aResult);

    virtual void Execute() override;

protected:
    uint8_t GetRegion(const uint8_t& aBasis);
    uint8_t GetRegion(const TColor& aColor);

private:
    IImage::Ptr m_Image;
    TRectangle m_Rectangle;
    THistogram& m_Result;
};

CTaskAnalyzeBlockImage::CTaskAnalyzeBlockImage(IImage::Ptr aImage, const TRectangle &aRectangle, THistogram& aResult)
    :m_Image(aImage), m_Rectangle(aRectangle), m_Result(aResult)
{}

void CTaskAnalyzeBlockImage::Execute()
{
    CRAII<CObservableTask::Ptr> l(this->GetObserver(), [](CObservableTask::Ptr aObserver) { aObserver->NotifyStart(); },
        [](CObservableTask::Ptr aObserver) { aObserver->NotifyComplete(); });

    auto lPixels = m_Image->GetColors(m_Rectangle);

    for (uint32_t iY = 0; iY < m_Rectangle.m_Size.m_Height; ++iY)
        for (uint32_t iX = 0; iX < m_Rectangle.m_Size.m_Width; ++iX)
            ++m_Result.m_Data[GetRegion(TColor::FromRGB(lPixels->GetElement<uint32_t>(iY*m_Rectangle.m_Size.m_Width + iX)))];

    auto countPixels = m_Rectangle.m_Size.m_Height * m_Rectangle.m_Size.m_Width;
    for (auto& lRegion : m_Result.m_Data)
        lRegion = 100 * lRegion / countPixels;
}

uint8_t CTaskAnalyzeBlockImage::GetRegion(const uint8_t& aBasis)
{
    if (aBasis >= 0 && aBasis < 64)  return 0;
    else if (aBasis >= 64 && aBasis < 128) return 1;
    else if (aBasis >= 128 && aBasis < 192) return 2;
    else if (aBasis >= 192 && aBasis < 256) return 3;
    else
        THROW_ERROR(exceptions::task_analyze_error, "Can't convert value='" + std::to_string(aBasis) + "' to region.");
    return 0;
}

uint8_t CTaskAnalyzeBlockImage::GetRegion(const TColor& aColor)
{
    return GetRegion(aColor.m_Red) * 16 + GetRegion(aColor.m_Green) * 4 + GetRegion(aColor.m_Blue);
}
//-------------------------------------------------------------------------
ITask::Ptr CreateTaskAnalyzeBlock(IImage::Ptr aImage, const TRectangle &aRectangle, THistogram& aResult)
{
    return std::make_shared<CTaskAnalyzeBlockImage>(aImage, aRectangle, aResult);
}

}
}
