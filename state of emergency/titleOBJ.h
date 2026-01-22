//==============================================================
//
// [titleOBJ.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _TITLEOBJ_H_ // このマクロ定義がされてなかったら
#define _TITLEOBJ_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object.h"

// タイトルオブジェクトクラス
class CTitleObjX : public CObject
{
public:
	CTitleObjX(int nPriority = 3);
	~CTitleObjX();

	static CTitleObjX* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPos(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;			// メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアルへのポインタ
	DWORD m_dwNumMat;			// マテリアルの数
	D3DXVECTOR3 m_pos;			// 位置
	D3DXVECTOR3 m_rot;			// 向き
	D3DXMATRIX m_mtxWorld;		// ワールドマトリックス

	float m_fMove;				// 自動で動かす用のメンバ変数
	int m_nMovingCounter[4];	// 自動で動かす用のカウンター
};

#endif