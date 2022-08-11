#pragma once
#include <d3d11.h>
#include "Define.h"
#include "singleton.hpp"

namespace Engine2D
{
	enum class CullingMode
	{
		NONE,
		FRONT,
		BACK,
		MAX
	};
	class DX11 final : public Singleton<DX11>
	{
	private:
		HRESULT Create(HWND hwnd, UINT width, UINT height, bool fullscreen);
	
	public:
		DX11();
		virtual ~DX11();
		void Init(HWND hwnd, UINT width, UINT height, bool fullscreen);
		void SetCulling(CullingMode mode);

		ComPtr<ID3D11Device> GetDevice();
		ComPtr<ID3D11DeviceContext> GetContext();
		ComPtr<IDXGISwapChain> GetSwapChain();
		ComPtr<ID3D11RenderTargetView> GetRenderTargetView();

		HRESULT GetLastError() { return lastError; }
	private:
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;
		ComPtr<IDXGISwapChain> swapChain;
		ComPtr<ID3D11RenderTargetView> renderTargetView;
		ComPtr<ID3D11RasterizerState> rasterizer[(int)CullingMode::MAX];
		HRESULT lastError;
	};
}