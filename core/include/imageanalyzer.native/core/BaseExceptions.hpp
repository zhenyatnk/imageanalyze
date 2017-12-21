#pragma once

#include <imageanalyzer.native/core/export.hpp>
#include <baseex/core/BaseExceptions.hpp>
#include <stdexcept>

namespace imageanalyzer {
namespace native {
namespace core {
namespace exceptions {

class IMAGEANALYZER_CORE_EXPORT imageanalyzer_error_base
    :public baseex::core::exceptions_base::error_base
{
public:
    imageanalyzer_error_base(const std::string &aMessage, const int &aErrorCode)
        :baseex::core::exceptions_base::error_base(aMessage, aErrorCode)
    {}
};

}
}
}
}
