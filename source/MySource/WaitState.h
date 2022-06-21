////////////////////////////////////////////////////////////////////////////////////////////
// WaitState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// ‘Ò‹@ó‘Ô‚ÉŠÖ‚·‚é‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
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
	virtual void Update(CEnemy * enemy, HierarchyState *parent);	//parent:e

private:

};