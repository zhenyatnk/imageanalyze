#pragma once

namespace imageanalyzer {
namespace core {

struct TSize
{
    TSize()
        :m_Width(0), m_Height(0)
    {}

    TSize(unsigned int aWidth, unsigned int aHeight)
        :m_Width(aWidth), m_Height(aHeight)
    {}

    unsigned int m_Width;
    unsigned int m_Height;
};

}
}
