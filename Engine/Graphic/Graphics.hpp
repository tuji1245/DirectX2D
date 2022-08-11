#pragma once

#include <memory>

#include "pch.h"

#include "DX11.hpp"
#include "singleton.hpp"
#include "Texture/Texture.hpp"
#include "BlendState.hpp"
#include "SamplerState.hpp"
#include "DepthStencilState.hpp"
#include "Color.hpp"

namespace Engine2D
{
	class Graphics final : public Singleton<Graphics>
	{
	public:
		enum class SamplerStateType
		{
			POINT,
			LINEAR,
			MAX
		};
		enum class DepthStencilType
		{
			OFF,
			ON,
			MAX
		};
		enum class BlendStateType
		{
			ALPHA,
			ADD,
			MAX
		};
	protected:
		Graphics() = default;
		~Graphics() = default;
	public:
		void Init();
		void Uninit();
		void BeginFrame();
		void EndFrame();

		void SetRenderTarget(std::shared_ptr<Texture>* renderTargetArray, uint8_t numView, Color* pClearColor = nullptr);
		void SetRenderTargetDefault(Color* pClearColor = nullptr);
		void SetDepthStencilView(std::shared_ptr<Texture> pDepthStencilView, bool isClear = false);
		void SetDepthStencilViewDefault(bool isClear = false);

		void SetBlendState(BlendStateType type);
		void SetBlendState(std::shared_ptr<BlendState> pState);
		std::weak_ptr<BlendState> GetBlendState();

		void SetSamplerState(SamplerStateType type);
		void SetSamplerState(std::shared_ptr<SamplerState> pState);
		std::weak_ptr<SamplerState> GetSamplerState();

		void SetDepthStencilState(DepthStencilType type);
		void SetDepthStencilState(std::shared_ptr<DepthStencilState> pState);
		std::weak_ptr<DepthStencilState> GetDepthStencilState();

	private:
		void UpdateTargetView();

	private:
		std::shared_ptr<Texture> defRenderTarget;
		std::shared_ptr<Texture> defDepthStencil;
		std::shared_ptr<Texture> renderTarget[4];
		uint8_t renderTargetNum;
		std::shared_ptr<Texture> depthStencilView;
		std::shared_ptr<BlendState> defBlendState[(int)BlendStateType::MAX];
		std::shared_ptr<BlendState> blendState;
		std::shared_ptr<SamplerState> defSamplerState[(int)SamplerStateType::MAX];
		std::shared_ptr<SamplerState> samplerState;
		std::shared_ptr<DepthStencilState> defDepthStencilState[(int)DepthStencilType::MAX];
		std::shared_ptr<DepthStencilState> depthStencilState;
	};

}