//==============================================================
//
// [blood.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _BLOOD_H_ // このマクロ定義がされてなかったら
#define _BLOOD_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object2D.h"

// 血のテクスチャクラス
class CBlood : public CObject2D
{
public:
	CBlood(int nPriority = 6);
	~CBlood();

	static HRESULT Load(void);
	static void Unload(void);

	static CBlood* Create(D3DXVECTOR3 pos, float xsize, float ysize);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float xsize, float ysize);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif