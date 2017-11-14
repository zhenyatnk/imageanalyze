#pragma once

#include <imageanalyzer.native/core/export.hpp>
#include <imageanalyzer.native/core/BaseExceptions.hpp>

namespace imageanalyzer {
namespace native {
namespace core {
namespace exceptions {

class IMAGEANALYZER_CORE_EXPORT stream_error
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
}