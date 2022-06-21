//////////////////////////////////////////////////
// Object.cpp
//------------------------------------------------
// 2020/07/17	�쐬
//		07/20	ObjNum�ǉ�
//		07/26	�^�O�ǉ�
//
//////////////////////////////////////////////////

//--- �C���N���[�h��
#include "Object.h"
#include "ObjectList.h"
#include "Camera.h"
#include "Game.h"

#include "Field.h"

//--- �ÓI�����o�ϐ�
int CObject::m_nObjNum = 0;

//--- �R���X�g���N�^
CObject::CObject()
{
	// �X�e�[�^�X�̏�����
	m_Move = { 0.0f, 0.0f };
	m_Timer = 0;
	m_bExist = true;
	m_bHit = true;
	m_Tag = E_OBJ::MAX;
	// �I�u�W�F�N�g���J�E���g
	m_nObjNum++;

}

//--- �f�X�g���N�^
CObject::~CObject()
{
	Destroy();
	m_nObjNum--;
}

//--- �X�V
void CObject::Update()
{
	if (!m_bExist) return;	// ���݂��Ȃ�

	// �ړ��ʂ̍X�V
	m_Position.x += m_Move.x;
	m_Position.y += m_Move.y;

	// �J�����𔽉f
	m_Animation.SetPos(m_Position.x - GetCamera()->GetPosX(),
		m_Position.y - GetCamera()->GetPosY());

	// �A�j���̍X�V
	m_Animation.Update();

}

//--- �`�� 
void CObject::Draw()
{
	if (!m_bExist) return;	// ���݂��Ȃ�

	// �A�j���̕`��
	m_Animation.Draw();
}

//--- ���W�ݒ�
void CObject::SetPos(float PosX, float PosY)
{
	m_Position = { PosX, PosY };
}

//--- �ړ��ʐݒ�
void CObject::SetMove(float MoveX, float MoveY)
{
	m_Move = { MoveX, MoveY };
}

//--- ��ސݒ�
void CObject::SetTag(E_OBJ Type)
{
	m_Tag = Type;
}

//--- ����
void CObject::Destroy()
{
	m_bExist = false;
	m_bHit = false;
}

//--- ���W�擾
VECTOR2<> CObject::GetPos()
{
	return m_Position;
}

//--- �ړ��ʎ擾
VECTOR2<> CObject::GetMove()
{
	return m_Move;
}

//--- ��ގ擾
E_OBJ CObject::GetType()
{
	if (!this) return E_OBJ::MAX;
	return m_Tag;
}

//--- �I�u�W�F�N�g�̐��擾
int CObject::GetObjNum()
{
	return m_nObjNum;
}

//--- �����蔻��
CObject* CObject::Hit(float LooseX, float LooseY)
{
	//�����̓����蔻�肪�����ꍇ
	if (!m_bHit)	return NULL;

	// ���X�g���擾
	OBJECT_LIST* pList = CObjectList::GetList();

	// �����蔻��D�揇�ʂŕ��ёւ�
	CObjectList::Sort(SORT::TAG);

	// ���ԂɏՓ˔���
	pList = CObjectList::GetList();
	for (int i = 0; i < m_nObjNum; i++, pList = pList->Next)
	{
		CObject* Target = pList->Data;
		// �����蔻�薳��
		if (!Target->m_bHit) continue;
		if (!Target->m_bExist) continue;
		if (Target->m_Tag == m_Tag) continue;

		//--- ��`����
		VECTOR2<> half1 = { m_Animation.GetSize().x / 2, m_Animation.GetSize().y / 2 };
		VECTOR2<> half2 = { Target->m_Animation.GetSize().x / 2, Target->m_Animation.GetSize().y / 2 };
		// �ڂ����Ƃ��̋���
		float distX = GetPos().x - Target->GetPos().x;
		if (distX < 0) distX *= -1;
		float distY = GetPos().y - Target->GetPos().y;
		if (distY < 0) distY *= -1;
		// ����
		if ((distX < half1.x + half2.x * LooseX)
			&& (distY < half2.y + half2.y * LooseY))
		{
			return Target;
		}
		// �������ĂȂ�
		else continue;

		break;
	}

	return NULL;
}
