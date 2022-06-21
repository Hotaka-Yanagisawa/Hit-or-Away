///////////////////////////////////////
// Game.cpp
//-------------------------------------
// 2020/07/17	�쐬
//		07/22	ObjList�ǉ�
//		07/26	GameMgr, �V�[�������ǉ�
//		08/05	�V�[���}�l���V���O���g��
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "Game.h"
#include "DirectX.h"
#include "Polygon.h"
#include "Keyboard.h"
#include "SceneMgr.h"
#include "Pattern.h"
#include "effectList.h"


//--- �O���[�o���ϐ�
SceneManager* g_pScene;

//--- ������
HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr = S_OK;

	// DirectX�̏�����
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "DirectX�̏������Ɏ��s���܂���",
			"Error", MB_OK | MB_ICONERROR);
		return hr;
	}

	// �|���S���̏�����
	hr = InitPolygon(width, height);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�|���S���̏������Ɏ��s���܂���",
			"Error", MB_OK | MB_ICONERROR);
		return hr;
	}

	// �L�[�{�[�h�̏�����
	hr = InitKeyboard();
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̏������Ɏ��s���܂���",
			"Error", MB_OK | MB_ICONERROR);
		return hr;
	}

	//�G�t�F�N�g���X�g�̏�����
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();
	pEffectList->Init();

	//�T�E���h�̏�����		
	CSound::InitSound();

	// �V�[���}�l�[�W���[�̏�����
	g_pScene = &Singleton<SceneManager>::GetInstance();
	g_pScene->SetStartScene();
	g_pScene->Init();

	// �G�t�F�N�g�̏�����
	Effect::Init();

	return hr;
}

//--- �I��
void Uninit()
{
	// �V�[���}�l�[�W���[�̏I��
	g_pScene->Uninit();

	// �G�t�F�N�g�̏I��
	Effect::Uninit();
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();
	pEffectList->AllDelete();

	// �T�E���h�̏I��
	CSound::UninitSound();

	// �L�[�{�[�h�̏I��
	UninitKeyboard();

	// �|���S���̏I��
	UninitPolygon();

	// DirectX�̏I��
	UninitDirectX();

}

//--- �X�V
void Update()
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	// �V�[���̍X�V
	g_pScene->Update();

}

//--- �`��
void Draw()
{
	// �`��J�n
	BeginDrawDirectX();

	// �V�[�����Ƃ̕`��
	g_pScene->Draw();

	//DrawKeyboard();

	// �`��I��
	EndDrawDirectX();
}

