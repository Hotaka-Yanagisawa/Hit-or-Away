///////////////////////////////////////
// Act.cpp
//-------------------------------------
// 2020/09/02	�쐬
//		09/03	���s�A�j������
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "Act.h"
#include "Field.h"

//--- �O���[�o���ϐ�
int CAct::m_nAnimeSpB;

//--- �R���X�g���N�^
CAct::CAct()
{
	m_nHp = 0;
	m_nAttack = 1;
	m_fSpeed = 1.0f;

	//m_bMove = false;
	//m_bAttack = false;
	//m_nAtkCnt = 0;
	
	m_AnimeBase = { 0, 0 };
	m_nAnimeNum = 4;

	m_nAnimeSpB = 10;

	m_Direct = m_OldDirect = E_DIRECT::MAX;
}

//--- �f�X�g���N�^
CAct::~CAct()
{

}

//--- �X�V
void CAct::Update()
{
	// �ړ����Ă���
	if ((m_Move.x != 0) || (m_Move.y != 0))
	{
		m_Animation.Play(true);
		// �������f
		if (!m_bLockDirect) UpdateDirect();

		// �ړ��������ς����
		if (m_Direct != m_OldDirect)
		{
			// �A�j���������ɍ��킹��
			m_Animation.Play(false);
			m_Animation.SetAnime(m_AnimeBase.x, m_AnimeBase.y + (int)m_Direct, m_nAnimeNum,
				m_nAnimeSpB - m_fSpeed);	// �A�j�����x
			// �������X�V
			m_OldDirect = m_Direct;
		}
	}
	// �ړ����Ă��Ȃ�
	else
	{
		m_Animation.Play(false);
		//m_Animation.SetUV(m_AnimeBase.x, m_AnimeBase.y - 1);
		//m_Direct = E_DIRECT::MAX;
	}

	// �I�u�W�F�N�g�̍X�V
	CObject::Update();

	// �t�B�[���h�O�ɏo�Ȃ�
	if (m_Position.x < 50) { m_Move.x = 0; m_Position.x = 50; }
	if (m_Position.y < 50) { m_Move.y = 0; m_Position.y = 50; }
	if (m_Position.x > CField::GetSize().x * 100 - 50) { m_Move.x = 0; m_Position.x = CField::GetSize().x * 100 - 50; }
	if (m_Position.y > CField::GetSize().y * 100 - 50) { m_Move.y = 0; m_Position.y = CField::GetSize().y * 100 - 50; }

}

//--- �`��
void CAct::Draw()
{
	// �I�u�W�F�N�g�̕`��
	CObject::Draw();

}

//--- �ړ�
// �ړ���
void CAct::Move(float fMoveX, float fMoveY)
{
	// �ړ��ʔ��f
	m_Move.x = fMoveX;
	m_Move.y = fMoveY;
}
// �p�x
void CAct::Move(float fAngle)
{
	// �ړ��ʂ����߂�

}

//--- �ړ��ʂ�����������߂�
void CAct::UpdateDirect()
{
	// ���̌�����ۑ�
	m_OldDirect = m_Direct;

	//--- �ł��傫���ړ��ʂɌ�����ς���
	// ��Βl
	float absMoveX = (m_Move.x > 0) ? m_Move.x : -m_Move.x;
	float absMoveY = (m_Move.y > 0) ? m_Move.y : -m_Move.y;
	// ��r
	if (absMoveX > absMoveY)
		if (m_Move.x > 0) m_Direct = E_DIRECT::RIGHT;
		else m_Direct = E_DIRECT::LEFT;
	else
		if (m_Move.y > 0) m_Direct = E_DIRECT::DOWN;
		else m_Direct = E_DIRECT::UP;
}

