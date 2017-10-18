#include <stdio.h>

#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/IDirectoryObject.hpp>

#include <threadpoolex/core/TaskWaiting.hpp>
#include <threadpoolex/core/ITimerActiveObserver.hpp>
#include <threadpoolex/core/ITimerActive.hpp>
#include <iostream>

using namespace imageanalyzer::core;
using namespace threadpoolex::core;


namespace
{
    class CObserverPrintProgress
        :public EmptyObserverTimer
    {
    public:
        CObserverPrintProgress(uint32_t aCount, std::atomic_int &aCurrent)
            :m_Count(aCount), m_Current(aCurrent)
        {}

        void HandleCheck() override
        {
            std::cout << "Progress: " << (m_Current*100) / m_Count << "%" << std::endl;
        }
        void HandleClose() override
        {
            std::cout << "Progress: " << (m_Current * 100) / m_Count << "%" << std::endl;
        }

    private:
        uint32_t m_Count;
        std::atomic_int &m_Current;
    };
    //-----------------------------------------------------------------------------
    class CObserverTryExpansion
        :public EmptyObserverTimer
    {
    public:
        CObserverTryExpansion(IThreadPool::Ptr aThreadPool)
            :m_ThreadPool(aThreadPool)
        {}

        void HandleCheck() override
        {
            m_ThreadPool->TryExpansion();
        }

    private:
        IThreadPool::Ptr m_ThreadPool;
    };
}


std::future<void> AddToThreadPool(ITask::Ptr aTask, const std::vector<IObserverTask::Ptr>& aObservers, IThreadPool::Ptr aThreadPool)
{
    std::promise<void> lPromise;

    for(auto& lObserver: aObservers)
        aTask->AddObserver(lObserver);

    auto lFinish = lPromise.get_future();
    aThreadPool->AddTask(CreateWaitingTask(aTask, std::move(lPromise)));
    return lFinish;
}

int main(int ac, char** av)
{
    if (ac > 1)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        std::atomic_int lCountComplete = 0;
        std::vector<std::future<void>> lFinishs;
        IDirectoryObject::Ptr lTestCollection = CreateDirectoryObject(CPathName(av[1]));
        auto lFiles = lTestCollection->GetFiles();
        if (!lFiles->empty())
        {
            ITimerActive::Ptr lTimer = CreateTimerActive(1000);
            lTimer->AddObserver(std::make_shared<CObserverPrintProgress>(lFiles->size(), lCountComplete));

            ITimerActive::Ptr lTimerFiles = CreateTimerActive(1000);
            lTimerFiles->AddObserver(std::make_shared<CObserverTryExpansion>(ThreadPoolGlobal::GetInstance()()));

            for (auto lFile : *lFiles)
                lFinishs.push_back(AddToThreadPool(CreateTaskAnalyzeInFile(lFile->GetName()),
                { CreateObserverImgAnalyzeCounter(lCountComplete),
                    CreateObserverImgAnalyzeOnlyError(lFile->GetName()) }, ThreadPoolGlobal::GetInstance()()));

            for (auto& lFinish : lFinishs)
                lFinish.wait();
        }

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time analyze: '"
            << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
            << "' s.\n";
    }

    return 0;
}