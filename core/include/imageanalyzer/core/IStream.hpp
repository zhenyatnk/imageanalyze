#pragma once

#include <imageanalyzer/core/IStreamException.hpp>

#include <memory>
#include <string>
#include <vector>

namespace imageanalyzer {
namespace core {

class IMAGEANALYZER_CORE_EXPORT ILinearStream
{
public:
    typedef std::shared_ptr<ILinearStream> Ptr;

public:
    virtual ~ILinearStream() = default;

    virtual size_t Size() const = 0;
    virtual const void* GetBuff() const = 0;

    template<class Type>
    size_t Size() const
    {
        return Size() / sizeof(Type);
    }

    template<class Type>
    Type GetBuff() const
    {
        return static_cast<Type>(GetBuff());
    }

    template<class Type>
    Type GetElement(uint64_t aElement) const
    {
        CHECK_THROW_BOOL((Size<Type>() > aElement),
            exceptions::stream_error, "Stream index out of bounds. Size stream='" + std::to_string(Size<Type>()) + "' Requsted index='" + std::to_string(aElement) + "'.");
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

    virtual size_t Size() const = 0;
    virtual size_t Read(size_t Offset, uint8_t* buffer, size_t size) const = 0;
    virtual IStream::Ptr Read(size_t Offset, size_t size) const = 0;

    template<class Type>
    size_t Size() const
    {
        return Size() / sizeof(Type);
    }
};

class IWriteStream
    :public virtual IStream
{
public:
    typedef std::shared_ptr<IWriteStream> Ptr;

public:
    virtual ~IWriteStream() = default;

    virtual void Write(size_t Offset, const uint8_t* buffer, size_t size) = 0;
    virtual void Write(size_t Offset, IStream::Ptr aStream) = 0;
};

//-------------------------------------------------------------------------------------
IMAGEANALYZER_CORE_EXPORT IStream::Ptr CreateStreamBuffer(const void* aBuff, const size_t &aSize);
IMAGEANALYZER_CORE_EXPORT IStream::Ptr CreateStreamBuffer(IStream::Ptr aStream);

IMAGEANALYZER_CORE_EXPORT ILinearStream::Ptr CreateLinearBuffer(const void* aBuff, const size_t &aSize);
IMAGEANALYZER_CORE_EXPORT ILinearStream::Ptr CreateLinearBuffer(IStream::Ptr aStream);

IMAGEANALYZER_CORE_EXPORT ILinearWriteStream::Ptr CreateLinearWriteBuffer(const size_t &aSize);

}
}
