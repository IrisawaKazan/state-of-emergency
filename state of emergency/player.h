//==============================================================
//
// [player.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _PLAYER_H_ // このマクロ定義がされてなかったら
#define _PLAYER_H_ // 2重インクルード防止のマクロ定義

// インクルード
#include"main.h"
#include"object.h"

// マクロ定義
#define MAX_PLAYER_MOVE (0.5f * m_fDash) // プレイヤーの移動量
#define MAX_PLAYER_JUMP (2.0f)           // プレイヤーのジャンプ量
#define MAX_DASH (2.0f)                  // ダッシュの倍率

// プレイヤークラス
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetPositionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);

	void SetEnable(bool enable) { m_bUse = enable; }

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetPosOld(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetSize(void);

	bool GetEnable(void) { return m_bUse; }

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;       // メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER m_pBuffMat;  // マテリアルへのポインタ
	DWORD m_dwNumMat;         // マテリアルの数
	D3DXVECTOR3 m_pos;        // 位置
	D3DXVECTOR3 m_posOld;     // 前回の位置
	D3DXVECTOR3 m_move;       // 移動量
	D3DXVECTOR3 m_rot;        // 向き
	D3DXMATRIX m_mtxWorld;    // ワールドマトリックス

	float m_fRotation;		  // ローテーション
	D3DXVECTOR3 m_size;		  // 大きさ
	D3DXVECTOR3 m_vtxMin;	  // モデルの最小値
	D3DXVECTOR3 m_vtxMax;	  // モデルの最大値

	bool m_bJump;             // ジャンプしているかどうか
	int m_nJumpCnt;           // ジャンプカウンター
	bool m_bJumpCnt;          // ジャンプカウンターの抑制

	bool m_bUse;			  // 使用しているか

	float m_fDash;            // 走る
};

#endif