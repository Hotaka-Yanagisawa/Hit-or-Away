
#pragma once

//--- インクルード部
#include "Object.h"
#include "Pattern.h"

//--- 列挙体
enum class SORT
{
	Y,
	TAG,

};

//--- リスト
using OBJECT_LIST = LIST<CObject*>;

//--- クラス
class CObjectList
{
public:

	CObjectList();	// コンストラクタ
	~CObjectList();	// デストラクタ

	CObject* Add(CObject*);	// リストに追加
	void Delete(CObject*);	// リストから消去

	void Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	static void Sort(SORT);	// 並び替え

	static OBJECT_LIST* GetList();	// リスト取得

private:

	static OBJECT_LIST* m_pListTop;	// リストの先頭アドレス

};

