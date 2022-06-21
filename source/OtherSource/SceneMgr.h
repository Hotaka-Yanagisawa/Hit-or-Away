///////////////////////////////////////
// SceneMgr.h
//-------------------------------------
// 2020/07/28	作成
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include <Windows.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "Fade.h"
#include "MySound.h"

//--- 列挙体
enum SCENE
{
	SCENE_TITLE,	// タイトル
	SCENE_GAME,		// ゲーム

	SCENE_MAX
};

//--- クラス
class SceneManager
{
public:

	void SetStartScene();	// マネージャーの初期化

	// シーンごとの処理
	HRESULT Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

private:

	SCENE m_scene;			// 現在のシーン
	SCENE m_nextScene;		// 次のシーン(予約)

	TitleScene* m_title;	// タイトルシーンの処理
	GameScene* m_game;		// ゲームシーンの処理

	Fade m_fade;			// フェード処理
	CSound sound;			// サウンド
};

