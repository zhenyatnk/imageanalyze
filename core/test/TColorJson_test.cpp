#include <imageanalyzer.native/core/TColorJson.hpp>

#include <gtest/gtest.h>

using namespace imageanalyzer::native::core;
using namespace nlohmann;
//--------------------------------------------------
namespace
{

bool TestEq(const TColor &l, const TColor &r)
{
    return  l.m_Alpha == r.m_Alpha &&
            l.m_Red   == r.m_Red   &&
            l.m_Green == l.m_Green &&
            l.m_Blue  == r.m_Blue;
}
}
//--------------------------------------------------

class TColorJson_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(TColorJson_test, serialize_color_zero)
{
    json test = TColor::FromRGBA(0);
    ASSERT_STREQ("0", test.dump().c_str());
}

TEST_F(TColorJson_test, serialize_color_max)
{
    json test = TColor::FromRGBA(0xFFFFFFFF);
    ASSERT_STREQ("4294967295", test.dump().c_str());
}

TEST_F(TColorJson_test, serialize_color)
{
    json test = TColor::FromRGBA(287462911);
    ASSERT_STREQ("287462911", test.dump().c_str());
}

TEST_F(TColorJson_test, deserialize_color_zero)
{
    json test = "0"_json;
    ASSERT_EQ(true, TestEq(test.get<TColor>(), TColor::FromRGBA(0)));
}

TEST_F(TColorJson_test, deserialize_color_max)
{
    json test = "4294967295"_json;
    ASSERT_EQ(true, TestEq(test.get<TColor>(), TColor::FromRGBA(0xFFFFFFFF)));
}

TEST_F(TColorJson_test, deserialize_color)
{
    json test = "287462911"_json;
    ASSERT_EQ(true, TestEq(test.get<TColor>(), TColor::FromRGBA(287462911)));
}

TEST_F(TColorJson_test, json_cycle_color_zero)
{
    TColor lTestColor(TColor::FromRGBA(0));

    json test = lTestColor;
    ASSERT_EQ(true, TestEq(test.get<TColor>(), lTestColor));
}

TEST_F(TColorJson_test, json_cycle_color_max)
{
    TColor lTestColor(TColor::FromRGBA(0xFFFFFFFF));

    json test = lTestColor;
    ASSERT_EQ(true, TestEq(test.get<TColor>(), lTestColor));
}

TEST_F(TColorJson_test, json_cycle_color)
{
    TColor lTestColor(TColor::FromRGBA(287462911));

    json test = lTestColor;
    ASSERT_EQ(true, TestEq(test.get<TColor>(), lTestColor));
}