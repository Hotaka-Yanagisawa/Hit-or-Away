////////////////////////////////////////////////////////////////////////////////////////////
// WaitState.h
//----------------------------------------------------------------------------------------
// 作成者：柳沢 帆貴
//----------------------------------------------------------------------------------------
// 待機状態に関すること
//-----------------------------------------------------------------------------------------
// 2020/08/07	作成
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once


#include "State.h"

class CEnemy;

class WaitState : public State
{
public:

	static WaitState *GetInstance()
	{
		static WaitState instance;
		return &instance;
	}

	virtual ~WaitState() {}
	virtual void Init(CEnemy *enemy);
	virtual void Update(CEnemy * enemy, HierarchyState *parent);	//parent:親

private:

};