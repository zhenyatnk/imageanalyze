#pragma once

#include <imageanalyzer/core/IFileObject.hpp>
#include <imageanalyzer/core/CPathName.hpp>

#include <vector>
#include <memory>

namespace imageanalyzer {
namespace core {

class IMAGEANALYZER_CORE_EXPORT IDirectoryObject
{
public:
    using Ptr = std::shared_ptr<IDirectoryObject>;
    using ListPtr = std::shared_ptr<std::vector<Ptr>>;

public:
    virtual CPathName GetName() const = 0;

    virtual IDirectoryObject::ListPtr GetDirectories() const = 0;
    virtual IFileObject::ListPtr GetFiles() const = 0;
    virtual IFileObject::ListPtr GetFiles(std::wstring aMask) const = 0;
};

IMAGEANALYZER_CORE_EXPORT IDirectoryObject::Ptr CreateDirectoryObject(const CPathName& aName);

}
}
