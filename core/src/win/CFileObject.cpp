#include <imageanalyzer/core/IFileObject.hpp>

namespace imageanalyzer {
namespace core {

class CFileObject
    :public IFileObject
{
public:
    explicit CFileObject(const CFileName& aFileName);

    virtual CFileName GetName() const override;

private:
    CFileName m_FileName;
};

CFileObject::CFileObject(const CFileName& aFileName)
    :m_FileName(aFileName)
{}

CFileName CFileObject::GetName() const
{
    return m_FileName;
}

IFileObject::Ptr CreateFileObject(const CFileName& aFileName)
{
    return std::make_shared<CFileObject>(aFileName);
}

}
}
