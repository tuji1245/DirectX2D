#include "pch.h"

#include "TextureFactory.hpp"
#include "RenderTarget.hpp"
#include "DepthStencil.hpp"


namespace Engine2D
{
	D3D11_TEXTURE2D_DESC TextureFactory::MakeTexDesc(DXGI_FORMAT format, uint16_t width, uint16_t hegiht)
	{
		D3D11_TEXTURE2D_DESC _desc{};
		_desc.Usage = D3D11_USAGE_DEFAULT;
		_desc.Format = format;
		_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		_desc.Width = width;
		_desc.Height = hegiht;
		_desc.MipLevels = 1;
		_desc.ArraySize = 1;
		_desc.SampleDesc.Count = 1;
		return _desc;
	}

	std::shared_ptr<Texture> TextureFactory::CreateFromData(DXGI_FORMAT format, uint16_t width, uint16_t hegiht, const void* pData)
	{
		D3D11_TEXTURE2D_DESC _desc = MakeTexDesc(format, width, hegiht);

		std::shared_ptr<Texture> _texture{ new Texture };
		if (SUCCEEDED(_texture->CreateResource(_desc)))
		{
			_texture->width = width;
			_texture->height = hegiht;
			return _texture;
		}

		return nullptr;
	}
	std::shared_ptr<Texture> TextureFactory::CreateRenderTarget(DXGI_FORMAT format, uint16_t width, uint16_t hegiht)
	{
		D3D11_TEXTURE2D_DESC _desc = MakeTexDesc(format, width, hegiht);
		_desc.BindFlags |= D3D11_BIND_RENDER_TARGET;

		std::shared_ptr<RenderTarget> _renderTexture{ new RenderTarget };
		if (SUCCEEDED(_renderTexture->CreateResource(_desc)))
		{
			_renderTexture->width = width;
			_renderTexture->height = hegiht;
			return _renderTexture;
		}
		return nullptr;
	}
	std::shared_ptr<Texture> TextureFactory::CreateRenderTargetFromScreen()
	{
		std::shared_ptr<RenderTarget> _renderTexture{ std::make_shared<RenderTarget>() };

		ComPtr<ID3D11Texture2D> _backBuffer{ NULL };
		auto _dxInstance = DX11::GetInstance();
		HRESULT _hr = _dxInstance->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D),(LPVOID*)(_renderTexture->tex.GetAddressOf()));

		if (SUCCEEDED(_hr))
		{
			_hr = _dxInstance->GetDevice()->CreateRenderTargetView(
				_renderTexture->tex.Get(),
				NULL,
				_renderTexture->RenderTargetView.ReleaseAndGetAddressOf());
			if (SUCCEEDED(_hr))
			{
				D3D11_TEXTURE2D_DESC _desc{};
				_renderTexture->tex->GetDesc(&_desc);
				_renderTexture->width = _desc.Width;
				_renderTexture->height = _desc.Height;
			}
		}
		if (FAILED(_hr))
		{
			return nullptr;
		}
		return _renderTexture;
	}
	std::shared_ptr<Texture> TextureFactory::CreateDepthStencil(uint16_t width, uint16_t height, bool useStencil)
	{
		D3D11_TEXTURE2D_DESC _desc = MakeTexDesc(useStencil ? DXGI_FORMAT_R24G8_TYPELESS : DXGI_FORMAT_R32_TYPELESS, width, height);
		_desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;

		std::shared_ptr<DepthStencil> _depthStencil{ std::make_shared<DepthStencil>() };
		if (SUCCEEDED(_depthStencil->CreateResource(_desc)))
		{
			_depthStencil->width = width;
			_depthStencil->height = height;
			return _depthStencil;
		}

		return nullptr;
	}
}