///////////////////////////////////////
// Game.h
//-------------------------------------
// 2020/07/17	作成
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include <Windows.h>

//--- 定数
#define SCREEN_WIDTH	(960)
#define SCREEN_HEIGHT	(540)

//--- プロトタイプ
HRESULT Init(HWND hWnd, UINT width, UINT heught);
void Uninit();
void Update();
void Draw();

