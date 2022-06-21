//////////////////////////////////////////////
// Texture.h
//--------------------------------------------
// 2020/07/17	作成
//		09/03	クラス化
//
//////////////////////////////////////////////

#pragma once

//--- インクルード部
#include "DirectX.h"

//--- クラス
class CTexture
{
public:

	ID3D11ShaderResourceView* m_pTexture;

public:

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	HRESULT LoadTexture(const char *pszFileName);	// 画像読み込み
	void UnLoadTexture();							// テクスチャ解放

};