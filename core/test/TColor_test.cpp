#include <imageanalyzer/core/TColor.hpp>

#include <gtest/gtest.h>

//--------------------------------------------------
using namespace imageanalyzer::core;

class TColor_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(TColor_test, operator_equal)
{
    ASSERT_EQ(true, TColor(1,2,3) == TColor(1,2,3));
}

TEST_F(TColor_test, operator_notequal_1)
{
    ASSERT_EQ(false, TColor(255, 2, 3) == TColor(1, 2, 3));
}

TEST_F(TColor_test, operator_notequal_2)
{
    ASSERT_EQ(false, TColor(1, 255, 3) == TColor(1, 2, 3));
}

TEST_F(TColor_test, operator_notequal_3)
{
    ASSERT_EQ(false, TColor(1, 2, 255) == TColor(1, 2, 3));
}

TEST_F(TColor_test, operator_notequal_4)
{
    ASSERT_EQ(false, TColor(0, 1, 2, 3) == TColor(255, 1, 2, 3));
}

TEST_F(TColor_test, To_RGB)
{
    ASSERT_EQ(0xFF7F50, TColor(255, 127, 80).To_RGB());
}

TEST_F(TColor_test, To_RGBA)
{
    ASSERT_EQ(0xFF7F5080, TColor(128, 255, 127, 80).To_RGBA());
}

TEST_F(TColor_test, To_ARGB)
{
    ASSERT_EQ(0x80FF7F50, TColor(128, 255, 127, 80).To_ARGB());
}

TEST_F(TColor_test, From_RGB)
{
    ASSERT_EQ(TColor(255, 127, 80), TColor::FromRGB(0xFF7F50));
}

TEST_F(TColor_test, From_RGBA)
{
    ASSERT_EQ(TColor(128, 255, 127, 80), TColor::FromRGBA(0xFF7F5080));
}

TEST_F(TColor_test, From_ARGB)
{
    ASSERT_EQ(TColor(128, 255, 127, 80), TColor::FromARGB(0x80FF7F50));
}
