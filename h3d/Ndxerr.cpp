#include "Ndxerr.h"
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "dxguid.lib") // �������Ӵ˿�

//--------------------------------------------------
// DirectX ר�ô�������
//--------------------------------------------------

// ANSI �汾�����ظ�ʽ���� HRESULT �ַ���
const CHAR* WINAPI DXGetErrorStringA(_In_ HRESULT hr) {
    // ʹ���ֲ߳̾��洢������̳߳�ͻ
    static __declspec(thread) CHAR s_str[512] = { 0 };
    const CHAR* pMsg = nullptr;

    // �ȵ��ú���д�� s_str
    DXGetErrorDescriptionA(hr, s_str, sizeof(s_str));
    // ��黺�����Ƿ���д������
    if (s_str[0] != '\0') {
        pMsg = s_str;
    }
    else {
        sprintf_s(s_str, sizeof(s_str), "HRESULT 0x%08X", static_cast<unsigned int>(hr));
        pMsg = s_str;
    }
    return pMsg;
}

// Unicode �汾�����ظ�ʽ���� HRESULT �ַ���
const WCHAR* WINAPI DXGetErrorStringW(_In_ HRESULT hr) {
    static __declspec(thread) WCHAR s_wstr[512] = { 0 };
    const WCHAR* pMsg = nullptr;

    DXGetErrorDescriptionW(hr, s_wstr, sizeof(s_wstr) / sizeof(WCHAR));
    if (s_wstr[0] != L'\0') {
        pMsg = s_wstr;
    }
    else {
        swprintf_s(s_wstr, sizeof(s_wstr) / sizeof(WCHAR), L"HRESULT 0x%08X", static_cast<unsigned int>(hr));
        pMsg = s_wstr;
    }
    return pMsg;
}

//--------------------------------------------------
// ���Ĵ���������ȡ������֧�� DirectX ר�ô����룩
//--------------------------------------------------

// ANSI �汾����ȡ��ϸ�Ĵ�������
void WINAPI DXGetErrorDescriptionA(_In_ HRESULT hr, _Out_cap_(count) CHAR* desc, _In_ size_t count) {
    if (!desc || count == 0) return;

    // ��� desc
    desc[0] = '\0';

    // 1. ���Ի�ȡ DirectX ר�ô�������
    HMODULE hDxgiDebug = LoadLibraryExW(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (hDxgiDebug) {
        DWORD flags = FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS;
        CHAR* pMsgBuf = nullptr;
        if (FormatMessageA(
            flags,
            hDxgiDebug,
            hr,
            0,
            reinterpret_cast<LPSTR>(&pMsgBuf),
            0,
            nullptr
        ) && pMsgBuf)
        {
            strncpy_s(desc, count, pMsgBuf, _TRUNCATE);
            LocalFree(pMsgBuf);
            FreeLibrary(hDxgiDebug);
            return;
        }
        FreeLibrary(hDxgiDebug);
    }

    // 2. ���˵�ϵͳ��������
    FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        hr,
        0,
        desc,
        static_cast<DWORD>(count),
        nullptr
    );
}

// Unicode �汾����ȡ��ϸ�Ĵ�������
void WINAPI DXGetErrorDescriptionW(_In_ HRESULT hr, _Out_cap_(count) WCHAR* desc, _In_ size_t count) {
    if (!desc || count == 0) return;

    desc[0] = L'\0';

    HMODULE hDxgiDebug = LoadLibraryExW(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (hDxgiDebug) {
        DWORD flags = FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS;
        WCHAR* pMsgBuf = nullptr;
        if (FormatMessageW(
            flags,
            hDxgiDebug,
            hr,
            0,
            reinterpret_cast<LPWSTR>(&pMsgBuf),
            0,
            nullptr
        ) && pMsgBuf)
        {
            wcsncpy_s(desc, count, pMsgBuf, _TRUNCATE);
            LocalFree(pMsgBuf);
            FreeLibrary(hDxgiDebug);
            return;
        }
        FreeLibrary(hDxgiDebug);
    }

    FormatMessageW(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        hr,
        0,
        desc,
        static_cast<DWORD>(count),
        nullptr
    );
}
