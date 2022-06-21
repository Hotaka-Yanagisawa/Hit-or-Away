////////////////////////////////////////////////////////////////////////////////////////////
// AttackWaitState.cpp
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �U����ɍs������
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#include "AttackWaitState.h"
#include "AttackState.h"
#include "ChaseState.h"
#include "Enemy.h"

void AttackWaitState::Init(CEnemy*)
{
	
}

void AttackWaitState::Update(CEnemy* enemy, HierarchyState *parent)
{
	int time = enemy->AddTime(1);

	if (enemy->GetPath() == PATHS::BOSS)
	{
		if (time > 10)
		{
			//�ēx�U�����邩�ǂ���
			if (enemy->IsDistanceToPlayer(DISTANCE, true))
			{
				parent->ChangeState(enemy, AttackState::GetInstance());
			}
			else
			{
				parent->ChangeState(enemy, ChaseState::GetInstance());
			}
		}
	}
	else
	{
		if (time > 10)
		{
			//�ēx�U�����邩�ǂ���
			if (enemy->IsDistanceToPlayer(2.0f, false))
			{
				parent->ChangeState(enemy, AttackState::GetInstance());
			}
			else
			{
				parent->ChangeState(enemy, ChaseState::GetInstance());
			}
		}
	}
}