#include <stdio.h>

#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/IDirectoryObject.hpp>

#include <threadpoolex/core/TaskWaiting.hpp>
#include <iostream>

using namespace imageanalyzer::core;

std::future<void> AddToThreadPool(threadpoolex::core::ITask::Ptr aTask)
{
    std::promise<void> lPromise;
    auto lFinish = lPromise.get_future();
    ThreadPools_Analyzers::GetInstance().GetPoolForFiles()->AddTask(threadpoolex::core::CreateWaitingTask(aTask, std::move(lPromise)));
    return lFinish;
}

int main(int ac, char** av)
{
    if (ac > 1)
    {
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        std::vector<std::future<void>> lFinishs;

        IDirectoryObject::Ptr lTestCollection = CreateDirectoryObject(CPathName(av[1]));
        auto lFiles = lTestCollection->GetFiles();
        auto lDirs = lTestCollection->GetDirectories();
        for(auto lFile : *lFiles)
            lFinishs.push_back(AddToThreadPool(CreateTaskAnalyzeInFile(lFile->GetName())));

        for(auto& lFinish: lFinishs)
            lFinish.wait();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time analyze: '"
            << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
            << "' s.\n";
    }
    return 0;
}