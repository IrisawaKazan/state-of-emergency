//==============================================================
//
// [mpn.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _MPN_H_ // このマクロ定義がされてなかったら
#define _MPN_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object.h"

// MPNクラス
class CMpn : public CObject
{
public:
	CMpn(int nPriority = 2);
	~CMpn();

	static CMpn* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

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
};

#endif