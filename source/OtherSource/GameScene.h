///////////////////////////////////////////
// GameScene.h
//-----------------------------------------
// 2020/08/05	タイトルをコピーして作成
//		08/10	ゲーム終了時の状態
//
///////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Scene.h"
#include "Camera.h"
#include "Stage.h"
#include "BackGround.h"
#include "GUI.h"
#include "Pattern.h"
#include "MySound.h"

//--- 列挙体
enum class GAME_RESULT	// ゲーム結果
{
	NO,
	CLEAR,		// クリア
	MISS,		// 失敗
	BREAK,		// 中断
	RESTART,	// やり直し
	MAX
};
enum PAUSE_MENU		// メニュー選択肢
{
	PAUSE_RESUME,	// 再開
	PAUSE_RETRY,	// やり直し
	PAUSE_END,		// 終了
	PAUSE_MAX
};

//--- クラス
class GameScene : public Scene
{
public:

	void Init();
	void Uninit();
	bool Update();
	void Draw();
	
	static GAME_RESULT GetResult();

private:

	CBackGround* m_pBG;	// 背景
	GUI* m_pGUI;		// システム
	PAUSE_MENU m_Menu;	// メニュー
	CStage* m_pStage;	// ステージ

	int m_nResultTime;	// リザルト画面タイマー
	bool m_bPause;		// ポーズ画面フラグ
	static GAME_RESULT m_Result;	// 終了時の状態

	CPolygon Fade;
	CPolygon Pause;
	CPolygon Resume;
	CPolygon Retry;
	CPolygon End;
	CAnime	 Arrow;

	CSound sound;
};

