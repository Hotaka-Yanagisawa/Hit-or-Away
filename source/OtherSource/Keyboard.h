// ウィンドウメッセージでもキー入力は取得できるが、
// ソースファイルに分割することでそれぞれの機能が
// すっきりと実装できる
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <Windows.h>

HRESULT InitKeyboard();
void UninitKeyboard();
void UpdateKeyboard();
void DrawKeyboard();

// 指定されたキーが押されているかを調べる関数
// 引数のnKeyに調べたいキーを指定
bool IsKeyPress(int nKey);
// 指定されたキーが今、初めて押されたか調べる関数
bool IsKeyTrigger(int nKey);
// 指定されたキーから指が離れた瞬間か調べる関数
bool IsKeyRelease(int nKey);

// リピート入力も調べられると便利！
// ボタンを押し続けてる間、最初の一回と
// しばらく経ってからの入力を調べる
bool IsKeyRepeat(int nKey);

#endif	// __KEYBOARD_H_
