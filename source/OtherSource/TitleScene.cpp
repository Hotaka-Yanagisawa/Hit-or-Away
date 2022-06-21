///////////////////////////////////////////
// TitleScene.cpp
//-----------------------------------------
// 2020/07/17	作成
//		07/23	タイトル用の画像（仮）
//		08/02	グローバル変数追加　微妙
//		08/03	Stage.h
//
///////////////////////////////////////////

//--- インクルード部
#include "TitleScene.h"
#include "Polygon.h"
#include "Keyboard.h"
#include "Stage.h"
#include "GameScene.h"

//--- グローバル変数
STAGE_ID TitleScene::m_SelectStage;

//--- コンストラクタ
TitleScene::TitleScene()
{
	// ステータスの初期化
	m_bSelect = false;
	m_nTime = 0;
	m_bUpDown = false;
	m_SelectStage = STAGE_ID::P_MOVE;
	m_maxSelectable = (int)STAGE_ID::MAX;
}

//--- 初期化
void TitleScene::Init()
{
	m_TitlePolygon.Init();
	m_SelectPolygon.Init();
	m_StageImage.Init();
	m_TipsList.Init();

	m_nTime = 0;
	m_bUpDown = false;

	//--- 画像の初期化
	// 背景
	Back = new CPolygon();
	Back->SetImage("Image/TitleBack.png");
	Back->SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Back->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	// ロゴ
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
	// カーソル
	Cursor = new CAnime();
	Cursor->SetImage("Image/Cursor.png");
	Cursor->SetSplit(3, 3);
	Cursor->SetAnime(0, 0, 3, 7);
	Cursor->SetPos(350, 220);
	Cursor->SetSize(50, 50);
	// 矢印
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
	// 鍵
	Unlock = new CPolygon();
	Unlock->SetImage("Image/Unlocked.png");
	Unlock->SetPos(550, 330);
	Unlock->SetSize(180, 120);
	Unlock->Show(false);
	// リストに追加
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
	// リストに追加
	m_TipsList.Add(Rela);
	m_TipsList.Add(Talk);
	m_TipsList.Add(Message);
	m_TipsList.Add(King);
	m_TipsList.Add(Tips);

	// ステージのイメージ
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

	// タイトル画面のみ
	if (!m_bSelect)
	{
		m_nCount = 0;
		// ロゴ
		Title->SetPos(460, 180);
		// PushEnter
		PushEnter = new CPolygon();
		PushEnter->SetImage("Image/Text.png");
		PushEnter->SetSplit(1, 7);
		PushEnter->SetUV(0, 0);
		PushEnter->SetPos(480, 400);
		PushEnter->SetSize(180, 52);
		PushEnter->SetColor(1, 1, 1, 1);
		// リストに追加
		m_TitlePolygon.Add(PushEnter);
		// 透明化
		Start->SetColor(1, 1, 1, 0);
		Select->SetColor(1, 1, 1, 0);
		Cursor->SetColor(1, 1, 1, 0);
		LAllow->SetColor(1, 1, 1, 0);
		RAllow->SetColor(1, 1, 1, 0);
		Unlock->SetColor(1, 1, 1, 0);
		for (int i = 0; i < 3; i++)
			SI[i]->SetColor(0, 0, 0, -1, true);
	}
	// ゲームから戻ってきた
	else
	{
		// ステージクリア後
		if ((GameScene::GetResult() == GAME_RESULT::CLEAR)
			&& ((int)m_SelectStage == m_maxSelectable - 1))
		{
			// 最大ステージ数
			if (m_maxSelectable < (int)STAGE_ID::MAX)
				m_maxSelectable++;
		}
	}
	//音
	sound.m_pSpeaker = NULL;
}

//--- 終了
void TitleScene::Uninit()
{
	// リスト消去
	m_TitlePolygon.Uninit();
	m_SelectPolygon.Uninit();
	m_StageImage.Uninit();
	m_TipsList.Uninit();

	delete Back;
}

//--- 更新
bool TitleScene::Update()
{
	POLYGON_LIST* SIList;

	// 遷移時の更新
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

	// タイトル
	if (!m_bSelect)
	{
		m_TitlePolygon.Update();

		if (m_nCount < 30) m_nCount++;
		else m_nCount = 0;

		if (IsKeyTrigger(VK_RETURN))
		{
			sound.m_pBuffer = sound.CreateSound("sound/decision7.mp3", false);
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			// セレクト画面へ
			m_TitlePolygon.Uninit();
			m_bSelect = true;
			m_nTime = 100;
		}
	}
	// ステージセレクト
	else
	{
		// キングトーク
		if (m_nKingTalk > 0)
		{
			m_nKingTalk--;
			King->Play();
		}
		else King->Play(false);
		// ステージ画像の更新
		int i;
		for (SIList = m_StageImage.GetList(), i = 0; i < 3; SIList = SIList->Next, i++)
		{
			SIList->Data->SetUV(((int)m_SelectStage + (1 - i)) % 4,
				((int)m_SelectStage + 1 - i) / 4);
		}
		// Tipsの更新
		if ((int)m_SelectStage < 6) Rela->SetUV((int)m_SelectStage, 0);
		else Rela->SetUV(6, 0);
		// セリフの更新
		if ((int)m_SelectStage % 3 == 0) Talk->SetUV((int)0, 0);
		else Talk->SetUV(1, 0);

		// タイトルに戻る
		if (IsKeyTrigger(VK_BACK))
		{
			m_SelectPolygon.Uninit();
			m_bSelect = false;
			m_bUpDown = false;
			Init();
			return false;
		}

		// カーソル上下
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

		// ステージ選択
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
		// 鍵
		if (((int)m_SelectStage == m_maxSelectable - 1)
			&& ((int)m_SelectStage != (int)STAGE_ID::MAX - 1)) Unlock->Show();
		else Unlock->Show(false);

		// 決定(Enter)
		if (IsKeyTrigger(VK_RETURN))
		{
			if (!m_bUpDown)
			{
				sound.m_pBuffer = sound.CreateSound("sound/decision26.mp3", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
				Cursor->SetPos(350, 430);
				m_bUpDown = true;
			}
			// ゲーム開始
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
	// タイトル
	if (!m_bSelect)
	{
		if (m_nCount < 15)	// チカチカ処理
			m_TitlePolygon.Draw();
	}
	// ステージセレクト
	else
	{
		Unlock->Draw();
		// ステージ画像
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
		// 矢印
		if (m_SelectStage == STAGE_ID::P_MOVE) LAllow->SetPos(-99, -99);
		else LAllow->SetPos(180, 320);
		if ((int)m_SelectStage == (int)m_maxSelectable - 1)	RAllow->SetPos(-99, -99);
		else RAllow->SetPos(520, 320);
		m_SelectPolygon.Draw();
		if (m_SelectStage != STAGE_ID::BOSS)        //← 変更箇所
			m_TipsList.Draw();
	}
}


//--- 選択されたステージの取得
STAGE_ID TitleScene::GetSelectStage()
{
	return m_SelectStage;
}
