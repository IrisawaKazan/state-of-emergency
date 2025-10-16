//==============================================================
//
// [effect.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _EFFECT_H_ // このマクロ定義がされてなかったら
#define _EFFECT_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object2D.h"

// エフェクトクラス
class CEffect : public CObject2D
{
public:
	CEffect(int nPriority = 7);
	~CEffect();

	static HRESULT Load(void);
	static void Unload(void);

	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife, float xsize, float ysize);

	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius, int nLife);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float xsize, float ysize);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_pos; // 位置
	D3DXCOLOR m_col;   // 色
	float m_fRedius;   // 半径(大きさ)
	int m_nLife;       // 寿命
};

#endif