
#pragma once

//--- インクルード部
#include "Polygon.h"
#include "Pattern.h"

//--- リスト
using POLYGON_LIST = LIST<CPolygon*>;

//--- クラス
class CPolygonList
{
public:

	CPolygonList();	// コンストラクタ
	~CPolygonList();	// デストラクタ

	CPolygon* Add(CPolygon*);	// リストに追加
	void Delete(CPolygon*);		// リストから消去

	void Init();	// 初期化
	void Uninit();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	POLYGON_LIST* GetList() { return m_pListTop; };
	CPolygon* SearchName(const char* Name);	// 名前で検索

private:

	POLYGON_LIST* m_pListTop;	// リストの先頭アドレス

};

