////////////////////////////////////////////////////////////////////////////////////////////
// DiscoveryState.cpp
//----------------------------------------------------------------------------------------
// ì¬ŽÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ”­Œ©Œã‚És‚¤‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
			// ŠK‘wó‘Ô‚Ì•ÏX
			enemy->ChangeState(PatrolState::GetInstance());
		}
		else
		{
			// ŽqŠK‘w‚ÌXV
			enemy->m_ChildState->Update(enemy, DiscoveryState::GetInstance());
		}
	}
	else
	{
		if (enemy->IsDistanceToPlayer(DISTANCE, true))	//‹——£‚ª‰“‚­‚È‚é‚Æ
		{
			// ŠK‘wó‘Ô‚Ì•ÏX
			enemy->ChangeState(PatrolState::GetInstance());
		}
		else
		{
			// ŽqŠK‘w‚ÌXV
			enemy->m_ChildState->Update(enemy, DiscoveryState::GetInstance());
		}
	}

}

void DiscoveryState::ChangeState(CEnemy *enemy, State *new_state)
{
	enemy->ResetTime();
	enemy->m_ChildState = new_state;
	// ŽqŠK‘wXV
	enemy->m_ChildState->Init(enemy);
}
