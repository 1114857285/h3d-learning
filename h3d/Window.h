#pragma once
#include <Windows.h>
#include "MyException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <optional>
#include <memory>



class Window
{
public:
	class Exception :public MyException
	{
		using MyException::MyException;
	public:
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
	};
	class HrException:public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;

		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException :public Exception 
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};
private:
	//singleton managers registration/claenup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept ; 
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;

	};
public:
	Window(int width, int height, const char* name)noexcept;
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lPara) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lPara) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};

//error exception helper macro
#define CHWND_EXCEPT( hr ) Window::HrException( __LINE__,__FILE__,(hr) )
#define CHWND_LAST_EXCEPT() Window::HrException( __LINE__,__FILE__,GetLastError() )
#define CHWND_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )