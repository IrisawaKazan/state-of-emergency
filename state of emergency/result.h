//==============================================================
//
// [result.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _RESULT_H_ // このマクロ定義がされてなかったら
#define _RESULT_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"manager.h"

// マクロ定義


// リザルト画面クラス
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};

#endif