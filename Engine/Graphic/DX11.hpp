#pragma once
#include <d3d11.h>
#include <memory>
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
	class D3D11 final : public Singleton<D3D11>
	{
	private:
		HRESULT Create(HWND hwnd, UINT width, UINT height, bool fullscreen);
	
	public:
		D3D11();
		virtual ~D3D11();
		void Init(HWND hwnd, UINT width, UINT height, bool fullscreen);
		void SetCulling(CullingMode mode);
		void Release();
		void BeginFrame() {};
		void Render() {};
		void EndFrame() {};

		inline std::weak_ptr<ID3D11Device> GetDevice();
		inline std::weak_ptr<ID3D11DeviceContext> GetContext();
		inline std::weak_ptr<IDXGISwapChain> GetSwapChain();
		inline std::weak_ptr<ID3D11RenderTargetView> GetRenderTargetView();

		inline HRESULT GetLastError() { return lastError; }
	private:
		std::shared_ptr<ID3D11Device> device;
		std::shared_ptr<ID3D11DeviceContext> context;
		std::shared_ptr<IDXGISwapChain> swapChain;
		std::shared_ptr<ID3D11RenderTargetView> renderTargetView;
		std::shared_ptr<ID3D11RasterizerState> rasterizer[(int)CullingMode::MAX];
		HRESULT lastError;
	};
}