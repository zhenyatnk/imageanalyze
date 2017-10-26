#pragma once

#include <imageanalyzer/core/export.hpp>
#include <threadpoolex/core/BaseExceptions.hpp>
#include <stdexcept>

namespace imageanalyzer {
namespace core {
namespace exceptions {

class IMAGEANALYZER_CORE_EXPORT imageanalyzer_error_base
    :public exceptions_base::error_base
{
public:
    imageanalyzer_error_base(const std::string &aMessage, const int &aErrorCode)
        :exceptions_base::error_base(aMessage, aErrorCode)
    {}
};

}
}
}
