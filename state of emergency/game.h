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
#define BALL_POS_Z (275.0f)

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

	int m_nCnt;		// テストカウンター
	//int m_nSpawn;	// 湧くスピード
};

#endif