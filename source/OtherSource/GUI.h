////////////////////////////////////////
// GUI.h
//--------------------------------------
// 2020/09/26	�쐬
//
////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "PolygonList.h"
#include "Anime.h"

//--- �N���X
class GUI
{
public:

	void Init();	// ������
	void Uninit();	// �I��

	void Update();	// �X�V
	void Draw();	// �`��

private:

	bool m_bTutorial;		// ����\�����邵�Ȃ�

	CPolygonList* m_Apple;	// �p���[
	CAnime* m_Shine;		// �L���L��
	CAnime* m_Push;			// �{�^��
	CPolygon* m_EnemySym;	// �G

};


