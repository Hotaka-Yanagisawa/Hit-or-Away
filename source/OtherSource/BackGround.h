///////////////////////////////////////
// BackGround.h
//-------------------------------------
// 2020/07/20	�쐬
//		08/10	Field�Ɉړ�
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Polygon.h"

//--- �N���X
class CBackGround : public CPolygon
{
public:

	CBackGround();	// �R���X�g���N�^
	~CBackGround();	// �f�X�g���N�^

	void Update();	// �X�V
	void Draw();	// �`��

private:

	VECTOR2<> m_Coord;

};

