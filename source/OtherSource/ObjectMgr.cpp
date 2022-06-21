///////////////////////////////////////
// ObjectMgr.cpp
//-------------------------------------
// 2020/07/28	作成
//
///////////////////////////////////////

//--- インクルード部
#include "ObjectMgr.h"
#include "ObjectList.h"

#include "Player.h"
#include "Enemy.h"
#include "PatrolState.h"

CPlayer* pPlayer;

//--- 初期化
void ObjectManager::Init()
{
	// リストのオブジェクト初期化
	m_List.Init();
}

//--- 終了
void ObjectManager::Uninit()
{
	// リストのオブジェクト終了
	m_List.Uninit();

}

//--- 更新
void ObjectManager::Update()
{
	// リストのオブジェクト更新
	m_List.Update();

}

//--- 描画
void ObjectManager::Draw()
{
	// リストをY座標昇順でソート
	//m_List.Sort(SORT::Y);
	// リストのオブジェクト描画
	m_List.Draw();

}

//--- オブジェクト生成
void ObjectManager::CreatePlayer(E_PLAYER Type, float x, float y)
{
	pPlayer = new CPlayer(Type, x, y);
	m_List.Add(pPlayer);
}
void ObjectManager::CreateBullet(E_BULLET Type, float x, float y, float mx, float my)
{
	CBullet* pBullet = new CBullet(Type, x, y, mx, my);
	m_List.Add(pBullet);
}
void ObjectManager::CreateEnemy(PATHS path, float x, float y)
{
	CEnemy* pEnemy = new CEnemy(pPlayer, PatrolState::GetInstance(), path, x, y);
	m_List.Add(pEnemy);
}
void ObjectManager::CreateGimmick(E_GIMMICK Type, float x, float y)
{
	CGimmick* pGimmick = new CGimmick(Type, x, y);
	m_List.Add(pGimmick);
}
void ObjectManager::CreateItem(E_ITEM Type, float x, float y)
{
	CItem* pItem = new CItem(Type, x, y);
	m_List.Add(pItem);
}

//--- オブジェクトの消去(ポインタ)
void ObjectManager::DestroyObject(CObject* pObj)
{
	OBJECT_LIST* p = CObjectList::GetList();

	// 消去するデータまでリストを辿る
	while (p->Next != NULL && p->Next->Data != pObj) p = p->Next;

	// ポインタをつなぎ変える
	OBJECT_LIST* temp;
	temp = p->Next;		// 次ポインタを取り置く
	p->Next = temp->Next;	// つなぎ変える

	// データを削除
	delete temp->Data;
	free(temp);

}
//--- オブジェクトの消去(タグ)
void ObjectManager::DestroyObject(E_OBJ Type)
{
	OBJECT_LIST* p = CObjectList::GetList();

	// 消去するデータまでリストを辿る
	while (p->Next != NULL && p->Next->Data->GetType() != Type) p = p->Next;

	// データ無し
	if (p->Next == NULL) return;

	// ポインタをつなぎ変える
	OBJECT_LIST* temp;
	temp = p->Next;			// 次ポインタを取り置く
	p->Next = temp->Next;	// つなぎ変える

	// データを削除
	delete temp->Data;
	free(temp);
}

