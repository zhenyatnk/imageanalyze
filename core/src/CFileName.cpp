#include <imageanalyzer/core/CFileName.hpp>

#include <fstream>
#include <algorithm>

namespace imageanalyzer {
namespace core {

//--------------------------------------------------------------------------------------------------------
CFileName::CFileName()
    :m_Path(L""), m_FileName(L""), m_FullFileName(L"")
{
#ifdef _WIN32
    m_Separator = L"\\";
#else
    m_Separator = L"/";
#endif
}

CFileName::CFileName(const std::wstring& aFullFileName)
    :m_Path(L""), m_FileName(L""), m_FullFileName(aFullFileName)
{
#ifdef _WIN32
    m_Separator = L"\\";
#else
    m_Separator = L"/";
#endif

    std::size_t winFound = aFullFileName.rfind(L"\\");
    std::size_t linFound = aFullFileName.rfind(L"/");
    std::size_t found = winFound;

    if (linFound != std::wstring::npos)
        if (found == std::wstring::npos || found < linFound)
            found = linFound;

    if (found != std::wstring::npos)
    {
        m_FileName = aFullFileName.substr(found + 1);
        m_Path = aFullFileName.substr(0, found);
    }
    else
        m_FileName = aFullFileName;
}
CFileName::CFileName(const CPathName& aPath, const std::wstring& aFileName)
    :m_Path(aPath), m_FileName(aFileName), m_FullFileName(L"")
{
#ifdef _WIN32
    m_Separator = L"\\";
#else
    m_Separator = L"/";
#endif
    while (!m_FileName.empty() && (m_FileName.front() == L'\\' || m_FileName.front() == L'/'))
        m_FileName = m_FileName.substr(1);
}

CFileName& CFileName::AddPath(const CPathName &aPath)
{
    m_Path.AddPath(aPath);
    m_FullFileName = L"";
    return *this;
}

CFileName& CFileName::AddFileName(const CFileName &aFileName)
{
    this->AddPath(aFileName.GetPath());
    this->m_FileName = aFileName.GetFileName();
    m_FullFileName = L"";
    return *this;
}

std::wstring CFileName::GetExtension() const
{
    std::wstring lExtension = GetFileName();
    size_t lDotPos = lExtension.rfind(L".");
    if (lDotPos != std::wstring::npos)
        lExtension = lExtension.substr(lDotPos + 1);
    else
        lExtension = L"";
    return lExtension;
}

std::wstring CFileName::GetName() const
{
    std::wstring lName = GetFileName();
    size_t lDotPos = lName.rfind(L".");
    if (lDotPos != std::wstring::npos)
        lName = lName.substr(0, lDotPos);
    return lName;
}

std::wstring CFileName::GetFileName() const
{
    return m_FileName;
}

CPathName CFileName::GetPath() const
{
    return m_Path;
}

std::wstring CFileName::GetFullFileName() const
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

void CFileName::SetSeparator(std::wstring aSeparator)
{
    m_Separator = aSeparator;
    m_Path.SetSeparator(aSeparator);
}

}
}
