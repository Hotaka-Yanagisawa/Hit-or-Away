////////////////////////////////////////////////////////////////////////////////////////////
// MoveState.cpp
//----------------------------------------------------------------------------------------
// ì¬ŽÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ˆÚ“®ó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////

#include "MoveState.h"
#include "WaitState.h"
#include "HierarchyState.h"
#include "Enemy.h"

void MoveState::Init(CEnemy *enemy)
{
}

void MoveState::Update(CEnemy *enemy, HierarchyState *parent)
{
	int time = enemy->AddTime(1);

	if (enemy->Paths(enemy->GetPath(), time))
	{
		parent->ChangeState(enemy, WaitState::GetInstance());
	}
}
