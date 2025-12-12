//==============================================================
//
// [camera.cpp]
// Author: Irisawa Kazan
//
//==============================================================
// インクルード
#include"camera.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"
#include"debugproc.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CCamera::CCamera()
{
	m_mtxView = D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	m_mtxProjection = D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = 0.0f;
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CCamera::~CCamera()
{

}

//----------------------------------------
// カメラの初期化処理
//----------------------------------------
HRESULT CCamera::Init(void)
{
	// 視点, 注視点, 上方向を設定する
	m_posV = D3DXVECTOR3(0.0f, 500.0f, -300.0f);
	m_posR = D3DXVECTOR3(0.0f, -120.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = sqrtf((m_posR.x - m_posV.x) * (m_posR.x - m_posV.x) +
		(m_posR.y - m_posV.y) * (m_posR.y - m_posV.y) +
		(m_posR.z - m_posV.z) * (m_posR.z - m_posV.z));

	return S_OK;
}

//----------------------------------------
// カメラの終了処理
//----------------------------------------
void CCamera::Uninit(void)
{

}

//----------------------------------------
// カメラの更新処理
//----------------------------------------
void CCamera::Update(void)
{
/*
#ifdef _DEBUG // Debug時のみ

	// キーボードの取得
	CInputKeyboard* pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 注視点の旋回
	if (pInputKeyboard->GetPress(DIK_NUMPAD7) == true)
	{
		m_rot.y -= 0.02f;

		// 角度の正規化
		if (-D3DX_PI > m_rot.y)
		{
			m_rot.y = m_rot.y + D3DX_PI * 2.0f;
		}

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	else if (pInputKeyboard->GetPress(DIK_NUMPAD9) == true)
	{
		m_rot.y += 0.02f;

		// 角度の正規化
		if (D3DX_PI < m_rot.y)
		{
			m_rot.y = m_rot.y - D3DX_PI * 2.0f;
		}

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

	// 視点の旋回
	if (pInputKeyboard->GetPress(DIK_NUMPAD1) == true)
	{
		m_rot.y -= 0.02f;

		// 角度の正規化
		if (-D3DX_PI > m_rot.y)
		{
			m_rot.y = m_rot.y + D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}
	else if (pInputKeyboard->GetPress(DIK_NUMPAD3) == true)
	{
		m_rot.y += 0.02f;

		// 角度の正規化
		if (D3DX_PI < m_rot.y)
		{
			m_rot.y = m_rot.y - D3DX_PI * 2.0f;
		}

		m_posV.x = m_posR.x - sinf(m_rot.y) * m_fDistance;
		m_posV.z = m_posR.z - cosf(m_rot.y) * m_fDistance;
	}

	// カメラの移動
	if (pInputKeyboard->GetPress(DIK_NUMPAD4) == true)
	{// 左
		if (pInputKeyboard->GetPress(DIK_NUMPAD8) == true)
		{// 左上に移動
			// 左
			m_posV.x -= cosf(m_rot.y) * 1.0f;
			m_posV.z += sinf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;

			// 上
			m_posV.x += sinf(m_rot.y) * 1.0f;
			m_posV.z += cosf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
		else if (pInputKeyboard->GetPress(DIK_NUMPAD2) == true)
		{// 左下に移動
			// 左
			m_posV.x -= cosf(m_rot.y) * 1.0f;
			m_posV.z += sinf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;

			// 下
			m_posV.x -= sinf(m_rot.y) * 1.0f;
			m_posV.z -= cosf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
		else
		{// 左に移動
			m_posV.x -= cosf(m_rot.y) * 1.0f;
			m_posV.z += sinf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_NUMPAD6) == true)
	{// 右
		if (pInputKeyboard->GetPress(DIK_NUMPAD8) == true)
		{// 右上に移動
			// 右
			m_posV.x += cosf(m_rot.y) * 1.0f;
			m_posV.z -= sinf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;

			// 上
			m_posV.x += sinf(m_rot.y) * 1.0f;
			m_posV.z += cosf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
		else if (pInputKeyboard->GetPress(DIK_NUMPAD2) == true)
		{// 右下に移動
			// 右
			m_posV.x += cosf(m_rot.y) * 1.0f;
			m_posV.z -= sinf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;

			// 下
			m_posV.x -= sinf(m_rot.y) * 1.0f;
			m_posV.z -= cosf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
		else
		{// 右に移動
			m_posV.x += cosf(m_rot.y) * 1.0f;
			m_posV.z -= sinf(m_rot.y) * 1.0f;

			m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
			m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_NUMPAD8) == true)
	{// 上
		m_posV.x += sinf(m_rot.y) * 1.0f;
		m_posV.z += cosf(m_rot.y) * 1.0f;

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}
	else if (pInputKeyboard->GetPress(DIK_NUMPAD2) == true)
	{// 下
		m_posV.x -= sinf(m_rot.y) * 1.0f;
		m_posV.z -= cosf(m_rot.y) * 1.0f;

		m_posR.x = m_posV.x + sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.y) * m_fDistance;
	}

#endif
*/
}

//----------------------------------------
// カメラの設定処理
//----------------------------------------
void CCamera::SetCamera(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}