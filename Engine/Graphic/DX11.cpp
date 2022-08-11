#include "pch.h"

#include "DX11.hpp"
#include <memory>

namespace Engine2D
{
	HRESULT DX11::Create(HWND hwnd, UINT width, UINT height, bool fullscreen)
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
				swapChain.ReleaseAndGetAddressOf(),			// IDXGIDwapChain�C���^�t�F�[�X	
				device.ReleaseAndGetAddressOf(),			// ID3D11Device�C���^�t�F�[�X
				&_featureLevel,		// �T�|�[�g����Ă���@�\���x��
				context.ReleaseAndGetAddressOf());		// �f�o�C�X�R���e�L�X�g
			if (SUCCEEDED(_hr)) { break; }
		}
		if (FAILED(_hr)) { return _hr; }

		//--- ���X�^���C�Y
		D3D11_RASTERIZER_DESC _rasterDesc{};
	
		_rasterDesc.FillMode = D3D11_FILL_SOLID;
		_rasterDesc.CullMode = D3D11_CULL_NONE;
		_hr = device->CreateRasterizerState(&_rasterDesc, &rasterizer[(int)CullingMode::NONE]);
		if (FAILED(_hr)) { return _hr; }
		_rasterDesc.CullMode = D3D11_CULL_FRONT;
		_hr = device->CreateRasterizerState(&_rasterDesc, &rasterizer[(int)CullingMode::FRONT]);
		if (FAILED(_hr)) { return _hr; }
		_rasterDesc.CullMode = D3D11_CULL_BACK;
		_hr = device->CreateRasterizerState(&_rasterDesc, &rasterizer[(int)CullingMode::BACK]);
		if (FAILED(_hr)) { return _hr; }

		SetCulling(CullingMode::NONE);

		return S_OK;
	}
	DX11::DX11()
		: device(nullptr)
		, context(nullptr)
		, swapChain(nullptr)
		, renderTargetView(nullptr)
		, lastError(S_OK)
	{
		for (int i = 0; i < (int)CullingMode::MAX; i++)
			rasterizer[i] = nullptr;
	}
	DX11::~DX11()
	{
	}
	void DX11::Init(HWND hwnd, UINT width, UINT height, bool fullscreen)
	{
		lastError = E_FAIL;
		lastError = Create(hwnd, width, height, fullscreen);
	}
	void DX11::SetCulling(Engine2D::CullingMode mode)
	{
		context->RSSetState(rasterizer[(int)mode].Get());
	}
	inline ComPtr<ID3D11Device> DX11::GetDevice()
	{
		return device;
	}
	inline ComPtr<ID3D11DeviceContext> DX11::GetContext()
	{
		return context;
	}
	inline ComPtr<IDXGISwapChain> DX11::GetSwapChain()
	{
		return swapChain;
	}
	inline ComPtr<ID3D11RenderTargetView> DX11::GetRenderTargetView()
	{
		return renderTargetView;
	}
}