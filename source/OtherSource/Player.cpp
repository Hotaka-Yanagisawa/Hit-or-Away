///////////////////////////////////////
// Player.cpp
//-------------------------------------
// 2020/07/17	�쐬
//		07/20	�Ȃ񂩂��낢�����
//		07/26	�ړ��ǉ�			��
//				�J����.���ʉ����� ��
//		07/30	���s�A�j���[�V����
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "Player.h"
#include "Keyboard.h"
#include "GameScene.h"
#include "Bullet.h"
#include "Stage.h"
#include "Camera.h"
#include "TitleScene.h"

//--- �萔
#define FILE_PLAYER_ARMOR	("Image/Armor.png")
#define FILE_PLAYER_THIEF	("Image/Thief.png")
#define FILE_PLAYER_SNIPE	("Image/Sniper.png")

//--- �O���[�o���ϐ�
bool CPlayer::m_bResult;
bool CPlayer::m_bCharge;
int CPlayer::m_nSpecial;

//--- �R���X�g���N�^
CPlayer::CPlayer(E_PLAYER Type, float x, float y)
{
	// �摜�ǂݍ���
	m_Animation.SetSplit(4, 5);
	// �����ݒ�
	SetPos(x, y);
	m_Animation.SetSize(100.0f, 100.0f);
	SetWalkAnime(0, 1);
	SetTag(E_OBJ::PLAYER);
	m_nAtkCnt = 0;
	m_bCharge = false;
	m_nSpecial = 0;
	m_bResult = false;
	m_Type = Type;

	// ��ނ��Ƃ̐ݒ�
	switch (Type)
	{
	case E_PLAYER::ARMOR:
		m_Animation.SetImage(FILE_PLAYER_ARMOR);
		m_nHp = 50;
		m_fSpeed = 4.0f;
		break;

	case E_PLAYER::THIEF:
		m_Animation.SetImage(FILE_PLAYER_THIEF);
		m_nHp = 1;
		m_fSpeed = 7.0f;
		break;

	case E_PLAYER::SNIPE:
		m_Animation.SetImage(FILE_PLAYER_SNIPE);
		m_nHp = 3;
		m_fSpeed = 5.0f;
		m_bCharge = true;
		break;
	default:
		break;
	}
	//��
	sound.m_pSpeaker = NULL;
}

//--- �f�X�g���N�^
CPlayer::~CPlayer()
{

}

//--- �X�V
void CPlayer::Update()
{
	if ((IsKeyTrigger('S'))
		&& ((int)TitleScene::GetSelectStage() > 4)
		&& (m_Move.x + m_Move.y == 0))
	{
		sound.m_pBuffer = sound.CreateSound("sound/switch1.mp3", false);
		sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
		if (m_Type == E_PLAYER::SNIPE)
		{
			m_Type = E_PLAYER::ARMOR;
		}
		else
		{
			m_Type = (E_PLAYER)(1 + (int)m_Type);
		}
		switch (m_Type)
		{
		case E_PLAYER::ARMOR:
			m_Animation.SetImage(FILE_PLAYER_ARMOR);
			m_nHp = 50;
			m_fSpeed = 4.0f;
			break;

		case E_PLAYER::THIEF:
			m_Animation.SetImage(FILE_PLAYER_THIEF);
			m_nHp = 1;
			m_fSpeed = 7.0f;
			break;

		case E_PLAYER::SNIPE:
			m_Animation.SetImage(FILE_PLAYER_SNIPE);
			m_nHp = 3;
			m_fSpeed = 5.0f;
			break;
		default:
			break;
		}
	}

	// �Q�[������
	if (GameScene::GetResult() != GAME_RESULT::NO)
	{
		m_Animation.SetColor(1, 1, 1, 1);
		// �\��ω�
		switch (GameScene::GetResult())
		{
		case GAME_RESULT::CLEAR:
			m_Animation.SetUV(1, 0);
			break;
		case GAME_RESULT::MISS:
			if(m_nHp > 0)
				m_Animation.SetUV(2, 0);
			break;
		default:
			break;
		}

		return;	// �������Ȃ�
	}

	//-- �����蔻��
	CObject* pTObj = Hit(0.6f, 0.8f);
	//--- �U���\�ɂ���
	// �j��Ώ�
	if (m_Type == E_PLAYER::ARMOR)
	{
		if (((pTObj->GetType() == E_OBJ::BOX) && (m_nSpecial > 0))
			|| (pTObj->GetType() == E_OBJ::ENEMY))
		{
			pTObj->m_Animation.SetColor(1, 0.5f, 0.5f, 1);
			// �ːi��
			m_bCharge = true;
		}
		else if (m_nAtkCnt == 0) m_bCharge = false;
	}
	// ���蔲��
	if (m_Type == E_PLAYER::THIEF)
	{
		if (((pTObj->GetType() == E_OBJ::ROCK)) && (m_nSpecial > 0))
		{
			pTObj->m_Animation.SetColor(0.5f, 0.5f, 1, 1);
			// ��
			m_bCharge = true;
		}
		else m_bCharge = false;
	}
	// �e
	if (m_Type == E_PLAYER::SNIPE)
	{
		if (m_nSpecial > 0) m_bCharge = true;
		else m_bCharge = false;
	}
	// �G
	if (pTObj->GetType() == E_OBJ::ENEMY)
	{
		// �������
		m_Position.x += pTObj->GetMove().x - m_Move.x;
		m_Position.y += pTObj->GetMove().y - m_Move.y;
		m_Move = { 0, 0 };
		m_nAtkCnt = 0;

		if (m_Type != E_PLAYER::ARMOR)
		{
			// ������
			sound.m_pBuffer = sound.CreateSound("sound/punch-heavy3.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			GetCamera()->Shake(4);
			m_nHp--;
		}
	}
	// ��
	if ((pTObj->GetType() == E_OBJ::WALL)
		|| (pTObj->GetType() == E_OBJ::BOX)
		|| (pTObj->GetType() == E_OBJ::ROCK))
	{
		// �߂�
		m_Position.x -= m_Move.x;
		m_Position.y -= m_Move.y;
		m_Move = { 0, 0 };

	}
	// ��



	// �U��������Ȃ�
	if (m_nAtkCnt == 0)
	{
		E_FIELD FType = CField::GetType();
		// ���C(�X��)
		if(FType != E_FIELD::ICE) Move(0, 0);
		// �����Œ�
		if (IsKeyPress(VK_SHIFT)) Lock();
		else Lock(false);
		// �㉺���E�ړ�
		if((FType == E_FIELD::STEPPE) ||
			((FType == E_FIELD::ICE) && (m_Move.x + m_Move.y == 0)))
		{
			if (IsKeyPress(VK_UP))		Move(0, -m_fSpeed);
			if (IsKeyPress(VK_DOWN))	Move(0, m_fSpeed);
			if (IsKeyPress(VK_LEFT))	Move(-m_fSpeed, 0);
			if (IsKeyPress(VK_RIGHT))	Move(m_fSpeed, 0);
		}
	}
	if ((m_Type == E_PLAYER::ARMOR) && (m_nAtkCnt == 0)) SetTag(E_OBJ::PLAYER);

	// ����Z
	if (m_bCharge)
	{
		switch (m_Type)
		{
		case E_PLAYER::ARMOR:	// �̓�����
		{
			if ((IsKeyTrigger('A')) && (m_nAtkCnt == 0))
			{
				// �U������
				m_nAtkCnt = 5;
			}

			// �U������ɂ���
			if (m_nAtkCnt > 0)
			{
				// �e��
				SetTag(E_OBJ::BULLET);
				m_nAtkCnt--;
				if (m_Direct == E_DIRECT::UP) SetMove(0, -4);
				if (m_Direct == E_DIRECT::DOWN) SetMove(0, 4);
				if (m_Direct == E_DIRECT::LEFT) SetMove(-4, 0);
				if (m_Direct == E_DIRECT::RIGHT) SetMove(4, 0);

				CAct::Update();

				// �ǂƏՓ�
				CObject* tempObject = Hit(0.6f, 0.8f);
				if (tempObject != NULL &&
					(tempObject->GetType() == E_OBJ::WALL)
					|| (tempObject->GetType() == E_OBJ::BOX)
					|| (tempObject->GetType() == E_OBJ::ROCK))
				{
					sound.m_pBuffer = sound.CreateSound("sound/punch-heavy2.mp3", false);
					sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
					if ((m_nSpecial > 0)
						&& (tempObject->GetType() == E_OBJ::BOX))
					{
						// �j��
						tempObject->Destroy();
						m_nSpecial--;
						GetCamera()->Shake(8);
					}
					else
					{
						// �߂�
						m_Position.x -= m_Move.x;
						m_Position.y -= m_Move.y;
						m_Move = { 0, 0 };
					}

					m_nAtkCnt = 0;
				}
			}

			break;
		}
		case E_PLAYER::THIEF:
		{
			if (IsKeyTrigger('A'))
			{
				sound.m_pBuffer = sound.CreateSound("sound/punch-real-swing1.mp3", false);

				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);

				if (m_Direct == E_DIRECT::UP   ) m_Move.y = -185;
				if (m_Direct == E_DIRECT::DOWN ) m_Move.y = 185;
				if (m_Direct == E_DIRECT::LEFT ) m_Move.x = -180;
				if (m_Direct == E_DIRECT::RIGHT) m_Move.x = 180;
				m_nAtkCnt = 20;
				m_bCharge = false;
				m_Position.x += m_Move.x;
				m_Position.y += m_Move.y;
			}
			if (m_nAtkCnt > 0)
			{
				CObject* pTObj = Hit(0.6f, 0.6f);
				if ((pTObj->GetType() == E_OBJ::WALL)
					|| (pTObj->GetType() == E_OBJ::BOX)
					|| (pTObj->GetType() == E_OBJ::ROCK))
				{
					// �߂�
					m_Position.x -= m_Move.x;
					m_Position.y -= m_Move.y;
				}
				else
				{
					m_nSpecial--;
				}

				m_Move = { 0, 0 };
			}

			break;
		}
		case E_PLAYER::SNIPE:	// �e
		{
			if ((IsKeyTrigger('A')) && (m_nSpecial > 0))
			{
				sound.m_pBuffer = sound.CreateSound("sound/cancel4.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
				if (m_Direct == E_DIRECT::UP)
					CStage::GetObjMgr()->CreateBullet(E_BULLET::NORMAL, m_Position.x, m_Position.y, 0, -10);
				if (m_Direct == E_DIRECT::DOWN)
					CStage::GetObjMgr()->CreateBullet(E_BULLET::NORMAL, m_Position.x, m_Position.y, 0, 10);
				if (m_Direct == E_DIRECT::LEFT)
					CStage::GetObjMgr()->CreateBullet(E_BULLET::NORMAL, m_Position.x, m_Position.y, -10, 0);
				if (m_Direct == E_DIRECT::RIGHT)
					CStage::GetObjMgr()->CreateBullet(E_BULLET::NORMAL, m_Position.x, m_Position.y, 10, 0);

				m_nSpecial--;
			}
		}
			break;

		default:
			break;
		}
	}
	if (m_Type == E_PLAYER::THIEF)
		if (m_nAtkCnt > 0) m_nAtkCnt--;

	// ���ꂽ
	if (m_nHp < 1)
	{
		m_bResult = true;
		m_Animation.SetUV(3, 0);
	}

	// �I�u�W�F�N�g�̍X�V
	CAct::Update();

}

//--- �`��
void CPlayer::Draw()
{
	// �I�u�W�F�N�g�̕`��
	CAct::Draw();

}

E_PLAYER CPlayer::GetPlayerType()
{
	return m_Type;
}

int CPlayer::GetSpecial()
{
	return m_nSpecial;
}

void CPlayer::SetSpecial(int val)
{
	m_nSpecial += val;
}

