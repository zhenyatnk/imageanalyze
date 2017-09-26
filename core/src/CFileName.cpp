#include <imageanalyzer/core/CFileName.hpp>

#include <fstream>
#include <algorithm>

namespace imageanalyzer {
namespace core {

//--------------------------------------------------------------------------------------------------------
CFileName::CFileName()
    :m_Path(""), m_FileName(""), m_FullFileName("")
{
#ifdef _WIN32
    m_Separator = "\\";
#else
    m_Separator = "/";
#endif
}

CFileName::CFileName(const std::string& aFullFileName)
    :m_Path(""), m_FileName(""), m_FullFileName(aFullFileName)
{
#ifdef _WIN32
    m_Separator = "\\";
#else
    m_Separator = "/";
#endif

    std::size_t winFound = aFullFileName.rfind("\\");
    std::size_t linFound = aFullFileName.rfind("/");
    std::size_t found = winFound;

    if (linFound != std::string::npos)
        if (found == std::string::npos || found < linFound)
            found = linFound;

    if (found != std::string::npos)
    {
        m_FileName = aFullFileName.substr(found + 1);
        m_Path = aFullFileName.substr(0, found);
    }
    else
        m_FileName = aFullFileName;
}
CFileName::CFileName(const CPathName& aPath, const std::string& aFileName)
    :m_Path(aPath), m_FileName(aFileName), m_FullFileName("")
{
#ifdef _WIN32
    m_Separator = "\\";
#else
    m_Separator = "/";
#endif
    while (!m_FileName.empty() && (m_FileName.front() == '\\' || m_FileName.front() == '/'))
        m_FileName = m_FileName.substr(1);
}

CFileName& CFileName::AddPath(const CPathName &aPath)
{
    m_Path.AddPath(aPath);
    m_FullFileName = "";
    return *this;
}

CFileName& CFileName::AddFileName(const CFileName &aFileName)
{
    this->AddPath(aFileName.GetPath());
    this->m_FileName = aFileName.GetFileName();
    m_FullFileName = "";
    return *this;
}

std::string CFileName::GetExtension() const
{
    std::string lExtension = GetFileName();
    size_t lDotPos = lExtension.rfind(".");
    if (lDotPos != std::string::npos)
        lExtension = lExtension.substr(lDotPos + 1);
    else
        lExtension = "";
    return lExtension;
}

std::string CFileName::GetName() const
{
    std::string lName = GetFileName();
    size_t lDotPos = lName.rfind(".");
    if (lDotPos != std::string::npos)
        lName = lName.substr(0, lDotPos);
    return lName;
}

std::string CFileName::GetFileName() const
{
    return m_FileName;
}

CPathName CFileName::GetPath() const
{
    return m_Path;
}

std::string CFileName::GetFullFileName() const
{
    if (m_FullFileName.empty())
    {
        if (!GetPath().ToString().empty())
            m_FullFileName = GetPath().ToString() + m_Separator + GetFileName();
        else
            m_FullFileName = GetFileName();
    }
    return m_FullFileName;
}

void CFileName::SetSeparator(std::string aSeparator)
{
    m_Separator = aSeparator;
    m_Path.SetSeparator(aSeparator);
}

}
}
