////////////////////////////////////
// Camera.cpp
//�v���C���[�𒆐S�ɃJ�������쐬�@��
////////////////////////////////////

//--- �C���N���[�h��
#include "Camera.h"
#include "Player.h"
#include "Game.h"
#include "ObjectList.h"
#include "Keyboard.h"

//---�O���[�o���ϐ�
Camera g_camera;

//--- ������
HRESULT Camera::Init()
{
	m_posX = 0.0f;
	m_posY = 0.0f;

	//�v���C���[�̈ʒu���
	OBJECT_LIST* List = CObjectList::GetList();
	while (List->Data->GetType() != E_OBJ::PLAYER)
	{
		List = List->Next;
	}
	m_baseObj = List->Data;

	return S_OK;
}

//--- �I��
void Camera::Uninit()
{

}

//--- �X�V
void Camera::Update()
{
	// ����W������
	m_posX = m_baseObj->GetPos().x - SCREEN_WIDTH * 0.5f;
	m_posY = m_baseObj->GetPos().y - SCREEN_HEIGHT * 0.5f;

	// �h�炵
	if (m_nTime > 0)
	{
		m_nTime--;
		m_posX += m_nTime % 3 * 5;
		m_posY += m_nTime + 1 % 3 * 5;
	}

}

//--- �J�����̍��WX
float Camera::GetPosX()
{
	return m_posX;
}

//--- �J�����̍��WY
float Camera::GetPosY()
{
	return m_posY;
}

//--- ��ʗh�炵
void Camera::Shake(int Time)
{
	m_nTime = Time;
}

//--- �J�����̏����擾���邽�߂̊֐�
Camera* GetCamera()
{
	return &g_camera;
}
