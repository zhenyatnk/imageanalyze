#pragma once

#include <imageanalyzer/core/TColor.hpp>
#include <imageanalyzer/nlohmann_json/json.hpp>

#include <memory>

namespace imageanalyzer {
namespace core {

void to_json(nlohmann::json& j, const TColor& p);
void from_json(const nlohmann::json& j, TColor& p);

}
}
