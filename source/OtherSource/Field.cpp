///////////////////////////////////////////
// Field.cpp
//-----------------------------------------
// 2020/08/05	�쐬
//		08/10	BackGround����ړ�
//
///////////////////////////////////////////

//--- �C���N���[�h��
#include "Field.h"
#include "Game.h"
#include "Camera.h"
#include "Keyboard.h"

//--- �萔
#define FILE_FIELD	("Image/Steppe.png")

//--- �O���[�o���ϐ�
VECTOR2<> CField::m_fSize;
E_FIELD	CField::m_Type;

//--- �R���X�g���N�^
CField::CField()
{

}

//--- �f�X�g���N�^
CField::~CField()
{

}

//--- ������
void CField::Init(E_FIELD Type, float SizeX, float SizeY)
{
	m_Type = Type;
	// �摜�ǂݍ���
	switch (Type)
	{
	case E_FIELD::STEPPE:
		SetImage(FILE_FIELD);
		break;
	case E_FIELD::ICE:
		SetImage("Image/Ice.png");
		break;

	default:
		break;
	}

	// �L���ݒ�
	m_fSize = { SizeX, SizeY };
	SetPos(m_fSize.x * 100 / 2, m_fSize.y * 100 / 2);
	SetSize(m_fSize.x * 100, m_fSize.y * 100);
	
}

//--- �I��
void CField::Uninit()
{

}

//--- �X�V
void CField::Update()
{
	// �J�������f
	SetPos(m_fSize.x * 100 / 2 - GetCamera()->GetPosX(),
		m_fSize.y * 100 / 2 - GetCamera()->GetPosY());

	// �|���S���̍X�V
	CPolygon::Update();

}

//--- �`��
void CField::Draw()
{
	// �|���S���̕`��
	CPolygon::Draw();

}



