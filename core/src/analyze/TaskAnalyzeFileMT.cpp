#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/TaskAnalyzeExceptions.hpp>
#include <imageanalyzer/core/TRectangle.hpp>
#include <imageanalyzer/core/TMetaImage.hpp>
#include <imageanalyzer/core/TMetaImageJson.hpp>
#include <imageanalyzer/core/Unicode.hpp>

#include <threadpoolex/core/RAII.hpp>
#include <threadpoolex/core/TaskPromise.hpp>

#include <mutex>
#include <fstream>
#include <future>
#include <vector>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace core {
//---------------------------------------------------------------------------
class CTaskAnalyzeFileMT
    :public ITask, virtual CBaseObservableTask
{
public:
    CTaskAnalyzeFileMT(IImage::Ptr aImage, const CFileName &aFileResult, IThreadPool::WPtr aThreadPool);

    virtual void Execute() override;

protected:
    std::vector<TRectangle> GetBlocksAnalyze(TSize aSizeAnalyze, uint8_t aX, uint8_t aY);
    std::future<void> AddTaskToThreadPool(ITask::Ptr);

private:
    IImage::Ptr m_Image;
    CFileName m_FileResult;
    IThreadPool::WPtr m_ThreadPool;
};

CTaskAnalyzeFileMT::CTaskAnalyzeFileMT(IImage::Ptr aImage, const CFileName &aFileResult, IThreadPool::WPtr aThreadPool)
    :m_Image(aImage), m_FileResult(aFileResult), m_ThreadPool(aThreadPool)
{}

void CTaskAnalyzeFileMT::Execute()
{
    try
    {
        CRAII<CObservableTask::Ptr> l(this->GetObserver(), [](CObservableTask::Ptr aObserver) { aObserver->NotifyStart(); },
            [](CObservableTask::Ptr aObserver) { aObserver->NotifyComplete(); });

        TMetaImage lResult;
        {
            auto lBlocks = GetBlocksAnalyze(m_Image->GetSize(), 3, 3);
            std::vector<std::future<void>> lFutures;

            for (uint32_t index = 0; index < lBlocks.size(); ++index)
                lFutures.push_back(AddTaskToThreadPool(CreateTaskAnalyzeBlock(m_Image, lBlocks[index], lResult.m_Histograms[index])));

            for (auto& lFuture : lFutures)
                lFuture.get();
        }
        std::ofstream lFileJson(m_FileResult.GetFullFileName());
        lFileJson << nlohmann::json(lResult) << std::endl;
    }
    CATCH_CODE_ERROR(exceptions_base::error_base, this->GetObserver()->NotifyError);
}

std::vector<TRectangle> CTaskAnalyzeFileMT::GetBlocksAnalyze(TSize aSizeAnalyze, uint8_t aX, uint8_t aY)
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

std::future<void> CTaskAnalyzeFileMT::AddTaskToThreadPool(ITask::Ptr aTask)
{
    auto lThreadPool = m_ThreadPool.lock();
    CHECK_THROW_BOOL(!!lThreadPool, exceptions::task_analyze_error, "Can't execute MT task, thread pool already destroy. FileResult:'" + convert(m_FileResult.GetFullFileName()) + "'");

    std::promise<void> lPromise;
    auto lFuture = lPromise.get_future();
    lThreadPool->AddTask(CreateTaskPromise(aTask, std::move(lPromise)));
    return lFuture;
}
//-------------------------------------------------------------------------
ITask::Ptr CreateTaskAnalyzeInFileMT(const CFileName &aFileName, IThreadPool::WPtr aThreadPool)
{
    return CreateTaskAnalyzeInFileMT(CreateImage(aFileName), CFileName(aFileName.GetFullFileName() + L".data"), aThreadPool);
}
ITask::Ptr CreateTaskAnalyzeInFileMT(IImage::Ptr aImage, const CFileName &aFileResult, IThreadPool::WPtr aThreadPool)
{
    return std::make_shared<CTaskAnalyzeFileMT>(aImage, aFileResult, aThreadPool);
}

}
}
