////////////////////////////////////////////////////////////////////////////////////////////
// PatrolState.cpp
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ���G�E����Ɋւ��邱��
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
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

	// �G�𔭌�
	if (enemy->IsDistanceToPlayer(DISTANCE, false))
	{
		// �K�w��Ԃ𔭌��ɕύX
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
