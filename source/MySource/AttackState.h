////////////////////////////////////////////////////////////////////////////////////////////
// AttackState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �U�����ɍs������
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "State.h"

class AttackState : public State
{
public:
	static AttackState *GetInstance()
	{
		static AttackState instance;
		return &instance;
	}

	virtual ~AttackState() {}
	virtual void Init(CEnemy *);
	virtual void Update(CEnemy *, HierarchyState *parent);

private:
	AttackState() {}
};