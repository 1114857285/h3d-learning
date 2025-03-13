#include <Windows.h>
#include <string>
#include <sstream>
#include "Window.h"


int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	try {

		Window wnd(800, 300, "Donkey Fart Box");
		//message pump
		MSG msg;
		BOOL gResult;
		while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
#if 0
			while (!wnd.mouse.IsEmpty())
			{
				const auto e = wnd.mouse.Read();
				if (e.GetType() == Mouse::Event::Type::Move)
				{
					std::ostringstream oss;
					oss << "Mouse Postion:(" << e.GetPosX() << "," << e.GetPosY();
					wnd.SetTitle(oss.str());
				}
				else if (e.GetType() == Mouse::Event::Type::LPress)
				{
					std::ostringstream oss;
					oss << "Mouse Pressed Postion:(" << e.GetPosX() << "," << e.GetPosY();
					wnd.SetTitle(oss.str());
				}
			}
#endif
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