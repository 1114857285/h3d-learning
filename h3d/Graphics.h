#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <directxmath.h>
#include "MyException.h"
#include <vector>
#include <wrl.h>
#include "DxgiInfoManager.h"
#include "GraphicsThrowMacros.h"
#include <stdexcept>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>

class Graphics
{
	friend class Bindable;
public:
	class Exception :public MyException
	{
		using MyException::MyException;
	};
	class HrException :public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what()const noexcept override;
		const char* GetType()const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException :public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&)=delete;
	Graphics& operator= (const Graphics&) = delete;
	~Graphics()=default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue)noexcept;
	void DrawIndexed(UINT count) noexcept(NDEBUG);
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
private:
	UINT width;
	UINT height;
	DirectX::XMMATRIX projection;
	//DirectX::XMMATRIX camera;
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
private:
	Microsoft::WRL::ComPtr<ID3D11Device>pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain>pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>pContext;
	Microsoft::WRL::ComPtr< ID3D11RenderTargetView>pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>pDSV;
};