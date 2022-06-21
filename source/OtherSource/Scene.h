///////////////////////////////////////
// Scene.h
//-------------------------------------
// 2020/08/05	作成
//
///////////////////////////////////////

#pragma once

//--- インクルード部
#include "MySound.h"

//--- クラス
class Scene
{
public:

	Scene();	// コンストラクタ
	~Scene();	// デストラクタ

	virtual void Init() = 0;	// 初期化
	virtual void Uninit() = 0;	// 終了
	virtual bool Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画

private:

	// サウンド周り
	// BGMのデータ
	XAUDIO2_BUFFER* m_pBGM;
	// 音を鳴らしてるオブジェクト
	IXAudio2SourceVoice* m_pBGMSpeaker;
	// 音量
	float m_fVolume;

};

