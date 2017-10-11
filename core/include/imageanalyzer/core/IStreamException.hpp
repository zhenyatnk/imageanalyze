#pragma once

#include <imageanalyzer/core/BaseExceptions.hpp>

namespace imageanalyzer {
namespace core {
namespace exceptions {

class stream_error
    :public imageanalyzer_error_base
{
public:
    stream_error(const std::string &aMessage, const int &aErrorCode)
        :imageanalyzer_error_base("IStream error: \'" + aMessage + "\'", aErrorCode)
    {}
};

}
}
}
