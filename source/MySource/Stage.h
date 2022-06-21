///////////////////////////////////////////
// Stage.h
//-----------------------------------------
// 2020/08/03	�쐬
//
//
///////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "ObjectMgr.h"
#include "Timer.h"
#include "Field.h"
#include "Gimmick.h"
#include "Item.h"
#include <vector>
#include <string>
#include "MySound.h"

using namespace std;

//--- �\����
typedef struct
{
	PATHS path;
	float x;
	float y;
}ENEMY_DATA;

typedef struct
{
	E_GIMMICK type;
	float x;
	float y;
}GIMMICK_DATA;

typedef struct
{
	E_ITEM type;
	float x;
	float y;
}ITEM_DATA;

//--- �񋓑�
enum class STAGE_ID	// �X�e�[�W���ʗp
{
	NO = -1,
	P_MOVE,
	P_ATTACK,
	P_ARMOR,
	P_THIEF,
	P_SNIPE,
	P_SWITCH,
	ICE1,
	SWITCH1,
	SPEED1,
	ICE2,
	SPEED2,
	SWITCH2,
	ICE3,
	SNIPE,
	BOSS,

	MAX
};
enum class CLEAR_TARGET	// �N���A����
{
	NO = -1,
	DEFEAT,		// �G��|��
	RECOVER,	// �������
	ESCAPE,		// �����c��
	REACH,		// ���B����

	MAX
};
enum class STAGE_RESULT	// ����
{
	NO = 0,
	CLEAR,
	MISS,

	MAX
};

// �\���̂���Z�߂ɂ��ăR���e�i�^�ɂ�������
typedef struct
{
	vector<ENEMY_DATA>    enemy;
	vector<GIMMICK_DATA>  gimmick;
	vector<ITEM_DATA>	  item;
}STAGE_DATA;

typedef struct
{
	E_FIELD fieldType;	// �X�e�[�W�̎��
	string loadPathName;	// path�� practice/ �Ȃ�
	float sizeX;			// �t�B�[���h�̃T�C�Y
	float sizeY;
	E_PLAYER playerType;	// �v���C���[�^�C�v
	float PlayerPosX;
	float PlayerPosY;
	int TimeNum;
	CLEAR_TARGET clearTarget;
}FILE_LOAD;

//--- �N���X
class CStage
{
public:

	CStage();	// �R���X�g���N�^
	~CStage();	// �f�X�g���N�^

	void Init(STAGE_ID);
	void Uninit();
	STAGE_RESULT Update();
	void Draw();

	static int	GetSpilit() { return m_nSpilit; };
	static void	SetSpilit(int v) { m_nSpilit += v; };

	static ObjectManager* GetObjMgr() { return m_pObject; };

private:

	CTimer* m_pTimer;
	CField* m_pField;

	CLEAR_TARGET m_ClearCondition;	// �N���A����
	static int m_nSpilit;

	static ObjectManager* m_pObject;	// �I�u�W�F�N�g�Ǘ����X�g

	STAGE_DATA m_Data;
	void LoadStageData(STAGE_ID);
	void LoadCsv();
	FILE_LOAD m_loadData;
	CSound sound;
};

