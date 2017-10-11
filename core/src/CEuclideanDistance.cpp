#include <imageanalyzer/core/IMetaComparator.hpp>

#include <fstream>
#include <algorithm>

namespace imageanalyzer {
namespace core {

//--------------------------------------------------------------------------------------------------------
class CEuclideanDistance
    :public IMetaComparator
{
public:
    virtual float GePercentEqual(const TMetaImage&, const TMetaImage&) const override;

protected:
    float GetDistance(const TMetaImage&, const TMetaImage&) const;
    float GetDistance(const THistogram&, const THistogram&) const;
};

float CEuclideanDistance::GePercentEqual(const TMetaImage& aLeft, const TMetaImage& aRight) const
{
    return (float)100.0 - ((float)GetDistance(aLeft, aRight) / (2 * 9));
}

float CEuclideanDistance::GetDistance(const TMetaImage& aLeft, const TMetaImage& aRight) const
{
    float lDistanceAll = 0;
    for (std::size_t lIndex = 0; lIndex < std::tuple_size<TMetaImage::TContainerHistograms>::value; ++lIndex)
        lDistanceAll += GetDistance(aLeft.m_Histograms[lIndex], aRight.m_Histograms[lIndex]);

    return lDistanceAll;
}

float CEuclideanDistance::GetDistance(const THistogram& aLeft, const THistogram& aRight) const
{
    float lDistance = 0;
    for (std::size_t lIndex = 0; lIndex < std::tuple_size<THistogram::TContainerColor>::value; ++lIndex)
    {
        float lELementResult = aLeft.m_Data[lIndex];
        lELementResult -= aRight.m_Data[lIndex];
        if (lELementResult < 0)
            lELementResult = lELementResult * -1;
        lDistance += lELementResult;
    }
    return lDistance;
}

IMetaComparator::Ptr CreateEuclideanDistance()
{
    return std::make_shared<CEuclideanDistance>();
}

}
}
