#pragma once

#include "DX11.hpp"

namespace Engine2D
{
	class Texture
	{
	public:
		Texture();
		virtual ~Texture();
		virtual void Release();

		uint16_t GetWidth() const;
		uint16_t GetHegiht() const;
		std::weak_ptr<ID3D11ShaderResourceView> GetResource() const;

	protected:
		virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* data = nullptr);

	private:
		uint16_t width;
		uint16_t height;

		std::shared_ptr<ID3D11ShaderResourceView> ShaderResourceView;

	protected:
		std::shared_ptr<ID3D11Texture2D> Tex;
	};
}