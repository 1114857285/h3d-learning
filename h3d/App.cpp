#include "App.h"

App::App()
	:
	wnd(800, 600, "The DonKey Fart Box")
{}


int App::Go()
{

	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		// execute the game logic
		DoFrame();

	}

}

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	const float a = cos(timer.Peek()) / 2.0f + 0.5f;
	const float b = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd.Gfx().ClearBuffer(c, a, b);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}