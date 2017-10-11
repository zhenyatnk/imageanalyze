#pragma once

#include <imageanalyzer/core/BaseExceptions.hpp>

namespace imageanalyzer {
namespace core {
namespace exceptions {

class task_error
    :public imageanalyzer_error_base
{
public:
    task_error(const std::string &aMessage, const int &aErrorCode)
        :imageanalyzer_error_base("Task analyzer error: \'" + aMessage + "\'", aErrorCode)
    {}
};

}
}
}
