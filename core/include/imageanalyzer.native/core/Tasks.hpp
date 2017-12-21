#pragma once


#include <imageanalyzer.native/core/IImage.hpp>
#include <imageanalyzer.native/core/TMetaImage.hpp>

#include <threadpoolex/core/ITask.hpp>
#include <threadpoolex/core/IThreadPool.hpp>

#include <baseex/core/CFileName.hpp>
#include <baseex/core/TSingleton.hpp>

#include <atomic>

namespace imageanalyzer {
namespace native {
namespace core {

SINGLETON_NAME(threadpoolex::core::IThreadPool::Ptr, threadpoolex::core::CreateThreadPool(1, threadpoolex::core::CreateExpansionToCPU(baseex::core::CreateSystemInfo(), 80, 1)), ThreadPoolGlobal);

IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeBlock(IImage::Ptr aImage, const TRectangle &aRectangle, THistogram& aResult);

IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(const baseex::core::CFileName &aFileName);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(const baseex::core::CFileName &aFileName, const baseex::core::CFileName &aFileResult);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFileMT(const baseex::core::CFileName &aFileName, threadpoolex::core::IThreadPool::WPtr aThreadPool);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFileMT(const baseex::core::CFileName &aFileName, const baseex::core::CFileName &aFileResult, threadpoolex::core::IThreadPool::WPtr aThreadPool);

IMAGEANALYZER_CORE_EXPORT threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeAll(const baseex::core::CFileName &aFileName);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeCounter(std::atomic_int &aCounter);
IMAGEANALYZER_CORE_EXPORT threadpoolex::core::IObserverTask::Ptr CreateObserverImgAnalyzeOnlyError(const baseex::core::CFileName &aFileName);

}
}
}