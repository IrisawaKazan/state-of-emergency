//==============================================================
//
// [light.h]
// Author: Irisawa Kazan
//
//==============================================================
#include"light.h"
#include"manager.h"
#include"renderer.h"

//----------------------------------------
// コンストラクタ
//----------------------------------------
CLight::CLight()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_aLight[nCnt] = D3DLIGHT9();
	}
}

//----------------------------------------
// デストラクタ
//----------------------------------------
CLight::~CLight()
{

}

//----------------------------------------
// ライトの初期化処理
//----------------------------------------
HRESULT CLight::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir; // ライトの方向ベクトル

	// ライトをクリアする
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	//=========
	// ライト0
	//=========
	// ライト0の情報を設定
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// ライト0の拡散光を設定
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト0の方向を設定
	vecDir = D3DXVECTOR3(1.5f, -1.5f, -1.5f);

	// 正規化する(大きさ位置のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[0].Direction = vecDir;

	// ライト0の設定をする
	pDevice->SetLight(0, &m_aLight[0]);

	// ライト0を有効にする(ON,OFF)
	pDevice->LightEnable(0, TRUE);

	//=========
	// ライト1
	//=========
	// ライト1の情報を設定
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	// ライト1の拡散光を設定
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト1の方向を設定
	vecDir = D3DXVECTOR3(-1.5f, -1.5f, 1.5f);

	// 正規化する(大きさ位置のベクトルにする)
	D3DXVec3Normalize(&vecDir, &vecDir);

	m_aLight[1].Direction = vecDir;

	// ライト1の設定をする
	pDevice->SetLight(1, &m_aLight[1]);

	// ライト1を有効にする(ON,OFF)
	pDevice->LightEnable(1, TRUE);

	////=========
	//// ライト2
	////=========
	//// ライト2の情報を設定
	//m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//// ライト2の拡散光を設定
	//m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ライト2の方向を設定
	//vecDir = D3DXVECTOR3(-1.5f, -1.5f, -1.5f);

	//// 正規化する(大きさ位置のベクトルにする)
	//D3DXVec3Normalize(&vecDir, &vecDir);

	//m_aLight[2].Direction = vecDir;

	//// ライト2の設定をする
	//pDevice->SetLight(2, &m_aLight[2]);

	//// ライト2を有効にする(ON,OFF)
	//pDevice->LightEnable(2, TRUE);

	////=========
	//// ライト3
	////=========
	//// ライト3の情報を設定
	//m_aLight[3].Type = D3DLIGHT_DIRECTIONAL;

	//// ライト3の拡散光を設定
	//m_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ライト3の方向を設定
	//vecDir = D3DXVECTOR3(1.5f, -1.5f, 1.5f);

	//// 正規化する(大きさ位置のベクトルにする)
	//D3DXVec3Normalize(&vecDir, &vecDir);

	//m_aLight[3].Direction = vecDir;

	//// ライト3の設定をする
	//pDevice->SetLight(3, &m_aLight[3]);

	//// ライト3を有効にする(ON,OFF)
	//pDevice->LightEnable(3, TRUE);

	return S_OK;
}

//----------------------------------------
// ライトの終了処理
//----------------------------------------
void CLight::Uninit(void)
{

}

//----------------------------------------
// ライトの更新処理
//----------------------------------------
void CLight::Update(void)
{

}