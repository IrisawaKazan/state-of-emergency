//==============================================================
//
// [sound.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _SOUND_H_ // このマクロ定義がされてなかったら
#define _SOUND_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"

// サウンドクラス
class CSound
{
public:
	// サウンド一覧
	typedef enum
	{
		SOUND_LABEL_SAMPLE_BGM = 0,			// サンプルのBGM
		//SOUND_LABEL_SAMPLE_TITLE_BGM,		// サンプルのBGM
		//SOUND_LABEL_TITLE_BGM,			// タイトルのBGM
		//SOUND_LABEL_GAME_BGM,				// ゲームのBGM
		//SOUND_LABEL_RESULT_BGM,			// リザルトのBGM

		SOUND_LABEL_SAMPLE_SE,				// サンプルSE

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
		const char* m_pFilename;	// ファイル名
		int m_nCntLoop;				// ループカウント
	} SOUNDINFO;

	IXAudio2* m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/sample_bgm.wav", -1},		// サンプルメインBGM
		//{"data/BGM/sample_bgm_game.wav", -1},		// サンプルタイトルBGM
		//{"data/BGM/titleBGM.wav", -1},			// タイトルBGM
		//{"data/BGM/M_M_I.wav", -1},				// ゲームBGM
		//{"data/BGM/M_b_I_lastpart.wav", -1},	// リザルトBGM

		{"data/SE/sample_se.wav", 0},			// サンプルSE
	};
};

#endif