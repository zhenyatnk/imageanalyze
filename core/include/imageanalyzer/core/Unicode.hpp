#pragma once

#include <imageanalyzer/core/export.hpp>

#include <string>

namespace imageanalyzer {
namespace core {

IMAGEANALYZER_CORE_EXPORT std::string convert(const std::wstring&);
IMAGEANALYZER_CORE_EXPORT std::wstring convert(const std::string&);

}
}
