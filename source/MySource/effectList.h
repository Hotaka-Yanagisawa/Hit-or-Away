//=================================================================
//
//	effectList.h
//	�I�u�W�F�N�g�̃��X�g�֘A
//
//-----------------------------------------------------------------
//	author: AT12D 35 ���򔿋M
//-----------------------------------------------------------------
//	�J������
//	2020/08/18  �쐬
//  2020/08/18  �N���X��
//  2020/09/01  ����̃v���W�F�N�g�p�ɉ���
//
//=================================================================
#ifndef __EFFECTLIST_H__
#define __EFFECTLIST_H__

#include "Pattern.h"
#include "Effect.h"

using EFFECT_LIST = DUMMYLIST<Effect*>;

class CEffectList
{
public:
	CEffectList();
	~CEffectList();

	void Init();
	bool Update();
	void Draw();
	void AllDelete(void);
	void Remove(EFFECT_LIST *);

	Effect* Add(Effect *);
	void CreateEffect(float x, float y, FX_KIND kind);

	static EFFECT_LIST * GetList();

private:

};

#endif

