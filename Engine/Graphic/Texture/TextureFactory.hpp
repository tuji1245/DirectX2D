#pragma once

#include "Graphic\Texture\Texture.hpp"

namespace Engine2D
{
	class TextureFactory
	{
	public:
		static std::shared_ptr<Texture> CreateFromData(DXGI_FORMAT format, uint16_t width, uint16_t hegiht, const void* pData);
		static std::shared_ptr<Texture> CreateRenderTarget(DXGI_FORMAT format, uint16_t width, uint16_t hegiht);
		static std::shared_ptr<Texture> CreateRenderTargetFromScreen();
		static std::shared_ptr<Texture> CreateDepthStencil(uint16_t width, uint16_t hegiht, bool useStencil = false);

	private:
		static D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT format, uint16_t width, uint16_t hegiht);
	};
}