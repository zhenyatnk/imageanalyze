#pragma once

#include <imageanalyzer/core/CFileName.hpp>
#include <imageanalyzer/core/IImage.hpp>
#include <imageanalyzer/core/TMetaImage.hpp>

#include <threadpoolex/core/ITask.hpp>
#include <threadpoolex/core/IThreadPool.hpp>
#include <threadpoolex/core/TSingleton.hpp>

#include <atomic>

namespace imageanalyzer {
namespace core {

SINGLETON_NAME(threadpoolex::core::IThreadPool::Ptr, threadpoolex::core::CreateThreadPool(1, threadpoolex::core::CreateExpansionToCPU(threadpoolex::core::CreateSystemInfo(), 80, 1)), ThreadPoolGlobal);

IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeBlock(IImage::Ptr aImage, const TRectangle &aRectangle, THistogram& aResult);

IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(const CFileName &aFileName);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(const CFileName &aFileName, const CFileName &aFileResult);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFileMT(const CFileName &aFileName, threadpoolex::core::IThreadPool::WPtr aThreadPool);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFileMT(const CFileName &aFileName, const CFileName &aFileResult, threadpoolex::core::IThreadPool::WPtr aThreadPool);

IMAGEANALYZER_CORE_EXPORT threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeAll(const CFileName &aFileName);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeCounter(std::atomic_int &aCounter);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeOnlyError(const CFileName &aFileName);

}
}
