#pragma once

#include <imageanalyzer/core/TPoint.hpp>
#include <imageanalyzer/core/TSize.hpp>

namespace imageanalyzer {
namespace core {

struct TRectangle
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
