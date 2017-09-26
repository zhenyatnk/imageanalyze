#pragma once

namespace imageanalyzer {
namespace core {

struct TPoint
{
    TPoint()
        :m_X(0), m_Y(0)
    {}

    TPoint(int aX, int aY)
        :m_X(aX), m_Y(aY)
    {}

    int m_X;
    int m_Y;
};

}
}
