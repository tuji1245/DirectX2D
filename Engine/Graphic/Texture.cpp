#include "pch.h"
#include "framework.h"

#include "Texture.hpp"
#include "safe_release.h"

namespace Engine2D
{
	Texture::Texture()
		: width(0), height(0)
		, Tex(nullptr)
		, ShaderResourceView(nullptr)
	{
	}

	Texture::~Texture()
	{
		Release();
	}

	void Texture::Release()
	{
		safe_release(ShaderResourceView);
		safe_release(Tex);
	}

	uint16_t Texture::GetWidth() const
	{
		return width;
	}

	uint16_t Texture::GetHegiht() const
	{
		return height;
	}

	std::weak_ptr<ID3D11ShaderResourceView> Texture::GetResource() const
	{
		return ShaderResourceView;
	}

	HRESULT Texture::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* data)
	{
		D3D11_SUBRESOURCE_DATA _data{};
		_data.pSysMem = data;
		_data.SysMemPitch = desc.Width * 4;

		return E_NOTIMPL;
	}
}