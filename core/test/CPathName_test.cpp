#include <imageanalyzer/core/CPathName.hpp>

#include <gtest/gtest.h>

//--------------------------------------------------
using namespace imageanalyzer::core;

class CPathName_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(CPathName_test, ToString)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1");
}

TEST_F(CPathName_test, Ctor1)
{
    CPathName lPathName(L"path/path1\\");
    lPathName.SetSeparator(L"/");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1");
}

TEST_F(CPathName_test, Ctor2)
{
    CPathName lPathName(L"path/path1/");
    lPathName.SetSeparator(L"/");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1");
}

TEST_F(CPathName_test, Ctor3)
{
    CPathName lPathName(L"path/path1//");
    lPathName.SetSeparator(L"/");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1");
}

TEST_F(CPathName_test, Ctor4)
{
    CPathName lPathName(L"path/path1//\\");
    lPathName.SetSeparator(L"/");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1");
}

TEST_F(CPathName_test, Ctor5)
{
    CPathName lPathName(L"\\\\path/path1//\\");
    lPathName.SetSeparator(L"\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"\\\\path\\path1");
}
TEST_F(CPathName_test, AddPath1)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    lPathName.AddPath(L"path3");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1/path3");
}

TEST_F(CPathName_test, AddPath2)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    lPathName.AddPath(L"path3/path4");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1/path3/path4");
}

TEST_F(CPathName_test, AddPath_exclude_sep_1)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    lPathName.AddPath(L"path3\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1/path3");
}

TEST_F(CPathName_test, AddPath_exclude_sep_2)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    lPathName.AddPath(L"path3\\/");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1/path3");
}

TEST_F(CPathName_test, AddPath_exclude_sep_3)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    lPathName.AddPath(L"/path3\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1/path3");
}

TEST_F(CPathName_test, AddPath_exclude_sep_4)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    lPathName.AddPath(L"\\/path3\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1/path3");
}

TEST_F(CPathName_test, AddPath_type_path)
{
    CPathName lPathName(L"path/path1");
    lPathName.SetSeparator(L"/");
    lPathName.AddPath(CPathName(L"\\/path3\\"));
    ASSERT_STREQ(lPathName.ToString().c_str(), L"path/path1/path3");
}