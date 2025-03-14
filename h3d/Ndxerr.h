#ifndef NDXERR_H
#define NDXERR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Windows.h>

    // ANSI 版本函数声明
    const CHAR* WINAPI DXGetErrorStringA(_In_ HRESULT hr);
    void WINAPI DXGetErrorDescriptionA(_In_ HRESULT hr, _Out_cap_(count) CHAR* desc, _In_ size_t count);

    // Unicode 版本函数声明
    const WCHAR* WINAPI DXGetErrorStringW(_In_ HRESULT hr);
    void WINAPI DXGetErrorDescriptionW(_In_ HRESULT hr, _Out_cap_(count) WCHAR* desc, _In_ size_t count);

#ifdef __cplusplus
}
#endif

// 自动适配宏定义
#ifdef UNICODE
#define DXGetErrorString          DXGetErrorStringW
#define DXGetErrorDescription     DXGetErrorDescriptionW
#else
#define DXGetErrorString          DXGetErrorStringA
#define DXGetErrorDescription     DXGetErrorDescriptionA
#endif

#endif // NDXERR_H
