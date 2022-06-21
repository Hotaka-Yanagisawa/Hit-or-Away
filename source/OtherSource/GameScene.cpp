///////////////////////////////////////////
// GameScene.cpp
//-----------------------------------------
// 2020/08/05	�^�C�g�����R�s�[���č쐬
//		08/06	���j���[���
//		08/
//
///////////////////////////////////////////

//--- �C���N���[�h��
#include "GameScene.h"
#include "TitleScene.h"
#include "Keyboard.h"

//--- �O���[�o���ϐ�
GAME_RESULT GameScene::m_Result;

//--- ������
void GameScene::Init()
{
	// �w�i
	m_pBG = new CBackGround();

	// �t�F�[�h�̏�����
	Fade.SetImage(NULL);
	Fade.SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Fade.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	Fade.SetColor(0, 0, 0, 0.5f);
	//--- �摜�̏�����
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
	// ���
	Arrow.SetImage("Image/Cursor.png");
	Arrow.SetSplit(3, 3);
	Arrow.SetAnime(0, 1, 3, 8);
	Arrow.SetPos(360, 210);
	Arrow.SetSize(50, 50);

	// �X�e�[�W�̏�����	
	m_pStage = new CStage();
	m_pStage->Init(TitleScene::GetSelectStage());

	// �J�����̏�����
	GetCamera()->Init();
	GetCamera()->Update();

	// GUI
	m_pGUI = new GUI();
	m_pGUI->Init();

	m_Menu = PAUSE_RESUME;
	m_bPause = false;
	m_Result = GAME_RESULT::NO;
	m_nResultTime = 0;

	//�T�E���h�̏�����
	sound.m_pBuffer = sound.CreateSound("sound/cursor10.mp3", false);
}

//--- �I��
void GameScene::Uninit()
{
	// GUI�̏I��
	m_pGUI->Uninit();
	delete m_pGUI;

	// �J�����̏I��
	GetCamera()->Uninit();

	// �X�e�[�W�̏I��
	m_pStage->Uninit();
	delete m_pStage;

	// �w�i�̏I��
	delete m_pBG;
}

//--- �X�V
bool GameScene::Update()
{
	// ���U���g��ʂ̍X�V
	if (m_nResultTime > 0)
	{
		// �J�E���g�_�E��
		m_nResultTime--;



		// �Q�[���I��
		if (m_nResultTime == 0) return true;
	}

	// �|�[�Y��ʂ̍X�V
	if (m_bPause)
	{
		// ���̍X�V
		Arrow.Update();

		// �L�����Z��
		if (IsKeyTrigger('Q'))
		{
			m_bPause = false;
		}

		// �J�[�\���ړ�
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

		//Fade���Ă΂ꂽ��@�\����
		sound.Update();

		// �|�[�Y��ʑI��
		switch (m_Menu)
		{
		case PAUSE_RESUME:	// �ĊJ
			Arrow.SetPos(350, 210);
			if (IsKeyTrigger(VK_RETURN)) m_bPause = false;
			break;
		case PAUSE_RETRY:	// ��蒼��
			Arrow.SetPos(370, 290);
			if (IsKeyTrigger(VK_RETURN))
			{
				m_Result = GAME_RESULT::RESTART;
				return true;
			}
			break;
		case PAUSE_END:		// �I��
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

	// �w�i�̍X�V
	m_pBG->Update();

	// GUI�̍X�V
	m_pGUI->Update();

	// �J�����̍X�V
	GetCamera()->Update();

	//--- �X�e�[�W�̍X�V
	STAGE_RESULT StageResult = m_pStage->Update();
	// �X�e�[�W����
	if ((StageResult != STAGE_RESULT::NO)
		&& (m_Result == GAME_RESULT::NO))
	{
		switch (StageResult)
		{
		// �N���A
		case STAGE_RESULT::CLEAR:
			m_Result = GAME_RESULT::CLEAR;
			m_nResultTime = 100;
			break;

		// ���s
		case STAGE_RESULT::MISS:
			m_Result = GAME_RESULT::MISS;
			m_nResultTime = 100;
			break;

		default:
			break;
		}
	}

	// �����N���A
	//if (IsKeyTrigger('Z'))
	//{
	//	m_Result = GAME_RESULT::CLEAR;
	//	return true;
	//}

	// �|�[�Y
	if (IsKeyTrigger('Q'))
	{
		m_bPause = true;
	}

	return false;
}

//--- �`��
void GameScene::Draw()
{
	// �w�i�̕`��
	m_pBG->Draw();

	// �X�e�[�W�̕`��
	m_pStage->Draw();

	// GUI�̕`��
	if (m_Result == GAME_RESULT::NO) m_pGUI->Draw();

	// �|�[�Y��ʂ̕`��
	if (m_bPause)
	{
		//�t�F�[�h�̕`��
		Fade.Draw();

		// �e�L�X�g�̕`��
		Pause.Draw();
		Resume.Draw();
		Retry.Draw();
		End.Draw();

		// ���̕`��
		Arrow.Draw();

		return;
	}
}

// �Q�[�����ʂ�Ԃ�
GAME_RESULT GameScene::GetResult()
{
	return m_Result;
}
