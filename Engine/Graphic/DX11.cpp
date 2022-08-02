#include "pch.h"

#include "DX11.hpp"
#include <memory>
#include "safe_release.h"

namespace Engine2D
{
	HRESULT D3D11::Create(HWND hwnd, UINT width, UINT height, bool fullscreen)
	{
		HRESULT	_hr = E_FAIL;

		// スワップチェインの設定
		// スワップチェインとは、ウインドウへの表示ダブルバッファを管理する
		// マルチサンプリング、リフレッシュレートが設定できる
		// 複数のバックバッファが作成できる
		DXGI_SWAP_CHAIN_DESC _sd{};							// ゼロクリア
		_sd.BufferDesc.Width = width;						// バックバッファの幅
		_sd.BufferDesc.Height = height;						// バックバッファの高さ
		_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// バックバッファフォーマット(R,G,B,A)
		_sd.SampleDesc.Count = 1;			// マルチサンプルの数
		_sd.BufferDesc.RefreshRate.Numerator = 1000;
		_sd.BufferDesc.RefreshRate.Denominator = 1;
		_sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// バックバッファの使用方法
		_sd.BufferCount = 1;									// バックバッファの数
		_sd.OutputWindow = hwnd;								// 関連付けるウインドウ
		_sd.Windowed = fullscreen ? FALSE : TRUE;
		//_sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


		// ドライバの種類
		const D3D_DRIVER_TYPE _driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
			D3D_DRIVER_TYPE_WARP,		// 高精度(低速
			D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
		};
		const UINT _numDriverTypes = ARRAYSIZE(_driverTypes);

		UINT _createDeviceFlags = 0;
		// createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		// 機能レベル
		const D3D_FEATURE_LEVEL _featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
			D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
			D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
			D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
			D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
			D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
			D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
		};
		const UINT _numFeatureLevels = ARRAYSIZE(_featureLevels);

		D3D_DRIVER_TYPE _driverType;
		D3D_FEATURE_LEVEL _featureLevel;
		ID3D11Device* _device;
		IDXGISwapChain* _swapChain;
		ID3D11DeviceContext* _context;
		for (UINT _driverTypeIndex = 0; _driverTypeIndex < _numDriverTypes; ++_driverTypeIndex)
		{
			_driverType = _driverTypes[_driverTypeIndex];
			_hr = D3D11CreateDeviceAndSwapChain(
				NULL,					// ディスプレイデバイスのアダプタ（NULLの場合最初に見つかったアダプタ）
				_driverType,			// デバイスドライバのタイプ
				NULL,					// ソフトウェアラスタライザを使用する場合に指定する
				_createDeviceFlags,		// デバイスフラグ
				_featureLevels,			// 機能レベル
				_numFeatureLevels,		// 機能レベル数
				D3D11_SDK_VERSION,		// 
				&_sd,					// スワップチェインの設定
				&_swapChain,			// IDXGIDwapChainインタフェース	
				&_device,				// ID3D11Deviceインタフェース
				&_featureLevel,		// サポートされている機能レベル
				&_context);		// デバイスコンテキスト
			if (SUCCEEDED(_hr)) 
			{
				swapChain.reset(_swapChain);
				device.reset(_device);
				context.reset(_context);
				break;
			}
		}
		if (FAILED(_hr))	return _hr;

		//--- ラスタライズ
		D3D11_RASTERIZER_DESC _rasterDesc{};
		ID3D11RasterizerState* _rasterizer[(int)CullingMode::MAX]{};
	
		_rasterDesc.FillMode = D3D11_FILL_SOLID;
		_rasterDesc.CullMode = D3D11_CULL_NONE;
		_hr = device->CreateRasterizerState(&_rasterDesc, &_rasterizer[(int)CullingMode::NONE]);
		if (FAILED(_hr)) { return _hr; }
		_rasterDesc.CullMode = D3D11_CULL_FRONT;
		_hr = device->CreateRasterizerState(&_rasterDesc, &_rasterizer[(int)CullingMode::FRONT]);
		if (FAILED(_hr)) { return _hr; }
		_rasterDesc.CullMode = D3D11_CULL_BACK;
		_hr = device->CreateRasterizerState(&_rasterDesc, &_rasterizer[(int)CullingMode::BACK]);
		if (FAILED(_hr)) { return _hr; }
		for (int i = 0; i < (int)CullingMode::MAX; ++i)
		{
			rasterizer[i].reset(_rasterizer[i]);
		}
		SetCulling(CullingMode::NONE);

		return S_OK;
	}
	D3D11::D3D11(HWND hwnd, UINT width, UINT height, bool fullscreen)
	{
		lastError = E_FAIL;
		lastError = Create(hwnd, width, height, fullscreen);
	}
	D3D11::~D3D11()
	{
		Release();
	}
	void D3D11::SetCulling(Engine2D::CullingMode mode)
	{
		if (auto p = rasterizer[(int)mode])
		{
			context->RSSetState(p.get());
		}
	}
	void D3D11::Release()
	{
		safe_release(renderTargetView);
		for (int i = (int)CullingMode::MAX - 1; i > 0; --i)
			safe_release(rasterizer[i]);
		safe_release(swapChain);
		safe_release(context);
		safe_release(device);
	}
	inline std::weak_ptr<ID3D11Device> D3D11::GetDevice()
	{
		return std::weak_ptr<ID3D11Device>();// device;
	}
	inline std::weak_ptr<ID3D11DeviceContext> D3D11::GetContext()
	{
		return std::weak_ptr<ID3D11DeviceContext>();// context;
	}
	inline std::weak_ptr<IDXGISwapChain> D3D11::GetSwapChain()
	{
		return std::weak_ptr<IDXGISwapChain>();// swapChain;
	}
	inline std::weak_ptr<ID3D11RenderTargetView> D3D11::GetRenderTargetView()
	{
		return std::weak_ptr<ID3D11RenderTargetView>();// renderTargetView;
	}
}