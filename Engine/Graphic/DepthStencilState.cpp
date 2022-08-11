#include "pch.h"

#include "DepthStencilState.hpp"
#include "DX11.hpp"
#include "Graphics.hpp"

namespace Engine2D
{
	DepthStencilState::DepthStencilState()
		: state(nullptr)
	{
	}
	DepthStencilState::~DepthStencilState()
	{
	}
	HRESULT DepthStencilState::Create(bool depthEnable, bool stencilEnable)
	{
		D3D11_DEPTH_STENCIL_DESC desc;

		desc.DepthEnable = stencilEnable;
		desc.DepthFunc = D3D11_COMPARISON_LESS;
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

		desc.StencilEnable = stencilEnable;
		desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
		desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
		desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		desc.FrontFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;
		desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_INCR;
		desc.BackFace.StencilFunc = D3D11_COMPARISON_GREATER_EQUAL;

		return DX11::GetInstance()->GetDevice()->CreateDepthStencilState(&desc, state.ReleaseAndGetAddressOf());
	}
	void DepthStencilState::Bind()
	{
		DX11::GetInstance()->GetContext()->OMSetDepthStencilState(state.Get(), 0);
		Graphics::GetInstance()->SetDepthStencilState(std::shared_ptr<DepthStencilState>(this));
	}
}