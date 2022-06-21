///////////////////////////////////////
// Item.h
//-------------------------------------
// 2020/07/30	作成
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include "Object.h"
#include "MySound.h"

//--- 列挙体
enum class E_ITEM
{
	APPLE,
	BAD_APPLE,
	SPILIT,

	MAX
};

//--- クラス
class CItem : public CObject
{
public:

	CItem(E_ITEM Type, float x = 0.0f, float y = 0.0f);
	~CItem();

	void Update();
	void Draw();

	static int GetNum();
	static void ResetNum() { m_nNum = 0; };
	
private:

	E_ITEM m_Type;	// 種類
	static int m_nNum;

	CSound sound;
};

