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
#define BALL_DEPTH_POS_X (0.0f)			// ボールDepthが生成される位置(X)
#define BALL_DEPTH_POS_Y (-100.0f)		// ボールDepthが生成される位置(Y)
#define BALL_DEPTH_POS_Z (275.0f)		// ボールDepthが生成される位置(Z)
#define BALL_BESIDE_POS_X (-375.0f)		// ボールBesideが生成される位置(X)
#define BALL_BESIDE_POS_Y (0.0f)		// ボールBesideが生成される位置(Y)
#define BALL_BESIDE_POS_Z (0.0f)		// ボールBesideが生成される位置(Z)
#define GOAL_POS_X (NUM_WALL_X - 25.0f)	// ドアの位置(X)
#define GOAL_POS_Z (NUM_WALL_Z - 25.0f)	// ドアの位置(Z)
#define MAX_SPAWN (20)					// ボトルの湧く率(数字が小さいと出現しにくくなる)
#define MAX_SPAWN_RARE (5)				// レアボトルの湧く率(数字が小さいと出現しにくくなる)
#define NUM_FRAME_CNT (60 * 2)			// ボトルがどれだけ連続して沸くか
#define NUM_FRAME_CNT_RARE (60 * 10)	// レアボトルがどれだけ連続して沸くか
#define MAX_FRAMECOUNTER (12)			// フレームカウンターの数
#define MAX_BALLCOUNTER (6)				// ボールのカウンターの数

#define NUM_BOTTLE_SCORE (10)			// ボトルのスコア
#define NUM_BOTTLE_RARE_SCORE (100)		// レアボトルのスコア

//#define KEY_TIME (15)					// 鍵が出る時間
#define KEY_POINT (1000)				// 鍵が出るポイント
#define TIME_OUT (120)					// 強制終了する時間

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

	int m_nCnt[MAX_BALLCOUNTER];			// ボールカウンター
	int m_nSpawn;							// 湧くスピード
	int m_nFrameCounter[MAX_FRAMECOUNTER];	// フレイムカウンター
	int m_nKeyCnt;							// 鍵が出るまでカウンター

	int m_nEscapeCnt;						// 脱出までの制限時間

	int m_nKeyNum;							// 鍵の多段生成防止
};

#endif