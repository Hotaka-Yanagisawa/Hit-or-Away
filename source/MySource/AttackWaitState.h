////////////////////////////////////////////////////////////////////////////////////////////
// AttackWaitState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// UŒ‚Œã‚És‚¤‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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