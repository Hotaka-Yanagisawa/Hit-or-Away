//////////////////////////////////////////////////////////////////////////////////////////
// Enemy.h
//-------------------------------------
// �쐬�ҁFAT12D_35_���򔿋M
//-------------------------------------
// 2020/07/20	�쐬
// 2020/07/26	�����o�ϐ��𑝂₵��
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

//--- �C���N���[�h��
#include "Object.h"
#include <stdio.h>
#include "MySound.h"
#include "HierarchyState.h"


//--- �萔��`
//#define MAX_ENEMY (20)

class CPlayer;


//--- �񋓑�
enum class E_ENEMY		// �G�̎��
{
	SLIME = 1,
	RED_SLIME,
	GHOST,
	HIGH_GHOST,
	KING,

	MAX
};

enum PATHS
{
	STOP,					//�Î~
	UP_AND_DOWN,			//�㉺
	LEFT_AND_RIGHT,			//���E
	UP_DOWN_LEFT_RIGHT,		//�㉺���E
	RUSH_AND_REST,			//�ːi�Ƌx��
	TERESA,					//�e���T�݂����ȓ���
	TARGET_PLAYER,			//�v���C���[��ǂ��Ă���
	TARGET_PLAYER_AND_RETURN,			//�v���C���[��ǂ��Ă���
	BOSS,

	MAX_PATHS,
};



//--- �N���X
class CEnemy : public CObject
{
public:
	enum MOVE_VEC
	{
		LEFT = (1 << 0),	// ��
		RIGHT = (1 << 1),	// �E
		UP = (1 << 2),	// ��
		DOWN = (1 << 3),	// ��
	};

	CEnemy(CPlayer *, HierarchyState *, PATHS, float, float);		// �R���X�g���N�^
	~CEnemy();	// �f�X�g���N�^

	static void Init();
	void Update();	// �X�V
	void Draw();	// �`��

	static int GetNum();	// ���擾
	static void ResetNum();	// ��������

	bool Paths(PATHS Pattern, int time);

	// ��Ԑ؂�ւ�
	void ChangeState(HierarchyState *state);
	// �v���C���[�Ƃ̋����`�F�b�N
	bool IsDistanceToPlayer(float distance, bool is_out_side);
	// �ړ�
	void Move(int vec);
	// �ǐ�
	void Chase();
	// ��ʒu�ɋA��
	bool Return();
	bool UpAndDown(int);
	bool LeftAndRight(int);
	bool UDAndLR(int);

	void RandomCreateEnemy(int);
	void RandomCreateEnemy();

	bool Escape(int);

	int AddTime(int add);
	void ResetTime();
	E_ENEMY GetEnemyType();
	PATHS   GetPath();

	State *m_ChildState;

private:
	void UpdateDestroyFade();
	void SetCharacter(PATHS Path);
	void SetType(E_ENEMY Type);

	// �v���C���[�Ƃ̋����擾
	float GetDistance();

	static int row;		//���ɓǂݍ��ޗ�ԍ�

	static int m_nNum;	// ���݂��鐔

	E_ENEMY			m_Type;			// ���
	PATHS			m_Path;			// �ړ����[�g�̎��
	int				m_nHp;			// �̗�
	int				m_stopTime;		// ��~����
	int				m_moveTime;		// �ړ�����
	float			m_fSpd;			// ����
	float			m_fadeCnt;		// ���S���̃t�F�[�h�J�E���^�[
	float			m_DeltaTime;	// ���S���̎��Ԓ���
	bool			m_bDestroy;		// ���S����
	float			m_fDestroyCnt;	// ���ԍ��œ|���悤��
	static bool		m_bBoss;		// �{�X���|�ꂽ��true		

	VECTOR2<> m_FixedPos;	// ��ʒu

	CPlayer *m_Player;			//�v���C���[
	HierarchyState *m_State;	//���
	static CSound sound;

};
