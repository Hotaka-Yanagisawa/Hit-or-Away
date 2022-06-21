///////////////////////////////////////
// Anime.cpp
//-------------------------------------
// 2020/09/03	作成
//
///////////////////////////////////////

//--- インクルード部
#include "Anime.h"

//--- 更新
void CAnime::Update()
{
	//--- アニメの更新
	// 再生されている
	if (m_Status == ANIM_STATUS::PLAY)
	{
		// カウント
		m_nCount++;
		// 一定時間経過したらテクスチャを切り替える
		if (m_nCount > m_nPace)
		{
			// アニメが一周した
			if ((m_TexCoord.x == m_End.x)
				&& (m_TexCoord.y == m_End.y))
			{
				if (m_bLoop)	// アニメの先頭に戻る
				{
					m_TexCoord.x = (float)m_Start.x;
					m_TexCoord.y = (float)m_Start.y;
				}
				else			// ループを終わる
				{
					m_Status = ANIM_STATUS::END;
				}

				// 以下の処理をしない
				m_nCount = 0;
				return;
			}

			// 次のテクスチャ
			m_TexCoord.x++;

			// 端までいったら列を変える
			if (m_TexCoord.x >= m_Split.x)
			{
				m_TexCoord.x = 0.0f;
				m_TexCoord.y += 1.0f;
			}
			// 終端までいったら最初に戻る
			if (m_TexCoord.y >= m_Split.y)
				m_TexCoord.y = 0.0f;

			// アニメカウントリセット
			m_nCount = 0;
		}
	}

	// ポリゴンの更新
	CPolygon::Update();
}

//--- 描画
void CAnime::Draw()
{
	// ポリゴンの描画
	CPolygon::Draw();
}

//--- アニメ設定
void CAnime::SetAnime(int StartX, int StartY, int Num, int Pace, bool Loop)
{
	if (m_Status == ANIM_STATUS::PLAY) return;

	m_Start = { StartX, StartY };	// 開始位置
	// 終了位置を計算
	int EndX = (StartX + (Num - 1)) % (int)m_Split.x;
	int EndY = (int)(StartY + ((StartX + (Num - 1)) / m_Split.x));
	m_End = { EndX, EndY };			// 終了位置
	m_nPace = Pace;					// 再生速度
	m_nCount = 0;					// カウンタ	
	m_bLoop = Loop;					// ループ
	m_Status = ANIM_STATUS::PLAY;			// アニメを開始

	// アニメの最初
	m_TexCoord.x = (float)m_Start.x;
	m_TexCoord.y = (float)m_Start.y;
}

//--- アニメ再生停止
void CAnime::Play(bool Play)
{
	// アニメが設定されていない
	if (m_Status == ANIM_STATUS::NO) return;

	if (Play)
		m_Status = ANIM_STATUS::PLAY;
	else
		m_Status = ANIM_STATUS::STOP;
}

//--- アニメの状態取得
ANIM_STATUS CAnime::isPlay()
{
	return m_Status;
}


