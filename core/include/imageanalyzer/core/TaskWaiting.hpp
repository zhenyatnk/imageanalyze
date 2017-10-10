#pragma once

#include <threadpoolex/core/ITask.hpp>

#include <future>

namespace imageanalyzer {
namespace core {

threadpoolex::core::ITask::Ptr CreateWaitingTask(threadpoolex::core::ITask::Ptr aTask, std::promise<void> &&aPromise);

}
}
