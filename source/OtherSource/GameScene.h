///////////////////////////////////////////
// GameScene.h
//-----------------------------------------
// 2020/08/05	�^�C�g�����R�s�[���č쐬
//		08/10	�Q�[���I�����̏��
//
///////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Scene.h"
#include "Camera.h"
#include "Stage.h"
#include "BackGround.h"
#include "GUI.h"
#include "Pattern.h"
#include "MySound.h"

//--- �񋓑�
enum class GAME_RESULT	// �Q�[������
{
	NO,
	CLEAR,		// �N���A
	MISS,		// ���s
	BREAK,		// ���f
	RESTART,	// ��蒼��
	MAX
};
enum PAUSE_MENU		// ���j���[�I����
{
	PAUSE_RESUME,	// �ĊJ
	PAUSE_RETRY,	// ��蒼��
	PAUSE_END,		// �I��
	PAUSE_MAX
};

//--- �N���X
class GameScene : public Scene
{
public:

	void Init();
	void Uninit();
	bool Update();
	void Draw();
	
	static GAME_RESULT GetResult();

private:

	CBackGround* m_pBG;	// �w�i
	GUI* m_pGUI;		// �V�X�e��
	PAUSE_MENU m_Menu;	// ���j���[
	CStage* m_pStage;	// �X�e�[�W

	int m_nResultTime;	// ���U���g��ʃ^�C�}�[
	bool m_bPause;		// �|�[�Y��ʃt���O
	static GAME_RESULT m_Result;	// �I�����̏��

	CPolygon Fade;
	CPolygon Pause;
	CPolygon Resume;
	CPolygon Retry;
	CPolygon End;
	CAnime	 Arrow;

	CSound sound;
};

