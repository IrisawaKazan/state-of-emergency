//==============================================================
//
// [playerTex.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _PLAYERTEX_H_ // このマクロ定義がされてなかったら
#define _PLAYERTEX_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object2D.h"

// プレイヤーテクスチャクラス
class CPlayerTex : public CObject2D
{
public:
	CPlayerTex(int nPriority = 1);
	~CPlayerTex();

	static HRESULT Load(void);
	static void Unload(void);

	static CPlayerTex* Create(D3DXVECTOR3 pos, float xsize, float ysize);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float xsize, float ysize);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_move;
};

#endif