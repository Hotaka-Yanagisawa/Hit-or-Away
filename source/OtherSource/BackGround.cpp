///////////////////////////////////////
// BackGround.cpp
//-------------------------------------
// 2020/07/20	作成
//		08/10	Fieldに移動
//
//
///////////////////////////////////////

//--- インクルード部
#include "BackGround.h"
#include "Game.h"

//--- 定数・マクロ定義
#define F_BACK	("Image/Back.png")

//--- コンストラクタ
CBackGround::CBackGround()
{
	// 画像読み込み
	SetImage(F_BACK);

	SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_Coord = { 0, 0 };
}

//--- デストラクタ
CBackGround::~CBackGround()
{

}

//--- 更新
void CBackGround::Update()
{
	m_Coord.x += 0.001f;
	if (m_Coord.x >= 1.0f) m_Coord.x = 0.0f;
	m_Coord.y += 0.001f;
	if (m_Coord.y >= 1.0f) m_Coord.y = 0.0f;

	SetUV(m_Coord.x, m_Coord.y);

	// ポリゴンの更新
	CPolygon::Update();

}

//--- 描画
void CBackGround::Draw()
{
	// ポリゴンの描画
	CPolygon::Draw();

}

