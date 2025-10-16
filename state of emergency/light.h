//==============================================================
//
// [light.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _LIGHT_H_ // このマクロ定義がされてなかったら
#define _LIGHT_H_ // 2重インクルード防止のマクロ定義

#include"main.h"

// マクロ定義
#define MAX_LIGHT (5)

// ライトクラス
class CLight
{
public:
	CLight();
	~CLight();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];
};

#endif