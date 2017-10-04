#pragma once

#include <imageanalyzer/core/TMetaImage.hpp>

#include <memory>

namespace imageanalyzer {
namespace core {

class IMetaComparator
{
public:
    using Ptr = std::shared_ptr<IMetaComparator>;

public:
    virtual ~IMetaComparator() = default;

    virtual double GePercentEqual(const TMetaImage&, const TMetaImage&) const = 0;
    virtual double GePercentEqual(TMetaImage::Ptr aLeft, TMetaImage::Ptr aRight) const
    {
        return GePercentEqual(*aLeft, *aRight);
    }
};

IMetaComparator::Ptr CreateEuclideanDistance();

}
}
