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

#include <imageanalyzer/core/IImage.hpp>

#include <gtest/gtest.h>

//--------------------------------------------------
using namespace imageanalyzer::core;

class CImage_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(CImage_test, GetSize_Width_3x3)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_1.png"));
    ASSERT_EQ(3, lImage->GetSize().m_Width);
}

TEST_F(CImage_test, GetSize_Height_3x3)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_1.png"));
    ASSERT_EQ(3, lImage->GetSize().m_Height);
}

TEST_F(CImage_test, GetSize_Width_1x3)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_2.png"));
    ASSERT_EQ(1, lImage->GetSize().m_Width);
}

TEST_F(CImage_test, GetSize_Height_1x3)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_2.png"));
    ASSERT_EQ(3, lImage->GetSize().m_Height);
}

TEST_F(CImage_test, GetSize_Width_3x1)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_3.png"));
    ASSERT_EQ(3, lImage->GetSize().m_Width);
}

TEST_F(CImage_test, GetSize_Height_3x1)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_3.png"));
    ASSERT_EQ(1, lImage->GetSize().m_Height);
}

TEST_F(CImage_test, GetColor_Black)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_1.png"));
    ASSERT_EQ(TColor(0, 0, 0), lImage->GetColor({ 0,0 }));
}

TEST_F(CImage_test, GetColor_White)
{
    IImage::Ptr lImage = CreateImage(CFileName("../CImage_test_1.png"));
    ASSERT_EQ(TColor(255, 255, 255), lImage->GetColor({ 1,0 }));
}