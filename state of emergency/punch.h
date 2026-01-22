//==============================================================
//
// [punch.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _PUNCH_H_ // このマクロ定義がされてなかったら
#define _PUNCH_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object.h"

// マクロ定義
#define MAX_PUNCH_CNT (5) // パンチカウンターの最大数

// パンチクラス
class CPunch : public CObject
{
public:
	// パンチの種類
	typedef enum
	{
		PUNCH_NONE = 0,
		PUNCH_000_A, // 右奥から
		PUNCH_000_B, // 左奥から
		PUNCH_000_C, // 右手前から
		PUNCH_000_D, // 左手前から

		PUNCH_MAX
	}PUNCH;

	CPunch(int nPriority = 3);
	~CPunch();

	static CPunch* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, PUNCH type);

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

	void SetType(PUNCH type) { m_type = type; }
	PUNCH GetType(void) { return m_type; }

	void Collision(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;						// メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER m_pBuffMat;				// マテリアルへのポインタ
	DWORD m_dwNumMat;						// マテリアルの数
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_posOld;					// 前回の位置
	D3DXVECTOR3 m_rot;						// 向き
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス

	D3DXVECTOR3 m_size;						// 大きさ
	D3DXVECTOR3 m_vtxMin;					// モデルの最小値
	D3DXVECTOR3 m_vtxMax;					// モデルの最大値

	PUNCH m_type;							// パンチの種類の管理

	int m_nMovingCounter[MAX_PUNCH_CNT];	// ムーブメントカウンター
};

#endif