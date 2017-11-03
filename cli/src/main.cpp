#include <stdio.h>

#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/IDirectoryObject.hpp>
#include <imageanalyzer/core/TMetaImageJson.hpp>
#include <imageanalyzer/core/IMetaComparator.hpp>
#include <imageanalyzer/core/Unicode.hpp>

#include <threadpoolex/core/TaskPromise.hpp>
#include <threadpoolex/core/ITimerActiveObserver.hpp>
#include <threadpoolex/core/ITimerActive.hpp>
#include <iostream>
#include <fstream>

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
    aThreadPool->AddTask(CreateTaskPromise(aTask, std::move(lPromise)));
    return lFinish;
}

void command_analyze(const CPathName& aPathName)
{
    std::atomic_int lCountComplete = 0;
    std::vector<std::future<void>> lFinishs;
    IDirectoryObject::Ptr lDirectory = CreateDirectoryObject(aPathName);
    auto lFiles = lDirectory->GetFiles(L"*.jpg");
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

}

void command_compare(const CFileName& aFileName, const CPathName& aPathName)
{
    IDirectoryObject::Ptr lDirectory = CreateDirectoryObject(aPathName);
    auto lFiles = lDirectory->GetFiles(L"*.data");
    if (!lFiles->empty())
    {
        std::multimap<float, std::wstring> lResultFind;
        auto lAnalyzeTask = CreateTaskAnalyzeInFile(aFileName);
        lAnalyzeTask->AddObserver(CreateObserverImgAnalyzeOnlyError(aFileName));
        lAnalyzeTask->Execute();
        
        std::ifstream data_(CFileName(aFileName.GetFullFileName() + L".data").GetFullFileName());
        if (!data_.is_open())
            return;
        nlohmann::json j_data;
        data_ >> j_data;
        auto lMetaFind = j_data.get<TMetaImage>();

        for (auto lFile : *lFiles)
        {
            auto lFullFileName = lFile->GetName().GetFullFileName();
            std::ifstream data(lFullFileName);
            nlohmann::json j_data;
            data >> j_data;
            lResultFind.insert(std::make_pair(CreateEuclideanDistance()->GePercentEqual(lMetaFind, j_data.get<TMetaImage>()), lFullFileName));
        }
        
        auto lCount = 0;
        for (auto lResult = lResultFind.rbegin(); lCount != 15 && lResult != lResultFind.rend(); ++lCount, ++lResult)
            std::wcout << (uint16_t)lResult->first << L"%\tFileName: '" << lResult->second << L"'" << std::endl;
    }
}

int main(int ac, char** av)
{
    std::locale::global(std::locale(""));
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    if      (ac > 2 && std::string("analyze") == av[1])   command_analyze(CPathName(convert(av[2])));
    else if (ac > 3 && std::string("compare") == av[1])   command_compare(CFileName(convert(av[2])), CPathName(convert(av[3])));
    else
        ;
    std::cout << "Time process operation: '"
        << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count()
        << "' s.\n" << std::endl;

    return 0;
}
