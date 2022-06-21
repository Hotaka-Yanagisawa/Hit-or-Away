#include "Keyboard.h"

//--- �萔
// �J��Ԃ����͊J�n�܂ł̑҂�����
#define KEY_WAIT	(20)
// �J��Ԃ����͂̔����Ԋu
#define KEY_TICK	(9)

//--- �O���[�o���ϐ�
// �S�ẴL�[(256���)�̓��͏���ێ�����z��
BYTE g_key[256];
// ��O�̃L�[�̓��͏��
BYTE g_oldKey[256];
// �S�ẴL�[�̓��͌p�����Ԃ�ێ�����z��
BYTE g_keyCount[256];

HRESULT InitKeyboard()
{
	// ����K�v�Ȃ�
	return S_OK;
}

void UninitKeyboard()
{
	// ����K�v�Ȃ�
}

void UpdateKeyboard()
{
	// �R�s�[��A�R�s�[���A�R�s�[�T�C�Y
	memcpy(g_oldKey, g_key, sizeof(g_key));

	GetKeyboardState(g_key);

	//--- �J��Ԃ����͗p����
	for (int i = 0; i < 256; i++)
	{
		// �L�[���͂�����ꍇ�A�A�����ĉ�����Ă��鎞�Ԃ𑝂₷
		if (IsKeyPress(i))
		{
			g_keyCount[i] ++;
		}
		else
		{
			g_keyCount[i] = 0;
		}
	}
}

void DrawKeyboard()
{

}

bool IsKeyPress(int nKey)
{
	// 8�r�b�g��(char�^�̍ŏ�ʃr�b�g)�Ɋi�[����Ă���
	return g_key[nKey] & 0x80;
}

bool IsKeyTrigger(int nKey)
{
	// (g_oldKey[nKey] & 0x80) == 0 && (g_Key[nKey) & 0x80) == 1
	// �r�b�g���Z���g���ĒZ���L�q
	return (g_oldKey[nKey] ^ g_key[nKey]) & g_key[nKey] & 0x80;
}

bool IsKeyRelease(int nKey)
{
	// �����[�X���(1) ���r�b�g���Z�ŋ��߂�
	return (g_oldKey[nKey] ^ g_key[nKey]) & g_oldKey[nKey] & 0x80;
}

bool IsKeyRepeat(int nKey)
{
	// �ŏ��ɉ����ꂽ�Ƃ��͔�������
	if (g_keyCount[nKey] == 1)
	{
		return true;
	}
	// ���΂炭���Ԃ������Ă���A�Ăє�������
	else if (g_keyCount[nKey] > KEY_WAIT)
	{
		// ���Ԋu(���l�Ŋ��������̗]�肪0)�œ��͂𔽉�������
		if(g_keyCount[nKey] % KEY_TICK == 0)
		return true;
	}

	return false;
}
