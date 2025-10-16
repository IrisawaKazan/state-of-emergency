//==============================================================
//
// [sound.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _SOUND_H_ // ���̃}�N����`������ĂȂ�������
#define _SOUND_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#include"main.h"

// �T�E���h�N���X
class CSound
{
public:
	// �T�E���h�ꗗ
	typedef enum
	{
		SOUND_LABEL_SAMPLE_BGM = 0, // �T���v����BGM
		SOUND_LABEL_TITLE_BGM,      // �^�C�g����BGM
		SOUND_LABEL_GAME_BGM,       // �Q�[����BGM
		SOUND_LABEL_RESULT_BGM,     // ���U���g��BGM

		SOUND_LABEL_SAMPLE_SE,      // �T���v��SE
		SOUND_LABEL_COIN_SE,        // �R�C��SE
		SOUND_LABEL_DEADZONE_SE,    // �f�b�h�]�[��SE
		SOUND_LABEL_KILLP_SE,       // �L���v���C���[SE
		SOUND_LABEL_BREAK_SE,       // �j��SE
		SOUND_LABEL_ITEM_SE,        // �A�C�e��SE
		SOUND_LABEL_ITEMUSE_SE,     // �A�C�e���g�pSE
		SOUND_LABEL_MORSE_SE,       // �E�E�E---SE
		SOUND_LABEL_NOISE_SE,       // �z���C�g�m�C�YSE
		SOUND_LABEL_CAVEAT_SE,      // �x��SE
		SOUND_LABEL_LIGHT_SE,       // ���C�gSE
		SOUND_LABEL_ERROR_SE,       // �G���[SE
		SOUND_LABEL_APPLAUSE_SE,    // ����SE

		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	CSound();
	~CSound();

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	typedef struct
	{
		const char* m_pFilename; // �t�@�C����
		int m_nCntLoop;          // ���[�v�J�E���g
	} SOUNDINFO;

	IXAudio2* m_pXAudio2;                                  // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;             // �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX]; // �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];                  // �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];                   // �I�[�f�B�I�f�[�^�T�C�Y
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/sample_bgm.wav", -1},     // �T���v�����C��BGM
		{"data/BGM/titleBGM.wav", -1},       // �^�C�g��BGM
		{"data/BGM/M_M_I.wav", -1},          // �Q�[��BGM
		{"data/BGM/M_b_I_lastpart.wav", -1}, // ���U���gBGM

		{"data/SE/sample_se.wav", 0},        // �T���v��SE
		{"data/SE/coinSE.wav", 0},           // �R�C��SE
		{"data/SE/deadzoneSE.wav", 0},       // �Ă���SE
		{"data/SE/killplayerSE.wav", 0},     // �v���C���[�����񂾂Ƃ�SE
		{"data/SE/breakSE.wav", 0},          // �����SE
		{"data/SE/itemSE.wav", 0},           // �A�C�e��SE
		{"data/SE/itemuseSE.wav", 0},        // �A�C�e���g�pSE
		{"data/SE/titleSE_morse.wav", 0},    // �E�E�E---SE
		{"data/SE/titleSE_noise.wav", 0},    // �z���C�g�m�C�YSE
		{"data/SE/caveatSE.wav", 0},         // �x��SE
		{"data/SE/lightSE.wav", 0},          // ���C�gSE
		{"data/SE/error.wav", 0},            // �G���[SE
		{"data/SE/applauseSE.wav", 0},       // ����SE

	};
};

#endif