#include "pch.h"

#include "BlendState.hpp"
#include "Graphics.hpp"

namespace Engine2D
{
	BlendState::BlendState()
		: state(nullptr)
	{
	}
	BlendState::~BlendState()
	{
	}
	HRESULT BlendState::Create(D3D11_RENDER_TARGET_BLEND_DESC desc)
	{
		D3D11_BLEND_DESC _blendDesc{};
		_blendDesc.RenderTarget[0] = desc;

		return DX11::GetInstance()->GetDevice()->CreateBlendState(&_blendDesc, state.ReleaseAndGetAddressOf());
	}
	void BlendState::Bind()
	{
		float _blendFactor[4]{ 0,0,0,0 };
		DX11::GetInstance()->GetContext()->OMSetBlendState(state.Get(), _blendFactor, 0xffffffff);
		Graphics::GetInstance()->SetBlendState(std::shared_ptr<BlendState>(this));
	}
}