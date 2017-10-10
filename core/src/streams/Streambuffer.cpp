#include <imageanalyzer/core/IStream.hpp>

#include <cstring>
#include <cstdlib>

namespace imageanalyzer {
namespace core {

class CStreamLinear
    :public ILinearStream
{
public:
    CStreamLinear(IStream::Ptr aStream);
    CStreamLinear(const void* aBuff, uint64_t aSize);
    ~CStreamLinear();

    virtual uint64_t Size() const override;
    virtual const void* GetBuff() const override;

private:
    void* m_Buff;
    uint64_t m_Size;
};

CStreamLinear::CStreamLinear(IStream::Ptr aStream)
    :m_Size(aStream->Size())
{
    m_Buff = malloc(m_Size);
    aStream->Read(0, (uint8_t*)m_Buff, m_Size);
}

CStreamLinear::CStreamLinear(const void* aBuff, uint64_t aSize)
    :m_Size(aSize)
{
    m_Buff = malloc(m_Size);
    memcpy(m_Buff, aBuff, m_Size);
}

CStreamLinear::~CStreamLinear()
{
    free(m_Buff);
}

uint64_t CStreamLinear::Size() const
{
    return m_Size;
}

const void* CStreamLinear::GetBuff() const
{
    return m_Buff;
}

ILinearStream::Ptr CreateLinearBuffer(const void* aBuff, const uint64_t &aSize)
{
    return ILinearStream::Ptr(new CStreamLinear(aBuff, aSize));
}
ILinearStream::Ptr CreateLinearBuffer(IStream::Ptr aStream)
{
    return ILinearStream::Ptr(new CStreamLinear(aStream));
}
//---------------------------------------------------------------------------------------
class CStreamLinearWrite
    :public ILinearWriteStream
{
public:
    CStreamLinearWrite(uint64_t aSize);
    ~CStreamLinearWrite();

    virtual uint64_t Size() const override;
    virtual const void* GetBuff() const override;
    virtual void* GetBuff() override;

private:
    void* m_Buff;
    uint64_t m_Size;
};

CStreamLinearWrite::CStreamLinearWrite(uint64_t aSize)
    :m_Size(aSize)
{
    m_Buff = malloc(m_Size);
    memset(m_Buff, 0, m_Size);
}

CStreamLinearWrite::~CStreamLinearWrite()
{
    free(m_Buff);
}

uint64_t CStreamLinearWrite::Size() const
{
    return m_Size;
}

const void* CStreamLinearWrite::GetBuff() const
{
    return m_Buff;
}

void* CStreamLinearWrite::GetBuff()
{
    return m_Buff;
}

ILinearWriteStream::Ptr CreateLinearWriteBuffer(const uint64_t &aSize)
{
    return ILinearWriteStream::Ptr(new CStreamLinearWrite(aSize));
}
//---------------------------------------------------------------------------------------
class CStreamBuffer
    :public IStream
{
public:
    CStreamBuffer(IStream::Ptr aStream);
    CStreamBuffer(const void* aBuff, uint64_t aSize);
    ~CStreamBuffer();

    virtual uint64_t Size() const override;
    virtual size_t Read(uint64_t Offset, uint8_t* buffer, size_t size) const override;
    virtual IStream::Ptr Read(uint64_t Offset, size_t size) const override;

private:
    void* m_Buff;
    uint64_t m_Size;
};

CStreamBuffer::CStreamBuffer(IStream::Ptr aStream)
    :m_Size(aStream->Size())
{
    m_Buff = malloc(m_Size);
    aStream->Read(0, (uint8_t*)m_Buff, m_Size);
}

CStreamBuffer::CStreamBuffer(const void* aBuff, uint64_t aSize)
    :m_Size(aSize)
{
    m_Buff = malloc(m_Size);
    memcpy(m_Buff, aBuff, m_Size);
}

CStreamBuffer::~CStreamBuffer()
{
    free(m_Buff);
}

uint64_t CStreamBuffer::Size() const
{
    return m_Size;
}

size_t CStreamBuffer::Read(uint64_t Offset, uint8_t* buffer, size_t size) const
{
    size_t lReadSize = 0;
    if (m_Size > Offset)
    {
        lReadSize = size;
        if (!!lReadSize && (Offset + lReadSize) > m_Size)
            lReadSize = m_Size - Offset;
        memcpy(buffer, (char*)m_Buff + Offset, lReadSize);
    }
    return lReadSize;
}

IStream::Ptr CStreamBuffer::Read(uint64_t Offset, size_t size) const
{
    IStream::Ptr lStreamBuffer;
    if (m_Size > Offset)
    {
        if (Offset + size > m_Size)
            size = m_Size - Offset;
        lStreamBuffer = CreateStreamBuffer((void*)((char*)m_Buff + Offset), size);
    }
    return lStreamBuffer;
}

IStream::Ptr CreateStreamBuffer(const void* aBuff, const uint64_t &aSize)
{
    return IStream::Ptr(new CStreamBuffer(aBuff, aSize));
}
IStream::Ptr CreateStreamBuffer(IStream::Ptr aStream)
{
    return IStream::Ptr(new CStreamBuffer(aStream));
}
//-------------------------------------------------------------------------------------

}
}
