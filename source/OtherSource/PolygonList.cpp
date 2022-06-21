
//--- インクルード部
#include "PolygonList.h"
#include "Polygon.h"
#include <Windows.h>

//--- コンストラクタ
CPolygonList::CPolygonList()
{

}

//--- デストラクタ
CPolygonList::~CPolygonList()
{

}

//--- 初期化
void CPolygonList::Init()
{
	m_pListTop = NULL;
}

//--- 終了
void CPolygonList::Uninit()
{
	// リストを解放
	POLYGON_LIST* p = m_pListTop;
	POLYGON_LIST* temp;

	while (p != NULL)
	{
		temp = p->Next;
		delete(p->Data);
		free(p);
		p = temp;
	}

	m_pListTop = NULL;
}

//--- 更新
void CPolygonList::Update()
{
	POLYGON_LIST *p;

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
void CPolygonList::Draw()
{
	POLYGON_LIST *p;

	// 先頭アドレスから実行
	p = m_pListTop;
	while (p != NULL)
	{
		p->Data->Draw();
		p = p->Next;
	}
}

//--- リストに追加
CPolygon* CPolygonList::Add(CPolygon* pCPolygon)
{
	POLYGON_LIST *p;

	// メモリの確保
	p = (POLYGON_LIST*) malloc(sizeof(POLYGON_LIST));

	// データを登録
	p->Data = pCPolygon;

	// ポインタのつなぎ換え
	p->Next = m_pListTop;
	m_pListTop = p;

	return m_pListTop->Data;
}

//--- リストから消去
void CPolygonList::Delete(CPolygon* pCPolygon)
{
	POLYGON_LIST *p;
	POLYGON_LIST *temp;
	// 先頭アドレスから実行
	p = m_pListTop;

	while (p->Next->Data != pCPolygon)
	{
		p = p->Next;
	}

	temp = p->Next;
	p->Next = temp->Next;

	delete temp->Data;
}

//--- 名前で検索
CPolygon* CPolygonList::SearchName(const char* Name)
{
	POLYGON_LIST* p;

	// 先頭アドレスから実行
	p = m_pListTop;
	while (p != NULL)
	{
		char* Tname = p->Data->GetName();
		if (!strcmp(Tname, Name)) break;
		p = p->Next;
	}

	if (p == NULL) return m_pListTop->Data;
	return p->Data;
}
