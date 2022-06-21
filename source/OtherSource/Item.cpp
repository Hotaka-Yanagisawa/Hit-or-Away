///////////////////////////////////////
// Item.cpp
// 作成者：柳沢帆貴
//-------------------------------------
// 2020/09/06	作成
//
///////////////////////////////////////

//--- インクルード部
#include "Item.h"
#include "Player.h"
#include "Stage.h"

//--- 定数定義
#define FILE_ITEM	("Image/Item.png")

int CItem::m_nNum;		// 総数カウント用

//--- コンストラクタ
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

//--- デストラクタ
CItem::~CItem()
{

}

//--- 更新
void CItem::Update()
{
	// 当たり判定
	if (Hit(0.1f,0.1f)->GetType() == E_OBJ::PLAYER)
	{
		// リンゴ
		if (m_Type == E_ITEM::APPLE)
		{
			sound.m_pBuffer = sound.CreateSound("sound/touch1.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			CPlayer::SetSpecial(1);
			// 消す
			Destroy();
		}

		// 魂
		if (m_Type == E_ITEM::SPILIT)
		{
			sound.m_pBuffer = sound.CreateSound("sound/touch1.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			CStage::SetSpilit(1);
			// 消す
			Destroy();
		}
	}
	
	// オブジェクトの更新
	CObject::Update();
}

//--- 描画
void CItem::Draw()
{
	// オブジェクトの描画
	CObject::Draw();
}

int CItem::GetNum()
{
	return m_nNum;
}
