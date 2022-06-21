////////////////////////////////////////
// Player.h
//--------------------------------------
// 2020/07/18	作成
//		08/29	やられ確認用のフラグ追加
//
////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Act.h"
#include "MySound.h"

//--- 定数定義
#define MAX_AP	(3)	// アイテム最大所持

//--- 列挙体
enum class E_PLAYER		// 種類
{
	ARMOR = 1,
	THIEF,
	SNIPE,

	MAX
};

//--- クラス
class CPlayer : public CAct
{
public:

	CPlayer(E_PLAYER, float x, float y);	// コンストラクタ
	~CPlayer();	// デストラクタ

	void Update();	// 更新
	void Draw();	// 描画

	static int GetResult(void)
	{
		return m_bResult;
	}

	E_PLAYER GetPlayerType();
	static int GetSpecial();
	static bool GetCanAtk() { return m_bCharge; };
	static void SetSpecial(int val);

private:

	E_PLAYER	m_Type;		// 種類
	static int	m_nSpecial;	// キャラごとの特殊な要素
	static bool	m_bCharge;	// 攻撃可能フラグ
	static bool	m_bResult;	// やられた
	int			m_nAtkCnt;	// 攻撃してるカウント

	CSound sound;
};
