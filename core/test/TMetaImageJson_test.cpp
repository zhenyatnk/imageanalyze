#include <imageanalyzer/core/TMetaImageJson.hpp>

#include <gtest/gtest.h>

using namespace imageanalyzer::core;
using namespace nlohmann;
//--------------------------------------------------
namespace
{

bool TestEq(const TColor &l, const TColor &r)
{
    return  l.m_Alpha == r.m_Alpha &&
        l.m_Red == r.m_Red   &&
        l.m_Green == l.m_Green &&
        l.m_Blue == r.m_Blue;
}
}
//--------------------------------------------------

class TMetaImageJson_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(TMetaImageJson_test, serialize_zero)
{
    TMetaImage::TypeData lData;
    for (auto& element : lData)
        element = TColor::FromRGBA(0);

    json test = TMetaImage(std::move(lData));
    ASSERT_STREQ("[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]", test.dump().c_str());
}

TEST_F(TMetaImageJson_test, serialize_first_nonzero)
{
    TMetaImage::TypeData lData;
    for (auto& element : lData)
        element = TColor::FromRGBA(0);
    
    lData[0] = TColor::FromRGBA(1);

    json test = TMetaImage(std::move(lData));
    ASSERT_STREQ("[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]", test.dump().c_str());
}

TEST_F(TMetaImageJson_test, serialize_first_and_second_nonzero)
{
    TMetaImage::TypeData lData;
    for (auto& element : lData)
        element = TColor::FromRGBA(0);

    lData[0] = TColor::FromRGBA(1);
    lData[1] = TColor::FromRGBA(2);

    json test = TMetaImage(std::move(lData));
    ASSERT_STREQ("[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]", test.dump().c_str());
}

TEST_F(TMetaImageJson_test, deserialize_zero)
{
    json test = "[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]"_json;
    auto lResult = test.get<TMetaImage>();
    ASSERT_EQ(64, lResult.m_Data.size());
    ASSERT_EQ(0, lResult.m_Data[0].To_RGBA());
    ASSERT_EQ(0, lResult.m_Data[1].To_RGBA());
    ASSERT_EQ(0, lResult.m_Data[2].To_RGBA());
}

TEST_F(TMetaImageJson_test, deserialize_first_nonzero)
{
    json test = "[1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]"_json;
    auto lResult = test.get<TMetaImage>();
    ASSERT_EQ(64, lResult.m_Data.size());
    ASSERT_EQ(1, lResult.m_Data[0].To_RGBA());
    ASSERT_EQ(0, lResult.m_Data[1].To_RGBA());
    ASSERT_EQ(0, lResult.m_Data[2].To_RGBA());
}

TEST_F(TMetaImageJson_test, deserialize_first_and_second_nonzero)
{
    json test = "[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]"_json;
    auto lResult = test.get<TMetaImage>();
    ASSERT_EQ(64, lResult.m_Data.size());
    ASSERT_EQ(1, lResult.m_Data[0].To_RGBA());
    ASSERT_EQ(2, lResult.m_Data[1].To_RGBA());
    ASSERT_EQ(0, lResult.m_Data[2].To_RGBA());
}

TEST_F(TMetaImageJson_test, cycle_json_zero)
{
    TMetaImage::TypeData lData;
    for (auto& element : lData)
        element = TColor::FromRGBA(0);

    json test = TMetaImage(std::move(lData));
    auto lResult = test.get<TMetaImage>();

    ASSERT_EQ(lData.size(), lResult.m_Data.size());
    ASSERT_EQ(true, TestEq(lData[0], lResult.m_Data[0]));
    ASSERT_EQ(true, TestEq(lData[1], lResult.m_Data[1]));
    ASSERT_EQ(true, TestEq(lData[2], lResult.m_Data[2]));
}

TEST_F(TMetaImageJson_test, cycle_json_first_nonzero)
{
    TMetaImage::TypeData lData;
    for (auto& element : lData)
        element = TColor::FromRGBA(0);

    lData[0] = TColor::FromRGBA(1);

    json test = TMetaImage(std::move(lData));
    auto lResult = test.get<TMetaImage>();

    ASSERT_EQ(lData.size(), lResult.m_Data.size());
    ASSERT_EQ(true, TestEq(lData[0], lResult.m_Data[0]));
    ASSERT_EQ(true, TestEq(lData[1], lResult.m_Data[1]));
    ASSERT_EQ(true, TestEq(lData[2], lResult.m_Data[2]));
}

TEST_F(TMetaImageJson_test, cycle_json_first_and_second_nonzero)
{
    TMetaImage::TypeData lData;
    for (auto& element : lData)
        element = TColor::FromRGBA(0);

    lData[0] = TColor::FromRGBA(1);
    lData[1] = TColor::FromRGBA(2);

    json test = TMetaImage(std::move(lData));
    auto lResult = test.get<TMetaImage>();

    ASSERT_EQ(lData.size(), lResult.m_Data.size());
    ASSERT_EQ(true, TestEq(lData[0], lResult.m_Data[0]));
    ASSERT_EQ(true, TestEq(lData[1], lResult.m_Data[1]));
    ASSERT_EQ(true, TestEq(lData[2], lResult.m_Data[2]));
}