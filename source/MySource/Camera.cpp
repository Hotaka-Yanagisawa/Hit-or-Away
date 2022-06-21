////////////////////////////////////
// Camera.cpp
//プレイヤーを中心にカメラを作成　柳
////////////////////////////////////

//--- インクルード部
#include "Camera.h"
#include "Player.h"
#include "Game.h"
#include "ObjectList.h"
#include "Keyboard.h"

//---グローバル変数
Camera g_camera;

//--- 初期化
HRESULT Camera::Init()
{
	m_posX = 0.0f;
	m_posY = 0.0f;

	//プレイヤーの位置が基準
	OBJECT_LIST* List = CObjectList::GetList();
	while (List->Data->GetType() != E_OBJ::PLAYER)
	{
		List = List->Next;
	}
	m_baseObj = List->Data;

	return S_OK;
}

//--- 終了
void Camera::Uninit()
{

}

//--- 更新
void Camera::Update()
{
	// 基準座標が中央
	m_posX = m_baseObj->GetPos().x - SCREEN_WIDTH * 0.5f;
	m_posY = m_baseObj->GetPos().y - SCREEN_HEIGHT * 0.5f;

	// 揺らし
	if (m_nTime > 0)
	{
		m_nTime--;
		m_posX += m_nTime % 3 * 5;
		m_posY += m_nTime + 1 % 3 * 5;
	}

}

//--- カメラの座標X
float Camera::GetPosX()
{
	return m_posX;
}

//--- カメラの座標Y
float Camera::GetPosY()
{
	return m_posY;
}

//--- 画面揺らし
void Camera::Shake(int Time)
{
	m_nTime = Time;
}

//--- カメラの情報を取得するための関数
Camera* GetCamera()
{
	return &g_camera;
}
