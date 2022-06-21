//////////////////////////////////////////////////////////////////////////////////////////
// Enemy.cpp
//-------------------------------------
// �쐬�ҁFAT12D_35_���򔿋M
//-------------------------------------
// 2020/07/20	�쐬
//		07/26	�I�u�W�F�N�g���쐬���ăR���X�g���N�^���Ăяo����csv�t�@�C����̃f�[�^��
//				�I�u�W�F�N�g�̕ϐ��ɑ���ł���悤�ɂ����B
//		07/28	���̃��U���g�V�[���J�ڒǉ�(����)
//		08/     ���U���g�V�[���J�ڂ�SceneMgr�Ɉړ�
//      08/07   �X�e�[�g�����ɂ���i�o�O����j
//      09/01   �G�t�F�N�g�̒ǉ�
//      09/03   �v���C���[�ɂԂ���������SE�ǉ�
//				�G�l�~�[�̎��S�����������߂��ď�����悤�ɂ���
//		09/05   �X�e�[�g�����̃o�O�����Ȃ���!
//		09/06   �֐�Paths�̍쐬�A��Paths�Ŏg���֐��̍쐬
//				�ǂݍ���path�̎�ނɂ���ăe�N�X�`����ύX�o����悤�ɂ���
//
///////////////////////////////////////////////////////////////////////////////////////////

//--- �C���N���[�h��
#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "SceneMgr.h"
#include "effectList.h"
#include "ObjectMgr.h"
#include "Field.h"
#include <ctime>

using namespace std;

//--- �萔
#define FILE_ENEMY	("Image/Enemy.png")
#define FILE_BOSS   ("Image/Boss.png")

//--- �O���[�o���ϐ�
ObjectManager *g_pObjMgr;


int CEnemy::m_nNum;		// �����J�E���g�p
bool CEnemy::m_bBoss;
CSound CEnemy::sound;

//--- �R���X�g���N�^
CEnemy::CEnemy(CPlayer *player, HierarchyState *state, PATHS Path, float x, float y)
{
	m_Path = Path;
	// �摜�ǂݍ���
	//if (Path != PATHS::BOSS)
	//{
	//	m_Animation.SetImage(FILE_ENEMY);
	//	m_Animation.SetSplit(8, 9);
	//}
	//else
	//{
	//	m_Animation.SetImage(FILE_BOSS);
	//	m_Animation.SetSplit(2, 1);
	//}

	m_fSpd = 1.0f;
	SetTag(E_OBJ::ENEMY);
	// ��ނ��Ƃ̐ݒ�
	SetCharacter(Path);

	SetPos(x, y);
	m_Animation.SetSize(100.0f, 100.0f);

	// �X�e�[�^�X�̏�����
	m_nHp = 1;
	m_FixedPos = GetPos();

	// �v���C���[���̎擾
	m_Player = player;

	// �K�w�A��Ԃ̎擾
	m_State = state;
	m_State->Init(this);

	// ���J�E���g
	m_nNum++;

	//���S�������̏�����
	if (m_Path != PATHS::BOSS)
	{
		m_fadeCnt = 60.0f;
	}
	else
	{
		m_fadeCnt = 300.0f;
	}
	m_DeltaTime = 0;
	m_bDestroy = false;
	m_moveTime = 0;
	m_bBoss = false;
	m_fDestroyCnt = (rand() % 180 + 30) / 60.0f;

	if (m_Path == PATHS::BOSS)
	{
		RandomCreateEnemy();
	}
}

//--- �f�X�g���N�^
CEnemy::~CEnemy()
{

}

//--- ������
void CEnemy::Init()
{
	srand((unsigned)time(NULL));
	//�T�E���h�̏�����
	sound.m_pBuffer = sound.CreateSound("sound/punch-heavy2.mp3", false);

	g_pObjMgr = &Singleton<ObjectManager>::GetInstance();
}

//--- �X�V
void CEnemy::Update()
{
	if (!m_bDestroy)
	{
		CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();

		if (m_bBoss)
		{
			m_bHit = false;
			m_fSpd = 0;
			m_fDestroyCnt -= 1.0f / 60;
			if (m_fDestroyCnt < 0)
			{
				m_bDestroy = true;

				// �G�̍��v���J�E���g�����炷
				m_nNum--;
				// �u�o�V�b�v�Đ�
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 0.1f, 0.01f);

				// �����G�t�F�N�g
				pEffectList->CreateEffect(GetPos().x, GetPos().y, EXPLOSION);
				// ��ʗh�炵
				GetCamera()->Shake(30);
			}
		}
		//--- �����蔻��
		// �v���C���[�̍U��
		if (Hit(0.6f, 0.8f)->GetType() == E_OBJ::BULLET)
		{
			if (m_Path != PATHS::BOSS)
			{
				// �G�t�F�N�g
				pEffectList->CreateEffect(GetPos().x, GetPos().y, EXPLOSION);
			}
			else
			{
				SetCharacter(PATHS::BOSS);
				m_bBoss = true;
				// �G�t�F�N�g
				pEffectList->CreateEffect(GetPos().x, GetPos().y, FIRE);
			}
			// ���S
			m_bDestroy = true;
			m_bHit = false;
			m_fSpd = 0;
			// �G�̍��v���J�E���g�����炷
			m_nNum--;
			// �u�o�V�b�v�Đ�
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);

			// ��ʗh�炵
			GetCamera()->Shake(4);
		}
		if (Hit(0.6f, 0.8f)->GetType() != E_OBJ::PLAYER)
			m_Animation.SetColor(1, 1, 1, 1);

		//Fade���Ă΂ꂽ��@�\����
		sound.Update();

		if (m_bExist)
		{
			if (m_Path != STOP)
				m_State->Update(this);
		}
	
	}
	else
	{

		UpdateDestroyFade();
	}

	// �I�u�W�F�N�g�̍X�V
	CObject::Update();
}

//--- �`��
void CEnemy::Draw()
{
	// �I�u�W�F�N�g�̕`��

	CObject::Draw();
}


void CEnemy::UpdateDestroyFade()
{
	float rate;
	m_DeltaTime += 1.0f;
	rate = 1.0f - m_DeltaTime / m_fadeCnt;
	m_Animation.SetColor(1.0f, 1.0f, 1.0f, rate);

	if (rate <= 0.0f)
	{
		Destroy();
	}
	if (m_bBoss)
	{
		if (m_Path == PATHS::BOSS)
			SetCharacter(PATHS::BOSS);
	}
}

void CEnemy::SetCharacter(PATHS Path)
{
	switch (Path)
	{
	case STOP:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::SLIME;
		m_Animation.SetAnime(0, 1, 4, 10);
		m_nHp = 1;
		m_fSpd = 1.0f;
		break;

	case UP_AND_DOWN:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::RED_SLIME;
		m_Animation.SetAnime(4, 1, 4, 10);
		m_nHp = 1;
		m_fSpd = 2.0f;
		break;

	case LEFT_AND_RIGHT:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::RED_SLIME;
		m_Animation.SetAnime(4, 1, 4, 10);
		m_nHp = 1;
		m_fSpd = 2.0f;
		break;

	case UP_DOWN_LEFT_RIGHT:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::RED_SLIME;
		m_Animation.SetAnime(4, 1, 4, 10);
		m_nHp = 1;
		m_fSpd = 2.0f;
		break;

	case RUSH_AND_REST:
		//�������Ă܂���
		break;

	case TERESA:
		//�������Ă܂���
		//m_Type = E_ENEMY::GHOST;
		//m_Animation.SetAnime(0, 5, 3, 10);
		//m_nHp = 1;
		//m_fSpd = 1.0f;
		break;

	case TARGET_PLAYER:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::GHOST;
		m_Animation.SetAnime(0, 5, 3, 10);
		m_nHp = 1;
		m_fSpd = 1.0f;
		break;

	case TARGET_PLAYER_AND_RETURN:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::HIGH_GHOST;
		m_Animation.SetAnime(4, 5, 3, 10);
		m_nHp = 1;
		m_fSpd = 4.0f;
		break;

	case BOSS:
		m_Animation.SetImage(FILE_BOSS);
		m_Animation.SetSplit(2, 1);
		m_Animation.Play(false);
		m_Type = E_ENEMY::KING;
		m_Animation.SetAnime(4, 8, 3, 10);
		m_nHp = 1;
		m_fSpd = 1.0f;
		break;
	case MAX_PATHS:
		break;
	default:
		break;
	}
}

void CEnemy::SetType(E_ENEMY Type)
{
	m_Type = Type;

	m_Animation.Play(false);
	switch (Type)
	{
	case E_ENEMY::SLIME:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::SLIME;
		m_Animation.SetAnime(0, 1, 4, 10);
		m_fSpd = 1.0f;
		break;

	case E_ENEMY::HIGH_GHOST:
		m_Animation.SetImage(FILE_ENEMY);
		m_Animation.SetSplit(8, 9);
		m_Type = E_ENEMY::HIGH_GHOST;
		m_Animation.SetAnime(4, 5, 3, 10);
		m_nHp = 1;
		m_fSpd = 4.0f;
		break;

	case E_ENEMY::KING:
		m_Animation.SetImage(FILE_BOSS);
		m_Animation.SetSplit(2, 1);
		m_Type = E_ENEMY::KING;
		m_Animation.SetAnime(4, 8, 3, 10);
		m_nHp = 1;
		m_fSpd = 1.0f;
		break;

	default:
		break;
	}
}

bool CEnemy::Paths(PATHS Pattern, int time)
{
	switch (Pattern)
	{
	case STOP:
		return false;
	case UP_AND_DOWN:
		return UpAndDown(time);

	case LEFT_AND_RIGHT:
		return LeftAndRight(time);

	case UP_DOWN_LEFT_RIGHT:
		return UDAndLR(time);

	case RUSH_AND_REST:
		return false;

	case TERESA:
		return false;

	case TARGET_PLAYER:
		m_Move.x = 0;
		m_Move.y = 0;
		return true;
	case TARGET_PLAYER_AND_RETURN:
		return Return();
	case BOSS:
		return Escape(time);
	case MAX_PATHS:
		break;
	default:
		break;
	}
	return false;
}

//--- �G�̐��擾
int CEnemy::GetNum()
{
	return m_nNum;
}

//--- �G�̐�������
void CEnemy::ResetNum()
{
	m_nNum = 0;
}

void CEnemy::ResetTime()
{
	m_moveTime = 0;
}

E_ENEMY CEnemy::GetEnemyType()
{
	return m_Type;
}

PATHS CEnemy::GetPath()
{
	return m_Path;
}

int CEnemy::AddTime(int add)
{
	m_moveTime += add;
	return m_moveTime;
}

// ��ԕύX
void CEnemy::ChangeState(HierarchyState *new_state)
{
	ResetTime();
	m_State = new_state;
	m_State->Init(this);
}

// �v���C���[�Ƃ̋����`�F�b�N
bool CEnemy::IsDistanceToPlayer(float distance, bool is_out_side)
{
	if (is_out_side == false)
	{
		return GetDistance() <= distance ? true : false;
	}
	return GetDistance() >= distance ? true : false;
}

// �v���C���[�Ƃ̋����擾
float CEnemy::GetDistance()
{
	float x =
		(m_Position.x - m_Player->GetPos().x) * (m_Position.x - m_Player->GetPos().x);
	float y =
		(m_Position.y - m_Player->GetPos().y) * (m_Position.y - m_Player->GetPos().y);

	return sqrt(x + y);
}

// �ړ�
void CEnemy::Move(int move_vec)
{
	if (move_vec & MOVE_VEC::LEFT)
	{
		m_Position.x -= m_fSpd;
	}
	else if (move_vec & MOVE_VEC::RIGHT)
	{

		m_Position.x += m_fSpd;
	}
	else if (move_vec & MOVE_VEC::UP)
	{
		m_Position.y -= m_fSpd;
	}
	else if (move_vec & MOVE_VEC::DOWN)
	{
		m_Position.y += m_fSpd;
	}
}

// �ǐ�
void CEnemy::Chase()
{
	float move_vec_x = m_Player->GetPos().x - m_Position.x;
	float move_vec_y = m_Player->GetPos().y - m_Position.y;

	if (move_vec_x >= 0)	m_Move.x = m_fSpd;
	else                    m_Move.x = -m_fSpd;

	if (move_vec_y >= 0)	m_Move.y = m_fSpd;
	else                    m_Move.y = -m_fSpd;
}

bool CEnemy::Return()
{
	float move_vec_x = m_FixedPos.x - m_Position.x;
	float move_vec_y = m_FixedPos.y - m_Position.y;

	if (move_vec_x >= 0)	m_Move.x = m_fSpd;
	else                    m_Move.x = -m_fSpd;

	if (move_vec_y >= 0)	m_Move.y = m_fSpd;
	else                    m_Move.y = -m_fSpd;

	return false;
}

bool CEnemy::UpAndDown(int time)
{
	if (time < 60)
	{
		Move(CEnemy::MOVE_VEC::UP);
		return false;
	}
	else if (time < 120)
	{
		Move(CEnemy::MOVE_VEC::DOWN);
		return false;
	}
	return true;
}

bool CEnemy::LeftAndRight(int time)
{
	if (time < 60)
	{
		Move(CEnemy::MOVE_VEC::LEFT);
		return false;
	}
	else if (time < 120)
	{
		Move(CEnemy::MOVE_VEC::RIGHT);
		return false;
	}
	return true;
}

bool CEnemy::UDAndLR(int time)
{
	if (time < 60)
	{
		Move(CEnemy::MOVE_VEC::UP);
		return false;
	}
	else if (time < 120)
	{
		Move(CEnemy::MOVE_VEC::DOWN);
		return false;
	}
	if (time < 180)
	{
		Move(CEnemy::MOVE_VEC::LEFT);
		return false;
	}
	else if (time < 240)
	{
		Move(CEnemy::MOVE_VEC::RIGHT);
		return false;
	}
	return true;
}


void CEnemy::RandomCreateEnemy(int time)
{
	//---�ϐ��錾
	float AppearX;
	float AppearY;
	PATHS enemyPathType;
	int nFieldCenterX;
	int nFieldCenterY;

	//---������
	AppearX = 0;
	AppearY = 0;
	enemyPathType = PATHS::BOSS;
	nFieldCenterX = CField::GetSize().x * 80;
	nFieldCenterY = CField::GetSize().y * 80;


	if (time % 10 < 1)
	{
		for (int i = 0; i < 30; i++)
		{
			if (CEnemy::GetNum() > 250) break;
			enemyPathType = (PATHS)(rand() % 2);
			AppearX = rand() % nFieldCenterX + 100;
			AppearY = rand() % nFieldCenterY + 100;
			g_pObjMgr->CreateEnemy(enemyPathType, AppearX, AppearY);	//�����_��
		}
	}
}

void CEnemy::RandomCreateEnemy()
{
	//---�ϐ��錾
	float AppearX;
	float AppearY;
	PATHS enemyPathType;
	int nFieldCenterX;
	int nFieldCenterY;

	//---������
	AppearX = 0;
	AppearY = 0;
	enemyPathType = PATHS::BOSS;
	nFieldCenterX = CField::GetSize().x * 80;
	nFieldCenterY = CField::GetSize().y * 80;



	for (int i = 0; i < 30; i++)
	{
		if (CEnemy::GetNum() > 180) break;
		enemyPathType = (PATHS)(rand() % 2);
		AppearX = rand() % nFieldCenterX + 100;
		AppearY = rand() % nFieldCenterY + 100;
		g_pObjMgr->CreateEnemy(enemyPathType, AppearX, AppearY);	//�����_��
	}
}


bool CEnemy::Escape(int time)
{
	//---�ϐ��錾
	float fFieldSizeX;
	float fFieldSizeY;
	float EnemyPosX;
	float EnemyPosY;
	int num = rand() % 9;

	//---������
	fFieldSizeX = CField::GetSize().x * 100;
	fFieldSizeY = CField::GetSize().y * 100;
	EnemyPosX = 0;
	EnemyPosY = 0;

	if (time % 30 < 1)

	if(m_Type != E_ENEMY::KING)	SetType(E_ENEMY::KING);

	if (time % 60 < 1)
	{
		// �����_���œ�����
		switch (num)
		{
		case 0:
			EnemyPosX = fFieldSizeX * 0.25f;
			EnemyPosY = fFieldSizeY * 0.5f;
			break;
		case 1:
			EnemyPosX = fFieldSizeX * 0.75f;
			EnemyPosY = fFieldSizeY * 0.5f;
			break;
		case 2:
			EnemyPosX = fFieldSizeX * 0.5f;
			EnemyPosY = fFieldSizeY * 0.75f;
			break;
		case 4:
			EnemyPosX = fFieldSizeX * 0.5f;
			EnemyPosY = fFieldSizeY * 0.25f;
			break;
		case 5:
			EnemyPosX = fFieldSizeX * 0.25f;
			EnemyPosY = fFieldSizeY * 0.15f;
			break;
		case 6:
			EnemyPosX = fFieldSizeX * 0.5f;
			EnemyPosY = fFieldSizeY * 0.25f;
			break;
		case 7:
			EnemyPosX = fFieldSizeX * 0.25f;
			EnemyPosY = fFieldSizeY * 0.15f;
			break;
		case 8:
			EnemyPosX = fFieldSizeX * 0.25f;
			EnemyPosY = fFieldSizeY * 0.15f;
			break;
		default:
			break;
		}
		//���~�ߗp�̃L����
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x + 100, m_Player->GetPos().y);	// �E
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x - 100, m_Player->GetPos().y);	// ��
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x, m_Player->GetPos().y + 200);	// ��
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x, m_Player->GetPos().y - 200);	// ��
		SetPos(EnemyPosX, EnemyPosY);

		SetType(E_ENEMY::HIGH_GHOST);

		return true;
	}
	return false;
}