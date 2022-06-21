////////////////////////////////////////
// GUI.cpp
//--------------------------------------
// 2020/09/26	作成
//
////////////////////////////////////////

//--- インクルード部
#include "GUI.h"
#include "Player.h"
#include "Enemy.h"

//--- 初期化
void GUI::Init()
{
	m_bTutorial = true;

	// リンゴ
	m_Apple = new CPolygonList();
	m_Apple->Init();
	CPolygon* Apple[MAX_AP];
	for (int i = 0; i < MAX_AP; i++)
	{
		Apple[i] = new CPolygon();
		Apple[i]->SetSize(40, 40);
		Apple[i]->SetPos(110 - i * 40.0f, 40);
		Apple[i]->SetImage("Image/Badge.png");
		Apple[i]->SetSplit(2, 1);
		Apple[i]->SetColor(1, 1, 1, 0.9f);
		Apple[i]->Show(false);

		m_Apple->Add(Apple[i]);
	}

	// キラキラ
	m_Shine = new CAnime();
	m_Shine->SetSize(100, 100);
	m_Shine->SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	m_Shine->SetImage("Image/Shine.png");
	m_Shine->SetSplit(4, 1);
	m_Shine->SetAnime(0, 0, 4, 7);
	m_Shine->SetColor(1, 1, 1, 0.9f);
	m_Shine->Show(false);
	m_Shine->Play(false);

	//--- ボタン指示
	if (m_bTutorial)
	{
		// A
		m_Push = new CAnime();
		m_Push->SetSize(30, 30);
		m_Push->SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 70);
		m_Push->SetImage("Image/Push.png");
		m_Push->SetSplit(4, 1);
		m_Push->SetAnime(0, 0, 4, 7);
		m_Push->SetColor(1, 1, 1, 0.8f);
		m_Push->Show(false);
		m_Push->Play(false);
	}
}

//--- 終了
void GUI::Uninit()
{
	m_Apple->Uninit();
	delete m_Apple;
	delete m_Shine;

	if (m_bTutorial)
		delete m_Push;
}

//--- 更新
void GUI::Update()
{
	//--- プレイヤーの状態
	// リンゴ
	int AppleNum = CPlayer::GetSpecial();
	int i;
	POLYGON_LIST* pApple;
	for (i = 0, pApple = m_Apple->GetList(); i < MAX_AP; i++, pApple = pApple->Next)
	{
		if(i < AppleNum) pApple->Data->Show();
		else pApple->Data->Show(false);
	}
	// キラキラ
	if (AppleNum > 0) {
		m_Shine->Show();
		m_Shine->Play();
		//m_Shine->SetAnime(0, 0, 10 - AppleNum * 2, 7);
	}
	else {
		m_Shine->Show(false);
		m_Shine->Play(false);
	}

	//--- 指示
	if (m_bTutorial)
	{
		// ボタン
		if (CPlayer::GetCanAtk()) {
			m_Push->Show();
			m_Push->Play();
		}
		else {
			m_Push->Show(false);
			m_Push->Play(false);
		}
	}

	m_Apple->Update();
	m_Shine->Update();

	if (m_bTutorial)
		m_Push->Update();
}

//--- 描画
void GUI::Draw()
{
	m_Apple->Draw();
	m_Shine->Draw();

	if (m_bTutorial)
		m_Push->Draw();
}

