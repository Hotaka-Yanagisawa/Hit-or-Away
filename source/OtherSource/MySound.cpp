/////////////////////////////////////////////////////////
//MYSound.cpp
//-----------------------------------------------------
//�쐬�ҁF�@AT12D_35_���򔿋M
//-----------------------------------------------------
//2020/07/23	�w�Z����z�z���ꂽSound.cpp&.h���N���X��
//				�p���j���O��t�F�[�h�������\��
//2020/07/24	InOut�̃`�����l������Ԃ��֐�LoadIOCh�쐬
//2020/07/25	�l�X�ȃp���j���O���ł���Pan�֐��쐬
//2020/07/29	�t�F�[�h�����̃v���g�^�C�v�쐬
//2020/09/03    Update�ǉ�,PlaySound�Ńt�F�[�h�̓��͉\�ɕύX
//              InitSound��UninitSound��ÓI�����o�֐��ɕύX
//              �Ȃǂ��s���g���₷������
//
/////////////////////////////////////////////////////////

#include "MySound.h"

IXAudio2* CSound::m_pXAudio = nullptr;
IXAudio2MasteringVoice* CSound::m_pMasterVoice = nullptr;

CSound::CSound()
{
	m_vol = 0;
	m_tempVol = 0;
	m_tempTime = 0;
	m_bFade;
	m_Deltatime;

	
	m_Rad; 
	m_RadX; 
	m_RadY;

	m_DistanceX;
	m_DistanceY;

	m_InChannels = -1;
	m_OutChannels = -1;
	m_LRswitch = false;
	m_Volumes[0] = 1.0f;
	m_Volumes[1] = 0.0f;
	m_Cnt = 0;
}
CSound::~CSound()
{
	SoundList::iterator soundIt = m_soundList.begin();
	while (soundIt != m_soundList.end())
	{
		delete[] soundIt->second.pBuffer;
		++soundIt;
	}
	
}

void CSound::Uninit()
{
}

/**
 * @brief ������
 * @return ��������
 */
HRESULT CSound::InitSound(void)
{
	HRESULT hr = E_FAIL;

	// COM�I�u�W�F�N�g������
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		return hr;
	}

	// XAUDIO2������
	hr = XAudio2Create(&m_pXAudio);
	if (FAILED(hr))
	{
		return hr;
	}

	// �}�X�^�[�{�C�X(�\�[�X)�쐬
	hr = m_pXAudio->CreateMasteringVoice(&m_pMasterVoice);

	return hr;
}






/**
 * @brief �I������
 */
void CSound::UninitSound(void)
{

	if (m_pMasterVoice != NULL)
	{
		m_pMasterVoice->DestroyVoice();
		m_pMasterVoice = NULL;
	}
	if (m_pXAudio != NULL)
	{
		m_pXAudio->Release();
		m_pXAudio = NULL;
	}
	CoUninitialize();
}


bool CSound::Fade(float TargetVolume, float TargetTime)	//vol�͂P���O���D�܂���
{
	m_tempVol = TargetVolume;
	m_tempTime = TargetTime;
	m_Deltatime = 0;
	
	return true;
}

void CSound::UpdateSoundFade()
{
	//�S�̎��Ԃ̊���
	float rate = 1.0f;

	//�S�̎��Ԃ���������ړI�̉��ʂ������
	if (m_Deltatime >= m_tempTime)
	{
		m_vol = m_tempVol;
		m_pSpeaker->SetVolume(m_vol);
		m_bFade = false;
		if (m_tempVol == 0.0f) m_pSpeaker->Stop();
	}
	//�t�F�[�h�A�E�g
	else if (m_tempVol == 0.0f)
	{
		rate = m_Deltatime / m_tempTime;
		m_vol = m_vol - rate;
		if (m_vol < 0.0f) m_vol = 0.0f;
		m_pSpeaker->SetVolume(m_vol);
	}
	//�t�F�[�h�C��
	else
	{
		rate = m_Deltatime / m_tempTime;

		if (m_tempVol <= rate)
		{
			m_vol = m_tempVol;
			m_pSpeaker->SetVolume(m_vol);
		}
		else
		{
			m_vol = rate;
			m_pSpeaker->SetVolume(m_vol);
		}
	}
}

void CSound::Update()
{
	//Fade���Ă΂ꂽ��@�\����
	if (m_bFade)
	{
		m_Deltatime += 1.0f / 60;
		UpdateSoundFade();
	}
	
}


////////////////////////////////////////////
//
//�����t�@�C���̓��o�̓`�����l�������擾����
//
////////////////////////////////////////////
std::tuple<int, int> CSound::LoadIOCh(IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice)
{
	XAUDIO2_VOICE_DETAILS details;
	pSourceVoice->GetVoiceDetails(&details); // �\�[�X�{�C�X�̏��𓾂�
	int InChannels = details.InputChannels;
	pMasteringVoice->GetVoiceDetails(&details); // �}�X�^�[�{�C�X�̏��𓾂�
	int OutChannels = details.InputChannels;

	return std::forward_as_tuple(InChannels, OutChannels);	//std::tie(a,b...)=LoadIOCh�Ŏ󂯎��Ba,b�͔C�ӂ̕ϐ�
}															//std::tie(a, std::ignore, c)��ignore�̏ꏊ�͎󂯎��Ȃ��B




void CSound::Pan(IXAudio2SourceVoice* pSourceVoice, IXAudio2MasteringVoice* pMasteringVoice, int Type, FLOAT2 pos)//FLOAT2 = nullptr
{
	if (m_InChannels < 0 && m_OutChannels < 0)
	{
		std::tie(m_InChannels, m_OutChannels) = LoadIOCh(pSourceVoice, pMasteringVoice);
	}

	switch (Type)
	{
	case 0:
		if (!m_LRswitch)
		{
			m_Volumes[0] -= 1.0f / 300;
			m_Volumes[1] += 1.0f / 300;
			if (m_Volumes[0] < 0)	m_Volumes[0] = 0.0f;
			if (m_Volumes[0] == 0)
			{
				m_LRswitch = true;
			}
		}
		else
		{
			m_Volumes[0] += 1.0f / 300;
			m_Volumes[1] -= 1.0f / 300;
			if (m_Volumes[1] < 0)	m_Volumes[1] = 0.0f;
			if (m_Volumes[1] == 0)
			{
				m_LRswitch = false;
			}
		}
		pSourceVoice->SetOutputMatrix(NULL, m_InChannels, m_OutChannels, m_Volumes);
		break;
	case 1:	//���E�ɉ�������
		if (!m_LRswitch)
		{
			m_Volumes[0] = 1.0f;
			m_Volumes[1] = 0.3f;

			m_Cnt++;
			if (m_Cnt > 10)
			{
				m_Cnt = 0;

				m_LRswitch = true;
			}
		}
		else
		{
			m_Volumes[0] = 0.3f;
			m_Volumes[1] = 1.0f;

			m_Cnt++;
			if (m_Cnt > 10)
			{
				m_Cnt = 0;

				m_LRswitch = false;
			}
		}
		pSourceVoice->SetOutputMatrix(NULL, m_InChannels, m_OutChannels, m_Volumes);
		break;

	case 2://�߂Â��Ɖ�����
		m_DistanceY = (fabsf(pos.y - SCREEN_HEIGHT) / (float)SCREEN_HEIGHT);	//�߂��قǒl�͏�����
		m_DistanceX = (fabsf(pos.x - SCREEN_WIDTH * 0.5f) / (float)SCREEN_WIDTH);//�X�N���[�����I�u�W�F�N�g��pos�ɕς���
		m_DistanceX *= 2.0f;


		if (1.0f - m_DistanceX - m_DistanceY < 0)
		{
			m_Volumes[0] = 0;
			m_Volumes[1] = 0;
		}
		else
		{
			m_Volumes[0] = 1.0f - m_DistanceX - m_DistanceY;// ���{�����[��
			m_Volumes[1] = 1.0f - m_DistanceX - m_DistanceY; // �E�{�����[��
		}

		pSourceVoice->SetOutputMatrix(NULL, m_InChannels, m_OutChannels, m_Volumes);
		break;
	case 3:
		m_Rad = (pos.y / SCREEN_HEIGHT * 90.0f)*(M_PI / 180.0f);
		m_Volumes[0] = cosf(m_Rad);
		m_Volumes[1] = sinf(m_Rad);
		pSourceVoice->SetOutputMatrix(NULL, m_InChannels, m_OutChannels, m_Volumes);

		break;
	}
}





/**
 * @brief �T�E���h�쐬
 * @param[in] file �ǂݍ��ރt�@�C��
 * @param[in] loop �J��Ԃ��Đ�
 * @return �T�E���h�o�b�t�@
 */
XAUDIO2_BUFFER* CSound::CreateSound(const char *file, bool loop)
{
	SoundData data;

	SoundList::iterator it = m_soundList.find(file);
	if (it != m_soundList.end())
	{
		// ���łɓǂݍ��񂾃T�E���h�t�@�C��������
		return &it->second.sound;
	}


	// �g���q���Ƃɓǂݍ��ݏ������s
	HRESULT hr = E_FAIL;
	LPSTR ext = PathFindExtension(file);
	if (ext != NULL) {
		if (memcmp(ext, ".wav", 4) == 0) {
			hr = LoadWav(file, &data);
		}
		else if (memcmp(ext, ".mp3", 4) == 0) {
			hr = LoadMP3(file, &data);
		}
	}
	if (FAILED(hr)) {
		return NULL;
	}

	//--- �o�b�t�@�[�쐬
	ZeroMemory(&data.sound, sizeof(data.sound));
	// �T�E���h�f�[�^�̃o�C�g��
	data.sound.AudioBytes = data.bufSize;
	// �T�E���h�f�[�^�̐擪�A�h���X
	data.sound.pAudioData = data.pBuffer;
	// ���[�v�w��
	if (loop)			//�����炭������ւ�ŃV�[�N�������o����
	{
		data.sound.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	data.sound.Flags = XAUDIO2_END_OF_STREAM;

	// �o�^
	m_soundList.insert(SoundKey(file, data));
	it = m_soundList.find(file);

	return &it->second.sound;
}






/**
 * @brief �T�E���h�Đ�
 * @param[in] pSound �T�E���h�o�b�t�@
 */
IXAudio2SourceVoice* CSound::PlaySound(XAUDIO2_BUFFER* pSound, float TargetVolume, float TargetTime)
{
	HRESULT hr;
	IXAudio2SourceVoice* pSource;

	// �Đ�����f�[�^��T��
	SoundList::iterator soundIt = m_soundList.begin();
	while (soundIt != m_soundList.end())
	{
		if (&soundIt->second.sound == pSound)
		{
			break;
		}
		++soundIt;
	}
	if (soundIt == m_soundList.end())
	{
		// �Y���̃f�[�^�Ȃ�
		return NULL;
	}

	// ���g�p�̃\�[�X��T��
	XAUDIO2_VOICE_STATE state;
	SourceList::iterator sourceIt = m_sourceList.begin();
	while (sourceIt != m_sourceList.end())
	{
		(*sourceIt)->GetState(&state);
		if (state.BuffersQueued == 0)
		{
			break;
		}
		++sourceIt;
	}
	if (sourceIt != m_sourceList.end())
	{
		// �����\�[�X���g�p
		pSource = *sourceIt;
		pSource->SetVolume(1.0f);
	}
	else
	{
		// �t�H�[�}�b�g���w�肵�ă\�[�X���쐬
		/*----------
		* WAVEFORMATEX
		* wFormatTag
		*  �t�H�[�}�b�g
		* nChannels
		*  �`�����l����
		*  1... ���m����
		*  2... �X�e���I
		* wBitsPerSample
		*  1�T���v��������̃r�b�g��
		*  8...128�𖳉��Ƃ���0~255
		*  16...0�𖳉��Ƃ���-32768~32767
		* nSamplesPerSec
		*  �T���v�����O���[�g
		*  (1�b������̃T���v����
		*  �P�ʂ�Hz(�w���c
		*----------*/
		hr = m_pXAudio->CreateSourceVoice(&pSource, &soundIt->second.format);
		if (FAILED(hr)) {
			return NULL;
		}
		// �\�[�X�����X�g�ɒǉ�
		m_sourceList.push_back(pSource);
	}
	pSource->SubmitSourceBuffer(pSound);

	// �Đ�
	pSource->Start();


	return pSource;
	//
	//m_pSpeaker = pSource;

	//m_pSpeaker->SubmitSourceBuffer(pSound);

	//if (TargetVolume != NULL && TargetTime != NULL)
	//{
	//	m_pSpeaker->SetVolume(0.0f);
	//	m_bFade = Fade(TargetVolume, TargetTime);
	//}
	//// �Đ�
	//m_pSpeaker->Start();
}





/**
 * @brief wav�t�@�C���ǂݍ���
 * @param[in] file �ǂݍ��ރt�@�C��
 * @param[out] pData �T�E���h�f�[�^
 * @return ��������
 */
HRESULT CSound::LoadWav(const char *file, SoundData *pData)
{
	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;
	MMRESULT mmRes;

	// WAVE�t�@�C���I�[�v��
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(const_cast<char*>(file), &mmioInfo, MMIO_READ);
	if (hMmio == NULL) {
		return E_FAIL;
	}

	// RIFF�`�����N����
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}

	// �t�H�[�}�b�g�`�����N����
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}

	// �t�H�[�}�b�g�擾
	DWORD formatSize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, reinterpret_cast<HPSTR>(&pData->format), formatSize);
	if (size != formatSize) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}
	
	// RIFF�`�����N�Ɉړ�
	mmioAscend(hMmio, &formatChunk, 0);


	// �f�[�^�`�����N����
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}

	// �f�[�^�擾
	pData->bufSize = dataChunk.cksize;
	pData->pBuffer = new BYTE[pData->bufSize];
	size = mmioRead(hMmio, reinterpret_cast<HPSTR>(pData->pBuffer), pData->bufSize);
	if (size != dataChunk.cksize) {
		pData->bufSize = 0;
		if (pData->pBuffer != NULL)
		{
			delete[] pData->pBuffer;
			pData->pBuffer;
		}
		return E_FAIL;
	}

	mmioClose(hMmio, 0);
	return S_OK;
}






/**
 * @brief mp3�t�@�C���ǂݍ���
 * @param[in] file �ǂݍ��ރt�@�C��
 * @param[out] pData �T�E���h�f�[�^
 * @return ��������
 */
HRESULT CSound::LoadMP3(const char *file, SoundData *pData)
{
	HANDLE hFile; // �t�@�C���|�C���^
	DWORD readSize; // �ǂݍ��݃T�C�Y

	// �ǂݍ���
	hFile = CreateFile(
		file, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		return E_FAIL;
	}

	// �t�@�C���t�H�[�}�b�g�ǂݍ���
	MP3FormatInfo format;
	readSize = ReadMP3Format(hFile, &format);
	if(readSize == 0) {
		return E_FAIL;
	}

	// �T�E���h�t���[���w�b�_�ǂݍ���
	MP3FrameInfo frame;
	readSize = ReadMP3FrameHeader(hFile, format.offset, &frame);
	if(readSize == 0) {
		return E_FAIL;
	}

	// �T�E���h�f�[�^�ǂݍ���
	readSize = ReadMP3Data(hFile, format.offset, format.dataSize, &frame, pData);
	if (readSize == 0) {
		return E_FAIL;
	}

	return S_OK;
}





/**
 * @brief MP3�t�H�[�}�b�g�`�F�b�N
 * @param[in] hFile �t�@�C���|�C���^
 * @param[out] pFormat �t�@�C���t�H�[�}�b�g
 * @return �f�[�^�T�C�Y
 */
DWORD CSound::ReadMP3Format(HANDLE hFile, MP3FormatInfo *pFormat)
{
	DWORD readSize;

	// MP3�t�@�C���T�C�Y
	DWORD fileSize = GetFileSize(hFile, NULL);

	// �@�w�b�_�[/�t�b�^�[�̗L���𒲂ׂ�
	/*----------
	* ID3v1
	*  -�����Ƀ^�O������or�^�O�Ȃ�
	*  [MP3�f�[�^]
	*		or
	*	[MP3�f�[�^]["TAG"(3byte)][�^�O���(125byte)]
	* ID3v2
	*  -�擪�Ƀ^�O������
	*	["ID3"(3byte)][�o�[�W����(2byte)][�t���O(1byte)][�^�O�T�C�Y(4byte)][�g���w�b�_][MP3�f�[�^]
	*----------*/
	const BYTE ID3V2_HEADER_SIZE = 10;
	BYTE header[ID3V2_HEADER_SIZE];	// �w�b�_�[���
	ReadFile(hFile, header, sizeof(header), &readSize, NULL);

	// �^�O���`�F�b�N���AMP3�f�[�^�̈ʒu�A�T�C�Y���v�Z
	const char *ID3V1_TAG = "TAG";
	const char *ID3V2_TAG = "ID3";
	const BYTE MP3_TAG_SIZE = 3;
	if (memcmp(header, ID3V2_TAG, MP3_TAG_SIZE) == CMP_MATCH)
	{
		// ID3v2�w�b�_�[�����
		/*----------
		* [�g���w�b�_]�̃f�[�^�T�C�Y�ɂ���
		*  [�^�O�T�C�Y]�̃f�[�^�\��
		*	 [0AAAAAAA][0BBBBBBB][0CCCCCCC][0DDDDDDD]
		*	���ۂ̃f�[�^�T�C�Y
		*	 0x0000AAAAAAABBBBBBBCCCCCCCDDDDDDD
		*
		* - �f�[�^�̍ŏ�ʃr�b�g�͕K��0
		*	 ���ۂ̃T�C�Y�́A0���Ȃ��ċl�߂�����
		*----------*/
		DWORD exHeaderSize =
			(header[6] << 21) |
			(header[7] << 14) |
			(header[8] << 7) |
			(header[9]);
		pFormat->offset = exHeaderSize + ID3V2_HEADER_SIZE;
		pFormat->dataSize = fileSize - pFormat->offset;
	}
	else
	{
		// ID3v1�t�b�^�[�����
		const BYTE ID3V1_FOOTER_SIZE = 128;
		BYTE tag[MP3_TAG_SIZE];
		SetFilePointer(hFile, fileSize - ID3V1_FOOTER_SIZE, NULL, FILE_BEGIN);
		ReadFile(hFile, tag, MP3_TAG_SIZE, &readSize, NULL);
		pFormat->offset = 0;
		if (memcmp(tag, ID3V1_TAG, MP3_TAG_SIZE) == CMP_MATCH)
		{
			pFormat->dataSize = fileSize - 128;
		}
		else
		{
			pFormat->dataSize = fileSize;
		}
	}
	return pFormat->dataSize;
}





/** 
 * @brief MP3�T�E���h�t���[���w�b�_�ǂݍ���
 * @param[in] hFile �t�@�C���|�C���^
 * @param[in] seek �t���[���ǂݍ��݈ʒu
 * @param[out] pFrame �t���[�����
 * @return �ǂݍ��݃T�C�Y
 */ 
DWORD CSound::ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo *pFrame)
{
	DWORD readSize;

	// �@�t���[���w�b�_��������擾
	/*----------
	 * MP3�f�[�^�̍\��
	 *	[�t���[���w�b�_(4byte)][�f�[�^]
	 *	[�t���[���w�b�_(4byte)][�f�[�^]
	 *	[�t���[���w�b�_(4byte)][�f�[�^]
	 *	...(�J��Ԃ�
	 *----------*/
	// MP3�f�[�^�ʒu�ֈړ�
	SetFilePointer(hFile, seek, NULL, FILE_BEGIN);

	/*----------
	 * �t���[���w�b�_���
	 * http://www.cactussoft.co.jp/Sarbo/divMPeg3UnmanageHeader.html
	 *	[AAAAAAAA][AAABBCCD][EEEEFFGH][IIJJKLMM]
	 *	 A - �����r�b�g(�K���P)
	 *	 B - MP3�̃o�[�W����
	 *		00 - MPEG2.5
	 *		01 - �\��
	 *		10 - MPEG2
	 *		11 - MPEG1
	 *	 C - ���C���[
	 *		00 - �\��
	 *		01 - Layer3
	 *		10 - Layer2
	 *		11 - Layer1
	 *	 D - CRC��茟�o�̗L��
	 *	 E - �r�b�g���[�g
	 *	 F - �T���v�����O���g��
	 *	 G - �p�f�B���O(�t���[���̍Ō�̃f�[�^��0xFF�������ꍇ�A
	 *		 ���̃t���[���̓��ƂȂ��邽�߁A�t���[���̍Ō��NULL���}�������
	 *		 ���ۂɃf�[�^���}�����ꂽ���ǂ����̏�������
	 *	 H - �g��(���g�p
	 *	 I - �`�����l�����[�h
	 *	 J - �g��
	 *	 K - ���쌠�̗L��
	 *	 L - �I���W�i��(�R�s�[or�I���W�i��
	 *	 M - ����
	 *
	 *	- �Œ���K�v�ȏ���B,C,E,F,G,I
	 *----------*/
	const BYTE FRAME_HEADER_SIZE = 4;
	BYTE frameHeader[FRAME_HEADER_SIZE];
	ReadFile(hFile, frameHeader, FRAME_HEADER_SIZE, &readSize, NULL);

	// �����r�b�g�`�F�b�N
	if (!(frameHeader[0] == 0xFF && (frameHeader[1] & 0xE0) == 0xE0)) {
		return 0;
	}

	// �o�[�W����
	BYTE version = (frameHeader[1] >> 3) & 0b11;

	// ���C���[
	BYTE layer = (frameHeader[1] >> 1) & 0b11;

	// �r�b�g���[�g(�P�ʂ�kbit/sec
	const int bitRateTable[][16] = {
		// MPEG1, Layer1
		{ 0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, -1 },
		// MPEG1, Layer2
		{ 0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, -1 },
		// MPEG1, Layer3
		{ 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, -1 },
		// MPEG2, Layer1
		{ 0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, -1 },
		// MPEG2/2.5, Layer2,3
		{ 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, -1 }
	};
	BYTE bitRateTableIndex;
	if (version == 0b11) {
		bitRateTableIndex = 0b11 - layer;
	}
	else if (version == 0b10 && layer == 0b11) {
		bitRateTableIndex = 3;
	}
	else {
		bitRateTableIndex = 4;
	}
	WORD bitRate = bitRateTable[bitRateTableIndex][frameHeader[2] >> 4];

	// �T���v�����O���[�g
	const int sampleRateTable[][4] = {
		// MPEG1
		{ 44100, 48000, 32000, -1 },
		// MPEG2
		{ 22050, 24000, 16000, -1 },
		// MPEG2.5
		{ 11025, 12000, 8000, -1 },
	};
	BYTE sampleRateTableIndex;
	switch (version) {
	case 0b00: sampleRateTableIndex = 2; break;
	case 0b10: sampleRateTableIndex = 1; break;
	case 0b11: sampleRateTableIndex = 0; break;
	default: return E_FAIL;
	}
	WORD sampleRate = sampleRateTable[sampleRateTableIndex][(frameHeader[2] >> 2) & 0b11];

	// �p�f�B���O
	BYTE padding = (frameHeader[2] >> 1) & 0b01;

	// �`�����l��
	BYTE channel = frameHeader[3] >> 6;


	// �t���[���T�C�Y
	// �r�b�g���[�g��kbit/sec�Ȃ̂�bit/sec�ɕϊ����邽�߂�1000�{����
	const int samplePerFrame[][4] = {
		// layer1
		{ 384, 384, 384, -1 },
		// layer2
		{ 1152, 1152, 1152, -1 },
		// layer3
		{ 1152, 576, 576, -1 }
	};
	WORD frameBlockSize = ((samplePerFrame[0b11 - layer][sampleRateTableIndex] * bitRate * 1000 / 8) / sampleRate) + padding;

	// �A�擾�����������Ƃ�MEPGLAYER3WAVEFORMAT�Ƀf�[�^�ݒ�
	/*----------
	 *	MPEGLAYER3WAVEFORMAT
	 *	http://www.cactussoft.co.jp/Sarbo/divMPeg3UnmanageStruct.html
	 *	 - mpeg�I�[�f�B�I���C���[3(mp3)���������߂Ɋg�����ꂽWAVEFORMAT�\����
	 *	.wfx.cbSize				- �\���̂̊g���T�C�Y�AMPEGLAYER3_WFX_EXTRA_BYTES���w��
	 *	.wfx.nChannels			- �`�����l�����A���m�������P�A�X�e���I���Q
	 *	.wfx.wFormatTag			- mp3��\���AWAVE_FORMAT_MPEGLAYER3���w��
	 *	.wfx.nBlockAlign		- 1���w��
	 *	.wfx.wBitsPerSample		- 0���w��
	 *	.wfx.nSamplesPerSec		- �T���v�����O���g��
	 *	.wfx.nAvgBytesPerSec	- 1�b�ԂɕK�v�ȃf�[�^�T�C�Y
	 *	wID						- MPEGLAYER3_ID_MPEG���w��
	 *	fdwFlags				- �p�f�B���O�̑}��������Ύw��
	 *	nFramesPerBlock			- 1�̃u���b�N�ɔz�u����t���[����
	 *	nBlockSize				- �u���b�N�T�C�Y(�t���[���T�C�Y * �t���[����)
	 *	nCodecDelay				- 1393(0x571)���w��
	 *----------*/

	// channel
	// sample
	// bitRate
	// padding
	pFrame->channel = channel == 0x11 ? 1 : 2;
	pFrame->sampleRate = sampleRate;
	pFrame->bitRate = bitRate;
	pFrame->padding = padding;
	pFrame->frameSize = frameBlockSize;

	return pFrame->frameSize;
}






/**
 * @brief MP3�T�E���h�f�[�^�ǂݍ���
 * @param[in] hFile �t�@�C���|�C���^
 * @param[in] seek �t���[���ǂݍ��݈ʒu
 * @param[in] size �ǂݍ��݃f�[�^��
 * @param[in] pFrame �t���[�����
 * @param[out] pData �T�E���h�f�[�^
 * @return �ǂݍ��݃T�C�Y
 */
DWORD CSound::ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo *pFrame, SoundData *pData)
{
	// �ϊ��t�H�[�}�b�g�쐬
	MPEGLAYER3WAVEFORMAT mp3WavFormat;
	mp3WavFormat.wfx.cbSize = MPEGLAYER3_WFX_EXTRA_BYTES;
	mp3WavFormat.wfx.nChannels = pFrame->channel;
	mp3WavFormat.wfx.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
	mp3WavFormat.wfx.nBlockAlign = 1;
	mp3WavFormat.wfx.wBitsPerSample = 0;
	mp3WavFormat.wfx.nSamplesPerSec = pFrame->sampleRate;
	mp3WavFormat.wfx.nAvgBytesPerSec = (pFrame->bitRate * 1000) / 8;

	mp3WavFormat.wID = MPEGLAYER3_ID_MPEG;
	mp3WavFormat.fdwFlags = pFrame->padding ? MPEGLAYER3_FLAG_PADDING_ON : MPEGLAYER3_FLAG_PADDING_OFF;
	mp3WavFormat.nFramesPerBlock = 1;
	mp3WavFormat.nBlockSize = static_cast<WORD>(pFrame->frameSize * mp3WavFormat.nFramesPerBlock);
	mp3WavFormat.nCodecDelay = 0x571;

	// mp3��wav�֕ϊ��\��
	// �ϊ��\�ł����,wavFormat�փf�[�^��ݒ�
	WAVEFORMATEX wavFormat;
	wavFormat.wFormatTag = WAVE_FORMAT_PCM;
	MMRESULT mmr;
	mmr = acmFormatSuggest(NULL, &mp3WavFormat.wfx, &wavFormat, sizeof(WAVEFORMATEX), ACM_FORMATSUGGESTF_WFORMATTAG);
	if (mmr != MMSYSERR_NOERROR) {
		return 0;
	}

	// ACM�X�g���[���I�[�v��
	// mp3����wav�փt�H�[�}�b�g�ϊ�
	HACMSTREAM has;
	mmr = acmStreamOpen(&has, NULL, &mp3WavFormat.wfx, &wavFormat, NULL, NULL, NULL, 0);

	// MP3�̃u���b�N�T�C�Y����WAVE�`���փf�R�[�h��̃T�C�Y���擾
	DWORD waveBlockSize;
	acmStreamSize(has, size, &waveBlockSize, ACM_STREAMSIZEF_SOURCE);

	// �ϊ��f�[�^�Z�b�g
	ACMSTREAMHEADER ash = { 0 };
	ash.cbStruct = sizeof(ACMSTREAMHEADER);
	ash.cbSrcLength = size;
	ash.pbSrc = new BYTE[ash.cbSrcLength];
	ash.cbDstLength = waveBlockSize;
	ash.pbDst = new BYTE[ash.cbDstLength];

	// �f�R�[�h
	acmStreamPrepareHeader(has, &ash, 0);
	DWORD readSize;
	SetFilePointer(hFile, seek, NULL, FILE_BEGIN);
	ReadFile(hFile, ash.pbSrc, ash.cbSrcLength, &readSize, NULL);
	mmr = acmStreamConvert(has, &ash, 0);
	acmStreamUnprepareHeader(has, &ash, 0);
	acmStreamClose(has, 0);

	// wav�f�[�^�R�s�[
	if (ash.cbDstLengthUsed > 0) {
		pData->bufSize = ash.cbDstLengthUsed;
		pData->pBuffer = new BYTE[pData->bufSize];
		pData->format = wavFormat;
		memcpy_s(pData->pBuffer, pData->bufSize,
			ash.pbDst, ash.cbDstLengthUsed);
	}

	delete[] ash.pbSrc;
	delete[] ash.pbDst;

	CloseHandle(hFile);

	return ash.cbSrcLengthUsed;
}



// EOF