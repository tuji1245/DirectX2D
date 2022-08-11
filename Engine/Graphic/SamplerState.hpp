#pragma once

#include <d3d11.h>
#include "Define.h"

namespace Engine2D
{
	class SamplerState
	{
	public:
		SamplerState();
		~SamplerState();

		HRESULT Create(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address);
		void Bind();

	private:
		ComPtr<ID3D11SamplerState> state;
	};
}