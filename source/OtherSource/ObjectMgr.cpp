///////////////////////////////////////
// ObjectMgr.cpp
//-------------------------------------
// 2020/07/28	�쐬
//
///////////////////////////////////////

//--- �C���N���[�h��
#include "ObjectMgr.h"
#include "ObjectList.h"

#include "Player.h"
#include "Enemy.h"
#include "PatrolState.h"

CPlayer* pPlayer;

//--- ������
void ObjectManager::Init()
{
	// ���X�g�̃I�u�W�F�N�g������
	m_List.Init();
}

//--- �I��
void ObjectManager::Uninit()
{
	// ���X�g�̃I�u�W�F�N�g�I��
	m_List.Uninit();

}

//--- �X�V
void ObjectManager::Update()
{
	// ���X�g�̃I�u�W�F�N�g�X�V
	m_List.Update();

}

//--- �`��
void ObjectManager::Draw()
{
	// ���X�g��Y���W�����Ń\�[�g
	//m_List.Sort(SORT::Y);
	// ���X�g�̃I�u�W�F�N�g�`��
	m_List.Draw();

}

//--- �I�u�W�F�N�g����
void ObjectManager::CreatePlayer(E_PLAYER Type, float x, float y)
{
	pPlayer = new CPlayer(Type, x, y);
	m_List.Add(pPlayer);
}
void ObjectManager::CreateBullet(E_BULLET Type, float x, float y, float mx, float my)
{
	CBullet* pBullet = new CBullet(Type, x, y, mx, my);
	m_List.Add(pBullet);
}
void ObjectManager::CreateEnemy(PATHS path, float x, float y)
{
	CEnemy* pEnemy = new CEnemy(pPlayer, PatrolState::GetInstance(), path, x, y);
	m_List.Add(pEnemy);
}
void ObjectManager::CreateGimmick(E_GIMMICK Type, float x, float y)
{
	CGimmick* pGimmick = new CGimmick(Type, x, y);
	m_List.Add(pGimmick);
}
void ObjectManager::CreateItem(E_ITEM Type, float x, float y)
{
	CItem* pItem = new CItem(Type, x, y);
	m_List.Add(pItem);
}

//--- �I�u�W�F�N�g�̏���(�|�C���^)
void ObjectManager::DestroyObject(CObject* pObj)
{
	OBJECT_LIST* p = CObjectList::GetList();

	// ��������f�[�^�܂Ń��X�g��H��
	while (p->Next != NULL && p->Next->Data != pObj) p = p->Next;

	// �|�C���^���Ȃ��ς���
	OBJECT_LIST* temp;
	temp = p->Next;		// ���|�C���^�����u��
	p->Next = temp->Next;	// �Ȃ��ς���

	// �f�[�^���폜
	delete temp->Data;
	free(temp);

}
//--- �I�u�W�F�N�g�̏���(�^�O)
void ObjectManager::DestroyObject(E_OBJ Type)
{
	OBJECT_LIST* p = CObjectList::GetList();

	// ��������f�[�^�܂Ń��X�g��H��
	while (p->Next != NULL && p->Next->Data->GetType() != Type) p = p->Next;

	// �f�[�^����
	if (p->Next == NULL) return;

	// �|�C���^���Ȃ��ς���
	OBJECT_LIST* temp;
	temp = p->Next;			// ���|�C���^�����u��
	p->Next = temp->Next;	// �Ȃ��ς���

	// �f�[�^���폜
	delete temp->Data;
	free(temp);
}

