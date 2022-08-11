#pragma once

#include "DepthStencil.hpp"

namespace Engine2D
{
	ComPtr<ID3D11DepthStencilView> DepthStencil::GetView() const
	{
		return DepthStencilView;
	}
}