////////////////////////////////////////////////////////////////////////////////////////////
// DiscoveryState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ”­Œ©Œã‚És‚¤‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "HierarchyState.h"

class CEnemy;

class DiscoveryState : public HierarchyState
{
public:
	static DiscoveryState *GetInstance()
	{
		static DiscoveryState instance;
		return &instance;
	}

	virtual ~DiscoveryState() {}
	virtual void Init(CEnemy *enemy);
	virtual void Update(CEnemy *enemy);
	virtual void ChangeState(CEnemy *, State *);
};
