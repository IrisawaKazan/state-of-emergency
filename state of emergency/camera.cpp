//==============================================================
//
// [camera.cpp]
// Author: Irisawa Kazan
//
//==============================================================
#include"camera.h"
#include"manager.h"
#include"renderer.h"
#include"input.h"

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
	// 視点,注視点,上方向を設定する
	m_posV = D3DXVECTOR3(0.0f, 375.0f, -1.0f);
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