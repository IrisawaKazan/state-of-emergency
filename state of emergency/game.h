//==============================================================
//
// [game.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _GAME_H_ // このマクロ定義がされてなかったら
#define _GAME_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"manager.h"

// 前方宣言
class CPlayer;

// マクロ定義
#define NUM_WALL_X (300.0f)				// 見えない壁(X)
#define NUM_WALL_Z (200.0f)				// 見えない壁(Z)
#define BALL_POS_Z (275.0f)				// ボールが生成される位置
#define GOAL_POS_X (NUM_WALL_X - 10.0f)	// ドアの位置(X)
#define GOAL_POS_Z (NUM_WALL_Z - 10.0f)	// ドアの位置(Z)
#define MAX_SPAWN (20)					// ボトルの湧く率(数字が小さいと出現しにくくなる)
#define MAX_SPAWN_RARE (5)				// レアボトルの湧く率(数字が小さいと出現しにくくなる)
#define NUM_FRAME_CNT (60 * 2)			// ボトルがどれだけ連続して沸くか
#define NUM_FRAME_CNT_RARE (60 * 10)	// レアボトルがどれだけ連続して沸くか
#define MAX_FRAMECOUNTER (12)			// フレームカウンターの数

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

	static CPlayer* GetPlayer(void) { return m_pPlayer; }

private:
	static CPlayer* m_pPlayer;

	int m_nCnt;								// テストカウンター
	int m_nSpawn;							// 湧くスピード
	int m_nFrameCounter[MAX_FRAMECOUNTER];	// フレイムカウンター
};

#endif