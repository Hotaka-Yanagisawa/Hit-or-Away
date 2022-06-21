//===================================================================
//
//	objectList.cpp
//	オブジェクトのリスト関連
//
//
//-------------------------------------------------------------------
//	作成者：AT12D 35 柳沢帆貴
//-------------------------------------------------------------------
//	開発履歴
//	2020/08/17	作成
//  2020/09/01  今回のプロジェクト用に改変
//
//===================================================================

#include <math.h>
#include "effectList.h"

EFFECT_LIST* pDummyHead = NULL;	// 先頭ノード
EFFECT_LIST* pDummyTail = NULL;	// 末尾ノード



CEffectList::CEffectList()
{
	
}

CEffectList::~CEffectList()
{

}

/////////////////////////////////
//
// リストの先頭と末尾の作成
//
////////////////////////////////
void CEffectList::Init()	
{
	pDummyHead = (EFFECT_LIST*)malloc(sizeof(EFFECT_LIST));
	//ノードの値を設定して前後のノードを初期化
	pDummyHead->Data = NULL;
	pDummyHead->Next = NULL;
	pDummyHead->Prev = NULL;

	pDummyTail = (EFFECT_LIST*)malloc(sizeof(EFFECT_LIST));
	//ノードの値を設定して前後のノードを初期化
	pDummyTail->Data = NULL;
	pDummyTail->Next = NULL;
	pDummyTail->Prev = pDummyHead;

	pDummyHead->Next = pDummyTail;
}



////////////////////////////////////////
//
// 更新
//
////////////////////////////////////////
bool CEffectList::Update()
{
	EFFECT_LIST* pNode = pDummyHead->Next;

	while (pNode != pDummyTail)
	{
		pNode->Data->Update();

		//使用済なら削除
		if (pNode->Data->isPlay() == ANIM_STATUS::END)
		{
			EFFECT_LIST* temp = pNode;
			pNode = pNode->Next;
			CEffectList::Remove(temp);
			continue;
		}
		pNode = pNode->Next;
	}
	return false;
}




////////////////////////////////////////
//
// 描画
//
////////////////////////////////////////
void CEffectList::Draw()
{
	EFFECT_LIST* pNode = pDummyHead->Next;

	while (pNode != pDummyTail)
	{
		pNode->Data->Draw();
		pNode = pNode->Next;
	}
}




////////////////////////////////////////
//
// リストの追加
//
////////////////////////////////////////
Effect* CEffectList::Add(Effect* pEffect)	//たぶん完成
{
	//ノードのメモリを確保する
	EFFECT_LIST* pNode = (EFFECT_LIST*)malloc(sizeof(EFFECT_LIST));

	//ノードの値を設定して前後のノードを初期化
	pNode->Data  = pEffect;
	pNode->Next = NULL;
	pNode->Prev = NULL;

	//ダミー以外のノードが無い場合
	if (pDummyHead->Next == pDummyTail)
	{
		pDummyHead->Next = pNode;
		pNode->Prev	  = pDummyHead;
		pDummyTail->Prev = pNode;
		pNode->Next      = pDummyTail;
		return NULL;
	}

	//ダミーを除いた現在の末尾の次のノードとして登録
	pDummyTail->Prev->Next = pNode;
	//ダミーを除いた末尾のノードとして登録
	pNode->Prev = pDummyTail->Prev;
	//末尾ダミー前のノードとして登録
	pDummyTail->Prev = pNode;
	//追加したノードの次を末尾ダミーにする
	pNode->Next = pDummyTail;

	return pNode->Data;
}


////////////////////////////////////////
//
// リストの削除
//
////////////////////////////////////////
void CEffectList::Remove(EFFECT_LIST* pNode)	
{	
	pNode->Prev->Next = pNode->Next;
	pNode->Next->Prev = pNode->Prev;

	free(pNode);
}

////////////////////////////////////////
//
// effectの作成
//
////////////////////////////////////////
void CEffectList::CreateEffect(float x, float y, FX_KIND kind)
{
	Effect* pEffect = new Effect(kind, x, y);
	Add(pEffect);
}



////////////////////////////////////////
//
// リストの全消去
//
////////////////////////////////////////
void CEffectList::AllDelete(void)	
{
	for (EFFECT_LIST* p = pDummyHead; p != pDummyTail;)
	{
		EFFECT_LIST* temp = p;		
		p = p->Next;
		free(temp);
	}
}

////////////////////////////////////////
//
// リストの先頭アドレス取得
//
////////////////////////////////////////
EFFECT_LIST* CEffectList::GetList()
{
	return pDummyHead->Next;
}