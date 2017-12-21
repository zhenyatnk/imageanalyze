#include <imageanalyzer.native/core/Tasks.hpp>

#include <threadpoolex/core/ITaskObserver.hpp>

#include <baseex/core/Unicode.hpp>

#include <iostream>
#include <chrono>

using namespace threadpoolex::core;

namespace imageanalyzer {
namespace native {
namespace core {

class CObserverTaskAnalyzer
    :public IObserverTask
{

public:
    explicit CObserverTaskAnalyzer(const baseex::core::CFileName &aFileName);

public:
    virtual void HandleStart() override;
    virtual void HandleComplete() override;
    virtual void HandleError(const std::string &aMessage, const int& aErrorCode) override;

private:
    baseex::core::CFileName m_FileName;
    std::chrono::steady_clock::time_point m_Start;
};

CObserverTaskAnalyzer::CObserverTaskAnalyzer(const baseex::core::CFileName &aFileName)
    :m_FileName(aFileName)
{}

void CObserverTaskAnalyzer::HandleStart()
{
    std::chrono::steady_clock::time_point m_Start = std::chrono::steady_clock::now();
    std::wcout << "Start analyze image ='" << m_FileName.GetFullFileName() << "'" << std::endl;
}

void CObserverTaskAnalyzer::HandleComplete()
{
    std::wcout << "Complete analyze image ='" << m_FileName.GetFullFileName() << "'. Ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_Start).count() << std::endl;
}

void CObserverTaskAnalyzer::HandleError(const std::string &aMessage, const int& aErrorCode)
{
    std::wcout << "Error in proccess analyze image ='" << m_FileName.GetFullFileName() << "'. Message '" << baseex::core::convert(aMessage) << "'" << std::endl;
}

threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeAll(const baseex::core::CFileName &aFileName)
{
    return std::make_shared<CObserverTaskAnalyzer>(aFileName);
}

}
}
}