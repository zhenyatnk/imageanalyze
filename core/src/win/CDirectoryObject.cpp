#include <imageanalyzer/core/IDirectoryObject.hpp>

#include <windows.h>

namespace imageanalyzer {
namespace core {

class CDirectoryObject
    :public IDirectoryObject
{
public:
    explicit CDirectoryObject(const CPathName& aName);

    virtual CPathName GetName() const override;

    virtual IDirectoryObject::ListPtr GetDirectories() const override;
    virtual IFileObject::ListPtr GetFiles() const override;
    virtual IFileObject::ListPtr GetFiles(std::wstring aMask) const override;

private:
    CPathName m_Name;
    mutable IDirectoryObject::ListPtr m_Directories;
    mutable IFileObject::ListPtr m_Files;
};

CDirectoryObject::CDirectoryObject(const CPathName& aName)
    :m_Name(aName)
{}

CPathName CDirectoryObject::GetName() const
{
    return m_Name;
}

IDirectoryObject::ListPtr CDirectoryObject::GetDirectories() const
{
    if (!m_Directories)
    {
        m_Directories = std::make_shared<std::vector<IDirectoryObject::Ptr>>();

        WIN32_FIND_DATAW ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        hFind = FindFirstFileW(GetName().AddPath(L"*").ToString().c_str(), &ffd);
        if (INVALID_HANDLE_VALUE != hFind)
        {
            do
            {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    if(!!wcscmp(ffd.cFileName, L"..") && !!wcscmp(ffd.cFileName, L"."))
                        m_Directories->push_back(CreateDirectoryObject(CPathName(GetName()).AddPath(ffd.cFileName)));
            }
            while (!!FindNextFileW(hFind, &ffd));
        }

    }
    return m_Directories;
}

IFileObject::ListPtr CDirectoryObject::GetFiles() const
{
    return GetFiles(L"*");
}

IFileObject::ListPtr CDirectoryObject::GetFiles(std::wstring aMask) const
{
    if (!m_Files)
    {
        m_Files = std::make_shared<std::vector<IFileObject::Ptr>>();
        WIN32_FIND_DATAW ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        hFind = FindFirstFileW(GetName().AddPath(aMask).ToString().c_str(), &ffd);
        if (INVALID_HANDLE_VALUE != hFind)
        {
            do
            {
                if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    m_Files->push_back(CreateFileObject(CFileName(GetName(), ffd.cFileName)));
            } while (!!FindNextFileW(hFind, &ffd));
        }
    }
    return m_Files;
}

IDirectoryObject::Ptr CreateDirectoryObject(const CPathName& aName)
{
    return std::make_shared<CDirectoryObject>(aName);
}


}
}
