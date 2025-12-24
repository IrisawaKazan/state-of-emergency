//==============================================================
//
// [timeover.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TIMEOVER_H_ // このマクロ定義がされてなかったら
#define _TIMEOVER_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"manager.h"

// マクロ定義
#define NUM_TIMEOVER_POS_X (0.0f)			// タイムオーバーのモデルのX座標
#define NUM_TIMEOVER_POS_Y (450.0f)			// タイムオーバーのモデルのY座標
#define NUM_TIMEOVER_POS_Z (-325.0f)		// タイムオーバーのモデルのZ座標
#define NUM_TIMEOVER_ROT_X (D3DX_PI / 2.5f)	// タイムオーバーのモデルのXの向き
#define NUM_TIMEOVER_ROT_Y (0.0f)			// タイムオーバーのモデルのYの向き
#define NUM_TIMEOVER_ROT_Z (0.0f)			// タイムオーバーのモデルのZの向き

// タイムオーバー画面クラス
class CTimeover : public CScene
{
public:
	CTimeover();
	~CTimeover();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nEnterCnt;	// エンターを押した後の処理のためのカウンター
	bool m_bEnter;		// エンターを押したかどうか
};

#endif