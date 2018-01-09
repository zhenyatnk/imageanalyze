#pragma once

#include <imageanalyzer.native/core/TColor.hpp>
#include <imageanalyzer.native/core/TSize.hpp>
#include <imageanalyzer.native/core/TPoint.hpp>
#include <imageanalyzer.native/core/TRectangle.hpp>
#include <imageanalyzer.native/core/IImageExceptions.hpp>
#include <baseex/core/IStream.hpp>
#include <baseex/core/CFileName.hpp>

#include <memory>

namespace imageanalyzer {
namespace native {
namespace core {

class IMAGEANALYZER_CORE_EXPORT IImage
{
public:
    using Ptr = std::shared_ptr<IImage>;

public:
    virtual ~IImage() = default;

    virtual TColor GetColor(const TPoint&) = 0;
    virtual baseex::core::IStreamBuffer::Ptr GetColors(const TRectangle&) = 0;
    virtual TSize GetSize() = 0;
};

IMAGEANALYZER_CORE_EXPORT IImage::Ptr CreateImage(const baseex::core::CFileName& aFileName);

}
}
}