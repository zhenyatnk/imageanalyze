#pragma once

#include <imageanalyzer/core/CFileName.hpp>
#include <imageanalyzer/core/IImage.hpp>

#include <threadpoolex/core/ITask.hpp>
#include <threadpoolex/core/IThreadPool.hpp>
#include <threadpoolex/core/TSingleton.hpp>

namespace imageanalyzer {
namespace core {

SINGLETON_NAME(threadpoolex::core::IThreadPool::Ptr, threadpoolex::core::CreateThreadPool(9, threadpoolex::core::CreateExpansionToMax(45)), ThreadPool_Blocks);
SINGLETON_NAME(threadpoolex::core::IThreadPool::Ptr, threadpoolex::core::CreateThreadPool(1, threadpoolex::core::CreateExpansionToMax(5)), ThreadPool_Files);

threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(const CFileName &aFileNae);
threadpoolex::core::ITask::Ptr CreateTaskAnalyzeInFile(IImage::Ptr aImage, const CFileName &aFileResult);

}
}
