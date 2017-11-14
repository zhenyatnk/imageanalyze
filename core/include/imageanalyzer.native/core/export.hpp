#pragma once

#ifdef imageanalyzer_core_SHARED_DEFINE
#   ifndef IMAGEANALYZER_CORE_EXPORT
#       ifdef imageanalyzer_core_EXPORTS
#           if defined _WIN32
#               define IMAGEANALYZER_CORE_EXPORT __declspec(dllexport)
#           elif defined __GNUC__ || defined __clang__
#               define IMAGEANALYZER_CORE_EXPORT __attribute__((visibility("default")))
#           endif
#       else
#           if defined _WIN32
#               define IMAGEANALYZER_CORE_EXPORT __declspec(dllimport)
#           elif defined __GNUC__ || defined __clang__
#               define IMAGEANALYZER_CORE_EXPORT __attribute__((visibility("default")))
#           endif
#       endif
#   endif
#   ifndef IMAGEANALYZER_CORE_NO_EXPORT
#       if defined _WIN32
#           define IMAGEANALYZER_CORE_NO_EXPORT
#       elif defined __GNUC__ || defined __clang__
#           define IMAGEANALYZER_CORE_NO_EXPORT __attribute__((visibility("hidden")))
#       endif
#   endif
#else
#   define IMAGEANALYZER_CORE_EXPORT
#   define IMAGEANALYZER_CORE_NO_EXPORT
#endif

#ifndef IMAGEANALYZER_CORE_DEPRECATED
#   if defined _WIN32
#       define IMAGEANALYZER_CORE_DEPRECATED __declspec(deprecated)
#   elif defined __GNUC__ || defined __clang__
#       define IMAGEANALYZER_CORE_DEPRECATED __attribute__ ((__deprecated__))
#   endif
#endif

#ifndef IMAGEANALYZER_CORE_DEPRECATED_EXPORT
#  define IMAGEANALYZER_CORE_DEPRECATED_EXPORT IMAGEANALYZER_CORE_EXPORT IMAGEANALYZER_CORE_DEPRECATED
#endif

#ifndef IMAGEANALYZER_CORE_DEPRECATED_NO_EXPORT
#  define IMAGEANALYZER_CORE_DEPRECATED_NO_EXPORT IMAGEANALYZER_CORE_NO_EXPORT IMAGEANALYZER_CORE_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define IMAGEANALYZER_CORE_NO_DEPRECATED
#endif
