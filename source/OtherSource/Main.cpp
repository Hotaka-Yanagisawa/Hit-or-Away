////////////////////////////////////////////
//
//	2020/07/17
//	DX21 U22応募作品
//	AT12D171 32 水野樹生
//
////////////////////////////////////////////

//--- インクルード部
#include <windows.h>
#include <stdio.h>
#include "Game.h"

#pragma comment(lib, "winmm.lib")

//--- プロトタイプ宣言
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);


//--- エントリポイント
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{

	// 変数宣言
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG message;

	// ウィンドウクラス情報の設定
	ZeroMemory(&wcex, sizeof(wcex));
	wcex.hInstance = hInstance;
	wcex.lpszClassName = "Class Name";
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_CLASSDC;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hIcon =
		LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor =
		LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground =
		(HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			"ウィンドウクラス情報の登録に失敗しました",
			"エラー", MB_OK | MB_ICONERROR);
		return 0;
	}

	// ウィンドウの作成
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		wcex.lpszClassName,
		"タイトル",
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 初期化処理
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	timeBeginPeriod(1);	// 時間計測の精度

	//--- FPS制御の初期化
	int fpsCount = 0;	// 一秒間の処理回数
	DWORD countStartTime = timeGetTime();	// 計測の開始時間
	DWORD preExecTime = countStartTime;		// 前回の実行時間

	//--- ウィンドウの管理
	while (1)
	{
		if (PeekMessage(
			&message, NULL, 0, 0,
			PM_NOREMOVE))
		{
			if (!GetMessage(&message,
				NULL, 0, 0))
			{
				break;
			}
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			// FPSの制御
			DWORD nowTime = timeGetTime();
			if (nowTime - countStartTime >= 1000)
			{
				// タイトル部分にFPSを表示
				char fpsText[20];
				sprintf(fpsText, "FPS:%d", fpsCount);
				SetWindowText(hWnd, fpsText);
				// 次の一秒間の計測準備
				countStartTime = nowTime;
				fpsCount = 0;
			}

			// ゲームの処理
			if (nowTime - preExecTime >= 1000 / 60)
			{
				Update();
				Draw();

				// FPS処理
				fpsCount++;
				preExecTime = nowTime;
			}
		}
	}

	//--- 終了時
	timeEndPeriod(1);
	Uninit();
	// ウィンドウクラス情報の登録解除
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	// 受け取ったメッセージごとに処理
	switch (message)
	{
		// ウィンドウを閉じた
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	//ほかのメッセージは基本の処理を行わせる
	return DefWindowProc(
		hWnd, message,
		wParam, lParam
	);
}



