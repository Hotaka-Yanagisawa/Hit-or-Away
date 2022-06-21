////////////////////////////////////////////////////////////////////////////////////////////
// AttackWaitState.cpp
//----------------------------------------------------------------------------------------
// ì¬ŽÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// UŒ‚Œã‚És‚¤‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
			//Ä“xUŒ‚‚·‚é‚©’Ç‚¤‚©
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
			//Ä“xUŒ‚‚·‚é‚©’Ç‚¤‚©
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