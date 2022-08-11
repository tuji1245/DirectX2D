#include "pch.h"

#include "Texture.hpp"

namespace Engine2D
{
	Texture::Texture()
		: width(0), height(0)
		, tex(nullptr)
		, ShaderResourceView(nullptr)
	{
	}

	Texture::~Texture()
	{
	}

	HRESULT Texture::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* data)
	{
		D3D11_SUBRESOURCE_DATA _data{};
		_data.pSysMem = data;
		_data.SysMemPitch = desc.Width * 4;
		auto _device = DX11::GetInstance()->GetDevice();
		_device->CreateTexture2D(&desc, data ? &_data : nullptr, tex.ReleaseAndGetAddressOf());

		D3D11_SHADER_RESOURCE_VIEW_DESC _srvDesc{};
		_srvDesc.Format = desc.Format;
		_srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		_srvDesc.Texture2D.MipLevels = 1;
		
		return _device->CreateShaderResourceView(
			tex.Get(),
			&_srvDesc,
			ShaderResourceView.ReleaseAndGetAddressOf());
	}
}