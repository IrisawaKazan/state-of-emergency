//==============================================================
//
// [pause.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _PAUSE_H_ // このマクロ定義がされてなかったら
#define _PAUSE_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object2D.h"

// ポーズクラス
class CPause : public CObject2D
{
public:
	CPause(int nPriority = 2);
	~CPause();

	static HRESULT Load(void);
	static void Unload(void);

	static CPause* Create(D3DXVECTOR3 pos, float xsize, float ysize);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetUse(bool use);
	bool GetUse(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;

	bool m_bUse;
};

#endif