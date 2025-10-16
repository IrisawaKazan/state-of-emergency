//==============================================================
//
// [objectBillboard.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _OBJECTBILLBOARD_H_ // このマクロ定義がされてなかったら
#define _OBJECTBILLBOARD_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object.h"

// オブジェクトビルボードクラス
class CObjectBillboard : public CObject
{
public:
	CObjectBillboard(int nPriority = 3);
	~CObjectBillboard();

	static CObjectBillboard* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetUV(float aUV, float zUV);
	void SetSize(float sizeX, float sizeY);
	void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRedius);

	D3DXVECTOR3 GetPos(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;     // 位置
	D3DXVECTOR3 m_rot;     // 向き
	D3DXMATRIX m_mtxWorld; // ワールドマトリックス
	float m_fLength;
	float m_fAngle;
	float m_faUV;
	float m_fzUV;
	float m_fxSize;
	float m_fySize;
	//float m_fWidth;
	//float m_fHeight;
};

#endif