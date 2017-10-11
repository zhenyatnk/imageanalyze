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

        WIN32_FIND_DATA ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        hFind = FindFirstFile(GetName().AddPath("*").ToString().c_str(), &ffd);
        if (INVALID_HANDLE_VALUE != hFind)
        {
            while (!!FindNextFile(hFind, &ffd))
            {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                    if(!!strcmp(ffd.cFileName, ".."))
                        m_Directories->push_back(CreateDirectoryObject(CPathName(GetName()).AddPath(ffd.cFileName)));
            }
        }

    }
    return m_Directories;
}

IFileObject::ListPtr CDirectoryObject::GetFiles() const
{
    if (!m_Files)
    {
        m_Files = std::make_shared<std::vector<IFileObject::Ptr>>();
        WIN32_FIND_DATA ffd;
        HANDLE hFind = INVALID_HANDLE_VALUE;
        hFind = FindFirstFile(GetName().AddPath("*").ToString().c_str(), &ffd);
        if (INVALID_HANDLE_VALUE != hFind)
        {
            while (!!FindNextFile(hFind, &ffd))
            {
                if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    m_Files->push_back(CreateFileObject(CFileName(GetName(),ffd.cFileName)));
            }
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
