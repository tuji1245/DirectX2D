#pragma once

#include "Texture.hpp"

namespace Engine2D
{
	uint16_t Texture::GetWidth() const
	{
		return width;
	}

	uint16_t Texture::GetHeight() const
	{
		return height;
	}

	ComPtr<ID3D11ShaderResourceView> Texture::GetResource() const
	{
		return ShaderResourceView;
	}
}