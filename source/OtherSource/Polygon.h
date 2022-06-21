//////////////////////////////////////////////
// Polygon.h
//--------------------------------------------
// 2020/07/17	�쐬
//		07/18	�A�j�������֐��ǉ�
//		07/20	SetVtx�֐�����
//		07/26	GetPos, Size�֐��ǉ�
//		08/03	Set�֐��̑��Ύw��ǉ�
//
//////////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Texture.h"

//--- �\����
template <typename Type = float>
struct VECTOR2	// ���W
{
	Type x;
	Type y;
};
struct COLOR	// �F���
{
	float r;
	float g;
	float b;
	float a;
};

//--- �N���X
class CPolygon
{
public:

	CPolygon();		// �R���X�g���N�^
	 ~CPolygon();	// �f�X�g���N�^

	virtual void Update();	// �X�V
	virtual void Draw();	// �`��

	//--- �|���S��
	virtual void SetPos(float PosX, float PosY, bool Relative = false);			// ���W�ݒ�
	void SetSize(float SizeX, float SizeY, bool Relative = false);				// �傫���ݒ�
	void SetColor(float r, float g, float b, float a, bool Relative = false);	// �F�ݒ�
	void SetAngle(float Angle, bool Relative = false);							// �p�x�ݒ�(�x��)
	void SetImage(const char* FileName);										// �摜�ǂݍ���
	void SetTexture(ID3D11ShaderResourceView* pTexture);						// �e�N�X�`���ݒ�
	void SetSplit(float w, float h);											// �������ݒ�
	void SetUV(float u, float v);												// UV���W�ݒ�
	void SetName(const char* Name);												// ���O�ݒ�
	void Show(bool show = true) { m_bShow = show; };							// �\���ݒ�

	VECTOR2<> GetPos();		// ���W�擾
	VECTOR2<> GetSize();	// �傫���擾
	char*	GetName();		// ���O�擾

protected:

	CTexture	m_Texture;	// �e�N�X�`��
	VECTOR2<>	m_Position;	// �ʒu
	VECTOR2<>	m_Size;		// �傫��
	VECTOR2<>	m_Split;	// ������
	VECTOR2<>	m_TexCoord;	// UV���W
	COLOR	m_Color;		// �F
	float	m_fRadian;		// �p�x
	char	m_szName[10];	// ���O
	bool	m_bShow;		// �\������

};

//--- �v���g�^�C�v�錾
HRESULT InitPolygon(UINT width, UINT height);	// ������
void UninitPolygon();							// �I��

