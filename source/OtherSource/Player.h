////////////////////////////////////////
// Player.h
//--------------------------------------
// 2020/07/18	�쐬
//		08/29	����m�F�p�̃t���O�ǉ�
//
////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Act.h"
#include "MySound.h"

//--- �萔��`
#define MAX_AP	(3)	// �A�C�e���ő及��

//--- �񋓑�
enum class E_PLAYER		// ���
{
	ARMOR = 1,
	THIEF,
	SNIPE,

	MAX
};

//--- �N���X
class CPlayer : public CAct
{
public:

	CPlayer(E_PLAYER, float x, float y);	// �R���X�g���N�^
	~CPlayer();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

	static int GetResult(void)
	{
		return m_bResult;
	}

	E_PLAYER GetPlayerType();
	static int GetSpecial();
	static bool GetCanAtk() { return m_bCharge; };
	static void SetSpecial(int val);

private:

	E_PLAYER	m_Type;		// ���
	static int	m_nSpecial;	// �L�������Ƃ̓���ȗv�f
	static bool	m_bCharge;	// �U���\�t���O
	static bool	m_bResult;	// ���ꂽ
	int			m_nAtkCnt;	// �U�����Ă�J�E���g

	CSound sound;
};
