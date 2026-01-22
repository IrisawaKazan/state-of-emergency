//==============================================================
//
// [tutorialTex.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TUTORIALTEX_H_ // このマクロ定義がされてなかったら
#define _TUTORIALTEX_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object2D.h"

// チュートリアテクスチャクラス
class CTutorialTex : public CObject2D
{
public:
	CTutorialTex(int nPriority = 1);
	~CTutorialTex();

	static HRESULT Load(void);
	static void Unload(void);

	static CTutorialTex* Create(D3DXVECTOR3 pos, float xsize, float ysize);

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