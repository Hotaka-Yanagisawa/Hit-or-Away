////////////////////////////////////////
// Bullet.h
//--------------------------------------
// 2020/09/03	作成
//
////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Object.h"

//--- 列挙体
enum class E_BULLET		// 種類
{
	NORMAL,

	MAX
};

//--- クラス
class CBullet : public CObject
{
public:

	CBullet(E_BULLET, float PosX, float PosY, float MoveX, float MoveY);
	~CBullet();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

	E_BULLET GetType()
	{
		return m_Type;
	}

private:

	E_BULLET m_Type;	// 種類

};
