////////////////////////////////////////////////////////////////////////////////////////////
// AttackState.cpp
//----------------------------------------------------------------------------------------
// ì¬ŽÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// UŒ‚Žž‚És‚¤‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#include "AttackState.h"
#include "AttackWaitState.h"
#include "Enemy.h"

void AttackState::Init(CEnemy* enemy)
{
	
}

void AttackState::Update(CEnemy* enemy, HierarchyState *parent)
{
	int time = enemy->AddTime(1);

	if (enemy->GetPath() == PATHS::BOSS)
	{
		enemy->RandomCreateEnemy(time);
	}
	if (time > 10)
	{
		parent->ChangeState(enemy, AttackWaitState::GetInstance());
	}
}
