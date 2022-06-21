// フェードアウト...徐々に暗くなりながら、画面が消える(アウト)
// フェードイン...徐々に明るくなりながら、画面が登場(イン)
#ifndef __FADE_H__
#define __FADE_H__

#include<Windows.h>
#include "Polygon.h"

class Fade : private CPolygon
{
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// フェード完了判定
	bool IsFinish();
	// フェード実行判定
	bool IsExecute();
	// フェード開始
	void Start(float time, bool isOut);

private:
	bool m_isOut;	// フェードの種類(フェードアウトかどうか)
	float m_maxTime;	// フェード実行時間
	float m_time;	// フェード経過時間
};

#endif	// __FADE_H__
