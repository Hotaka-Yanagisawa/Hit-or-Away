////////////////////////////////////////////////////////////////////////////////////////////
// PatrolState.h
//----------------------------------------------------------------------------------------
// �쐬�ҁF���� ���M
//----------------------------------------------------------------------------------------
// ���G�E����Ɋւ��邱��
//-----------------------------------------------------------------------------------------
// 2020/08/07	�쐬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyState.h"

class CEnemy;

// ������
class PatrolState : public HierarchyState
{
public:
	static PatrolState *GetInstance()
	{
		static PatrolState instance;
		return &instance;
	}

	virtual void Init(CEnemy *enemy);
	virtual void Update(CEnemy *enemy);
	virtual void ChangeState(CEnemy *, State *);

private:
	PatrolState() {}
};

