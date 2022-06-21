///////////////////////////////////////
// Object.h
//-------------------------------------
// 2020/07/17	�쐬
//		07/26	�^�O�ǉ�
//		07/30	�e�Q�b�^�[�ǉ�
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Anime.h"

//--- �񋓑�
enum class E_OBJ	// �I�u�W�F�N�g�̎��
{
	// �������蔻��̗D�揇��
	PLAYER,	// �v���C���[
	WALL,	// ��
	BOX,	// �󂹂��
	ROCK,	// ���蔲�������
	BULLET,	// �v���C���[�̍U��
	GIMICK,	// �M�~�b�N
	ITEM,	// �A�C�e��
	ENEMY,	// �G

	MAX		// �ݒ薳��
};

//--- �N���X
class CObject
{
public:

	CObject();	// �R���X�g���N�^
	virtual  ~CObject();	// �f�X�g���N�^

	virtual void Update();
	virtual void Draw();

	void SetPos(float PosX, float PosY);	// ���W�ݒ�
	void SetMove(float MoveX, float MoveY);	// �ړ��ʐݒ�
	void SetTag(E_OBJ);						// ��ސݒ�

	virtual void Destroy();		// ��ʂ������

	CAnime	m_Animation;	// �A�j���[�V����

	CObject* Hit(float = 1.0f, float = 1.0f);	// �����蔻��

	VECTOR2<> GetPos();		// ���W�擾
	VECTOR2<> GetMove();	// �ړ��ʎ擾
	E_OBJ GetType();		// ��ގ擾
	bool GetExist() { return m_bExist; };

	int GetObjNum();	// �I�u�W�F�N�g�̐��擾

protected:

	VECTOR2<>	m_Position;	// �ʒu
	VECTOR2<>	m_Move;		// �ړ���
	int		m_Timer;		// �^�C�}�[
	bool	m_bExist;		// ����
	bool	m_bHit;			// �����蔻��
	E_OBJ	m_Tag;			// ���

private:

	static int m_nObjNum;
	
};

