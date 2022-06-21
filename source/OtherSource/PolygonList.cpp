
//--- �C���N���[�h��
#include "PolygonList.h"
#include "Polygon.h"
#include <Windows.h>

//--- �R���X�g���N�^
CPolygonList::CPolygonList()
{

}

//--- �f�X�g���N�^
CPolygonList::~CPolygonList()
{

}

//--- ������
void CPolygonList::Init()
{
	m_pListTop = NULL;
}

//--- �I��
void CPolygonList::Uninit()
{
	// ���X�g�����
	POLYGON_LIST* p = m_pListTop;
	POLYGON_LIST* temp;

	while (p != NULL)
	{
		temp = p->Next;
		delete(p->Data);
		free(p);
		p = temp;
	}

	m_pListTop = NULL;
}

//--- �X�V
void CPolygonList::Update()
{
	POLYGON_LIST *p;

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
void CPolygonList::Draw()
{
	POLYGON_LIST *p;

	// �擪�A�h���X������s
	p = m_pListTop;
	while (p != NULL)
	{
		p->Data->Draw();
		p = p->Next;
	}
}

//--- ���X�g�ɒǉ�
CPolygon* CPolygonList::Add(CPolygon* pCPolygon)
{
	POLYGON_LIST *p;

	// �������̊m��
	p = (POLYGON_LIST*) malloc(sizeof(POLYGON_LIST));

	// �f�[�^��o�^
	p->Data = pCPolygon;

	// �|�C���^�̂Ȃ�����
	p->Next = m_pListTop;
	m_pListTop = p;

	return m_pListTop->Data;
}

//--- ���X�g�������
void CPolygonList::Delete(CPolygon* pCPolygon)
{
	POLYGON_LIST *p;
	POLYGON_LIST *temp;
	// �擪�A�h���X������s
	p = m_pListTop;

	while (p->Next->Data != pCPolygon)
	{
		p = p->Next;
	}

	temp = p->Next;
	p->Next = temp->Next;

	delete temp->Data;
}

//--- ���O�Ō���
CPolygon* CPolygonList::SearchName(const char* Name)
{
	POLYGON_LIST* p;

	// �擪�A�h���X������s
	p = m_pListTop;
	while (p != NULL)
	{
		char* Tname = p->Data->GetName();
		if (!strcmp(Tname, Name)) break;
		p = p->Next;
	}

	if (p == NULL) return m_pListTop->Data;
	return p->Data;
}
