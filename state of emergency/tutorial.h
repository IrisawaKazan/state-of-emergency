//==============================================================
//
// [tutorial.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TUTORIAL_H_ // このマクロ定義がされてなかったら
#define _TUTORIAL_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"manager.h"

// マクロ定義


// チュートリアル画面クラス
class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nEnterCnt;	// エンターを押した後の処理のためのカウンター
	bool m_bEnter;		// エンターを押したかどうか
};

#endif