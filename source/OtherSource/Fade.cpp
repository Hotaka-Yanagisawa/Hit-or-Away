
//--- インクルード部
#include "Fade.h"
#include "Game.h"

//--- 初期化
HRESULT Fade::Init()
{
	m_isOut = false;
	m_maxTime = 0.0f;
	m_time = 0.0f;
	return S_OK;
}

//--- 終了
void Fade::Uninit()
{

}

//--- 更新
void Fade::Update()
{
	// 経過時間の計測
	if (m_maxTime > m_time)
	{
		// 60FPS換算
		m_time += 1.0f / 60;
	}
}

//--- 描画
void Fade::Draw()
{
	//--- 透過色の計算
	// 全体の実行時間を1としたときの経過時間の割合
	float rate = 1.0f;
	if (m_maxTime != 0.0f)
	{
		// フェードが完了すると0割が発生するのでエラー対処
		rate = m_time / m_maxTime;
	}
	// 透過色
	float alpha = rate;
	if(!m_isOut)
	{
		alpha = 1 - alpha;
	}

	// フェード用のポリゴンの透過設定
	SetColor(0, 0, 0, alpha);
	// フェード用のポリゴン描画
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SetImage(NULL);
	CPolygon::Draw();
	// 通常の色設定に戻す
	SetColor(1, 1, 1, 1);

}

// フェード完了判定
bool Fade::IsFinish()
{
	return m_maxTime <= m_time;
}

// フェード実行判定
bool Fade::IsExecute()
{
	return m_maxTime > 0.0f;
}

// フェード開始
void Fade::Start(float time, bool isOut)
{
	m_time = 0;
	m_maxTime = time;
	m_isOut = isOut;
}

