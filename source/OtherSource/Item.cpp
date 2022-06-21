///////////////////////////////////////
// Item.cpp
// �쐬�ҁF���򔿋M
//-------------------------------------
// 2020/09/06	�쐬
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "Item.h"
#include "Player.h"
#include "Stage.h"

//--- �萔��`
#define FILE_ITEM	("Image/Item.png")

int CItem::m_nNum;		// �����J�E���g�p

//--- �R���X�g���N�^
CItem::CItem(E_ITEM Type, float x, float y)
{
	SetTag(E_OBJ::ITEM);
	m_Animation.SetImage(FILE_ITEM);
	m_Animation.SetSplit(4, 2);
	m_Animation.SetSize(100.0f, 100.0f);

	switch (Type)
	{
	case E_ITEM::APPLE:
		m_Animation.SetAnime(0, 0, 4, 10);
		break;

	case E_ITEM::BAD_APPLE:

		break;

	case E_ITEM::SPILIT:
		m_Animation.SetAnime(0, 1, 4, 10);
		m_nNum++;
		break;

	default:
		break;
	}

	m_Type = Type;
	SetPos(x, y);

	sound.m_pSpeaker = NULL;
}

//--- �f�X�g���N�^
CItem::~CItem()
{

}

//--- �X�V
void CItem::Update()
{
	// �����蔻��
	if (Hit(0.1f,0.1f)->GetType() == E_OBJ::PLAYER)
	{
		// �����S
		if (m_Type == E_ITEM::APPLE)
		{
			sound.m_pBuffer = sound.CreateSound("sound/touch1.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			CPlayer::SetSpecial(1);
			// ����
			Destroy();
		}

		// ��
		if (m_Type == E_ITEM::SPILIT)
		{
			sound.m_pBuffer = sound.CreateSound("sound/touch1.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			CStage::SetSpilit(1);
			// ����
			Destroy();
		}
	}
	
	// �I�u�W�F�N�g�̍X�V
	CObject::Update();
}

//--- �`��
void CItem::Draw()
{
	// �I�u�W�F�N�g�̕`��
	CObject::Draw();
}

int CItem::GetNum()
{
	return m_nNum;
}
