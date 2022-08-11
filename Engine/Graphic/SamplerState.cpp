#include "pch.h"

#include "SamplerState.hpp"
#include "DX11.hpp"
#include "Graphics.hpp"

namespace Engine2D
{
	SamplerState::SamplerState()
		: state(nullptr)
	{
	}
	SamplerState::~SamplerState()
	{
	}
	HRESULT SamplerState::Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address)
	{
		D3D11_SAMPLER_DESC desc{};
		desc.Filter = filter;
		desc.AddressU = address;
		desc.AddressV = address;
		desc.AddressW = address;
		return DX11::GetInstance()->GetDevice()->CreateSamplerState(&desc, state.ReleaseAndGetAddressOf());
	}
	void SamplerState::Bind()
	{
		DX11::GetInstance()->GetContext()->PSSetSamplers(0, 1, state.GetAddressOf());
		Graphics::GetInstance()->SetSamplerState(std::shared_ptr<SamplerState>(this));
	}
}