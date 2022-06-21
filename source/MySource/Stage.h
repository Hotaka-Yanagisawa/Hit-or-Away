///////////////////////////////////////////
// Stage.h
//-----------------------------------------
// 2020/08/03	作成
//
//
///////////////////////////////////////////

#pragma once

//--- インクルード部
#include "ObjectMgr.h"
#include "Timer.h"
#include "Field.h"
#include "Gimmick.h"
#include "Item.h"
#include <vector>
#include <string>
#include "MySound.h"

using namespace std;

//--- 構造体
typedef struct
{
	PATHS path;
	float x;
	float y;
}ENEMY_DATA;

typedef struct
{
	E_GIMMICK type;
	float x;
	float y;
}GIMMICK_DATA;

typedef struct
{
	E_ITEM type;
	float x;
	float y;
}ITEM_DATA;

//--- 列挙体
enum class STAGE_ID	// ステージ識別用
{
	NO = -1,
	P_MOVE,
	P_ATTACK,
	P_ARMOR,
	P_THIEF,
	P_SNIPE,
	P_SWITCH,
	ICE1,
	SWITCH1,
	SPEED1,
	ICE2,
	SPEED2,
	SWITCH2,
	ICE3,
	SNIPE,
	BOSS,

	MAX
};
enum class CLEAR_TARGET	// クリア条件
{
	NO = -1,
	DEFEAT,		// 敵を倒す
	RECOVER,	// 回収する
	ESCAPE,		// 生き残る
	REACH,		// 到達する

	MAX
};
enum class STAGE_RESULT	// 結果
{
	NO = 0,
	CLEAR,
	MISS,

	MAX
};

// 構造体を一纏めにしてコンテナ型にしたもの
typedef struct
{
	vector<ENEMY_DATA>    enemy;
	vector<GIMMICK_DATA>  gimmick;
	vector<ITEM_DATA>	  item;
}STAGE_DATA;

typedef struct
{
	E_FIELD fieldType;	// ステージの種類
	string loadPathName;	// path名 practice/ など
	float sizeX;			// フィールドのサイズ
	float sizeY;
	E_PLAYER playerType;	// プレイヤータイプ
	float PlayerPosX;
	float PlayerPosY;
	int TimeNum;
	CLEAR_TARGET clearTarget;
}FILE_LOAD;

//--- クラス
class CStage
{
public:

	CStage();	// コンストラクタ
	~CStage();	// デストラクタ

	void Init(STAGE_ID);
	void Uninit();
	STAGE_RESULT Update();
	void Draw();

	static int	GetSpilit() { return m_nSpilit; };
	static void	SetSpilit(int v) { m_nSpilit += v; };

	static ObjectManager* GetObjMgr() { return m_pObject; };

private:

	CTimer* m_pTimer;
	CField* m_pField;

	CLEAR_TARGET m_ClearCondition;	// クリア条件
	static int m_nSpilit;

	static ObjectManager* m_pObject;	// オブジェクト管理リスト

	STAGE_DATA m_Data;
	void LoadStageData(STAGE_ID);
	void LoadCsv();
	FILE_LOAD m_loadData;
	CSound sound;
};

