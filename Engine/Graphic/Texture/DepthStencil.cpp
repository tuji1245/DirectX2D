#include "pch.h"
#include "DepthStencil.hpp"
namespace Engine2D
{
	DepthStencil::DepthStencil()
	{
	}

	DepthStencil::~DepthStencil()
	{
	}
	HRESULT DepthStencil::CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData)
	{
		bool _useStencil = (desc.Format == DXGI_FORMAT_D24_UNORM_S8_UINT);

		desc.Format = _useStencil ? DXGI_FORMAT_R24_UNORM_X8_TYPELESS : DXGI_FORMAT_R32_TYPELESS;
		HRESULT _hr = Texture::CreateResource(desc, nullptr);

		D3D11_DEPTH_STENCIL_VIEW_DESC _dsvDesc{};
		_dsvDesc.Format = _useStencil ? DXGI_FORMAT_D24_UNORM_S8_UINT : DXGI_FORMAT_D32_FLOAT;
		_dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		return DX11::GetInstance()->GetDevice()->CreateDepthStencilView(
			tex.Get(),
			&_dsvDesc,
			DepthStencilView.ReleaseAndGetAddressOf());
	}
}