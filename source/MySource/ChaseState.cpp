////////////////////////////////////////////////////////////////////////////////////////////
// ChaseState.cpp
//----------------------------------------------------------------------------------------
// ì¬ŽÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// UŒ‚Œã‚És‚¤‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
		// UŒ‚‚ÉˆÚ‚é‚©’Ç‚¢‘±‚¯‚é‚©
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
		// ƒ{ƒX‚È‚ç’Ç‚í‚¸‚ÉUŒ‚‚ÖˆÚ‚é
		parent->ChangeState(enemy, AttackState::GetInstance());
	}
}
