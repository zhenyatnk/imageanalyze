#pragma once

#include <imageanalyzer/core/TColor.hpp>
#include <imageanalyzer/core/TSize.hpp>
#include <imageanalyzer/core/TPoint.hpp>
#include <imageanalyzer/core/TRectangle.hpp>
#include <imageanalyzer/core/IStream.hpp>
#include <imageanalyzer/core/CFileName.hpp>
#include <imageanalyzer/core/IImageExceptions.hpp>

#include <memory>

namespace imageanalyzer {
namespace core {

class IImage
{
public:
    using Ptr = std::shared_ptr<IImage>;

public:
    virtual ~IImage() = default;

    virtual TColor GetColor(const TPoint&) = 0;
    virtual ILinearStream::Ptr GetColors(const TRectangle&) = 0;
    virtual TSize GetSize() = 0;
};

IImage::Ptr CreateImage(const CFileName& aFileName);

}
}
