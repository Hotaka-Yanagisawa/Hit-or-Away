////////////////////////////////////////////
//
//	2020/07/17
//	DX21 U22�����i
//	AT12D171 32 �������
//
////////////////////////////////////////////

//--- �C���N���[�h��
#include <windows.h>
#include <stdio.h>
#include "Game.h"

#pragma comment(lib, "winmm.lib")

//--- �v���g�^�C�v�錾
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
);


//--- �G���g���|�C���g
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{

	// �ϐ��錾
	WNDCLASSEX wcex;
	HWND hWnd;
	MSG message;

	// �E�B���h�E�N���X���̐ݒ�
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
			"�E�B���h�E�N���X���̓o�^�Ɏ��s���܂���",
			"�G���[", MB_OK | MB_ICONERROR);
		return 0;
	}

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		wcex.lpszClassName,
		"�^�C�g��",
		WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ����������
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	timeBeginPeriod(1);	// ���Ԍv���̐��x

	//--- FPS����̏�����
	int fpsCount = 0;	// ��b�Ԃ̏�����
	DWORD countStartTime = timeGetTime();	// �v���̊J�n����
	DWORD preExecTime = countStartTime;		// �O��̎��s����

	//--- �E�B���h�E�̊Ǘ�
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
			// FPS�̐���
			DWORD nowTime = timeGetTime();
			if (nowTime - countStartTime >= 1000)
			{
				// �^�C�g��������FPS��\��
				char fpsText[20];
				sprintf(fpsText, "FPS:%d", fpsCount);
				SetWindowText(hWnd, fpsText);
				// ���̈�b�Ԃ̌v������
				countStartTime = nowTime;
				fpsCount = 0;
			}

			// �Q�[���̏���
			if (nowTime - preExecTime >= 1000 / 60)
			{
				Update();
				Draw();

				// FPS����
				fpsCount++;
				preExecTime = nowTime;
			}
		}
	}

	//--- �I����
	timeEndPeriod(1);
	Uninit();
	// �E�B���h�E�N���X���̓o�^����
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
)
{
	// �󂯎�������b�Z�[�W���Ƃɏ���
	switch (message)
	{
		// �E�B���h�E�����
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}

	//�ق��̃��b�Z�[�W�͊�{�̏������s�킹��
	return DefWindowProc(
		hWnd, message,
		wParam, lParam
	);
}



