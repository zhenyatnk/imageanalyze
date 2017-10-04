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

TEST_F(CEuclideanDistance_test, not_equal_1)
{
    TMetaImage lLeft;
    for (auto& element : lLeft.m_Data)
        element = TColor::FromRGBA(0xFFFFFFFF);

    TMetaImage lRight;
    for (auto& element : lRight.m_Data)
        element = TColor::FromRGBA(0);
    
    ASSERT_EQ(0.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, not_equal_2)
{
    TMetaImage lLeft;
    for (auto& element : lLeft.m_Data)
        element = TColor::FromRGBA(0xFFFFFFFF);

    TMetaImage lRight;
    for (auto& element : lRight.m_Data)
        element = TColor::FromRGBA(0);

    ASSERT_EQ(0.0, CreateEuclideanDistance()->GePercentEqual(lRight, lLeft));
}

TEST_F(CEuclideanDistance_test, not_equal_3)
{
    TMetaImage lLeft;
    for (auto& element : lLeft.m_Data)
        element = TColor::FromRGBA(0xFF11FF11);

    TMetaImage lRight;
    for (auto& element : lRight.m_Data)
        element = TColor::FromRGBA(0x11111111);

    ASSERT_NE(100.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
    ASSERT_NE(0.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, equal_1)
{
    TMetaImage lLeft;
    for (auto& element : lLeft.m_Data)
        element = TColor::FromRGBA(0xFFFFFFFF);

    TMetaImage lRight;
    for (auto& element : lRight.m_Data)
        element = TColor::FromRGBA(0xFFFFFFFF);

    ASSERT_EQ(100.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}

TEST_F(CEuclideanDistance_test, equal_2)
{
    TMetaImage lLeft;
    for (auto& element : lLeft.m_Data)
        element = TColor::FromRGBA(0);

    TMetaImage lRight;
    for (auto& element : lRight.m_Data)
        element = TColor::FromRGBA(0);

    ASSERT_EQ(100.0, CreateEuclideanDistance()->GePercentEqual(lRight, lLeft));
}

TEST_F(CEuclideanDistance_test, equal_3)
{
    TMetaImage lLeft;
    for (auto& element : lLeft.m_Data)
        element = TColor::FromRGBA(0xFF11FF11);

    TMetaImage lRight;
    for (auto& element : lRight.m_Data)
        element = TColor::FromRGBA(0xFF11FF11);

    ASSERT_EQ(100.0, CreateEuclideanDistance()->GePercentEqual(lLeft, lRight));
}
