#include <imageanalyzer/core/TMetaImageJson.hpp>

#include <gtest/gtest.h>

using namespace imageanalyzer::core;
using namespace nlohmann;
//--------------------------------------------------

class THistogramJson_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(THistogramJson_test, serialize_zero)
{
    THistogram lTestObject;
    json test = lTestObject;
    ASSERT_STREQ("{\"data\":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}", test.dump().c_str());
}

TEST_F(THistogramJson_test, serialize_first_nonzero)
{
    THistogram lTestObject;
    lTestObject.m_Data[0] = 1;
    json test = lTestObject;
    ASSERT_STREQ("{\"data\":[1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}", test.dump().c_str());
}

TEST_F(THistogramJson_test, serialize_first_and_second_nonzero)
{
    THistogram lTestObject;
    lTestObject.m_Data[0] = 1;
    lTestObject.m_Data[1] = 2;
    json test = lTestObject;
    ASSERT_STREQ("{\"data\":[1.0,2.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}", test.dump().c_str());
}

TEST_F(THistogramJson_test, deserialize_zero)
{
    json test = "{\"data\":[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}"_json;
    auto lResult = test.get<THistogram>();
    ASSERT_EQ(64, lResult.m_Data.size());
    ASSERT_EQ(0.0, lResult.m_Data[0]);
    ASSERT_EQ(0.0, lResult.m_Data[1]);
    ASSERT_EQ(0.0, lResult.m_Data[2]);
}

TEST_F(THistogramJson_test, deserialize_float_first)
{
    json test = "{\"data\":[1.198,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}"_json;
    auto lResult = test.get<THistogram>();
    ASSERT_EQ(64, lResult.m_Data.size());
    ASSERT_FLOAT_EQ((float)1.198, lResult.m_Data[0]);
}

TEST_F(THistogramJson_test, deserialize_first_nonzero)
{
    json test = "{\"data\":[1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}"_json;
    auto lResult = test.get<THistogram>();
    ASSERT_EQ(64, lResult.m_Data.size());
    ASSERT_EQ(1, lResult.m_Data[0]);
    ASSERT_EQ(0.0, lResult.m_Data[1]);
    ASSERT_EQ(0.0, lResult.m_Data[2]);
}

TEST_F(THistogramJson_test, deserialize_first_and_second_nonzero)
{
    json test = "{\"data\":[1.0,2.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]}"_json;
    auto lResult = test.get<THistogram>();
    ASSERT_EQ(64, lResult.m_Data.size());
    ASSERT_EQ(1, lResult.m_Data[0]);
    ASSERT_EQ(2, lResult.m_Data[1]);
    ASSERT_EQ(0.0, lResult.m_Data[2]);
}

TEST_F(THistogramJson_test, cycle_json_zero)
{
    THistogram lTestObject;
    json test = lTestObject;
    auto lResult = test.get<THistogram>();

    ASSERT_EQ(lTestObject.m_Data.size(), lResult.m_Data.size());
    ASSERT_EQ(lTestObject.m_Data[0], lResult.m_Data[0]);
    ASSERT_EQ(lTestObject.m_Data[1], lResult.m_Data[1]);
    ASSERT_EQ(lTestObject.m_Data[2], lResult.m_Data[2]);
}

TEST_F(THistogramJson_test, cycle_json_first_nonzero)
{
    THistogram lTestObject;
    lTestObject.m_Data[0] = 1;

    json test = lTestObject;
    auto lResult = test.get<THistogram>();

    ASSERT_EQ(lTestObject.m_Data.size(), lResult.m_Data.size());
    ASSERT_EQ(lTestObject.m_Data[0], lResult.m_Data[0]);
    ASSERT_EQ(lTestObject.m_Data[1], lResult.m_Data[1]);
    ASSERT_EQ(lTestObject.m_Data[2], lResult.m_Data[2]);
}

TEST_F(THistogramJson_test, cycle_json_first_and_second_nonzero)
{
    THistogram lTestObject;

    lTestObject.m_Data[0] = 1;
    lTestObject.m_Data[1] = 2;

    json test = lTestObject;
    auto lResult = test.get<THistogram>();

    ASSERT_EQ(lTestObject.m_Data.size(), lResult.m_Data.size());
    ASSERT_EQ(lTestObject.m_Data[0], lResult.m_Data[0]);
    ASSERT_EQ(lTestObject.m_Data[1], lResult.m_Data[1]);
    ASSERT_EQ(lTestObject.m_Data[2], lResult.m_Data[2]);
}