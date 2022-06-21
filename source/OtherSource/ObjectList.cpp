
//--- インクルード部
#include "ObjectList.h"
#include "Object.h"
#include <Windows.h>

OBJECT_LIST* CObjectList::m_pListTop;	// リストの先頭アドレス

//--- コンストラクタ
CObjectList::CObjectList()
{

}

//--- デストラクタ
CObjectList::~CObjectList()
{

}

//--- 初期化
void CObjectList::Init()
{
	m_pListTop = NULL;
}

//--- 終了
void CObjectList::Uninit()
{
	// リストを解放
	OBJECT_LIST* p = m_pListTop;
	OBJECT_LIST* temp;

	while (p != NULL)
	{
		temp = p->Next;
		delete p->Data;
		free(p);
		p = temp;
	}

	m_pListTop = NULL;
}

//--- 更新
void CObjectList::Update()
{
	OBJECT_LIST *p;

	//// 存在しないオブジェクトを消す
	//p = m_pListTop;
	//while (p != NULL)
	//{
	//	if (p->Next == NULL) break;

	//	if (!p->Next->Data->GetExist())
	//	{
	//		OBJECT_LIST* temp = p->Next;
	//		p->Next = temp->Next;
	//		delete(temp);
	//	}
	//	p = p->Next;
	//}
	
	// 先頭アドレスから実行
	p = m_pListTop;
	while (p != NULL)
	{
		if (p->Data == nullptr) break;
		p->Data->Update();
		p = p->Next;
	}
}

//--- 描画
void CObjectList::Draw()
{
	OBJECT_LIST *p;

	// 先頭アドレスから実行
	p = m_pListTop;
	while (p != NULL)
	{
		p->Data->Draw();
		p = p->Next;
	}
}

//--- リストに追加
CObject* CObjectList::Add(CObject* pCObject)
{
	OBJECT_LIST *p;

	// メモリの確保
	p = (OBJECT_LIST*) malloc(sizeof(OBJECT_LIST));

	// データを登録
	p->Data = pCObject;

	// ポインタのつなぎ換え
	p->Next = m_pListTop;
	m_pListTop = p;

	return m_pListTop->Data;
}

//--- リストから消去
void CObjectList::Delete(CObject* pCObject)
{
	OBJECT_LIST *p;
	OBJECT_LIST *temp;
	// 先頭アドレスから実行
	p = m_pListTop;

	while (p->Next->Data != pCObject)
	{
		p = p->Next;
	}

	temp = p->Next;
	p->Next = temp->Next;

	delete temp->Data;
}

//--- リスト取得
OBJECT_LIST* CObjectList::GetList()
{
	return m_pListTop;
}

//---  ソート
void CObjectList::Sort(SORT Type)
{
	OBJECT_LIST *p;

	switch (Type)
	{
	case SORT::Y:
		// Y座標昇順でソート
		p = m_pListTop;
		while (p->Next != NULL)
		{
			float Y1 = p->Data->GetPos().y;
			float Y2 = p->Next->Data->GetPos().y;
			if (Y1 > Y2)
			{
				CObject* temp = p->Data;
				p->Data = p->Next->Data;
				p->Next->Data = temp;
			}
			p = p->Next;
		}
		break;

	case SORT::TAG:
		// タグ昇順でソート
		p = m_pListTop;
		while (p->Next != NULL)
		{
			int Y1 = (int)p->Data->GetType();
			int Y2 = (int)p->Next->Data->GetType();
			if (Y1 > Y2)
			{
				CObject* temp = p->Data;
				p->Data = p->Next->Data;
				p->Next->Data = temp;
			}
			p = p->Next;
		}
		break;

	default:
		break;
	}
}
