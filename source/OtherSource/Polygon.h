//////////////////////////////////////////////
// Polygon.h
//--------------------------------------------
// 2020/07/17	作成
//		07/18	アニメ処理関数追加
//		07/20	SetVtx関数消去
//		07/26	GetPos, Size関数追加
//		08/03	Set関数の相対指定追加
//
//////////////////////////////////////////////

#pragma once

//--- インクルード部
#include "Texture.h"

//--- 構造体
template <typename Type = float>
struct VECTOR2	// 座標
{
	Type x;
	Type y;
};
struct COLOR	// 色情報
{
	float r;
	float g;
	float b;
	float a;
};

//--- クラス
class CPolygon
{
public:

	CPolygon();		// コンストラクタ
	 ~CPolygon();	// デストラクタ

	virtual void Update();	// 更新
	virtual void Draw();	// 描画

	//--- ポリゴン
	virtual void SetPos(float PosX, float PosY, bool Relative = false);			// 座標設定
	void SetSize(float SizeX, float SizeY, bool Relative = false);				// 大きさ設定
	void SetColor(float r, float g, float b, float a, bool Relative = false);	// 色設定
	void SetAngle(float Angle, bool Relative = false);							// 角度設定(度数)
	void SetImage(const char* FileName);										// 画像読み込み
	void SetTexture(ID3D11ShaderResourceView* pTexture);						// テクスチャ設定
	void SetSplit(float w, float h);											// 分割数設定
	void SetUV(float u, float v);												// UV座標設定
	void SetName(const char* Name);												// 名前設定
	void Show(bool show = true) { m_bShow = show; };							// 表示設定

	VECTOR2<> GetPos();		// 座標取得
	VECTOR2<> GetSize();	// 大きさ取得
	char*	GetName();		// 名前取得

protected:

	CTexture	m_Texture;	// テクスチャ
	VECTOR2<>	m_Position;	// 位置
	VECTOR2<>	m_Size;		// 大きさ
	VECTOR2<>	m_Split;	// 分割数
	VECTOR2<>	m_TexCoord;	// UV座標
	COLOR	m_Color;		// 色
	float	m_fRadian;		// 角度
	char	m_szName[10];	// 名前
	bool	m_bShow;		// 表示する

};

//--- プロトタイプ宣言
HRESULT InitPolygon(UINT width, UINT height);	// 初期化
void UninitPolygon();							// 終了

