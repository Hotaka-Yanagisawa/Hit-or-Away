///////////////////////////////////////
// Gimmick.cpp
//-------------------------------------
// 2020/07/30	作成
//
///////////////////////////////////////

//--- インクルード部
#include "Gimmick.h"
#include "Player.h"
#include "Keyboard.h"

//--- 定数定義
#define FILE_GIMMICK	("Image/Gimmick.png")

//--- グローバル変数
bool CGimmick::m_bSwitch;

//--- コンストラクタ
CGimmick::CGimmick(E_GIMMICK Type, float x, float y)
{
	
	m_Animation.SetSize(100.0f, 100.0f);
	m_Animation.SetImage(FILE_GIMMICK);
	m_Animation.SetSplit(4, 3);
	SetTag(E_OBJ::GIMICK);

	switch (Type)
	{
	case E_GIMMICK::BOX:
		SetTag(E_OBJ::BOX);
		m_Animation.SetUV(0, 0);
		break;

	case E_GIMMICK::WALL:
		SetTag(E_OBJ::WALL);
		m_Animation.SetUV(3, 0);
		break;

	case E_GIMMICK::ROCK:
		SetTag(E_OBJ::ROCK);
		m_Animation.SetUV(0, 1);
		break;

	case E_GIMMICK::SWITCH:
		m_bSwitch = false;
		m_Animation.SetUV(2 + m_bSwitch, 1);
		break;

	case E_GIMMICK::FLOOR:
		m_Animation.SetUV(0, 2);
		break;

	default:
		break;
	}

	m_Type = Type;
	m_bBreak = false;
	SetPos(x, y);

}

//--- デストラクタ
CGimmick::~CGimmick()
{

}

//--- 更新
void CGimmick::Update()
{
	switch (m_Type)
	{
	case E_GIMMICK::BOX:
		if ((Hit(0.6f, 0.8f)->GetType() != E_OBJ::PLAYER) && (CPlayer::GetSpecial()))
			m_Animation.SetColor(1, 1, 1, 1);

		if (m_bBreak)
		{
			if (m_Animation.isPlay() == ANIM_STATUS::END)
				CObject::Destroy();
		}

		break;

	case E_GIMMICK::ROCK:
		if (Hit(0.6f, 0.8f)->GetType() != E_OBJ::PLAYER)
			m_Animation.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	case E_GIMMICK::SWITCH:
		if (Hit(0.6f, 0.8f)->GetType() == E_OBJ::BULLET)
		{
			// 切り替え
			m_bSwitch ^= true;
			m_Animation.SetUV(2 + m_bSwitch, 1);
		}
		break;

	case E_GIMMICK::FLOOR:
		if (Hit(0.6f, 0.8f)->GetType() == E_OBJ::PLAYER)

		break;

	default:
		break;
	}

	// オブジェクトの更新
	CObject::Update();
}

//--- 描画
void CGimmick::Draw()
{
	// オブジェクトの描画
	CObject::Draw();
}

//--- 破壊
void CGimmick::Destroy()
{
	m_Animation.SetAnime(0, 0, 3, 2, false);
	m_bHit = false;
	m_bBreak = true;
}

