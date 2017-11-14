#include <imageanalyzer.native/core/Tasks.hpp>
#include <imageanalyzer.native/core/Tasks.hpp>

#include <threadpoolex/core/ITaskObserver.hpp>

#include <iostream>
#include <chrono>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace native {
namespace core {

class CObserverTaskCounter
    :public EmptyObserverTask
{

public:
    explicit CObserverTaskCounter(std::atomic_int &aCounter);

public:
    virtual void HandleComplete() override;

private:
    std::atomic_int &m_Counter;
};

CObserverTaskCounter::CObserverTaskCounter(std::atomic_int &aCounter)
    :m_Counter(aCounter)
{}

void CObserverTaskCounter::HandleComplete()
{
    ++m_Counter;
}

threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeCounter(std::atomic_int &aCounter)
{
    return std::make_shared<CObserverTaskCounter>(aCounter);
}

}
}
}