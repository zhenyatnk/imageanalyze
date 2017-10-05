#pragma once

#include <imageanalyzer/core/TMetaImage.hpp>
#include <imageanalyzer/nlohmann_json/json.hpp>

#include <memory>

namespace imageanalyzer {
namespace core {

void to_json(nlohmann::json& j, const TMetaImage& p);
void from_json(const nlohmann::json& j, TMetaImage& p);

void to_json(nlohmann::json& j, const TMetaImage::Ptr& p);
void from_json(const nlohmann::json& j, TMetaImage::Ptr& p);

void to_json(nlohmann::json& j, const THistogram& p);
void from_json(const nlohmann::json& j, THistogram& p);

}
}