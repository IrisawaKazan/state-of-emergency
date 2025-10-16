//==============================================================
//
// [tutorial.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TUTORIAL_H_ // このマクロ定義がされてなかったら
#define _TUTORIAL_H_ // 2重インクルード防止のマクロ定義

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

};

#endif