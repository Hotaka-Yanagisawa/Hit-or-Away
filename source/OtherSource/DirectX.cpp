#include"DirectX.h"

//---- �O���[�o���ϐ�
// GPU�ɓn�����߂̃f�[�^�̍쐬���Ǘ�
ID3D11Device *g_pDevice;
// ��������̃f�[�^��GPU�ŕ`�悷�邽�߂̋��n��
ID3D11DeviceContext *g_pContext;
// �����̃o�b�N�o�b�t�@���Ǘ�
IDXGISwapChain *g_pSwapChain;
// GPU�ɓn���`�����ݐ�
ID3D11RenderTargetView *g_pRenderTarget;
// �摜�̍������@�̐݌v�f�[�^
ID3D11BlendState* g_pBlendState[2];

/**
* @�T�v�@DirectX������
* @���� width �E�B���h�E����
* @���� height �E�B���h�E�c��
* @�����@fullScreen �t���X�N���[��
* @�߂�l �������̐���
**/
HRESULT InitDirectX(
	HWND hWnd, UINT width, UINT height, bool fullScreen)
{
	HRESULT hr;// �֐��̎��s����

	//---- �X���b�v�`�F�[���̍쐬
	// Window�̉�ʂɒ��ڕ`����s���̂ł͂Ȃ��A
	// BackBuffer�ƌĂ΂��ڂɌ����Ȃ��̈�ɏ������݂��s���A
	// ���̃^�C�~���O��Window�̉�ʂɕ\�����s��

	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC scDesc;
	ZeroMemory(&scDesc, sizeof(scDesc));	// 0�ŏ�����
	// �o�b�N�o�b�t�@�̑傫��(����)���w��
	scDesc.BufferDesc.Width = width;
	// �o�b�N�o�b�t�@�̑傫��(�c��)���w��
	scDesc.BufferDesc.Height = height;
	// �o�b�N�o�b�t�@�ň�����F�͈̔͂��w��
	// ��8�r�b�g,��8�r�b�g,��8�r�b�g,����8�r�b�g
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// �K��1���w�肷��
	scDesc.SampleDesc.Count = 1;
	// ��ʂ̍X�V�p�x(���t���b�V�����[�g)
	scDesc.BufferDesc.RefreshRate.Numerator = 1000;//����
	scDesc.BufferDesc.RefreshRate.Denominator = 1;//���q
	// �o�b�N�o�b�t�@�̎g�p���@���w��
	// �ŏI�I�ɉ�ʂ֏o�͂���F�̏������ݐ�Ƃ��Ďg�p
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// �쐬����o�b�t�@�̐�
	scDesc.BufferCount = 1;
	// �o�b�N�o�b�t�@�̕\���̃E�B���h�E���w��
	scDesc.OutputWindow = hWnd;
	// �t���X�N���[���\���̎w��
	if (fullScreen)
	{
		scDesc.Windowed = FALSE;
	}
	else
	{
		scDesc.Windowed = TRUE;
	}

	// �X���b�v�`�F�[���̍쐬(DirectX�̏�����)
	//---- �쐬�ɕK�v�ȃp�����[�^��p��
	// �h���C�o�̎��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,  // GPu�ŕ`��(��{)
		D3D_DRIVER_TYPE_WARP,      // WARP�h���C�o�[
		D3D_DRIVER_TYPE_REFERENCE, // ��荂���x(�ᑬ)
	};
	// �h���C�o�̔z��
	UINT numDriver =
		sizeof(driverTypes) / sizeof(driverTypes[0]);
	// �@�\���x��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		// ���ꂼ�ꂪ�ǂ̃��x����DirectX��
		// �Ή�����̂�������
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	// �@�\���x���̔z��
	UINT numFeatureLevel =
		sizeof(featureLevels) / sizeof(featureLevels[0]);

	//---- �X���b�v�`�F�[���̍쐬(DirectX�̏�����)
	D3D_FEATURE_LEVEL useLevel;// ���ۂɎg�p�����@�\���x��
	// �h���C�o�[������m�F
	for (UINT i = 0; i < numDriver; ++i)
	{
		hr = D3D11CreateDeviceAndSwapChain
		(
			NULL,              // ���ɐݒ�Ȃ�
			driverTypes[i],    // ���p����h���C�o
			NULL, 0,           // ���ɐݒ�Ȃ�
			featureLevels,	   // ���p����@�\���x���̈ꗗ
			numFeatureLevel,   // �@�\���x���̐�
			D3D11_SDK_VERSION, // ���ɂǂ̃o�[�W������DirectX���g�p���邩
			&scDesc,           // �X���b�v�`�F�[���̐ݒ�
			&g_pSwapChain,     // �쐬�����X���b�v�`�F�[���̊i�[��
			&g_pDevice,        // �쐬����Device�̊i�[��
			&useLevel,         // ���ۂɗ��p�����@�\���x��
			&g_pContext        // �쐬����Context�̊i�[��
		);
		// �쐬������������I��
		if (SUCCEEDED(hr))
		{
			break;
		}

	}
	// �쐬������������Ȃ�����
	if (FAILED(hr))
	{
		return E_FAIL;	// ���s��\���p�����[�^�[��߂�
	}

	//--- �����_�[�^�[�Q�b�g�̍쐬
	// �o�b�N�o�b�t�@�̃|�C���^���擾
	ID3D11Texture2D *pBackBuffer = NULL;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		(LPVOID*)&pBackBuffer);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// �o�b�N�o�b�t�@�̃|�C���^�����Ƀ����_�[�^�[�Q�b�g�쐬
	hr = g_pDevice->CreateRenderTargetView(
		pBackBuffer, NULL, &g_pRenderTarget);
	pBackBuffer->Release();
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// �g�p���郌���_�[�^�[�Q�b�g��ݒ�
	g_pContext->OMSetRenderTargets(1, &g_pRenderTarget, NULL);

	//--- �A���t�@�u�����h(�摜�̍������@)�̐ݒ�
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	// �F(�ŏI�I�ɕ\�������F�̌v�Z���@���w��)
	// �\�������F * �\������鑤�̓����x
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	// ���̐F * (1 - �\������鑤�̓����x)
	blendDesc.RenderTarget[0].DestBlend =
		D3D11_BLEND_INV_SRC_ALPHA;
		//D3D11_BLEND_ONE;
	// �\�������F �� ���̐F �̍������@(�����Z)
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// �A���t�@
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	// �Ώ�
	blendDesc.RenderTarget[0].RenderTargetWriteMask =
		D3D11_COLOR_WRITE_ENABLE_ALL;

	// �A���t�@�u�����h�̃f�[�^�𐶐�
	hr = g_pDevice->CreateBlendState(&blendDesc, &g_pBlendState[0]);
	if (FAILED(hr))
	{
		return hr;
	}
	// ���Z�����̃f�[�^���쐬
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	// ���Z�����p�̃p�����[�^�ɂȂ��Ă���blendDesc�ŐV�����쐬
	hr = g_pDevice->CreateBlendState(&blendDesc, &g_pBlendState[1]);
	if (FAILED(hr))
	{
		return hr;
	}
	// �������@�̐ݒ�
	SetAddBlend(false);
	
	//--- �e�N�X�`���̌J��Ԃ��ݒ�
	// �T���v���[�X�e�[�g
	D3D11_SAMPLER_DESC smpDesc;
	ID3D11SamplerState* pSampler;
	ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	// �e�N�X�`���̌J��Ԃ����@
	// CLAMP ...�[�̐F�����������Ă��ė��p(�f�t�H���g�̎w��)
	// WRAP  ...�J��Ԃ��ĕ\��
	// MIRROR...���ʂ��ŕ\��
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	// �g��k�����̐F�̎擾���@
	// POINT ...���ɕ�Ԃ��Ȃ�
	// LINEAR...���`���(�f�t�H���g�̎w��)
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	// �T���v���[�X�e�[�g�̍쐬
	hr = g_pDevice->CreateSamplerState(&smpDesc, &pSampler);

	if (FAILED(hr))
	{
		return hr;
	}
	// �`��ɃT���v���[�X�e�[�g��ݒ�
	g_pContext->PSSetSamplers(0, 1, &pSampler);
	SAFE_RELEASE(pSampler);

	// �r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)width;
	vp.Height = (float)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pContext->RSSetViewports(1, &vp);


	// ����������
	return S_OK;	// ������\���p�����[�^

}
/**
* @�T�v�@DirectX�I������
**/

void UninitDirectX()
{
	// GPU�ɓn�����ݒ�����ׂĉ��
	g_pContext->ClearState();
	// �t���X�N���[����Ԃ̉���
	g_pSwapChain->SetFullscreenState(FALSE, NULL);

	// �������
	g_pContext->Release();
	g_pDevice->Release();
	g_pSwapChain->Release();

}

/**
* @�T�v�@�`��̑O����
**/
void BeginDrawDirectX()
{
	// �����_�[�^�[�Q�b�g�̃N���A
	// ������ԁA�΁A�A����
	// WindowsAPI�ł͈�̐F��0�`255�ŕ\�������A
	// DirectX�ł�0.0f�`1.0f�ŕ\�����Ƃ�����
	float color[4] = { 0.8f,0.7f,0.7f,1.0f };
	g_pContext->ClearRenderTargetView(g_pRenderTarget, color);
}

/**
* @�T�v �`��̌㏈��
**/
void EndDrawDirectX()
{
	// �����_�[�^�[�Q�b�g�̓��e��`���̃E�B���h�E�ɕ\��
	g_pSwapChain->Present(1, 0);
}

/**
* @�T�v DirectX�̎擾
**/
ID3D11Device *GetDevice()
{
	return g_pDevice;
}

/**
* @�T�v DeviceContxte�̎擾
**/
ID3D11DeviceContext *GetContext()
{
	return g_pContext;
}

void SetAddBlend(bool isUse)
{
	// �ǂ���̍������@���g�p���邩
	int idx = 0;	// ���u�����h
	if (isUse)
	{
		idx = 1;	// ���Z����
	}

	// �A���t�@�u�����h��`��ɐݒ�
	float blendFactor[4] = { 0,0,0,0 };
	g_pContext->OMSetBlendState(g_pBlendState[idx], blendFactor, 0xffffffff);

}
