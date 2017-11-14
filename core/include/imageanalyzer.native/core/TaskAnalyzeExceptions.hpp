#pragma once

#include <imageanalyzer.native/core/BaseExceptions.hpp>

#include <threadpoolex/core/ITaskExceptions.hpp>

namespace imageanalyzer {
namespace native {
namespace core {
namespace exceptions {

class IMAGEANALYZER_CORE_EXPORT task_analyze_error
    :public threadpoolex::core::exceptions::task_error
{
public:
    task_analyze_error(const std::string &aMessage, const int &aErrorCode)
        :threadpoolex::core::exceptions::task_error("Task analyzer error: \'" + aMessage + "\'", aErrorCode)
    {}
};

}
}
}
}