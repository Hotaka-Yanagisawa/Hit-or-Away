////////////////////////////////////////
// Bullet.h
//--------------------------------------
// 2020/09/03	�쐬
//
////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Object.h"

//--- �񋓑�
enum class E_BULLET		// ���
{
	NORMAL,

	MAX
};

//--- �N���X
class CBullet : public CObject
{
public:

	CBullet(E_BULLET, float PosX, float PosY, float MoveX, float MoveY);
	~CBullet();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

	E_BULLET GetType()
	{
		return m_Type;
	}

private:

	E_BULLET m_Type;	// ���

};
