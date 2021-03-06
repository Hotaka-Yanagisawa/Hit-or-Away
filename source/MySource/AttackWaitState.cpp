////////////////////////////////////////////////////////////////////////////////////////////
// AttackWaitState.cpp
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 攻撃後に行うこと
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
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
			//再度攻撃するか追うか
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
			//再度攻撃するか追うか
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