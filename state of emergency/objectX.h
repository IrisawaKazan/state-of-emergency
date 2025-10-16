//==============================================================
//
// [objectX.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _OBJECTX_H_ // このマクロ定義がされてなかったら
#define _OBJECTX_H_ // 2重インクルード防止のマクロ定義

#include"main.h"
#include"object.h"

// マクロ定義
#define MAX_PMOVE (2.0f) // プレーヤーの速さ

// オブジェクトXクラス
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 3);
	~CObjectX();

	static CObjectX* Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetPositionOld(D3DXVECTOR3 posOld);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetDeadCounter(int DeadCounter);
	void SetBonus(int bonus);

	void SetEnable(bool enable);
	void SetSigns(bool signs);
	void SetPowerUp(bool powerup);
	void SetScoreBonus(bool scorebonus);

	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetPosOld(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetSize(void);
	int GetDeadCounter(void);
	int GetBonus(void);

	bool GetEnable(void);
	bool GetSigns(void);
	bool GetPowerUp(void);
	bool GetScoreBonus(void);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;       // メッシュ(頂点座標)へのポインタ
	LPD3DXBUFFER m_pBuffMat;  // マテリアルへのポインタ
	DWORD m_dwNumMat;         // マテリアルの数
	D3DXVECTOR3 m_pos;        // 位置
	D3DXVECTOR3 m_posOld;     // 前回の位置
	D3DXVECTOR3 m_rot;        // 向き
	D3DXMATRIX m_mtxWorld;    // ワールドマトリックス

	float m_fRotation;		  // ローテーション
	D3DXVECTOR3 m_size;		  // 大きさ
	D3DXVECTOR3 m_vtxMin;	  // モデルの最小値
	D3DXVECTOR3 m_vtxMax;	  // モデルの最大値

	bool m_bUse;			  // 使用しているか
	bool m_bRetention;		  // アイテムを保持しているか
	bool m_bPowerUp;		  // パワーアップしているか
	bool m_bScoreBonus;		  // スコアボーナスタイムか

	int m_nScoreBonus;		  // スコアボーナスの倍率

	int m_nCounter;           // スコアで使うカウンター
	int m_nDeadCounter;       // 死までのカウンター
	int m_nPowerUpCounter;    // パワーアップ時に使うカウンター
	int m_nScoreBonusCounter; // スコアボーナス時に使うカウンター

	float m_fSpeedUp;         // パワーアップ時にプレイヤーの移動速度が速くなる
};

#endif