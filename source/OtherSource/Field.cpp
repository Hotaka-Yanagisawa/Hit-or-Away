///////////////////////////////////////////
// Field.cpp
//-----------------------------------------
// 2020/08/05	作成
//		08/10	BackGroundから移動
//
///////////////////////////////////////////

//--- インクルード部
#include "Field.h"
#include "Game.h"
#include "Camera.h"
#include "Keyboard.h"

//--- 定数
#define FILE_FIELD	("Image/Steppe.png")

//--- グローバル変数
VECTOR2<> CField::m_fSize;
E_FIELD	CField::m_Type;

//--- コンストラクタ
CField::CField()
{

}

//--- デストラクタ
CField::~CField()
{

}

//--- 初期化
void CField::Init(E_FIELD Type, float SizeX, float SizeY)
{
	m_Type = Type;
	// 画像読み込み
	switch (Type)
	{
	case E_FIELD::STEPPE:
		SetImage(FILE_FIELD);
		break;
	case E_FIELD::ICE:
		SetImage("Image/Ice.png");
		break;

	default:
		break;
	}

	// 広さ設定
	m_fSize = { SizeX, SizeY };
	SetPos(m_fSize.x * 100 / 2, m_fSize.y * 100 / 2);
	SetSize(m_fSize.x * 100, m_fSize.y * 100);
	
}

//--- 終了
void CField::Uninit()
{

}

//--- 更新
void CField::Update()
{
	// カメラ反映
	SetPos(m_fSize.x * 100 / 2 - GetCamera()->GetPosX(),
		m_fSize.y * 100 / 2 - GetCamera()->GetPosY());

	// ポリゴンの更新
	CPolygon::Update();

}

//--- 描画
void CField::Draw()
{
	// ポリゴンの描画
	CPolygon::Draw();

}



