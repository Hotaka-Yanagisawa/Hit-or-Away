///////////////////////////////////////////
// Stage.cpp
//-----------------------------------------
// 2020/08/05	作成
// 2020/08/18   関数LoadStageData,LoadCsvを作成
//              LoadStageDataの呼び出しによって
//				そのステージで必要なEnemy,
//				PlayerなどのデータをLoadCsvで
//				読み込むことが可能に(柳沢)
//				
//
///////////////////////////////////////////


//--- インクルード部
#include "Stage.h"
#include "Timer.h"
#include "Field.h"
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "effectList.h"

//--- 定数・マクロ定義
#define FILE_STAGE ("database/Stage.csv")
#define MAX_LOAD_CSV (2)

//--- グローバル変数
int row;		//次に読み込む列番号
ObjectManager* CStage::m_pObject;
int CStage::m_nSpilit;
CTimer timer;
CField Field;

//--- コンストラクタ
CStage::CStage()
{
	CEnemy::Init();

}

//--- デストラクタ
CStage::~CStage()
{

}

//--- 初期化
void CStage::Init(STAGE_ID ID)
{
	//--- ステージ情報取得
	LoadStageData(ID);
	// タイマーの初期化
	if (m_loadData.TimeNum > 0)
		timer.Init(m_loadData.TimeNum * 60);
	else timer.Init(-1);	// 制限時間なし
	// クリア条件
	m_ClearCondition = m_loadData.clearTarget;
	m_nSpilit = 0;

	//--- ゲーム内のオブジェクトの初期化
	// オブジェクトマネージャー
	m_pObject = new ObjectManager();
	m_pObject = &Singleton<ObjectManager>::GetInstance();

	// プレイヤー
	m_pObject->CreatePlayer(m_loadData.playerType, m_loadData.PlayerPosX, m_loadData.PlayerPosY);

	// フィールド
	Field.Init(m_loadData.fieldType, m_loadData.sizeX, m_loadData.sizeY);

	// 敵
	CEnemy::ResetNum();
	for (auto temp = m_Data.enemy.begin(); temp != m_Data.enemy.end(); ++temp)
	{
		m_pObject->CreateEnemy(temp->path, temp->x, temp->y);
	}

	//　ギミック
	for (auto temp = m_Data.gimmick.begin(); temp != m_Data.gimmick.end(); ++temp)
	{
		m_pObject->CreateGimmick(temp->type, temp->x, temp->y);
	}

	//　アイテム
	CItem::ResetNum();
	for (auto temp = m_Data.item.begin(); temp != m_Data.item.end(); ++temp)
	{
		m_pObject->CreateItem(temp->type, temp->x, temp->y);
	}
	//音
	sound.m_pBuffer = sound.CreateSound("sound/Victory! Sharpshooter.wav", false);
	sound.m_pSpeaker = NULL;
}

//--- 終了
void CStage::Uninit()
{
	// タイマーの終了
	timer.Uninit();
	// フィールドの終了
	Field.Uninit();
	// オブジェクトの終了
	m_pObject->Uninit();
	//delete m_pObject;

	//データを開放
	m_Data.enemy.clear();
	m_Data.gimmick.clear();
	m_Data.enemy.shrink_to_fit();
	m_Data.gimmick.shrink_to_fit();
}

//--- 更新
STAGE_RESULT CStage::Update()
{
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();

	// オブジェクトの更新
	m_pObject->Update();

	//エフェクトの更新
	pEffectList->Update();

	// フィールドの更新
	Field.Update();

	//--- 終了
	// 敵
	if ((m_ClearCondition == CLEAR_TARGET::DEFEAT)
		&& (CEnemy::GetNum() < 1))
	{
		if (m_loadData.loadPathName != "boss/")
		{
			if (sound.m_pSpeaker == NULL)
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
		}
		else
		{
			if (sound.m_pSpeaker == NULL)
			{
				sound.m_pBuffer = sound.CreateSound("sound/Victory! All Clear.wav", false);
				sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			}
		}
		return STAGE_RESULT::CLEAR;
	}
	// アイテム
	if ((m_ClearCondition == CLEAR_TARGET::RECOVER)
		&& (m_nSpilit >= CItem::GetNum()))
	{
		if(sound.m_pSpeaker == NULL)
		sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
		return STAGE_RESULT::CLEAR;
	}
	// 時間
	if (timer.Update())
	{
		if (m_ClearCondition == CLEAR_TARGET::ESCAPE)
		{
			if (sound.m_pSpeaker == NULL)
			sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
			return STAGE_RESULT::CLEAR;
		}
		else
			return STAGE_RESULT::MISS;
	}
	// やられ
	if (CPlayer::GetResult())
	{
		return STAGE_RESULT::MISS;
	}

	return STAGE_RESULT::NO;
}

//--- 描画
void CStage::Draw()
{
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();

	// フィールドの描画
	Field.Draw();

	// オブジェクトの描画
	m_pObject->Draw();

	//エフェクトの描画
	pEffectList->Draw();

	// タイマーの描画
	timer.Draw();
}

/////////////////////////////////
//  作成者：柳沢帆貴
// IDによって必要なデータをcsvから読み込む
// FILE_LOADのメンバ変数に格納
/////////////////////////////////
void CStage::LoadStageData(STAGE_ID StageId)
{
	string LoadFileName = FILE_STAGE;
	int row;
	//読み飛ばしたいデータ量を代入
	row = (int)StageId;

	//ファイルオープン
	ifstream fileStream;
	fileStream.open(LoadFileName);
	if (!fileStream) return;	//失敗したら戻る
	//何行目か
	int i = 0;
	while (true)
	{
		i++;
		string bufferString;
		fileStream >> bufferString;
		// 1 + row行目はデータ名 + 読み込みたくないデータなので読み飛ばす
		if (i <= 1 + row) continue;
		istringstream stringStream(bufferString);
		vector<string> datas;
		string temp;
		//データの読み込み
		//カンマごとにデータを区切る
		while (getline(stringStream, temp, ','))
		{
			if (fileStream.eof()) break;
			datas.push_back(temp);
		}
		if (fileStream.eof()) break;
		int typeTemp;
		//読み込んだデータをメンバ変数に代入
		typeTemp = (int)strtof(datas[0].c_str(), NULL);
		m_loadData.fieldType = (E_FIELD)typeTemp;
		m_loadData.loadPathName = datas[1];
		m_loadData.sizeX = strtof(datas[2].c_str(), NULL);
		m_loadData.sizeY = strtof(datas[3].c_str(), NULL);
		typeTemp = (int)strtof(datas[4].c_str(), NULL);
		m_loadData.playerType = (E_PLAYER)typeTemp;
		m_loadData.PlayerPosX = strtof(datas[5].c_str(), NULL);
		m_loadData.PlayerPosY = strtof(datas[6].c_str(), NULL);
		m_loadData.TimeNum = (int)strtof(datas[7].c_str(), NULL);
		typeTemp = (int)strtof(datas[8].c_str(), NULL);
		m_loadData.clearTarget = (CLEAR_TARGET)typeTemp;
		break;
	}
	//ファイルクローズ
	fileStream.close();
	LoadCsv();
}
///////////////////////////////////////
// 作成者：柳沢帆貴
// 必ずLoadStageDataのあとに呼び出すこと
// 
//
///////////////////////////////////////
void CStage::LoadCsv()
{
	string Path;
	string extension;
	string LoadFileName;
	//何行目か
	int i = 0;
	int j = 0;
	//ファイルが読み終えたら終了
	while (true)
	{
		switch (j)
		{
		case 0:
			Path = ("database/");

			extension = ("Enemy.csv");
			//読み込むファイル名の作成
			LoadFileName = Path + m_loadData.loadPathName + extension;
			break;

		case 1:
			Path = ("database/");

			extension = ("Gimmick.csv");
			//読み込むファイル名の作成
			LoadFileName = Path + m_loadData.loadPathName + extension;
			break;

		case 2:
			Path = ("database/");

			extension = ("Item.csv");
			//読み込むファイル名の作成
			LoadFileName = Path + m_loadData.loadPathName + extension;
			break;
		default:
			break;
		}

		//ファイルオープン
		ifstream fileStream;
		fileStream.open(LoadFileName);
		if (!fileStream) return;
		i = 0;
		while (true)
		{
			i++;
			string bufferString;
			fileStream >> bufferString;
			//1行目はデータ名なので読み飛ばす
			if (i <= 1) continue;
			istringstream stringStream(bufferString);
			vector<string> datas;
			string temp;
			//カンマごとにデータを区切る
			while (getline(stringStream, temp, ','))
			{
				if (fileStream.eof()) break;
				datas.push_back(temp);
			}
			if (fileStream.eof()) break;
			switch (j)
			{
				int typeTemp;
			case 0:
				ENEMY_DATA eData;
				typeTemp = (int)strtof(datas[0].c_str(), NULL);
				eData.path = (PATHS)typeTemp;
				eData.x = strtof(datas[1].c_str(), NULL);
				eData.y = strtof(datas[2].c_str(), NULL);
				m_Data.enemy.push_back(eData);	//格納
				break;

			case 1:
				GIMMICK_DATA gData;
				typeTemp = (int)strtof(datas[0].c_str(), NULL);
				gData.type = (E_GIMMICK)typeTemp;
				gData.x = strtof(datas[1].c_str(), NULL);
				gData.y = strtof(datas[2].c_str(), NULL);
				m_Data.gimmick.push_back(gData);	//格納
				break;

			case 2:
				ITEM_DATA iData;
				typeTemp = (int)strtof(datas[0].c_str(), NULL);
				iData.type = (E_ITEM)typeTemp;
				iData.x = strtof(datas[1].c_str(), NULL);
				iData.y = strtof(datas[2].c_str(), NULL);
				m_Data.item.push_back(iData);	//格納
				break;
			default:
				return;
			}
		}
		// ファイルクローズ
		fileStream.close();
		// 空にする
		Path.clear();
		extension.clear();
		LoadFileName.clear();
		//次のcsvファイルへ
		++j;
		if (j > MAX_LOAD_CSV)
		{
			//読み込み終了
			return;
		}
	}
}
