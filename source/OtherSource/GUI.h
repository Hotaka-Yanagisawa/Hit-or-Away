////////////////////////////////////////
// GUI.h
//--------------------------------------
// 2020/09/26	作成
//
////////////////////////////////////////

#pragma once

//--- インクルード部
#include "PolygonList.h"
#include "Anime.h"

//--- クラス
class GUI
{
public:

	void Init();	// 初期化
	void Uninit();	// 終了

	void Update();	// 更新
	void Draw();	// 描画

private:

	bool m_bTutorial;		// 操作表示するしない

	CPolygonList* m_Apple;	// パワー
	CAnime* m_Shine;		// キラキラ
	CAnime* m_Push;			// ボタン
	CPolygon* m_EnemySym;	// 敵

};


