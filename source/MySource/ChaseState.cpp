////////////////////////////////////////////////////////////////////////////////////////////
// ChaseState.cpp
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 攻撃後に行うこと
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
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
		// 攻撃に移るか追い続けるか
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
		// ボスなら追わずに攻撃へ移る
		parent->ChangeState(enemy, AttackState::GetInstance());
	}
}
