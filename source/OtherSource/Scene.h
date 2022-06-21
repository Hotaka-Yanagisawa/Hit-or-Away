///////////////////////////////////////
// Scene.h
//-------------------------------------
// 2020/08/05	�쐬
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "MySound.h"

//--- �N���X
class Scene
{
public:

	Scene();	// �R���X�g���N�^
	~Scene();	// �f�X�g���N�^

	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual bool Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

private:

	// �T�E���h����
	// BGM�̃f�[�^
	XAUDIO2_BUFFER* m_pBGM;
	// ����炵�Ă�I�u�W�F�N�g
	IXAudio2SourceVoice* m_pBGMSpeaker;
	// ����
	float m_fVolume;

};

