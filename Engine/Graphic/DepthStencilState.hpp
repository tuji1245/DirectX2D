#pragma once

#include <d3d11.h>
#include "Define.h"

namespace Engine2D
{
	class DepthStencilState
	{
	public:
		DepthStencilState();
		~DepthStencilState();
	
		HRESULT Create(bool depthEnable, bool stencilEnable);
		void Bind();

	private:
		ComPtr<ID3D11DepthStencilState> state;
	};
}