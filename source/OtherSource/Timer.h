///////////////////////////////////////////
// Timer.h
//-----------------------------------------
// 2020/07/25	�쐬
//		08/29	Init�Ɉ����ǉ�
//
///////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Polygon.h"

//--- �N���X
class CTimer
{
public:

	void Init(int Num);
	void Uninit();
	bool Update();
	void Draw();

private:

	int m_nCount;	//�^�C�}�[�̃J�E���^
	CPolygon* m_polygon;
	CPolygon* m_timer;

};

