#include "Ndxerr.h"
#include <stdio.h>
#include <string.h>

// ANSI 版本：返回格式化的 HRESULT 字符串
const CHAR* WINAPI DXGetErrorStringA(_In_ HRESULT hr)
{
    // 使用静态缓冲区存储字符串（非线程安全）
    static CHAR s_str[64] = { 0 };
    sprintf_s(s_str, sizeof(s_str), "HRESULT 0x%08X", (unsigned int)hr);
    return s_str;
}

// Unicode 版本：返回格式化的 HRESULT 字符串
const WCHAR* WINAPI DXGetErrorStringW(_In_ HRESULT hr)
{
    static WCHAR s_wstr[64] = { 0 };
    swprintf_s(s_wstr, sizeof(s_wstr) / sizeof(WCHAR), L"HRESULT 0x%08X", (unsigned int)hr);
    return s_wstr;
}

// ANSI 版本：利用 FormatMessageA 将 hr 转换为错误描述，并写入 desc 缓冲区
void WINAPI DXGetErrorDescriptionA(_In_ HRESULT hr, _Out_cap_(count) CHAR* desc, _In_ size_t count)
{
    if (!desc || count == 0)
        return;

    desc[0] = '\0';

    CHAR* msgBuf = NULL;
    DWORD msgLen = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,   // 使用系统错误消息
        hr,
        0,      // 默认语言
        (LPSTR)&msgBuf,
        0,
        NULL
    );

    if (msgLen > 0 && msgBuf)
    {
        strncpy_s(desc, count, msgBuf, _TRUNCATE);
        LocalFree(msgBuf);
    }
    else
    {
        strncpy_s(desc, count, "Unknown error", _TRUNCATE);
    }
}

// Unicode 版本：利用 FormatMessageW 将 hr 转换为错误描述，并写入 desc 缓冲区
void WINAPI DXGetErrorDescriptionW(_In_ HRESULT hr, _Out_cap_(count) WCHAR* desc, _In_ size_t count)
{
    if (!desc || count == 0)
        return;

    desc[0] = L'\0';

    WCHAR* msgBuf = NULL;
    DWORD msgLen = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        hr,
        0,      // 默认语言
        (LPWSTR)&msgBuf,
        0,
        NULL
    );

    if (msgLen > 0 && msgBuf)
    {
        wcsncpy_s(desc, count, msgBuf, _TRUNCATE);
        LocalFree(msgBuf);
    }
    else
    {
        wcsncpy_s(desc, count, L"Unknown error", _TRUNCATE);
    }
}
