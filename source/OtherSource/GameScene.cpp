///////////////////////////////////////////
// GameScene.cpp
//-----------------------------------------
// 2020/08/05	タイトルをコピーして作成
//		08/06	メニュー画面
//		08/
//
///////////////////////////////////////////

//--- インクルード部
#include "GameScene.h"
#include "TitleScene.h"
#include "Keyboard.h"

//--- グローバル変数
GAME_RESULT GameScene::m_Result;

//--- 初期化
void GameScene::Init()
{
	// 背景
	m_pBG = new CBackGround();

	// フェードの初期化
	Fade.SetImage(NULL);
	Fade.SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Fade.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	Fade.SetColor(0, 0, 0, 0.5f);
	//--- 画像の初期化
	// Pause
	Pause.SetImage("Image/Text.png");
	Pause.SetSplit(1, 7);
	Pause.SetUV(0, 2);
	Pause.SetPos(480, 120);
	Pause.SetSize(320, 80);
	// Resume
	Resume = Pause;
	Resume.SetUV(0, 3);
	Resume.SetPos(480, 210);
	// Retry
	Retry = Pause;
	Retry.SetUV(0, 4);
	Retry.SetPos(480, 290);
	// End
	End = Pause;
	End.SetUV(0, 5);
	End.SetPos(480, 370);
	// 矢印
	Arrow.SetImage("Image/Cursor.png");
	Arrow.SetSplit(3, 3);
	Arrow.SetAnime(0, 1, 3, 8);
	Arrow.SetPos(360, 210);
	Arrow.SetSize(50, 50);

	// ステージの初期化	
	m_pStage = new CStage();
	m_pStage->Init(TitleScene::GetSelectStage());

	// カメラの初期化
	GetCamera()->Init();
	GetCamera()->Update();

	// GUI
	m_pGUI = new GUI();
	m_pGUI->Init();

	m_Menu = PAUSE_RESUME;
	m_bPause = false;
	m_Result = GAME_RESULT::NO;
	m_nResultTime = 0;

	//サウンドの初期化
	sound.m_pBuffer = sound.CreateSound("sound/cursor10.mp3", false);
}

//--- 終了
void GameScene::Uninit()
{
	// GUIの終了
	m_pGUI->Uninit();
	delete m_pGUI;

	// カメラの終了
	GetCamera()->Uninit();

	// ステージの終了
	m_pStage->Uninit();
	delete m_pStage;

	// 背景の終了
	delete m_pBG;
}

//--- 更新
bool GameScene::Update()
{
	// リザルト画面の更新
	if (m_nResultTime > 0)
	{
		// カウントダウン
		m_nResultTime--;



		// ゲーム終了
		if (m_nResultTime == 0) return true;
	}

	// ポーズ画面の更新
	if (m_bPause)
	{
		// 矢印の更新
		Arrow.Update();

		// キャンセル
		if (IsKeyTrigger('Q'))
		{
			m_bPause = false;
		}

		// カーソル移動
		if (IsKeyRepeat(VK_UP))
		{
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.1f);

			if (m_Menu != PAUSE_RESUME)
				m_Menu = PAUSE_MENU((int)m_Menu - 1);
			else m_Menu = PAUSE_MENU((int)PAUSE_MAX - 1);
		}
		if (IsKeyRepeat(VK_DOWN))
		{
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.1f);

			m_Menu = PAUSE_MENU((int)m_Menu + 1);
			m_Menu = PAUSE_MENU((int)m_Menu % (int)PAUSE_MAX);
		}

		//Fadeが呼ばれたら機能する
		sound.Update();

		// ポーズ画面選択
		switch (m_Menu)
		{
		case PAUSE_RESUME:	// 再開
			Arrow.SetPos(350, 210);
			if (IsKeyTrigger(VK_RETURN)) m_bPause = false;
			break;
		case PAUSE_RETRY:	// やり直し
			Arrow.SetPos(370, 290);
			if (IsKeyTrigger(VK_RETURN))
			{
				m_Result = GAME_RESULT::RESTART;
				return true;
			}
			break;
		case PAUSE_END:		// 終了
			Arrow.SetPos(390, 370);
			if (IsKeyTrigger(VK_RETURN))
			{
				m_Result = GAME_RESULT::BREAK;
				return true;
			}
				break;
		default:
			break;
		}

		return false;
	}

	// 背景の更新
	m_pBG->Update();

	// GUIの更新
	m_pGUI->Update();

	// カメラの更新
	GetCamera()->Update();

	//--- ステージの更新
	STAGE_RESULT StageResult = m_pStage->Update();
	// ステージ結果
	if ((StageResult != STAGE_RESULT::NO)
		&& (m_Result == GAME_RESULT::NO))
	{
		switch (StageResult)
		{
		// クリア
		case STAGE_RESULT::CLEAR:
			m_Result = GAME_RESULT::CLEAR;
			m_nResultTime = 100;
			break;

		// 失敗
		case STAGE_RESULT::MISS:
			m_Result = GAME_RESULT::MISS;
			m_nResultTime = 100;
			break;

		default:
			break;
		}
	}

	// 強制クリア
	//if (IsKeyTrigger('Z'))
	//{
	//	m_Result = GAME_RESULT::CLEAR;
	//	return true;
	//}

	// ポーズ
	if (IsKeyTrigger('Q'))
	{
		m_bPause = true;
	}

	return false;
}

//--- 描画
void GameScene::Draw()
{
	// 背景の描画
	m_pBG->Draw();

	// ステージの描画
	m_pStage->Draw();

	// GUIの描画
	if (m_Result == GAME_RESULT::NO) m_pGUI->Draw();

	// ポーズ画面の描画
	if (m_bPause)
	{
		//フェードの描画
		Fade.Draw();

		// テキストの描画
		Pause.Draw();
		Resume.Draw();
		Retry.Draw();
		End.Draw();

		// 矢印の描画
		Arrow.Draw();

		return;
	}
}

// ゲーム結果を返す
GAME_RESULT GameScene::GetResult()
{
	return m_Result;
}
