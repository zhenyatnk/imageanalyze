#pragma once

#include <memory>
#include <string>
#include <vector>

namespace imageanalyzer {
namespace core {

class ILinearStream
{
public:
    typedef std::shared_ptr<ILinearStream> Ptr;

public:
    virtual ~ILinearStream() = default;

    virtual uint64_t Size() const = 0;
    virtual const void* GetBuff() const = 0;

    template<class Type>
    Type GetBuff() const
    {
        return static_cast<Type>(GetBuff());
    }

    template<class Type>
    Type GetElement(uint64_t aElement) const
    {
        if (Size() / sizeof(Type) < aElement)
            ;
        return *(GetBuff<const Type*>() + aElement);
    }
};

template<>
inline std::string ILinearStream::GetBuff() const
{
    return std::string(GetBuff<const char*>(), Size());
}

//-------------------------------------------------------------
class ILinearWriteStream
    :public ILinearStream
{
public:
    typedef std::shared_ptr<ILinearWriteStream> Ptr;

public:
    virtual ~ILinearWriteStream() = default;

    virtual void* GetBuff() = 0;

    template<class Type>
    Type GetBuff()
    {
        return static_cast<Type>(GetBuff());
    }
};

//-------------------------------------------------------------
class IStream
{
public:
    typedef std::shared_ptr<IStream> Ptr;

public:
    virtual ~IStream() = default;

    virtual uint64_t Size() const = 0;
    virtual size_t Read(uint64_t Offset, uint8_t* buffer, size_t size) const = 0;
    virtual IStream::Ptr Read(uint64_t Offset, size_t size) const = 0;
};

class IWriteStream
    :public virtual IStream
{
public:
    typedef std::shared_ptr<IWriteStream> Ptr;

public:
    virtual ~IWriteStream() = default;

    virtual void Write(uint64_t Offset, const uint8_t* buffer, size_t size) = 0;
    virtual void Write(uint64_t Offset, IStream::Ptr aStream) = 0;
};

//-------------------------------------------------------------------------------------
IStream::Ptr CreateStreamBuffer(const void* aBuff, const uint64_t &aSize);
IStream::Ptr CreateStreamBuffer(IStream::Ptr aStream);

ILinearStream::Ptr CreateLinearBuffer(const void* aBuff, const uint64_t &aSize);
ILinearStream::Ptr CreateLinearBuffer(IStream::Ptr aStream);
ILinearWriteStream::Ptr CreateLinearWriteBuffer(const uint64_t &aSize);

}
}
