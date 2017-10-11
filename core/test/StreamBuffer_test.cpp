#include <imageanalyzer/core/IStream.hpp>
#include <gtest/gtest.h>

namespace
{
std::string ConvertToString(imageanalyzer::core::IStream::Ptr aStream)
{
    uint8_t *lBuffer = new uint8_t[aStream->Size()];
    aStream->Read(0, lBuffer, aStream->Size());
    std::string lRet((char*)lBuffer, aStream->Size());
    delete[] lBuffer;
    return lRet;
}
std::string ConvertToString(imageanalyzer::core::ILinearStream::Ptr aStream)
{
     return std::string(aStream->GetBuff<const char*>(), aStream->Size());
}
}

class StreamBuffer_test_stage_0
    :public ::testing::Test
{
public:
	void SetUp()
	{}
};

//--------------------------------------------------------------------------------------------------------------------------------------
TEST_F(StreamBuffer_test_stage_0, size)
{
    std::string lNominal = "test1 test2";
    imageanalyzer::core::IStream::Ptr lStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    ASSERT_EQ(lNominal.size(), lStream->Size());
}

TEST_F(StreamBuffer_test_stage_0, read_buffer_full)
{
    std::string lNominal = "test1 test2";
    imageanalyzer::core::IStream::Ptr lStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    uint8_t *lResult = new uint8_t[lStream->Size() + 1];
    lStream->Read(0, lResult, lStream->Size());
    lResult[lStream->Size()] = 0;
    EXPECT_STREQ(lNominal.c_str(), (char*)lResult);
    delete[] lResult;
}

TEST_F(StreamBuffer_test_stage_0, read_buffer_fisrt_part)
{
    std::string lNominalPart = "test1";
    std::string lNominal = lNominalPart + " test2";
    
    imageanalyzer::core::IStream::Ptr lStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    uint8_t *lResult = new uint8_t[lNominalPart.size() + 1];
    lStream->Read(0, lResult, lNominalPart.size());
    lResult[lNominalPart.size()] = 0;

    EXPECT_STREQ(lNominalPart.c_str(), (char*)lResult);
    delete[] lResult;
}

TEST_F(StreamBuffer_test_stage_0, read_buffer_second_part)
{
    std::string lNominalPart = "test1";
    std::string lNominal = lNominalPart + " test2";

    imageanalyzer::core::IStream::Ptr lStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    unsigned lSecondPartSize = lNominal.size() - lNominalPart.size();
    uint8_t *lResult = new uint8_t[lSecondPartSize + 1];
    lStream->Read(lNominalPart.size(), lResult, lSecondPartSize);
    lResult[lSecondPartSize] = 0;

    EXPECT_STREQ(" test2", (char*)lResult);
    delete[] lResult;
}

TEST_F(StreamBuffer_test_stage_0, read_buffer_big_size)
{
    std::string lNominalPart = "test1";
    std::string lNominal = lNominalPart + " test2";

    imageanalyzer::core::IStream::Ptr lStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    unsigned lSecondPartSize = 1024;
    uint8_t *lResult = new uint8_t[lSecondPartSize];
    lResult[lStream->Read(lNominalPart.size(), lResult, lSecondPartSize)] = 0;

    EXPECT_STREQ(" test2", (char*)lResult);
    delete[] lResult;
}

TEST_F(StreamBuffer_test_stage_0, read_stream_size_full)
{
    std::string lNominal = "test1 test2";
    imageanalyzer::core::IStream::Ptr lNominalStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    imageanalyzer::core::IStream::Ptr lResultStream = lNominalStream->Read(0, lNominalStream->Size());

    ASSERT_EQ(lNominalStream->Size(), lResultStream->Size());
}

TEST_F(StreamBuffer_test_stage_0, read_stream_size_part)
{
    std::string lNominal = "test1 test2";
    imageanalyzer::core::IStream::Ptr lNominalStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    imageanalyzer::core::IStream::Ptr lResultStream = lNominalStream->Read(0, 5);

    ASSERT_EQ(5, lResultStream->Size());
}

TEST_F(StreamBuffer_test_stage_0, read_stream_data_full)
{
    std::string lNominal = "test1 test2";
    imageanalyzer::core::IStream::Ptr lNominalStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    imageanalyzer::core::IStream::Ptr lResultStream = lNominalStream->Read(0, lNominalStream->Size());

    ASSERT_STREQ(ConvertToString(lNominalStream).c_str(), ConvertToString(lResultStream).c_str());
}

TEST_F(StreamBuffer_test_stage_0, read_stream_data_first_part)
{
    std::string lNominalPart = "test1";
    std::string lNominal = lNominalPart + " test2";

    imageanalyzer::core::IStream::Ptr lNominalStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    imageanalyzer::core::IStream::Ptr lResultStream = lNominalStream->Read(0, lNominalPart.size());

    ASSERT_STREQ(lNominalPart.c_str(), ConvertToString(lResultStream).c_str());
}

TEST_F(StreamBuffer_test_stage_0, read_stream_data_second_part)
{
    std::string lNominalPart = "test1";
    std::string lNominal = lNominalPart + " test2";
    unsigned lSecondPartSize = lNominal.size() - lNominalPart.size();

    imageanalyzer::core::IStream::Ptr lNominalStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    imageanalyzer::core::IStream::Ptr lResultStream = lNominalStream->Read(lNominalPart.size(), lSecondPartSize);

    ASSERT_STREQ(" test2", ConvertToString(lResultStream).c_str());
}

TEST_F(StreamBuffer_test_stage_0, read_stream_data_big_size)
{
    std::string lNominalPart = "test1";
    std::string lNominal = lNominalPart + " test2";
    unsigned lSecondPartSize = lNominal.size() - lNominalPart.size();

    imageanalyzer::core::IStream::Ptr lNominalStream = imageanalyzer::core::CreateStreamBuffer(lNominal.c_str(), lNominal.size());
    imageanalyzer::core::IStream::Ptr lResultStream = lNominalStream->Read(lNominalPart.size(), 1024);

    ASSERT_STREQ(" test2", ConvertToString(lResultStream).c_str());
}

TEST_F(StreamBuffer_test_stage_0, write_linear_stream_write)
{
    std::string lPart1 = "test1";
    std::string lPart2 = "test2";
    imageanalyzer::core::ILinearWriteStream::Ptr lStreamWrite = imageanalyzer::core::CreateLinearWriteBuffer(lPart1.size() + lPart1.size());
    memcpy(lStreamWrite->GetBuff<char*>(), lPart1.c_str(), lPart1.size());
    memcpy(lStreamWrite->GetBuff<char*>() + lPart1.size(), lPart2.c_str(), lPart2.size());

    ASSERT_STREQ("test1test2", ConvertToString(lStreamWrite).c_str());
}

