// Camera.h

#pragma once

//--- �C���N���[�h��
#include <Windows.h>
#include "Object.h"

class Camera
{
public:

	HRESULT Init();
	void Uninit();
	void Update();

	float GetPosX();
	float GetPosY();
	
	void Shake(int nTime);	// �h�炷

private:

	// �J�����̍��W
	float m_posX;
	float m_posY;

	int m_nTime;	// �h�炵����

	// ����W
	CObject* m_baseObj;
};

// �J�����̏����擾���邽�߂̊֐�
Camera* GetCamera();

