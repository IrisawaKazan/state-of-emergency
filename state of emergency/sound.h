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
		SOUND_LABEL_SAMPLE_BGM = 0,		// サンプルのBGM
		SOUND_LABEL_TITLE_RESULT_BGM,	// タイトル, リザルトのBGM
		SOUND_LABEL_GAME_BGM,			// ゲームのBGM
		SOUND_LABEL_GAMEOVER_BGM,		// ゲームオーバーのBGM

		SOUND_LABEL_SAMPLE_SE,			// サンプルSE
		SOUND_LABEL_JUMP_SE,			// ジャンプSE
		SOUND_LABEL_ARROW_SE,			// 矢印SE
		SOUND_LABEL_BOTTLE_SE,			// ボトルSE
		SOUND_LABEL_DEAD_SE,			// 死亡SE
		SOUND_LABEL_KEY_SE,				// 鍵SE
		SOUND_LABEL_TUTORIAL_PLAYER_SE,	// チュートリアルのプレイヤーSE
		SOUND_LABEL_DOOR_SE,			// ドアSE
		SOUND_LABEL_COUNTDOWN_SE,		// カウントダウンSE

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
		{"data/BGM/title_result_BGM.wav", -1},	// タイトル, リザルトBGM
		{"data/BGM/game_BGM.wav", -1},			// ゲームBGM
		{"data/BGM/gameover_BGM.wav", -1},		// ゲームオーバーBGM

		{"data/SE/sample_se.wav", 0},			// サンプルSE
		{"data/SE/Jump_SE.wav", 0},				// ジャンプSE
		{"data/SE/arrow_SE.wav", 0},			// 矢印SE
		{"data/SE/bottle_SE.wav", 0},			// ボトルSE
		{"data/SE/dead_SE.wav", 0},				// 死亡SE
		{"data/SE/key_SE.wav", 0},				// 鍵SE
		{"data/SE/tutorial_SE.wav", 0},			// チュートリアルのプレイヤーSE
		{"data/SE/door_SE.wav", 0},				// ドアSE
		{"data/SE/caveat_SE.wav", 0},			// ドアSE
	};
};

#endif