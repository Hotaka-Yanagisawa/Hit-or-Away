///////////////////////////////////////////
// TitleScene.h
//-----------------------------------------
// 2020/07/17	作成
//		08/03	Updateでステージ種類を返す
//
///////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Scene.h"
#include "PolygonList.h"
#include "Anime.h"
#include "MySound.h"
#include "Stage.h"

//--- クラス
class TitleScene : public Scene
{
public:

	TitleScene();

	void Init();
	void Uninit();
	bool Update();
	void Draw();

	static STAGE_ID GetSelectStage();	// 選択されたステージの取得

private:

	static STAGE_ID m_SelectStage;	// 選択されたステージ
	int m_maxSelectable;			// 選択できるステージ数

	int		m_nCount;	// チカチカカウント
	int		m_nTime;	// 遷移タイマー
	bool	m_bSelect;	// セレクト画面
	bool	m_bUpDown;	// STARTフラグ
	int		m_nKingTalk;	// キングしゃべり

	CPolygonList m_TitlePolygon;
	CPolygonList m_SelectPolygon;
	CPolygonList m_StageImage;
	CPolygonList m_TipsList;

	CPolygon *Back, *Title, *PushEnter;	// タイトル
	CPolygon *Select, *Start, *Unlock;	// ステージ選択
	CAnime *Cursor, *LAllow, *RAllow;	// カーソル
	CPolygon *Tips, *Rela;				// 簡易説明
	CPolygon *Message, *Talk; CAnime *King;	// キングトーク

	CSound sound;
};

