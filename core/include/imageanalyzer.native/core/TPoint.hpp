#pragma once

namespace imageanalyzer {
namespace native {
namespace core {

struct IMAGEANALYZER_CORE_EXPORT TPoint
{
    TPoint()
        :m_X(0), m_Y(0)
    {}

    TPoint(int aX, int aY)
        :m_X(aX), m_Y(aY)
    {}

    TPoint operator + (const TPoint& aRght)
    {
        return TPoint(m_X + aRght.m_X, m_Y + aRght.m_Y);
    }

    int m_X;
    int m_Y;
};

}
}
}