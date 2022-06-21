
#pragma once

//--- �C���N���[�h��
#include "Polygon.h"
#include "Pattern.h"

//--- ���X�g
using POLYGON_LIST = LIST<CPolygon*>;

//--- �N���X
class CPolygonList
{
public:

	CPolygonList();	// �R���X�g���N�^
	~CPolygonList();	// �f�X�g���N�^

	CPolygon* Add(CPolygon*);	// ���X�g�ɒǉ�
	void Delete(CPolygon*);		// ���X�g�������

	void Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	POLYGON_LIST* GetList() { return m_pListTop; };
	CPolygon* SearchName(const char* Name);	// ���O�Ō���

private:

	POLYGON_LIST* m_pListTop;	// ���X�g�̐擪�A�h���X

};

