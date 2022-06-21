///////////////////////////////////////////
// Field.h
//-----------------------------------------
// 2020/08/05	作成
//
//
///////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Polygon.h"

//--- 列挙体
enum class E_FIELD
{
	STEPPE,	// 草原
	ICE,	// 氷床
	WIND,	// 風
	MAG,	// 溶岩

	MAX
};

//--- クラス
class CField : public CPolygon
{
public:

	CField();	// コンストラクタ
	~CField();	// デストラクタ

	void Init(E_FIELD, float SizeX, float SizeY);	// 初期化
	void Uninit();									// 終了

	void Update();	// 更新
	void Draw();	// 描画

	static E_FIELD GetType() { return m_Type; };
	static VECTOR2<> GetSize() { return m_fSize; };

private:

	static E_FIELD m_Type;	// 種類
	static VECTOR2<> m_fSize;	// 大きさ

};
