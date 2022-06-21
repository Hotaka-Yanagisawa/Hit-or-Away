////////////////////////////////////////
// Act.h
//--------------------------------------
// 2020/09/02	作成
//		09/03	歩行アニメ処理
//
////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Object.h"

//--- 定数定義
#define MOVE_UP		(0)
#define MOVE_DOWN	(180)
#define MOVE_LEFT	(90)
#define MOVE_RIGHT	(270)

//--- 列挙体
enum class E_DIRECT	// 方向
{
	UP = 0,	// 上
	DOWN,	// 下
	LEFT,	// 左
	RIGHT,	// 右
	MAX
};

//--- クラス
class CAct: public CObject
{
public:

	CAct();		// コンストラクタ
	~CAct();	// デストラクタ

	virtual void Update();	// 更新
	virtual void Draw();	// 描画

	// 歩行アニメの設定
	void SetWalkAnime(int BaseX, int BaseY,int Num = 4)
	{
		m_AnimeBase = { BaseX, BaseY };
		m_nAnimeNum = Num;
	}

	// 移動
	void Move(float MoveX, float MoveY);	// 移動量指定
	void Move(float Angle);					// 角度指定

	void Lock(bool Lock = true) { m_bLockDirect = Lock; };	// 方向固定

protected:

	int		m_nHp;		// 体力
	int		m_nAttack;	// 攻撃力
	float	m_fSpeed;	// 移動速度

	E_DIRECT	m_Direct;	// 向いてる方向

	//bool	m_bAttack;	// 攻撃してる
	//int	m_nAtkCnt;	// 攻撃してるカウント

	VECTOR2<int>	m_AnimeBase;	// 基準のUV座標
	int				m_nAnimeNum;	// アニメのフレーム数

private:

	static int m_nAnimeSpB;	// アニメ速度の基本値

	bool m_bLockDirect;		// 方向固定

	void UpdateDirect();	// 移動量から方向を求める

private:

	E_DIRECT	m_OldDirect;	// 向いてた方向

};
