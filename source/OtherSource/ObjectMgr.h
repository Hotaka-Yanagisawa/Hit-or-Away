///////////////////////////////////////
// ObjectMgr.h
//-------------------------------------
// 2020/07/28	作成
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include "Object.h"
#include "ObjectList.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Gimmick.h"
#include "Item.h"

//--- オブジェクトを管理するクラス
class ObjectManager
{
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// オブジェクトの生成
	void CreatePlayer(E_PLAYER, float x, float y);
	void CreateBullet(E_BULLET, float x, float y, float mx, float my);
	void CreateEnemy(PATHS path, float x, float y);
	void CreateGimmick(E_GIMMICK Type, float x, float y);
	void CreateItem(E_ITEM Type, float x, float y);

	void DestroyObject(CObject*);	// オブジェクト消去(ポインタ)
	void DestroyObject(E_OBJ);		// オブジェクト消去(タグ)

private:

	CObjectList m_List;	// オブジェクトリスト

};

