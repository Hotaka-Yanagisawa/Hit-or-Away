///////////////////////////////////////////
// TitleScene.cpp
//-----------------------------------------
// 2020/07/17	�쐬
//		07/23	�^�C�g���p�̉摜�i���j
//		08/02	�O���[�o���ϐ��ǉ��@����
//		08/03	Stage.h
//
///////////////////////////////////////////

//--- �C���N���[�h��
#include "TitleScene.h"
#include "Polygon.h"
#include "Keyboard.h"
#include "Stage.h"
#include "GameScene.h"

//--- �O���[�o���ϐ�
STAGE_ID TitleScene::m_SelectStage;

//--- �R���X�g���N�^
TitleScene::TitleScene()
{
	// �X�e�[�^�X�̏�����
	m_bSelect = false;
	m_nTime = 0;
	m_bUpDown = false;
	m_SelectStage = STAGE_ID::P_MOVE;
	m_maxSelectable = (int)STAGE_ID::MAX;
}

//--- ������
void TitleScene::Init()
{
	m_TitlePolygon.Init();
	m_SelectPolygon.Init();
	m_StageImage.Init();
	m_TipsList.Init();

	m_nTime = 0;
	m_bUpDown = false;

	//--- �摜�̏�����
	// �w�i
	Back = new CPolygon();
	Back->SetImage("Image/TitleBack.png");
	Back->SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Back->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	// ���S
	Title = new CPolygon();
	Title->SetImage("Image/Logo.png");
	Title->SetPos(200, 80);
	Title->SetSize(320, 256);
	// Start
	Start = new CPolygon();
	Start->SetImage("Image/Start.png");
	Start->SetSplit(1, 2);
	Start->SetUV(0, 0);
	Start->SetPos(350, 480);
	Start->SetSize(150, 75);
	// SelectStage
	Select = new CPolygon();
	Select->SetImage("Image/Text.png");
	Select->SetSplit(1, 7);
	Select->SetUV(0, 1);
	Select->SetPos(350, 190);
	Select->SetSize(340, 70);
	// �J�[�\��
	Cursor = new CAnime();
	Cursor->SetImage("Image/Cursor.png");
	Cursor->SetSplit(3, 3);
	Cursor->SetAnime(0, 0, 3, 7);
	Cursor->SetPos(350, 220);
	Cursor->SetSize(50, 50);
	// ���
	LAllow = new CAnime();
	RAllow = new CAnime();
	LAllow->SetImage("Image/Cursor.png");
	LAllow->SetSplit(3, 3);
	LAllow->SetSize(50, 50);
	*RAllow = *LAllow;
	LAllow->SetAnime(0, 2, 3, 10);
	RAllow->SetAnime(0, 1, 3, 10);
	LAllow->SetPos(200, 320);
	RAllow->SetPos(500, 320);
	// ��
	Unlock = new CPolygon();
	Unlock->SetImage("Image/Unlocked.png");
	Unlock->SetPos(550, 330);
	Unlock->SetSize(180, 120);
	Unlock->Show(false);
	// ���X�g�ɒǉ�
	m_SelectPolygon.Add(Cursor);
	m_SelectPolygon.Add(LAllow);
	m_SelectPolygon.Add(RAllow);
	m_SelectPolygon.Add(Start);
	m_SelectPolygon.Add(Select);

	// Rela
	Rela = new CPolygon();
	Rela->SetImage("Image/Relation.png");
	Rela->SetSplit(7, 1);
	Rela->SetPos(800,170);
	Rela->SetSize(200, 120);
	// Talk
	Talk = new CPolygon();
	Talk->SetImage("Image/Talk.png");
	Talk->SetSplit(2, 1);
	Talk->SetPos(800, 330);
	Talk->SetSize(150, 90);
	// Message
	Message = new CPolygon();
	Message->SetImage("Image/Message.png");
	Message->SetPos(800, 360);
	Message->SetSize(190, 190);
	// King
	King = new CAnime();
	King->SetImage("Image/King.png");
	King->SetSplit(2, 1);
	King->SetPos(750, 480);
	King->SetSize(100, 100);
	King->SetAnime(0, 0, 2, 6);
	King->Play(false);
	// Tips
	Tips = new CPolygon();
	Tips->SetImage("Image/Tips.png");
	Tips->SetPos(800, 150);
	Tips->SetSize(270, 240);
	// ���X�g�ɒǉ�
	m_TipsList.Add(Rela);
	m_TipsList.Add(Talk);
	m_TipsList.Add(Message);
	m_TipsList.Add(King);
	m_TipsList.Add(Tips);

	// �X�e�[�W�̃C���[�W
	CPolygon* SI[3];
	for (int i = 0; i < 3; i++)
	{
		SI[i] = new CPolygon();
		SI[i]->SetImage("Image/StageImage.png");
		SI[i]->SetSplit(4, 5);
		SI[i]->SetPos(150 + i * 200, 330);
		if (i == 1) SI[i]->SetSize(240, 160);
		else
		{
			SI[i]->SetSize(180, 120);
			SI[i]->SetColor(0.7f, 0.7f, 0.7f, 1);
		}

		m_StageImage.Add(SI[i]);
	}

	// �^�C�g����ʂ̂�
	if (!m_bSelect)
	{
		m_nCount = 0;
		// ���S
		Title->SetPos(460, 180);
		// PushEnter
		PushEnter = new CPolygon();
		PushEnter->SetImage("Image/Text.png");
		PushEnter->SetSplit(1, 7);
		PushEnter->SetUV(0, 0);
		PushEnter->SetPos(480, 400);
		PushEnter->SetSize(180, 52);
		PushEnter->SetColor(1, 1, 1, 1);
		// ���X�g�ɒǉ�
		m_TitlePolygon.Add(PushEnter);
		// ������
		Start->SetColor(1, 1, 1, 0);
		Select->SetColor(1, 1, 1, 0);
		Cursor->SetColor(1, 1, 1, 0);
		LAllow->SetColor(1, 1, 1, 0);
		RAllow->SetColor(1, 1, 1, 0);
		Unlock->SetColor(1, 1, 1, 0);
		for (int i = 0; i < 3; i++)
			SI[i]->SetColor(0, 0, 0, -1, true);
	}
	// �Q�[������߂��Ă���
	else
	{
		// �X�e�[�W�N���A��
		if ((GameScene::GetResult() == GAME_RESULT::CLEAR)
			&& ((int)m_SelectStage == m_maxSelectable - 1))
		{
			// �ő�X�e�[�W��
			if (m_maxSelectable < (int)STAGE_ID::MAX)
				m_maxSelectable++;
		}
	}
	//��
	sound.m_pSpeaker = NULL;
}

//--- �I��
void TitleScene::Uninit()
{
	// ���X�g����
	m_TitlePolygon.Uninit();
	m_SelectPolygon.Uninit();
	m_StageImage.Uninit();
	m_TipsList.Uninit();

	delete Back;
}

//--- �X�V
bool TitleScene::Update()
{
	POLYGON_LIST* SIList;

	// �J�ڎ��̍X�V
	if(m_nTime > 0)
	{
		m_nTime--;

		Title->SetPos(-3, -1, true);
		Select->SetColor(0, 0, 0, 0.01f, true);
		Start->SetColor(0, 0, 0, 0.01f, true);
		Cursor->SetColor(0, 0, 0, 0.01f, true);
		LAllow->SetColor(0, 0, 0, 0.01f, true);
		RAllow->SetColor(0, 0, 0, 0.01f, true);
		Unlock->SetColor(0, 0, 0, 0.01f, true);
		for (SIList = m_StageImage.GetList(); SIList != NULL; SIList = SIList->Next)
		{
			SIList->Data->SetColor(0, 0, 0, 0.01f, true);			
		}
	}

	// �^�C�g��
	if (!m_bSelect)
	{
		m_TitlePolygon.Update();

		if (m_nCount < 30) m_nCount++;
		else m_nCount = 0;

		if (IsKeyTrigger(VK_RETURN))
		{
			sound.m_pBuffer = sound.CreateSound("sound/decision7.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			// �Z���N�g��ʂ�
			m_TitlePolygon.Uninit();
			m_bSelect = true;
			m_nTime = 100;
		}
	}
	// �X�e�[�W�Z���N�g
	else
	{
		// �L���O�g�[�N
		if (m_nKingTalk > 0)
		{
			m_nKingTalk--;
			King->Play();
		}
		else King->Play(false);
		// �X�e�[�W�摜�̍X�V
		int i;
		for (SIList = m_StageImage.GetList(), i = 0; i < 3; SIList = SIList->Next, i++)
		{
			SIList->Data->SetUV(((int)m_SelectStage + (1 - i)) % 4,
				((int)m_SelectStage + 1 - i) / 4);
		}
		// Tips�̍X�V
		if ((int)m_SelectStage < 6) Rela->SetUV((int)m_SelectStage, 0);
		else Rela->SetUV(6, 0);
		// �Z���t�̍X�V
		if ((int)m_SelectStage % 3 == 0) Talk->SetUV((int)0, 0);
		else Talk->SetUV(1, 0);

		// �^�C�g���ɖ߂�
		if (IsKeyTrigger(VK_BACK))
		{
			m_SelectPolygon.Uninit();
			m_bSelect = false;
			m_bUpDown = false;
			Init();
			return false;
		}

		// �J�[�\���㉺
		if (IsKeyTrigger(VK_UP))
		{
			sound.m_pBuffer = sound.CreateSound("sound/cursor10.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			Cursor->SetPos(350, 220);
			m_bUpDown = false;
		}
		if (IsKeyTrigger(VK_DOWN))
		{
			sound.m_pBuffer = sound.CreateSound("sound/cursor10.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			Cursor->SetPos(350, 430);
			m_bUpDown = true;
		}

		// �X�e�[�W�I��
		if ((IsKeyTrigger(VK_LEFT)) && (!m_bUpDown))
		{
			if (m_SelectStage > STAGE_ID::P_MOVE)
			{
				sound.m_pBuffer = sound.CreateSound("sound/cursor10.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
				m_SelectStage = (STAGE_ID)((int)m_SelectStage - 1);
				m_nKingTalk = 20;
			}
			else
			{
				sound.m_pBuffer = sound.CreateSound("sound/cancel2.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			}
		}
		if ((IsKeyTrigger(VK_RIGHT)) && (!m_bUpDown))
		{
			if ((int)m_SelectStage < (int)m_maxSelectable - 1)
			{
				sound.m_pBuffer = sound.CreateSound("sound/cursor10.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
				m_SelectStage = (STAGE_ID)((int)m_SelectStage + 1);
				m_nKingTalk = 20;
			}
			else
			{
				sound.m_pBuffer = sound.CreateSound("sound/cancel2.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			}
		}
		// ��
		if (((int)m_SelectStage == m_maxSelectable - 1)
			&& ((int)m_SelectStage != (int)STAGE_ID::MAX - 1)) Unlock->Show();
		else Unlock->Show(false);

		// ����(Enter)
		if (IsKeyTrigger(VK_RETURN))
		{
			if (!m_bUpDown)
			{
				sound.m_pBuffer = sound.CreateSound("sound/decision26.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
				Cursor->SetPos(350, 430);
				m_bUpDown = true;
			}
			// �Q�[���J�n
			else
			{
				sound.m_pBuffer = sound.CreateSound("sound/decision8.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
				Start->SetUV(0, 1);

				return true;
			}
		}

		m_SelectPolygon.Update();
		m_TipsList.Update();
	}

	return false;
}

void TitleScene::Draw()
{
	Back->Draw();
	Title->Draw();
	// �^�C�g��
	if (!m_bSelect)
	{
		if (m_nCount < 15)	// �`�J�`�J����
			m_TitlePolygon.Draw();
	}
	// �X�e�[�W�Z���N�g
	else
	{
		Unlock->Draw();
		// �X�e�[�W�摜
		POLYGON_LIST* SIList = m_StageImage.GetList();
		int i;
		for (SIList = m_StageImage.GetList(), i = 0; i < 3; SIList = SIList->Next, i++)
		{
			if (i == 0)
				if ((int)m_SelectStage == (int)m_maxSelectable - 1) SIList->Data->Show(false);
				else SIList->Data->Show();
			if (i == 2)
				if (m_SelectStage == STAGE_ID::P_MOVE) SIList->Data->Show(false);
				else SIList->Data->Show();
			SIList->Data->Draw();
		}
		// ���
		if (m_SelectStage == STAGE_ID::P_MOVE) LAllow->SetPos(-99, -99);
		else LAllow->SetPos(180, 320);
		if ((int)m_SelectStage == (int)m_maxSelectable - 1)	RAllow->SetPos(-99, -99);
		else RAllow->SetPos(520, 320);
		m_SelectPolygon.Draw();
		if (m_SelectStage != STAGE_ID::BOSS)        //�� �ύX�ӏ�
			m_TipsList.Draw();
	}
}


//--- �I�����ꂽ�X�e�[�W�̎擾
STAGE_ID TitleScene::GetSelectStage()
{
	return m_SelectStage;
}
