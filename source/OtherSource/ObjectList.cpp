
//--- �C���N���[�h��
#include "ObjectList.h"
#include "Object.h"
#include <Windows.h>

OBJECT_LIST* CObjectList::m_pListTop;	// ���X�g�̐擪�A�h���X

//--- �R���X�g���N�^
CObjectList::CObjectList()
{

}

//--- �f�X�g���N�^
CObjectList::~CObjectList()
{

}

//--- ������
void CObjectList::Init()
{
	m_pListTop = NULL;
}

//--- �I��
void CObjectList::Uninit()
{
	// ���X�g�����
	OBJECT_LIST* p = m_pListTop;
	OBJECT_LIST* temp;

	while (p != NULL)
	{
		temp = p->Next;
		delete p->Data;
		free(p);
		p = temp;
	}

	m_pListTop = NULL;
}

//--- �X�V
void CObjectList::Update()
{
	OBJECT_LIST *p;

	//// ���݂��Ȃ��I�u�W�F�N�g������
	//p = m_pListTop;
	//while (p != NULL)
	//{
	//	if (p->Next == NULL) break;

	//	if (!p->Next->Data->GetExist())
	//	{
	//		OBJECT_LIST* temp = p->Next;
	//		p->Next = temp->Next;
	//		delete(temp);
	//	}
	//	p = p->Next;
	//}
	
	// �擪�A�h���X������s
	p = m_pListTop;
	while (p != NULL)
	{
		if (p->Data == nullptr) break;
		p->Data->Update();
		p = p->Next;
	}
}

//--- �`��
void CObjectList::Draw()
{
	OBJECT_LIST *p;

	// �擪�A�h���X������s
	p = m_pListTop;
	while (p != NULL)
	{
		p->Data->Draw();
		p = p->Next;
	}
}

//--- ���X�g�ɒǉ�
CObject* CObjectList::Add(CObject* pCObject)
{
	OBJECT_LIST *p;

	// �������̊m��
	p = (OBJECT_LIST*) malloc(sizeof(OBJECT_LIST));

	// �f�[�^��o�^
	p->Data = pCObject;

	// �|�C���^�̂Ȃ�����
	p->Next = m_pListTop;
	m_pListTop = p;

	return m_pListTop->Data;
}

//--- ���X�g�������
void CObjectList::Delete(CObject* pCObject)
{
	OBJECT_LIST *p;
	OBJECT_LIST *temp;
	// �擪�A�h���X������s
	p = m_pListTop;

	while (p->Next->Data != pCObject)
	{
		p = p->Next;
	}

	temp = p->Next;
	p->Next = temp->Next;

	delete temp->Data;
}

//--- ���X�g�擾
OBJECT_LIST* CObjectList::GetList()
{
	return m_pListTop;
}

//---  �\�[�g
void CObjectList::Sort(SORT Type)
{
	OBJECT_LIST *p;

	switch (Type)
	{
	case SORT::Y:
		// Y���W�����Ń\�[�g
		p = m_pListTop;
		while (p->Next != NULL)
		{
			float Y1 = p->Data->GetPos().y;
			float Y2 = p->Next->Data->GetPos().y;
			if (Y1 > Y2)
			{
				CObject* temp = p->Data;
				p->Data = p->Next->Data;
				p->Next->Data = temp;
			}
			p = p->Next;
		}
		break;

	case SORT::TAG:
		// �^�O�����Ń\�[�g
		p = m_pListTop;
		while (p->Next != NULL)
		{
			int Y1 = (int)p->Data->GetType();
			int Y2 = (int)p->Next->Data->GetType();
			if (Y1 > Y2)
			{
				CObject* temp = p->Data;
				p->Data = p->Next->Data;
				p->Next->Data = temp;
			}
			p = p->Next;
		}
		break;

	default:
		break;
	}
}
