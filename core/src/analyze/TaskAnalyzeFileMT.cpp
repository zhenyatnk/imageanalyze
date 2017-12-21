#include <imageanalyzer.native/core/Tasks.hpp>
#include <imageanalyzer.native/core/TaskAnalyzeExceptions.hpp>
#include <imageanalyzer.native/core/TRectangle.hpp>
#include <imageanalyzer.native/core/TMetaImage.hpp>
#include <imageanalyzer.native/core/TMetaImageJson.hpp>
#include <imageanalyzer.native/core/Unicode.hpp>

#include <threadpoolex/core/ITaskWait.hpp>

#include <baseex/core/RAII.hpp>

#include <mutex>
#include <fstream>
#include <future>
#include <vector>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace native {
namespace core {
//---------------------------------------------------------------------------
class CTaskAnalyzeFileMT
    :public ITask, virtual CBaseObservableTask
{
public:
    CTaskAnalyzeFileMT(const baseex::core::CFileName &aImageName, const baseex::core::CFileName &aFileResult, IThreadPool::WPtr aThreadPool);

    virtual void Execute() override;

protected:
    std::vector<TRectangle> GetBlocksAnalyze(IImage::Ptr aImage, TSize aSizeAnalyze, uint8_t aX, uint8_t aY);
    IWait::Ptr AddTaskToThreadPool(ITask::Ptr);

private:
    baseex::core::CFileName m_ImageName;
    baseex::core::CFileName m_FileResult;
    IThreadPool::WPtr m_ThreadPool;
};

CTaskAnalyzeFileMT::CTaskAnalyzeFileMT(const baseex::core::CFileName &aImageName, const baseex::core::CFileName &aFileResult, IThreadPool::WPtr aThreadPool)
    :m_ImageName(aImageName), m_FileResult(aFileResult), m_ThreadPool(aThreadPool)
{}

void CTaskAnalyzeFileMT::Execute()
{
    try
    {
        baseex::core::CRAII<CObservableTask::Ptr> l(this->GetObserver(), [](CObservableTask::Ptr aObserver) { aObserver->NotifyStart(); },
            [](CObservableTask::Ptr aObserver) { aObserver->NotifyComplete(); });

        TMetaImage lResult;
        {
            IImage::Ptr lImage = CreateImage(m_ImageName);
            auto lBlocks = GetBlocksAnalyze(lImage, lImage->GetSize(), 3, 3);
            std::vector<IWait::Ptr> lWaits;

            for (uint32_t index = 0; index < lBlocks.size(); ++index)
                lWaits.push_back(AddTaskToThreadPool(CreateTaskAnalyzeBlock(lImage, lBlocks[index], lResult.m_Histograms[index])));

            for (auto& lWait : lWaits)
                lWait->Wait();
        }
        std::ofstream lFileJson(m_FileResult.GetFullFileName());
        lFileJson << nlohmann::json(lResult) << std::endl;
    }
    CATCH_CODE_ERROR(baseex::core::exceptions_base::error_base, this->GetObserver()->NotifyError);
}

std::vector<TRectangle> CTaskAnalyzeFileMT::GetBlocksAnalyze(IImage::Ptr aImage, TSize aSizeAnalyze, uint8_t aX, uint8_t aY)
{
    std::vector<TRectangle> lResult;

    TSize lSizeBlock(aImage->GetSize().m_Width / aX, aImage->GetSize().m_Height / aY);
    for (auto iY = 0; iY < aY; ++iY)
        for (auto iX = 0; iX < aX; ++iX)
            lResult.push_back(TRectangle(TPoint(lSizeBlock.m_Width*iX, lSizeBlock.m_Height * iY), lSizeBlock));

    for (auto iY = 0; iY < aY; ++iY)
        lResult[iY*aX + aX - 1].m_Size.m_Width = aSizeAnalyze.m_Width - lResult[iY * aX + aX - 1].m_Left.m_X;

    for (auto iX = 0; iX < aX; ++iX)
        lResult[(aY - 1)*aX + iX].m_Size.m_Height = aSizeAnalyze.m_Height - lResult[(aY - 1)*aX + iX].m_Left.m_Y;

    return lResult;
}

IWait::Ptr CTaskAnalyzeFileMT::AddTaskToThreadPool(ITask::Ptr aTask)
{
    auto lThreadPool = m_ThreadPool.lock();
    CHECK_THROW_BOOL(!!lThreadPool, exceptions::task_analyze_error, "Can't execute MT task, thread pool already destroy. FileResult:'" + convert(m_FileResult.GetFullFileName()) + "'");

    IWait::Ptr lWait;
    lThreadPool->AddTask(CreateTaskWait(aTask, lWait));
    return lWait;
}
//-------------------------------------------------------------------------
ITask::Ptr CreateTaskAnalyzeInFileMT(const baseex::core::CFileName &aFileName, IThreadPool::WPtr aThreadPool)
{
    return CreateTaskAnalyzeInFileMT(aFileName, baseex::core::CFileName(aFileName.GetFullFileName() + L".data"), aThreadPool);
}
ITask::Ptr CreateTaskAnalyzeInFileMT(const baseex::core::CFileName &aFileName, const baseex::core::CFileName &aFileResult, IThreadPool::WPtr aThreadPool)
{
    return std::make_shared<CTaskAnalyzeFileMT>(aFileName, aFileResult, aThreadPool);
}

}
}
}