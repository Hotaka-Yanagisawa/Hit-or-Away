///////////////////////////////////////
// Bullet.cpp
//-------------------------------------
// 2020/09/03	作成
//
///////////////////////////////////////

//--- インクルード部
#include "Bullet.h"
#include "Game.h"
#include "Field.h"

//--- 定数
#define FILE_BULLET	("Image/Bullet.png")

//--- コンストラクタ
CBullet::CBullet(E_BULLET Type, float PosX, float PosY, float MoveX, float MoveY)
{
	// 初期設定
	SetPos(PosX, PosY);
	SetMove(MoveX, MoveY);
	m_Animation.SetSize(50.0f, 50.0f);
	SetTag(E_OBJ::BULLET);
	m_Type = Type;
	// 種類ごとの設定
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

//--- デストラクタ
CBullet::~CBullet()
{

}

//--- 更新
void CBullet::Update()
{

	//-- 当たり判定
	// 敵
	CObject* pTObj = Hit(0.6f, 0.8f);
	if (pTObj->GetType() == E_OBJ::ENEMY)
	{
		//Destroy();
	}

	// 画面外
	if ((m_Position.x < 0)
		|| (m_Position.y < 0)
		|| (m_Position.x > CField::GetSize().x * 100)
		|| (m_Position.y > CField::GetSize().y * 100))
	{
		Destroy();
	}

	// オブジェクトの更新
	CObject::Update();

}

//--- 描画
void CBullet::Draw()
{
	// オブジェクトの描画
	CObject::Draw();

}

