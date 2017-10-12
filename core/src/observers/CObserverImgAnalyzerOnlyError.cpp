#include <imageanalyzer/core/Tasks.hpp>

#include <threadpoolex/core/ITaskObserver.hpp>

#include <iostream>
#include <chrono>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace core {

class CObserverImgAnalyzerOnlyError
    :public EmptyObserverTask
{

public:
    explicit CObserverImgAnalyzerOnlyError(const CFileName &aFileName);

public:
    virtual void HandleError(const std::string &aMessage, const int& aErrorCode) override;

private:
    CFileName m_FileName;
};

CObserverImgAnalyzerOnlyError::CObserverImgAnalyzerOnlyError(const CFileName &aFileName)
    :m_FileName(aFileName)
{}

void CObserverImgAnalyzerOnlyError::HandleError(const std::string &aMessage, const int& aErrorCode)
{
    std::cout << "Error in proccess analyze image ='" << m_FileName.GetFullFileName() << "'. Message '" << aMessage << "'" << std::endl;
}

threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeOnlyError(const CFileName &aFileName)
{
    return std::make_shared<CObserverImgAnalyzerOnlyError>(aFileName);
}

}
}
