#pragma once

namespace imageanalyzer {
namespace core {

struct TColor
{
    TColor()
        :m_Alpha(100), m_Red(0), m_Green(0), m_Blue(0)
    {}

    TColor(unsigned char aRed, unsigned char aGreen, unsigned char aBlue)
        :m_Alpha(100), m_Red(aRed), m_Green(aGreen), m_Blue(aBlue)
    {}

    TColor(unsigned char aAlpha, unsigned char aRed, unsigned char aGreen, unsigned char aBlue)
        :m_Alpha(aAlpha), m_Red(aRed), m_Green(aGreen), m_Blue(aBlue)
    {}

    unsigned char m_Alpha;
    unsigned char m_Red;
    unsigned char m_Green;
    unsigned char m_Blue;
};

}
}
