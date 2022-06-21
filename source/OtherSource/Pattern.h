///////////////////////////////////////
// Pattern.h
//-------------------------------------
// 2020/07/27	�쐬
//
///////////////////////////////////////

#pragma once

//--- ���X�g
template <typename T>
struct LIST
{
	T Data;
	LIST* Next;
};

template <typename T>
struct DUMMYLIST
{
	T Data;
	DUMMYLIST* Next;
	DUMMYLIST* Prev;
};

//--- �V���O���g��
template<class T>
class Singleton
{
public:

	static inline T& GetInstance()
	{
		static T instance;
		return instance;
	}

protected:

	Singleton() {}			// �R���X�g���N�^
	virtual ~Singleton() {}	// �f�X�g���N�^

private:

	void operator=(const Singleton& obj) {}	// ������Z�q�֎~
	Singleton(const Singleton &obj) {}		// �R�s�[�R���X�g���N�^�֎~

};





