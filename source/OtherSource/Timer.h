///////////////////////////////////////////
// Timer.h
//-----------------------------------------
// 2020/07/25	作成
//		08/29	Initに引数追加
//
///////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Polygon.h"

//--- クラス
class CTimer
{
public:

	void Init(int Num);
	void Uninit();
	bool Update();
	void Draw();

private:

	int m_nCount;	//タイマーのカウンタ
	CPolygon* m_polygon;
	CPolygon* m_timer;

};

