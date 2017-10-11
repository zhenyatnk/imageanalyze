#include <stdio.h>

#include <imageanalyzer/core/Tasks.hpp>
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

        CPathName lPath("e:/test_collection");
        for (auto index = 1; index <= 100; ++index)
            lFinishs.push_back(AddToThreadPool(CreateTaskAnalyzeInFile(CFileName(lPath, std::to_string(index) + ".jpg"))));

        //ThreadPools_Analyzers::GetInstance().GetPoolForFiles()->AddTask(threadpoolex::core::CreateWaitingTask(CreateTaskAnalyzeInFile(CFileName(av[1])), std::move(lPromise)));
        for(auto& lFinish: lFinishs)
            lFinish.wait();

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Time "
            << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
            << "us.\n";
    }
    return 0;
}