#pragma once

namespace imageanalyzer {
namespace core {

#define TO_BYTE(value, number) (value >> number*8) & 0xff

struct TColor
{
    using Byte = unsigned char;

    TColor()
        :m_Alpha(255), m_Red(0), m_Green(0), m_Blue(0)
    {}

    TColor(Byte aRed, Byte aGreen, Byte aBlue)
        :m_Alpha(255), m_Red(aRed), m_Green(aGreen), m_Blue(aBlue)
    {}

    TColor(Byte aAlpha, Byte aRed, Byte aGreen, Byte aBlue)
        :m_Alpha(aAlpha), m_Red(aRed), m_Green(aGreen), m_Blue(aBlue)
    {}

    bool operator == (const TColor& aRht) const
    {
        return m_Alpha == aRht.m_Alpha &&
               m_Red   == aRht.m_Red   &&
               m_Green == aRht.m_Green &&
               m_Blue  == aRht.m_Blue;
    }

    unsigned long To_RGB() const
    {
        return ((m_Red & 0xff) << 2*8) + ((m_Green & 0xff) << 1*8) + (m_Blue & 0xff);
    }

    unsigned long To_RGBA() const
    {
        return ((m_Red & 0xff) << 3*8) + ((m_Green & 0xff) << 2*8) + ((m_Blue & 0xff)<< 1*8) + (m_Alpha & 0xff);
    }

    unsigned long To_ARGB() const
    {
        return ((m_Alpha & 0xff) << 3*8) + ((m_Red & 0xff) << 2*8) + ((m_Green & 0xff) << 1*8) + (m_Blue & 0xff);
    }
    //------------------------------------------------------------
    static TColor FromRGBA(unsigned long aValue)
    {
        return TColor(TO_BYTE(aValue, 0), TO_BYTE(aValue, 3), TO_BYTE(aValue, 2), TO_BYTE(aValue, 1));
    }
    static TColor FromARGB(unsigned long aValue)
    {
        return TColor(TO_BYTE(aValue, 3), TO_BYTE(aValue, 2), TO_BYTE(aValue, 1), TO_BYTE(aValue, 0));
    }
    static TColor FromRGB(unsigned long aValue)
    {
        return TColor(TO_BYTE(aValue, 2), TO_BYTE(aValue, 1), TO_BYTE(aValue, 0));
    }

    Byte m_Alpha;
    Byte m_Red;
    Byte m_Green;
    Byte m_Blue;
};

}
}
