#pragma once

#include <imageanalyzer.native/core/TPoint.hpp>
#include <imageanalyzer.native/core/TSize.hpp>

namespace imageanalyzer {
namespace native {
namespace core {

struct IMAGEANALYZER_CORE_EXPORT TRectangle
{
    TRectangle(TPoint aLeft, TSize aSize)
        :m_Left(aLeft), m_Size(aSize)
    {}

    TRectangle MoveTo(TPoint aPoint) const
    {
        return TRectangle(aPoint, m_Size);
    }

    TPoint m_Left;
    TSize m_Size;
};

}
}
}