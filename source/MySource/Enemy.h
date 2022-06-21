//////////////////////////////////////////////////////////////////////////////////////////
// Enemy.h
//-------------------------------------
// 作成者：AT12D_35_柳沢帆貴
//-------------------------------------
// 2020/07/20	作成
// 2020/07/26	メンバ変数を増やした
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

//--- インクルード部
#include "Object.h"
#include <stdio.h>
#include "MySound.h"
#include "HierarchyState.h"


//--- 定数定義
//#define MAX_ENEMY (20)

class CPlayer;


//--- 列挙体
enum class E_ENEMY		// 敵の種類
{
	SLIME = 1,
	RED_SLIME,
	GHOST,
	HIGH_GHOST,
	KING,

	MAX
};

enum PATHS
{
	STOP,					//静止
	UP_AND_DOWN,			//上下
	LEFT_AND_RIGHT,			//左右
	UP_DOWN_LEFT_RIGHT,		//上下左右
	RUSH_AND_REST,			//突進と休み
	TERESA,					//テレサみたいな動き
	TARGET_PLAYER,			//プレイヤーを追ってくる
	TARGET_PLAYER_AND_RETURN,			//プレイヤーを追ってくる
	BOSS,

	MAX_PATHS,
};



//--- クラス
class CEnemy : public CObject
{
public:
	enum MOVE_VEC
	{
		LEFT = (1 << 0),	// 左
		RIGHT = (1 << 1),	// 右
		UP = (1 << 2),	// 上
		DOWN = (1 << 3),	// 下
	};

	CEnemy(CPlayer *, HierarchyState *, PATHS, float, float);		// コンストラクタ
	~CEnemy();	// デストラクタ

	static void Init();
	void Update();	// 更新
	void Draw();	// 描画

	static int GetNum();	// 個数取得
	static void ResetNum();	// 個数初期化

	bool Paths(PATHS Pattern, int time);

	// 状態切り替え
	void ChangeState(HierarchyState *state);
	// プレイヤーとの距離チェック
	bool IsDistanceToPlayer(float distance, bool is_out_side);
	// 移動
	void Move(int vec);
	// 追跡
	void Chase();
	// 定位置に帰る
	bool Return();
	bool UpAndDown(int);
	bool LeftAndRight(int);
	bool UDAndLR(int);

	void RandomCreateEnemy(int);
	void RandomCreateEnemy();

	bool Escape(int);

	int AddTime(int add);
	void ResetTime();
	E_ENEMY GetEnemyType();
	PATHS   GetPath();

	State *m_ChildState;

private:
	void UpdateDestroyFade();
	void SetCharacter(PATHS Path);
	void SetType(E_ENEMY Type);

	// プレイヤーとの距離取得
	float GetDistance();

	static int row;		//次に読み込む列番号

	static int m_nNum;	// 存在する数

	E_ENEMY			m_Type;			// 種類
	PATHS			m_Path;			// 移動ルートの種類
	int				m_nHp;			// 体力
	int				m_stopTime;		// 停止時間
	int				m_moveTime;		// 移動時間
	float			m_fSpd;			// 速さ
	float			m_fadeCnt;		// 死亡時のフェードカウンター
	float			m_DeltaTime;	// 死亡時の時間調整
	bool			m_bDestroy;		// 死亡判定
	float			m_fDestroyCnt;	// 時間差で倒れるように
	static bool		m_bBoss;		// ボスが倒れたらtrue		

	VECTOR2<> m_FixedPos;	// 定位置

	CPlayer *m_Player;			//プレイヤー
	HierarchyState *m_State;	//状態
	static CSound sound;

};
