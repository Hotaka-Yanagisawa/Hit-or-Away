////////////////////////////////////////////////////////////////////////////////////////////
// AttackState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// UŒ‚‚És‚¤‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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