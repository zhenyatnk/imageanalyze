#include <imageanalyzer/core/IMetaComparator.hpp>

#include <gtest/gtest.h>

//--------------------------------------------------
using namespace imageanalyzer::core;

class CEuclideanDistance_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(CEuclideanDistance_test, not_equal_simple)
{
    TMetaImage lLeft;
    for (auto& histogram : lLeft.m_Histograms)
        histogram.m_Data[0] = 100;

    TMetaImage lRight;
    for (auto& histogram : lRight.m_Histograms)
        histogram.m_Data[1] = 100;

    ASSERT_EQ(0.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, not_equal_all)
{
    TMetaImage lLeft;
    for (auto& histogram : lLeft.m_Histograms)
        for (auto element = 0; element < 32; ++element)
            histogram.m_Data[element] = 100.0 / 32;

    TMetaImage lRight;
    for (auto& histogram : lRight.m_Histograms)
        for (auto element = 32; element < 64; ++element)
            histogram.m_Data[element] = 100.0 / 32;

    ASSERT_EQ(0.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, equal_simple)
{
    TMetaImage lLeft;
    for (auto& histogram : lLeft.m_Histograms)
        histogram.m_Data[0] = 100;

    TMetaImage lRight;
    for (auto& histogram : lRight.m_Histograms)
        histogram.m_Data[0] = 100;

    ASSERT_EQ(100.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, equal_all)
{
    TMetaImage lLeft;
    for (auto& histogram : lLeft.m_Histograms)
        for (auto element = 0; element < 64; ++element)
            histogram.m_Data[element] = 100.0 / 64;

    TMetaImage lRight;
    for (auto& histogram : lRight.m_Histograms)
        for (auto element = 0; element < 64; ++element)
            histogram.m_Data[element] = 100.0 / 64;

    ASSERT_EQ(100.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, equal_other_all)
{
    TMetaImage lLeft;
    for (auto& histogram : lLeft.m_Histograms)
        for (auto element = 0; element < 32; ++element)
            histogram.m_Data[element] = 100.0 / 32;

    TMetaImage lRight;
    for (auto& histogram : lRight.m_Histograms)
        for (auto element = 0; element < 32; ++element)
            histogram.m_Data[element] = 100.0 / 32;

    ASSERT_EQ(100.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, not_equal_other_percent)
{
    TMetaImage lLeft;
    for (auto& histogram : lLeft.m_Histograms)
        for (auto element = 24; element < 24+32; ++element)
            histogram.m_Data[element] = 100.0 / 32;

    TMetaImage lRight;
    for (auto& histogram : lRight.m_Histograms)
        for (auto element = 12; element < 12+32; ++element)
            histogram.m_Data[element] = 100.0 / 32;

    auto lResult = CreateEuclideanDistance()->GePercentEqual(lLeft, lRight);

    ASSERT_NE(0.0, lResult);
    ASSERT_NE(100.0, lResult);
}