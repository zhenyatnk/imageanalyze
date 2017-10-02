#pragma once

#include <imageanalyzer/core/BaseExceptions.hpp>

namespace imageanalyzer {
namespace core {
namespace exceptions {

class image_error
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