#pragma once

#include <imageanalyzer/core/CPathName.hpp>

#include <string>
#include <memory>
#include <vector>

namespace imageanalyzer {
namespace core {

class CFileName
{
public:
    using Ptr = std::shared_ptr<CFileName>;

public:
    CFileName();
    CFileName(const std::string &aFullFileName);
    CFileName(const CPathName& aPath, const std::string &aFileName);

    CFileName& AddPath(const CPathName &aPath);
    CFileName& AddFileName(const CFileName &aFileName);

    std::string GetExtension() const;
    std::string GetName() const;
    std::string GetFileName() const;
    CPathName   GetPath() const;
    std::string GetFullFileName() const;

    void SetSeparator(std::string aSeparator);

private:
    std::string m_FileName;
    CPathName m_Path;
    mutable std::string m_FullFileName;
    std::string m_Separator;
};

}
}
