#include <imageanalyzer.native/core/Tasks.hpp>
#include <imageanalyzer.native/core/Unicode.hpp>

#include <threadpoolex/core/ITaskObserver.hpp>

#include <iostream>
#include <chrono>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace native {
namespace core {

class CObserverImgAnalyzerOnlyError
    :public EmptyObserverTask
{

public:
    explicit CObserverImgAnalyzerOnlyError(const baseex::core::CFileName &aFileName);

public:
    virtual void HandleError(const std::string &aMessage, const int& aErrorCode) override;

private:
    baseex::core::CFileName m_FileName;
};

CObserverImgAnalyzerOnlyError::CObserverImgAnalyzerOnlyError(const baseex::core::CFileName &aFileName)
    :m_FileName(aFileName)
{}

void CObserverImgAnalyzerOnlyError::HandleError(const std::string &aMessage, const int& aErrorCode)
{
    std::wcout << "Error in proccess analyze image ='" << m_FileName.GetFullFileName() << "'. Message '" << convert(aMessage) << "'" << std::endl;
}

threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeOnlyError(const baseex::core::CFileName &aFileName)
{
    return std::make_shared<CObserverImgAnalyzerOnlyError>(aFileName);
}

}
}
}