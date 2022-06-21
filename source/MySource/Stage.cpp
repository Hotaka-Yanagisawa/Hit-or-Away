///////////////////////////////////////////
// Stage.cpp
//-----------------------------------------
// 2020/08/05	�쐬
// 2020/08/18   �֐�LoadStageData,LoadCsv���쐬
//              LoadStageData�̌Ăяo���ɂ����
//				���̃X�e�[�W�ŕK�v��Enemy,
//				Player�Ȃǂ̃f�[�^��LoadCsv��
//				�ǂݍ��ނ��Ƃ��\��(����)
//				
//
///////////////////////////////////////////


//--- �C���N���[�h��
#include "Stage.h"
#include "Timer.h"
#include "Field.h"
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "effectList.h"

//--- �萔�E�}�N����`
#define FILE_STAGE ("database/Stage.csv")
#define MAX_LOAD_CSV (2)

//--- �O���[�o���ϐ�
int row;		//���ɓǂݍ��ޗ�ԍ�
ObjectManager* CStage::m_pObject;
int CStage::m_nSpilit;
CTimer timer;
CField Field;

//--- �R���X�g���N�^
CStage::CStage()
{
	CEnemy::Init();

}

//--- �f�X�g���N�^
CStage::~CStage()
{

}

//--- ������
void CStage::Init(STAGE_ID ID)
{
	//--- �X�e�[�W���擾
	LoadStageData(ID);
	// �^�C�}�[�̏�����
	if (m_loadData.TimeNum > 0)
		timer.Init(m_loadData.TimeNum * 60);
	else timer.Init(-1);	// �������ԂȂ�
	// �N���A����
	m_ClearCondition = m_loadData.clearTarget;
	m_nSpilit = 0;

	//--- �Q�[�����̃I�u�W�F�N�g�̏�����
	// �I�u�W�F�N�g�}�l�[�W���[
	m_pObject = new ObjectManager();
	m_pObject = &Singleton<ObjectManager>::GetInstance();

	// �v���C���[
	m_pObject->CreatePlayer(m_loadData.playerType, m_loadData.PlayerPosX, m_loadData.PlayerPosY);

	// �t�B�[���h
	Field.Init(m_loadData.fieldType, m_loadData.sizeX, m_loadData.sizeY);

	// �G
	CEnemy::ResetNum();
	for (auto temp = m_Data.enemy.begin(); temp != m_Data.enemy.end(); ++temp)
	{
		m_pObject->CreateEnemy(temp->path, temp->x, temp->y);
	}

	//�@�M�~�b�N
	for (auto temp = m_Data.gimmick.begin(); temp != m_Data.gimmick.end(); ++temp)
	{
		m_pObject->CreateGimmick(temp->type, temp->x, temp->y);
	}

	//�@�A�C�e��
	CItem::ResetNum();
	for (auto temp = m_Data.item.begin(); temp != m_Data.item.end(); ++temp)
	{
		m_pObject->CreateItem(temp->type, temp->x, temp->y);
	}
	//��
	sound.m_pBuffer = sound.CreateSound("sound/Victory! Sharpshooter.wav", false);
	sound.m_pSpeaker = NULL;
}

//--- �I��
void CStage::Uninit()
{
	// �^�C�}�[�̏I��
	timer.Uninit();
	// �t�B�[���h�̏I��
	Field.Uninit();
	// �I�u�W�F�N�g�̏I��
	m_pObject->Uninit();
	//delete m_pObject;

	//�f�[�^���J��
	m_Data.enemy.clear();
	m_Data.gimmick.clear();
	m_Data.enemy.shrink_to_fit();
	m_Data.gimmick.shrink_to_fit();
}

//--- �X�V
STAGE_RESULT CStage::Update()
{
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();

	// �I�u�W�F�N�g�̍X�V
	m_pObject->Update();

	//�G�t�F�N�g�̍X�V
	pEffectList->Update();

	// �t�B�[���h�̍X�V
	Field.Update();

	//--- �I��
	// �G
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
	// �A�C�e��
	if ((m_ClearCondition == CLEAR_TARGET::RECOVER)
		&& (m_nSpilit >= CItem::GetNum()))
	{
		if(sound.m_pSpeaker == NULL)
		sound.m_pSpeaker = sound.PlaySound(sound.m_pBuffer, 2.0f, 0.01f);
		return STAGE_RESULT::CLEAR;
	}
	// ����
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
	// ����
	if (CPlayer::GetResult())
	{
		return STAGE_RESULT::MISS;
	}

	return STAGE_RESULT::NO;
}

//--- �`��
void CStage::Draw()
{
	CEffectList* pEffectList = &Singleton<CEffectList>::GetInstance();

	// �t�B�[���h�̕`��
	Field.Draw();

	// �I�u�W�F�N�g�̕`��
	m_pObject->Draw();

	//�G�t�F�N�g�̕`��
	pEffectList->Draw();

	// �^�C�}�[�̕`��
	timer.Draw();
}

/////////////////////////////////
//  �쐬�ҁF���򔿋M
// ID�ɂ���ĕK�v�ȃf�[�^��csv����ǂݍ���
// FILE_LOAD�̃����o�ϐ��Ɋi�[
/////////////////////////////////
void CStage::LoadStageData(STAGE_ID StageId)
{
	string LoadFileName = FILE_STAGE;
	int row;
	//�ǂݔ�΂������f�[�^�ʂ���
	row = (int)StageId;

	//�t�@�C���I�[�v��
	ifstream fileStream;
	fileStream.open(LoadFileName);
	if (!fileStream) return;	//���s������߂�
	//���s�ڂ�
	int i = 0;
	while (true)
	{
		i++;
		string bufferString;
		fileStream >> bufferString;
		// 1 + row�s�ڂ̓f�[�^�� + �ǂݍ��݂����Ȃ��f�[�^�Ȃ̂œǂݔ�΂�
		if (i <= 1 + row) continue;
		istringstream stringStream(bufferString);
		vector<string> datas;
		string temp;
		//�f�[�^�̓ǂݍ���
		//�J���}���ƂɃf�[�^����؂�
		while (getline(stringStream, temp, ','))
		{
			if (fileStream.eof()) break;
			datas.push_back(temp);
		}
		if (fileStream.eof()) break;
		int typeTemp;
		//�ǂݍ��񂾃f�[�^�������o�ϐ��ɑ��
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
	//�t�@�C���N���[�Y
	fileStream.close();
	LoadCsv();
}
///////////////////////////////////////
// �쐬�ҁF���򔿋M
// �K��LoadStageData�̂��ƂɌĂяo������
// 
//
///////////////////////////////////////
void CStage::LoadCsv()
{
	string Path;
	string extension;
	string LoadFileName;
	//���s�ڂ�
	int i = 0;
	int j = 0;
	//�t�@�C�����ǂݏI������I��
	while (true)
	{
		switch (j)
		{
		case 0:
			Path = ("database/");

			extension = ("Enemy.csv");
			//�ǂݍ��ރt�@�C�����̍쐬
			LoadFileName = Path + m_loadData.loadPathName + extension;
			break;

		case 1:
			Path = ("database/");

			extension = ("Gimmick.csv");
			//�ǂݍ��ރt�@�C�����̍쐬
			LoadFileName = Path + m_loadData.loadPathName + extension;
			break;

		case 2:
			Path = ("database/");

			extension = ("Item.csv");
			//�ǂݍ��ރt�@�C�����̍쐬
			LoadFileName = Path + m_loadData.loadPathName + extension;
			break;
		default:
			break;
		}

		//�t�@�C���I�[�v��
		ifstream fileStream;
		fileStream.open(LoadFileName);
		if (!fileStream) return;
		i = 0;
		while (true)
		{
			i++;
			string bufferString;
			fileStream >> bufferString;
			//1�s�ڂ̓f�[�^���Ȃ̂œǂݔ�΂�
			if (i <= 1) continue;
			istringstream stringStream(bufferString);
			vector<string> datas;
			string temp;
			//�J���}���ƂɃf�[�^����؂�
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
				m_Data.enemy.push_back(eData);	//�i�[
				break;

			case 1:
				GIMMICK_DATA gData;
				typeTemp = (int)strtof(datas[0].c_str(), NULL);
				gData.type = (E_GIMMICK)typeTemp;
				gData.x = strtof(datas[1].c_str(), NULL);
				gData.y = strtof(datas[2].c_str(), NULL);
				m_Data.gimmick.push_back(gData);	//�i�[
				break;

			case 2:
				ITEM_DATA iData;
				typeTemp = (int)strtof(datas[0].c_str(), NULL);
				iData.type = (E_ITEM)typeTemp;
				iData.x = strtof(datas[1].c_str(), NULL);
				iData.y = strtof(datas[2].c_str(), NULL);
				m_Data.item.push_back(iData);	//�i�[
				break;
			default:
				return;
			}
		}
		// �t�@�C���N���[�Y
		fileStream.close();
		// ��ɂ���
		Path.clear();
		extension.clear();
		LoadFileName.clear();
		//����csv�t�@�C����
		++j;
		if (j > MAX_LOAD_CSV)
		{
			//�ǂݍ��ݏI��
			return;
		}
	}
}
