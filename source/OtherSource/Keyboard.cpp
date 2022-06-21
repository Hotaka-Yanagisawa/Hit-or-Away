#include "Keyboard.h"

//--- 定数
// 繰り返し入力開始までの待ち時間
#define KEY_WAIT	(20)
// 繰り返し入力の発生間隔
#define KEY_TICK	(9)

//--- グローバル変数
// 全てのキー(256種類)の入力情報を保持する配列
BYTE g_key[256];
// 一つ前のキーの入力情報
BYTE g_oldKey[256];
// 全てのキーの入力継続時間を保持する配列
BYTE g_keyCount[256];

HRESULT InitKeyboard()
{
	// 現状必要なし
	return S_OK;
}

void UninitKeyboard()
{
	// 現状必要なし
}

void UpdateKeyboard()
{
	// コピー先、コピー元、コピーサイズ
	memcpy(g_oldKey, g_key, sizeof(g_key));

	GetKeyboardState(g_key);

	//--- 繰り返し入力用処理
	for (int i = 0; i < 256; i++)
	{
		// キー入力がある場合、連続して押されている時間を増やす
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
	// 8ビット目(char型の最上位ビット)に格納されている
	return g_key[nKey] & 0x80;
}

bool IsKeyTrigger(int nKey)
{
	// (g_oldKey[nKey] & 0x80) == 0 && (g_Key[nKey) & 0x80) == 1
	// ビット演算を使って短く記述
	return (g_oldKey[nKey] ^ g_key[nKey]) & g_key[nKey] & 0x80;
}

bool IsKeyRelease(int nKey)
{
	// リリース状態(1) をビット演算で求める
	return (g_oldKey[nKey] ^ g_key[nKey]) & g_oldKey[nKey] & 0x80;
}

bool IsKeyRepeat(int nKey)
{
	// 最初に押されたときは反応する
	if (g_keyCount[nKey] == 1)
	{
		return true;
	}
	// しばらく時間がたってから、再び反応する
	else if (g_keyCount[nKey] > KEY_WAIT)
	{
		// 一定間隔(数値で割った時の余りが0)で入力を反応させる
		if(g_keyCount[nKey] % KEY_TICK == 0)
		return true;
	}

	return false;
}
