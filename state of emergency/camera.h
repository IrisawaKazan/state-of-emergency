//==============================================================
//
// [camera.h]
// Author: Irisawa Kazan
//
//==============================================================
#ifndef _CAMERA_H_ // このマクロ定義がされてなかったら
#define _CAMERA_H_ // 2重インクルード防止のマクロ定義

#include"main.h"

// カメラクラス
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

private:
	D3DXMATRIX m_mtxView;       // ビューマトリックス
	D3DXMATRIX m_mtxProjection; // プロジェクションマトリックス
	D3DXVECTOR3 m_posV;         // 視点
	D3DXVECTOR3 m_posR;         // 注視点
	D3DXVECTOR3 m_vecU;         // 上方向ベクトル
	D3DXVECTOR3 m_rot;          // 向き(角度)
	float m_fDistance;          // 視点から注視点までの距離
};

#endif