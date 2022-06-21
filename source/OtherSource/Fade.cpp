
//--- �C���N���[�h��
#include "Fade.h"
#include "Game.h"

//--- ������
HRESULT Fade::Init()
{
	m_isOut = false;
	m_maxTime = 0.0f;
	m_time = 0.0f;
	return S_OK;
}

//--- �I��
void Fade::Uninit()
{

}

//--- �X�V
void Fade::Update()
{
	// �o�ߎ��Ԃ̌v��
	if (m_maxTime > m_time)
	{
		// 60FPS���Z
		m_time += 1.0f / 60;
	}
}

//--- �`��
void Fade::Draw()
{
	//--- ���ߐF�̌v�Z
	// �S�̂̎��s���Ԃ�1�Ƃ����Ƃ��̌o�ߎ��Ԃ̊���
	float rate = 1.0f;
	if (m_maxTime != 0.0f)
	{
		// �t�F�[�h�����������0������������̂ŃG���[�Ώ�
		rate = m_time / m_maxTime;
	}
	// ���ߐF
	float alpha = rate;
	if(!m_isOut)
	{
		alpha = 1 - alpha;
	}

	// �t�F�[�h�p�̃|���S���̓��ߐݒ�
	SetColor(0, 0, 0, alpha);
	// �t�F�[�h�p�̃|���S���`��
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	SetImage(NULL);
	CPolygon::Draw();
	// �ʏ�̐F�ݒ�ɖ߂�
	SetColor(1, 1, 1, 1);

}

// �t�F�[�h��������
bool Fade::IsFinish()
{
	return m_maxTime <= m_time;
}

// �t�F�[�h���s����
bool Fade::IsExecute()
{
	return m_maxTime > 0.0f;
}

// �t�F�[�h�J�n
void Fade::Start(float time, bool isOut)
{
	m_time = 0;
	m_maxTime = time;
	m_isOut = isOut;
}

