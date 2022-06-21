///////////////////////////////////////
// BackGround.h
//-------------------------------------
// 2020/07/20	作成
//		08/10	Fieldに移動
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include "Polygon.h"

//--- クラス
class CBackGround : public CPolygon
{
public:

	CBackGround();	// コンストラクタ
	~CBackGround();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

private:

	VECTOR2<> m_Coord;

};

