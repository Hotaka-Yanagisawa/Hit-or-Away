////////////////////////////////////////////////////////////////////////////////////////////
// ChaseState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// �ǐՎ��ɍs������
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once
#include "State.h"

//class CEnemy;
//class HierarchyParent;

class ChaseState : public State
{
public:
	static ChaseState *GetInstance()
	{
		static ChaseState instance;
		return &instance;
	}

	virtual ~ChaseState() {}
	virtual void Init(CEnemy *enemy);
	virtual void Update(CEnemy *enemy, HierarchyState *parent);
};
