//////////////////////////////////////////////
// Texture.h
//--------------------------------------------
// 2020/07/17	�쐬
//		09/03	�N���X��
//
//////////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "DirectX.h"

//--- �N���X
class CTexture
{
public:

	ID3D11ShaderResourceView* m_pTexture;

public:

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	HRESULT LoadTexture(const char *pszFileName);	// �摜�ǂݍ���
	void UnLoadTexture();							// �e�N�X�`�����

};