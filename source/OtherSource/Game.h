///////////////////////////////////////
// Game.h
//-------------------------------------
// 2020/07/17	�쐬
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include <Windows.h>

//--- �萔
#define SCREEN_WIDTH	(960)
#define SCREEN_HEIGHT	(540)

//--- �v���g�^�C�v
HRESULT Init(HWND hWnd, UINT width, UINT heught);
void Uninit();
void Update();
void Draw();

