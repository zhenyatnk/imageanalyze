#include <imageanalyzer/core/CPathName.hpp>

#include <fstream>
#include <algorithm>

namespace imageanalyzer {
namespace core {

//--------------------------------------------------------------------------------------------------------
CPathName::CPathName()
{
#ifdef _WIN32
    m_Separator = "\\";
#else
    m_Separator = "/";
#endif
}
CPathName::CPathName(const std::string& aPath)
{
#ifdef _WIN32
    m_Separator = "\\";
#else
    m_Separator = "/";
#endif
    std::string lPath = aPath;
    std::string lDirectory = "";
    for (auto lSymbol : lPath)
    {
        if (lSymbol == '\\' || lSymbol == '/')
        {
            if (!lDirectory.empty() || m_Directories.empty() || m_Directories.back().empty())
                m_Directories.push_back(lDirectory);
            lDirectory = "";
        }
        else
            lDirectory.push_back(lSymbol);
    }
    if (!lDirectory.empty())
        m_Directories.push_back(lDirectory);
}

CPathName& CPathName::AddPath(const std::string &aPath)
{
    std::string lPath = aPath;
    std::string lDirectory = "";
    for (auto lSymbol : lPath)
    {
        if (lSymbol == '\\' || lSymbol == '/')
        {
            if (!lDirectory.empty() || m_Directories.empty())
                m_Directories.push_back(lDirectory);
            lDirectory = "";
        }
        else
            lDirectory.push_back(lSymbol);
    }
    if (!lDirectory.empty())
        m_Directories.push_back(lDirectory);

    return *this;
}

CPathName& CPathName::AddPath(const CPathName &aPath)
{
    std::vector<std::string> lDirectories = aPath.GetDirectories();
    for (auto lDirectory : lDirectories)
        if (!lDirectory.empty())
            m_Directories.push_back(lDirectory);
    return *this;
}

std::string CPathName::ToString() const
{
    std::string lPath = "";
    for (auto lDirectory : m_Directories)
        lPath += lDirectory + m_Separator;
    if (m_Directories.size() > 1)
        lPath = lPath.substr(0, lPath.size() - 1);
    return lPath;
}

std::vector<std::string> CPathName::GetDirectories() const
{
    return m_Directories;
}

void CPathName::SetSeparator(std::string aSeparator)
{
    m_Separator = aSeparator;
}

}
}
