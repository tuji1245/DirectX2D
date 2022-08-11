#pragma once

#include "Texture.hpp"

namespace Engine2D
{
	class DepthStencil final : public Texture
	{
		friend class TextureFactory;
	public:
		DepthStencil();
		~DepthStencil();

		ComPtr<ID3D11DepthStencilView> GetView() const;

	protected:
		virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr) override;

	private:
		ComPtr<ID3D11DepthStencilView> DepthStencilView;
	};
}

#include "DepthStencil.inl"