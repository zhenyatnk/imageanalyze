#pragma once

#include <imageanalyzer/core/CFileName.hpp>
#include <imageanalyzer/core/IImage.hpp>

#include <threadpoolex/core/ITask.hpp>
#include <threadpoolex/core/IThreadPool.hpp>
#include <threadpoolex/core/TSingleton.hpp>

#include <future>

namespace imageanalyzer {
namespace core {

class ThreadPools_Analyzers
{
public:
    static ThreadPools_Analyzers& GetInstance()
    {
        static ThreadPools_Analyzers gSingleton;
        return gSingleton;
    }

public:
    ThreadPools_Analyzers(const ThreadPools_Analyzers&) = delete;
    ThreadPools_Analyzers& operator = (const ThreadPools_Analyzers&) = delete;

    threadpoolex::core::IThreadPool::Ptr GetPoolForFiles() const
    {
        return m_PoolForFiles;
    }
    threadpoolex::core::IThreadPool::Ptr GetPoolForBlocks() const
    {
        return m_PoolForBlocks;
    }

private:
    ThreadPools_Analyzers()
        :m_PoolForFiles(threadpoolex::core::CreateThreadPool(1, threadpoolex::core::CreateExpansionToMax(9))),
        m_PoolForBlocks(threadpoolex::core::CreateThreadPool(9, threadpoolex::core::CreateExpansionToMax(45)))
    {}

    ~ThreadPools_Analyzers()
    {
        m_PoolForFiles.reset();
        m_PoolForBlocks.reset();
    }

private:
    threadpoolex::core::IThreadPool::Ptr m_PoolForFiles;
    threadpoolex::core::IThreadPool::Ptr m_PoolForBlocks;
};

threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(const CFileName &aFileNae);
threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(IImage::Ptr aImage, const CFileName &aFileResult);

threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeAll(const CFileName &aFileName);
threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeCounter(std::atomic_int &aCounter);
threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeOnlyError(const CFileName &aFileName);

}
}
