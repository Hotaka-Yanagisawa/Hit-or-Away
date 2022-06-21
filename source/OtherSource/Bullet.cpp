///////////////////////////////////////
// Bullet.cpp
//-------------------------------------
// 2020/09/03	�쐬
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "Bullet.h"
#include "Game.h"
#include "Field.h"

//--- �萔
#define FILE_BULLET	("Image/Bullet.png")

//--- �R���X�g���N�^
CBullet::CBullet(E_BULLET Type, float PosX, float PosY, float MoveX, float MoveY)
{
	// �����ݒ�
	SetPos(PosX, PosY);
	SetMove(MoveX, MoveY);
	m_Animation.SetSize(50.0f, 50.0f);
	SetTag(E_OBJ::BULLET);
	m_Type = Type;
	// ��ނ��Ƃ̐ݒ�
	switch (Type)
	{
	case E_BULLET::NORMAL:
		m_Animation.SetImage(FILE_BULLET);
		m_Animation.SetSplit(2, 1);
		m_Animation.SetAnime(0, 0, 2, 4);
		break;

	default:
		break;
	}

}

//--- �f�X�g���N�^
CBullet::~CBullet()
{

}

//--- �X�V
void CBullet::Update()
{

	//-- �����蔻��
	// �G
	CObject* pTObj = Hit(0.6f, 0.8f);
	if (pTObj->GetType() == E_OBJ::ENEMY)
	{
		//Destroy();
	}

	// ��ʊO
	if ((m_Position.x < 0)
		|| (m_Position.y < 0)
		|| (m_Position.x > CField::GetSize().x * 100)
		|| (m_Position.y > CField::GetSize().y * 100))
	{
		Destroy();
	}

	// �I�u�W�F�N�g�̍X�V
	CObject::Update();

}

//--- �`��
void CBullet::Draw()
{
	// �I�u�W�F�N�g�̕`��
	CObject::Draw();

}

