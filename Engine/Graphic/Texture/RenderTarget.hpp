#pragma once

#include "Texture.hpp"

namespace Engine2D
{
	class RenderTarget final : public Texture
	{
		friend class TextureFactory;
	public:
		RenderTarget();
		~RenderTarget();

		ComPtr<ID3D11RenderTargetView> GetView() const;

	protected:
		virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr) override;

	private:
		ComPtr<ID3D11RenderTargetView> RenderTargetView;
	};
}

#include "RenderTargetView.inl"