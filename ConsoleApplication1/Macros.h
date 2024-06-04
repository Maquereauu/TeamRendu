#pragma once

#include <iostream>
#include <string>

// Macro Interface debug Dx12
#define ASSERT_FAILED(x)                                            \
{                                                           \
    HRESULT dhr = (x);                                      \
    if (FAILED(dhr))                                        \
    {                                                       \
        if (FACILITY_WINDOWS == HRESULT_FACILITY(dhr))      \
            dhr = HRESULT_CODE(dhr);                        \
                                                            \
        TCHAR* szErrMsg;                                    \
        if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dhr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&szErrMsg, 0, NULL) != 0) \
        {                                                   \
            std::wcout << szErrMsg;                         \
            LocalFree(szErrMsg);                            \
        }                                                   \
        else std::wcout << L"Could not find a description for error " << dhr << L'\n'; \
        __debugbreak();                                 \
    }                                                       \
    std::wcout << L"Success" << std::endl;\
}

// Macro pour print
#define PRINT(x) std::wcout << x << std::endl
