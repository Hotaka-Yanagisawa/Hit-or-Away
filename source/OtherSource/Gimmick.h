///////////////////////////////////////
// Gimmick.h
//-------------------------------------
// 2020/07/30	�쐬
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Object.h"

//--- �񋓑�
enum class E_GIMMICK
{
	BOX,	// �󂹂��
	WALL,	// �󂹂Ȃ���
	ROCK,	// �V�[�t���ʂ��
	SWITCH,	// �X�C�b�`
	FLOOR,	// ��

	MAX
};

//--- �N���X
class CGimmick : public CObject
{
public:

	CGimmick(E_GIMMICK Type, float x = 0.0f, float y = 0.0f);
	~CGimmick();

	void Update();	// �X�V
	void Draw();	// �`��

	void Destroy();	// �j��

	static bool GetSwitch() { return m_bSwitch; };	// �X�C�b�`�̏��

private:

	E_GIMMICK	m_Type;		// ���
	static bool	m_bSwitch;	// �X�C�b�`

	bool m_bBreak;

};

