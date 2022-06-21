////////////////////////////////////////////////////////////////////////////////////////////
// ChaseState.cpp
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �U����ɍs������
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#include "ChaseState.h"
#include "HierarchyState.h"
#include "PatrolState.h"
#include "AttackState.h"
#include "Enemy.h"

void ChaseState::Init(CEnemy *enemy)
{
	
}

void ChaseState::Update(CEnemy *enemy, HierarchyState *parent)
{
	if (enemy->GetPath() != PATHS::BOSS)
	{
		// �U���Ɉڂ邩�ǂ������邩
		if (enemy->IsDistanceToPlayer(2.0f, false))
		{
			parent->ChangeState(enemy, AttackState::GetInstance());
		}
		else
		{
			enemy->Chase();
		}
	}
	else
	{
		// �{�X�Ȃ�ǂ킸�ɍU���ֈڂ�
		parent->ChangeState(enemy, AttackState::GetInstance());
	}
}
