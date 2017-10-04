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
    //static constexpr  max_distance = ;

public:
    virtual double GePercentEqual(const TMetaImage&, const TMetaImage&) const override;
};

double CEuclideanDistance::GePercentEqual(const TMetaImage& aLeft, const TMetaImage& aRight) const
{
    uint64_t lDistance = 0;
    for (std::size_t lIndex = 0; lIndex < std::tuple_size<TMetaImage::TypeData>::value; ++lIndex)
    {
        int64_t lELementResult = aLeft.m_Data[lIndex].To_RGB();
        lELementResult -= aRight.m_Data[lIndex].To_RGB();
        lELementResult = lELementResult*lELementResult;

        lDistance += lELementResult;
    }
    return 100.0 - 100.0 * ((double)lDistance / ((uint64_t)0xFFFFFF * 0xFFFFFF * 64));
}

IMetaComparator::Ptr CreateEuclideanDistance()
{
    return std::make_shared<CEuclideanDistance>();
}

}
}
