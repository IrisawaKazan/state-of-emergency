//==============================================================
//
// [title_arrow.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TITLEARROW_H_ // このマクロ定義がされてなかったら
#define _TITLEARROW_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object.h"

// タイトルアロークラス
class CTitleArrow : public CObject
{
public:
	CTitleArrow(int nPriority = 3);
	~CTitleArrow();

	static CTitleArrow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetRot(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;			// メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアルへのポインタ
	DWORD m_dwNumMat;			// マテリアルの数
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス

	float m_fRotation;			// ローテーション

	bool m_bEnter;				// エンターを押したかどうか
};

#endif