///////////////////////////////////////
// BackGround.cpp
//-------------------------------------
// 2020/07/20	�쐬
//		08/10	Field�Ɉړ�
//
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "BackGround.h"
#include "Game.h"

//--- �萔�E�}�N����`
#define F_BACK	("Image/Back.png")

//--- �R���X�g���N�^
CBackGround::CBackGround()
{
	// �摜�ǂݍ���
	SetImage(F_BACK);

	SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_Coord = { 0, 0 };
}

//--- �f�X�g���N�^
CBackGround::~CBackGround()
{

}

//--- �X�V
void CBackGround::Update()
{
	m_Coord.x += 0.001f;
	if (m_Coord.x >= 1.0f) m_Coord.x = 0.0f;
	m_Coord.y += 0.001f;
	if (m_Coord.y >= 1.0f) m_Coord.y = 0.0f;

	SetUV(m_Coord.x, m_Coord.y);

	// �|���S���̍X�V
	CPolygon::Update();

}

//--- �`��
void CBackGround::Draw()
{
	// �|���S���̕`��
	CPolygon::Draw();

}

