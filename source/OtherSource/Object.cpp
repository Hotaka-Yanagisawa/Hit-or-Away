//////////////////////////////////////////////////
// Object.cpp
//------------------------------------------------
// 2020/07/17	作成
//		07/20	ObjNum追加
//		07/26	タグ追加
//
//////////////////////////////////////////////////

//--- インクルード部
#include "Object.h"
#include "ObjectList.h"
#include "Camera.h"
#include "Game.h"

#include "Field.h"

//--- 静的メンバ変数
int CObject::m_nObjNum = 0;

//--- コンストラクタ
CObject::CObject()
{
	// ステータスの初期化
	m_Move = { 0.0f, 0.0f };
	m_Timer = 0;
	m_bExist = true;
	m_bHit = true;
	m_Tag = E_OBJ::MAX;
	// オブジェクト数カウント
	m_nObjNum++;

}

//--- デストラクタ
CObject::~CObject()
{
	Destroy();
	m_nObjNum--;
}

//--- 更新
void CObject::Update()
{
	if (!m_bExist) return;	// 存在しない

	// 移動量の更新
	m_Position.x += m_Move.x;
	m_Position.y += m_Move.y;

	// カメラを反映
	m_Animation.SetPos(m_Position.x - GetCamera()->GetPosX(),
		m_Position.y - GetCamera()->GetPosY());

	// アニメの更新
	m_Animation.Update();

}

//--- 描画 
void CObject::Draw()
{
	if (!m_bExist) return;	// 存在しない

	// アニメの描画
	m_Animation.Draw();
}

//--- 座標設定
void CObject::SetPos(float PosX, float PosY)
{
	m_Position = { PosX, PosY };
}

//--- 移動量設定
void CObject::SetMove(float MoveX, float MoveY)
{
	m_Move = { MoveX, MoveY };
}

//--- 種類設定
void CObject::SetTag(E_OBJ Type)
{
	m_Tag = Type;
}

//--- 消去
void CObject::Destroy()
{
	m_bExist = false;
	m_bHit = false;
}

//--- 座標取得
VECTOR2<> CObject::GetPos()
{
	return m_Position;
}

//--- 移動量取得
VECTOR2<> CObject::GetMove()
{
	return m_Move;
}

//--- 種類取得
E_OBJ CObject::GetType()
{
	if (!this) return E_OBJ::MAX;
	return m_Tag;
}

//--- オブジェクトの数取得
int CObject::GetObjNum()
{
	return m_nObjNum;
}

//--- 当たり判定
CObject* CObject::Hit(float LooseX, float LooseY)
{
	//自分の当たり判定が無い場合
	if (!m_bHit)	return NULL;

	// リストを取得
	OBJECT_LIST* pList = CObjectList::GetList();

	// 当たり判定優先順位で並び替え
	CObjectList::Sort(SORT::TAG);

	// 順番に衝突判定
	pList = CObjectList::GetList();
	for (int i = 0; i < m_nObjNum; i++, pList = pList->Next)
	{
		CObject* Target = pList->Data;
		// 当たり判定無し
		if (!Target->m_bHit) continue;
		if (!Target->m_bExist) continue;
		if (Target->m_Tag == m_Tag) continue;

		//--- 矩形判定
		VECTOR2<> half1 = { m_Animation.GetSize().x / 2, m_Animation.GetSize().y / 2 };
		VECTOR2<> half2 = { Target->m_Animation.GetSize().x / 2, Target->m_Animation.GetSize().y / 2 };
		// 接したときの距離
		float distX = GetPos().x - Target->GetPos().x;
		if (distX < 0) distX *= -1;
		float distY = GetPos().y - Target->GetPos().y;
		if (distY < 0) distY *= -1;
		// 判定
		if ((distX < half1.x + half2.x * LooseX)
			&& (distY < half2.y + half2.y * LooseY))
		{
			return Target;
		}
		// 当たってない
		else continue;

		break;
	}

	return NULL;
}
