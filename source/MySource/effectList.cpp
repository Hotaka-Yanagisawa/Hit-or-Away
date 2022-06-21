//===================================================================
//
//	objectList.cpp
//	�I�u�W�F�N�g�̃��X�g�֘A
//
//
//-------------------------------------------------------------------
//	�쐬�ҁFAT12D 35 ���򔿋M
//-------------------------------------------------------------------
//	�J������
//	2020/08/17	�쐬
//  2020/09/01  ����̃v���W�F�N�g�p�ɉ���
//
//===================================================================

#include <math.h>
#include "effectList.h"

EFFECT_LIST* pDummyHead = NULL;	// �擪�m�[�h
EFFECT_LIST* pDummyTail = NULL;	// �����m�[�h



CEffectList::CEffectList()
{
	
}

CEffectList::~CEffectList()
{

}

/////////////////////////////////
//
// ���X�g�̐擪�Ɩ����̍쐬
//
////////////////////////////////
void CEffectList::Init()	
{
	pDummyHead = (EFFECT_LIST*)malloc(sizeof(EFFECT_LIST));
	//�m�[�h�̒l��ݒ肵�đO��̃m�[�h��������
	pDummyHead->Data = NULL;
	pDummyHead->Next = NULL;
	pDummyHead->Prev = NULL;

	pDummyTail = (EFFECT_LIST*)malloc(sizeof(EFFECT_LIST));
	//�m�[�h�̒l��ݒ肵�đO��̃m�[�h��������
	pDummyTail->Data = NULL;
	pDummyTail->Next = NULL;
	pDummyTail->Prev = pDummyHead;

	pDummyHead->Next = pDummyTail;
}



////////////////////////////////////////
//
// �X�V
//
////////////////////////////////////////
bool CEffectList::Update()
{
	EFFECT_LIST* pNode = pDummyHead->Next;

	while (pNode != pDummyTail)
	{
		pNode->Data->Update();

		//�g�p�ςȂ�폜
		if (pNode->Data->isPlay() == ANIM_STATUS::END)
		{
			EFFECT_LIST* temp = pNode;
			pNode = pNode->Next;
			CEffectList::Remove(temp);
			continue;
		}
		pNode = pNode->Next;
	}
	return false;
}




////////////////////////////////////////
//
// �`��
//
////////////////////////////////////////
void CEffectList::Draw()
{
	EFFECT_LIST* pNode = pDummyHead->Next;

	while (pNode != pDummyTail)
	{
		pNode->Data->Draw();
		pNode = pNode->Next;
	}
}




////////////////////////////////////////
//
// ���X�g�̒ǉ�
//
////////////////////////////////////////
Effect* CEffectList::Add(Effect* pEffect)	//���Ԃ񊮐�
{
	//�m�[�h�̃��������m�ۂ���
	EFFECT_LIST* pNode = (EFFECT_LIST*)malloc(sizeof(EFFECT_LIST));

	//�m�[�h�̒l��ݒ肵�đO��̃m�[�h��������
	pNode->Data  = pEffect;
	pNode->Next = NULL;
	pNode->Prev = NULL;

	//�_�~�[�ȊO�̃m�[�h�������ꍇ
	if (pDummyHead->Next == pDummyTail)
	{
		pDummyHead->Next = pNode;
		pNode->Prev	  = pDummyHead;
		pDummyTail->Prev = pNode;
		pNode->Next      = pDummyTail;
		return NULL;
	}

	//�_�~�[�����������݂̖����̎��̃m�[�h�Ƃ��ēo�^
	pDummyTail->Prev->Next = pNode;
	//�_�~�[�������������̃m�[�h�Ƃ��ēo�^
	pNode->Prev = pDummyTail->Prev;
	//�����_�~�[�O�̃m�[�h�Ƃ��ēo�^
	pDummyTail->Prev = pNode;
	//�ǉ������m�[�h�̎��𖖔��_�~�[�ɂ���
	pNode->Next = pDummyTail;

	return pNode->Data;
}


////////////////////////////////////////
//
// ���X�g�̍폜
//
////////////////////////////////////////
void CEffectList::Remove(EFFECT_LIST* pNode)	
{	
	pNode->Prev->Next = pNode->Next;
	pNode->Next->Prev = pNode->Prev;

	free(pNode);
}

////////////////////////////////////////
//
// effect�̍쐬
//
////////////////////////////////////////
void CEffectList::CreateEffect(float x, float y, FX_KIND kind)
{
	Effect* pEffect = new Effect(kind, x, y);
	Add(pEffect);
}



////////////////////////////////////////
//
// ���X�g�̑S����
//
////////////////////////////////////////
void CEffectList::AllDelete(void)	
{
	for (EFFECT_LIST* p = pDummyHead; p != pDummyTail;)
	{
		EFFECT_LIST* temp = p;		
		p = p->Next;
		free(temp);
	}
}

////////////////////////////////////////
//
// ���X�g�̐擪�A�h���X�擾
//
////////////////////////////////////////
EFFECT_LIST* CEffectList::GetList()
{
	return pDummyHead->Next;
}