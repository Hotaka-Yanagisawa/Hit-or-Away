////////////////////////////////////////////////////////////////////////////////////////////
// AttackWaitState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �U����ɍs������
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "State.h"

//class CEnemy;

class AttackWaitState : public State
{
public:
	static AttackWaitState *GetInstance()
	{
		static AttackWaitState instance;
		return &instance;
	}

	virtual ~AttackWaitState() {}
	virtual void Init(CEnemy*);
	virtual void Update(CEnemy*, HierarchyState *parent);

private:
	AttackWaitState() {}
};