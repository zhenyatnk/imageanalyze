#pragma once

#include <imageanalyzer/core/IFileObject.hpp>
#include <imageanalyzer/core/CPathName.hpp>

#include <vector>
#include <memory>

namespace imageanalyzer {
namespace core {

class IDirectoryObject
{
public:
    using Ptr = std::shared_ptr<IDirectoryObject>;
    using ListPtr = std::shared_ptr<std::vector<Ptr>>;

public:
    virtual CPathName GetName() const = 0;

    virtual IDirectoryObject::ListPtr GetDirectories() const = 0;
    virtual IFileObject::ListPtr GetFiles() const = 0;
};

IDirectoryObject::Ptr CreateDirectoryObject(const CPathName& aName);

}
}
