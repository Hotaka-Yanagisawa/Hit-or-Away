////////////////////////////////////////////////////////////////////////////////////////////
// PatrolState.cpp
//----------------------------------------------------------------------------------------
// ì¬ŽÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// õ“GE„‰ñ‚ÉŠÖ‚·‚é‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////
#include "PatrolState.h"
#include "DiscoveryState.h"
#include "WaitState.h"
#include "MoveState.h"
#include "Enemy.h"

void PatrolState::Init(CEnemy *enemy)
{
	ChangeState(enemy, MoveState::GetInstance());
}

void PatrolState::Update(CEnemy *enemy)
{
	if (enemy->GetPath() == PATHS::BOSS) 
	{
		if (enemy->IsDistanceToPlayer(400.0f, true))
		{
			enemy->ChangeState(DiscoveryState::GetInstance());
			return;
		}
		else
		{
			enemy->m_ChildState->Update(enemy, PatrolState::GetInstance());
			return;
		}
	}

	// “G‚ð”­Œ©
	if (enemy->IsDistanceToPlayer(DISTANCE, false))
	{
		// ŠK‘wó‘Ô‚ð”­Œ©‚É•ÏX
		enemy->ChangeState(DiscoveryState::GetInstance());
	}
	else 
	{
		enemy->m_ChildState->Update(enemy, PatrolState::GetInstance());
	}
}

void PatrolState::ChangeState(CEnemy *enemy, State *state)
{
	enemy->ResetTime();
	enemy->m_ChildState = state;
	enemy->m_ChildState->Init(enemy);
}
