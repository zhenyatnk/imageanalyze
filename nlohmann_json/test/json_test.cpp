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

#include <imageanalyzer/nlohmann_json/json.hpp>
#include <gtest/gtest.h>

using namespace nlohmann;

//--------------------------------------------------------------------------------------------------------------------------------------
class json_test
    :public ::testing::Test
{
public:
	void SetUp()
	{}
};

//--------------------------------------------------------------------------------------------------------------------------------------
TEST_F(json_test, serialization_field_number)
{
    json test;
    test["test_field"] = 1;

    ASSERT_STREQ(test.dump().c_str(), "{\"test_field\":1}");
}

TEST_F(json_test, serialization_field_string)
{
    json test;
    test["test_field"] = "test value";

    ASSERT_STREQ(test.dump().c_str(), "{\"test_field\":\"test value\"}");
}

TEST_F(json_test, deserialization_field_number)
{
    json test;
    test["test_field"] = 1;

    ASSERT_EQ(test["test_field"].get<int>(), 1);
}

TEST_F(json_test, deserialization_field_string)
{
    json test;
    test["test_field"] = "test value";

    ASSERT_EQ(test["test_field"].get<std::string>(), "test value");
}

TEST_F(json_test, deserialization_exist_field)
{
    json test;
    test["test_field"] = "test value";

    ASSERT_EQ(test["test_field"].empty(), false);
}

TEST_F(json_test, deserialization_exist_field1)
{
    json test;
    test["test_field"] = "";

    ASSERT_EQ(test["test_field"].empty(), false);
}

TEST_F(json_test, deserialization_non_field)
{
    json test;
    test["test_field"] = "test value";

    ASSERT_EQ(test["non_exist"].empty(), true);
}
