//==============================================================
//
// [title.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TITLE_H_ // このマクロ定義がされてなかったら
#define _TITLE_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"manager.h"

// 前方宣言
//class CObjectX;

// マクロ定義
#define MAX_PLAYER (4)                     // 再生プレイヤーの数
#define NUM_SEPLAY_FRAME_CNT (60 * 20)     // 同じ種類のSEがどれだけ連続して再生されるか
#define MAX_SPAWN_FLOAT (5)                // 浮遊物の湧く率(数字が小さいと出現しにくくなる)
#define SPAWN_POS_Z (250.0f)               // 浮遊物が湧く場所
#define UNINIT_POS_Z (SPAWN_POS_Z + 50.0f) // 浮遊物が消える場所
#define MAX_FRAMECOUNTER_F (8)             // フレイムカウンター

// タイトル画面クラス
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//static CObjectX* GetObjectX(void);
	//static void DestoryPlayer(void);

private:
	int m_nPlay;                             // SEを再生する
	int m_nCounter[MAX_PLAYER];              // 多段で再生しないためのカウンター
	int m_nFrameCounter[MAX_FRAMECOUNTER_F]; // フレイムカウンター

	int m_nSpawnFloating;                    // 浮遊物のスポーン率の調整

	//static CObjectX* m_pObjectX;
};

#endif