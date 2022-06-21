// �t�F�[�h�A�E�g...���X�ɈÂ��Ȃ�Ȃ���A��ʂ�������(�A�E�g)
// �t�F�[�h�C��...���X�ɖ��邭�Ȃ�Ȃ���A��ʂ��o��(�C��)
#ifndef __FADE_H__
#define __FADE_H__

#include<Windows.h>
#include "Polygon.h"

class Fade : private CPolygon
{
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// �t�F�[�h��������
	bool IsFinish();
	// �t�F�[�h���s����
	bool IsExecute();
	// �t�F�[�h�J�n
	void Start(float time, bool isOut);

private:
	bool m_isOut;	// �t�F�[�h�̎��(�t�F�[�h�A�E�g���ǂ���)
	float m_maxTime;	// �t�F�[�h���s����
	float m_time;	// �t�F�[�h�o�ߎ���
};

#endif	// __FADE_H__
