//==============================================================
//
// [key.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _KEY_H_ // このマクロ定義がされてなかったら
#define _KEY_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object.h"

// マクロ定義


// 鍵クラス
class CKey : public CObject
{
public:
	CKey(int nPriority = 3);
	~CKey();

	static CKey* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetPositionOld(D3DXVECTOR3 posOld);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetPosOld(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetSize(void);

	void Collision(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;			// メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアルへのポインタ
	DWORD m_dwNumMat;			// マテリアルの数
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_posOld;		// 前回の位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス

	D3DXVECTOR3 m_size;			// 大きさ
	D3DXVECTOR3 m_vtxMin;		// モデルの最小値
	D3DXVECTOR3 m_vtxMax;		// モデルの最大値

	float m_fRotation;			// ローテーション
};

#endif