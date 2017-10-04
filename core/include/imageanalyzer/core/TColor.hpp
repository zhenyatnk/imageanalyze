#pragma once

#include <cstdint>

namespace imageanalyzer {
namespace core {

#define TO_BYTE(value, number) (value >> number*8) & 0xff

struct TColor
{
    TColor()
        :m_Alpha(255), m_Red(0), m_Green(0), m_Blue(0)
    {}

    TColor(uint8_t aRed, uint8_t aGreen, uint8_t aBlue)
        :m_Alpha(255), m_Red(aRed), m_Green(aGreen), m_Blue(aBlue)
    {}

    TColor(uint8_t aAlpha, uint8_t aRed, uint8_t aGreen, uint8_t aBlue)
        :m_Alpha(aAlpha), m_Red(aRed), m_Green(aGreen), m_Blue(aBlue)
    {}

    bool operator == (const TColor& aRht) const
    {
        return m_Alpha == aRht.m_Alpha &&
               m_Red   == aRht.m_Red   &&
               m_Green == aRht.m_Green &&
               m_Blue  == aRht.m_Blue;
    }

    uint32_t To_RGB() const
    {
        return ((m_Red & 0xff) << 2*8) + ((m_Green & 0xff) << 1*8) + (m_Blue & 0xff);
    }

    uint32_t To_RGBA() const
    {
        return ((m_Red & 0xff) << 3*8) + ((m_Green & 0xff) << 2*8) + ((m_Blue & 0xff)<< 1*8) + (m_Alpha & 0xff);
    }

    uint32_t To_ARGB() const
    {
        return ((m_Alpha & 0xff) << 3*8) + ((m_Red & 0xff) << 2*8) + ((m_Green & 0xff) << 1*8) + (m_Blue & 0xff);
    }
    //------------------------------------------------------------
    static TColor FromRGBA(uint32_t aValue)
    {
        return TColor(TO_BYTE(aValue, 0), TO_BYTE(aValue, 3), TO_BYTE(aValue, 2), TO_BYTE(aValue, 1));
    }
    static TColor FromARGB(uint32_t aValue)
    {
        return TColor(TO_BYTE(aValue, 3), TO_BYTE(aValue, 2), TO_BYTE(aValue, 1), TO_BYTE(aValue, 0));
    }
    static TColor FromRGB(uint32_t aValue)
    {
        return TColor(TO_BYTE(aValue, 2), TO_BYTE(aValue, 1), TO_BYTE(aValue, 0));
    }

    uint8_t m_Alpha;
    uint8_t m_Red;
    uint8_t m_Green;
    uint8_t m_Blue;
};

}
}
