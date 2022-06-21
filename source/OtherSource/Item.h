///////////////////////////////////////
// Item.h
//-------------------------------------
// 2020/07/30	�쐬
//
///////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Object.h"
#include "MySound.h"

//--- �񋓑�
enum class E_ITEM
{
	APPLE,
	BAD_APPLE,
	SPILIT,

	MAX
};

//--- �N���X
class CItem : public CObject
{
public:

	CItem(E_ITEM Type, float x = 0.0f, float y = 0.0f);
	~CItem();

	void Update();
	void Draw();

	static int GetNum();
	static void ResetNum() { m_nNum = 0; };
	
private:

	E_ITEM m_Type;	// ���
	static int m_nNum;

	CSound sound;
};

