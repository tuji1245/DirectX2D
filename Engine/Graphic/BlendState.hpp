#pragma once

#include <d3d11.h>
#include "Define.h"

namespace Engine2D
{
	class BlendState
	{
	public:
		BlendState();
		~BlendState();

		HRESULT Create(D3D11_RENDER_TARGET_BLEND_DESC desc);
		void Bind();

	private:
		ComPtr<ID3D11BlendState> state;
	};
}
