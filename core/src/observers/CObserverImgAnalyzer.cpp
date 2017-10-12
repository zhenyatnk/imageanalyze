#include <imageanalyzer/core/Tasks.hpp>
#include <imageanalyzer/core/Tasks.hpp>

#include <threadpoolex/core/ITaskObserver.hpp>

#include <iostream>
#include <chrono>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace core {

class CObserverTaskAnalyzer
    :public IObserverTask
{

public:
    explicit CObserverTaskAnalyzer(const CFileName &aFileName);

public:
    virtual void HandleStart() override;
    virtual void HandleComplete() override;
    virtual void HandleError(const std::string &aMessage, const int& aErrorCode) override;

private:
    CFileName m_FileName;
    std::chrono::steady_clock::time_point m_Start;
};

CObserverTaskAnalyzer::CObserverTaskAnalyzer(const CFileName &aFileName)
    :m_FileName(aFileName)
{}

void CObserverTaskAnalyzer::HandleStart()
{
    std::chrono::steady_clock::time_point m_Start = std::chrono::steady_clock::now();
    std::cout << "Start analyze image ='" << m_FileName.GetFullFileName() << "'" << std::endl;
}

void CObserverTaskAnalyzer::HandleComplete()
{
    std::cout << "Complete analyze image ='" << m_FileName.GetFullFileName() << "'. Ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Start).count() << std::endl;
}

void CObserverTaskAnalyzer::HandleError(const std::string &aMessage, const int& aErrorCode)
{
    std::cout << "Error in proccess analyze image ='" << m_FileName.GetFullFileName() << "'. Message '" << aMessage << "'" << std::endl;
}

threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeAll(const CFileName &aFileName)
{
    return std::make_shared<CObserverTaskAnalyzer>(aFileName);
}

}
}
