#pragma once

#include <imageanalyzer/core/TColor.hpp>

#include <array>
#include <memory>

namespace imageanalyzer {
namespace core {

struct TMetaImage
{
public:
    using Ptr = std::shared_ptr<TMetaImage>;
    using TypeData = std::array<TColor, 64>;
    
public:
    TMetaImage() = default;
    TMetaImage(TMetaImage&& aData)
        :m_Data(std::move(aData.m_Data))
    {}
    TMetaImage(TypeData&& aData)
        :m_Data(std::move(aData))
    {}

    TMetaImage(const TMetaImage&) = delete;
    TMetaImage& operator= (const TMetaImage&) = delete;

public:
    TypeData m_Data;
};

}
}
