////////////////////////////////////////////////////////////////////////////////////////////
// DiscoveryState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ������ɍs������
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
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
