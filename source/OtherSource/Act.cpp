///////////////////////////////////////
// Act.cpp
//-------------------------------------
// 2020/09/02	作成
//		09/03	歩行アニメ処理
//
///////////////////////////////////////

//--- インクルード部
#include "Act.h"
#include "Field.h"

//--- グローバル変数
int CAct::m_nAnimeSpB;

//--- コンストラクタ
CAct::CAct()
{
	m_nHp = 0;
	m_nAttack = 1;
	m_fSpeed = 1.0f;

	//m_bMove = false;
	//m_bAttack = false;
	//m_nAtkCnt = 0;
	
	m_AnimeBase = { 0, 0 };
	m_nAnimeNum = 4;

	m_nAnimeSpB = 10;

	m_Direct = m_OldDirect = E_DIRECT::MAX;
}

//--- デストラクタ
CAct::~CAct()
{

}

//--- 更新
void CAct::Update()
{
	// 移動している
	if ((m_Move.x != 0) || (m_Move.y != 0))
	{
		m_Animation.Play(true);
		// 方向反映
		if (!m_bLockDirect) UpdateDirect();

		// 移動方向が変わった
		if (m_Direct != m_OldDirect)
		{
			// アニメを向きに合わせる
			m_Animation.Play(false);
			m_Animation.SetAnime(m_AnimeBase.x, m_AnimeBase.y + (int)m_Direct, m_nAnimeNum,
				m_nAnimeSpB - m_fSpeed);	// アニメ速度
			// 向きを更新
			m_OldDirect = m_Direct;
		}
	}
	// 移動していない
	else
	{
		m_Animation.Play(false);
		//m_Animation.SetUV(m_AnimeBase.x, m_AnimeBase.y - 1);
		//m_Direct = E_DIRECT::MAX;
	}

	// オブジェクトの更新
	CObject::Update();

	// フィールド外に出ない
	if (m_Position.x < 50) { m_Move.x = 0; m_Position.x = 50; }
	if (m_Position.y < 50) { m_Move.y = 0; m_Position.y = 50; }
	if (m_Position.x > CField::GetSize().x * 100 - 50) { m_Move.x = 0; m_Position.x = CField::GetSize().x * 100 - 50; }
	if (m_Position.y > CField::GetSize().y * 100 - 50) { m_Move.y = 0; m_Position.y = CField::GetSize().y * 100 - 50; }

}

//--- 描画
void CAct::Draw()
{
	// オブジェクトの描画
	CObject::Draw();

}

//--- 移動
// 移動量
void CAct::Move(float fMoveX, float fMoveY)
{
	// 移動量反映
	m_Move.x = fMoveX;
	m_Move.y = fMoveY;
}
// 角度
void CAct::Move(float fAngle)
{
	// 移動量を求める

}

//--- 移動量から方向を求める
void CAct::UpdateDirect()
{
	// 元の向きを保存
	m_OldDirect = m_Direct;

	//--- 最も大きい移動量に向きを変える
	// 絶対値
	float absMoveX = (m_Move.x > 0) ? m_Move.x : -m_Move.x;
	float absMoveY = (m_Move.y > 0) ? m_Move.y : -m_Move.y;
	// 比較
	if (absMoveX > absMoveY)
		if (m_Move.x > 0) m_Direct = E_DIRECT::RIGHT;
		else m_Direct = E_DIRECT::LEFT;
	else
		if (m_Move.y > 0) m_Direct = E_DIRECT::DOWN;
		else m_Direct = E_DIRECT::UP;
}

