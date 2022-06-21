//////////////////////////////////////////////////////////////////////////////////////////
// Effect.h
//------------------------------------------------------------------------------------------
// �쐬�ҁF���򔿋M
//------------------------------------------------------------------------------------------
// �G�t�F�N�g�Ɋւ��邱��
//------------------------------------------------------------------------------------------
// 2020/08/08	�쐬
// 
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Anime.h"

#define MAX_EFFECT (2)

enum FX_KIND
{
	EXPLOSION,
	FIRE,

	MAX_FX
};

class Effect : public CAnime
{
public:
	Effect() {};
	Effect(FX_KIND kind, float x, float y);

	~Effect();

	static void Init();
	static void Uninit();
	void Update();
	void Draw();

private:
	VECTOR2<> m_Pos;

	static CTexture m_Texture[MAX_EFFECT];
};


