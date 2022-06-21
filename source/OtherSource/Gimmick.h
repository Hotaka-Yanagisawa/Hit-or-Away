///////////////////////////////////////
// Gimmick.h
//-------------------------------------
// 2020/07/30	作成
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include "Object.h"

//--- 列挙体
enum class E_GIMMICK
{
	BOX,	// 壊せる壁
	WALL,	// 壊せない壁
	ROCK,	// シーフが通れる
	SWITCH,	// スイッチ
	FLOOR,	// 床

	MAX
};

//--- クラス
class CGimmick : public CObject
{
public:

	CGimmick(E_GIMMICK Type, float x = 0.0f, float y = 0.0f);
	~CGimmick();

	void Update();	// 更新
	void Draw();	// 描画

	void Destroy();	// 破壊

	static bool GetSwitch() { return m_bSwitch; };	// スイッチの情報

private:

	E_GIMMICK	m_Type;		// 種類
	static bool	m_bSwitch;	// スイッチ

	bool m_bBreak;

};

