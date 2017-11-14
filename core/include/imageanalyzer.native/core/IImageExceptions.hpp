#pragma once

#include <imageanalyzer.native/core/BaseExceptions.hpp>

namespace imageanalyzer {
namespace native {
namespace core {
namespace exceptions {

class IMAGEANALYZER_CORE_EXPORT image_error
    :public exceptions::imageanalyzer_error_base
{
public:
    image_error(const std::string &aMessage, const int &aErrorCode)
        :imageanalyzer_error_base("Image error: " + aMessage, aErrorCode)
    {}
};

}
}
}
}