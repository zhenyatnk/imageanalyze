#include <imageanalyzer/core/TColorJson.hpp>
#include <imageanalyzer/core/TMetaImageJson.hpp>

namespace imageanalyzer {
namespace core {

void to_json(nlohmann::json& j, const TColor& p)
{
    j = p.To_RGBA();
}

void from_json(const nlohmann::json& j, TColor& p) {
    p = TColor::FromRGBA(j.get<unsigned long>());
}

void to_json(nlohmann::json& j, const TMetaImage& p)
{
    j = p.m_Data;
}

void from_json(const nlohmann::json& j, TMetaImage& p) {
    p.m_Data = j.get<TMetaImage::TypeData>();
}

}
}