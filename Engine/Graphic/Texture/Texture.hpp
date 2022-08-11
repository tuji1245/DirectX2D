#pragma once

#include "Define.h"
#include <Graphic\DX11.hpp>

namespace Engine2D
{
	class Texture
	{
		friend class TextureFactory;
	public:
		Texture();
		virtual ~Texture();

		uint16_t GetWidth() const;
		uint16_t GetHeight() const;
		ComPtr<ID3D11ShaderResourceView> GetResource() const;

	protected:
		virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* data = nullptr);

	protected:
		uint16_t width;
		uint16_t height;

		ComPtr<ID3D11ShaderResourceView> ShaderResourceView;

	protected:
		ComPtr<ID3D11Texture2D> tex;
	};
}

#include "Texture.inl"