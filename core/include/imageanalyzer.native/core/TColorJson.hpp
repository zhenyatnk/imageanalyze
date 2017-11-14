#pragma once

#include <imageanalyzer.native/core/TColor.hpp>
#include <imageanalyzer.native/nlohmann_json/json.hpp>

#include <memory>

namespace imageanalyzer {
namespace native {
namespace core {

IMAGEANALYZER_CORE_EXPORT void to_json(nlohmann::json& j, const TColor& p);
IMAGEANALYZER_CORE_EXPORT void from_json(const nlohmann::json& j, TColor& p);

}
}
}