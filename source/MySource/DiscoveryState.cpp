////////////////////////////////////////////////////////////////////////////////////////////
// DiscoveryState.cpp
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ������ɍs������
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
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
			// �K�w��Ԃ̕ύX
			enemy->ChangeState(PatrolState::GetInstance());
		}
		else
		{
			// �q�K�w�̍X�V
			enemy->m_ChildState->Update(enemy, DiscoveryState::GetInstance());
		}
	}
	else
	{
		if (enemy->IsDistanceToPlayer(DISTANCE, true))	//�����������Ȃ��
		{
			// �K�w��Ԃ̕ύX
			enemy->ChangeState(PatrolState::GetInstance());
		}
		else
		{
			// �q�K�w�̍X�V
			enemy->m_ChildState->Update(enemy, DiscoveryState::GetInstance());
		}
	}

}

void DiscoveryState::ChangeState(CEnemy *enemy, State *new_state)
{
	enemy->ResetTime();
	enemy->m_ChildState = new_state;
	// �q�K�w�X�V
	enemy->m_ChildState->Init(enemy);
}
