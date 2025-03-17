#include <Windows.h>
#include <string>
#include <sstream>
#include "Window.h"
#include "App.h"


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
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