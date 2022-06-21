///////////////////////////////////////////
// Field.h
//-----------------------------------------
// 2020/08/05	�쐬
//
//
///////////////////////////////////////////

#pragma once

//--- �C���N���[�h��
#include "Polygon.h"

//--- �񋓑�
enum class E_FIELD
{
	STEPPE,	// ����
	ICE,	// �X��
	WIND,	// ��
	MAG,	// �n��

	MAX
};

//--- �N���X
class CField : public CPolygon
{
public:

	CField();	// �R���X�g���N�^
	~CField();	// �f�X�g���N�^

	void Init(E_FIELD, float SizeX, float SizeY);	// ������
	void Uninit();									// �I��

	void Update();	// �X�V
	void Draw();	// �`��

	static E_FIELD GetType() { return m_Type; };
	static VECTOR2<> GetSize() { return m_fSize; };

private:

	static E_FIELD m_Type;	// ���
	static VECTOR2<> m_fSize;	// �傫��

};
