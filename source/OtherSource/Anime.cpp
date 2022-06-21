///////////////////////////////////////
// Anime.cpp
//-------------------------------------
// 2020/09/03	�쐬
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "Anime.h"

//--- �X�V
void CAnime::Update()
{
	//--- �A�j���̍X�V
	// �Đ�����Ă���
	if (m_Status == ANIM_STATUS::PLAY)
	{
		// �J�E���g
		m_nCount++;
		// ��莞�Ԍo�߂�����e�N�X�`����؂�ւ���
		if (m_nCount > m_nPace)
		{
			// �A�j�����������
			if ((m_TexCoord.x == m_End.x)
				&& (m_TexCoord.y == m_End.y))
			{
				if (m_bLoop)	// �A�j���̐擪�ɖ߂�
				{
					m_TexCoord.x = (float)m_Start.x;
					m_TexCoord.y = (float)m_Start.y;
				}
				else			// ���[�v���I���
				{
					m_Status = ANIM_STATUS::END;
				}

				// �ȉ��̏��������Ȃ�
				m_nCount = 0;
				return;
			}

			// ���̃e�N�X�`��
			m_TexCoord.x++;

			// �[�܂ł���������ς���
			if (m_TexCoord.x >= m_Split.x)
			{
				m_TexCoord.x = 0.0f;
				m_TexCoord.y += 1.0f;
			}
			// �I�[�܂ł�������ŏ��ɖ߂�
			if (m_TexCoord.y >= m_Split.y)
				m_TexCoord.y = 0.0f;

			// �A�j���J�E���g���Z�b�g
			m_nCount = 0;
		}
	}

	// �|���S���̍X�V
	CPolygon::Update();
}

//--- �`��
void CAnime::Draw()
{
	// �|���S���̕`��
	CPolygon::Draw();
}

//--- �A�j���ݒ�
void CAnime::SetAnime(int StartX, int StartY, int Num, int Pace, bool Loop)
{
	if (m_Status == ANIM_STATUS::PLAY) return;

	m_Start = { StartX, StartY };	// �J�n�ʒu
	// �I���ʒu���v�Z
	int EndX = (StartX + (Num - 1)) % (int)m_Split.x;
	int EndY = (int)(StartY + ((StartX + (Num - 1)) / m_Split.x));
	m_End = { EndX, EndY };			// �I���ʒu
	m_nPace = Pace;					// �Đ����x
	m_nCount = 0;					// �J�E���^	
	m_bLoop = Loop;					// ���[�v
	m_Status = ANIM_STATUS::PLAY;			// �A�j�����J�n

	// �A�j���̍ŏ�
	m_TexCoord.x = (float)m_Start.x;
	m_TexCoord.y = (float)m_Start.y;
}

//--- �A�j���Đ���~
void CAnime::Play(bool Play)
{
	// �A�j�����ݒ肳��Ă��Ȃ�
	if (m_Status == ANIM_STATUS::NO) return;

	if (Play)
		m_Status = ANIM_STATUS::PLAY;
	else
		m_Status = ANIM_STATUS::STOP;
}

//--- �A�j���̏�Ԏ擾
ANIM_STATUS CAnime::isPlay()
{
	return m_Status;
}


