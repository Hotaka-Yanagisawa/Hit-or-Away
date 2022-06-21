///////////////////////////////////////
// SceneMgr.cpp
//-------------------------------------
// 2020/07/28	�쐬
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "SceneMgr.h"


//--- �Q�[���J�n���̏�����
void SceneManager::SetStartScene()
{
	// �V�[���̏�����
	m_title = new TitleScene();
	m_game = new GameScene();
	m_scene = SCENE_TITLE;
	m_nextScene = SCENE_MAX;
	m_fade.Init();

	// �Q�[����ʂ������オ�������p�̃t�F�[�h�C��
	m_fade.Start(2, false);
}

//--- �e�V�[���̏�����
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

//--- �e�V�[���̏I��
void SceneManager::Uninit()
{

	XAUDIO2_VOICE_STATE state;
	//�\�[�X�{�C�X�̏󋵂��擾
	sound.m_pSpeaker->GetState(&state);
	//�Ȃ��Ă鉹����ȏォ�t�F�[�h���ĂȂ�������X�g�b�v
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

//--- �X�V
void SceneManager::Update()
{
	m_fade.Update();

	//Fade���Ă΂ꂽ��@�\����
	sound.Update();

	// �t�F�[�h������������V�[�����X�V����
	if (m_fade.IsFinish())
	{
		// �V�[�����X�V
		if (m_nextScene != SCENE_MAX)
		{
			Uninit();

			m_scene = m_nextScene;
			m_nextScene = SCENE_MAX;

			Init();

			// �t�F�[�h�C��
			m_fade.Start(0.5f, false);
		}

		// ���ۂ̃Q�[������
		switch (m_scene)
		{
		case SCENE_TITLE:

			if (m_title->Update())
			{
				// �t�F�[�h�A�E�g�̊J�n
				m_fade.Start(0.5f, true);
				sound.m_bFade = sound.Fade(0.0f, 0.01f);

				// �Q�[���V�[����
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
				// �t�F�[�h�A�E�g�̊J�n
				
				sound.m_bFade = sound.Fade(0.0f, 0.01f);
			}

			break;

		default:
			break;
		}
	}
}

//--- �`��
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

	// �t�F�[�h
	m_fade.Draw();
}

