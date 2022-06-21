////////////////////////////////////////
// Act.h
//--------------------------------------
// 2020/09/02	�쐬
//		09/03	���s�A�j������
//
////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Object.h"

//--- �萔��`
#define MOVE_UP		(0)
#define MOVE_DOWN	(180)
#define MOVE_LEFT	(90)
#define MOVE_RIGHT	(270)

//--- �񋓑�
enum class E_DIRECT	// ����
{
	UP = 0,	// ��
	DOWN,	// ��
	LEFT,	// ��
	RIGHT,	// �E
	MAX
};

//--- �N���X
class CAct: public CObject
{
public:

	CAct();		// �R���X�g���N�^
	~CAct();	// �f�X�g���N�^

	virtual void Update();	// �X�V
	virtual void Draw();	// �`��

	// ���s�A�j���̐ݒ�
	void SetWalkAnime(int BaseX, int BaseY,int Num = 4)
	{
		m_AnimeBase = { BaseX, BaseY };
		m_nAnimeNum = Num;
	}

	// �ړ�
	void Move(float MoveX, float MoveY);	// �ړ��ʎw��
	void Move(float Angle);					// �p�x�w��

	void Lock(bool Lock = true) { m_bLockDirect = Lock; };	// �����Œ�

protected:

	int		m_nHp;		// �̗�
	int		m_nAttack;	// �U����
	float	m_fSpeed;	// �ړ����x

	E_DIRECT	m_Direct;	// �����Ă����

	//bool	m_bAttack;	// �U�����Ă�
	//int	m_nAtkCnt;	// �U�����Ă�J�E���g

	VECTOR2<int>	m_AnimeBase;	// ���UV���W
	int				m_nAnimeNum;	// �A�j���̃t���[����

private:

	static int m_nAnimeSpB;	// �A�j�����x�̊�{�l

	bool m_bLockDirect;		// �����Œ�

	void UpdateDirect();	// �ړ��ʂ�����������߂�

private:

	E_DIRECT	m_OldDirect;	// �����Ă�����

};
