///////////////////////////////////////
// Anime.cpp
//-------------------------------------
// 2020/09/03	�쐬
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Polygon.h"

//--- �񋓑�
enum class ANIM_STATUS	// �A�j���̏��
{
	NO,		// �Ȃ�
	PLAY,	// �Đ���
	STOP,	// ��~��
	END,	// �I�����Ă���

	MAX
};

//--- �N���X
class CAnime : public CPolygon
{
public:

	CAnime() {};	// �R���X�g���N�^
	~CAnime() {};	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

	void SetAnime(int StartX, int StartY, int Num, int Pace, bool Loop = true);	// �A�j���ݒ�
	void Play(bool Play = true);	// �A�j���Đ���~
	ANIM_STATUS isPlay();			// �A�j���̏�Ԏ擾

private:

	VECTOR2<int> m_Start;	// �A�j���J�n�ʒu
	VECTOR2<int> m_End;		// �A�j���I���ʒu
	int m_nPace;			// �A�j�����x
	int m_nCount;			// �J�E���^
	bool m_bLoop;			// ���[�v
	ANIM_STATUS m_Status;	// �A�j���̏��

};
