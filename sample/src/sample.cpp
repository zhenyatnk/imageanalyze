#include <stdio.h>

#include <imageanalyzer/core/Tasks.hpp>

using namespace imageanalyzer::core;

int main(int ac, char** av)
{
    if (ac > 1)
        ThreadPool_Files::GetInstance()()->AddTask(CreateTaskAnalyzeInFile(CFileName(av[1])));

    getchar();

    return 0;
}