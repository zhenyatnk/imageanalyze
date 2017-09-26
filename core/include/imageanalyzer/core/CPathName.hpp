#pragma once

#include <string>
#include <memory>
#include <vector>

namespace imageanalyzer {
namespace core {

class CPathName
{
public:
    using Ptr = std::shared_ptr<CPathName>;

public:
    CPathName();
    CPathName(const std::string &aPath);

    CPathName& AddPath(const std::string &aPath);
    CPathName& AddPath(const CPathName &aPath);

    std::string ToString() const;
    std::vector<std::string> GetDirectories() const;

    void SetSeparator(std::string aSeparator);

private:
    std::vector<std::string> m_Directories;
    std::string m_Separator;
};

}
}
