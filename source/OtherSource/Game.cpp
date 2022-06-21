///////////////////////////////////////
// Game.cpp
//-------------------------------------
// 2020/07/17	作成
//		07/22	ObjList追加
//		07/26	GameMgr, シーン処理追加
//		08/05	シーンマネをシングルトン
//
///////////////////////////////////////

//--- インクルード部
#include "Game.h"
#include "DirectX.h"
#include "Polygon.h"
#include "Keyboard.h"
#include "SceneMgr.h"
#include "Pattern.h"
#include "effectList.h"


//--- グローバル変数
SceneManager* g_pScene;

//--- 初期化
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = S_OK;

	// DirectXの初期化
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "DirectXの初期化に失敗しました",
			"Error", MB_OK | MB_ICONERROR);
		return hr;
	}

	// ポリゴンの初期化
	hr = InitPolygon(width, height);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "ポリゴンの初期化に失敗しました",
			"Error", MB_OK | MB_ICONERROR);
		return hr;
	}

	// キーボードの初期化
	hr = InitKeyboard();
	if (FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの初期化に失敗しました",
			"Error", MB_OK | MB_ICONERROR);
		return hr;
	}

	//エフェクトリストの初期化
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();
	pEffectList->Init();

	//サウンドの初期化		
	CSound::InitSound();

	// シーンマネージャーの初期化
	g_pScene = &Singleton<SceneManager>::GetInstance();
	g_pScene->SetStartScene();
	g_pScene->Init();

	// エフェクトの初期化
	Effect::Init();

	return hr;
}

//--- 終了
void Uninit()
{
	// シーンマネージャーの終了
	g_pScene->Uninit();

	// エフェクトの終了
	Effect::Uninit();
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();
	pEffectList->AllDelete();

	// サウンドの終了
	CSound::UninitSound();

	// キーボードの終了
	UninitKeyboard();

	// ポリゴンの終了
	UninitPolygon();

	// DirectXの終了
	UninitDirectX();

}

//--- 更新
void Update()
{
	// キーボードの更新
	UpdateKeyboard();

	// シーンの更新
	g_pScene->Update();

}

//--- 描画
void Draw()
{
	// 描画開始
	BeginDrawDirectX();

	// シーンごとの描画
	g_pScene->Draw();

	//DrawKeyboard();

	// 描画終了
	EndDrawDirectX();
}

