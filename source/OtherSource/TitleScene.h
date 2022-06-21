///////////////////////////////////////////
// TitleScene.h
//-----------------------------------------
// 2020/07/17	�쐬
//		08/03	Update�ŃX�e�[�W��ނ�Ԃ�
//
///////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Scene.h"
#include "PolygonList.h"
#include "Anime.h"
#include "MySound.h"
#include "Stage.h"

//--- �N���X
class TitleScene : public Scene
{
public:

	TitleScene();

	void Init();
	void Uninit();
	bool Update();
	void Draw();

	static STAGE_ID GetSelectStage();	// �I�����ꂽ�X�e�[�W�̎擾

private:

	static STAGE_ID m_SelectStage;	// �I�����ꂽ�X�e�[�W
	int m_maxSelectable;			// �I���ł���X�e�[�W��

	int		m_nCount;	// �`�J�`�J�J�E���g
	int		m_nTime;	// �J�ڃ^�C�}�[
	bool	m_bSelect;	// �Z���N�g���
	bool	m_bUpDown;	// START�t���O
	int		m_nKingTalk;	// �L���O����ׂ�

	CPolygonList m_TitlePolygon;
	CPolygonList m_SelectPolygon;
	CPolygonList m_StageImage;
	CPolygonList m_TipsList;

	CPolygon *Back, *Title, *PushEnter;	// �^�C�g��
	CPolygon *Select, *Start, *Unlock;	// �X�e�[�W�I��
	CAnime *Cursor, *LAllow, *RAllow;	// �J�[�\��
	CPolygon *Tips, *Rela;				// �ȈՐ���
	CPolygon *Message, *Talk; CAnime *King;	// �L���O�g�[�N

	CSound sound;
};

