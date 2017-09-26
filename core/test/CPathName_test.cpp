// EXCEPT WHERE OTHERWISE STATED, THE INFORMATION AND SOURCE CODE CONTAINED
// HEREIN AND IN RELATED FILES IS THE EXCLUSIVE PROPERTY OF PARAGON SOFTWARE
// GROUP COMPANY AND MAY NOT BE EXAMINED, DISTRIBUTED, DISCLOSED, OR REPRODUCED
// IN WHOLE OR IN PART WITHOUT EXPLICIT WRITTEN AUTHORIZATION FROM THE COMPANY.
//
// Copyright (c) 1994-2016 Paragon Software Group, All rights reserved.
//
// UNLESS OTHERWISE AGREED IN A WRITING SIGNED BY THE PARTIES, THIS SOFTWARE IS
// PROVIDED "AS-IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE, ALL OF WHICH ARE HEREBY DISCLAIMED. IN NO EVENT SHALL THE
// AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF NOT ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.

#include <imageanalyzer/core/CPathName.hpp>

#include <gtest/gtest.h>

//--------------------------------------------------
class CPathName_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(CPathName_test, ToString)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1");
}

TEST_F(CPathName_test, Ctor1)
{
    imageanalyzer::core::CPathName lPathName("path/path1\\");
    lPathName.SetSeparator("/");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1");
}

TEST_F(CPathName_test, Ctor2)
{
    imageanalyzer::core::CPathName lPathName("path/path1/");
    lPathName.SetSeparator("/");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1");
}

TEST_F(CPathName_test, Ctor3)
{
    imageanalyzer::core::CPathName lPathName("path/path1//");
    lPathName.SetSeparator("/");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1");
}

TEST_F(CPathName_test, Ctor4)
{
    imageanalyzer::core::CPathName lPathName("path/path1//\\");
    lPathName.SetSeparator("/");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1");
}

TEST_F(CPathName_test, Ctor5)
{
    imageanalyzer::core::CPathName lPathName("\\\\path/path1//\\");
    lPathName.SetSeparator("\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), "\\\\path\\path1");
}
TEST_F(CPathName_test, AddPath1)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    lPathName.AddPath("path3");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1/path3");
}

TEST_F(CPathName_test, AddPath2)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    lPathName.AddPath("path3/path4");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1/path3/path4");
}

TEST_F(CPathName_test, AddPath_exclude_sep_1)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    lPathName.AddPath("path3\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1/path3");
}

TEST_F(CPathName_test, AddPath_exclude_sep_2)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    lPathName.AddPath("path3\\/");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1/path3");
}

TEST_F(CPathName_test, AddPath_exclude_sep_3)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    lPathName.AddPath("/path3\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1/path3");
}

TEST_F(CPathName_test, AddPath_exclude_sep_4)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    lPathName.AddPath("\\/path3\\");
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1/path3");
}

TEST_F(CPathName_test, AddPath_type_path)
{
    imageanalyzer::core::CPathName lPathName("path/path1");
    lPathName.SetSeparator("/");
    lPathName.AddPath(imageanalyzer::core::CPathName("\\/path3\\"));
    ASSERT_STREQ(lPathName.ToString().c_str(), "path/path1/path3");
}