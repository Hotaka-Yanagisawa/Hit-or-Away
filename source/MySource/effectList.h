//=================================================================
//
//	effectList.h
//	オブジェクトのリスト関連
//
//-----------------------------------------------------------------
//	author: AT12D 35 柳沢帆貴
//-----------------------------------------------------------------
//	開発履歴
//	2020/08/18  作成
//  2020/08/18  クラス化
//  2020/09/01  今回のプロジェクト用に改変
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

