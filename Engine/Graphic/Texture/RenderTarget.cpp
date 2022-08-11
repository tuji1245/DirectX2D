#include "pch.h"
#include "RenderTarget.hpp"

namespace Engine2D
{
	RenderTarget::RenderTarget()
		: RenderTargetView(nullptr)
	{
	}
	RenderTarget::~RenderTarget()
	{
	}

	HRESULT RenderTarget::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
	{
		HRESULT hr = Texture::CreateResource(desc, nullptr);
		if (FAILED(hr)) { return hr; }

		D3D11_RENDER_TARGET_VIEW_DESC _rtvDesc{};
		_rtvDesc.Format = desc.Format;
		_rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		return DX11::GetInstance()->GetDevice()->CreateRenderTargetView(
			tex.Get(),
			&_rtvDesc,
			RenderTargetView.ReleaseAndGetAddressOf());
	}
}