// Camera.h

#pragma once

//--- インクルード部
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
	
	void Shake(int nTime);	// 揺らす

private:

	// カメラの座標
	float m_posX;
	float m_posY;

	int m_nTime;	// 揺らし時間

	// 基準座標
	CObject* m_baseObj;
};

// カメラの情報を取得するための関数
Camera* GetCamera();

