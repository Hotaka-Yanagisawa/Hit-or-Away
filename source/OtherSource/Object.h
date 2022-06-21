///////////////////////////////////////
// Object.h
//-------------------------------------
// 2020/07/17	作成
//		07/26	タグ追加
//		07/30	各ゲッター追加
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include "Anime.h"

//--- 列挙体
enum class E_OBJ	// オブジェクトの種類
{
	// ※当たり判定の優先順位
	PLAYER,	// プレイヤー
	WALL,	// 壁
	BOX,	// 壊せる壁
	ROCK,	// すり抜けられる壁
	BULLET,	// プレイヤーの攻撃
	GIMICK,	// ギミック
	ITEM,	// アイテム
	ENEMY,	// 敵

	MAX		// 設定無し
};

//--- クラス
class CObject
{
public:

	CObject();	// コンストラクタ
	virtual  ~CObject();	// デストラクタ

	virtual void Update();
	virtual void Draw();

	void SetPos(float PosX, float PosY);	// 座標設定
	void SetMove(float MoveX, float MoveY);	// 移動量設定
	void SetTag(E_OBJ);						// 種類設定

	virtual void Destroy();		// 画面から消去

	CAnime	m_Animation;	// アニメーション

	CObject* Hit(float = 1.0f, float = 1.0f);	// 当たり判定

	VECTOR2<> GetPos();		// 座標取得
	VECTOR2<> GetMove();	// 移動量取得
	E_OBJ GetType();		// 種類取得
	bool GetExist() { return m_bExist; };

	int GetObjNum();	// オブジェクトの数取得

protected:

	VECTOR2<>	m_Position;	// 位置
	VECTOR2<>	m_Move;		// 移動量
	int		m_Timer;		// タイマー
	bool	m_bExist;		// 存在
	bool	m_bHit;			// 当たり判定
	E_OBJ	m_Tag;			// 種類

private:

	static int m_nObjNum;
	
};

