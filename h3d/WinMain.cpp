#include <Windows.h>
#include <string>
#include <sstream>
#include "Window.h"
#include "wantSee.h"
#include "App.h"


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
#if 1
    int res = MessageBox(NULL, "¥­¥å©`¥ÖÒŠ¤¿¤¤¤Ç¤¹¤«£¿", "ßx’k", MB_YESNO | MB_ICONQUESTION);
    int res2 = 0;
    switch (res)
    {
    case IDYES:
        res2 = MessageBox(NULL, "É«¸¶¤­¤Þ¤¹¤«£¿", "ßx’k", MB_YESNO | MB_ICONQUESTION);
        if(res2==IDYES)
        break;
        else
        {
            wantSee = 1;
            break;
        }
    case IDNO:
        return 0;
    }
#endif
    try {
        return App{}.Go();
    }
    catch (const Graphics::HrException& e) {
        MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONERROR);
    }
    catch (const MyException& e) {
        MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONERROR);
    }
    catch (const std::exception& e) {
        MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONERROR);
    }
    catch (...) {
        MessageBox(nullptr, "Unknown Error", "Unknown Exception", MB_OK | MB_ICONERROR);
    }
    return -1;
}