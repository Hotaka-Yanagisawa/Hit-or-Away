///////////////////////////////////////
// ObjectMgr.h
//-------------------------------------
// 2020/07/28	�쐬
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Object.h"
#include "ObjectList.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Gimmick.h"
#include "Item.h"

//--- �I�u�W�F�N�g���Ǘ�����N���X
class ObjectManager
{
public:

	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �I�u�W�F�N�g�̐���
	void CreatePlayer(E_PLAYER, float x, float y);
	void CreateBullet(E_BULLET, float x, float y, float mx, float my);
	void CreateEnemy(PATHS path, float x, float y);
	void CreateGimmick(E_GIMMICK Type, float x, float y);
	void CreateItem(E_ITEM Type, float x, float y);

	void DestroyObject(CObject*);	// �I�u�W�F�N�g����(�|�C���^)
	void DestroyObject(E_OBJ);		// �I�u�W�F�N�g����(�^�O)

private:

	CObjectList m_List;	// �I�u�W�F�N�g���X�g

};

