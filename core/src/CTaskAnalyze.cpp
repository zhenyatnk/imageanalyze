#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/TRectangle.hpp>
#include <imageanalyzer/core/TMetaImage.hpp>
#include <imageanalyzer/core/TMetaImageJson.hpp>

#include <threadpoolex/core/TNotifier.hpp>

#include <mutex>
#include <fstream>
#include <vector>

namespace imageanalyzer {
namespace core {


class CTaskAnalyzeBlockImage
    :public threadpoolex::core::ITask
{
public:
    CTaskAnalyzeBlockImage(IImage::Ptr aImage, const TRectangle &aRectangle, std::shared_ptr<threadpoolex::core::TNotifier<void>> aComplete, THistogram& aResult);

    virtual void Execute() override;

protected:
    uint8_t GetRegion(const uint8_t& aBasis);
    uint8_t GetRegion(const TColor& aColor);

private:
    IImage::Ptr m_Image;
    TRectangle m_Rectangle;
    std::shared_ptr<threadpoolex::core::TNotifier<void>> m_Complete;
    THistogram& m_Result;
};

CTaskAnalyzeBlockImage::CTaskAnalyzeBlockImage(IImage::Ptr aImage, const TRectangle &aRectangle, std::shared_ptr<threadpoolex::core::TNotifier<void>> aComplete, THistogram& aResult)
    :m_Image(aImage), m_Rectangle(aRectangle), m_Complete(aComplete), m_Result(aResult)
{
}

void CTaskAnalyzeBlockImage::Execute()
{
    for (auto iY = 0; iY < m_Rectangle.m_Size.m_Height; ++iY)
        for (auto iX = 0; iX < m_Rectangle.m_Size.m_Width; ++iX)
            ++m_Result.m_Data[GetRegion(m_Image->GetColor(m_Rectangle.m_Left + TPoint(iX, iY)))];
    
    auto countPixels = m_Rectangle.m_Size.m_Height * m_Rectangle.m_Size.m_Width;
    for (auto& lRegion : m_Result.m_Data)
        lRegion = 100 * lRegion / countPixels;

    m_Complete->notify_one();
}

uint8_t CTaskAnalyzeBlockImage::GetRegion(const uint8_t& aBasis)
{
    if      (aBasis >= 0   && aBasis < 64)  return 0;
    else if (aBasis >= 64  && aBasis < 128) return 1;
    else if (aBasis >= 128 && aBasis < 192) return 2;
    else if (aBasis >= 192 && aBasis < 256) return 3;
    else
        throw std::exception("Несоответсвие типа цвета: тип составляющей цвета превышает 8 бит");
    return 0;
}

uint8_t CTaskAnalyzeBlockImage::GetRegion(const TColor& aColor)
{
    return GetRegion(aColor.m_Red) * 16 + GetRegion(aColor.m_Green) * 4 + GetRegion(aColor.m_Blue);
}

//---------------------------------------------------------------------------
class CTaskAnalyzeFile
    :public threadpoolex::core::ITask
{
public:
    CTaskAnalyzeFile(IImage::Ptr aImage, const CFileName &aFileResult);

    virtual void Execute() override;

protected:
    std::vector<TRectangle> GetBlocksAnalyze(TSize aSizeAnalyze, uint8_t aX, uint8_t aY);

private:
    IImage::Ptr m_Image;
    CFileName m_FileResult;
};

CTaskAnalyzeFile::CTaskAnalyzeFile(IImage::Ptr aImage, const CFileName &aFileResult)
    :m_Image(aImage), m_FileResult(aFileResult)
{}

void CTaskAnalyzeFile::Execute()
{
    TMetaImage lResult;
    {
        std::vector<threadpoolex::core::ITask::Ptr> lTasks;
        std::vector < std::shared_ptr<threadpoolex::core::TNotifier<void>>> lCompletings;

        auto lBlocks = GetBlocksAnalyze(m_Image->GetSize(), 3, 3);

        for (auto index = 0; index < lBlocks.size(); ++index)
        {
            lCompletings.push_back(std::make_shared<threadpoolex::core::TNotifier<void>>());
            lTasks.push_back(std::make_shared<CTaskAnalyzeBlockImage>(m_Image, lBlocks[index], lCompletings.back(), lResult.m_Histograms[index]));
        }
        ThreadPool_Blocks::GetInstance()()->AddTasks(lTasks);
        
        for (auto& aNotifier : lCompletings)
            aNotifier->wait();
    }
    std::ofstream lFileJson(m_FileResult.GetFullFileName());
    lFileJson << nlohmann::json(lResult) << std::endl;
}

std::vector<TRectangle> CTaskAnalyzeFile::GetBlocksAnalyze(TSize aSizeAnalyze, uint8_t aX, uint8_t aY)
{
    std::vector<TRectangle> lResult;

    TSize lSizeBlock(m_Image->GetSize().m_Width / aX, m_Image->GetSize().m_Height / aY);
    for (auto iY = 0; iY < aY; ++iY)
        for (auto iX = 0; iX < aX; ++iX)
            lResult.push_back(TRectangle(TPoint(lSizeBlock.m_Width*iX, lSizeBlock.m_Height * iY), lSizeBlock));

    for (auto iY = 0; iY < aY; ++iY)
        lResult[iY*aX + aX - 1].m_Size.m_Width = aSizeAnalyze.m_Width - lResult[iY * aX + aX - 1].m_Left.m_X;

    for (auto iX = 0; iX < aX; ++iX)
        lResult[(aY - 1)*aX + iX].m_Size.m_Height = aSizeAnalyze.m_Height - lResult[(aY - 1)*aX + iX].m_Left.m_Y;

    return lResult;
}

//-------------------------------------------------------------------------

threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(const CFileName &aFileName)
{
    return CreateTaskAnalyzeInFile(CreateImage(aFileName), CFileName(aFileName.GetFullFileName() + ".data"));
}
threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(IImage::Ptr aImage, const CFileName &aFileResult)
{
    return std::make_shared<CTaskAnalyzeFile>(aImage, aFileResult);
}

}
}
