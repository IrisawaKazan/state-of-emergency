//==============================================================
//
// [meshfield.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _MESHFIELD_H_ // このマクロ定義がされてなかったら
#define _MESHFIELD_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object.h"
#include"game.h"

// マクロ定義
#define MAX_POLYGONPOS_X (NUM_WALL_X + 25.0f)	// フィールドの横幅
#define MAX_POLYGONPOS_Z (NUM_WALL_Z + 25.0f)	// フィールドの立幅

// メッシュフィールドクラス
class CMeshfield : public CObject
{
public:
	CMeshfield(int nPriority = 3);
	~CMeshfield();

	static CMeshfield* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPos(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxWorld;
};

#endif