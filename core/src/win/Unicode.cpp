#include <imageanalyzer/core/Unicode.hpp>
#include <windows.h>

namespace imageanalyzer {
namespace core {

std::wstring convert(const std::string& aValue)
{
    int slength = (int)aValue.length() + 1;
    int len = MultiByteToWideChar(CP_ACP, 0, aValue.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, aValue.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

std::string convert(const std::wstring& aValue)
{
    int slength = (int)aValue.length() + 1;
    int len = WideCharToMultiByte(CP_ACP, 0, aValue.c_str(), slength, 0, 0, 0, 0);
    char* buf = new char[len];
    WideCharToMultiByte(CP_ACP, 0, aValue.c_str(), slength, buf, len, 0, 0);
    std::string r(buf);
    delete[] buf;
    return r;
}

}
}
