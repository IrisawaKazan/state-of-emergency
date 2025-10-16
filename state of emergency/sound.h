//==============================================================
//
// [sound.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _SOUND_H_ // このマクロ定義がされてなかったら
#define _SOUND_H_ // 2重インクルード防止のマクロ定義

#include"main.h"

// サウンドクラス
class CSound
{
public:
	// サウンド一覧
	typedef enum
	{
		SOUND_LABEL_SAMPLE_BGM = 0, // サンプルのBGM
		SOUND_LABEL_TITLE_BGM,      // タイトルのBGM
		SOUND_LABEL_GAME_BGM,       // ゲームのBGM
		SOUND_LABEL_RESULT_BGM,     // リザルトのBGM

		SOUND_LABEL_SAMPLE_SE,      // サンプルSE
		SOUND_LABEL_COIN_SE,        // コインSE
		SOUND_LABEL_DEADZONE_SE,    // デッドゾーンSE
		SOUND_LABEL_KILLP_SE,       // キルプレイヤーSE
		SOUND_LABEL_BREAK_SE,       // 破壊SE
		SOUND_LABEL_ITEM_SE,        // アイテムSE
		SOUND_LABEL_ITEMUSE_SE,     // アイテム使用SE
		SOUND_LABEL_MORSE_SE,       // ・・・---SE
		SOUND_LABEL_NOISE_SE,       // ホワイトノイズSE
		SOUND_LABEL_CAVEAT_SE,      // 警告SE
		SOUND_LABEL_LIGHT_SE,       // ライトSE
		SOUND_LABEL_ERROR_SE,       // エラーSE
		SOUND_LABEL_APPLAUSE_SE,    // 拍手SE

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
		const char* m_pFilename; // ファイル名
		int m_nCntLoop;          // ループカウント
	} SOUNDINFO;

	IXAudio2* m_pXAudio2;                                  // XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;             // マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX]; // ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];                  // オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];                   // オーディオデータサイズ
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/sample_bgm.wav", -1},     // サンプルメインBGM
		{"data/BGM/titleBGM.wav", -1},       // タイトルBGM
		{"data/BGM/M_M_I.wav", -1},          // ゲームBGM
		{"data/BGM/M_b_I_lastpart.wav", -1}, // リザルトBGM

		{"data/SE/sample_se.wav", 0},        // サンプルSE
		{"data/SE/coinSE.wav", 0},           // コインSE
		{"data/SE/deadzoneSE.wav", 0},       // 焼けるSE
		{"data/SE/killplayerSE.wav", 0},     // プレイヤーが死んだときSE
		{"data/SE/breakSE.wav", 0},          // 崩れるSE
		{"data/SE/itemSE.wav", 0},           // アイテムSE
		{"data/SE/itemuseSE.wav", 0},        // アイテム使用SE
		{"data/SE/titleSE_morse.wav", 0},    // ・・・---SE
		{"data/SE/titleSE_noise.wav", 0},    // ホワイトノイズSE
		{"data/SE/caveatSE.wav", 0},         // 警告SE
		{"data/SE/lightSE.wav", 0},          // ライトSE
		{"data/SE/error.wav", 0},            // エラーSE
		{"data/SE/applauseSE.wav", 0},       // 拍手SE

	};
};

#endif