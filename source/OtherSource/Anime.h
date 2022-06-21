///////////////////////////////////////
// Anime.cpp
//-------------------------------------
// 2020/09/03	作成
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include "Polygon.h"

//--- 列挙体
enum class ANIM_STATUS	// アニメの状態
{
	NO,		// なし
	PLAY,	// 再生中
	STOP,	// 停止中
	END,	// 終了している

	MAX
};

//--- クラス
class CAnime : public CPolygon
{
public:

	CAnime() {};	// コンストラクタ
	~CAnime() {};	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

	void SetAnime(int StartX, int StartY, int Num, int Pace, bool Loop = true);	// アニメ設定
	void Play(bool Play = true);	// アニメ再生停止
	ANIM_STATUS isPlay();			// アニメの状態取得

private:

	VECTOR2<int> m_Start;	// アニメ開始位置
	VECTOR2<int> m_End;		// アニメ終了位置
	int m_nPace;			// アニメ速度
	int m_nCount;			// カウンタ
	bool m_bLoop;			// ループ
	ANIM_STATUS m_Status;	// アニメの状態

};
