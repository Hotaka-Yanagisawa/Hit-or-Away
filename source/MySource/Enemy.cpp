//////////////////////////////////////////////////////////////////////////////////////////
// Enemy.cpp
//-------------------------------------
// 作成者：AT12D_35_柳沢帆貴
//-------------------------------------
// 2020/07/20	作成
//		07/26	オブジェクトを作成してコンストラクタを呼び出すとcsvファイル上のデータを
//				オブジェクトの変数に代入できるようにした。
//		07/28	仮のリザルトシーン遷移追加(水野)
//		08/     リザルトシーン遷移をSceneMgrに移動
//      08/07   ステート処理にする（バグあり）
//      09/01   エフェクトの追加
//      09/03   プレイヤーにぶつかった時のSE追加
//				エネミーの死亡時少しずつ透過して消えるようにした
//		09/05   ステート処理のバグ無くなった!
//		09/06   関数Pathsの作成、他Pathsで使う関数の作成
//				読み込んだpathの種類によってテクスチャを変更出来るようにした
//
///////////////////////////////////////////////////////////////////////////////////////////

//--- インクルード部
#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "SceneMgr.h"
#include "effectList.h"
#include "ObjectMgr.h"
#include "Field.h"
#include <ctime>

using namespace std;

//--- 定数
#define FILE_ENEMY	("Image/Enemy.png")
#define FILE_BOSS   ("Image/Boss.png")

//--- グローバル変数
ObjectManager *g_pObjMgr;


int CEnemy::m_nNum;		// 総数カウント用
bool CEnemy::m_bBoss;
CSound CEnemy::sound;

//--- コンストラクタ
CEnemy::CEnemy(CPlayer *player, HierarchyState *state, PATHS Path, float x, float y)
{
	m_Path = Path;
	// 画像読み込み
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
	// 種類ごとの設定
	SetCharacter(Path);

	SetPos(x, y);
	m_Animation.SetSize(100.0f, 100.0f);

	// ステータスの初期化
	m_nHp = 1;
	m_FixedPos = GetPos();

	// プレイヤー情報の取得
	m_Player = player;

	// 階層、状態の取得
	m_State = state;
	m_State->Init(this);

	// 個数カウント
	m_nNum++;

	//死亡時処理の初期化
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

//--- デストラクタ
CEnemy::~CEnemy()
{

}

//--- 初期化
void CEnemy::Init()
{
	srand((unsigned)time(NULL));
	//サウンドの初期化
	sound.m_pBuffer = sound.CreateSound("sound/punch-heavy2.mp3", false);

	g_pObjMgr = &Singleton<ObjectManager>::GetInstance();
}

//--- 更新
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

				// 敵の合計数カウントを減らす
				m_nNum--;
				// 「バシッ」再生
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 0.1f, 0.01f);

				// 爆発エフェクト
				pEffectList->CreateEffect(GetPos().x, GetPos().y, EXPLOSION);
				// 画面揺らし
				GetCamera()->Shake(30);
			}
		}
		//--- 当たり判定
		// プレイヤーの攻撃
		if (Hit(0.6f, 0.8f)->GetType() == E_OBJ::BULLET)
		{
			if (m_Path != PATHS::BOSS)
			{
				// エフェクト
				pEffectList->CreateEffect(GetPos().x, GetPos().y, EXPLOSION);
			}
			else
			{
				SetCharacter(PATHS::BOSS);
				m_bBoss = true;
				// エフェクト
				pEffectList->CreateEffect(GetPos().x, GetPos().y, FIRE);
			}
			// 死亡
			m_bDestroy = true;
			m_bHit = false;
			m_fSpd = 0;
			// 敵の合計数カウントを減らす
			m_nNum--;
			// 「バシッ」再生
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);

			// 画面揺らし
			GetCamera()->Shake(4);
		}
		if (Hit(0.6f, 0.8f)->GetType() != E_OBJ::PLAYER)
			m_Animation.SetColor(1, 1, 1, 1);

		//Fadeが呼ばれたら機能する
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

	// オブジェクトの更新
	CObject::Update();
}

//--- 描画
void CEnemy::Draw()
{
	// オブジェクトの描画

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
		//実装してません
		break;

	case TERESA:
		//実装してません
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

//--- 敵の数取得
int CEnemy::GetNum()
{
	return m_nNum;
}

//--- 敵の数初期化
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

// 状態変更
void CEnemy::ChangeState(HierarchyState *new_state)
{
	ResetTime();
	m_State = new_state;
	m_State->Init(this);
}

// プレイヤーとの距離チェック
bool CEnemy::IsDistanceToPlayer(float distance, bool is_out_side)
{
	if (is_out_side == false)
	{
		return GetDistance() <= distance ? true : false;
	}
	return GetDistance() >= distance ? true : false;
}

// プレイヤーとの距離取得
float CEnemy::GetDistance()
{
	float x =
		(m_Position.x - m_Player->GetPos().x) * (m_Position.x - m_Player->GetPos().x);
	float y =
		(m_Position.y - m_Player->GetPos().y) * (m_Position.y - m_Player->GetPos().y);

	return sqrt(x + y);
}

// 移動
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

// 追跡
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
	//---変数宣言
	float AppearX;
	float AppearY;
	PATHS enemyPathType;
	int nFieldCenterX;
	int nFieldCenterY;

	//---初期化
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
			g_pObjMgr->CreateEnemy(enemyPathType, AppearX, AppearY);	//ランダム
		}
	}
}

void CEnemy::RandomCreateEnemy()
{
	//---変数宣言
	float AppearX;
	float AppearY;
	PATHS enemyPathType;
	int nFieldCenterX;
	int nFieldCenterY;

	//---初期化
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
		g_pObjMgr->CreateEnemy(enemyPathType, AppearX, AppearY);	//ランダム
	}
}


bool CEnemy::Escape(int time)
{
	//---変数宣言
	float fFieldSizeX;
	float fFieldSizeY;
	float EnemyPosX;
	float EnemyPosY;
	int num = rand() % 9;

	//---初期化
	fFieldSizeX = CField::GetSize().x * 100;
	fFieldSizeY = CField::GetSize().y * 100;
	EnemyPosX = 0;
	EnemyPosY = 0;

	if (time % 30 < 1)

	if(m_Type != E_ENEMY::KING)	SetType(E_ENEMY::KING);

	if (time % 60 < 1)
	{
		// ランダムで逃げる
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
		//足止め用のキャラ
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x + 100, m_Player->GetPos().y);	// 右
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x - 100, m_Player->GetPos().y);	// 左
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x, m_Player->GetPos().y + 200);	// 下
		g_pObjMgr->CreateEnemy(TARGET_PLAYER_AND_RETURN, m_Player->GetPos().x, m_Player->GetPos().y - 200);	// 上
		SetPos(EnemyPosX, EnemyPosY);

		SetType(E_ENEMY::HIGH_GHOST);

		return true;
	}
	return false;
}