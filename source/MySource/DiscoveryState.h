////////////////////////////////////////////////////////////////////////////////////////////
// DiscoveryState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 発見後に行うこと
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
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
