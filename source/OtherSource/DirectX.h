// �C���N���[�h�K�[�h
#ifndef __DIRECTX_H__
#define __DIRECTX_H__

#include <d3d11.h>	// DirectX11�̋@�\���g���I�I

// ���C�u�����̓ǂݍ���
// .cpp�̊֐�����ɂ܂Ƃ܂����t�@�C��
#pragma comment(lib,"d3d11.lib")

// �}�N��
#define SAFE_RELEASE(p)	if(p) { p->Release(); p = NULL; }

//--- �v���g�^�C�v�錾
HRESULT InitDirectX(
	HWND hWnd, UINT width, UINT height, bool fullScreen);
void UninitDirectX();
void BeginDrawDirectX();
void EndDrawDirectX();

ID3D11Device *GetDevice();
ID3D11DeviceContext *GetContext();

// ���u�����h�A���Z�����؂�ւ�
void SetAddBlend(bool isUse);

#endif	// __DIRECTX_H__
