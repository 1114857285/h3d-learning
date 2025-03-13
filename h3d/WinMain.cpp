#include <Windows.h>
#include <string>
#include <sstream>
#include "Window.h"

/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "Dangerfield");
		}
		break;
	case WM_CHAR:
		{
			static std::string title;
			title.push_back((char)wParam);
			SetWindowText(hWnd, title.c_str());
		}
		break;
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd,oss.str().c_str());
	}

	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
*/

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
#if 0
	const auto pClassName = "hw3d";
	//register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor= nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
	//creat window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName, "Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);
	ShowWindow(hWnd, SW_SHOW);
#endif
	try {

		Window wnd(800, 300, "Donkey Fart Box");
		//message pump
		MSG msg;
		BOOL gResult;
		while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (wnd.kbd.KeyIsPressed(VK_MENU))
			{
				MessageBox(nullptr, "SomethingHappen!", "Space KeyPressed!",MB_OK);
			}
		}
		if (gResult == -1)
			return -1;

		return msg.wParam;
	}
	catch (const MyException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr,e.what(),"Standard Exceprion",MB_OK| MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unkonwn Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}