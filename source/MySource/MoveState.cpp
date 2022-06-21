////////////////////////////////////////////////////////////////////////////////////////////
// MoveState.cpp
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �ړ���ԂɊւ��邱��
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////

#include "MoveState.h"
#include "WaitState.h"
#include "HierarchyState.h"
#include "Enemy.h"

void MoveState::Init(CEnemy *enemy)
{
}

void MoveState::Update(CEnemy *enemy, HierarchyState *parent)
{
	int time = enemy->AddTime(1);

	if (enemy->Paths(enemy->GetPath(), time))
	{
		parent->ChangeState(enemy, WaitState::GetInstance());
	}
}
