///////////////////////////////////////
// Pattern.h
//-------------------------------------
// 2020/07/27	作成
//
///////////////////////////////////////

#pragma once

//--- リスト
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

//--- シングルトン
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

	Singleton() {}			// コンストラクタ
	virtual ~Singleton() {}	// デストラクタ

private:

	void operator=(const Singleton& obj) {}	// 代入演算子禁止
	Singleton(const Singleton &obj) {}		// コピーコンストラクタ禁止

};





