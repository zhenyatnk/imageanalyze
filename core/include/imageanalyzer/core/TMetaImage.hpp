#pragma once

#include <imageanalyzer/core/export.hpp>
#include <imageanalyzer/core/TColor.hpp>

#include <array>
#include <memory>

namespace imageanalyzer {
namespace core {

struct IMAGEANALYZER_CORE_EXPORT THistogram
{
public:
    using TContainerColor = std::array<float, 64>;

    THistogram()
        :m_Data({})
    {}

public:
    TContainerColor m_Data;
};

//------------------------------------------------------------
struct IMAGEANALYZER_CORE_EXPORT TMetaImage
{
public:
    using Ptr = std::shared_ptr<TMetaImage>;
    using TContainerHistograms = std::array<THistogram, 9>;
    
public:
    TMetaImage()
        :m_Histograms({})
    {}
    TMetaImage(TMetaImage&& aData)
        :m_Histograms(std::move(aData.m_Histograms))
    {}
    TMetaImage(TContainerHistograms&& aData)
        :m_Histograms(std::move(m_Histograms))
    {}

    TMetaImage(const TMetaImage&) = delete;
    TMetaImage& operator= (const TMetaImage&) = delete;

public:
    TContainerHistograms m_Histograms;
};

}
}