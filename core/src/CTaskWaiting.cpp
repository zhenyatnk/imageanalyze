#include <imageanalyzer/core/TaskWaiting.hpp>

namespace imageanalyzer {
namespace core {

class CTaskWaiting
    :public threadpoolex::core::ITask
{
public:
    CTaskWaiting(threadpoolex::core::ITask::Ptr aTask, std::promise<void> &&aPromise);

    virtual void Execute() override;

private:
    threadpoolex::core::ITask::Ptr m_Task;
    std::promise<void> m_Promise;
};

CTaskWaiting::CTaskWaiting(threadpoolex::core::ITask::Ptr aTask, std::promise<void> &&aPromise)
    :m_Task(aTask), m_Promise(std::move(aPromise))
{}

void CTaskWaiting::Execute()
{
    m_Task->Execute();
    m_Promise.set_value();
}

threadpoolex::core::ITask::Ptr CreateWaitingTask(threadpoolex::core::ITask::Ptr aTask, std::promise<void> &&aPromise)
{
    return std::make_shared<CTaskWaiting>(aTask, std::move(aPromise));
}

}
}
