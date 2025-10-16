//==============================================================
//
// [object2D.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _OBJECT2D_H_ // このマクロ定義がされてなかったら
#define _OBJECT2D_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object.h"

// オブジェクト2Dクラス
class CObject2D : public CObject
{
public:
	CObject2D(int nPriority = 3);
	~CObject2D();

	static CObject2D* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetUV(float aUV, float zUV);
	void SetSize(float xsize, float ysize);
	void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius);

	void TextureAnimation(int texposx, int animspeed);

	D3DXVECTOR3 GetPos(void);
	int GetPtAnim(void);
	int GetCntAnim(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	int m_nCounterAnim; // アニメーションカウンター
	int m_nPatternAnim; // アニメーションパターンNo.
	float m_fLength;
	float m_fAngle;
	float m_faUV;
	float m_fzUV;
	float m_fxSize;
	float m_fySize;
};

#endif