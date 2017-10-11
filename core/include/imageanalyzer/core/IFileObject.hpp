#pragma once

#include <imageanalyzer/core/CFileName.hpp>

#include <vector>
#include <memory>

namespace imageanalyzer {
namespace core {

class IFileObject
{
public:
    using Ptr = std::shared_ptr<IFileObject>;
    using ListPtr = std::shared_ptr<std::vector<Ptr>>;

public:
    virtual CFileName GetName() const = 0;
};

IFileObject::Ptr CreateFileObject(const CFileName &aFileName);

}
}
