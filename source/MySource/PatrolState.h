////////////////////////////////////////////////////////////////////////////////////////////
// PatrolState.h
//----------------------------------------------------------------------------------------
// ì¬ÒF–ö‘ò ”¿‹M
//----------------------------------------------------------------------------------------
// õ“GE„‰ñ‚ÉŠÖ‚·‚é‚±‚Æ
//-----------------------------------------------------------------------------------------
// 2020/08/07	ì¬
//				
//
///////////////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "HierarchyState.h"

class CEnemy;

// „‰ñó‘Ô
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

