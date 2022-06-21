//////////////////////////////////////////////////////////////////////////////////////////
// Effect.cpp
//------------------------------------------------------------------------------------------
// 作成者：柳沢帆貴
//------------------------------------------------------------------------------------------
// エフェクトに関すること
//------------------------------------------------------------------------------------------
// 2020/08/08	作成
// 2020/09/01   リストで管理することで作成と削除を容易した。
// 
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#include "Effect.h"
#include "Texture.h"
#include "Camera.h"

#define FX_NAME_0 ("Image/expBig.png")
#define FX_NAME_1 ("Image/particleBlue.png")


CTexture Effect::m_Texture[MAX_EFFECT];

Effect::Effect(FX_KIND kind, float x, float y)
{
	switch (kind)
	{
	case EXPLOSION:
		SetTexture(m_Texture[0].m_pTexture);
		SetSplit(6, 6);
		SetAnime(0, 0, 11, 1, false);
		SetSize(100, 100);
		break;
	case FIRE:
		SetTexture(m_Texture[1].m_pTexture);
		SetSplit(6, 6);
		SetAnime(0, 0, 36, 8, false);
		SetSize(100, 100);

	case MAX_FX:
		break;
	default:
		break;
	}
	//SetSize(200, 200);
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Pos = { x, y };
}

Effect::~Effect()
{

}

void Effect::Init()
{
	m_Texture[0].LoadTexture(FX_NAME_0);
	m_Texture[1].LoadTexture(FX_NAME_1);

}

void Effect::Uninit()
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		m_Texture[i].UnLoadTexture();
	}
}

void Effect::Update()
{
	SetPos(m_Pos.x - GetCamera()->GetPosX(), m_Pos.y - GetCamera()->GetPosY());
	CAnime::Update();
}

void Effect::Draw()
{
	CAnime::Draw();
}








