#pragma once

#include "RenderTarget.hpp"

namespace Engine2D
{
	ComPtr<ID3D11RenderTargetView> RenderTarget::GetView() const
	{
		return RenderTargetView;
	}
}