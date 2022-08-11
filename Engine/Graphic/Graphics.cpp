#include "pch.h"

#include "Graphics.hpp"
#include "Texture\TextureFactory.hpp"
#include "Color.hpp"
#include "Texture\RenderTarget.hpp"
#include "Texture\DepthStencil.hpp"

namespace Engine2D
{
	void Graphics::Init()
	{
		defRenderTarget = TextureFactory::CreateRenderTargetFromScreen();
		uint8_t _width = defRenderTarget->GetWidth();
		uint8_t _height = defRenderTarget->GetHeight();
		defDepthStencil = TextureFactory::CreateDepthStencil(_width, _height, false);
		{
			D3D11_RENDER_TARGET_BLEND_DESC _desc{};
			_desc.BlendEnable = TRUE;
			_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			_desc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			_desc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			_desc.BlendOp = D3D11_BLEND_OP_ADD;
			_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
			_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
			_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;

			defBlendState[(int)BlendStateType::ALPHA] = std::make_shared<BlendState>();
			defBlendState[(int)BlendStateType::ALPHA]->Create(_desc);

			_desc.DestBlend = D3D11_BLEND_ONE;
			defBlendState[(int)BlendStateType::ADD] = std::make_shared<BlendState>();
			defBlendState[(int)BlendStateType::ADD]->Create(_desc);
		}

		defSamplerState[(int)SamplerStateType::POINT] = std::make_shared<SamplerState>();
		defSamplerState[(int)SamplerStateType::POINT]->Create(D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
		defSamplerState[(int)SamplerStateType::LINEAR] = std::make_shared<SamplerState>();
		defSamplerState[(int)SamplerStateType::LINEAR]->Create(D3D11_FILTER_MIN_MAG_MIP_LINEAR, D3D11_TEXTURE_ADDRESS_WRAP);

		defDepthStencilState[(int)DepthStencilType::OFF] = std::make_shared<DepthStencilState>();
		defDepthStencilState[(int)DepthStencilType::OFF]->Create(false, false);
		defDepthStencilState[(int)DepthStencilType::ON] = std::make_shared<DepthStencilState>();
		defDepthStencilState[(int)DepthStencilType::ON]->Create(true, false);

		depthStencilView = defDepthStencil;
		SetRenderTargetDefault();
		SetDepthStencilViewDefault();
		SetBlendState(BlendStateType::ALPHA);
		SetSamplerState(SamplerStateType::LINEAR);
		SetDepthStencilState(DepthStencilType::ON);
	}
	void Graphics::Uninit()
	{
	}
	void Graphics::BeginFrame()
	{
		Color _color{ 0.8f,0.8f,0.9f,1.0f };
		ComPtr<ID3D11RenderTargetView> _rtv = std::reinterpret_pointer_cast<RenderTarget>(defRenderTarget)->GetView();
		ComPtr<ID3D11DepthStencilView> _dsv = std::reinterpret_pointer_cast<DepthStencil>(defDepthStencil)->GetView();
		auto _context = DX11::GetInstance()->GetContext();
		_context->ClearRenderTargetView(_rtv.Get(), _color.array);
		_context->ClearDepthStencilView(_dsv.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	void Graphics::EndFrame()
	{
		DX11::GetInstance()->GetSwapChain()->Present(0, 0);
	}
	void Graphics::SetRenderTarget(std::shared_ptr<Texture>* renderTargetArray, uint8_t numView, Color* pClearColor)
	{
		if (!renderTargetArray || !renderTargetArray[0])
		{
			return;
		}

		renderTargetNum = UtilityFunc::Min(numView, 4);
		for (uint8_t i = 0; i < renderTargetNum; i++)
		{
			renderTarget[i] = renderTargetArray[i];
		}
		UpdateTargetView();

		D3D11_VIEWPORT _vp{};
		_vp.TopLeftX = 0;
		_vp.TopLeftY = 0;
		_vp.Width = static_cast<FLOAT>(renderTarget[0]->GetWidth());
		_vp.Height = static_cast<FLOAT>(renderTarget[0]->GetHeight());
		_vp.MinDepth = 0.0f;
		_vp.MaxDepth = 1.0f;
		auto _context = DX11::GetInstance()->GetContext();
		_context->RSSetViewports(1, &_vp);

		if (pClearColor)
		{
			for (uint8_t i = 0; i < renderTargetNum; i++)
			{
				ComPtr<ID3D11RenderTargetView> _rtv = std::reinterpret_pointer_cast<RenderTarget>(renderTarget[i])->GetView();
				_context->ClearRenderTargetView(_rtv.Get(), pClearColor->array);
			}
		}
	}
	void Graphics::SetRenderTargetDefault(Color* pClearColor)
	{
		SetRenderTarget(&defRenderTarget, 1, pClearColor);
	}
	void Graphics::SetDepthStencilView(std::shared_ptr<Texture> pDepthStencilView, bool isClear)
	{
		if (!pDepthStencilView || depthStencilView == pDepthStencilView)
		{
			return;
		}

		depthStencilView = pDepthStencilView;
		UpdateTargetView();

		if (isClear)
		{
			auto _dsv = std::reinterpret_pointer_cast<DepthStencil>(depthStencilView);
			DX11::GetInstance()->GetContext()->ClearDepthStencilView(
				_dsv->GetView().Get(),
				D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL
				, 1.0f, 0.0f);
		}
	}
	void Graphics::SetDepthStencilViewDefault(bool isClear)
	{
		SetDepthStencilView(defDepthStencil, isClear);
	}
	void Graphics::SetBlendState(BlendStateType type)
	{
		defBlendState[(int)type]->Bind();
	}
	void Graphics::SetBlendState(std::shared_ptr<BlendState> pState)
	{
		blendState = pState;
	}
	std::weak_ptr<BlendState> Graphics::GetBlendState()
	{
		return blendState;
	}
	void Graphics::SetSamplerState(SamplerStateType type)
	{
		defSamplerState[(int)type]->Bind();
	}
	void Graphics::SetSamplerState(std::shared_ptr<SamplerState> pState)
	{
		samplerState = pState;
	}
	std::weak_ptr<SamplerState> Graphics::GetSamplerState()
	{
		return samplerState;
	}
	void Graphics::SetDepthStencilState(DepthStencilType type)
	{
		defDepthStencilState[(int)type]->Bind();
	}
	void Graphics::SetDepthStencilState(std::shared_ptr<DepthStencilState> pState)
	{
		depthStencilState = pState;
	}
	std::weak_ptr<DepthStencilState> Graphics::GetDepthStencilState()
	{
		return depthStencilState;
	}
	void Graphics::UpdateTargetView()
	{
		ID3D11RenderTargetView* _rtv[4]{};
		for (uint8_t i = 0; i < renderTargetNum; i++)
		{
			_rtv[i] = std::reinterpret_pointer_cast<RenderTarget>(renderTarget[i])->GetView().Get();
		}

		std::shared_ptr<DepthStencil> _dsv = std::reinterpret_pointer_cast<DepthStencil>(depthStencilView);
		DX11::GetInstance()->GetContext()->OMSetRenderTargets(renderTargetNum, _rtv, _dsv->GetView().Get());
	}
}
