#include "Ndxerr.h"
#include <stdio.h>
#include <string.h>

// ANSI �汾�����ظ�ʽ���� HRESULT �ַ���
const CHAR* WINAPI DXGetErrorStringA(_In_ HRESULT hr)
{
    // ʹ�þ�̬�������洢�ַ��������̰߳�ȫ��
    static CHAR s_str[64] = { 0 };
    sprintf_s(s_str, sizeof(s_str), "HRESULT 0x%08X", (unsigned int)hr);
    return s_str;
}

// Unicode �汾�����ظ�ʽ���� HRESULT �ַ���
const WCHAR* WINAPI DXGetErrorStringW(_In_ HRESULT hr)
{
    static WCHAR s_wstr[64] = { 0 };
    swprintf_s(s_wstr, sizeof(s_wstr) / sizeof(WCHAR), L"HRESULT 0x%08X", (unsigned int)hr);
    return s_wstr;
}

// ANSI �汾������ FormatMessageA �� hr ת��Ϊ������������д�� desc ������
void WINAPI DXGetErrorDescriptionA(_In_ HRESULT hr, _Out_cap_(count) CHAR* desc, _In_ size_t count)
{
    if (!desc || count == 0)
        return;

    desc[0] = '\0';

    CHAR* msgBuf = NULL;
    DWORD msgLen = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,   // ʹ��ϵͳ������Ϣ
        hr,
        0,      // Ĭ������
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

// Unicode �汾������ FormatMessageW �� hr ת��Ϊ������������д�� desc ������
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
        0,      // Ĭ������
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
