///////////////////////////////////////
// SceneMgr.h
//-------------------------------------
// 2020/07/28	�쐬
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include <Windows.h>
#include "TitleScene.h"
#include "GameScene.h"
#include "Fade.h"
#include "MySound.h"

//--- �񋓑�
enum SCENE
{
	SCENE_TITLE,	// �^�C�g��
	SCENE_GAME,		// �Q�[��

	SCENE_MAX
};

//--- �N���X
class SceneManager
{
public:

	void SetStartScene();	// �}�l�[�W���[�̏�����

	// �V�[�����Ƃ̏���
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

private:

	SCENE m_scene;			// ���݂̃V�[��
	SCENE m_nextScene;		// ���̃V�[��(�\��)

	TitleScene* m_title;	// �^�C�g���V�[���̏���
	GameScene* m_game;		// �Q�[���V�[���̏���

	Fade m_fade;			// �t�F�[�h����
	CSound sound;			// �T�E���h
};

