#pragma once
#include <imageanalyzer.native/core/export.hpp>
#include <imageanalyzer.native/core/TMetaImage.hpp>

#include <memory>

namespace imageanalyzer {
namespace native {
namespace core {

class IMAGEANALYZER_CORE_EXPORT IMetaComparator
{
public:
    using Ptr = std::shared_ptr<IMetaComparator>;

public:
    virtual ~IMetaComparator() = default;

    virtual float GePercentEqual(const TMetaImage&, const TMetaImage&) const = 0;
    virtual float GePercentEqual(TMetaImage::Ptr aLeft, TMetaImage::Ptr aRight) const
    {
        return GePercentEqual(*aLeft, *aRight);
    }
};

IMAGEANALYZER_CORE_EXPORT IMetaComparator::Ptr CreateEuclideanDistance();

}
}
}