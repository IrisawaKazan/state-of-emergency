//==============================================================
//
// [game.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _GAME_H_ // このマクロ定義がされてなかったら
#define _GAME_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"manager.h"

// 前方宣言
class CObjectX;
class CPause;

// マクロ定義
#define MAX_SPAWN (20)                     // 敵の湧く率(数字が小さいと出現しにくくなる)
#define NUM_FRAME_CNT (60 * 2)             // 同じ種類の敵がどれだけ連続して沸くか
#define MAX_FRAMECOUNTER (32)              // フレームカウンターの数
#define SPAWN_POS_X (325.0f)               // オブジェクトが湧く場所

#define UNINIT_POS (SPAWN_POS_X + 50.0f)   // オブジェクトが消える場所

#define MAX_STARDUST_SPAWN (10)            // アイテムの湧く率(数字が小さいと出現しにくくなる)
#define NUM_STARDUST_FRAME_CNT (60 * 15)   // アイテムがどれだけ連続して沸くか
#define MAX_COIN10_SPAWN (10)              // 10コインの湧く率(数字が小さいと出現しにくくなる)
#define NUM_COIN10_FRAME_CNT (60 * 10)     // 10コインどれだけ連続して沸くか

#define MAX_SmallThings_SPAWN (30)         // 小さきものの湧く率(数字が小さいと出現しにくくなる) ※ 消すかも

#define NUM_SPACESHIP_X (250.0f)           // 宇宙船の位置X
#define NUM_SPACESHIP_Y (-100.0f)          // 宇宙船の位置Y

// ゲーム画面クラス
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX* GetObjectX(void);
	static CPause* GetPause(void);

	static void DestoryPlayer(void);

private:
	bool m_bPause;                         // ポーズしているか否か
	int m_nSpawn;                          // スポーン率の調整
	int m_nFrameCounter[MAX_FRAMECOUNTER]; // フレイムカウンター
	int m_nScrapCounter;                   // 鉄くず用のカウンター(登場時間の調整用)
	int m_nSmallThingsCounter;             // 小さきもの用のカウンター(登場時間の調整用)
	int m_nBlackThingsCounter;             // ブラックエネミー用のカウンター(登場時間の調整用)

	int m_nSmallThingsSpawn;               // 小さきもののスポーン率の調整

	static CObjectX* m_pObjectX;
	static CPause* m_pPause;

	int m_nTransition;
};

#endif