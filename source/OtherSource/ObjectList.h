
#pragma once

//--- �C���N���[�h��
#include "Object.h"
#include "Pattern.h"

//--- �񋓑�
enum class SORT
{
	Y,
	TAG,

};

//--- ���X�g
using OBJECT_LIST = LIST<CObject*>;

//--- �N���X
class CObjectList
{
public:

	CObjectList();	// �R���X�g���N�^
	~CObjectList();	// �f�X�g���N�^

	CObject* Add(CObject*);	// ���X�g�ɒǉ�
	void Delete(CObject*);	// ���X�g�������

	void Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

	static void Sort(SORT);	// ���ёւ�

	static OBJECT_LIST* GetList();	// ���X�g�擾

private:

	static OBJECT_LIST* m_pListTop;	// ���X�g�̐擪�A�h���X

};

