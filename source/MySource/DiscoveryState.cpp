////////////////////////////////////////////////////////////////////////////////////////////
// DiscoveryState.cpp
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 発見後に行うこと
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#include "DiscoveryState.h"
#include "ChaseState.h"
#include "PatrolState.h"
#include "Enemy.h"

void DiscoveryState::Init(CEnemy *enemy)
{
	ChangeState(enemy, ChaseState::GetInstance());
}

void DiscoveryState::Update(CEnemy *enemy)
{
	if (enemy->GetPath() == PATHS::BOSS)
	{
		if (enemy->IsDistanceToPlayer(400.0f, false))
		{
			// 階層状態の変更
			enemy->ChangeState(PatrolState::GetInstance());
		}
		else
		{
			// 子階層の更新
			enemy->m_ChildState->Update(enemy, DiscoveryState::GetInstance());
		}
	}
	else
	{
		if (enemy->IsDistanceToPlayer(DISTANCE, true))	//距離が遠くなると
		{
			// 階層状態の変更
			enemy->ChangeState(PatrolState::GetInstance());
		}
		else
		{
			// 子階層の更新
			enemy->m_ChildState->Update(enemy, DiscoveryState::GetInstance());
		}
	}

}

void DiscoveryState::ChangeState(CEnemy *enemy, State *new_state)
{
	enemy->ResetTime();
	enemy->m_ChildState = new_state;
	// 子階層更新
	enemy->m_ChildState->Init(enemy);
}
