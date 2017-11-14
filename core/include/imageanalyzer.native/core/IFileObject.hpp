#pragma once

#include <imageanalyzer.native/core/CFileName.hpp>

#include <vector>
#include <memory>

namespace imageanalyzer {
namespace native {
namespace core {

class IMAGEANALYZER_CORE_EXPORT IFileObject
{
public:
    using Ptr = std::shared_ptr<IFileObject>;
    using ListPtr = std::shared_ptr<std::vector<Ptr>>;

public:
    virtual CFileName GetName() const = 0;
};

IMAGEANALYZER_CORE_EXPORT IFileObject::Ptr CreateFileObject(const CFileName &aFileName);

}
}
}