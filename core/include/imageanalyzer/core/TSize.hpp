#pragma once

#include <imageanalyzer/core/TPoint.hpp>

namespace imageanalyzer {
namespace core {

struct TSize
{
    TSize()
        :m_Width(0), m_Height(0)
    {}

    TSize(uint32_t aWidth, uint32_t aHeight)
        :m_Width(aWidth), m_Height(aHeight)
    {}

    TSize operator - (const TSize& aRght)
    {
        TSize lResult;
        if (m_Width > aRght.m_Width)
            lResult.m_Width = m_Width - aRght.m_Width;

        if (m_Height > aRght.m_Height)
            lResult.m_Height = m_Height - aRght.m_Height;
        return lResult;
    }

    uint32_t m_Width;
    uint32_t m_Height;
};

}
}
