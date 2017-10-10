#include <stdio.h>

#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/TaskWaiting.hpp>

using namespace imageanalyzer::core;

int main(int ac, char** av)
{
    if (ac > 1)
    {
        std::promise<void> lPromise;
        auto lFinish = lPromise.get_future();
        ThreadPools_Analyzers::GetInstance().GetPoolForFiles()->AddTask(CreateWaitingTask(CreateTaskAnalyzeInFile(CFileName(av[1])), std::move(lPromise)));
        
        lFinish.wait();
    }

    return 0;
}