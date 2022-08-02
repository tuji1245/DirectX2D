#include "pch.h"

#include "DX11.hpp"
#include <memory>
#include "safe_release.h"

namespace Engine2D
{
	HRESULT D3D11::Create(HWND hwnd, UINT width, UINT height, bool fullscreen)
	{
		HRESULT	_hr = E_FAIL;

		// �X���b�v�`�F�C���̐ݒ�
		// �X���b�v�`�F�C���Ƃ́A�E�C���h�E�ւ̕\���_�u���o�b�t�@���Ǘ�����
		// �}���`�T���v�����O�A���t���b�V�����[�g���ݒ�ł���
		// �����̃o�b�N�o�b�t�@���쐬�ł���
		DXGI_SWAP_CHAIN_DESC _sd{};							// �[���N���A
		_sd.BufferDesc.Width = width;						// �o�b�N�o�b�t�@�̕�
		_sd.BufferDesc.Height = height;						// �o�b�N�o�b�t�@�̍���
		_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B,A)
		_sd.SampleDesc.Count = 1;			// �}���`�T���v���̐�
		_sd.BufferDesc.RefreshRate.Numerator = 1000;
		_sd.BufferDesc.RefreshRate.Denominator = 1;
		_sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// �o�b�N�o�b�t�@�̎g�p���@
		_sd.BufferCount = 1;									// �o�b�N�o�b�t�@�̐�
		_sd.OutputWindow = hwnd;								// �֘A�t����E�C���h�E
		_sd.Windowed = fullscreen ? FALSE : TRUE;
		//_sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;


		// �h���C�o�̎��
		const D3D_DRIVER_TYPE _driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,	// GPU�ŕ`��
			D3D_DRIVER_TYPE_WARP,		// �����x(�ᑬ
			D3D_DRIVER_TYPE_REFERENCE,	// CPU�ŕ`��
		};
		const UINT _numDriverTypes = ARRAYSIZE(_driverTypes);

		UINT _createDeviceFlags = 0;
		// createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		// �@�\���x��
		const D3D_FEATURE_LEVEL _featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,		// DirectX11.1�Ή�GPU���x��
			D3D_FEATURE_LEVEL_11_0,		// DirectX11�Ή�GPU���x��
			D3D_FEATURE_LEVEL_10_1,		// DirectX10.1�Ή�GPU���x��
			D3D_FEATURE_LEVEL_10_0,		// DirectX10�Ή�GPU���x��
			D3D_FEATURE_LEVEL_9_3,		// DirectX9.3�Ή�GPU���x��
			D3D_FEATURE_LEVEL_9_2,		// DirectX9.2�Ή�GPU���x��
			D3D_FEATURE_LEVEL_9_1		// Direct9.1�Ή�GPU���x��
		};
		const UINT _numFeatureLevels = ARRAYSIZE(_featureLevels);

		D3D_DRIVER_TYPE _driverType;
		D3D_FEATURE_LEVEL _featureLevel;
		ID3D11Device* _device;
		IDXGISwapChain* _swapChain;
		ID3D11DeviceContext* _context;
		for (UINT _driverTypeIndex = 0; _driverTypeIndex < _numDriverTypes; ++_driverTypeIndex)
		{
			_driverType = _driverTypes[_driverTypeIndex];
			_hr = D3D11CreateDeviceAndSwapChain(
				NULL,					// �f�B�X�v���C�f�o�C�X�̃A�_�v�^�iNULL�̏ꍇ�ŏ��Ɍ��������A�_�v�^�j
				_driverType,			// �f�o�C�X�h���C�o�̃^�C�v
				NULL,					// �\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�Ɏw�肷��
				_createDeviceFlags,		// �f�o�C�X�t���O
				_featureLevels,			// �@�\���x��
				_numFeatureLevels,		// �@�\���x����
				D3D11_SDK_VERSION,		// 
				&_sd,					// �X���b�v�`�F�C���̐ݒ�
				&_swapChain,			// IDXGIDwapChain�C���^�t�F�[�X	
				&_device,				// ID3D11Device�C���^�t�F�[�X
				&_featureLevel,		// �T�|�[�g����Ă���@�\���x��
				&_context);		// �f�o�C�X�R���e�L�X�g
			if (SUCCEEDED(_hr)) 
			{
				swapChain.reset(_swapChain);
				device.reset(_device);
				context.reset(_context);
				break;
			}
		}
		if (FAILED(_hr))	return _hr;

		//--- ���X�^���C�Y
		D3D11_RASTERIZER_DESC _rasterDesc{};
		ID3D11RasterizerState* _rasterizer[(int)CullingMode::MAX]{};
	
		_rasterDesc.FillMode = D3D11_FILL_SOLID;
		_rasterDesc.CullMode = D3D11_CULL_NONE;
		_hr = device->CreateRasterizerState(&_rasterDesc, &_rasterizer[(int)CullingMode::NONE]);
		if (FAILED(_hr)) { return _hr; }
		_rasterDesc.CullMode = D3D11_CULL_FRONT;
		_hr = device->CreateRasterizerState(&_rasterDesc, &_rasterizer[(int)CullingMode::FRONT]);
		if (FAILED(_hr)) { return _hr; }
		_rasterDesc.CullMode = D3D11_CULL_BACK;
		_hr = device->CreateRasterizerState(&_rasterDesc, &_rasterizer[(int)CullingMode::BACK]);
		if (FAILED(_hr)) { return _hr; }
		for (int i = 0; i < (int)CullingMode::MAX; ++i)
		{
			rasterizer[i].reset(_rasterizer[i]);
		}
		SetCulling(CullingMode::NONE);

		return S_OK;
	}
	D3D11::D3D11(HWND hwnd, UINT width, UINT height, bool fullscreen)
	{
		lastError = E_FAIL;
		lastError = Create(hwnd, width, height, fullscreen);
	}
	D3D11::~D3D11()
	{
		Release();
	}
	void D3D11::SetCulling(Engine2D::CullingMode mode)
	{
		if (auto p = rasterizer[(int)mode])
		{
			context->RSSetState(p.get());
		}
	}
	void D3D11::Release()
	{
		safe_release(renderTargetView);
		for (int i = (int)CullingMode::MAX - 1; i > 0; --i)
			safe_release(rasterizer[i]);
		safe_release(swapChain);
		safe_release(context);
		safe_release(device);
	}
	inline std::weak_ptr<ID3D11Device> D3D11::GetDevice()
	{
		return std::weak_ptr<ID3D11Device>();// device;
	}
	inline std::weak_ptr<ID3D11DeviceContext> D3D11::GetContext()
	{
		return std::weak_ptr<ID3D11DeviceContext>();// context;
	}
	inline std::weak_ptr<IDXGISwapChain> D3D11::GetSwapChain()
	{
		return std::weak_ptr<IDXGISwapChain>();// swapChain;
	}
	inline std::weak_ptr<ID3D11RenderTargetView> D3D11::GetRenderTargetView()
	{
		return std::weak_ptr<ID3D11RenderTargetView>();// renderTargetView;
	}
}