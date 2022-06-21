///////////////////////////////////////
// SceneMgr.cpp
//-------------------------------------
// 2020/07/28	作成
//
///////////////////////////////////////

//--- インクルード部
#include "SceneMgr.h"


//--- ゲーム開始時の初期化
void SceneManager::SetStartScene()
{
	// シーンの初期化
	m_title = new TitleScene();
	m_game = new GameScene();
	m_scene = SCENE_TITLE;
	m_nextScene = SCENE_MAX;
	m_fade.Init();

	// ゲーム画面が立ち上がった時用のフェードイン
	m_fade.Start(2, false);
}

//--- 各シーンの初期化
HRESULT SceneManager::Init()
{
	HRESULT hr = E_FAIL;
	
	switch (m_scene)
	{
	case SCENE_TITLE:
		sound.m_pBuffer = sound.CreateSound("sound/Title Theme.wav", true);
		sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer);
		sound.m_pSpeaker->SetVolume(0.0f);
		sound.m_bFade = false;
		sound.m_bFade = sound.Fade(0.1f, 0.1f);
		m_title->Init();

		break;

	case SCENE_GAME:
		
		sound.m_pBuffer = sound.CreateSound("sound/Fields of Ice.wav", true);
		sound.m_pBuffer->PlayBegin = 12800 * 78;
		sound.m_pBuffer->LoopBegin = 12800 * 78;
		sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer);
		sound.m_pSpeaker->SetVolume(0.0f);
		
		sound.m_bFade = false;
		sound.m_bFade = sound.Fade(0.1f, 0.1f);

		m_game->Init();

		break;

	default:
		break;
	}

	return hr;
}

//--- 各シーンの終了
void SceneManager::Uninit()
{

	XAUDIO2_VOICE_STATE state;
	//ソースボイスの状況を取得
	sound.m_pSpeaker->GetState(&state);
	//なってる音が一つ以上かつフェードしてなかったらストップ
	if (state.BuffersQueued > 0 && !sound.m_bFade)
	{
		sound.m_pSpeaker->Stop();
	}

	switch (m_scene)
	{
	case SCENE_TITLE:

		m_title->Uninit();

		break;

	case SCENE_GAME:

		m_game->Uninit();

		break;

	default:
		break;
	}
}

//--- 更新
void SceneManager::Update()
{
	m_fade.Update();

	//Fadeが呼ばれたら機能する
	sound.Update();

	// フェードが完了したらシーンを更新する
	if (m_fade.IsFinish())
	{
		// シーンを更新
		if (m_nextScene != SCENE_MAX)
		{
			Uninit();

			m_scene = m_nextScene;
			m_nextScene = SCENE_MAX;

			Init();

			// フェードイン
			m_fade.Start(0.5f, false);
		}

		// 実際のゲーム処理
		switch (m_scene)
		{
		case SCENE_TITLE:

			if (m_title->Update())
			{
				// フェードアウトの開始
				m_fade.Start(0.5f, true);
				sound.m_bFade = sound.Fade(0.0f, 0.01f);

				// ゲームシーンへ
				m_nextScene = SCENE_GAME;
			}

			break;

		case SCENE_GAME:

			if(m_game->Update())
			{
				switch (GameScene::GetResult())
				{
				case GAME_RESULT::BREAK:
					m_fade.Start(0.5f, true);
					m_nextScene = SCENE_TITLE;
					break;

				case GAME_RESULT::MISS:
					m_fade.Start(0.5f, true);
					m_nextScene = SCENE_TITLE;
					break;

				case GAME_RESULT::CLEAR:
					m_fade.Start(6.0f, true);
					m_nextScene = SCENE_TITLE;
					break;

				case GAME_RESULT::RESTART:
					m_fade.Start(0.5f, true);
					m_nextScene = SCENE_GAME;
					break;
				default:
					break;
				}
				// フェードアウトの開始
				
				sound.m_bFade = sound.Fade(0.0f, 0.01f);
			}

			break;

		default:
			break;
		}
	}
}

//--- 描画
void SceneManager::Draw()
{
	switch (m_scene)
	{
	case SCENE_TITLE:

		m_title->Draw();

		break;

	case SCENE_GAME:

		m_game->Draw();

		break;

	default:
		break;
	}

	// フェード
	m_fade.Draw();
}

